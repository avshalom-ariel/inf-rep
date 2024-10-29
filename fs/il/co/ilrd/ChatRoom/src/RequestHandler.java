
import java.io.*;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.util.*;

public class RequestHandler {
    private final Map<SelectableChannel, String> channels = new HashMap<>();
    private volatile boolean isRunning = false;
    private final SelectorWrapper selector;

    public RequestHandler(InetAddress address, int port) {
        try {
            this.selector = new SelectorWrapper();
            registerServer(address, port);
        } catch (IOException e) {
            throw new RuntimeException("couldn't open selector");
        }
    }

    /////////////// Server Methods ////////////////

    public void start() throws IOException {
        isRunning = true;
        new Thread(this::serverRoutine).start();
    }

    public void stop() throws IOException {
        isRunning = false;
        selector.wakeup();
        selector.close();
    }

    public void serverRoutine(){
        while (isRunning) {
            try {
                selector.select();

                Set<SelectionKey> selectedKeys = selector.selectedKeys();
                Iterator<SelectionKey> iterator = selectedKeys.iterator();
                while (isRunning && iterator.hasNext()) {
                    SelectionKey key = iterator.next();
                    iterator.remove();

                    if (key.isAcceptable() && key.channel() instanceof ServerSocketChannel) {
                        acceptClient(key);
                    }
                    if (key.isReadable()) {
                        if (key.channel() instanceof SocketChannel) {
                            readTCPClient(key);
                        }
                    }
                }
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }

    /////////////// Selector Methods ////////////////

    private void registerServer(InetAddress address, int port) throws IOException {
        ServerSocketChannel server = ServerSocketChannel.open();
        server.bind(new InetSocketAddress(address, port));
        server.configureBlocking(false);
        selector.registerTCPServer(server, SelectionKey.OP_ACCEPT);
    }

    private void acceptClient(SelectionKey key) throws IOException {
        ServerSocketChannel server = (ServerSocketChannel) key.channel();
        SocketChannel clientChannel = server.accept();
        clientChannel.configureBlocking(false);

        System.out.println("Accepted connection from client: " + clientChannel.getRemoteAddress());
        selector.registerTCP(clientChannel, SelectionKey.OP_READ);
    }

    /////////////// Selector Loop Methods ////////////////

    private void readTCPClient(SelectionKey key) throws IOException {
        SocketChannel client = (SocketChannel) key.channel();
        Message message = getMessageFromTCPChannel(client);

        if(null == message){
            System.out.println("couldnt get message from client");
            return;
        }
        handleMessage(client, message);
    }

    /////////////// Case handlers ////////////////

    private void registerHandler(SocketChannel client, Message message) throws IOException {
        Message response = null;
        if (!channels.containsKey(client) && !channels.containsKey(message.getMessage())) {
            channels.put(client, message.getMessage());
            System.out.println("Client " + message.getMessage() + " has been registered.");
            response = new Message(message.getMessage(), MessageType.REGISTER_APPROVED);
            sendMessage(client, response);

            response = new Message(message.getMessage() + " registered", MessageType.BROADCAST_MESSAGE);

            broadcastMessageHandler(client, response);
        } else {
            response = new Message("Client already registered!", MessageType.REGISTER_DECLINED);
        }

        sendMessage(client, response);
    }

    private void unregisterHandler(SocketChannel client, Message message) throws IOException {
        Message response = null;
        if (channels.containsKey(client)) {
            channels.remove(client);
            System.out.println("Client " + message.getMessage() + " has been unregistered.");
            response = new Message("Unregistered successfully", MessageType.UNREGISTER_APPROVED);
            sendMessage(client, response);
            client.close();
        } else {
            response = new Message("Client not registered!", MessageType.UNREGISTER_DECLINED);
            sendMessage(client, response);
        }
    }

    private void broadcastMessageHandler(SocketChannel client, Message message) throws IOException {
        Message response = null;
        if (channels.containsKey(client)) {
            System.out.println("[" + channels.get(client) + "] " + message.getMessage());
            response = new Message( "[" + channels.get(client) + "] " + message.getMessage(), MessageType.BROADCAST_MESSAGE);
            broadcast(response);
        } else {
            response = new Message("Please register first", MessageType.MESSAGE_DECLINED);
            sendMessage(client, response);
        }
    }

    ///////////// Help Methods ////////////////

    private void handleMessage(SocketChannel client, Message message) throws IOException {
        switch (message.getMessageType()) {
            case REGISTER:
                registerHandler(client, message);
                break;
            case UNREGISTER:
                unregisterHandler(client, message);
                break;
            case SEND_MESSAGE:
                broadcastMessageHandler(client, message);
                break;
            default:
                Message response = new Message("Invalid message type", MessageType.MESSAGE_DECLINED);
                sendMessage(client, response);
        }
    }

    private void sendMessage(SocketChannel client, Message message) throws IOException {
        ByteBuffer buffer = ByteBuffer.wrap(serializeMessage(message));
        while (buffer.hasRemaining()) {
            client.write(buffer);
        }
    }

    private void broadcast(Message message) {
        for (SelectableChannel channel : channels.keySet()) {
            try {
                sendMessage((SocketChannel)channel, message);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }

    private Message getMessageFromTCPChannel(SocketChannel client) throws IOException {
        ByteBuffer buffer = ByteBuffer.allocate(2048);

        int bytesRead = client.read(buffer);

        if (0 >= bytesRead) {
            if (-1 == bytesRead) {
                client.close();
            }
            return null;
        }
        buffer.flip();
        byte[] bytes = new byte[buffer.remaining()];
        buffer.get(bytes);

        return deserializeMessage(bytes);
    }

    ///////////////// Serializations ///////////////////////

    public static byte[] serializeMessage(Message message) throws IOException {
        ByteArrayOutputStream bytesOut = new ByteArrayOutputStream();
        ObjectOutputStream oos = new ObjectOutputStream(bytesOut);
        oos.writeObject(message);
        oos.flush();
        byte[] bytes = bytesOut.toByteArray();
        bytesOut.close();
        oos.close();
        return bytes;
    }

    public static Message deserializeMessage(byte[] bytes) throws IOException {
        ByteArrayInputStream byteArrayInputStream = new ByteArrayInputStream(bytes);
        Message message = null;
        try (ObjectInputStream objectInputStream = new ObjectInputStream(byteArrayInputStream)) {
            message = (Message) objectInputStream.readObject();

        } catch (ClassNotFoundException e) {
            System.out.println("In Here" + e.getMessage());
            throw new RuntimeException(e);
        }
        return message;
    }
}

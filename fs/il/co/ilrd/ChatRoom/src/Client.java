
import java.io.*;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.Scanner;

public class Client {
    private final SocketChannel socketChannel;
    private final Scanner scanner = new Scanner(System.in);
    private volatile boolean isRunning = false;

    public Client(InetAddress host, int port) throws IOException {
        socketChannel = SocketChannel.open(new InetSocketAddress(host, port));
    }

    public void start() {
        try {
            isRunning = true;
            enterChatroom();
            new Thread(this::receiveMessages).start();
            sendMessages();
        } catch (IOException e) {
            throw new RuntimeException(e);
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }

        unregister();
        close();
    }

    private void enterChatroom() throws IOException, ClassNotFoundException {
        while (isRunning) {
            System.out.print("Enter username: ");
            String username = scanner.nextLine();
            if (!username.isEmpty()) {
                sendMessage(new Message(username, MessageType.REGISTER));
                Message response = getMessageFromServer();
                if (response.getMessageType() == MessageType.REGISTER_APPROVED) {
                    System.out.println("registered: " + response.getMessage());
                    break;
                } else {
                    System.out.println("register failed: " + response.getMessage());
                }
            }
        }
    }

    private void sendMessages() throws IOException {
        System.out.println("enter '/quit' to exit.");
        while (isRunning) {
            String message = scanner.nextLine().trim();
            if ("/quit".equalsIgnoreCase(message)) {
                break;
            } else {
                sendMessage(new Message(message, MessageType.SEND_MESSAGE));
            }
        }
    }

    private void receiveMessages() {
        try {
            while (isRunning) {
                Message message = getMessageFromServer();
                System.out.println(message.getMessage());
            }
        } catch (IOException e) {
            if (isRunning) {
                System.out.println("Error receiving messages: " + e.getMessage());
            }
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    private void unregister() {
        try {
            System.out.println("unregistering....");
            sendMessage(new Message("", MessageType.UNREGISTER));
        } catch (IOException e) {
            System.out.println("Error during unregister: " + e.getMessage());
        } finally {
            isRunning = false;
        }
    }

    private void sendMessage(Message message) throws IOException {
        ByteBuffer buffer = serialize(message);
        socketChannel.write(buffer);
    }

    private Message getMessageFromServer() throws IOException, ClassNotFoundException {
        ByteBuffer buffer = ByteBuffer.allocate(1024);
        int bytesRead = socketChannel.read(buffer);
        if (bytesRead == -1) {
            throw new IOException("Connection closed by server");
        }
        buffer.flip();

        return deserialize(buffer);
    }

//    private ByteBuffer serialize(Message message) throws IOException {
//        try (ByteArrayOutputStream baos = new ByteArrayOutputStream();
//             ObjectOutputStream oos = new ObjectOutputStream(baos)) {
//            oos.writeObject(message);
//            return ByteBuffer.wrap(baos.toByteArray());
//        }
//    }
//
//    private Message deserialize(ByteBuffer buffer) {
//        byte[] bytes = new byte[buffer.remaining()];
//        buffer.get(bytes);
//        try (ObjectInputStream ois = new ObjectInputStream(new ByteArrayInputStream(bytes))) {
//            return (Message) ois.readObject();
//        } catch (IOException | ClassNotFoundException e) {
//            throw new RuntimeException(e);
//        }
//    }

    public static ByteBuffer serialize(Message message) throws IOException {

        ByteArrayOutputStream byteStream = new ByteArrayOutputStream();
        ObjectOutputStream output = new ObjectOutputStream(byteStream);
        output.writeObject(message);
        // output.flush();

        return  ByteBuffer.wrap(byteStream.toByteArray());
    }

    public static Message deserialize(ByteBuffer buffer)
            throws IOException, ClassNotFoundException  {
        buffer.rewind();
        buffer.flip();

        byte[] byteArray = new byte[buffer.remaining() ];
        buffer.get(byteArray);

        ByteArrayInputStream byteStream = new ByteArrayInputStream(byteArray);
        ObjectInputStream input = new ObjectInputStream(byteStream);

        return(Message) input.readObject();
    }


    private void close() {
        try {
            socketChannel.close();
            scanner.close();
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }

    public static void main(String[] args) {
        try {
            Client client = new Client(InetAddress.getByName("10.10.1.137"), 9090);
            client.start();
        } catch (IOException e) {
            System.out.println("Error starting client: " + e.getMessage());
        }
    }
}

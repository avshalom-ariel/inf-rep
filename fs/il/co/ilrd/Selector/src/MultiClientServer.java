import java.io.IOException;
import java.net.*;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

public class MultiClientServer {
    private final Selector selector;
    private Set<SelectableChannel> channelSet = new HashSet<>();
    private boolean isRunning = true;
    
    public MultiClientServer() throws IOException {
        selector = Selector.open();
    }

    public void start(){
        new Thread(() -> {
            try {
                serverRoutine();
            } catch (IOException e) {
                System.out.println("Error starting server");
            }
        }).start();
    }

    public void stop() throws IOException {
        isRunning = false;
        selector.wakeup();
        selector.close();

        for(SelectableChannel channel : channelSet){
            channel.close();
        }
    }

    public void register(int port, InetAddress address) throws IOException {
        registerTCP(address, port);
        registerUDP(address, port + 1);
        registerBroadcast(port + 2);
    }

    public void registerTCP(InetAddress address, int port) throws IOException {
        ServerSocketChannel tcpChannel = ServerSocketChannel.open();
        channelSet.add(tcpChannel);
        tcpChannel.bind(new InetSocketAddress(address, port));
        tcpChannel.configureBlocking(false);
        tcpChannel.register(selector, SelectionKey.OP_ACCEPT);
    }

    public void registerUDP(InetAddress address, int port) throws IOException {
        DatagramChannel udpChannel = DatagramChannel.open();
        channelSet.add(udpChannel);
        udpChannel.bind(new InetSocketAddress(address, port));
        udpChannel.configureBlocking(false);
        udpChannel.register(selector, SelectionKey.OP_READ);
    }

    public void registerBroadcast(int port) throws IOException {
        DatagramChannel broadcastChannel = DatagramChannel.open();
        channelSet.add(broadcastChannel);
        broadcastChannel.setOption(StandardSocketOptions.SO_BROADCAST, true);
        broadcastChannel.bind(new InetSocketAddress(port));
        broadcastChannel.configureBlocking(false);
        broadcastChannel.register(selector, SelectionKey.OP_READ);
    }

    public void serverRoutine() throws IOException {
        while (isRunning) {
            selector.select();
            Set<SelectionKey> selectedKeys = selector.selectedKeys();
            Iterator<SelectionKey> iterator = selectedKeys.iterator();

            while (iterator.hasNext()) {
                SelectionKey key = iterator.next();

                if (key.isAcceptable() && key.channel() instanceof ServerSocketChannel) {
                    acceptServer(key);
                    iterator.remove();

                }
                if (key.isReadable()) {
                    if (key.channel() instanceof SocketChannel) {
                        readTCPClient(key);

                    } else if (key.channel() instanceof DatagramChannel) {
                        readUDPClient(key);
                    }
                }
            }
        }
    }

    private void acceptServer(SelectionKey key) throws IOException {
        ServerSocketChannel server = (ServerSocketChannel) key.channel();
        SocketChannel clientChannel = server.accept();
        clientChannel.configureBlocking(false);

        System.out.println("Accepted connection from client: " + clientChannel.getRemoteAddress());
        clientChannel.register(selector, SelectionKey.OP_READ);
    }

    private void readTCPClient(SelectionKey key) throws IOException {
        SocketChannel client = (SocketChannel) key.channel();
        channelSet.add(client);
        String message = getMessageFromTCPChannel(client);
        if(null == message){
            return;
        }
        System.out.println("Server received: " + message);

        ByteBuffer buffer = setBuffer(message);;

        buffer.flip();
        client.write(buffer);
        buffer.clear();
    }

    private String getMessageFromTCPChannel(SocketChannel client) throws IOException {
        ByteBuffer buffer = ByteBuffer.allocate(1024);
        if(client.read(buffer) == -1){
            return null;
        }
        String strFromClient = new String(buffer.array(), buffer.arrayOffset(), buffer.position());
        strFromClient = strFromClient.replaceAll("\n", "").replaceAll("\r", "");
        buffer.clear();
        return strFromClient;
    }

    private void readUDPClient(SelectionKey key) throws IOException {
        DatagramChannel clientChannel = (DatagramChannel)key.channel();
        ByteBuffer buffer = ByteBuffer.allocate(1024);
        SocketAddress clientAddress = clientChannel.receive(buffer);

        buffer.flip();
        String message = new String(buffer.array()).trim();
        System.out.println("Server received: " + message);

        buffer = setBuffer(message);
        buffer.flip();

        if (null != clientAddress && null != message){
            clientChannel.send(buffer, clientAddress);
        }
        buffer.clear();
    }

    private ByteBuffer setBuffer(String message){
        ByteBuffer buffer = ByteBuffer.allocate(256);
        if("Ping".equals(message)){
            buffer.put("Pong".getBytes());
        }
        else if("Ping".equals(message)){
            buffer.put("Ping".getBytes());
        }
        else{
            buffer.put("Error".getBytes());
        }
        return buffer;
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        MultiClientServer multiClientServer = new MultiClientServer();
        multiClientServer.register(60001, InetAddress.getByName("localhost"));

        multiClientServer.start();
        Thread.sleep(10000);
        multiClientServer.stop();

    }
}
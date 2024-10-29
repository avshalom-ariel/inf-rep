import java.io.*;
import java.net.InetAddress;
import java.nio.channels.*;
import java.util.*;

public class ChatRoomServer {
    private final Map<SelectableChannel, String> channels = new HashMap<>();
    private ServerSocketChannel server;
    private RequestHandler requestHandler;

    public ChatRoomServer(InetAddress address, int port) {
        requestHandler = new RequestHandler(address, port);
    }

    /////////////// Server Methods ////////////////

    public void start() throws IOException {
        requestHandler.start();
    }

    public void stop() throws IOException {
        requestHandler.stop();
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        ChatRoomServer server = new ChatRoomServer(InetAddress.getByName("10.1.0.11"), 12345);

        server.start();
        Thread.sleep(100000);
        server.stop();
    }
}

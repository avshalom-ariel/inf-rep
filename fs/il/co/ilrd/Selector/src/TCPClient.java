import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.Scanner;

public class TCPClient {
    private boolean isRunning = true;

    public void start(final int portNumber, String hostName) throws IOException, InterruptedException {
        try (SocketChannel channel = SocketChannel.open()) {
//            Scanner scanner = new Scanner(System.in);
//            byte[] message = scanner.nextLine().getBytes();

            InetSocketAddress serverAddress = new InetSocketAddress(hostName, portNumber);
            channel.connect(serverAddress);

            System.out.print("Enter your name: ");
            String message = "Ping";

            ByteBuffer byteBuffer = ByteBuffer.allocate(512);
            while (isRunning) {
                //prepare a message for the server:
                byteBuffer.clear();
                byteBuffer.put(message.getBytes());
                byteBuffer.flip(); //flip buffer to prepare for writing to the channel
                //write the message to the server:
                while (byteBuffer.hasRemaining()) {
                    channel.write(byteBuffer);
                }

                //read response from server:
                byteBuffer.clear();
                int bytesRead = channel.read(byteBuffer);
//                System.out.println(message);
                if (bytesRead > 0) {
                    byteBuffer.flip();  //prepare buffer for reading
                    byte[] response = new byte[bytesRead];
                    byteBuffer.get(response);
                    System.out.println("Client" + Thread.currentThread().getName() + "received: " + new String(response));
                }

                Thread.sleep(1000);
            }
        }
    }

    public void stop() {
        isRunning = false;
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        TCPClient client = new TCPClient();
        client.start(60001, "localhost");
        Thread.sleep(10000);
        client.stop();
    }
}

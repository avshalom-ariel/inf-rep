import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.DatagramChannel;

public class UDPClient {
    private boolean isRunning = true;

    public void start(final int serverPort, String serverAddress) throws IOException, InterruptedException {
        String message = "Ping";

        try (DatagramChannel channel = DatagramChannel.open()) {
            InetSocketAddress serverSocketAddress = new InetSocketAddress(InetAddress.getByName(serverAddress), serverPort);

            // Prepare the message in a byte buffer
            while(isRunning) {
                ByteBuffer buffer = ByteBuffer.wrap(message.getBytes());

                // Send the packet
                channel.send(buffer, serverSocketAddress);
    //               System.out.println("Message sent: " + message);

                // Prepare a buffer to receive the server's response
                byte[] receiveBuffer = new byte[256];
                ByteBuffer receivedBuffer = ByteBuffer.wrap(receiveBuffer);

                // Receive the response
                channel.receive(receivedBuffer);
                Thread.sleep(1000);
                String response = new String(receivedBuffer.array()).trim();
                System.out.println("Client received: " + response);
                buffer.clear();
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void stop() {
        isRunning = false;
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        UDPClient client = new UDPClient();
        client.start(60002, "localhost");
        Thread.sleep(10000);
        client.stop();
    }
}

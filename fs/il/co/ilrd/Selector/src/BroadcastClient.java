import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.StandardSocketOptions;
import java.nio.ByteBuffer;
import java.nio.channels.DatagramChannel;

public class BroadcastClient {
    private boolean isRunning = true;

    public void start(final int portNumber) throws InterruptedException {
        String broadcastMessage = "Ping";

        try (DatagramChannel channel = DatagramChannel.open()) {
            channel.setOption(StandardSocketOptions.SO_BROADCAST, true);  // Enable broadcast mode
            InetSocketAddress broadcastAddress = new InetSocketAddress(InetAddress.getByName("255.255.255.255"), portNumber);

            while (isRunning) {
                ByteBuffer buffer = ByteBuffer.wrap(broadcastMessage.getBytes());
                channel.send(buffer, broadcastAddress);

                ByteBuffer receivedBuffer = ByteBuffer.wrap(new byte[256]);
                channel.receive(receivedBuffer);
                String response = new String(receivedBuffer.array()).trim();

                System.out.println("Broadcast client received: " + response);

                Thread.sleep(1000);
            }
        } catch(IOException e){
            e.printStackTrace();
        }
    }

    public void stop() {
        isRunning = false;
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        BroadcastClient client = new BroadcastClient();
        client.start(60003);
        Thread.sleep(10000);
        client.stop();
    }
}

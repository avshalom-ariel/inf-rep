import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

import static java.lang.Thread.sleep;

public class PingPongUDPSocket {

    public static class Client {

        public void connectToServer() throws IOException {
            int port = 60001;

            Scanner scanner = new Scanner(System.in);
            try (DatagramSocket socket = new DatagramSocket()) {

                while (true) {
                    byte[] sendBuffer = scanner.nextLine().getBytes();
                    InetAddress address = InetAddress.getByName("localhost");
                    DatagramPacket sendPacket = new DatagramPacket(sendBuffer, sendBuffer.length, address, port);
                    socket.send(sendPacket);

                    byte[] receiveBuffer = new byte[1024];
                    DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);

                    socket.receive(receivePacket);

                    String responseMessage = new String(receivePacket.getData(), 0, receivePacket.getLength());

                    System.out.println("        " + responseMessage);
                }
            }
        }
    }
    public static class Server {

        public void startService() throws IOException, InterruptedException {
            int port = 60001;
            try (DatagramSocket socket = new DatagramSocket(port)) {

                while (true) {
                    byte[] receiveBuffer = new byte[1024];
                    DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);

                    socket.receive(receivePacket);

                    String message = new String(receivePacket.getData(), 0, receivePacket.getLength());

                    String responseMessage = "";
                    if ("Ping".equals(message)) {
                        responseMessage = "Pong";
                    } else if ("Pong".equals(message)) {
                        responseMessage = "Ping";
                    } else {
                        responseMessage = "error";
                    }


                    byte[] sendBuffer = responseMessage.getBytes();
                    DatagramPacket sendPacket = new DatagramPacket(
                            sendBuffer,
                            sendBuffer.length,
                            receivePacket.getAddress(),
                            receivePacket.getPort()
                    );
                    socket.send(sendPacket);
                }
            }
        }
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        Client client = new Client();
        Server server = new Server();

        Thread thread = new Thread(()-> {
            try {
                server.startService();
            } catch (IOException | InterruptedException e) {
                throw new RuntimeException(e);
            }
        });
        thread.start();
        sleep(2000);
        client.connectToServer();

    }
}

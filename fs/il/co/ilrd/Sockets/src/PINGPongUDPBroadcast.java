import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

import static java.lang.Thread.sleep;

public class PINGPongUDPBroadcast {

    public static class Server {
        public static void startService() {
            int port = 60001;

            try (DatagramSocket socket = new DatagramSocket(port)) {
                socket.setBroadcast(true); // Enable broadcast mode

                while (true) {
                    byte[] receiveBuffer = new byte[1024];
                    DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);

                    socket.receive(receivePacket);

                    String message = new String(receivePacket.getData(), 0, receivePacket.getLength());

                    String responseMessage = "";
                    if (message.equals("Ping")) {
                        responseMessage = "Pong";
                    } else if (message.equals("Pong")) {
                        responseMessage = "Ping";
                    } else {
                        responseMessage = "Error";
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
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    public static class Client1 {
        public static void connectToServer() {
            String broadcastAddress = "255.255.255.255";
            int port = 60001;
            Scanner scanner = new Scanner(System.in);

            try (DatagramSocket socket = new DatagramSocket()) {
                socket.setBroadcast(true);

                InetAddress address = InetAddress.getByName(broadcastAddress);

                while (true) {
                    byte[] sendBuffer = scanner.nextLine().getBytes();

                    DatagramPacket sendPacket = new DatagramPacket(sendBuffer, sendBuffer.length, address, port);
                    socket.send(sendPacket);

                    byte[] receiveBuffer = new byte[1024];
                    DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);

                    socket.receive(receivePacket);

                    String responseMessage = new String(receivePacket.getData(), 0, receivePacket.getLength());
                    System.out.println(responseMessage);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        Client1 client1 = new Client1();
        Server server = new Server();

        Thread thread = new Thread(()-> {
            server.startService();
        });
        thread.start();
        sleep(2000);
        client1.connectToServer();
    }
}

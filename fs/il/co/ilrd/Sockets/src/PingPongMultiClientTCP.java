import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.*;
import java.util.Scanner;

import static java.lang.Thread.sleep;

public class PingPongMultiClientTCP {
    static int UDPport = 60002;

    public static class Server {
        public static void startService() throws IOException, InterruptedException {
            int TCPport = 60001;

            ServerSocket serverSocket = new ServerSocket(TCPport);

            try (DatagramSocket socket = new DatagramSocket()) {
                byte[] sendBuffer = "Ping".getBytes();
                InetAddress address = InetAddress.getByName("localhost");
                DatagramPacket sendPacket = new DatagramPacket(sendBuffer, sendBuffer.length, address, UDPport);
                socket.send(sendPacket);
            }

            while (true) {
                Socket socket = serverSocket.accept();
                new Thread(()-> {
                    try {
                        connect(socket);
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                }).start() ;
            }
        }

        public static void connect(Socket socket) throws IOException, InterruptedException {
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            while (true) {
                String line = in.readLine();
                System.out.println("server received:" + line);
                if (line.equals("Ping")) {
                    out.println("       Pong");
                } else if (line.equals("Pong")) {
                    out.println("Ping");
                } else {
                    System.out.println("error");
                    break;
                }
            }
        }
    }


    public static class Client {
        public static void connectToServer() throws IOException, InterruptedException {
            Socket socket = new Socket("localhost", 60001);
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
//            Scanner scanner = new Scanner(System.in);

            while (true) {
//                String message = scanner.nextLine();
                String message = "Ping";
                out.println(message);
                String receivedMessage = in.readLine();
                System.out.println("Client: " + Thread.currentThread().getName() + receivedMessage);
                Thread.sleep(10000);
            }
        }
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        Server server = new Server();

        Client client = new Client();
        Client client2 = new Client();
        Client client3 = new Client();
        Client client4 = new Client();

        Thread thread = new Thread(()-> {
            try {
                server.startService();
            } catch (IOException | InterruptedException e) {
                throw new RuntimeException(e);
            }
        });
        thread.start();
        sleep(2000);
        Thread thread1 = new Thread(()-> {
            try {
                client.connectToServer();
            } catch (IOException | InterruptedException e) {
                throw new RuntimeException(e);
            }
        });
        thread1.start();
        Thread thread2 = new Thread(()-> {
            try {
                client2.connectToServer();
            } catch (IOException | InterruptedException e) {
                throw new RuntimeException(e);
            }
        });
        thread2.start();
        Thread thread3 = new Thread(()-> {
            try {
                client3.connectToServer();
            } catch (IOException | InterruptedException e) {
                throw new RuntimeException(e);
            }
        });
        thread3.start();
        Thread thread4 = new Thread(()-> {
            try {
                client4.connectToServer();
            } catch (IOException | InterruptedException e) {
                throw new RuntimeException(e);
            }
        });
        thread4.start();
    }
}

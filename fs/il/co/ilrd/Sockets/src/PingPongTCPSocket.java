import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

import static java.lang.Thread.sleep;

public class PingPongTCPSocket {
    public static class Client {
        public static void connectToServer() throws IOException, InterruptedException {
            Socket socket = new Socket("localhost", 60001);
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);  //true for auto-flush buffer
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            Scanner scanner = new Scanner(System.in);

            while (true) {
                String message = scanner.nextLine();
                out.println(message);
                String receivedMessage = in.readLine();
                System.out.println(receivedMessage);
            }
        }
    }
    public static class Server {
        public static void startService() throws IOException, InterruptedException {
            ServerSocket serverSocket = new ServerSocket(60001);

            Socket socket = serverSocket.accept();

            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            while (true) {
                String line = in.readLine();
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

    public static void main(String[] args) throws IOException, InterruptedException {
        Server server = new Server();
        Client client = new Client();

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
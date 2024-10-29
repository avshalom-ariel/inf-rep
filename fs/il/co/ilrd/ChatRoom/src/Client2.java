import java.io.*;
import java.net.InetAddress;

public class Client2 {
    public static void main(String[] args) {
        try {
            Client client = new Client(InetAddress.getByName("10.1.0.11"), 1234);
            client.start();
        } catch (IOException e) {
            System.out.println("Error starting client: " + e.getMessage());
        }
    }
}

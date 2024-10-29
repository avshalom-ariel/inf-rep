

import com.google.gson.Gson;
import com.google.gson.JsonObject;

import java.io.*;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.DatagramChannel;
import java.nio.channels.SocketChannel;

public class Client {

    public static void registerTCP(InetSocketAddress address) throws IOException, InterruptedException {
        SocketChannel socketChannel1 = SocketChannel.open(address);

        JsonObject jsonObject = new JsonObject();

        jsonObject.addProperty("Key", "RegCompany");

        JsonObject message = new JsonObject();
        message.addProperty("Name", "Apple");
        message.addProperty("Number of products", "5");

        jsonObject.add("Data", message);

        ByteBuffer buffer = ByteBuffer.wrap(new Gson().toJson(jsonObject).getBytes());

        socketChannel1.write(buffer);

        buffer.clear();

        ByteBuffer responseBuffer = ByteBuffer.allocate(1024);
        responseBuffer.clear();

        int byteRead = socketChannel1.read(responseBuffer);

        System.out.println("byteRead: " + byteRead);

        responseBuffer.flip();

        String reponse = new String(responseBuffer.array()).trim();

        jsonObject = new Gson().fromJson(reponse, JsonObject.class);

        System.out.println(jsonObject);

        Thread.sleep(5000);
    }

    public static void registerUDP(InetSocketAddress address) throws IOException, InterruptedException {
        DatagramChannel datagramChannel = DatagramChannel.open();

        datagramChannel.connect(address);

        JsonObject jsonObject = new JsonObject();

        jsonObject.addProperty("Key", "RegCompany");

        JsonObject message = new JsonObject();
        message.addProperty("Name", "Apple");
        message.addProperty("Number of products", "5");

        jsonObject.add("Data", message);

        ByteBuffer buffer = ByteBuffer.wrap(new Gson().toJson(jsonObject).getBytes());

        datagramChannel.send(buffer, address);

        ByteBuffer respondBuffer = ByteBuffer.allocate(1024);

        datagramChannel.receive(respondBuffer);

        String reponse = new String(respondBuffer.array()).trim();

        System.out.println(reponse);
    }

    public static void sendHTTP() {


    }

    public static void main(String[] args) throws IOException, InterruptedException {
        registerTCP(new InetSocketAddress(InetAddress.getByName("10.10.0.56"), 60000));
        registerUDP(new InetSocketAddress(InetAddress.getByName("10.10.0.56"), 60001));
        

    }
}

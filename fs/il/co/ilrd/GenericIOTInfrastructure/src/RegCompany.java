
import com.google.gson.Gson;
import com.google.gson.JsonObject;

import java.io.IOException;
import java.nio.ByteBuffer;

public class RegCompany implements Command{
    String name;
    int numOfProducts;

    public RegCompany(JsonObject data) {
        name = data.get("Name").getAsString();
        numOfProducts = data.get("Number of products").getAsInt();
    }

    @Override
    public void execute(RespondableChannel respondableChannel) {
        System.out.println("Company Registered successfully!");
        System.out.println("Company Name: " + name);
        System.out.println("Number of products: " + numOfProducts);

        JsonObject data = new JsonObject();
        data.addProperty("StatusCode", 200);
        data.addProperty("Info", "Company Registered successfully! " + name + " " + numOfProducts);
        String jsonString = new Gson().toJson(data);
//        ByteBuffer.wrap(jsonString.getBytes());

        try {
            respondableChannel.respond(ByteBuffer.wrap(jsonString.getBytes()));
        } catch (IOException e) {
            System.out.println("Cannot respond in execute");
            throw new RuntimeException(e);
        }
    }
}

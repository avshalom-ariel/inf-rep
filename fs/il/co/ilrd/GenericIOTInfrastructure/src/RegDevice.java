
public class RegDevice implements Command {
    String name;
    public RegDevice(String name) {
        this.name = name;
    }

    public RegDevice(RespondableChannel respondableChannel) {    }


    @Override
    public void execute(RespondableChannel respondableChannel) {
        System.out.println("Product Registered successfully!");
    }
}


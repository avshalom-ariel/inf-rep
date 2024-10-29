
public class RegProduct implements Command {

    @Override
    public void execute(RespondableChannel respondableChannel) {
        System.out.println("Product Registered successfully!");
    }

    public RegProduct(RespondableChannel respondableChannel) {    }

}


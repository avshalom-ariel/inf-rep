
public class RegIOT implements Command {
    private String IOTname;
    public RegIOT(String IOTname) {
        this.IOTname = IOTname;
    }

    public RegIOT(RespondableChannel respondableChannel) {    }


    @Override
    public void execute(RespondableChannel respondableChannel) {
        System.out.println("IOT Registered successfully!");
    }
}
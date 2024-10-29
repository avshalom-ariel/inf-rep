public class EagerSingleton  implements DummyInterface{
    private static final EagerSingleton INSTANCE = new EagerSingleton();

    private EagerSingleton() {}

    public static EagerSingleton getInstance() {
        return INSTANCE;
    }

    public String display() {
        return "EagerSingleton display";
    }
}

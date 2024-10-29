public class HolderIdiomSingleton {
    // Static inner class that holds the singleton instance
    private static class SingletonHolder {
        // The instance created only when the Singleton is accessed
        private static final HolderIdiomSingleton INSTANCE = new HolderIdiomSingleton();
    }

    private HolderIdiomSingleton() {}

    public static HolderIdiomSingleton getInstance() {
        return SingletonHolder.INSTANCE;
    }

    public String display() {
        return "HolderIdiomSingleton display";
    }
}

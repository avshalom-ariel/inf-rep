public class SingletonDoubleCheckLocking {
    // ensures that an attribute's value is always the same when read from all threads (no caching)
    private static volatile SingletonDoubleCheckLocking instance;

    private SingletonDoubleCheckLocking() {}

    public static SingletonDoubleCheckLocking getInstance() {
        if (instance == null) { // Check if instance is not initialized
            synchronized (SingletonDoubleCheckLocking.class) { // Synchronize to ensure thread safety
                if (null == instance) { // Double-check to prevent multiple instantiations
                    instance = new SingletonDoubleCheckLocking(); // Create the single instance
                }
            }
        }
        return instance;
    }

    public String display() {
        return "SingletonDoubleCheckLocking display";
    }
}


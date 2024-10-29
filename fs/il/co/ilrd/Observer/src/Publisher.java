public class Publisher<T> {
    private final Dispatcher<T> dispatcher = new Dispatcher<>();

    public Publisher() {}

    public void register(Callback<T> cb) {
        dispatcher.register(cb);
    }

    public void produce(T data) {
        dispatcher.updateAll(data);
    }
    public void close() {
        dispatcher.stopService();
    }
}

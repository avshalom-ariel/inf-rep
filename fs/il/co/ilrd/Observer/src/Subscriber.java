import java.util.function.Consumer;

public class Subscriber<T> {
    private Callback<T> callback;
    private T data;

    public Subscriber() {
        callback = new Callback<>(new DefaultConsumer(), ()->{});
    }
    public Subscriber(Consumer<T> consumer, Runnable runnable) {
        this.callback = new Callback<>(consumer.andThen(new DefaultConsumer()), runnable);
    }

    public void register(Publisher<T> publisher) {
        publisher.register(callback);
    }
    public void unregister() {
        callback.unregister();
    }
    public T getData() {
        return data;
    }

    private class DefaultConsumer implements Consumer<T> {
        @Override
        public void accept(T data) {
            Subscriber.this.data = data;
        }
    }
}
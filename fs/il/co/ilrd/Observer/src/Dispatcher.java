import java.util.ArrayList;

public class Dispatcher<T> {
    ArrayList<Callback<T>> list = new ArrayList<>();

    public Dispatcher() {}

    public void register(Callback<T> cb) {
        list.add(cb);
        cb.setDispatcher(this);
    }
    public void unregister(Callback<T> cb) {
        list.remove(cb);
    }
    public void updateAll(T data) {
        for (Callback<T> cb : list) {
            cb.update(data);
        }
    }
    public void stopService() {
        for (Callback<T> cb : list) {
            cb.stopUpdate();
        }
        list.clear();
    }
}
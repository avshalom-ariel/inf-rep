import java.util.Collections;
import java.util.Map;
import java.util.ArrayList;

public class Pair<K,V> implements Map.Entry<K,V> {
    private K key;
    private V value;

    public Pair(K key, V value) {
        this.key = key;
        this.value = value;
    }

    public static <K,V> Pair<V, K> swap(Pair<K, V> pair) {
        return new Pair<>(pair.getValue(), pair.getKey());
    }

    public static <K, V> Pair<K, V> of(K key, V value) {
        return new Pair<>(key, value);
    }

    public static <T extends Comparable<T>> Pair<T, T> minmax(ArrayList<T> elements) {
        return new Pair<>(Collections.min(elements), Collections.max(elements));
    }

    @Override
    public V setValue(V value) {
        V oldValue = this.value;
        this.value = value;
        return oldValue;
    }

    @Override
    public K getKey() {
        return key;
    }

    @Override
    public V getValue() {
        return value;
    }

    @Override
    public String toString() {
        return "(" + key + ", " + value + ")";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (null == o || !(o instanceof Pair)) return false;
        if (!value.equals(((Pair<K,V>)o).value)) { return false; }
        return key.equals(((Pair<K,V>)o).key);
    }

    @Override
    public int hashCode() {
        return key.hashCode();
    }
}
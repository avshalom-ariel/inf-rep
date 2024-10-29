import java.util.*;

public class HashMap<K, V> implements Map<K, V> {
    private final List<LinkedList<Map.Entry<K,V>>> container;
    public static final int DEFAULT_INITIAL_CAPACITY = 16;
    public int capacity = DEFAULT_INITIAL_CAPACITY;
    private int modCount = 0;
    Set<K> keySet = new SetOfKeys();
    Collection<V> values = new CollectionOfValues();
    Set<Entry<K, V>> entrySet = new SetOfEntries();

    public HashMap() {
        //default size of 16
        this(DEFAULT_INITIAL_CAPACITY);
    }
    public HashMap(int capacity) {
        this.capacity = capacity;
        container = new ArrayList<>(capacity);
        for (int i = 0; i < capacity; i++) {
            container.add(new LinkedList<>());
        }
    }

    //Maps Overrides
    @Override
    public int size() {
        int counter = 0;
        for (List<Map.Entry<K,V>> bucket : container) {
            counter += bucket.size();
        }
        return counter;
    }

    @Override
    public boolean isEmpty() {
        for (List<Map.Entry<K,V>> bucket : container) {
            if (!bucket.isEmpty()) {
                return false;
            }
        }
        return true;
    }

    @Override
    public boolean containsKey(Object key) {
        List<Map.Entry<K,V>> bucket = container.get(keyToIndex(key));

        for (Map.Entry<K,V> pair : bucket) {
            if(null == pair.getKey()) {
                if (null == key) {
                    return true;
                }
            } else if (pair.getKey().equals(key)) {
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean containsValue(Object value) {
        for (List<Map.Entry<K,V>> bucket : container) {
            for (Map.Entry<K,V> pair : bucket) {
                if(null == pair.getValue()) {
                    if (null == value) {
                        return true;
                    }
                } else if (pair.getValue().equals(value)) {
                    return true;
                }
            }
        }
        return false;
    }

    @Override
    public V get(Object key) {
        List<Map.Entry<K,V>> bucket = container.get(keyToIndex(key));
        for (Map.Entry<K,V> pair : bucket) {
            if(null == pair.getKey()) {
                if (null == key) {
                    return pair.getValue();
                }
            } else if (pair.getKey().equals(key)) {
                return pair.getValue();
            }
        }
        return null;
    }

    @Override
    public V put(K key, V value) {
        ++modCount;
        int index = keyToIndex(key);

        List<Map.Entry<K,V>> bucket = container.get(index);
        for (Map.Entry<K,V> pair : bucket) {
            if(null == pair.getKey()) {
                if (null == key) {
                    V oldValue = pair.getValue();
                    pair.setValue(value);
                    return oldValue;
                }
            } else if (pair.getKey().equals(key)) {
                V oldValue = pair.getValue();
                pair.setValue(value);
                return oldValue;
            }
        }
        bucket.add(new Pair<>(key, value));
        return null;
    }

    @Override
    public V remove(Object key) {
        ++modCount;
        List<Map.Entry<K,V>> bucket = container.get(keyToIndex(key));
        int indexToRemove = 0;
        V returnValue = null;
        for (Map.Entry<K,V> pair : bucket) {
            if(null == pair.getKey()) {
                if (null == key) {
                    returnValue = pair.getValue();
                    bucket.remove(indexToRemove);
                    return returnValue;
                }
            } else if (pair.getKey().equals(key)) {
                returnValue = pair.getValue();
                bucket.remove(indexToRemove);
                return returnValue;
            }
            ++indexToRemove;
        }

        return null;
    }

    @Override
    public void putAll(Map<? extends K, ? extends V> m) {
        for (Entry<? extends K, ? extends V> entry : m.entrySet()) {
            put(entry.getKey(), entry.getValue());
        }
    }

    @Override
    public void clear() {
        ++modCount;
        for (List<Map.Entry<K,V>> bucket : container) {
            bucket.clear();
        }
    }

    @Override //O(1) space
    public Set<K> keySet() {
       return keySet;
    }

    @Override  //O(1) space
    public Collection<V> values() {
        return values;
    }

    @Override  //O(1) space
    public Set<Entry<K, V>> entrySet() {
        return entrySet;
    }

    private class SetOfEntries extends AbstractSet<Map.Entry<K, V>> {
        @Override
        public Iterator<Entry<K, V>> iterator() {
            return new EntriesIterator();
        }

        @Override
        public int size() {
            return HashMap.this.size();
        }

        // Private help classes
        private class EntriesIterator  implements Iterator<Entry<K,V>> {
            int expectedModCount;
            int code = -1;

            public EntriesIterator() {
                expectedModCount = modCount;
                int bucketIndex = 0;
                for (List<Map.Entry<K,V>> bucket : container) {
                    if (!bucket.isEmpty()) {
                        code = pairToCode(0, bucketIndex);
                        return;
                    }
                    ++bucketIndex;
                }
            }

            @Override
            public boolean hasNext() {
                if (expectedModCount != HashMap.this.modCount) {
                    throw new ConcurrentModificationException();
                }

                return -1 != code;
            }

            @Override
            public Entry<K, V> next() {
                if (-1 == code) {
                    throw new NoSuchElementException();
                }
                if (expectedModCount != HashMap.this.modCount) {
                    throw new ConcurrentModificationException();
                }

                int bucketIndex = codeToBucketIndex(code);
                int pairIndex = codeToPairIndex(code);
                Map.Entry<K,V> pair = container.get(bucketIndex).get(pairIndex);

                code = getNextPair(code);

                return pair;
            }
        }
    }

    private class SetOfKeys extends AbstractSet<K> {
        @Override
        public Iterator<K> iterator() {
            return new KeysIterator();
        }

        @Override
        public int size() {
            return HashMap.this.size();
        }

        private class KeysIterator implements Iterator<K> {
            Iterator<Entry<K, V>> iterator = entrySet.iterator();

            @Override
            public boolean hasNext() {
                return iterator.hasNext();
            }

            @Override
            public K next() {

                return iterator.next().getKey();
            }
        }
    }

    private class CollectionOfValues extends AbstractCollection<V> {

        @Override
        public Iterator<V> iterator() {
            return new ValueMapIterator();
        }

        @Override
        public int size() {
            return HashMap.this.size();
        }

        private class ValueMapIterator implements Iterator<V> {
            Iterator<Entry<K, V>> iterator = entrySet.iterator();

            @Override
            public boolean hasNext() {
                return iterator.hasNext();
            }

            @Override
            public V next() {
                return iterator.next().getValue();
            }
        }
    }

    //Private helping methods
    private int pairToCode(int pairIndex, int bucketIndex) {
        return bucketIndex + pairIndex * capacity;
    }

    private int codeToBucketIndex(int code) {
        return code % capacity;
    }

    private int codeToPairIndex(int code) {
        return code / capacity;
    }

    private int getNextPair(int code) {
        int bucketIndex = codeToBucketIndex(code);
        int pairIndex = codeToPairIndex(code);

        if (pairIndex + 1 < container.get(bucketIndex).size()) {
            return pairToCode(pairIndex + 1, bucketIndex);
        }
        for (int i = bucketIndex + 1; i < capacity; i++) {
            if(!container.get(i).isEmpty()) {
                return pairToCode(0, i);
            }
        }
        return -1;
    }

    private int keyToIndex(Object key) {
        if (key == null) {
            return 0;
        }
        return Math.abs(key.hashCode() % capacity);
    }
}


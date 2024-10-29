import org.junit.*;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

import static org.junit.Assert.*;
import static org.junit.Assert.assertEquals;

public class HashMapTest {
    HashMap<Integer, String> hashMap = new HashMap<>(1024);

    @Test
    public void putTest() {
        assertEquals(null, hashMap.put(1, "Amit"));
        assertEquals("Amit", hashMap.put(1, "or"));
        assertEquals(null, hashMap.put(2, "Yarden"));
        assertEquals(null, hashMap.put(3, "Uriah"));
        assertEquals(null, hashMap.put(4, "Ido"));
        assertEquals(null, hashMap.put(5, "Itay"));
        assertEquals(null, hashMap.put(6, "Shahar"));
        assertEquals(null, hashMap.put(null, "Shahar"));
        assertEquals("Shahar", hashMap.put(null, "tal"));

    }

    @Test
    public void getTest() {
        hashMap.put(1, "Amit");
        hashMap.put(2, "Yarden");
        hashMap.put(3, "Uriah");
        hashMap.put(4, "Ido");
        hashMap.put(5, "Itay");
        hashMap.put(6, "Shahar");

        assertEquals("Amit", hashMap.get(1));
        assertEquals("Yarden", hashMap.get(2));
        assertEquals("Uriah", hashMap.get(3));
        assertEquals("Ido", hashMap.get(4));
        assertEquals("Itay", hashMap.get(5));
        assertEquals("Shahar", hashMap.get(6));
    }

    @Test
    public void removeTest() {
        hashMap.put(1, "Amit");
        hashMap.put(2, "Yarden");
        hashMap.put(3, "Uriah");
        hashMap.put(4, "Ido");
        hashMap.put(5, "Itay");
        hashMap.put(6, "Shahar");

        hashMap.remove(2);
        hashMap.remove(5);

        assertEquals("Amit", hashMap.get(1));
        assertEquals(null, hashMap.get(2));
        assertEquals("Uriah", hashMap.get(3));
        assertEquals("Ido", hashMap.get(4));
        assertEquals(null, hashMap.get(5));
        assertEquals("Shahar", hashMap.get(6));
    }

    @Test
    public void containsKeyTest() {
        hashMap.put(1, "Amit");
        hashMap.put(2, "Yarden");
        hashMap.put(3, "Uriah");
        hashMap.put(4, "Ido");
        hashMap.put(5, "Itay");
        hashMap.put(6, "Shahar");

        assertTrue(hashMap.containsKey(1));
        assertTrue(hashMap.containsKey(2));
        assertTrue(hashMap.containsKey(3));
        assertTrue(hashMap.containsKey(4));
        assertTrue(hashMap.containsKey(5));
        assertTrue(hashMap.containsKey(6));
        assertFalse(hashMap.containsKey(7));
        assertFalse(hashMap.containsKey(8));
        assertFalse(hashMap.containsKey(9));
    }

    @Test
    public void containsValueTest() {
        hashMap.put(1, "Amit");
        hashMap.put(2, "Yarden");
        hashMap.put(3, "Uriah");
        hashMap.put(4, "Ido");
        hashMap.put(5, "Itay");
        hashMap.put(6, "Shahar");

        assertTrue(hashMap.containsValue("Amit"));
        assertTrue(hashMap.containsValue("Yarden"));
        assertTrue(hashMap.containsValue("Uriah"));
        assertTrue(hashMap.containsValue("Ido"));
        assertTrue(hashMap.containsValue("Itay"));
        assertTrue(hashMap.containsValue("Shahar"));
        assertFalse(hashMap.containsValue("Oded"));
        assertFalse(hashMap.containsValue("Rina"));
        assertFalse(hashMap.containsValue("Idan"));
    }

    @Test
    public void sizeTest() {
        assertEquals(0, hashMap.size());
        hashMap.put(1, "Amit");
        assertEquals(1, hashMap.size());
        hashMap.put(2, "Yarden");
        assertEquals(2, hashMap.size());
        hashMap.put(3, "Uriah");
        assertEquals(3, hashMap.size());
        hashMap.put(4, "Ido");
        assertEquals(4, hashMap.size());
        hashMap.put(5, "Itay");
        assertEquals(5, hashMap.size());
        hashMap.put(6, "Shahar");
        assertEquals(6, hashMap.size());

        hashMap.remove(2);
        assertEquals(5, hashMap.size());
        hashMap.remove(5);
        assertEquals(4, hashMap.size());
    }

    @Test
    public void isEmpty() {
        assertTrue(hashMap.isEmpty());
        hashMap.put(1, "Amit");
        assertFalse(hashMap.isEmpty());
        hashMap.remove(1);
        assertTrue(hashMap.isEmpty());
    }

    @Test
    public void clearTest() {
        hashMap.put(1, "Amit");
        hashMap.put(2, "Yarden");
        hashMap.put(3, "Uriah");
        hashMap.put(4, "Ido");
        hashMap.put(5, "Itay");
        hashMap.put(6, "Shahar");
        hashMap.clear();
        assertTrue(hashMap.isEmpty());
    }

    @Test
    public void putAll() {
        Map<Integer, String> myMap = new ConcurrentHashMap<>();
        myMap.put(1, "Amit");
        myMap.put(2, "Yarden");
        myMap.put(3, "Uriah");
        myMap.put(4, "Ido");
        myMap.put(5, "Itay");
        myMap.put(6, "Shahar");

        hashMap.putAll(myMap);
        assertEquals("Amit", hashMap.get(1));
        assertEquals("Yarden", hashMap.get(2));
        assertEquals("Uriah", hashMap.get(3));
        assertEquals("Ido", hashMap.get(4));
        assertEquals("Itay", hashMap.get(5));
        assertEquals("Shahar", hashMap.get(6));
    }

    @Test
    public void keySetTest() {
        hashMap.put(6, "Shahar");
        hashMap.put(1, "Amit");
        hashMap.put(4, "Ido");
        hashMap.put(3, "Uriah");
        hashMap.put(2, "Yarden");
        hashMap.put(5, "Itay");
        Set<Integer> keySet = hashMap.keySet();
        Iterator<Integer> iter = keySet.iterator();

        assertTrue(iter.hasNext());
        System.out.println(iter.next());
        assertTrue(iter.hasNext());
        System.out.println(iter.next());
        assertTrue(iter.hasNext());
        System.out.println(iter.next());
        assertTrue(iter.hasNext());
        System.out.println(iter.next());
        assertTrue(iter.hasNext());
        System.out.println(iter.next());
        assertTrue(iter.hasNext());
        System.out.println(iter.next());
        assertFalse(iter.hasNext());
    }

    @Test
    public void valuesTest() {
        hashMap.put(6, "Shahar");
        hashMap.put(1, "Amit");
        hashMap.put(4, "Ido");
        hashMap.put(3, "Uriah");
        hashMap.put(2, "Yarden");
        hashMap.put(5, "Itay");
        Collection<String> values = hashMap.values();
        Iterator<String> iter = values.iterator();

        assertTrue(iter.hasNext());
        System.out.println(iter.next());
        assertTrue(iter.hasNext());
        System.out.println(iter.next());
        assertTrue(iter.hasNext());
        System.out.println(iter.next());
        assertTrue(iter.hasNext());
        System.out.println(iter.next());
        assertTrue(iter.hasNext());
        System.out.println(iter.next());
        assertTrue(iter.hasNext());
        System.out.println(iter.next());
        assertFalse(iter.hasNext());
    }

    @Test
    public void entrySetTest() {
        hashMap.put(6, "Shahar");
        hashMap.put(1, "Amit");
        hashMap.put(4, "Ido");
        hashMap.put(3, "Uriah");
        hashMap.put(2, "Yarden");
        hashMap.put(5, "Itay");
        Set<Map.Entry<Integer, String>> entrySet = hashMap.entrySet();
        Iterator<Map.Entry<Integer, String>> iter = entrySet.iterator();

        assertTrue(iter.hasNext());
        System.out.println(iter.next());
        assertTrue(iter.hasNext());
        System.out.println(iter.next());
        assertTrue(iter.hasNext());
        System.out.println(iter.next());
        assertTrue(iter.hasNext());
        System.out.println(iter.next());
        assertTrue(iter.hasNext());
        System.out.println(iter.next());
        assertTrue(iter.hasNext());
        System.out.println(iter.next());
        assertFalse(iter.hasNext());
    }

    @Test
    public void nullTest() {
        hashMap.put(1, null);
        hashMap.put(null, "Yarden");
        hashMap.put(3, "Uriah");
        hashMap.put(4, null);
        hashMap.put(5, "Itay");
        hashMap.put(6, "Shahar");

        hashMap.remove(2);
        hashMap.remove(5);

        assertEquals(null, hashMap.get(1));
        assertEquals(null, hashMap.get(2));
        assertEquals("Uriah", hashMap.get(3));
        assertEquals(null, hashMap.get(4));
        assertEquals(null, hashMap.get(5));
        assertEquals("Shahar", hashMap.get(6));
    }

    @Test
    public void failFastTest() {
        hashMap.put(6, "Shahar");
        hashMap.put(1, "Amit");
        hashMap.put(4, "Ido");
        hashMap.put(3, "Uriah");
        hashMap.put(2, "Yarden");

        Set<Map.Entry<Integer, String>> entrySet = hashMap.entrySet();
        Iterator<Map.Entry<Integer, String>> iterator = entrySet.iterator();

        try {
            System.out.println("Iterating over the list:");
            while (iterator.hasNext()) {
                System.out.println(iterator.next());

                hashMap.put(5, "Itay");// This should cause ConcurrentModificationException
            }
        } catch (ConcurrentModificationException e) {
            System.out.println("ConcurrentModificationException caught (as expected)");
        }
    }

}

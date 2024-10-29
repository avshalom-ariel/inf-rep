import org.junit.*;

import java.util.ArrayList;

import static org.junit.Assert.*;
import static org.junit.Assert.assertEquals;

public class PairTest {

    @Test
    public void getKeyTest() {
        Pair<String, Integer> Avshi = new Pair<>("Avshi", 0);
        Pair<String, Integer> Amit = new Pair<>("Amit", 0);
        Pair<String, Integer> Uriah = new Pair<>("Uriah", 1);
        Pair<String, Integer> Yarden = new Pair<>("Yarden", 2);

        assertEquals("Avshi", Avshi.getKey());
        assertEquals("Amit", Amit.getKey());
        assertEquals("Uriah", Uriah.getKey());
        assertEquals("Yarden", Yarden.getKey());
    }

    @Test
    public void getValueTest() {
        Pair<String, Integer> Avshi = new Pair<>("Avshi", 0);
        Pair<String, Integer> Amit = new Pair<>("Amit", 0);
        Pair<String, Integer> Uriah = new Pair<>("Uriah", 1);
        Pair<String, Integer> Yarden = new Pair<>("Yarden", 2);

        assertEquals(0, (int)Avshi.getValue());
        assertEquals(0, (int)Amit.getValue());
        assertEquals(1, (int)Uriah.getValue());
        assertEquals(2, (int)Yarden.getValue());
    }

    @Test
    public void setValueTest() {
        Pair<String, Integer> Avshi = new Pair<>("Avshi", 0);
        Pair<String, Integer> Amit = new Pair<>("Amit", 0);
        Pair<String, Integer> Uriah = new Pair<>("Uriah", 1);
        Pair<String, Integer> Yarden = new Pair<>("Yarden", 2);

        assertEquals(0, (int)Avshi.setValue(10));
        assertEquals(0, (int)Amit.setValue(20));
        assertEquals(1, (int)Uriah.setValue(30));
        assertEquals(2, (int)Yarden.setValue(40));

        assertEquals(10, (int)Avshi.getValue());
        assertEquals(20, (int)Amit.getValue());
        assertEquals(30, (int)Uriah.getValue());
        assertEquals(40, (int)Yarden.getValue());
    }

    @Test
    public void toStringTest() {
        Pair<String, Integer> Avshi = new Pair<>("Avshi", 0);
        Pair<String, Integer> Amit = new Pair<>("Amit", 0);
        Pair<String, Integer> Uriah = new Pair<>("Uriah", 1);
        Pair<String, Integer> Yarden = new Pair<>("Yarden", 2);

        assertEquals("(Avshi, 0)", Avshi.toString());
        assertEquals("(Amit, 0)", Amit.toString());
        assertEquals("(Uriah, 1)", Uriah.toString());
        assertEquals("(Yarden, 2)", Yarden.toString());
    }

    @Test
    public void equalsTest() {
        Pair<String, Integer> Avshi = new Pair<>("Avshi", 0);
        Pair<String, Integer> Amit = new Pair<>("Amit", 0);
        Pair<String, Integer> Uriah = new Pair<>("Uriah", 1);
        Pair<String, Integer> Yarden = new Pair<>("Yarden", 2);

        assertFalse(Avshi.equals(Amit));
        assertTrue(Uriah.equals(Uriah));
        assertFalse(Uriah.equals(Amit));
        assertTrue(Yarden.equals(Yarden));
        assertFalse(Yarden.equals(Amit));
        assertTrue(Avshi.equals(Avshi));
    }

    @Test
    public void hashCodeTest() {
        Pair<String, Integer> Avshi = new Pair<>("Avshi", 0);
        Pair<String, Integer> Amit = new Pair<>("Amit", 0);
        Pair<String, Integer> Uriah = new Pair<>("Uriah", 1);
        Pair<String, Integer> Yarden = new Pair<>("Yarden", 2);

        assertEquals(Avshi.hashCode(), Avshi.hashCode());
        assertEquals(Amit.hashCode(), Amit.hashCode());
        assertEquals(Uriah.hashCode(), Uriah.hashCode());
        assertEquals(Yarden.hashCode(), Yarden.hashCode());

        assertNotEquals(Avshi.hashCode(), Uriah.hashCode());
        assertNotEquals(Amit.hashCode(), Avshi.hashCode());
        assertNotEquals(Amit.hashCode(), Yarden.hashCode());
        assertNotEquals(Yarden.hashCode(), Uriah.hashCode());
    }


    @Test
    public void swapTest() {
        Pair<String, Integer> Avshi = new Pair<>("Avshi", 0);
        Pair<String, Integer> Amit = new Pair<>("Amit", 0);
        Pair<String, Integer> Uriah = new Pair<>("Uriah", 1);
        Pair<String, Integer> Yarden = new Pair<>("Yarden", 2);

        Pair<Integer, String> swapedAvshi = Avshi.swap(Avshi);
        Pair<Integer, String> swapedAmit = Amit.swap(Amit);
        Pair<Integer, String> swapedUriah = Uriah.swap(Uriah);
        Pair<Integer, String> swapedYarden = Yarden.swap(Yarden);

        assertEquals("Avshi", swapedAvshi.getValue());
        assertEquals("Amit", swapedAmit.getValue());
        assertEquals("Uriah", swapedUriah.getValue());
        assertEquals("Yarden", swapedYarden.getValue());

        assertEquals(0, (int)swapedAvshi.getKey());
        assertEquals(0, (int)swapedAmit.getKey());
        assertEquals(1, (int)swapedUriah.getKey());
        assertEquals(2, (int)swapedYarden.getKey());
    }

    @Test
    public void ofTest () {
        Pair<String, Integer> Avshi = Pair.of("Avshi", 0);
        Pair<String, Integer> Amit = Pair.of("Amit", 0);
        Pair<String, Integer> Uriah = Pair.of("Uriah", 1);
        Pair<String, Integer> Yarden = Pair.of("Yarden", 2);

        assertEquals(0, (int)Avshi.getValue());
        assertEquals(0, (int)Amit.getValue());
        assertEquals(1, (int)Uriah.getValue());
        assertEquals(2, (int)Yarden.getValue());

        assertEquals("Avshi", Avshi.getKey());
        assertEquals("Amit", Amit.getKey());
        assertEquals("Uriah", Uriah.getKey());
        assertEquals("Yarden", Yarden.getKey());
    }

    @Test
    public void minmaxTest() {
        ArrayList<Integer> arr = new ArrayList<Integer>();

        arr.add(1);
        arr.add(2);
        arr.add(3);
        arr.add(4);
        arr.add(5);
        arr.add(6);
        arr.add(7);
        arr.add(8);
        arr.add(9);

        Pair<Integer, Integer> pair = Pair.minmax(arr);

        assertEquals(1, (int)pair.getKey());
        assertEquals(9, (int)pair.getValue());
    }

}

import org.junit.*;
import java.util.ConcurrentModificationException;
import java.util.Iterator;
import static org.junit.Assert.*;

public class LinkedListTest {
    LinkedListGen<Integer> list = new LinkedListGen<>();
    LinkedListGen<Integer> list2 = new LinkedListGen<>();

    @Test
    public void printListTest() {
        list.pushFront(1);
        list.pushFront(2);
        list.pushFront(3);
        list.pushFront(4);
        list.pushFront(5);

        list.printList(list);
    }

    @Test
    public void pushFrontTest() {
        list.pushFront(1);
        list.pushFront(2);
        list.pushFront(3);
        list.pushFront(4);
        list.pushFront(5);

        list.printList(list);
    }

    @Test
    public void popFrontTest() {
        list.pushFront(1);
        list.pushFront(2);
        list.pushFront(3);
        list.pushFront(4);
        list.pushFront(5);

        assertEquals(5, (int) list.popFront());
        assertEquals(4, (int) list.popFront());
        assertEquals(3, (int) list.popFront());
        assertEquals(2, (int) list.popFront());
        assertEquals(1, (int) list.popFront());
    }

    @Test
    public void sizeTest() {
        assertEquals(0, (int) list.size());

        list.pushFront(1);

        assertEquals(1, (int) list.size());

        list.pushFront(2);

        assertEquals(2, (int) list.size());

        list.pushFront(3);

        assertEquals(3, (int) list.size());

        list.pushFront(4);

        assertEquals(4, (int) list.size());

        list.pushFront(5);

        assertEquals(5, (int) list.size());
    }

    @Test
    public void isEmptyTest() {
        assertTrue(list.isEmpty());

        list.pushFront(1);

        assertFalse(list.isEmpty());

        list.pushFront(2);

        assertFalse(list.isEmpty());

        list.popFront();

        assertFalse(list.isEmpty());

        list.popFront();

        assertTrue(list.isEmpty());

        assertTrue(list.isEmpty());

        list.pushFront(3);

        assertFalse(list.isEmpty());

        list.pushFront(4);

        assertFalse(list.isEmpty());

        list.popFront();

        assertFalse(list.isEmpty());

        list.popFront();

        assertTrue(list.isEmpty());
    }

    @Test
    public void findTest() {
        list.pushFront(1);
        list.pushFront(2);
        list.pushFront(3);
        list.pushFront(4);
        list.pushFront(5);

        assertNotNull(list.find(1));
        assertNotNull(list.find(2));
        assertNotNull(list.find(3));
        assertNotNull(list.find(4));
        assertNotNull(list.find(5));

        assertNull(list.find(6));
        assertNull(list.find(7));
        assertNull(list.find(8));
        assertNull(list.find(0));
        assertNull(list.find(-1));

        Iterator<Integer> iterator = list.find(3);

        assertTrue(iterator.hasNext());
        assertEquals(3, (int) iterator.next());
        assertTrue(iterator.hasNext());
        assertEquals(2, (int) iterator.next());
        assertTrue(iterator.hasNext());
        assertEquals(1, (int) iterator.next());
        assertFalse(iterator.hasNext());
    }

    @Test
    public void mergeListsTest() {
        list.pushFront(5);
        list.pushFront(4);
        list.pushFront(3);
        list.pushFront(2);
        list.pushFront(1);

        list2.pushFront(10);
        list2.pushFront(9);
        list2.pushFront(8);
        list2.pushFront(7);
        list2.pushFront(6);

        LinkedListGen<Integer> mergedList = LinkedListGen.mergeLists(list, list2);

        assertTrue(list.isEmpty());
        assertTrue(list2.isEmpty());

        assertEquals(1, (int) mergedList.popFront());
        assertEquals(2, (int) mergedList.popFront());
        assertEquals(3, (int) mergedList.popFront());
        assertEquals(4, (int) mergedList.popFront());
        assertEquals(5, (int) mergedList.popFront());
        assertEquals(6, (int) mergedList.popFront());
        assertEquals(7, (int) mergedList.popFront());
        assertEquals(8, (int) mergedList.popFront());
        assertEquals(9, (int) mergedList.popFront());
        assertEquals(10, (int) mergedList.popFront());
    }

    @Test
    public void newReverseTest() {
        list.pushFront(1);
        list.pushFront(2);
        list.pushFront(3);
        list.pushFront(4);
        list.pushFront(5);

        LinkedListGen<Integer> reversedList = LinkedListGen.newReverse(list);

        assertEquals(1, (int) reversedList.popFront());
        assertEquals(2, (int) reversedList.popFront());
        assertEquals(3, (int) reversedList.popFront());
        assertEquals(4, (int) reversedList.popFront());
        assertEquals(5, (int) reversedList.popFront());
    }

    @Test
    public void iteratorTest() {
        list.pushFront(1);
        list.pushFront(2);
        list.pushFront(3);
        list.pushFront(4);
        list.pushFront(5);

        Iterator<Integer> iterator = list.iterator();

        assertTrue(iterator.hasNext());
        assertEquals(5, (int) iterator.next());
        assertTrue(iterator.hasNext());
        assertEquals(4, (int) iterator.next());
        assertTrue(iterator.hasNext());
        assertEquals(3, (int) iterator.next());
        assertTrue(iterator.hasNext());
        assertEquals(2, (int) iterator.next());
        assertTrue(iterator.hasNext());
        assertEquals(1, (int) iterator.next());
        assertFalse(iterator.hasNext());
    }

    @Test
    public void oneThreadModCountTest() {
        list.pushFront(1);
        list.pushFront(2);
        list.pushFront(3);
        list.pushFront(4);
        list.pushFront(5);

        Iterator<Integer> iterator = list.iterator();

        try {
            System.out.println("Iterating over the list:");
            while (iterator.hasNext()) {
                Integer value = iterator.next();
                System.out.println("value is: " + value);

                list.pushFront(4); // This should cause ConcurrentModificationException
            }
        } catch (ConcurrentModificationException e) {
            System.out.println("ConcurrentModificationException caught (as expected)");
        }
    }

    @Test
    public void multiThreadModCountTest() {
        list.pushFront(5);
        list.pushFront(4);
        list.pushFront(3);
        list.pushFront(2);
        list.pushFront(1);

        // Thread  definition
        Thread modifierThread = new Thread(() -> {
            try {
                Thread.sleep(50); // Ensure the iterator starts first
                list.pushFront(4);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        });

        Iterator<Integer> iterator = list.iterator();

        //Start the thread
        modifierThread.start();

        try {
            System.out.println("Iterating over the list:");
            while (iterator.hasNext()) {
                Integer value = iterator.next();
                System.out.println("value is: " + value);

                // So this thread won't finish too fast
                Thread.sleep(40);
            }
        } catch (ConcurrentModificationException e) {
            System.out.println("ConcurrentModificationException caught as expected.");
        } catch (InterruptedException e) { // Just for the sleep
            throw new RuntimeException(e);
        }

        // wait fir thread to finish
        try {
            modifierThread.join();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}

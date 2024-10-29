//import org.junit.*;
//import static org.junit.Assert.*;
//
//public class SinglyLinkedListTest {
//
//    SinglyLinkedList list = new SinglyLinkedList();
//    Integer data1 = 1;
//    Integer data2 = 2;
//    Integer data3 = 3;
//    Integer data4 = 4;
//    Integer data5 = 5;
//
//    @BeforeClass
//    public static void setUpBeforeClass() throws Exception {
//        System.out.println("Starting tests: \n");
//    }
//
//    @AfterClass
//    public static void tearDownAfterClass() throws Exception {
//        System.out.println("\nFinished tests");
//    }
//
//    @Test
//    public void mainTest1() {
//        assertTrue(list.isEmpty());
//
//        list.pushFront(data1);
//        list.pushFront(data2);
//        list.pushFront(data3);
//        list.pushFront(data4);
//        list.pushFront(data5);
//
//        assertFalse(list.isEmpty());
//
//        assertEquals(5, list.size());
//
//        assertEquals(5, list.popFront());
//
//        assertEquals(4, list.size());
//
//        assertEquals(4, list.popFront());
//
//        assertEquals(3, list.size());
//
//        assertEquals(3, list.popFront());
//
//        assertEquals(2, list.size());
//
//        assertEquals(2, list.popFront());
//
//        assertEquals(1, list.size());
//
//        assertEquals(1, list.popFront());
//    }
//
//    @Test
//    public void mainTest2() {
//        int i = 5;
//        list.pushFront(data1);
//        list.pushFront(data2);
//        list.pushFront(data3);
//        list.pushFront(data4);
//        list.pushFront(data5);
//
//        ListIterator iter = list.begin();
//
//        while (iter.hasNext()) {
//            assertEquals(i, iter.next());
//            --i;
//        }
//
//        assertEquals(0, i);
//
//        iter = list.find(data4);
//        i = 4;
//
//        while (iter.hasNext()) {
//            assertEquals(i, iter.next());
//            --i;
//        }
//
//        assertEquals(0, i);
//    }
//}
//

//-------------------------------------
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;


public class SinglyLinkedListTest {

    static SinglyLinkedList list = null;

    @Before
    public void testInit() {
        list = new SinglyLinkedList();
    }



    @Test
    public void testIsEmpty() {
        assertTrue(list.isEmpty());

        list.pushFront(1);

        assert(!list.isEmpty());

        list.popFront();

        assert(list.isEmpty());

        for (int i = 1; i <= 5; ++i) {
            list.pushFront(i);
        }
        assert(!list.isEmpty());

        for (int i = 1; i <= 5; ++i) {
            list.popFront();
        }

        assert(list.isEmpty());
    }

    @Test
    public void testSize(){
        assertEquals(0, list.size());

        list.pushFront(1);

        assertEquals(1, list.size());

        list.popFront();

        assertEquals(0, list.size());

        for (int i = 1; i <= 5; ++i) {
            list.pushFront(i);
        }

        assertEquals(5, list.size());
    }

    @Test
    public void testPushFront(){
        list.pushFront(1);

        ListIterator iterator = list.begin();

        assert (iterator.next().equals(1));

        list.popFront();

        for (int i = 5; i > 0; --i) {
            list.pushFront(i);
        }

        for (int i = 5; i > 0; --i) {
            System.out.println(list.popFront());
        }

        iterator = list.begin();
        int i = 1;

        while (iterator.hasNext()) {
            assert (iterator.next().equals(i));
            ++i;
        }

        assertEquals(1, list.popFront());

        i = 2;

        while (list.begin().hasNext()) {
            assertEquals(i, list.popFront());
            ++i;
        }
    }
}

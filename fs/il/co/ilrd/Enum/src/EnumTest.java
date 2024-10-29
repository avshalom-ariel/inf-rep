import org.junit.*;
import static org.junit.Assert.*;

public class EnumTest {
    @Test
    public void getValueTest() {
        EWeekDay sunday = EWeekDay.SUNDAY;
        EWeekDay monday = EWeekDay.MONDAY;
        EWeekDay tuesday = EWeekDay.TUESDAY;
        EWeekDay wednesday = EWeekDay.WEDNESDAY;
        EWeekDay thursday = EWeekDay.THURSDAY;
        EWeekDay friday = EWeekDay.FRIDAY;
        EWeekDay saturday = EWeekDay.SATURDAY;

        assertEquals(1, sunday.getValue());
        assertEquals(2, monday.getValue());
        assertEquals(3, tuesday.getValue());
        assertEquals(4, wednesday.getValue());
        assertEquals(5, thursday.getValue());
        assertEquals(6, friday.getValue());
        assertEquals(7, saturday.getValue());
    }

    @Test
    public void fromValueTest() {
        assertEquals("SUNDAY", EWeekDay.fromValue(1));
        assertEquals("MONDAY", EWeekDay.fromValue(2));
        assertEquals("TUESDAY", EWeekDay.fromValue(3));
        assertEquals("WEDNESDAY", EWeekDay.fromValue(4));
        assertEquals("THURSDAY", EWeekDay.fromValue(5));
        assertEquals("FRIDAY", EWeekDay.fromValue(6));
        assertEquals("SATURDAY", EWeekDay.fromValue(7));
    }

    @Test
    public void printTest() { EWeekDay.print(); }

    @Test
    public void anotherGetValueTest() {
        AnotherEWeekDay sunday = AnotherEWeekDay.SUNDAY;
        AnotherEWeekDay monday = AnotherEWeekDay.MONDAY;
        AnotherEWeekDay tuesday = AnotherEWeekDay.TUESDAY;
        AnotherEWeekDay wednesday = AnotherEWeekDay.WEDNESDAY;
        AnotherEWeekDay thursday = AnotherEWeekDay.THURSDAY;
        AnotherEWeekDay friday = AnotherEWeekDay.FRIDAY;
        AnotherEWeekDay saturday = AnotherEWeekDay.SATURDAY;

        assertEquals(1, sunday.getValue());
        assertEquals(2, monday.getValue());
        assertEquals(3, tuesday.getValue());
        assertEquals(4, wednesday.getValue());
        assertEquals(5, thursday.getValue());
        assertEquals(6, friday.getValue());
        assertEquals(7, saturday.getValue());
    }

    @Test
    public void anotherFromValueTest() {
        assertEquals("SUNDAY", AnotherEWeekDay.fromValue(1));
        assertEquals("MONDAY", AnotherEWeekDay.fromValue(2));
        assertEquals("TUESDAY", AnotherEWeekDay.fromValue(3));
        assertEquals("WEDNESDAY", AnotherEWeekDay.fromValue(4));
        assertEquals("THURSDAY", AnotherEWeekDay.fromValue(5));
        assertEquals("FRIDAY", AnotherEWeekDay.fromValue(6));
        assertEquals("SATURDAY", AnotherEWeekDay.fromValue(7));
    }
}


//import java.awt.*;
import java.lang.Enum;
import java.util.Arrays;

enum EWeekDay {
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY;

    int getValue() {return ordinal() + 1;}

    static String fromValue(int value) {
        if (0 > value || 7 < value) { return null; }

        return EWeekDay.values()[value - 1].toString();
    }

    public static void print() {
        System.out.println(Arrays.toString(EWeekDay.values()));
    }
}

enum AnotherEWeekDay {
    SUNDAY {int getValue() {return 1;}},
    MONDAY{int getValue() {return 2;}},
    TUESDAY{int getValue() {return 3;}},
    WEDNESDAY{int getValue() {return 4;}},
    THURSDAY{int getValue() {return 5;}},
    FRIDAY{int getValue() {return 6;}},
    SATURDAY{int getValue() {return 7;}};

    abstract int getValue();

    static String fromValue(int value) {
        return EWeekDay.values()[value - 1].toString();
    }

    public static void print() {
        System.out.println(Arrays.toString(EWeekDay.values()));
    }
}



public class ArrayPrinter {

    public static <T> void printArray(T[] array) {
        for (T t : array) {
            System.out.print(t + " ");
        }
        System.out.println(" ");
    }

    public static void main(String[] args) {
        Integer[] intArray = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        String[] stringArray = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
        Boolean[] boolArray = {true, false, true, false, true, false, true, false};

        printArray(intArray);
        printArray(stringArray);
        printArray(boolArray);
    }
}


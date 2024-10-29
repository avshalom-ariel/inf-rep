public class OuterClass {
    private static String staticField = "Static Field";

    // Non-static inner class
    class InnerClass {
        void display() {
            // Accessing the static field of the outer class
            System.out.println("Accessing static field: " + staticField);
        }
    }

    public static void main(String[] args) {
        OuterClass outer = new OuterClass();
        OuterClass.InnerClass inner = outer.new InnerClass();
        inner.display();
    }
}

import java.io.IOException;

public class Foo {
    public void func1() throws IOException {}

    public void func2() {
        String str = null;
        int length = str.length();
    }

    public static void main(String[] args) throws IOException {
        Foo foo = new Foo();

        byte[] byteArray = new byte[100];

        MyClass1 myClass1 = new MyClass1();
        MyClass2 myClass2 = new MyClass2();

        System.out.println(byteArray[byteArray.length + 1]);

        try {
            foo.func1();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

//        foo.func2();
    }

    public class MyException1 extends RuntimeException {
        public MyException1(String message) {
            super(message);
        }
    }

    public class MyException2 extends IOException {
        public MyException2(String message) {
            super(message);
        }
    }

    public void func3() throws MyException1 {

    }
    public void func4() throws MyException2 {

    }

}


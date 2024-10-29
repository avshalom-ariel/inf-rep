public class InnerClasses {
    public static void main(String[] args) {
        OuterClass st = new OuterClass();
            OuterClass.InnerClass fl = st.new InnerClass();
            fl.foo(23);
    }
}

class OuterClass {
    public int x = 0;
    String outerString = "outer string";

    public void outerMethod() {
        System.out.println("outer method invoked");
    }

    class InnerClass {
        public int x = 1;
        void foo(int x) {
            System.out.println("x = " + x);
            System.out.println("this.x = " + this.x);
            System.out.println("OuterClass.this.x = " + OuterClass.this.x);
            OuterClass.this.outerMethod();
        }
    }

    static class InnerClass2 {
        public int x = 1;
        void foo(int x) {
            System.out.println("x = " + x);
            System.out.println("this.x = " + this.x);
            System.out.println("OuterClass.this.x = " + OuterClass.this.x);
        }

        Animal animal = new Animal() {
            @Override
            public void makeSound() {
                System.out.println("Animal Roar");
            }
        };
        {
            animal.makeSound();
        }
    }
}

abstract class Animal {
    public abstract void makeSound();
}

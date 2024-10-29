import org.junit.*;
import static org.junit.Assert.*;

import java.util.function.Function;

public class FactoryTest {
    private static class Fruit {
        String name;
        public Fruit(String name) {
            this.name = name;
        }
    }

    private static class Apple extends Fruit {
        String type;
        public Apple(String name, String type) {
            super(name);
            this.type = type;
        }
        @Override
        public String toString() {
            return type;
        }
    }

    private static class Grape extends Fruit {
        String type;
        public Grape(String name, String type) {
            super(name);
            this.type = type;
        }
        @Override
        public String toString() {
            return type;
        }
    }

    public String instanceMethod(String name) {
        return "instance Method";
    }

    public static String staticMethod(String name) {
        return "static Method";
    }

    @Test
    public void test() {
        Function<Double, Double> half = a -> a / 2.0;
        Function<Double, Double> quarter = a -> a / 3.0;
        Function<Double, Double> halfQuarter = a -> a / 4.0;
        Factory<Integer, Double, Double> calculateFactory = new Factory<>();

        calculateFactory.add(3, half);
        calculateFactory.add(7, quarter);
        calculateFactory.add(20, halfQuarter);

        assertEquals(0, Double.compare((double) calculateFactory.create(3, 100.0), 50.0));
        assertEquals(0, Double.compare((double) calculateFactory.create(7, 100.0), 33.333333333333336));
        assertEquals(0, Double.compare((double) calculateFactory.create(20, 100.0), 25.0));

        Function<String, Fruit> createApple = s -> new Grape(s, s);
        Function<String, Fruit> createGrape = s -> new Grape(s, s);
        Factory<String, Fruit, String> fruitFactory= new Factory<>();

        fruitFactory.add("apple", createApple);
        fruitFactory.add("grape", createGrape);

        System.out.println(fruitFactory.create("apple", "pink lady"));
        System.out.println(fruitFactory.create("grape", "cabarnne"));

        Factory<String, String, String> methodFactory = new Factory<>();

        FactoryTest instance = new FactoryTest();
        methodFactory.add("instance", instance::instanceMethod);
        methodFactory.add("static", FactoryTest::staticMethod);

        System.out.println(methodFactory.create("instance", "dummy"));
        System.out.println(methodFactory.create("static", "dummy"));
    }
}

import org.junit.*;

import java.lang.reflect.InvocationTargetException;

public class ObjectAnalyzerTest {


    @Test
    public void printAncestorTest() {
        class Foo1 {
            String foo1;
        }

        class Foo2 extends Foo1 {
            String foo2;
        }

        Foo2 foo2 = new Foo2();

        ObjectAnalyzer.PrintAncestor(foo2);
    }

    @Test
    public void getModifiersAndInterfacesTest() {
        String str = new String("getModifiersAndInterfacesTest");

        ObjectAnalyzer.getModifiersAndInterfaces(str);
    }

    @Test
    public void getMembersTest() {
        String str = new String("getModifiersAndInterfacesTest");

        ObjectAnalyzer.getMembers(str);
    }

    @Test
    public void getInstanceTest() throws InvocationTargetException, NoSuchMethodException, InstantiationException, IllegalAccessException {

        String foo = new String("hey to you");

        Object foo2 = ObjectAnalyzer.getInstance(foo);

        if (null != foo2) {
            System.out.println(foo2.getClass());
            System.out.println(foo2.toString());
        }
    }
}

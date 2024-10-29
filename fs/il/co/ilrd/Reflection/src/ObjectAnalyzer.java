import java.lang.reflect.*; // Modifiers, Field

public class ObjectAnalyzer {

    public static void PrintAncestor(Object obj) {
        Class<?> thisClass = obj.getClass(); // Example class

        Class<?> superClass = thisClass.getSuperclass();

        Class<?> ancestorClass = superClass.getSuperclass();

        if (null != ancestorClass) {
            System.out.println("This class" + thisClass.getName());
            System.out.println("Parent class" + superClass.getName());
            System.out.println("Ancestor class" + ancestorClass.getName());
        } else {
            System.out.println("No ancestor");
        }
    }

    public static void getModifiersAndInterfaces(Object obj) {
        Class<?> thisClass = obj.getClass();

        int modifiers = thisClass.getModifiers();
        Class<?>[] interfaces = thisClass.getInterfaces();

        System.out.println("Modifiers are:");
        System.out.println(Modifier.toString(modifiers));

        System.out.println("Interfaces are:");
        for (Class<?> iface : interfaces) {
            System.out.println(iface.getName());
        }
    }

    public static void getMembers(Object obj) {
        Class<?> thisClass = obj.getClass();

        Field[] fields = thisClass.getDeclaredFields();

        System.out.println("Declared Fields:");
        for (Field field : fields) {
            System.out.println("Name: " + field.getName() + ", Type: " + field.getType());
        }
    }

    public static Object getInstance(Object obj) throws NoSuchMethodException {
        Object instance = null;
        Class<?> thisClass = obj.getClass();

        try {
            Constructor<?> constructor = thisClass.getConstructor();
            instance = constructor.newInstance();
            return instance;
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
            return null;
        } catch (InvocationTargetException e) {
            throw new RuntimeException(e);
        } catch (InstantiationException e) {
            throw new RuntimeException(e);
        } catch (IllegalAccessException e) {
            throw new RuntimeException(e);
        }
    }
}


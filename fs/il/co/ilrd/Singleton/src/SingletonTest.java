import org.junit.*;
import static org.junit.Assert.*;

public class SingletonTest {

    @Test
    public void eagerTest() {
        EagerSingleton instance = EagerSingleton.getInstance();

        assertEquals("EagerSingleton display", instance.display());
    }

    @Test
    public void lazyTest() {
        LazySingleton instance = LazySingleton.getInstance();

        assertEquals("LazySingleton display", instance.display());
    }

    @Test
    public void SingletonDoubleCheckLockingTest() {
        SingletonDoubleCheckLocking instance = SingletonDoubleCheckLocking.getInstance();

        assertEquals("SingletonDoubleCheckLocking display", instance.display());
    }

    @Test
    public void HolderIdiomSingletonTest() {
        HolderIdiomSingleton instance = HolderIdiomSingleton.getInstance();

        assertEquals("HolderIdiomSingleton display", instance.display());
    }

    @Test
    public void EnumSingletonTest() {
        EnumSingleton instance = EnumSingleton.INSTANCE;

        assertEquals("EnumSingleton display", instance.display());
    }

}

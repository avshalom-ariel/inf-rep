import org.junit.*;
import java.io.FileNotFoundException;

public class TreeTest {


    @Test
    public void test() throws FileNotFoundException {
        try {
            TreeComposite tree = new TreeComposite("/home/avshalom/git");
            tree.print();
            TreeComposite tree2 = new TreeComposite("some ");

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }
}



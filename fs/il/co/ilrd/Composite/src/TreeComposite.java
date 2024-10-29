import java.io.File;
import java.io.FileNotFoundException;

public class TreeComposite {
    Print root;

    public TreeComposite(String root) throws FileNotFoundException {
        this.root = new FileComposite(root);
    }

    public void print() {
        root.print();
    }
}

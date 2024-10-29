
import java.io.File;

public class Tree {
    File root;
    int spaceCounter = -1;

    public Tree(String root) {
        this.root = new File(root);
        if (!this.root.exists()) {
            System.out.println("File does not exist");
        }
    }

    public void print() {
        System.out.println(root.getName());
        printCurr(root);
    }

    private void printCurr(File file) {
        File[] list = file.listFiles();
        ++spaceCounter;
        for (int i = 0; i < list.length; i++) {
            if (0 != spaceCounter) {
                System.out.print("|");
            }
            for (int j = 0; j < spaceCounter; j++) {
                System.out.print("   |");
            }
            if (i == list.length - 1) {
                System.out.print("`");
            } else {
                System.out.print("");
            }

            System.out.println("--" + list[i].getName());

            if (list[i].canRead() && list[i].isDirectory()) {
                printCurr(list[i]);
            }
        }
        --spaceCounter;
    }

    public static void main(String[] args) {
        Tree tree = new Tree("/home/avshalom/git");
        tree.print();

    }
}


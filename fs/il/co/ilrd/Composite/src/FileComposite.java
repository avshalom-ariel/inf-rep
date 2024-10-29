import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.lang.Exception;

public class FileComposite implements Print{
    private File file;
    private ArrayList<Print> directories = new ArrayList<>();
    int spaceCounter = 0;

    public FileComposite(String file) throws FileNotFoundException {
        this.file = new File(file);

        if (!this.file.exists()) {
            throw new FileNotFoundException("File not found");
        } else if (!this.file.isDirectory()) {
            throw new FileNotFoundException("File is not a directory");
        }

        File[] files = this.file.listFiles();
        for (File f : files) {
            if (f.isDirectory()) {
                directories.add(new FileComposite(f.getPath()));
            } else {
                directories.add(new MyFIle(f.getPath()));
            }
        }

    }

    public void print() {
        System.out.println(file.getName());
        ++spaceCounter;
        for (Print f : directories) {
            f.print();
        }
        --spaceCounter;
    }
    private class MyFIle implements Print{
        private File file;

        public MyFIle(String fileName) throws FileNotFoundException {
            this.file = new File(fileName);
            if (!this.file.exists()) {
                throw new FileNotFoundException("File not found");
            }
        }

        public void print() {
            System.out.println(file.getName());
        }
    }

}

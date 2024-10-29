import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.*;
import java.util.Date;

public class DearMonitor {
    private WatchService watchService = null;;
    private final Path pathToLog;
    private boolean running = false;

    public DearMonitor(String dirToWatch, String fileToLog) {
        try {
            watchService = FileSystems.getDefault().newWatchService();
            pathToLog = Paths.get(fileToLog);

            Path pathToWatch = Paths.get(dirToWatch);
            if (!Files.exists(pathToWatch)) {
                throw new FileNotFoundException("File not found!");
            }
            if (!Files.isDirectory(pathToWatch)) {
                throw new IllegalArgumentException("File is not a directory!");
            }

            pathToWatch.register(watchService,
                            StandardWatchEventKinds.ENTRY_CREATE,
                            StandardWatchEventKinds.ENTRY_DELETE,
                            StandardWatchEventKinds.ENTRY_MODIFY);

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public void watch() throws InterruptedException, IOException {
        running = true;
        while (running) {
            WatchKey key = watchService.take();
            for (WatchEvent<?> watchEvent : key.pollEvents()) {
                String message = (new Date()) + " " + watchEvent.kind() + " " + watchEvent.context() + "\n";
                System.out.println(message);

                Files.write(pathToLog, message.getBytes(), StandardOpenOption.APPEND, StandardOpenOption.CREATE);
            }

            key.reset();
        }
    }

    public void stop() {
        running = false;
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        String pathToWatch = "/home/avshalom/Downloads";
        String fileToLog = "/home/avshalom/logger.txt";
        DearMonitor dearMonitor = new DearMonitor(pathToWatch, fileToLog);
        dearMonitor.watch();
    }
}
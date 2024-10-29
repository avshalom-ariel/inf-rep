package concurrency;
import java.util.LinkedList;

public class Ex3NoSemaphore {
    private static final int BUFFER_SIZE = 10;
    private static final LinkedList<Integer> buffer = new LinkedList<>();
    private static final Object lock = new Object(); // Lock object for synchronization

    public static void main(String[] args) {
        int numProducers = 3;
        int numConsumers = 3;

        // Create and start producer threads
        for (int i = 0; i < numProducers; i++) {
            new Thread(new Producer()).start();
        }

        // Create and start consumer threads
        for (int i = 0; i < numConsumers; i++) {
            new Thread(new Consumer()).start();
        }
    }

    static class Producer implements Runnable {
        @Override
        public void run() {
            try {
                while (true) {
                    int item = (int) (Math.random() * 100); // Generate a random item

                    synchronized (lock) {
                        while (buffer.size() == BUFFER_SIZE) {
                            lock.wait(); // Wait if buffer is full
                        }
                        buffer.add(item); // Add item to the buffer
                        System.out.println("Produced: " + item);
                        lock.notifyAll(); // Notify consumers that an item is available
                    }
                    Thread.sleep(1000);
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }

    static class Consumer implements Runnable {
        @Override
        public void run() {
            try {
                while (true) {
                    synchronized (lock) {
                        while (buffer.isEmpty()) {
                            lock.wait(); // Wait if buffer is empty
                        }
                        int item = buffer.removeFirst(); // Take item from the buffer
                        System.out.println("Consumed: " + item);
                        lock.notifyAll(); // Notify producers that space is clear
                    }
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}

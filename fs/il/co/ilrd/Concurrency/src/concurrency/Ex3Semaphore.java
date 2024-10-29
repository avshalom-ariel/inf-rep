package concurrency;
import java.util.LinkedList;
import java.util.concurrent.Semaphore;

public class Ex3Semaphore {
    private static final LinkedList<Integer> buffer = new LinkedList<>();
    private static final Object lock = new Object(); // Lock object for synchronization
    private static final Semaphore semaphore = new Semaphore(0); // Single semaphore for buffer capacity

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
                        buffer.add(item); // Add item to the buffer
                        System.out.println("Produced: " + item);
//                        lock.notifyAll(); // Notify consumers that an item is available
                    }
                    semaphore.release(); // Wait for an available slot in the buffer

                    Thread.sleep(500); // Sleep to simulate production time
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
                    semaphore.acquire(); // Wait for an available slot in the buffer

                    synchronized (lock) {
                        int item = buffer.removeFirst(); // Take item from the buffer
                        System.out.println("Consumed: " + item);
                    }

                    Thread.sleep(500); // Sleep to simulate consumption time
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}

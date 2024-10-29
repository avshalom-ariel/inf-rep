package concurrency;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Ex2FixedReentrantLock {
    private static int counter = 0;
    private static final int INCREMENT_COUNT = 10000000;
    private static final Lock lock = new ReentrantLock();

    public static void main(String[] args) throws InterruptedException {
        long startTime = System.currentTimeMillis();

        Thread thread1 = new Thread(new IncrementTask());
        Thread thread2 = new Thread(new IncrementTask());

        thread1.start();
        thread2.start();

        thread1.join(); // Wait for thread1 to finish
        thread2.join(); // Wait for thread2 to finish

        long endTime = System.currentTimeMillis();
        System.out.println("Counter value: " + counter);
        System.out.println("Execution time: " + (endTime - startTime) + " milliseconds");
    }

    private static class IncrementTask extends Thread {
        @Override
        public void run() {
            for (int i = 0; i < INCREMENT_COUNT; i++) {
                lock.lock(); // Acquire the lock
                try {
                    counter++;
                } finally {
                    lock.unlock(); // Ensure the lock is always released!!!!
                }
            }
        }
    }
}

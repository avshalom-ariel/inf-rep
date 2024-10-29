package concurrency;
import java.util.concurrent.atomic.AtomicInteger;

public class Ex2FixedAtomics {
    private static final AtomicInteger counter = new AtomicInteger(0);
    private static final int INCREMENT_COUNT = 10000000;

    public static void main(String[] args) throws InterruptedException {
        long startTime = System.currentTimeMillis();

        Thread thread1 = new Thread(new IncrementTask());
        Thread thread2 = new Thread(new IncrementTask());

        thread1.start();
        thread2.start();

        thread1.join();
        thread2.join();

        long endTime = System.currentTimeMillis();
        System.out.println("Counter value: " + counter.get());
        System.out.println("Execution time: " + (endTime - startTime) + " milliseconds");
    }

    private static class IncrementTask extends Thread {
        @Override
        public void run() {
            for (int i = 0; i < INCREMENT_COUNT; ++i) {
                counter.incrementAndGet();
            }
        }
    }
}

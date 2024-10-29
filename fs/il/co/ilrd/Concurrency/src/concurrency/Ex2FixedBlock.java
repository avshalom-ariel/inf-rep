package concurrency;
public class Ex2FixedBlock {
    private static volatile int counter = 0;
    private static final int INCREMENT_COUNT = 10000000;

    private static class IncrementTask implements Runnable {

        // synchronized block
        @Override
        public void run() {
            for (int i = 0; i < INCREMENT_COUNT; i++) {
                synchronized (Ex2FixedBlock.class) {
                    counter++;
                }
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        long startTime = System.currentTimeMillis();

        Runnable incrementTask = new IncrementTask();

        Thread thread1 = new Thread(incrementTask);
        Thread thread2 = new Thread(incrementTask);

        thread1.start();
        thread2.start();

        thread1.join();
        thread2.join();

        long endTime = System.currentTimeMillis();
        System.out.println("Counter value: " + counter);
        System.out.println("Execution time: " + (endTime - startTime) + " milliseconds");
    }
}

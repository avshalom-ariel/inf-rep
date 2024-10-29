package concurrency;
public class Ex2FixedMethod {
    private static int counter = 0;
    private static final int INCREMENT_COUNT = 10000000;

    public static void main(String[] args) throws InterruptedException {
        Thread thread1 = new Thread(new IncrementTask());
        Thread thread2 = new Thread(new IncrementTask());

        long startTime = System.currentTimeMillis();

        thread1.start();
        thread2.start();

        thread1.join();
        thread2.join();

        long endTime = System.currentTimeMillis();
        System.out.println("Counter value: " + counter);
        System.out.println("Execution time: " + (endTime - startTime) + " milliseconds");
    }

    private static class IncrementTask extends Thread {
        @Override
        public void run() {
            incrementCounter();
        }
    }

    private synchronized static void incrementCounter() {
        for (int i = 0; i < INCREMENT_COUNT; i++) {
            counter++;
        }
    }
}
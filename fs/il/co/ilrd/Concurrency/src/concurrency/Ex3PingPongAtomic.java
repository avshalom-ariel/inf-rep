package concurrency;
import java.util.concurrent.atomic.AtomicInteger;

public class Ex3PingPongAtomic {
    private static final AtomicInteger turn = new AtomicInteger(0);

    public static void main(String[] args) {
        Thread producer = new Producer();
        Thread consumer = new Consumer();

        producer.start();
        consumer.start();
    }

    static class Producer extends Thread {
        @Override
        public void run() {
            while (true) {
                while (turn.get() != 0) {
                    // Wait until it's this thread's turn
                }
                System.out.println("Ping");
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                turn.set(1); // Signal the consumer thread
            }
        }
    }

    static class Consumer extends Thread {
        @Override
        public void run() {
            while (true) {
                while (turn.get() != 1) {
                    // Wait until it's this thread's turn
                }
                System.out.println("Pong");
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                turn.set(0); // Signal the producer thread
            }
        }
    }
}

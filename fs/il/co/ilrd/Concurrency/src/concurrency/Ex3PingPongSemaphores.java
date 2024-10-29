package concurrency;
import java.util.concurrent.Semaphore;

public class Ex3PingPongSemaphores {
    private static final Semaphore pingSemaphore = new Semaphore(1); // Start with 1 for first ping
    private static final Semaphore pongSemaphore = new Semaphore(0); // Start with 0 for wait for pong

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
                try {
                    pingSemaphore.acquire(); // Wait for permit
                    System.out.println("Ping");
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                    pongSemaphore.release(); // Signal the consumer thread
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        }
    }

    static class Consumer extends Thread {
        @Override
        public void run() {
            while (true) {
                try {
                    pongSemaphore.acquire(); // Wait for permit
                    System.out.println("Pong");
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                    pingSemaphore.release(); // Signal the producer thread
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        }
    }
}

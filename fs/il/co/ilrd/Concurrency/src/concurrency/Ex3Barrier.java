package concurrency;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Ex3Barrier {
<<<<<<< HEAD:fs/il/co/ilrd/Concurrency/src/Ex3Barrier.java
    private static final int NUM_CONSUMERS = 9; // Number of consumers
    private static final ReentrantLock lock = new ReentrantLock();
    private static final Condition allConsumersRead = lock.newCondition();
    private static final Semaphore semaphore = new Semaphore(0); // Ensure only one producer at a time
=======
    private static final Semaphore semaphore = new Semaphore(1); // To make sure only one producer at a time
    private static final ReentrantLock lock = new ReentrantLock();
    private static final Condition allConsumersRead = lock.newCondition();

    private static final int NUM_CONSUMERS = 10; // Number of consumers
>>>>>>> origin:fs/il/co/ilrd/Concurrency/src/concurrency/Ex3Barrier.java
    private static String message = null; // Message to be produced
    private static int consumersReadCount = 0; // Number of consumers that have read the message

    public static void main(String[] args) {
        // Start the producer thread
        new Thread(new Producer()).start();

        // Start consumer threads
        for (int i = 0; i < NUM_CONSUMERS; i++) {
            new Thread(new Consumer()).start();
        }
    }

    static class Producer implements Runnable {
        @Override
        public void run() {
            try {
                for (int i = 0; i < 10; i++) {
                    lock.lock();
                    try {
                        // Produce a new message
                        message = "some random message " + (int) (Math.random() * 100);
                        System.out.println("Produced: " + message);

                        // Allow consumer to consume
                        semaphore.release(NUM_CONSUMERS);

                        // Wait until all consumers have read the message
                        while (NUM_CONSUMERS != consumersReadCount) {
                            allConsumersRead.await();
                        }

                        // Reset the count of consumers that have read the message
                        consumersReadCount = 0;

                        System.out.println("All consumers have read the message.");
                    } catch (Exception e) {
                        Thread.currentThread().interrupt();
                    } finally {
                        lock.unlock();

<<<<<<< HEAD:fs/il/co/ilrd/Concurrency/src/Ex3Barrier.java
                    }
=======
//                    Thread.sleep(1000); // Sleep to simulate production time
>>>>>>> origin:fs/il/co/ilrd/Concurrency/src/concurrency/Ex3Barrier.java
                }
            } catch (Exception e) {
                Thread.currentThread().interrupt();
            }
        }
    }

    static class Consumer implements Runnable {
        static int roundCounter = 0;
        @Override
        public void run() {
            try {
                for (int i = 0; i < 10; i++) {
                    semaphore.acquire();
                    lock.lock();
                    try {
                        // Consume the message
                        System.out.println(Thread.currentThread().getName() + " consumed: " + message);

                        consumersReadCount++;

                        // If all consumers have read the message, signal the producer
                        if (consumersReadCount == NUM_CONSUMERS) {
<<<<<<< HEAD:fs/il/co/ilrd/Concurrency/src/Ex3Barrier.java
                            ++roundCounter;
                            allConsumersRead.signalAll();
                        } else {
                            while (i == roundCounter) {
                                allConsumersRead.await();
                            }
=======
                            message = null;
                            allConsumersRead.signalAll();
                        } else {
                            allConsumersRead.await();
>>>>>>> origin:fs/il/co/ilrd/Concurrency/src/concurrency/Ex3Barrier.java
                        }
                    } catch (Exception e) {
                        Thread.currentThread().interrupt();
                    } finally {
                        lock.unlock();
                    }

<<<<<<< HEAD:fs/il/co/ilrd/Concurrency/src/Ex3Barrier.java
=======
//                    Thread.sleep(500); // Sleep to simulate consumption time
>>>>>>> origin:fs/il/co/ilrd/Concurrency/src/concurrency/Ex3Barrier.java
                }
            } catch (Exception e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}

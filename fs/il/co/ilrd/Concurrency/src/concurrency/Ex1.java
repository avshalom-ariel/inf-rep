package concurrency;
//public class Ex1 implements Runnable {
public class Ex1 extends Thread{
    private volatile boolean running = true;
    @Override
    public void run() {
        while (running) {
            System.out.println("Thread is running...");
            try {
                Thread.sleep(1000); // Sleep for 1 second
            } catch (InterruptedException e) {
                System.out.println("Thread was interrupted.");
            }
        }
        System.out.println("Thread has stopped.");
    }

    public void stopRunning() {
        running = false;
    }

    public static void main(String[] args) throws InterruptedException {
        Ex1 example = new Ex1();

        // if extend Thread, use:
        example.start();

        // if implements Runnuble, use:
//        Thread thread = new Thread(example);
//        thread.start();

        Thread.sleep(5000); // Let the thread run for 5 seconds

        example.stopRunning(); // Stop the thread

        // if extend Thread, use:
        example.join(); // Wait for the thread to finish

        // if implements Runnuble, use:
//        thread.join(); // Wait for the thread to finish

    }
}

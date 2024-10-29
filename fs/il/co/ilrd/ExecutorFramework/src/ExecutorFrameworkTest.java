import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import org.junit.Test;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.*;

public class ExecutorFrameworkTest {

    public static void main(String[] args) throws InterruptedException, ExecutionException, TimeoutException {
        Executor executor = Executors.newFixedThreadPool(1);

        Callable<String> task = () -> {
            while (!Thread.currentThread().isInterrupted()) {
                Thread.sleep(2000); // Simulate long-running task
            }
            return "Task completed";
        };

        // its legal downcast!
        ExecutorService executorService = (ExecutorService) executor;
        Future<String> future = executorService.submit(task);


        executorService.shutdownNow();
        try {
            String result = future.get();
            System.out.println("the result is: " + result);
        } catch (InterruptedException | ExecutionException e) {
            System.out.println("Exception catch");
        }
    }

    @Test
    public void firstTest() {
        Executor executor = Executors.newFixedThreadPool(1);

        Callable<String> task = () -> {
            Thread.sleep(2000); // Simulate long-running task
            return "Task completed";
        };

        // its legal downcast!
        ExecutorService executorService = (ExecutorService) executor;
        Future<String> future = executorService.submit(task);

        executorService.shutdownNow();

        try {
            String result = future.get();
            System.out.println("the result is: " + result);
        } catch (InterruptedException | ExecutionException e) {
            System.out.println("Exception catch");
        }
    }

    @Test
    public void singleThreadPoolTest() throws InterruptedException {
        ExecutorService executorService = Executors.newSingleThreadExecutor();

        executorService.submit(() -> {
            System.out.println("Task 1 is running.");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt(); // Handle interruption
            }
            System.out.println("Task 1 is done.");
        });

        executorService.submit(() -> {
            System.out.println("Task 2 is running.");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt(); // Handle interruption
            }
            System.out.println("Task 2 is done.");
        });

        executorService.submit(() -> {
            System.out.println("Task 3 is running.");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt(); // Handle interruption
            }
            System.out.println("Task 3 is done.");
        });

        executorService.submit(() -> {
            System.out.println("Task 4 is running.");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt(); // Handle interruption
            }
            System.out.println("Task 4 is done.");
        });

        executorService.submit(() -> {
            System.out.println("Task 5 is running.");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt(); // Handle interruption
            }
            System.out.println("Task 5 is done.");
        });

        executorService.shutdown();

        assert !executorService.isTerminated();

        Thread.sleep(5000);

        assert executorService.isShutdown();


    }

    @Test
    public void fixedThreadPoolTest() throws InterruptedException {
        ExecutorService executorService = Executors.newFixedThreadPool(3);

        executorService.submit(() -> {
            System.out.println("Task 1 is running.");
            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt(); // Handle interruption
            }
            System.out.println("Task 1 is done.");
        });

        executorService.submit(() -> {
            System.out.println("Task 2 is running.");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt(); // Handle interruption
            }
            System.out.println("Task 2 is done.");
        });

        executorService.submit(() -> {
            System.out.println("Task 3 is running.");
            try {
                Thread.sleep(1500);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt(); // Handle interruption
            }
            System.out.println("Task 3 is done.");
        });

        executorService.submit(() -> {
            System.out.println("Task 4 is running.");
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt(); // Handle interruption
            }
            System.out.println("Task 4 is done.");
        });

        executorService.submit(() -> {
            try {
                System.out.println("Task 5 is running.");
                Thread.sleep(100);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt(); // Handle interruption
            }
            System.out.println("Task 5 is done.");
        });

        executorService.shutdown();

        //Trying to submit after shutdown result in exception
//        executorService.submit(() -> {
//            try {
//                System.out.println("shouldn't be executed.");
//                Thread.sleep(1);
//            } catch (InterruptedException e) {
//                Thread.currentThread().interrupt(); // Handle interruption
//            }
//            System.out.println("Task 5 is done.");
//        });

        Thread.sleep(5000);
    }

    @Test
    public void cachedThreadPoolTest() throws InterruptedException {
        ExecutorService executorService = Executors.newCachedThreadPool();

        executorService.submit(() -> {
            System.out.println("Task 1 is running.");
            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt(); // Handle interruption
            }
            System.out.println("Task 1 is done.");
        });

        executorService.submit(() -> {
            System.out.println("Task 2 is running.");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt(); // Handle interruption
            }
            System.out.println("Task 2 is done.");
        });

        executorService.submit(() -> {
            System.out.println("Task 3 is running.");
            try {
                Thread.sleep(1500);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt(); // Handle interruption
            }
            System.out.println("Task 3 is done.");
        });

        executorService.submit(() -> {
            System.out.println("Task 4 is running.");
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt(); // Handle interruption
            }
            System.out.println("Task 4 is done.");
        });

        executorService.submit(() -> {
            System.out.println("Task 5 is running.");
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt(); // Handle interruption
            }
            System.out.println("Task 5 is done.");
        });

        executorService.shutdown();
        try {
            if (!executorService.awaitTermination(5, TimeUnit.SECONDS)) {
                System.out.println("Pool did not terminate in the specified time.");
                executorService.shutdownNow(); // Force shutdown
            }
        } catch (InterruptedException ex) {
            Thread.currentThread().interrupt(); // Preserve interrupt status
            executorService.shutdownNow(); // Force shutdown
        }
    }

    @Test
    public void scheduledThreadPoolTest() throws InterruptedException {
        ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(5);

        scheduler.scheduleWithFixedDelay(() -> {
            System.out.println("Fixed delay task 1 is running.");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
            System.out.println("Fixed delay task 1 is done.");
        }, 0, 2, TimeUnit.SECONDS);

        scheduler.scheduleWithFixedDelay(() -> {
            System.out.println("Fixed delay task 2 is running.");
            try {
                Thread.sleep(1500);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
            System.out.println("Fixed delay task 2 is done.");
        }, 0, 3, TimeUnit.SECONDS);

        scheduler.scheduleAtFixedRate(() -> {
            System.out.println("Fixed rate task 1 is running.");
            // Simulate some work
            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
            System.out.println("Fixed rate task 1 is done.");
        }, 0, 4, TimeUnit.SECONDS);

        scheduler.scheduleAtFixedRate(() -> {
            System.out.println("Fixed rate task 2 is running.");

            try {
                Thread.sleep(2500);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
            System.out.println("Fixed rate task 2 is done.");
        }, 0, 5, TimeUnit.SECONDS);
        
        Thread.sleep(10000);

        scheduler.shutdown();
        try {
            if (!scheduler.awaitTermination(5, TimeUnit.SECONDS)) {
                System.out.println("Scheduler did not terminate in the specified time.");
                scheduler.shutdownNow();
            }
        } catch (InterruptedException ex) {
            Thread.currentThread().interrupt();
            scheduler.shutdownNow();
        }
    }
}



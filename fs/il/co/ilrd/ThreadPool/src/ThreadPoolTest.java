import org.junit.Test;

import java.util.concurrent.*;
import static org.junit.Assert.*;
import org.junit.*;
import org.junit.runners.MethodSorters;

import static java.lang.Thread.sleep;


@FixMethodOrder(MethodSorters.NAME_ASCENDING)
public class ThreadPoolTest {
    private static Monitor monitor = new Monitor();
    private static String message = "message";
    private int messageNumber = 0;

    @Test
    public void a_testCreatePool() {
        ThreadPool threadPool = new ThreadPool(3);
        threadPool.shutdown();
    }

    @Test
    public void b_testSubmitRunnable() throws ExecutionException, InterruptedException {
        ThreadPool threadPool = new ThreadPool(1);
        Future<?> future = threadPool.submit(() -> monitor.writeMessage("runnable task 1"));
        assertNull(future.get());
        assertEquals("runnable task 1", monitor.getLastMessage());
        Future<String> future1 = threadPool.submit(() -> doNothing(), Priority.HIGH, message + ++messageNumber);
        assertEquals("message1", future1.get());
        threadPool.shutdown();
    }

    @Test
    public void c_testSubmitCallable() throws ExecutionException, InterruptedException {
        messageNumber = 0;
        ThreadPool threadPool = new ThreadPool(1);
        Future<String> future = threadPool.submit(() -> message + ++messageNumber);
        assertEquals("message1", future.get());
        assertEquals(threadPool.submit(() -> 20).get(), Integer.valueOf(20));
        threadPool.shutdown();
    }

    @Test
    public void d_testPriority() throws ExecutionException, InterruptedException {
        messageNumber = 0;
        ThreadPool threadPool = new ThreadPool(1);
        for (int i = 0; i < 3; i++) {
            threadPool.submit(() -> {
                try {
                    System.out.println("LOw");
                    sleep(500);
                } catch (Exception e) {
                    throw new RuntimeException(e);
                }
                ++messageNumber;
                monitor.writeMessage(message + " low");
            }, Priority.LOW);
        }
        threadPool.submit(() -> {
            ++messageNumber;
            System.out.println("high");
            try {
                sleep(500);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }

            monitor.writeMessage(message + " high");
        }, Priority.HIGH);

        sleep(1000);

        threadPool.shutdown();
        threadPool.awaitTermination();
        assertEquals(4, messageNumber);
        assertEquals("message low", monitor.getLastMessage());
    }

    @Test
    public void e_setNumOfThreads() throws InterruptedException {
        messageNumber = 0;

        Callable<Void> callable = () -> {
            sleep(1000);
            return null;
        };
        ThreadPool threadPool = new ThreadPool(1);
        long startTime = System.nanoTime();
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.setNumOfThreads(5);

        threadPool.shutdown();
        threadPool.awaitTermination();
        long endTime = System.nanoTime();
        long elapsedTime = TimeUnit.NANOSECONDS.toMillis(endTime - startTime);
        assertTrue(5000 >= elapsedTime);

    }

    @Test
    public void f_testPauseResume() throws InterruptedException {
        messageNumber = 0;

        Callable<Void> callable = () -> {
            ++messageNumber;
            return null;
        };
        ThreadPool threadPool = new ThreadPool(1);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        sleep(1000);
        threadPool.pause();
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        sleep(1000);
        assertEquals(6, messageNumber);

        threadPool.resume();
//        sleep(1000);

        threadPool.shutdown();
        threadPool.awaitTermination();
        assertEquals(10, messageNumber);
    }

    @Test
    public void g_testAwait() throws InterruptedException {
        messageNumber = 0;

        Callable<Void> callable = () -> {
            sleep(3000);
            synchronized (monitor) {
                ++messageNumber;
            }
            return null;
        };
        ThreadPool threadPool = new ThreadPool(4);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);

        threadPool.shutdown();
        threadPool.awaitTermination();
        assertEquals(4, messageNumber);
    }

    @Test
    public void h_testAwaitWithTime() throws InterruptedException {
        messageNumber = 0;

        Callable<Void> callable = () -> {
            sleep(2000);
            return null;
        };
        ThreadPool threadPool = new ThreadPool(4);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);

        threadPool.shutdown();
        assertFalse(threadPool.awaitTermination(1, TimeUnit.SECONDS));
        assertTrue(threadPool.awaitTermination(3, TimeUnit.SECONDS));
    }

    @Test
    public void i_testFutureCancel() throws InterruptedException {
        messageNumber = 0;

        Callable<Void> callable = () -> {
            sleep(2000);
            return null;
        };
        ThreadPool threadPool = new ThreadPool(1);
        Future<Void> future = threadPool.submit(callable);
        sleep(500);
        assertFalse(future.cancel(true));
        Future<Void> future2 = threadPool.submit(callable);
        Future<Void> future3 = threadPool.submit(callable);
        Future<Void> future4 = threadPool.submit(callable);
        assertTrue(future2.cancel(false));
        assertTrue(future3.cancel(false));
        assertTrue(future4.cancel(false));
        assertFalse(future4.cancel(false));
        assertFalse(future.cancel(false));

        assertFalse(future.isCancelled());
        assertTrue(future2.isCancelled());
        assertTrue(future3.isCancelled());
        assertTrue(future4.isCancelled());

        threadPool.shutdown();
        threadPool.awaitTermination();
    }

    @Test
    public void j_testFutureIsDone() throws InterruptedException {
        messageNumber = 0;

        Callable<Void> callable = () -> {
            System.out.println("sleep 1 sec:");
            sleep(1000);
            return null;
        };
        ThreadPool threadPool = new ThreadPool(1);
        Future<Void> future = threadPool.submit(callable);
        assertFalse(future.isDone());
        sleep(1200);
        assertTrue(future.isDone());
        Future<Void> future2 = threadPool.submit(callable);
        Future<Void> future3 = threadPool.submit(callable);
        future2.cancel(true);
        sleep(3000);
        assertFalse(future2.isDone());

        threadPool.shutdown();
        threadPool.awaitTermination();
    }

    @Test
    public void getTest() throws InterruptedException, ExecutionException {
        ThreadPool threadPool = new ThreadPool(5);
        Thread.sleep(3000);
        Future<?>[] futures = new Future[10];

        for (int i = 0; i < 10; i++) {

            int I = i;
            futures[i] = threadPool.submit(() -> {
                Thread.sleep(2000);
                return I;
            });
        }

        for (int i = 0; i < 10; i++) {
            assertEquals(i, futures[i].get());
        }

        threadPool.shutdown();
        threadPool.awaitTermination();
    }

    @Test
    public void getTest2() throws InterruptedException, ExecutionException {
        ThreadPool threadPool = new ThreadPool(5);
        Thread.sleep(3000);
        Future<?>[] futures = new Future[10];

        for (int i = 0; i < 10; i++) {

            int I = i;
            futures[i] = threadPool.submit(() -> {
                Thread.sleep(2000);
                return I;
            });
        }

        for (int i = 0; i < 10; i++) {
            try {
                assertEquals(i, futures[i].get(3, TimeUnit.SECONDS));
            } catch (TimeoutException e) {
                assertEquals(e, TimeoutException.class);
            }
        }

        threadPool.shutdown();
        threadPool.awaitTermination();
    }

    @Test
    public void k_testFutureGet() throws InterruptedException, ExecutionException {
        ThreadPool threadPool = new ThreadPool(1);
        Future<String> future1 = threadPool.submit(()->"String");
        Future<Integer> future2 = threadPool.submit(()-> 13 + 5);
        Future<Double> future3 = threadPool.submit(()-> 4.12);
        String s = future1.get();
        Integer i = future2.get();
        Double d = future3.get();
        assertEquals(s, "String");
        assertEquals(Integer.valueOf(18), i);
        assertEquals(Double.valueOf(4.12), d);

        threadPool.shutdown();
        threadPool.awaitTermination();
    }

    @Test
    public void l_testFutureGetWithTime() throws InterruptedException, ExecutionException, TimeoutException {
        ThreadPool threadPool = new ThreadPool(1);
        Future<String> future1 = threadPool.submit(()->{
            sleep(2000);
            return "String";
        });
        String s = future1.get(3, TimeUnit.SECONDS);
        assertEquals(s, "String");

        threadPool.shutdown();
        threadPool.awaitTermination();
    }

    @Test
    public void m_testException() throws InterruptedException {
        ThreadPool threadPool = new ThreadPool(1);
        assertThrows(IllegalArgumentException.class, ()->new ThreadPool(0));
        assertThrows(IllegalArgumentException.class, () -> new ThreadPool(-1));
        assertThrows(NullPointerException.class, () -> threadPool.submit((Runnable) null));
        assertThrows(NullPointerException.class, () -> threadPool.submit((Callable<?>) null));
        assertThrows(NullPointerException.class, () -> threadPool.submit((Runnable) null, Priority.HIGH));
        assertThrows(NullPointerException.class, () -> threadPool.submit((Callable<?>) null, Priority.HIGH));
//        assertThrows(IllegalArgumentException.class, ()->threadPool.setNumOfThreads(0));
        threadPool.submit(()-> {
            try {
                sleep(1000);
            } catch (InterruptedException ignored) {}
        });
        Future<Void> future2 = threadPool.submit(()->null);
        future2.cancel(true);
        assertThrows(CancellationException.class, future2::get);

        Future<?> futureWithException = threadPool.submit(() -> {
            throw new RuntimeException("Test Exception");
        });
        sleep(1000);
        assertThrows(ExecutionException.class, futureWithException::get);

        Future<Void> longRunningTask = threadPool.submit(() -> {
            try {
                Thread.sleep(2000); // Simulate long task
            } catch (InterruptedException ignored) {}
            return null;
        });
        assertThrows(TimeoutException.class, () -> longRunningTask.get(1, TimeUnit.SECONDS));  // Timeout of 1 second

        Future<?> future = threadPool.submit(() -> {
            try {
                Thread.sleep(3000);  // Simulate long task
            } catch (InterruptedException ignored) {}
        });

        Thread.currentThread().interrupt(); // Simulate interruption
        assertThrows(InterruptedException.class, future::get);

        threadPool.shutdown();
        threadPool.awaitTermination();
        assertThrows(RejectedExecutionException.class, () -> threadPool.submit(() -> System.out.println("Task after shutdown")));
    }


    private void doNothing() {}

    private static class Monitor {
        private String lastMessage;

        public void writeMessage(String s) {
            lastMessage = s;
        }

        public String getLastMessage() {
            return lastMessage;
        }
    }
}




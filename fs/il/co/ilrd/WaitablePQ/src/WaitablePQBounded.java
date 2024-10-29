import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

public class WaitablePQBounded<E> {
    private final PriorityQueue<E> pq;
    private Semaphore upperSem;
    private Semaphore lowerSem;
    private static final int DEFAULT_CAPACITY = 10;

    public WaitablePQBounded() {
        pq = new PriorityQueue<>();
        lowerSem = new Semaphore(0);
        upperSem = new Semaphore(DEFAULT_CAPACITY);
    }
    public WaitablePQBounded(Comparator<E> comperator) {
        pq = new PriorityQueue<>(comperator);
        lowerSem = new Semaphore(0);
        upperSem = new Semaphore(DEFAULT_CAPACITY);
    }
    public WaitablePQBounded(int capacity) {
        pq = new PriorityQueue<>();
        lowerSem = new Semaphore(0);
        upperSem = new Semaphore(capacity);
    }
    public WaitablePQBounded(Comparator<E> comperator, int capacity) {
        pq = new PriorityQueue<>(comperator);
        lowerSem = new Semaphore(0);
        upperSem = new Semaphore(capacity);
    }

    public void enqueue(E e) {
        synchronized (pq) {
            pq.add(e);
        }
        try {
            upperSem.acquire();
            lowerSem.release();
        } catch (InterruptedException ex) {
            ex.printStackTrace();
        }
    }

    public E dequeue() {
        try {
            lowerSem.acquire();
            upperSem.release();
            synchronized (pq) {
                return pq.remove();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return null;
    }

    public E dequeue(long timeout, TimeUnit unit) {
        try {
            if (lowerSem.tryAcquire(timeout, unit)) {
                upperSem.release();
                synchronized (pq) {
                    return pq.remove();
                }
            } else {
                return null;
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return null;

    }

    public boolean remove(Object element) {
        try {
            synchronized (pq) {
                if (pq.remove(element)) {
                    lowerSem.acquire();
                    upperSem.release();
                    return true;
                }
            }
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        return false;
    }

    public E peek(){
        synchronized (pq) {
            return pq.peek();
        }
    }

    public int size(){
        synchronized (pq) {
            return pq.size();
        }
    }

    public boolean isEmpty(){
        synchronized (pq) {
            return pq.isEmpty();
        }
    }
}

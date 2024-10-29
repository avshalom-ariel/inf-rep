import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

public class WaitablePQSemaphore<E> {
    private final PriorityQueue<E> pq;
    private final Semaphore semaphore;

    public WaitablePQSemaphore() {
        this(null);
    }
    public WaitablePQSemaphore(Comparator<E> comperator) {
        pq = new PriorityQueue<>(comperator);
        semaphore = new Semaphore(0);
    }

    public void enqueue(E e) {
        semaphore.release();
        synchronized (pq) {
            pq.add(e);
        }
    }

    public E dequeue() {
        try {
            semaphore.acquire();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        synchronized (pq) {
            return pq.poll();
        }
    }

    public E dequeue(long timeout, TimeUnit unit) {
        long deadline = unit.toNanos(timeout) + System.currentTimeMillis();
        try {
            while (semaphore.tryAcquire(timeout, unit)) {
                synchronized (pq) {
                    return pq.poll();
                }
            }
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        return null;
    }

    public boolean remove(Object element) {
        synchronized (pq) {
            if(pq.remove(element)) {
                semaphore.release();
                return true;
            } else {
                return false;
            }
        }
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
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class WaitablePQ<E> {
    private final PriorityQueue<E> pq;
    private ReentrantLock lock;
    private Condition notEmpty;

    public WaitablePQ() {
        pq = new PriorityQueue<>();
        lock = new ReentrantLock();
        notEmpty = lock.newCondition();
    }
    public WaitablePQ(Comparator<E> comperator) {
        pq = new PriorityQueue<>(comperator);
        lock = new ReentrantLock();
        notEmpty = lock.newCondition();    }

    public void enqueue(E e) {
        lock.lock();
        try {
            pq.add(e);
            notEmpty.signal();
        } finally {
            lock.unlock();
        }
    }

    public E dequeue() {
        lock.lock();
        try {
            while (pq.isEmpty()){
                notEmpty.await();
            }
            E result = pq.remove();
            return result;
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            lock.unlock();
        }
        return null;
    }

    public E dequeue(long timeout, TimeUnit unit) {
        long startTime = System.nanoTime();
        try {
            lock.lock();
            while (pq.isEmpty()){
                notEmpty.await(timeout, unit);
                long endTime = System.nanoTime();
                if (convertTime((endTime - startTime), unit) > timeout){
                    return null;
                }
                timeout -= convertTime((endTime - startTime), unit);
            }
            E result = pq.remove();
            return result;

        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            lock.unlock();
        }
        return null;

    }

    public boolean remove(Object element) {
        synchronized (pq) {
            return pq.remove(element);
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

    private static long convertTime(long nanoseconds, TimeUnit timeUnit) {
        switch (timeUnit) {
            case MICROSECONDS:
                return nanoseconds / 1_000;
            case MILLISECONDS:
                return nanoseconds / 1_000_000;
            case SECONDS:
                return nanoseconds / 1_000_000_000;
            case NANOSECONDS:
            default:
                return nanoseconds;
        }
    }
}
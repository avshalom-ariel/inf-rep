import java.util.*;

public class LinkedListGen<E> implements Iterable<E> {
    private Node<E> head;
    private Node<E> tail;
    private volatile int modCount;

    // public functions
    public void pushFront(E t) {
        head = new Node<>(t, head);
        if (null == head.next) {
            tail = head;
        }

        ++modCount;
    }
    public E popFront() {
        if (isEmpty()) {
            throw new PopOnEmptyListException("Cant pop from empty list");
        }
        ++modCount;

        E result = head.data;
        head = head.next;

        if(null == head){
            tail = null;
        }

        return result;
    }
    public int size() {
        int size = 0;
        for(E element : this){
            ++size;
        }

        return size;
    }

    public boolean isEmpty() {
        return null == head;
    }

    public ListIterator<E> find(E data) {
        ListIterator<E> runner =  new ListIterator<>(head);
        ListIterator<E> result =   new ListIterator<>(head);

        while(runner.hasNext()){
            if (data.equals(runner.next())) {
                return result;
            }
            result.next();
        }
        return null;
    }

    //revmoes all nodes from both lists and returns a new one
    public static <E> LinkedListGen<E> mergeLists(LinkedListGen<E> list1, LinkedListGen<E> list2) {
        LinkedListGen<E> resultList = new LinkedListGen<E>();

        resultList.head = list1.head;
        resultList.tail = list2.tail;

        list1.tail.next = list2.head;

        list1.head = null;
        list2.head = null;
        list1.tail = null;
        list2.tail = null;

        list1.modCount = 0;
        list2.modCount = 0;

        return resultList;
    }

    public static <E> void printList(LinkedListGen<E> list) {
        for(E element : list){
            System.out.print(element + " ");
        }

    }

    @Override
    public Iterator<E> iterator() {
        return new ListIterator<E>(head);
    }

    // nested Node<T> class:
    private static class Node<E> {
        private E data;
        private Node<E> next;

        public Node(E t, Node<E> next) {
            data = t;
            this.next = next;
        }
    }

    // nested ListIterator<T> class:
    private class ListIterator<E> implements Iterator<E> {
        Node<E> node;
        private volatile int expectedModCount = modCount;

        //constructor:
        public ListIterator(Node<E> node) {
            this.node = node;
        }

        @Override
        public E next() {
            if (modCount != expectedModCount) {
                throw new ConcurrentModificationException();
            }
            if (!hasNext()) {
                throw new NoSuchElementException();
            }

            E data = node.data;
            node = node.next;
            return data;
        }

        @Override
        public boolean hasNext() {
            return null != node;
        }
    }

    public static <E> LinkedListGen<E> newReverse(LinkedListGen<E> list) {
        LinkedListGen<E> reversed = new LinkedListGen<>();
        for(E element : list){
            reversed.pushFront(element);
        }

        return reversed;
    }
}


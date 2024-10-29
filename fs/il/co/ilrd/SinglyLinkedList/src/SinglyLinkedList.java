/***************************
 * Author: Avshalom Ariel
 * Date: 11/08/2024
 * Status: Reviewed
 * Reviewer: Or
 * ************************/

public class SinglyLinkedList {
//    -------- private field(s) --------

    private Node head = null;

    // defualt Ctor

    //    -------- public methods --------

    public void pushFront(Object data){
        head = new Node(data, head);
    }

    public Object popFront(){
        assert head != null;
        Object data = head.data;
        head = head.next;
        return data;
    }

    public int size(){
        int count = 0;
        ListIterator current = new ListIteratorIMP(head);
        while(current.hasNext()){
            count++;
            current.next();
        }

        return count;
    }

    public boolean isEmpty(){
        return head == null;
    }

    public ListIterator begin(){
        return new ListIteratorIMP(head);
    }

    public ListIterator find(Object dataToMatch){
        Node current = head;
        while(current != null){
            if (dataToMatch.equals(current.data)) {
                return new ListIteratorIMP(current);
            }

            current = current.next;
        }
        return null;
    }

    //    -------- inner class Node --------
    private static class Node{
        private Object data;
        private Node next;

        public Node(Object data, Node next){
            this.data = data;
            this.next = next;
        }
    }

    //    -------- inner class LisIteratorIMP --------
    private static class ListIteratorIMP implements ListIterator{

        private Node node;

        public ListIteratorIMP(Node node){
            this.node = node;
        }

        @Override
        public boolean hasNext(){
            return node != null;
        }

        @Override
        public Object next(){
            Object data = node.data;
            this.node = node.next;
            return data;
        }
    }
}

//------------------------------------------

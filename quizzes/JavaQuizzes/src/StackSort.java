import java.util.Stack;

public class StackSort {
    public static void sortStackAscending(Stack<Integer> stackToSort) {
        Stack<Integer> auxiliaryStack = new Stack<>();

        while (!stackToSort.isEmpty()) {
            int temp = stackToSort.pop();

            while (!auxiliaryStack.isEmpty() && auxiliaryStack.peek() > temp) {
                stackToSort.push(auxiliaryStack.pop());
            }

            auxiliaryStack.push(temp);
        }

        while (!auxiliaryStack.isEmpty()) {
            stackToSort.push(auxiliaryStack.pop());
        }
    }

    public static void main(String[] args) {
        Stack<Integer> stackToSort = new Stack<>();
        stackToSort.push(6);
        stackToSort.push(2);
        stackToSort.push(1);
        stackToSort.push(8);
        stackToSort.push(7);
        stackToSort.push(5);
        stackToSort.push(3);
        stackToSort.push(4);
        stackToSort.push(10);
        stackToSort.push(9);

        sortStackAscending(stackToSort);

        while(!stackToSort.isEmpty()) {
            System.out.println(stackToSort.pop());
        }
    }
}

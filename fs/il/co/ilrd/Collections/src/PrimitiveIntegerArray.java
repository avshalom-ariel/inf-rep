import java.util.*;
import java.util.stream.Collectors;

public class PrimitiveIntegerArray {
    public static void main(String[] args){
        int[] arr = {7,1,6,3,4,2,5};

        System.out.println("Printing the array (before sort): " + Arrays.toString(arr));

        List<Integer> list = Arrays.stream(arr).boxed().collect(Collectors.toList());
        System.out.println("Printing the list (before sort): " + list);
        Collections.sort(list);
        System.out.println("Printing the list (after sort): " + list);
    }
}

public class Quiz1 {
    public static void main(String[] args) {
        Integer i = 10;
        Integer j = 11;
        Integer k = ++i;
        System.out.println("k == j is: " + (k == j));
        System.out.println("k.equals(j) is: " + k.equals(j));
        System.out.println(i==j);

        int[] arr1 = {1, 2, 3, 4, 5};
        int[] arr2 = {1, 2, 3, 4, 5};
        System.out.println("arr1 == arr2 is: " + (arr1 == arr2));
        System.out.println("arr1.equals(arr2) is: " + arr1.equals(arr2));

        Boolean b = null;
//        System.out.println(b? true:false);


//        String s1 = "hi";
        String s2 = new String("hi");
        String s3 = "hi";

        System.out.println(s2 == s3);
    }
}


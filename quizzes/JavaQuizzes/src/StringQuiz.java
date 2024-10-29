

public class StringQuiz {

    public static String printReverse(String org) {
        String reversed = "";
        for (int i = org.length() - 1; i >= 0; i--) {
            reversed += org.charAt(i);
        }
        System.out.println(reversed);

        return reversed;
    }

    public static boolean isPalindrome(String str) {
        for (int i = 0; i < str.length() / 2; i++) {
            if (str.charAt(i) != str.charAt(str.length() - 1 - i)) {
                return false;
            }
        }
        return true;
    }

    private static void printAllPermutations(String str) {
        permute(str, 0, str.length() - 1);
    }

    private static void permute(String str, int low, int high) {
        if (low == high) {
            System.out.println(str);
        }
        for (int i = low; i <= high; i++) {
            str = swap(str, low, i);
            permute(str, low + 1, high);
            str = swap(str, low, i);
        }
    }

    private static String swap(String str, int low, int high) {
        char[] charArr = str.toCharArray();
        char temp = charArr[low];
        charArr[low] = charArr[high];
        charArr[high] = temp;
        return String.valueOf(charArr);
    }



    public static void main(String[] args) {
        String org = "Hello World";
        assert ("dlroW olleH".equals(printReverse(org)));

        String pal1 = "1";
        String pal2 = "2222";
        String pal3 = "12321";
        String pal4 = "112321";

        assert isPalindrome(pal1);
        assert isPalindrome(pal2);
        assert isPalindrome(pal3);
        assert isPalindrome(pal4);


        String abcd = "ABCD";
        printAllPermutations(abcd);
    }
}

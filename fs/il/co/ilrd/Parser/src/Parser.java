import java.util.regex.*;
public class Parser {
    static final String REGEX = "@([a-zA-Z]+)@([a-zA-Z]+)";

    public String[] parse(String request) {
//        "(-?\\d+\\.\\d+)([+-]\\d+\\.\\d+)i";
        Pattern pattern = Pattern.compile(REGEX);
        Matcher matcher = pattern.matcher(request);

        if (matcher.matches()) {
            String key = matcher.group(1);
            String data = matcher.group(2);

            return new String[] {key, data};
        } else {
            throw new IllegalArgumentException("Invalid request");
        }
    }

    public static void main(String[] args) {
        Parser parser = new Parser();
        String request = "@someKey@someValue";
        String[] result = parser.parse(request);
        for (String s : result) {
            System.out.println(s);
        }

    }
}
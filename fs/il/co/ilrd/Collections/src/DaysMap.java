import java.util.*;

public class DaysMap {
    public static void main(String[] args){
        Map<Integer, String> days = new LinkedHashMap<>();

        days.put(1, "Sunday");
        days.put(2, "Monday");
        days.put(3, "Tuesday");
        days.put(4, "Wednesday");
        days.put(5, "Thursday");
        days.put(6, "Friday");
        days.put(7, "Saturday");

        for(Map.Entry<Integer, String> set : days.entrySet()){
            System.out.println("{" + set.getKey() + ", : " + set.getValue() + "}");
        }

        for(String value : days.values()){
            System.out.println("Value is: " + value);
        }

    }

}

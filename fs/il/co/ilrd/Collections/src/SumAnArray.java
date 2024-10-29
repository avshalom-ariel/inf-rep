import java.util.HashMap;
import java.util.Map;

public class SumAnArray {
    public static void main(String[] args) {
        DataObject[] dataArr = {
                new DataObject("Avshi", 1000000000),
                new DataObject("Yarden", 10),
                new DataObject("Or", 100),
                new DataObject("Yarden", 1000),
                new DataObject("Uriah", 10000),
                new DataObject("Uriah", 100000),
                new DataObject("Ido", 1000000),
                new DataObject("Uriah", 10000000)};


        Map<String, Integer> map = new HashMap<>();
        for (DataObject dataObject : dataArr) {
            map.put(dataObject.getCode(), map.getOrDefault(dataObject.getCode(), 0) + dataObject.getValue());
        }

        for (Map.Entry<String, Integer> entry : map.entrySet()) {
            System.out.println("code: " + entry.getKey() + ", sum of values: " + entry.getValue());
        }
    }
}

class DataObject{
    private int value;
    private String code;

    public DataObject(String code, int value){
        this.code = code;
        this.value = value;
    }

    public String getCode(){
        return code;
    }

    public int getValue(){
        return value;
    }
}

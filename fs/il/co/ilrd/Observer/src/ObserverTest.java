import java.util.function.Consumer;

public class ObserverTest {
    public static void main(String[] args) {
        StringBuilder locker = new StringBuilder("");
        WeatherMan dani = new WeatherMan("hot");
        IphoneWeatherApp iphone1 = new IphoneWeatherApp(s -> locker.append(s + " "), ()-> System.out.println("Stop"));
        IphoneWeatherApp iphone2 = new IphoneWeatherApp((a) -> System.out.println("data in iphone 2 is: " + a), ()-> System.out.println("Stop"));
        iphone2.register(dani);
        iphone1.register(dani);
        dani.setWeatherDescription("cold");
        dani.produce(dani.getWeatherDescription());
        System.out.println(iphone1.getData());
        System.out.println(iphone2.getData());
        dani.setWeatherDescription("very cold");
        iphone2.unregister();
        dani.produce(dani.getWeatherDescription());
        System.out.println(locker);
        dani.close();
    }
}

class IphoneWeatherApp extends Subscriber<String>{
    int dataLen = 0;
    public IphoneWeatherApp(Consumer<String> consumer, Runnable runnable) {
        super(consumer, runnable);
    }

    private class WeatherCons implements Consumer<String> {

        @Override
        public void accept(String s) {
            dataLen = s.length();
            System.out.println(s + " len is " + dataLen);
        }
    }
}

class WeatherMan extends Publisher<String>{
    private String weatherDescription;

    public WeatherMan(String weatherDescription){
        this.weatherDescription = weatherDescription;
    }

    public String getWeatherDescription() {
        return weatherDescription;
    }

    public void setWeatherDescription(String weatherDescription) {
        this.weatherDescription = weatherDescription;
    }
}
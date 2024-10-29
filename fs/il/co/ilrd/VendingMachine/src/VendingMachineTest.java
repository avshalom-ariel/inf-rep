import org.junit.*;
import static org.junit.Assert.*;

public class VendingMachineTest {
    VendingMachine vm;
    MonitorIMP monitor;
    Product product1;
    Product product2;
    Product product3;
    Product product4;

    @Before
    public void setUp() {
        // Create products
        product1 = new ProductIMP("Pikachu", 500);
        product2 = new ProductIMP("Charmander", 350);
        product3 = new ProductIMP("Squirtle", 200);
        product4 = new ProductIMP("Bulbazaur", 100);

        // Create monitor
        monitor = new MonitorIMP();

        // Initialize the vending machine with the monitor and products
        Product[] productList = {product1, product2, product3, product4};
        vm = new VendingMachine(monitor, productList);

        // Turn on the vending machine
        vm.turnOn();
    }

    @Test
    public void testTurnOnMachine() {
        vm.turnOn();
        vm.turnOff();

        assertEquals("Cancelled, please take your change 0", monitor.getLastMessage());
    }

    @Test
    public void selectProductTest() {
        vm.selectProduct(1);

        assertEquals("Not enough credit, please insert 350 more credit.", monitor.getLastMessage());

        vm.selectProduct(3);

        assertEquals("Not enough credit, please insert 100 more credit.", monitor.getLastMessage());

        vm.selectProduct(0);

        assertEquals("Not enough credit, please insert 500 more credit.", monitor.getLastMessage());
    }

    @Test
    public void insertCoinTest() {
        vm.insertCoin(Coin.SHEKEL);

        assertEquals("Coin inserted: 1 Shekel. Total credit: 100", monitor.getLastMessage());

        vm.insertCoin(Coin.HEZI_SHEKEL);

        assertEquals("Coin inserted: Hezi Shekel. Total credit: 150", monitor.getLastMessage());

        vm.insertCoin(Coin.SHNEKEL);

        assertEquals("Coin inserted: 2 Shekels. Total credit: 350", monitor.getLastMessage());
    }

    @Test
    public void cancelTest() {
        vm.insertCoin(Coin.SHEKEL);

        assertEquals("Coin inserted: 1 Shekel. Total credit: 100", monitor.getLastMessage());

        vm.insertCoin(Coin.HEZI_SHEKEL);

        assertEquals("Coin inserted: Hezi Shekel. Total credit: 150", monitor.getLastMessage());

        vm.cancel();

        assertEquals("Cancelled, please take your change 150", monitor.getLastMessage());

        vm.insertCoin(Coin.SHEKEL);

        assertEquals("Coin inserted: 1 Shekel. Total credit: 100", monitor.getLastMessage());
    }

    @Test
    public void changeTest1() {
        vm.insertCoin(Coin.SHEKEL);

        assertEquals("Coin inserted: 1 Shekel. Total credit: 100", monitor.getLastMessage());

        vm.selectProduct(1);

        assertEquals("Not enough credit, please insert 250 more credit.", monitor.getLastMessage());

        vm.insertCoin(Coin.SHEKEL);

        assertEquals("Not enough credit, please insert 150 more credit.", monitor.getLastMessage());

        vm.insertCoin(Coin.SHEKEL);

        assertEquals("Not enough credit, please insert 50 more credit.", monitor.getLastMessage());

        vm.insertCoin(Coin.SHEKEL);

        assertEquals("Current credit: 50", monitor.getLastMessage());

    }

    @Test
    public void changeTest2() {
        vm.insertCoin(Coin.SHEKEL);

        assertEquals("Coin inserted: 1 Shekel. Total credit: 100", monitor.getLastMessage());

        vm.insertCoin(Coin.SHEKEL);

        assertEquals("Coin inserted: 1 Shekel. Total credit: 200", monitor.getLastMessage());

        vm.insertCoin(Coin.SHEKEL);

        assertEquals("Coin inserted: 1 Shekel. Total credit: 300", monitor.getLastMessage());

        vm.insertCoin(Coin.SHEKEL);

        assertEquals("Coin inserted: 1 Shekel. Total credit: 400", monitor.getLastMessage());

        vm.selectProduct(3);

        assertEquals("Current credit: 300", monitor.getLastMessage());

        vm.selectProduct(1);

        assertEquals("Not enough credit, please insert 50 more credit.", monitor.getLastMessage());

        vm.insertCoin(Coin.HEZI_SHEKEL);

        assertEquals("Current credit: 0", monitor.getLastMessage());

        vm.turnOff();

        assertEquals("Cancelled, please take your change 0", monitor.getLastMessage());
    }

    @Test
    public void timerTest() throws InterruptedException {
        vm.selectProduct(1);
        Thread.sleep(4000);
        vm.insertCoin(Coin.SHEKEL);
        Thread.sleep(6000);
        assertEquals("No action for too long. returned change: 100", monitor.lastMessage);

        vm.insertCoin(Coin.SHEKEL);

        vm.selectProduct(1);
        Thread.sleep(1000);
        vm.selectProduct(1);
        Thread.sleep(1000);
        vm.selectProduct(1);
        Thread.sleep(1000);
        vm.selectProduct(1);
        Thread.sleep(1000);
        vm.selectProduct(1);
        Thread.sleep(1000);
        vm.selectProduct(1);
        Thread.sleep(1000);
        vm.selectProduct(1);
        Thread.sleep(1000);
        vm.cancel();

        assertEquals("Cancelled, please take your change 100", monitor.lastMessage);

        Thread.sleep(6000); // to make sure the thread is canceled
    }

    @Test
    public void fillProductTest1() {
        vm.insertCoin(Coin.TEN_SHEKEL);
        vm.insertCoin(Coin.TEN_SHEKEL);

        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);

        assertEquals("Product currently unavailable", monitor.lastMessage);

        vm.fillProduct(3);

        assertEquals("Please turn off machine first", monitor.lastMessage);

        vm.selectProduct(3);

        assertEquals("Product currently unavailable", monitor.lastMessage);

        vm.turnOff();
        vm.fillProduct(3);
        vm.turnOn();

        vm.selectProduct(3);

        assertEquals("Not enough credit, please insert 100 more credit.", monitor.lastMessage);

        vm.insertCoin(Coin.TEN_SHEKEL);

        assertEquals("Current credit: 900", monitor.lastMessage);

        vm.selectProduct(3);

        assertEquals("Current credit: 800", monitor.lastMessage);
    }

    @Test
    public void fillProductTest2() {
        vm.insertCoin(Coin.TEN_SHEKEL);
        vm.insertCoin(Coin.TEN_SHEKEL);

        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);

        assertEquals("Product currently unavailable", monitor.lastMessage);

        vm.fillProduct(3, 1);

        assertEquals("Please turn off machine first", monitor.lastMessage);

        vm.selectProduct(3);

        assertEquals("Product currently unavailable", monitor.lastMessage);

        vm.turnOff();
        vm.fillProduct(3, 1);
        vm.turnOn();

        vm.selectProduct(3);

        assertEquals("Not enough credit, please insert 100 more credit.", monitor.lastMessage);

        vm.insertCoin(Coin.TEN_SHEKEL);

        assertEquals("Current credit: 900", monitor.lastMessage);

        vm.selectProduct(3);

        assertEquals("Product currently unavailable", monitor.lastMessage);
    }

    @Test
    public void emptySlotTest() {
        vm.insertCoin(Coin.TEN_SHEKEL);

        vm.selectProduct(3);
        vm.selectProduct(3);
        vm.selectProduct(3);

        assertEquals("Current credit: 700", monitor.lastMessage);

        vm.turnOff();
        vm.emptySlot(3);
        vm.turnOn();

        vm.selectProduct(3);
        assertEquals("Product currently unavailable", monitor.lastMessage);
    }

    @Test
    public void reassignSlot() {
        Product newProduct = new ProductIMP("Charizard", 3000);

        vm.turnOff();
        vm.reassignSlot(3, newProduct);
        vm.turnOn();

        vm.selectProduct(3);

        assertEquals("Not enough credit, please insert 3000 more credit.", monitor.lastMessage);
    }

    /******************* Product implementation ********************/
    private static class ProductIMP implements Product {
        private String name;
        private int price;

        public ProductIMP(String name, int price) {
            this.name = name;
            this.price = price;
        }

        @Override
        public void setPrice(int newPrice) {
            this.price = newPrice;
        }

        @Override
        public int getPrice() {
            return price;
        }

        @Override
        public String getName() {
            return name;
        }

        @Override
        public String toString() {
            return "name: " + name + ", price: " + price;
        }
    }

    private static class MonitorIMP implements Monitor {
        public String lastMessage;

        @Override
        public void display(String outPut) {
            lastMessage = outPut;
            System.out.println(outPut);
        }

        public String getLastMessage() {
            return lastMessage;
        }
    }


}

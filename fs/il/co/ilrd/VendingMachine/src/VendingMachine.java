/*****************************/
/*Author: Avshalom Ariel     */
/*Status: Approved           */
/*Reviewer: Shahar Marom     */
/*Review Date: 18/08/2024    */
/*****************************/

import java.util.*; //for Time and TimerTask

public class VendingMachine {
    private VendingMachineState state = VendingMachineState.OFF;
    private int credit = 0;
    private final Monitor monitor;
    private VendingSlot[] slots;
    private int selectedCode = -1;
    private Timer resetTimer;

    private static final int PRODUCT_SLOTS = 50;
    private static final int DEFAULT_PRODUCT_AMOUNT = 10;

    //ctor
    public VendingMachine(Monitor monitor, Product[] productList) {
        this.monitor = monitor;
        slots = new VendingSlot[PRODUCT_SLOTS];
        int i = 0;

        for (; i < productList.length && i < PRODUCT_SLOTS; ++i) {
            slots[i] = new VendingSlot(productList[i], DEFAULT_PRODUCT_AMOUNT, i);
            monitor.display("Product " + productList[i] + ", code: " + indexToCode(i));
        }
        //Fill empty slots if needed
        for (; i < PRODUCT_SLOTS; ++i) {
            slots[i] = new VendingSlot(productList[0], 0, i);
        }
    }

    /********************** API Functions *************************/
    public void cancel() {
        state.cancel(this);
    }
    public void insertCoin(Coin coin) {
        state.insertCoin(this, coin);
    }
    public void selectProduct(int code) {
        state.selectProduct(this, code);
    }

    public void turnOn() {
        resetTimer();
        state.turnOn(this);
    }

    public void turnOff() {
        cancelTimer();
        state.turnOff(this);
    }

    /********************** Private Functions *************************/

    private int codeToIndex(int code) {
        int index = code;

        if (PRODUCT_SLOTS < index) {
            return -1;
        }

        return index;
    }

    private int indexToCode(int index) {
        int code = index;

        return code;
    }

    public void fillProduct(int code) {
        state.fillProduct(this, code);
    }

    public void fillProduct(int code, int amount) {
        state.fillProduct(this, code, amount);
    }

    public void emptySlot(int code) {
        state.emptySlot(this, code);
    }

    public void reassignSlot(int code, Product product) {
        state.reassignSlot(this, code, product);
    }

    private boolean isAvailable(int index) {
        if (0 == slots[index].amount) {
            return false;
        }
        return true;
    }

    private boolean isEnoughCredit(int index) {
        if (credit >= slots[index].product.getPrice()) {
            return true;
        }
        return false;
    }

    private void buy(int index) {
        resetTimer.cancel();
        credit -= slots[index].product.getPrice();
        slots[index].amount -= 1;
    }

    /******************* Vending Slot ****************************/
    private static class VendingSlot {
        private Product product;
        private int amount;
        private int code;

        //ctor
        private VendingSlot(Product product, int amount, int code){
            this.product = product;
            this.amount = amount;
            this.code = code;
        }

        @Override
        public String toString() {
            return "VendingSlot{" + "product: " + product.getName() + ", price: "
                    + product.getPrice() + ", amount: " + amount + ", code: " + code + '}';
        }
    }

/************************* ENUM *****************************/
    private enum VendingMachineState {
        WAITING_FOR_SELECTION {
            @Override
            public void cancel(VendingMachine vm) {
                vm.monitor.display("Cancelled, please take your change " + vm.credit);
                vm.credit = 0;
                vm.cancelTimer();
            }
            @Override
            public void insertCoin(VendingMachine vm, Coin coin) {
                vm.resetTimer();
                vm.credit += coin.getValue();
                vm.monitor.display("Coin inserted: " + coin.toString() + ". Total credit: " + vm.credit);
            }

            @Override
            public void fillProduct(VendingMachine vm, int code) { vm.monitor.display("Please turn off machine first"); }

            @Override
            public void fillProduct(VendingMachine vm, int code, int amount) { vm.monitor.display("Please turn off machine first"); }

            @Override
            public void emptySlot(VendingMachine vm, int code) { vm.monitor.display("Please turn off machine first"); }

            @Override
            public void reassignSlot(VendingMachine vm, int code, Product product) { vm.monitor.display("Please turn off machine first"); }
        },
        WAITING_FOR_COINS {
            @Override
            public void cancel(VendingMachine vm) {
                WAITING_FOR_SELECTION.cancel(vm);
                vm.state = WAITING_FOR_SELECTION;
            }

            @Override
            public void insertCoin(VendingMachine vm, Coin coin) {
                vm.resetTimer();
                vm.credit += coin.getValue();
                selectProduct(vm, vm.codeToIndex(vm.selectedCode));
            }

            @Override
            public void selectProduct(VendingMachine vm, int index) {
                WAITING_FOR_SELECTION.selectProduct(vm, index);
            }

            @Override
            public void fillProduct(VendingMachine vm, int code) { vm.monitor.display("Please turn off machine first"); }

            @Override
            public void fillProduct(VendingMachine vm, int code, int amount) { vm.monitor.display("Please turn off machine first"); }

            @Override
            public void emptySlot(VendingMachine vm, int code) { vm.monitor.display("Please turn off machine first"); }

            @Override
            public void reassignSlot(VendingMachine vm, int code, Product product) { vm.monitor.display("Please turn off machine first"); }
        },
        OFF {
            @Override
            public void turnOn(VendingMachine vm){
                vm.state = WAITING_FOR_SELECTION;
            }
            @Override
            public void turnOff(VendingMachine vm) {}

            @Override
            public void selectProduct(VendingMachine vm, int index) {}
        };

        /************************* ENUM Functions *****************************/

        public void selectProduct(VendingMachine vm, int code) {
            vm.selectedCode = code;
            int index = vm.codeToIndex(code);
            vm.resetTimer();

            if (index != -1) {
                vm.startTimer();
                if (!vm.isAvailable(index)) {
                    vm.monitor.display("Product currently unavailable");
                } else if (vm.isEnoughCredit(index)) {
                    vm.monitor.display("Product received");
                    vm.buy(index);
                    vm.monitor.display("Current credit: " + vm.credit);
                } else {
                    vm.monitor.display("Selected product: " + vm.slots[index].product.getName());
                    vm.monitor.display("Not enough credit, please insert " +
                            (vm.slots[index].product.getPrice() - vm.credit) + " more credit.");
                    vm.state = WAITING_FOR_COINS;
                }

            } else {
                vm.monitor.display("Invalid code");
            }
        }
        public void cancel(VendingMachine vm) {}
        public void insertCoin(VendingMachine vm, Coin coin) {};
        public void turnOn(VendingMachine vm){}
        public void turnOff(VendingMachine vm) {
            vm.state.cancel(vm);
            vm.state = OFF;
        }
        public void fillProduct(VendingMachine vm, int code) {
            int index = vm.codeToIndex(code);

            if (-1 == index) {
                vm.monitor.display("Invalid code");
            } else {
                vm.slots[index].amount = DEFAULT_PRODUCT_AMOUNT;
            }
        }
        public void fillProduct(VendingMachine vm, int code, int amount) {
            int index = vm.codeToIndex(code);

            if (-1 == index) {
                vm.monitor.display("Invalid code");
            } else {
                vm.slots[index].amount = amount;
            }
        }
        public void emptySlot(VendingMachine vm, int code) {
            int index = vm.codeToIndex(code);
            if (-1 == index) {
                vm.monitor.display("Invalid code");
            } else {
                vm.slots[index].amount = 0;
            }
        }
        public void reassignSlot(VendingMachine vm, int code, Product product) {
            int index = vm.codeToIndex(code);
            if (-1 == index) {
                vm.monitor.display("Invalid code");
            } else {
                vm.slots[index].product = product;
                vm.slots[index].amount = DEFAULT_PRODUCT_AMOUNT;
            }
        }
    }

    /********************* Timer ***************************/

    private class ReserTimerTask extends TimerTask {
        @Override
        public void run() {
            monitor.display("No action for too long. returned change: " + credit);
            credit = 0;
            state = VendingMachineState.WAITING_FOR_SELECTION;
            selectedCode = 0;
        }
    }
    private void startTimer() {
        cancelTimer(); // Cancel old ones before starting new one
        resetTimer = new Timer(true);
        resetTimer.schedule(new ReserTimerTask(), 5000); // 5 seconds
    }
    // For code readability
    private void resetTimer() {
        startTimer();
    }
    private void cancelTimer() {
        if (resetTimer != null) {
            resetTimer.cancel();
            resetTimer = null;
        }
    }
}


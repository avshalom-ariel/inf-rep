public class PizzaQuiz {
    public interface Pizza {
        String getName();
        int getPrice();
    }

    public interface PizzaDecorator extends Pizza {
        public Pizza pizza = null;

        String getName();
        int getPrice();
    }

    /************** Pizzas ******************/
    public static class PeppyPaneer implements Pizza {
        String name = "Peppy Pane";

        @Override
        public String getName() {
            return name;
        }
        public int getPrice() {
            return 10;
        }
    }





    public static class Tomato implements PizzaDecorator {
        String name = " Tomato";
        Pizza pizza;

        public Tomato(Pizza pizza) {
            this.pizza = pizza;
        }

        @Override
        public String getName() {
            return pizza.getName() + name;
        }
        public int getPrice() {
            return pizza.getPrice() + 1;
        }
    }


    public static void main(String[] args) {
        Pizza myPizza = new PeppyPaneer();
        System.out.println(myPizza.getName() + " cost: " + myPizza.getPrice());
        myPizza = new Tomato(myPizza);
        System.out.println(myPizza.getName() + " cost: " + myPizza.getPrice());
        myPizza = new Tomato(myPizza);
        System.out.println(myPizza.getName() + " cost: " + myPizza.getPrice());

    }


}

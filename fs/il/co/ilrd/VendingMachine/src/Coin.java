public enum Coin {
    TEN_AGOROT(10),
    HEZI_SHEKEL(50),
    SHEKEL(100),
    SHNEKEL(200),
    FIVE_SHEKEL(500),
    TEN_SHEKEL(1000);

    private final int value;

    Coin(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }

    @Override
    public String toString() {
        switch (this) {
            case TEN_AGOROT:
                return "10 Agorot";
            case HEZI_SHEKEL:
                return "Hezi Shekel";
            case SHEKEL:
                return "1 Shekel";
            case SHNEKEL:
                return "2 Shekels";
            case FIVE_SHEKEL:
                return "5 Shekels";
            case TEN_SHEKEL:
                return "10 Shekels";
            default:
                return super.toString();
        }
    }
}
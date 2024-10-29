import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.Objects;

public class ComplexNumber implements Comparable<ComplexNumber> {

    private double real;
    private double imaginary;

    // Constructors
    public ComplexNumber(){this(0,0);} // initial the real and imaginary to 0
    public ComplexNumber(double real, double imaginary){
        this.real = real;
        this.imaginary = imaginary;
    }

    // Getters and setters
    public double getReal() {
        return real;
    }

    public void setReal(double real) {
        this.real = real;
    }

    public double getImaginary() {
        return imaginary;
    }

    public void setImaginary(double imaginary) {
        this.imaginary = imaginary;
    }

    // Set the full complex number
    public void setValue(double real, double imaginary){
        this.real = real;
        this.imaginary = imaginary;
    }

    // Check if the object is real
    public boolean isReal(){
        Double zero = new Double(0);
        return zero.equals(imaginary);
    }

    // Check if the object is imaginary
    public boolean isImaginary(){
        return !isReal();
    }

    // Add between 2 complex numbers
    public ComplexNumber add(ComplexNumber other){
        ComplexNumber result = new ComplexNumber();

        result.setReal(this.real + other.getReal());
        result.setImaginary(this.imaginary + other.getImaginary());

        return result;
    }

    // Subtract between 2 complex numbers
    public ComplexNumber subtract(ComplexNumber other){
        ComplexNumber result = new ComplexNumber();

        result.setReal(this.real - other.getReal());
        result.setImaginary(this.imaginary - other.getImaginary());

        return result;
    }

    // Multiply two complex number
    public ComplexNumber multipleWith(ComplexNumber other){
        double real = this.real * other.getReal() - this.imaginary * other.getImaginary();
        double imaginary = this.real * other.getImaginary() + this.imaginary * other.getReal();

        return new ComplexNumber(real, imaginary);
    }

    // Divide two complex number - if divide by 0 is undefined
    public ComplexNumber divideBy(ComplexNumber other) {
        double divisorAbs = Math.pow(other.getReal(), 2) + Math.pow(other.getImaginary(), 2);

        double real = (this.real * other.getReal() + this.imaginary * other.getImaginary()) / divisorAbs;
        double imaginary = (this.imaginary * other.getReal() - this.real * other.getImaginary()) / divisorAbs;

        return new ComplexNumber(real, imaginary);
    }

    // Define a regex pattern to match the real and imaginary parts of the complex number
    static final String REGEX = "(-?\\d+\\.\\d+)([+-]\\d+\\.\\d+)i";


    // Parse string to complex number. pattern: x + yi
    public static ComplexNumber parse(String expression) {
        // Clean up whitespaces
        String cleanExpresion = expression.replaceAll("\\s+", "");

        Pattern pattern = Pattern.compile(REGEX);
        Matcher matcher = pattern.matcher(cleanExpresion);

        if (matcher.matches()) {
            double real = Double.parseDouble(matcher.group(1));
            double imaginary = Double.parseDouble(matcher.group(2));

            return new ComplexNumber(real, imaginary);
        } else {
            return null;
        }
    }

    @Override
    public String toString() {
        if (imaginary >= 0) {
            return real + "+" + imaginary + 'i';
        } else {
            return "" + real + imaginary + 'i';
        }
    }

    // Override equals to compare between 2 complex numbers
    @Override
    public boolean equals(Object o) {
        if (this == o) {return true;};

        if (!(o instanceof ComplexNumber)) {return false;}

        ComplexNumber other = (ComplexNumber) o;
        if (0 != (Double.compare(real, other.real))) {return false;}
        return 0 == Double.compare(imaginary, other.imaginary);
    }

    @Override
    public int hashCode() {
        return Objects.hash(real, imaginary);
    }

    @Override
    public int compareTo(ComplexNumber other){
        double thisAbs = Math.sqrt(Math.pow(real, 2) + Math.pow(imaginary, 2));
        double otherAbs = Math.sqrt(Math.pow(other.getImaginary(), 2) + Math.pow(other.getReal(), 2));

        return (int) (thisAbs - otherAbs);
    }
}

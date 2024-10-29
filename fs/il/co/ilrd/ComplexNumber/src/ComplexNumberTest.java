import org.junit.*;
import static org.junit.Assert.*;

public class ComplexNumberTest {

    ComplexNumber c1;
    ComplexNumber c2;
    ComplexNumber c3;
    ComplexNumber c4;
    ComplexNumber c5;

    @Before
    public void setUp() throws Exception {
        c1 = new ComplexNumber(4, 5);
        c2 = new ComplexNumber(0, 0);
        c3 = new ComplexNumber(-5.4554, 15956.45);
        c4 = new ComplexNumber(44444, -8954.546);
        c5 = new ComplexNumber(-1515151515, 5456.14);
    }


    @Test
    public void getRealTest() {
        assertEquals(0, Double.compare(4.0, c1.getReal()));
        assertEquals(0, Double.compare(0.0, c2.getReal()));
        assertEquals(0, Double.compare(-5.4554, c3.getReal()));
        assertEquals(0, Double.compare(44444.0, c4.getReal()));
        assertEquals(0, Double.compare(-1515151515.0, c5.getReal()));
    }

    @Test
    public void getImaginaryTest() {
        assertEquals(0, Double.compare(5.0, c1.getImaginary()));
        assertEquals(0, Double.compare(0.0, c2.getImaginary()));
        assertEquals(0, Double.compare(15956.45, c3.getImaginary()));
        assertEquals(0, Double.compare(-8954.546, c4.getImaginary()));
        assertEquals(0, Double.compare(5456.14, c5.getImaginary()));
    }

    @Test
    public void setRealTest() {
        c1.setReal(-1.11111);
        c2.setReal(-2.22222);
        c3.setReal(-3.33333);
        c4.setReal(-4.44444);
        c5.setReal(-5.55555);

        assertEquals(0, Double.compare(c1.getReal(), -1.11111));
        assertEquals(0, Double.compare(c2.getReal(), -2.22222));
        assertEquals(0, Double.compare(c3.getReal(), -3.33333));
        assertEquals(0, Double.compare(c4.getReal(), -4.44444));
        assertEquals(0, Double.compare(c5.getReal(), -5.55555));
    }

    @Test
    public void setImaginaryTest() {
        c1.setImaginary(-1.11111);
        c2.setImaginary(-2.22222);
        c3.setImaginary(-3.33333);
        c4.setImaginary(-4.44444);
        c5.setImaginary(-5.55555);

        assertEquals(0, Double.compare(c1.getImaginary(), -1.11111));
        assertEquals(0, Double.compare(c2.getImaginary(), -2.22222));
        assertEquals(0, Double.compare(c3.getImaginary(), -3.33333));
        assertEquals(0, Double.compare(c4.getImaginary(), -4.44444));
        assertEquals(0, Double.compare(c5.getImaginary(), -5.55555));
    }

    @Test
    public void setValueTest() {
        c1.setValue(-1.11111, -1.11111);
        c2.setValue(-2.22222, 2.22222);
        c3.setValue(3.33333, -3.33333);
        c4.setValue(-4.44444, 4.44444);
        c5.setValue(5.55555, -5.55555);

        assertEquals(0, Double.compare(c1.getImaginary(), -1.11111));
        assertEquals(0, Double.compare(c2.getImaginary(), 2.22222));
        assertEquals(0, Double.compare(c3.getImaginary(), -3.33333));
        assertEquals(0, Double.compare(c4.getImaginary(), 4.44444));
        assertEquals(0, Double.compare(c5.getImaginary(), -5.55555));

        assertEquals(0, Double.compare(c1.getReal(), -1.11111));
        assertEquals(0, Double.compare(c2.getReal(), -2.22222));
        assertEquals(0, Double.compare(c3.getReal(), 3.33333));
        assertEquals(0, Double.compare(c4.getReal(), -4.44444));
        assertEquals(0, Double.compare(c5.getReal(), 5.55555));
    }

    @Test
    public void isRealTest() {
        c3 = new ComplexNumber(-5.4554, 0);
        c4 = new ComplexNumber(44444, 0);
        c5 = new ComplexNumber(-1515151515, -1);

        assertFalse(c1.isReal());
        assertTrue(c2.isReal());
        assertTrue(c3.isReal());
        assertTrue(c4.isReal());
        assertFalse(c5.isReal());
    }

    @Test
    public void isImaginaryTest() {
        c1 = new ComplexNumber(4, 0);

        assertFalse(c1.isImaginary());
        assertFalse(c2.isImaginary());
        assertTrue(c3.isImaginary());
        assertTrue(c4.isImaginary());
        assertTrue(c5.isImaginary());
    }

    @Test
    public void addTest() {
        c1 = new ComplexNumber(4, 0);

        ComplexNumber result = c1.add(c2);

        assertEquals(0, Double.compare(4.0, result.getReal()));
        assertEquals(0, Double.compare(0.0, result.getImaginary()));

        result = c2.add(c2);

        assertEquals(0, Double.compare(0.0, result.getReal()));
        assertEquals(0, Double.compare(0.0, result.getImaginary()));


        result = c3.add(c4);

        assertEquals(0, Double.compare(44444-5.4554, result.getReal()));
        assertEquals(0, Double.compare(15956.45-8954.546, result.getImaginary()));

        result = c4.add(c5);

        assertEquals(0, Double.compare(44444-1515151515, result.getReal()));
        assertEquals(0, Double.compare(5456.14-8954.546, result.getImaginary()));

        result = c1.add(c5);

        assertEquals(0, Double.compare(4-1515151515, result.getReal()));
        assertEquals(0, Double.compare(5456.14+0, result.getImaginary()));
    }

    @Test
    public void subtractTest() {

        ComplexNumber result = c1.subtract(c2);

        assertEquals(0, Double.compare(4.0, result.getReal()));
        assertEquals(0, Double.compare(5.0, result.getImaginary()));

        result = c2.subtract(c2);

        assertEquals(0, Double.compare(0.0, result.getReal()));
        assertEquals(0, Double.compare(0.0, result.getImaginary()));


        result = c3.subtract(c4);

        assertEquals(0, Double.compare(-44444-5.4554, result.getReal()));
        assertEquals(0, Double.compare(15956.45+8954.546, result.getImaginary()));

        result = c4.subtract(c5);

        assertEquals(0, Double.compare(44444+1515151515, result.getReal()));
        assertEquals(0, Double.compare(-5456.14-8954.546, result.getImaginary()));

        result = c1.subtract(c5);

        assertEquals(0, Double.compare(4+1515151515, result.getReal()));
        assertEquals(0, Double.compare(-5456.14+5, result.getImaginary()));
    }

    @Test
    public void multipleWithTest() {
        c1 = new ComplexNumber(4, 0);

        ComplexNumber result = c1.multipleWith(c2);

        assertEquals(0, Double.compare(0.0, result.getReal()));
        assertEquals(0, Double.compare(0.0, result.getImaginary()));

        result = c2.multipleWith(c2);

        assertEquals(0, Double.compare(0, result.getReal()));
        assertEquals(0, Double.compare(0, result.getImaginary()));

        result = c3.multipleWith(c4);

        assertEquals(0, Double.compare(1.4264030572410002E8, result.getReal()));
        assertEquals(0, Double.compare(7.092173144302485E8, result.getImaginary()));

        result = c4.multipleWith(c5);

        assertEquals(0, Double.compare(-6.733934507540339E13, result.getReal()));
        assertEquals(0, Double.compare(1.356773643072335E13, result.getImaginary()));

        result = c1.multipleWith(c5);

        assertEquals(0, Double.compare(-6.06060606E9, result.getReal()));
        assertEquals(0, Double.compare(21824.56, result.getImaginary()));
    }

    @Test
    public void divideByTest() {
        c1 = new ComplexNumber(4, 0);

        ComplexNumber result = c2.divideBy(c1);

        assertEquals(0, Double.compare(0.0, result.getReal()));
        assertEquals(0, Double.compare(0.0, result.getImaginary()));

        result = c4.divideBy(c3);

        assertEquals(0, Double.compare(-0.5621388246146506, result.getReal()));
        assertEquals(0, Double.compare(-2.785139132316787, result.getImaginary()));

        result = c3.divideBy(c4);

        assertEquals(0, Double.compare(-0.06963196104495574, result.getReal()));
        assertEquals(0, Double.compare(0.34499431648260137, result.getImaginary()));

        result = c4.divideBy(c5);

        assertEquals(0, Double.compare(-2.933306128477391E-5, result.getReal()));
        assertEquals(0, Double.compare(5.90989473070025E-6, result.getImaginary()));

        result = c1.divideBy(c5);

        assertEquals(0, Double.compare(-2.6400000002297655E-9, result.getReal()));
        assertEquals(0, Double.compare(-9.506778337778077E-15, result.getImaginary()));
    }

    @Test
    public void equalsTest() {
        c1 = new ComplexNumber(4, 0);

        assertTrue(c1.equals(c1));
        assertFalse(c2.equals(c3));
        assertFalse(c3.equals(c2));
        assertTrue(c4.equals(c4));
        assertFalse(c5.equals(c4));
    }

    @Test
    public void compareToTest() {
        c1 = new ComplexNumber(4, 0);

        double c1Abs = complexAbs(c1);
        double c2Abs = complexAbs(c2);
        double c3Abs = complexAbs(c3);
        double c4Abs = complexAbs(c4);
        double c5Abs = complexAbs(c5);

        assertTrue((int)(c1Abs - c2Abs) == c1.compareTo(c2));
        assertTrue((int)(c1Abs - c3Abs) == c1.compareTo(c3));
        assertTrue((int)(c2Abs - c4Abs) == c2.compareTo(c4));
        assertTrue((int)(c3Abs - c1Abs) == c3.compareTo(c1));
        assertTrue((int)(c5Abs - c3Abs) == c5.compareTo(c3));
    }

    private double complexAbs(ComplexNumber z){
        return Math.sqrt(Math.pow(z.getReal(), 2) + Math.pow(z.getImaginary(), 2));
    }

    @Test
    public void toStringTest() {
        c1 = new ComplexNumber(4, 0);

        String c1String = "4.0+0.0i";
        String c2String = "0.0+0.0i";
        String c3String = "-5.4554+15956.45i";
        String c4String = "44444.0-8954.546i";
        String c5String = "-1.515151515E9+5456.14i";

        assertEquals(c1String, c1.toString());
        assertEquals(c2String, c2.toString());
        assertEquals(c3String, c3.toString());
        assertEquals(c4String, c4.toString());
        assertEquals(c5String, c5.toString());
    }

    @Test
    public void parseTest() {
        c1 = new ComplexNumber(4, 0);

        String c1String = "4.0+0.0i";
        String c2String = "0.0+0.0i";
        String c3String = "-5.4554+15956.45i";
        String c4String = "44444.0-8954.546i";
        String c5String = "-151515.0+5456.14i";

        ComplexNumber c1Parse = ComplexNumber.parse(c1String);
        ComplexNumber c2Parse = ComplexNumber.parse(c2String);
        ComplexNumber c3Parse = ComplexNumber.parse(c3String);
        ComplexNumber c4Parse = ComplexNumber.parse(c4String);
        ComplexNumber c5Parse = ComplexNumber.parse(c5String);

        assertEquals(c1String, c1Parse.toString());
        assertEquals(c2String, c2Parse.toString());
        assertEquals(c3String, c3Parse.toString());
        assertEquals(c4String, c4Parse.toString());
        assertEquals(c5String, c5Parse.toString());
    }

    @Test
    public void hashCodeTest() {
        c1 = new ComplexNumber(4, 0);

        assertEquals(c1.hashCode(), c1.hashCode());
        assertEquals(c2.hashCode(), c2.hashCode());
        assertEquals(c3.hashCode(), c3.hashCode());
        assertEquals(c4.hashCode(), c4.hashCode());
        assertEquals(c5.hashCode(), c5.hashCode());

        assertNotEquals(c1.hashCode(), c2.hashCode());
        assertNotEquals(c1.hashCode(), c3.hashCode());
        assertNotEquals(c1.hashCode(), c4.hashCode());
        assertNotEquals(c1.hashCode(), c5.hashCode());

        assertNotEquals(c2.hashCode(), c3.hashCode());
        assertNotEquals(c2.hashCode(), c4.hashCode());
        assertNotEquals(c2.hashCode(), c5.hashCode());

        assertNotEquals(c3.hashCode(), c4.hashCode());
        assertNotEquals(c3.hashCode(), c5.hashCode());

        assertNotEquals(c4.hashCode(), c5.hashCode());
    }
}


public class FooReference<T> {
	
	private T foo;
	
	public FooReference(T foo) {
        this.foo = foo;
    }
    
    public T getFoo() {
        return foo;
    }
    
    public void setFoo(T foo) {
        this.foo = foo;
    }
    
    public void display() {
        System.out.println("foo is: " + foo);
    }
}

import java.util.List;
import java.util.ArrayList;
import java.util.Set;

public class Main <T> {

//	static List<T> list;	
	
	List rawList;
	List<?> listOfAnyType;
	List<Object> listOfObject = new ArrayList<Object>();
	List<String> listOfString = new ArrayList<String>();
	List<Integer> listOfInteger = new ArrayList<Integer>();
	

	{
		listOfAnyType = rawList;
		rawList = listOfAnyType;
		rawList = listOfString;
		rawList = listOfInteger;
		listOfAnyType = listOfString;
		listOfAnyType = listOfInteger;
//		listOfObject = (List<Object>)listOfString;
	}

	
	public static void main(String[] args){
//		FooReference<Integer> integerFoo = new FooReference<>(123);
//		FooReference<String> stringFoo = new FooReference<>("foo");
//		FooReference<Boolean> booleanFoo = new FooReference<>(true);
//		
//		System.out.println("integerFoo value before set: " + integerFoo.getFoo());
//		System.out.println("stringFoo value before set: " + stringFoo.getFoo());
//		System.out.println("booleanFoo value before set: " + booleanFoo.getFoo());
//		
//		integerFoo.setFoo(12345);
//		stringFoo.setFoo("set foo");
//		booleanFoo.setFoo(false);
//		
//		System.out.println("integerFoo value after set: " + integerFoo.getFoo());
//		System.out.println("stringFoo value after set: " + stringFoo.getFoo());
//		System.out.println("booleanFoo value after set: " + booleanFoo.getFoo());
//		
//		System.out.println("Runtime classes are:");
//		System.out.println("inside integerFoo, foo class is: " + integerFoo.getFoo().getClass().getName());
//		System.out.println("inside stringFoo, foo class is: " + stringFoo.getFoo().getClass().getName());
//		System.out.println("inside booleanFoo, foo class is: " + booleanFoo.getFoo().getClass().getName());


//		List<Object> objectList;
//		List<String> stringList;
//		objectList = stringList;


	}
	
	
//	public <T> T foo(List<T> arg) {
//		return new T();
//	}

	
//	public class Example {
//		public void print(Set<String> strSet){}
//		public void print(Set<Integer> intSet){}
//	}
}

package calc;

public class Calculator {
	private int result =0;

	public void clear() {
		result = 0;		
	}
	
	public int getResult() {
		return result;
	}

	public void add(int i) {
		result += i;	
	}

	public void subtract(int i) {
		result -= i;		
	}

	public void divide(int i) {
		result /= i;
	}
	
	public void multiply(int i) {
		result *= i;
	}

}

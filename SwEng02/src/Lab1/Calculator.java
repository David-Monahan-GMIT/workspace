package Lab1;

public class Calculator {
	
	/**
	 * A method to take two numbers and multiply them
	 * @param x	The first number to be multiplied
	 * @param y The second number to be multiplied
	 * @return The product of the two paramaters
	 */
	public static int multiply(int x, int y) {
		return x*y;
	}
	
	/**
	 * A method to check if a passed integer is positive
	 * @param x The number being checked
	 * @return True if the number is positive, False otherwise
	 */
	public static boolean isPositive(int x) {
		if (x > 0) {
			return true;
		} else {
			return false;
		}
	}
	
	/**
	 * Reverse the letters of a string
	 * @author Dave
	 * @param rev The string to be reversed
	 * @return the reversed String
	 * @throws @NullPointerException of the string is null
	 */
	public static String reverseString(String rev) {
		return rev;
	}

}

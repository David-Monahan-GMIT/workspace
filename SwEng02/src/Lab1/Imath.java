package Lab1;

public final class Imath {

	public static void main(String[] args) {
		System.out.println(isqrt(144));

	}
	
	// returns an integer approximation of the sqrt of x
	public static int isqrt(int x) {
		int guess =1;
		while(guess * guess < x) {
			guess++;
		}
		return guess;
	}
}

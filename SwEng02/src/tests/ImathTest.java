package tests;

import static org.junit.Assert.*;

import org.junit.Test;
import java.lang.Math;

import Lab1.Imath;

public class ImathTest {

	@Test
	public void test() {
		for(int i =1; i < 100; i++) {
			assertEquals(Math.sqrt(i), Imath.isqrt(i));
		}
	}

}

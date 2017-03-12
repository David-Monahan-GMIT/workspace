package tests;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import Lab1.Calculator;

public class ArithmeticTest {

	@Before
	public void setUp() throws Exception {
		Calculator calc = new Calculator();
		System.out.println("setUp() was called");
	}

	@After
	public void tearDown() throws Exception {
		System.out.println("tearDown() was called");
	}

	@Test
	public void testMultiply() {
		assertEquals(4, Calculator.multiply(2,2));
		assertEquals(-15, Calculator.multiply(3,-5));
	}
	
	@Test
	public void testIsPositive() {
		assertTrue(Calculator.isPositive(5));
		assertFalse(Calculator.isPositive(-5));
		assertFalse(Calculator.isPositive(0));
	}

}

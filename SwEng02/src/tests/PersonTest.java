package tests;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class PersonTest {

	@Before
	public void sayItBefore() {
		System.out.println("I run *BEFORE EVERY TEST* ");
	}
	@After
	public void sayItAfter() {
		System.out.println("I run *AFTER EVERY TEST* ");
	}
	@Test
	public void test() {
		String s = new String("good");
		assertEquals("good", s.toString());
	}
	@Test
	public void test2() {
		fail("Not yet implemented");
	}

}

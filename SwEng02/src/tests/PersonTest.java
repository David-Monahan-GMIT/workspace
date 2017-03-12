package tests;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import Lab1.Person;

public class PersonTest {
	Person p;

	@Before
	public void sayItBefore() {
		System.out.println("I run *BEFORE EVERY TEST* ");
		p = new Person();
	}
	@After
	public void sayItAfter() {
		System.out.println("I run *AFTER EVERY TEST* ");
	}
	@Test
	public void test() {
		String s = new String("John Doe");
		assertEquals(p.getName(), s.toString());
		assertEquals(p.getAge(), 0);
		assertTrue(p instanceof Person);
		assertTrue(p.getGender());
	}
	@Test
	public void test2() {
		p.setName("Dave");
		p.setAge(29);
		assertEquals(p.getName(), "Dave");
		assertEquals(p.getAge(), 29);
	}
	@Test
	public void test3() {
		p = new Person("Tom Jones", 23);		
		assertEquals(p.getName(), "Tom Jones");
		assertEquals(p.getAge(), 23);
	}

}

/**
 * David Monahan
 * Junit Assignment
 * Test to check all the various classes that implement the Instrument interface
 * And their sublcasses. This test will check for instance types and ensure they
 * are all what they should be and test their methods to ensure they are behaving
 * as is expected for their class/subclass.
 * Coverage: 100%
 */

package tests;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import classes.Brass;
import classes.Instrument;
import classes.Percussion;
import classes.Stringed;
import classes.Wind;
import classes.Woodwind;

public class InstrumentTest {
	
	Instrument instrument;

	@Before
	public void setUp() throws Exception {
	}

	@After
	public void tearDown() throws Exception {
	}

	@Test
	public void test1() {
		System.out.println("Test Wind");
		
		instrument = new Wind();
		assertTrue(instrument instanceof Wind);
		assertFalse(instrument instanceof Brass);
		assertFalse(instrument instanceof Percussion);
		assertEquals(instrument.What(), "Wind");
		assertEquals(0, instrument.getPlayCount());
		instrument.play();
		assertEquals(1, instrument.getPlayCount());
		instrument.adjust();
		assertEquals(0, instrument.getPlayCount());
		
		instrument = new Woodwind();
		assertTrue(instrument instanceof Wind);
		assertFalse(instrument instanceof Brass);
		assertFalse(instrument instanceof Percussion);
		assertEquals("Woodwind", instrument.What());
		assertEquals(0, instrument.getPlayCount());
		instrument.play();
		assertEquals(2, instrument.getPlayCount());
		instrument.adjust();
		assertEquals(0, instrument.getPlayCount());
		
		instrument = new Brass();
		assertTrue(instrument instanceof Wind);
		assertTrue(instrument instanceof Brass);
		assertFalse(instrument instanceof Percussion);
		assertEquals("Wind", instrument.What());
		assertEquals(0, instrument.getPlayCount());
		instrument.play();
		assertEquals(3, instrument.getPlayCount());
		instrument.adjust();
		assertEquals(0, instrument.getPlayCount());
		
		assertTrue(instrument instanceof Instrument);
	}
	
	@Test
	public void test2() {
		System.out.println("Test Stringed");
		instrument = new Stringed();
		assertTrue(instrument instanceof Stringed);
		assertFalse(instrument instanceof Brass);
		assertFalse(instrument instanceof Percussion);
		assertEquals(instrument.What(), "Stringed");
		
		assertEquals(0, instrument.getPlayCount());
		instrument.play();
		assertEquals(1, instrument.getPlayCount());
		instrument.adjust();
		assertEquals(0, instrument.getPlayCount());
	}
	
	@Test
	public void test3() {
		System.out.println("Test Percussion");
		instrument = new Percussion();
		assertTrue(instrument instanceof Percussion);
		assertFalse(instrument instanceof Brass);
		assertFalse(instrument instanceof Stringed);
		assertEquals(instrument.What(), "Percussion");
		
		assertEquals(0, instrument.getPlayCount());
		instrument.play();
		assertEquals(1, instrument.getPlayCount());
		instrument.adjust();
		assertEquals(0, instrument.getPlayCount());
	}

}

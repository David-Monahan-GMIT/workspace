
/**
 * David Monahan Junit Test Assignment
 * 03/03/2017
 * This Junit test will test the Card class as thoroughly as possible.
 * This test functions by mimicing the behaviour of the the Class under test
 * and seeing does it's responses still match up.
 * Coverage at 97.2%
 */
package tests;

import static org.junit.Assert.*;

import java.util.ArrayList;
import java.util.List;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import classes.Card;

public class CardTest {

	Card testCard;
	String[] suits = {"Spades","Hearts", "Diamonds", "Clubs", "??"};
	String[] cards = {"","Ace", "2","3","4","5","6","7","8","9","10","Jack","Queen","King","??"};

	
	@Before
	public void setUp() throws Exception {
		System.out.println("I run before every test");
		testCard = null; // clear out any values before each test
		
	}

	@After
	public void tearDown() throws Exception {
		System.out.println("I run after every test");
	}

	@Test
	public void test1() {
		System.out.println("Testing Constructor");
		for(int i=0; i<4; i++) {
			testCard = new Card(1,i);
			assertEquals(i, testCard.getSuit()); 
		}
		for(int i=1; i<=13; i++) {
			testCard = new Card(i,1);
			assertEquals(i, testCard.getValue()); 
		}
	}
	
	@Test
	public void test2() {
		System.out.println("Testing Getters");
		for(int i=0; i<5; i++) {
			testCard = new Card(1,i);
			assertEquals(suits[i], testCard.getSuitAsString()); 
		}
		for(int i=1; i<=13; i++) {
			testCard = new Card(i,1);
			assertEquals(cards[i], testCard.getValueAsString()); 
		}
	}
	
	@Test
	public void test3() {
		System.out.println("Testing toString()");
		for(int i=0; i<4; i++) {
			for(int j=1; j<=13; j++) {
				testCard = new Card(j,i);
				//System.out.println(testCard.toString() + " : " + (cards[j] + " of " + suits[i]));
				assertEquals(testCard.toString(), (cards[j] + " of " + suits[i]));
			}
		}
	}

}

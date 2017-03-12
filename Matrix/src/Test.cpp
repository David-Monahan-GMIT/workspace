/*
 * Test.c

 *
 *  Created on: 31 Jan 2017
 *      Author: Dave
 */
#include <iostream>
#include <string>
#include "Matrix.h"

void testConstructors() {
	Matrix m1; // empty matrix default constructor
	Matrix m2(2.2);
	Matrix m3(3,5);
	Matrix m4(m3);

	std::cout << "Matrix 2= " << std::endl << m2;
	std::cout << "Matrix 2 element at 5,5 = " << m2.getElement(5,5) << std::endl;

	std::cout << "Matrix 3 (5x5)= " << std::endl << m3;
	std::cout << "Matrix 3 element at 2,2 = " << m3.getElement(2,2) << std::endl;

	std::cout << "Matrix 4 is a copy of Matrix 3(5x5)= " << std::endl << m4;
	std::cout << "Matrix 4 element at 2,2 = " << m4.getElement(2,2) << std::endl;

	m1 = m4;

	std::cout << "Matrix 1 = " << std::endl << m1;
	std::cout << "Matrix 1 element at 2,2 = " << m1.getElement(2,2) << std::endl;
	std::cout << "**************************************************************" << std::endl;
	std::cout << "END TEST 1 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
}
void testAssignment() {

	Matrix m1(6,6);
	Matrix m2(5,5);
	std::cout << "Matrix 1 = " << std::endl << m1;
	std::cout << "Matrix 1 element at 3,3 = " << m1.getElement(3,3) << std::endl;

	std::cout << "Matrix 2 (5x5)= " << std::endl << m2;
	std::cout << "Matrix 2 element at 3,3 = " << m2.getElement(3,3) << std::endl;

	m1 = m2;

	std::cout << "Matrix 1 = " << std::endl << m1;
	std::cout << "Matrix 1 element at 3,3 = " << m1.getElement(3,3) << std::endl;

	std::cout << "**************************************************************" << std::endl;
	std::cout << "END TEST 2 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
}

void testOperatorsPlusMinusAssignment() {
	// Make matrices
	Matrix m1(5), m2(3);
	std::cout << "Matrix 1 = " << std::endl << m1;
	std::cout << "Matrix 2 = " << std::endl << m2;
	// check adding
	m1+=m2;
	std::cout << "Matrix 1 = " << std::endl << m1;
	// check subtracting
	m2-=m1;
	std::cout << "Matrix 2 = " << std::endl << m2;
	// Check different sizes
	Matrix m3(5,5);
	m2+=m3;
	std::cout << "Matrix 2 = " << std::endl << m2;

	std::cout << "**************************************************************" << std::endl;
	std::cout << "END TEST 3 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
}
void testOperatorsBool() {
	// Make Matrices
	Matrix m1(4), m2(4);
	std::cout << "Matrix 1 = " << std::endl << m1;
	std::cout << "Matrix 2 = " << std::endl << m2;
	std::cout << "Are they equal: " << (m1==m2) << std::endl;
	std::cout << "Are they not equal: " << (m1!=m2) << std::endl;

	Matrix m3(10,10);
	std::cout << "Matrix 1 = " << std::endl << m1;
	std::cout << "Matrix 3 = " << std::endl << m3;
	std::cout << "Are they equal: " << (m1==m3) << std::endl;
	std::cout << "Are they not equal: " << (m1!=m3) << std::endl;

	std::cout << "**************************************************************" << std::endl;
	std::cout << "END TEST 4 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
}

void testOperatorsPlusMinus() {

	// Make matrices
	Matrix m1(5), m2(6);
	Matrix m3;
	std::cout << "Matrix 1 = " << std::endl << m1;
	std::cout << "Matrix 2 = " << std::endl << m2;

	// check adding
	std::cout << "Matrices added = " << std::endl << m1 + m2;

	// check subtracting
	std::cout << "Matrices subtracted = " << std::endl << m2 - m1;

	// Test assignment
	m3 = m2 = m1;
	std::cout << "Assignment m3 = m2 = m1 : " << std::endl << m3;

	// Test adding Assignment
	Matrix m4;
	m4 = m1 + m2;
	std::cout << "Assignment m4 = m1 + m2 : " << std::endl << m4;
	std::cout << "**************************************************************" << std::endl;
	std::cout << "END TEST 5 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
}

void testMultiplication() {
	Matrix m1(4,2), m2(2,3);
	Matrix m3;
	std::cout << "Matrix 1 = " << std::endl << m1;
	std::cout << "Matrix 2 = " << std::endl << m2;
	m3 = m1*m2;
	std::cout << "Multiplication m3 = m1 * m2 : " << std::endl << m3;

	std::cout << "**************************************************************" << std::endl;
	std::cout << "END TEST 6 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;

}

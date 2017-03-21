/*
 * Test.h
 *
 *  Created on: 31 Jan 2017
 *      Author: Dave
 */

#ifndef SRC_TEST_H_
#define SRC_TEST_H_

#include <iostream>
#include <string>
#include <stdlib.h>
#include "Matrix.h"

template <class T>
void testConstructors() {
	Matrix<T> m1; // empty matrix default constructor
	Matrix<T> m2(2.2);
	Matrix<T> m3(3,5);
	Matrix<T> m4(m3);

	std::cout << "Matrix 2= " << std::endl << m2;
	std::cout << "Matrix 2 element at 5,5 = " << m2.getElement(5,5) << std::endl;

	std::cout << "Matrix 3 (5x5)= " << std::endl << m3;
	std::cout << "Matrix 3 element at 2,2 = " << m3.getElement(2,2) << std::endl;

	std::cout << "Matrix 4 is a copy of Matrix 3(5x5)= " << std::endl << m4;
	std::cout << "Matrix 4 element at 2,2 = " << m4.getElement(2,2) << std::endl;

	m1 = m4;

	std::cout << "Matrix 1 = " << std::endl << m1;
	std::cout << "Matrix 1 element at 2,2 = " << m1.getElement(2,2) << std::endl;

	std::cout << "Number of matrices : " << m1.getMatrixCnt() << std::endl;
	std::cout << "**************************************************************" << std::endl;
	std::cout << "END TEST 1 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
}

template <class T>
void testAssignment() {

	Matrix<T> m1(6,6);
	Matrix<T> m2(5,5);
	std::cout << "Matrix 1 = " << std::endl << m1;
	std::cout << "Matrix 1 element at 3,3 = " << m1.getElement(3,3) << std::endl;

	std::cout << "Matrix 2 (5x5)= " << std::endl << m2;
	std::cout << "Matrix 2 element at 3,3 = " << m2.getElement(3,3) << std::endl;

	m1 = m2;

	std::cout << "Matrix 1 = " << std::endl << m1;
	std::cout << "Matrix 1 element at 3,3 = " << m1.getElement(3,3) << std::endl;

	std::cout << "Number of matrices : " << m1.getMatrixCnt() << std::endl;
	std::cout << "**************************************************************" << std::endl;
	std::cout << "END TEST 2 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
}

template <class T>
void testOperatorsPlusMinusAssignment() {
	// Make matrices
	Matrix<T> m1(5), m2(3);
	std::cout << "Matrix 1 = " << std::endl << m1;
	std::cout << "Matrix 2 = " << std::endl << m2;
	// check adding
	m1+=m2;
	std::cout << "Matrix 1 = " << std::endl << m1;
	// check subtracting
	m2-=m1;
	std::cout << "Matrix 2 = " << std::endl << m2;
	// Check different sizes
	Matrix<T> m3(5,5);
	m2+=m3;
	std::cout << "Matrix 2 = " << std::endl << m2;

	std::cout << "Number of matrices : " << m1.getMatrixCnt() << std::endl;
	std::cout << "**************************************************************" << std::endl;
	std::cout << "END TEST 3 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
}

template <class T>
void testOperatorsBool() {
	// Make Matrices
	Matrix<T> m1(4), m2(4);
	std::cout << "Matrix 1 = " << std::endl << m1;
	std::cout << "Matrix 2 = " << std::endl << m2;
	std::cout << "Are they equal: " << (m1==m2) << std::endl;
	std::cout << "Are they not equal: " << (m1!=m2) << std::endl;

	Matrix<T> m3(10,10);
	std::cout << "Matrix 1 = " << std::endl << m1;
	std::cout << "Matrix 3 = " << std::endl << m3;
	std::cout << "Are they equal: " << (m1==m3) << std::endl;
	std::cout << "Are they not equal: " << (m1!=m3) << std::endl;

	std::cout << "Number of matrices : " << m1.getMatrixCnt() << std::endl;
	std::cout << "**************************************************************" << std::endl;
	std::cout << "END TEST 4 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
}

template <class T>
void testOperatorsPlusMinus() {

	// Make matrices
	Matrix<T> m1(5), m2(6);
	Matrix<T> m3;
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
	Matrix<T> m4;
	m4 = m1 + m2;
	std::cout << "Assignment m4 = m1 + m2 : " << std::endl << m4;

	std::cout << "Number of matrices : " << m1.getMatrixCnt() << std::endl;
	std::cout << "**************************************************************" << std::endl;
	std::cout << "END TEST 5 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
}

template <class T>
void testMultiplication() {
	Matrix<T> m1(4,2), m2(2,3);
	Matrix<T> m3;
	std::cout << "Matrix 1 = " << std::endl << m1;
	std::cout << "Matrix 2 = " << std::endl << m2;
	m3 = m1*m2;
	std::cout << "Multiplication m3 = m1 * m2 : " << std::endl << m3;

	std::cout << "Number of matrices : " << m1.getMatrixCnt() << std::endl;
	std::cout << "**************************************************************" << std::endl;
	std::cout << "END TEST 6 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;

}
template <class T>
void testExceptions() {
	Matrix<T> m1(3,3), m2(4,4);
	std::cout << "Matrix 1 = " << std::endl << m1;
	std::cout << "Matrix 2 = " << std::endl << m2;
	std::cout << "Expect out of range:" << std::endl;
	m1.getElement(4,4);
	std::cout << "Expect out of range:" << std::endl;
	m2.setElement(5,5,1.1);
	std::cout << "**************************************************************" << std::endl;
	std::cout << "END TEST 7 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;

}

template <class T>
void testTemplate() {
	Matrix<T> m1(4,3);

	unsigned int row = m1.getRows();
	unsigned int col = m1.getCols();

	std::cout << "Matrix 1 size: " << row << "x" << col << std::endl;
	std::cout << "Matrix 1 = " << std::endl << m1;

	std::cout << "**************************************************************" << std::endl;
	std::cout << "END TEST 8 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
}

template <class T>
void TestCaseMenu(int argc, char **argv) {

	void (*testFunctions[])() = {
			testConstructors<T>,
			testAssignment<T>,
			testOperatorsPlusMinusAssignment<T>,
			testOperatorsBool<T>,
			testOperatorsPlusMinus<T>,
			testMultiplication<T>,
			testExceptions<T>,
			testTemplate<T>
		};

	// Divide the number of bytes in the array by the standard size of a function pointer
	// This is better than trying to work out the value manually as it will scale with 32 or 64 bit systems
	const int nTests =  sizeof(testFunctions)/sizeof(void*);

	for(int i=0; i<nTests; i++) {
		int test = atoi(*(argv + i));
		(*testFunctions[test])();
	}
}


#endif /* SRC_TEST_H_ */

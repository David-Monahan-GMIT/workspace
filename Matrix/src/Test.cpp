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
	Matrix m1;
	Matrix m2(2.2);
	Matrix m3(5,5);
	Matrix m4(m3);

	std::cout << "Matrix 1 = " << std::endl << m1;
	std::cout << "Matrix 1 element at 3,3 = " << m1.getElement(3,3) << std::endl;


	std::cout << "Matrix 2= " << std::endl << m2;
	std::cout << "Matrix 2 element at 5,5 = " << m2.getElement(5,5) << std::endl;

	std::cout << "Matrix 3 (5x5)= " << std::endl << m3;
	std::cout << "Matrix 3 element at 2,2 = " << m3.getElement(2,2) << std::endl;

	std::cout << "Matrix 4 is a copy of Matrix 3(5x5)= " << std::endl << m4;
	std::cout << "Matrix 4 element at 2,2 = " << m4.getElement(2,2) << std::endl;

	m1 = m4;

	std::cout << "Matrix 1 = " << std::endl << m1;
	std::cout << "Matrix 1 element at 3,3 = " << m1.getElement(3,3) << std::endl;
}
void testAssignment() {

	Matrix m1;
	Matrix m2(5,5);
	std::cout << "Matrix 1 = " << std::endl << m1;
	std::cout << "Matrix 1 element at 3,3 = " << m1.getElement(3,3) << std::endl;

	std::cout << "Matrix 2 (5x5)= " << std::endl << m2;
	std::cout << "Matrix 2 element at 3,3 = " << m2.getElement(3,3) << std::endl;

	m1 = m2;

	std::cout << "Matrix 1 = " << std::endl << m1;
	std::cout << "Matrix 1 element at 3,3 = " << m1.getElement(3,3) << std::endl;
}






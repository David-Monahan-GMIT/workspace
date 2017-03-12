/*
 * Main.cpp
 *
 *  Created on: 24 Jan 2017
 *      Author: Dave
 */
#include <iostream>
#include <string>
#include "Matrix.h"
#include "Test.h"

int main(int argc, char *argv[]) {

	testConstructors();
	testAssignment();
	testOperatorsPlusMinusAssignment();
	testOperatorsBool();
	testOperatorsPlusMinus();
	testMultiplication();

	return 0;
}

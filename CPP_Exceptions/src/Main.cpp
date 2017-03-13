/*
 * Main.cpp
 *
 *  Created on: 7 Mar 2017
 *      Author: Dave
 */

#include "TestExceptions.h"
#include "ExceptionSLTest.h"

int main(int argv, char *args[]) {
	//TestExceptions();
	TestBadAlloc();
	TestInvalidArgumentInSqrt();
	TestOutOfRangeError();

	return 0;
}




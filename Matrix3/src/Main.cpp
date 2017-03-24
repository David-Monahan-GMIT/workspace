/*
 * Main.cpp
 *
 *  Created on: 24 Jan 2017
 *      Author: Dave
 */
#include <iostream>
#include <string>
#include "Test.h"


int main(int argc, char *argv[]) {

	CallTestFunction<double>(argc,argv);
	CallTestFunction<int>(argc,argv);
	CallTestFunction<float>(argc,argv);
	return 0;
}

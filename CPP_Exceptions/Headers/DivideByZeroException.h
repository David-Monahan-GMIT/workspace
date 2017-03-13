/*

`..
`..   `..     `..        `..
`..            `..        `..
`..       `... `.....`... `.....
`..            `..        `..
`..   `..     `..        `..
`....

Michelle Lynch
2017
*/

#ifndef DIVIDEBYZEROEXCEPTION_H_INCLUDED
#define DIVIDEBYZEROEXCEPTION_H_INCLUDED

#include<iostream>

using namespace std;

class DivideByZeroException
{
private:
	const char *message;	                          // Message

public:
	DivideByZeroException()
		: message("Attempted to divide by zero") {}   // Constructor
	const char *What() const { return message; }      // What to do
};

#endif

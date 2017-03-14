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

#ifndef NANEXCEPTION_H_INCLUDED
#define NANEXCEPTION_H_INCLUDED

using namespace std;

// Class definition for handling a not-a-number exception
class NaNException {
private:
	const char *message;                        // Message
public:
	NaNException()                              // Constructor
        : message("Not a number") {};
	const char* What() const {return message; } // What to do
};


#endif // NANEXCEPTION_H_INCLUDED

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

#ifndef OUTOFRANGEEXCEPTION_H_INCLUDED
#define OUTOFRANGEEXCEPTION_H_INCLUDED

// Class definition for handling an out-of-range exception
class OutOfRangeException {
private:
	const char *message;                            // Message
public:
	OutOfRangeException() 
		: message("Out of range") {};				// Constructor
	const char* What() const {return message; }     // What to do

};

#endif // OUTOFRANGEEXCEPTION_H_INCLUDED

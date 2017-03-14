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

#include<iostream>
#include<string>
#include<climits>
#include"TestExceptions.h"
#include"NaNException.h"
#include"OutOfRangeException.h"

using namespace std;

void TestExceptions()
{
	int x = 0;
	bool done = 0;

	while (!done) {
		cout << "Enter a number between 0 and 23" << endl;
		cin >> x;

		if (x == -1)
			done = 1;
		try {
			if (cin.fail())
				throw NaNException();
			if ((x < 0) || (x > 23))
				throw OutOfRangeException();
		}
		catch (NaNException& ex) {
			cout << "Exception: " << ex.What() << endl;
		}

		catch (OutOfRangeException& ex) {
			cout << "Exception: " << ex.What() << endl;
		}

		catch (...) {
			cout << "Exception : Catch all";
		}

		cin.clear();
		cin.ignore(INT_MAX, '\n');
	} //end while(!done)
}

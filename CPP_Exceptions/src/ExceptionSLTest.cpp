/*

    `..
 `..   `..     `..        `..
`..            `..        `..
`..       `... `.....`... `.....
`..            `..        `..
 `..   `..     `..        `..
   `....

Michelle Lynch
2016
*/

#include<iostream>      // std::cout
#include<new>           // std::bad_alloc
#include<exception>     // std::exception
#include<stdexcept>     // std::invalid_argument, std::out_of_range
#include<cmath>			// sqrt function
#include"ExceptionSLTest.h"



// Function to demonstrate C++ standard bad_alloc exception
int TestBadAlloc()
{
    int counter = 0;

    while(1) {
        try {
            int* myarray = new int[5000000];
            counter += 1;
            std::cout << "Array " << counter << " allocated" << std::endl;
        }
        catch (std::bad_alloc& e) {
            std::cout << "Exception: " << e.what() << std::endl;
            return -1;
        }
    }

    return 0;
}

// Function to test a C++ standard exception
int TestInvalidArgumentInSqrt()
{
    try {
        // Function Sqrt may throw an exception
        double sqrt = Sqrt(-1.0);
    }
    catch (std::exception& e) {
        std::cout <<"Exception: "<< e.what() << std::endl;
    }

    return 0;
}

// Function to test a C++ standard out_of_range exception
int TestOutOfRangeError()
{
    try {
        if (100 > 10) {
            throw std::out_of_range("number out of range");
        }
    }
    catch (std::out_of_range & e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}

// Function to test a C++ invalid_argument exception
double Sqrt(double x)
{
    if(x < 0.0)
        throw std::invalid_argument("Invalid argument x in Sqrt()");

    return sqrt(x);
}

/*
*****************************************************************************
                        Assignment 1 - Milestone 2
Full Name  : Tyler Arcila-Rakoczy
Student ID#: 100391184
Email      : tarcila-rakoczy@myseneca.ca
Section    : NDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #1 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Receives a valid integer input from the user
int inputInt(void);

// Validates the integer input recieved from the user is greater than 0
int inputIntPositive(void);

// Validates the interger input recieved from the user is within the set range
int inputIntRange(int lowerBound, int upperBound);

// Receives a single character value from user input
char inputCharOption(const char charChosen[]);

// Returns multiple characters within the set limits
void inputCString(char* representingSymbol, int minChar, int maxChar);

// Returns an array of 10-character digits as a formatted phone number
void displayFormattedPhone(const char* representingSymbol);












// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H

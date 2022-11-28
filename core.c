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

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>


//
// Copy your work done from Milestone #1 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
// - Also copy the commented "sections" to help with finding functions quickly!
//

#include "core.h"
#include <string.h>

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// As demonstrated in the course notes: 
// https://intro2c.sdds.ca/D-Modularity/input-functions#clearing-the-buffer
// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Receives a valid integer input from the user
int inputInt(void)
{
    int value = 0;
    char newline = 'x';

    while (newline != '\n')
    {
        scanf("%d%c", &value, &newline);
        if (newline != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
        else if (newline == '\n')
        {
            return value;
        }
    }
    return value;
}

// Validates the integer input recieved from the user is greater than 0
int inputIntPositive(void)
{
    int value = 0;
    char newline = 'x';

    while (newline != '\n' || value <= 0)
    {
        scanf("%d%c", &value, &newline);
        if (newline != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
        else if (newline == '\n' && value <= 0)
        {
            printf("ERROR! Value must be > 0: ");
        }
        else if (newline == '\n' && value > 0)
        {
            return value;
        }
    }
    return value;
}

// Validates the interger input recieved from the user is within the set range
int inputIntRange(int lowerBound, int upperBound)
{
    int value = 0;
    char newline = 'x';

    while (newline != '\n' || (value < lowerBound || value > upperBound))
    {
        scanf("%d%c", &value, &newline);
        if (newline != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
        else if (newline == '\n' && (value < lowerBound || value > upperBound))
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
        }
        else if (newline == '\n' && (value >= lowerBound && value <= upperBound))
        {
            return value;
        }
    }
    return value;
}

// Receives a single character value from user input
char inputCharOption(const char charList[])
{
    char chosen = 'x';
    int listCheck = 0;

    while (chosen != charList[listCheck])
    {
        scanf(" %c", &chosen);
        for (listCheck = 0; charList[listCheck] != '\0'; listCheck++)
        {
            if (chosen == charList[listCheck])
            {
                return chosen;
            }
            else
            {
                continue;
            }
        }
        printf("ERROR: Character must be one of [");
        for (listCheck = 0; charList[listCheck] != '\0'; listCheck++)
        {
            printf("%c", charList[listCheck]);
        }
        printf("]: ");
    }
    return chosen;
}

// Returns multiple characters within the set limits
void inputCString(char* representingString, int minChar, int maxChar)
{
    int size = 0;
    int loop = 0;

    while (loop != 1)
    {
        scanf(" %[^\n]", representingString);
        size = strlen(representingString);

        if (minChar == maxChar)
        {
            if (size > maxChar || size < maxChar)
            {
                printf("ERROR: String length must be exactly %d chars: ", maxChar);
            }
            else if (size == maxChar)
            {
                return;
            }
        }
        else if (maxChar != minChar)
        {
            if (size > maxChar)
            {
                printf("ERROR: String length must be no more than %d chars: ", maxChar);
            }
            else if (size < minChar)
            {
                printf("ERROR: String length must be between %d and %d chars: ", minChar, maxChar);
            }
            else if (size <= maxChar && size >= minChar)
            {
                return;
            }
        }
    }
}


// Returns an array of 10 - character digits as a formatted phone number
void displayFormattedPhone(const char* representingSymbol)
{
    int numberCheck = 0;
    char validChar[10] = { '0','1', '2', '3', '4', '5', '6', '7', '8', '9' };
    char invalidChar[82] = { '`', '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+', '[', '{', ']', '}', '|', ';', ':', '"', ',', '<', '.', '>', '/', '?', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M' };
    int validCheck = 0;
    int phoneNumber = 0;

    if (representingSymbol == '\0')
    {
        printf("(___)___-____");
        return;
    }
    while (representingSymbol[numberCheck] > 0)
    {
        numberCheck++;
    }
    if (numberCheck > 10 || numberCheck < 10)
    {
        printf("(___)___-____");
    }

    else if (numberCheck == 10)
    {
        for (numberCheck = 0; numberCheck < 10; numberCheck++)
        {
            for (validCheck = 0; validCheck < 82; validCheck++)
            {
                if (representingSymbol[numberCheck] == invalidChar[validCheck])
                {
                    printf("(___)___-____");
                    return;
                }
                else
                {
                    continue;
                }
            }
        }
        printf("(");
        for (numberCheck = 0; numberCheck < 10; numberCheck++)
        {
            for (validCheck = 0; validCheck < 10; validCheck++)
            {
                if (validChar[validCheck] == representingSymbol[numberCheck])
                {
                    printf("%c", representingSymbol[numberCheck]);
                    phoneNumber++;
                    if (phoneNumber == 3)
                    {
                        printf(")");
                    }
                    else if (phoneNumber == 6)
                    {
                        printf("-");
                    }
                    else
                    {
                        continue;
                    }
                }
                else if (validChar[validCheck] != representingSymbol[numberCheck])
                {
                    continue;
                }
            }
        }
    }
    return;
}
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

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%.4s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%.4s)\n", patient->phone.description);
    }
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int display = 0;
    int records = 0;

    displayPatientTableHeader();
    for (display = 0; display < max; display++)
    {
        if (patient[display].patientNumber == 0)
        {
            continue;
        }
        else
        {
            printf("%05d %-15s ", patient[display].patientNumber,
                patient[display].name);
            displayFormattedPhone(patient[display].phone.number);
            printf(" (%s)\n", patient[display].phone.description);
            records++;  
        }
        if (records == 0)
        {
            printf("*** No records found ***\n");
        }
    }
    putchar('\n');
    return;
}



// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int selection = 0;
    int number = 0;


    do
    {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            searchPatientByPatientNumber(patient, max);
            suspend();
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            suspend();
            break;
        }
    } while (selection != 0);
    return;
}


// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int search = 0;
    int full = 0;
    int index = 0;

    for ( search = 0; search < max; search++)
    {
        if (patient[search].patientNumber == 0)
        {
            patient[search].patientNumber = nextPatientNumber(patient, max);
            inputPatient(&patient[search]);

            printf("*** New patient record added ***\n\n");
            break;
        }
        else
        {
            full++;
        }
    }
    if (full == max)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    return;
}


// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int patientNumber = 0;
    int index = 0;

    printf("Enter the patient number: ");
    scanf("%d", &patientNumber);
    putchar('\n');
    index = findPatientIndexByPatientNum(patientNumber, patient, max);
    if (patientNumber == patient[index].patientNumber)
    {
        menuPatientEdit(&patient[index]);
    }
    else
    {
        printf("*** No records found ***\n");
    }
    return;
}


// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int patientNumber = 0;
    int index = 0;
    char selection = 0;

    printf("Enter the patient number: ");
    scanf("%d", &patientNumber);
    putchar('\n');
    index = findPatientIndexByPatientNum(patientNumber, patient, max);
    if (patientNumber == patient[index].patientNumber)
    {
        displayPatientData(&patient[index], FMT_FORM);
        putchar('\n');
        printf("Are you sure you want to remove this patient record? (y/n): ");
        scanf(" %c", &selection);
        switch (selection)
        {
        case 'y':
                *patient[index].name = '\0';
                patient[index].patientNumber = '\0';
                *patient[index].phone.description = '\0';
                *patient[index].phone.number = '\0';
                printf("Patient record has been removed!\n");
            break;
        case 'n':
            printf("Operation aborted.\n");
            break;
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n");
    }
    putchar('\n');
    clearInputBuffer();
    return;
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientNumber = 0;
    int index = 0;

    printf("Search by patient number: ");
    scanf("%d", &patientNumber);
    putchar('\n');
    index = findPatientIndexByPatientNum(patientNumber, patient, max);
    if (patientNumber == patient[index].patientNumber)
    {
        displayPatientData(&patient[index], FMT_FORM);
    }
    else
    {
        printf("*** No records found ***\n");
    }
    putchar('\n');
    clearInputBuffer();
    return;
}


// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char phoneNumber [PHONE_LEN];
    int search = 0;
    int records = 0;

    printf("Search by phone number: ");
    scanf(" %s", phoneNumber);
    putchar('\n');
    displayPatientTableHeader();
    for ( search = 0; search < max; search++)
    {
        if (phoneNumber == patient[search].phone.number)
        {
            displayPatientData(&patient[search], FMT_TABLE);
            records++;
            putchar('\n');
        }
        else if(phoneNumber != patient[search].phone.number)
        {
            printf("%s\n", phoneNumber);
            printf("%s\n", patient[search].phone.number);
            continue;

        }
    }
    if (records == 0)
    {
        printf("*** No records found ***\n");
    }
    clearInputBuffer();
    return;
}


// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int search = 0;
    int nextNum = 0;

    for ( search = 0; search < max; search++)
    {
        if (patient[search].patientNumber >= nextNum)
        {
            nextNum = patient[search].patientNumber + 1;
        }
        else
        {
            continue;
        }
    }
    return nextNum;
}


// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int search = 0;

    for (search = 0; search < max; search++)
    {
        patient[search].patientNumber;
            if (patient[search].patientNumber == patientNumber)
            {
                return search;
            }
            else
            {
                continue;
            }
    }
    return -1;
}



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    scanf("%[^\n]", patient->name);
    putchar('\n');
    inputPhoneData(&patient->phone);
    return;
}


// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int selection = 0;
    int input = 0;
    int next = 0;
    
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    selection = inputIntRange(1, 4);
    putchar('\n');
    switch (selection)
    {
    case 1:
        for ( input = 0; input < PHONE_DESC_LEN; input++)
        {
            switch (input)
            {
            case 0:
                phone->description[input] = 'C';
                break;
            case 1:
                phone->description[input] = 'E';
                break;
            case 2:
                phone->description[input] = 'L';
                break;
            case 3:
                phone->description[input] = 'L';
                break;
            }
        }  
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        scanf("%s", phone->number);
        putchar('\n');
        clearInputBuffer();
        break;
    case 2:
        for (input = 0; input < PHONE_DESC_LEN; input++)
        {
            switch (input)
            {
            case 0:
                phone->description[input] = 'H';
                break;
            case 1:
                phone->description[input] = 'O';
                break;
            case 2:
                phone->description[input] = 'M';
                break;
            case 3:
                phone->description[input] = 'E';
                break;
            }
        }
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        scanf("%s", phone->number);
        putchar('\n');
        clearInputBuffer();
        break;
    case 3:
        for (input = 0; input < PHONE_DESC_LEN; input++)
        {
            switch (input)
            {
            case 0:
                phone->description[input] = 'W';
                break;
            case 1:
                phone->description[input] = 'O';
                break;
            case 2:
                phone->description[input] = 'R';
                break;
            case 3:
                phone->description[input] = 'K';
                break;
            }
        }
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        scanf("%s", phone->number);
        putchar('\n');
        clearInputBuffer();
        break;
    case 4:
        for (input = 0; input < PHONE_DESC_LEN; input++)
        {
            switch (input)
            {
            case 0:
                phone->description[input] = 'T';
                break;
            case 1:
                phone->description[input] = 'B';
                break;
            case 2:
                phone->description[input] = 'D';
                break;
            case 3:
                break;
            }
        }
        break;
    }
    return;
}

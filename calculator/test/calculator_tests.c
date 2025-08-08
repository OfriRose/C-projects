/*
    Developer: Ofri Rozner
    Reviwer: Romi Kamin
    Date: 31/10/23
    calculator - test file
*/
#include <stdio.h>
#include "calculator.h"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

int main()
{
    const char *expression = "10 + 5";
    double result = 0;
    status_t status = Calculate(expression, &result);

    printf("TEST MATH OPERATIONS\n");
    printf("-----------------------------------\n");

    status = Calculate(expression, &result);
    if (result == 15)
    {
        printf(GREEN"Test (addition) \t\t\t\t\tPASSED!\n"RESET);
    }
    else
    {
        printf(RED"Test (addition) \t\t\tFAILED!\n"RESET);
    }

    expression = "10 - 5";
    status = Calculate(expression, &result);
    if (result == 5)
    {
        printf(GREEN"Test (subtraction) \t\t\t\t\tPASSED!\n"RESET);
    }
    else
    {
        printf(RED"Test (subtraction) \t\t\tFAILED!\n"RESET);
    }

    expression = "10 * 5";
    status = Calculate(expression, &result);
    if (result == 50)
    {
        printf(GREEN"Test (multi) \t\t\t\t\tPASSED!\n"RESET);
    }
    else
    {
        printf(RED"Test (multi) \t\tFAILED!\n"RESET);
    }

    expression = "10 / 5";
    status = Calculate(expression, &result);
    if (result == 2)
    {
        printf(GREEN"Test (Divide) \t\t\t\t\t\tPASSED!\n"RESET);
    }
    else
    {
        printf(RED"Test (Divide) \t\t\tFAILED!\n"RESET);
    }
    
    expression = " 4 + 2 + (1+1)- (2 + (2*3)/2 +52 - (2+ 2+ 2- (1+3 *4)))";
    status = Calculate(expression, &result);
    if (result == 4 + 2 + (1+1)- (2 + (2*3)/2 +52 - (2+ 2+ 2- (1+3 *4))))
    {
        printf(GREEN"Test (4 operation, space, multipy parenthesis) \t\tPASSED!\n"RESET);
    }
    else
    {
        printf(RED"Test \t\tFAILED!\n"RESET);
         printf("res = %d", (int)result);
    }
  
    return 0;
}
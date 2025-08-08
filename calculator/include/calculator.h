/*
    Developer: Ofri Rozner
    Reviwer: Romi Kamin
    Date: 31/10/23
    calculator - header file
*/
#ifndef __ILRD_OL149_H_CALCULATOR__
#define __ILRD_OL149_H_CALCULATOR__

/*
Description: a simple calculator able to perform 4 basic math operations, allows parentheses.
*/

typedef enum status
{
   SUCCESS,
   ALLOC_ERROR,
   SYNTAX_ERROR,
   MATH_ERROR
} status_t;

/**
 * @brief calculate a mathematical expression
 * @param str a math expression to be calculated
 * @param result a refrence to where the result will be stored
 * @return the calculation success status
 */
status_t Calculate(const char *str, double *result);


#endif /* __ILRD_OL149_H_CALCULATOR__ */

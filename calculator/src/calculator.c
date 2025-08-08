/*
    Developer: Ofri Rozner
    Reviwer: Romi Kamin
    Date: 31/10/23
    calculator - src file
*/

#include <stdlib.h>/*strtod */
#include <string.h>/*strlen */
#include <assert.h>/*assert */
#include <stdio.h>


#include "calculator.h"/*calculator API*/
#include "stack.h"/*stack memory API*/

#define ASCII_LENGTH 256

typedef enum
{
    WAITING_FOR_OPERANDS,
    WAITING_FOR_OPERATORS,
    ERROR
} state_t;

typedef enum
{
    EMPTY,
    OPEN_PAREN,
    ADD,
    SUB,
    MULT,
    DIV
} operators_t;

typedef enum
{
    LOW_PREC = 2,
    HIGH_PREC = 4
} precedence_t;

typedef struct calculator_s
{
    char **str;
    status_t status;
    stack_t *operands;
    stack_t *operators;
} calc_t;

typedef state_t (*calc_func_t)(calc_t *);
typedef state_t (*state_func_t)(calc_t *);

state_t (*StateLUT[2][256])(calc_t *) = {{NULL}, {NULL}};
state_t (*OperationLUT[6])(calc_t *) = {0};

/********************************** Function Declerations *********************************/
status_t Calculate(const char *expression, double *result);
static void InitOperationLUT();
static status_t CreateCalculator(calc_t *calc, const char *expression);
static void CalculatorDestory(calc_t *calc);
static state_t OPAdd(calc_t *calc);
static state_t OPSub(calc_t *calc);
static state_t OPDivide(calc_t *calc);
static state_t OPAdd(calc_t *calc);
static state_t OPMultipy(calc_t *calc);
static state_t Calc(calc_t *calc, precedence_t PRECEDENCE);
static state_t SpaceOperator(calc_t *calc);
static state_t NumParse(calc_t *calc);
static state_t PushOpenParen(calc_t *calc);
static state_t OperandError(calc_t *calc);
static state_t OperatorError(calc_t *calc);
static state_t CalcToOpenParen(calc_t *calc);
static state_t PushAddOp(calc_t *calc);
static state_t PushSubOp(calc_t *calc);
static state_t PushMultOp(calc_t *calc);
static state_t PushDivOp(calc_t *calc);
static state_t EndOfExpression(calc_t *calc);
static state_t SpaceOperand(calc_t *calc);
static void InitStateLUT();

/********************************** Implementation *********************************/

status_t Calculate(const char *expression, double *result)
{
    calc_t calc;
    state_t state = WAITING_FOR_OPERANDS;
    int ch = 0;
    status_t status = SUCCESS;

    assert(expression);
   
    InitStateLUT();
    InitOperationLUT();

    *result = 0;
    status = CreateCalculator(&calc, expression);

    while (ERROR != state && SUCCESS == status)
    {
        calc.status = status;
        calc.str = (char **)&expression;      
        ch = (int)**calc.str;
        state = StateLUT[state][ch](&calc);    
        status = calc.status;
    }

    *result = *(double *)StackPeek(calc.operands);
    CalculatorDestory(&calc);
    return (status);
}

/********************************** Service Function *********************************/

static status_t CreateCalculator(calc_t *calc, const char *expression)
{
    size_t operands_size = sizeof(double);
    size_t operators_size = sizeof(operators_t);
    size_t expression_length = strlen(expression);
    operators_t empty = EMPTY;

    calc->operands = StackCreate(expression_length, operands_size);
    if (NULL == calc->operands)
    {
        free(calc); 
        calc = NULL;
        return (ALLOC_ERROR);
    }

    calc->operators = StackCreate(expression_length, operators_size);
    if (NULL == calc->operators)
    {
        StackDestroy(calc->operands);
        free(calc);
        calc = NULL;
        return (ALLOC_ERROR);
    }

    calc->str = (char **)&expression;
    StackPush(calc->operators, &empty);
    calc->status = SUCCESS;

    return SUCCESS;
}

static void CalculatorDestory(calc_t *calc)
{
    StackDestroy(calc->operands);
    calc->operands = NULL;
    StackDestroy(calc->operators);
    calc->operators = NULL;
}

static state_t OPAdd(calc_t *calc)
{
    double num2 = *(double *)StackPeek(calc->operands);
    double num1 = 0.0;
    double result = 0.0;

    StackPop(calc->operands);
    StackPop(calc->operators);

    num1 = *(double *)StackPeek(calc->operands);
    StackPop(calc->operands);

    result = (num1 + num2);
    StackPush(calc->operands, &result);

    return (WAITING_FOR_OPERANDS);
}

static state_t OPSub(calc_t *calc)
{
    double num2 = *(double *)StackPeek(calc->operands);
    double num1 = 0;
    double result = 0;

    StackPop(calc->operands);
    StackPop(calc->operators);

    num1 = *(double *)StackPeek(calc->operands);
    StackPop(calc->operands);

    result = (num1 - num2);
    StackPush(calc->operands, &result);

    return (WAITING_FOR_OPERANDS);
}

static state_t OPMultipy(calc_t *calc)
{
    double num2 = *(double *)StackPeek(calc->operands);
    double num1 = 0;
    double result = 0;

    StackPop(calc->operands);
    StackPop(calc->operators);

    num1 = *(double *)StackPeek(calc->operands);
    StackPop(calc->operands);

    result = (num1 * num2);
    StackPush(calc->operands, &result);

    return (WAITING_FOR_OPERANDS);
}

static state_t OPDivide(calc_t *calc)
{
    double num2 = *(double *)StackPeek(calc->operands);
    double num1 = 0;
    double result = 0;

    StackPop(calc->operands);
    StackPop(calc->operators);

    num1 = *(double *)StackPeek(calc->operands);
    StackPop(calc->operands);

    while (0 == num2)
    {
        calc->status = MATH_ERROR;
        return (ERROR);
    }

    result = (num1 / num2);
    StackPush(calc->operands, &result);

    return (WAITING_FOR_OPERANDS);
}

static void InitOperationLUT()
{
    OperationLUT[0] = NULL; /*empty to fit table*/
    OperationLUT[1] = NULL; /*empty to fit table*/
    OperationLUT[2] = OPAdd;
    OperationLUT[3] = OPSub;
    OperationLUT[4] = OPMultipy;
    OperationLUT[5] = OPDivide;
}

static state_t Calc(calc_t *calc, precedence_t PRECEDENCE)
{
    state_t state = WAITING_FOR_OPERANDS;
    operators_t OP = EMPTY;

    while (((OP = (*(operators_t *)StackPeek(calc->operators))) >= (operators_t)PRECEDENCE)
                                                                      && (state != ERROR))
    {
        state = OperationLUT[OP](calc);
    }

    return (state);
}

static state_t SpaceOperator(calc_t *calc)
{
    while (**calc->str == ' ')
    {
        ++(*calc->str);
    }

    return WAITING_FOR_OPERATORS;
}

static state_t SpaceOperand(calc_t *calc)
{
    while (**calc->str == ' ')
    {
        ++(*calc->str);
    }

    return WAITING_FOR_OPERANDS;
}

static state_t NumParse(calc_t *calc)
{
    const char *expression = *calc->str;
    double data = 0;

    data = strtod(expression, calc->str);

    StackPush(calc->operands, &data);
    return WAITING_FOR_OPERATORS;
}

static state_t PushOpenParen(calc_t *calc)
{
    operators_t open_paren = OPEN_PAREN;

    StackPush(calc->operators, &open_paren);
    ++(*calc->str);

    return (WAITING_FOR_OPERANDS);
}

static state_t OperandError(calc_t *calc)
{
    calc->status = SYNTAX_ERROR;
    return (ERROR);
}

static state_t OperatorError(calc_t *calc)
{
    calc->status = SYNTAX_ERROR;
    return (ERROR);
}

static state_t CalcToOpenParen(calc_t *calc)
{
    state_t state = Calc(calc, LOW_PREC);
    state = WAITING_FOR_OPERATORS;

    StackPop(calc->operators);
    ++(*calc->str);

    return (state);
}

static state_t PushAddOp(calc_t *calc)
{
    state_t state = Calc(calc, LOW_PREC);
    operators_t op = ADD;

    StackPush(calc->operators, &op);
    ++(*calc->str);

    return (state);
}

static state_t PushSubOp(calc_t *calc)
{
    state_t state = Calc(calc, LOW_PREC);
    operators_t op = SUB;

    StackPush(calc->operators, &op);
    ++(*calc->str);

    return (state);
}

static state_t PushMultOp(calc_t *calc)
{
    state_t state = Calc(calc, HIGH_PREC);
    operators_t op = MULT;

    StackPush(calc->operators, &op);
    ++(*calc->str);

    return (state);
}

static state_t PushDivOp(calc_t *calc)
{
    state_t state = Calc(calc, HIGH_PREC);
    operators_t op = DIV;

    StackPush(calc->operators, &op);
    ++(*calc->str);

    return (state);
}

static state_t EndOfExpression(calc_t *calc)
{
    state_t state = Calc(calc, LOW_PREC);

    /*both conditions will result in SYNTAX ERROR, otherwise SUCCESS*/
    calc->status = (((MATH_ERROR != calc->status) + 
                            (EMPTY != (*(operators_t *)StackPeek(calc->operators)))))/10; 
    
    state = ERROR;

    return (state);
}

static void InitStateLUT()
{
    size_t i = 0;
    int valid_input[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                          '+', '-', '.', ' '};

    for (i = 0; i < ASCII_LENGTH; ++i)
    {
        StateLUT[WAITING_FOR_OPERANDS][i] = OperandError;
    }

    for (i = 0; i < sizeof(valid_input)/sizeof(valid_input[0]); ++i)
    {
        StateLUT[WAITING_FOR_OPERANDS][valid_input[i]] = NumParse;
    }

    StateLUT[WAITING_FOR_OPERANDS]['('] = PushOpenParen;
    StateLUT[WAITING_FOR_OPERANDS][' '] = SpaceOperand;

    for (i = 0; i < ASCII_LENGTH; ++i)
    {
        StateLUT[WAITING_FOR_OPERATORS][i] = OperatorError;
    }

    StateLUT[WAITING_FOR_OPERATORS][' '] = SpaceOperator;
    StateLUT[WAITING_FOR_OPERATORS][')'] = CalcToOpenParen;
    StateLUT[WAITING_FOR_OPERATORS]['*'] = PushMultOp;
    StateLUT[WAITING_FOR_OPERATORS]['+'] = PushAddOp;
    StateLUT[WAITING_FOR_OPERATORS]['-'] = PushSubOp;
    StateLUT[WAITING_FOR_OPERATORS]['/'] = PushDivOp;
    StateLUT[WAITING_FOR_OPERATORS]['\0'] = EndOfExpression;
}





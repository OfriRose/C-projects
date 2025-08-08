#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#define RED   "\x1B[31m" /*printf with red font*/
#define GREEN "\x1B[32m" /*printf with green font*/ 
#define RESET "\x1B[0m" /*resets to colorless printf*/

int Expected(int condition, const char *message);
void PrintProgressBar(int percentage);
void PrintResult(const char *test_name, int failures);


#endif /* TEST_UTIL_H */


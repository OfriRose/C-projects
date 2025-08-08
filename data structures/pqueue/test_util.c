#include <stdio.h>
#include <stdlib.h>

#include "test_util.h"

int Expected(int condition, const char *message) 
{
    if (!condition) 
    {
        fprintf(stderr, "Test failed: %s\n", message);
        return 1; 
    }

    return 0;
}

void PrintResult(const char *test_name, int failures) 
{
    if (failures == 0) {
        printf("%s: \033[32mPASSED\033[0m\n", test_name);
    } else {
        printf("%s: \033[31mFAILED\033[0m\n", test_name);
    }
}

void PrintProgressBar(int percentage) 
{
    int bar_length = 50;
    int num_chars = (percentage * bar_length) / 100;
    int i = 0; 

    printf("[");
    for (i = 0; i < bar_length; i++) {
        if (i < num_chars) {
            printf("=");
        } else {
            printf(" ");
        }
    }
    printf("] %3d%%\r\n", percentage);
    printf("passed\n");
    fflush(stdout); 
}



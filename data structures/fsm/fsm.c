#include <stdio.h>

typedef enum STATE {
ACCEPTED,
WAITING,
INVALID,
FIRST
} state_t;

static const int TRANSFORMATION[4][2] = {   {ACCEPTED, WAITING},
							   				{ACCEPTED, WAITING},
							   				{INVALID, INVALID}, 
							  			    {WAITING, INVALID}    };

int IsAccepted(char* str)
{
	state_t state = FIRST;
	
	while('\0' != *str)
	{
		state = TRANSFORMATION[state][*str - '0'];
		++str;
	}
	
	return (state == ACCEPTED);
}

int main()
{
	char *str1 = "01101010010";
	char *str2 = "100110";
	char *str3 = "00";
	char *str4 = "0";
	char *str5 = "011001";
	char *str6 = "010101000110010100110";
	int accpeted_tests = 0;
	int expected_success = 3;
	
	accpeted_tests += IsAccepted(str1);
	accpeted_tests += IsAccepted(str2);
	accpeted_tests += IsAccepted(str3);
	accpeted_tests += IsAccepted(str4);
	accpeted_tests += IsAccepted(str5);
	accpeted_tests += IsAccepted(str6);
	
	if (accpeted_tests == expected_success)
	{
		printf("\nALL TESTS PASSED\n");
	}
	
	return 0;
}
	


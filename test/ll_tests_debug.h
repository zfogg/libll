#include "../src/ll.h"


#define WHITE_CC "\e[0m"

#define GREEN_CC "\e[32m"

#define RED_CC   "\e[31m"


extern int LL_testResults;

void processTestResults         (const char* testName, int results);

nodePtr newTestLL               (int count);

LL_value_t randTestVal          ();

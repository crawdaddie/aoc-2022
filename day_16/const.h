#ifndef _CONST_H
#define _CONST_H
#define ALPHA_CHARS 26
#define TOTAL_TIME 30

#define TEST

#ifdef TEST
#define NUM_VALVES 10
#define INPUT "./test_input.txt"
#else
#define NUM_VALVES 63
#define INPUT "./input.txt"
#endif

#endif

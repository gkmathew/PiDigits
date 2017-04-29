#include <stdlib.h>
#include <math.h> 
#include <stdio.h>  

#include "BigInt.h"

const unsigned int NDIGITS_DEF = 200;

// Compute digits of Pi to any precision based on Machin's formula:
// pi = 4*(4 * arctan(1/5) - arctan(1/239))

// argument == number of decimal places (default : 100)
int main(int argc, char *argv[]) 
{
   unsigned int ndigits;
   if (argc > 1) {
       ndigits = atoi(argv[1]);
   } else {
       ndigits = NDIGITS_DEF;
   }

   BigInt term(ndigits), sum(ndigits), scratch(ndigits);
   sum = term.ArcTan(5, ndigits, scratch);
   sum = sum * 4;
		
   sum = (sum - term.ArcTan(239, ndigits, scratch));
   sum = sum * 4;

   sum.print(ndigits);
   return 0;
}

#include <math.h>   
#include <assert.h> 
#include <stdio.h>  
#include "BigInt.h"

BigInt::BigInt(unsigned int ndigits)
{
    digits_per_location = 4;
    radix = (unsigned long) pow(10, digits_per_location);
    locations = ndigits/digits_per_location + 3;
    arr = new unsigned long[locations];
    if (arr == 0) {
       printf("failed to allocate memory");
    }
}

BigInt::BigInt(const BigInt& b) 
{
    for (unsigned int i=0 ; i < locations; i++) {
        arr[i] = b.arr[i];
    }
}

BigInt::~BigInt() 
{
    delete [] arr;
}

BigInt& BigInt::operator= (const BigInt& b) 
{
    for (unsigned int i=0 ; i < locations; i++) {
        arr[i] = b.arr[i];
    }
    return *this;
}

BigInt& BigInt::operator+ (const BigInt& b) 
{
	unsigned long sum, carry;
   unsigned long *pp = this->arr + locations - 1; // last location
   unsigned long *qq = b.arr + locations - 1;     // last location
   carry = 0;

	for (unsigned long i=0; i < locations; i++) {
		sum = *pp + *qq + carry;
      if (sum > radix) {
         *pp = sum - radix;
		   carry = 1;
      } else {
		   *pp = sum;
		   carry = 0;
      }
      pp--;
      qq--;
   }

   if (carry > 0) {
      printf ("overflow in multiprecision addition");
   }

   return *this;
}

BigInt& BigInt::operator- (const BigInt& b) 
{
	unsigned long carry;
   unsigned long *pp = this->arr + locations -1;
   unsigned long *qq = b.arr + locations - 1;
   carry = 0;

	for (unsigned long i=0; i < locations; i++) {
      if (*pp < *qq + carry) {
         *pp = radix + *pp - *qq - carry;
         carry = 1;
      } else {
         *pp = *pp - *qq - carry;
         carry = 0;
      }
      pp--;
      qq--;
   }
   if (carry > 0) {
      printf ("overflow in multiprecision subtraction");
   }
   return *this;
}

void BigInt::print(unsigned int ndigits) const
{
       unsigned long temp = 1;
       unsigned long base = 1;
       unsigned long *a = arr;
       putchar('\n');
       for (unsigned long i=1; i <= ndigits + 1; i++) {  /* output in 80 column format */
                temp = (base == 1)? *a++ : temp;
                base = (base == 1)? radix/10: base/10;
                printf((i%100) ? "%d":"%d\n",temp/base);
                temp %= base;
       }
       putchar('\n');
}

BigInt& BigInt::ArcTan(unsigned int m, unsigned int ndigits, BigInt& term)
/* return arctan of (1/m) */
{
   unsigned long i, *p, j;
   unsigned int terms;
   terms = (int) (((double)locations * (double)digits_per_location * log(10.0))/(2.0* log((double)m)) + 1.0);
   
   printf("arctan(1/%d) computation: %d terms to be summed\n", m, terms);
   i = 1;
   p = this->arr;
   for (j=0; j<locations; j++) {
      *p++ = 0;
   }
   p = term.arr;
   *p++ = radix/10;
   for (j=1; j<locations; j++) {
      *p++ = 0;
   }
	term = term / m;
	for (j=0; j<terms; j++) {
      if ((j % 2) > 0) {
		     *this = *this - term;
      } else {
		     *this = *this + term;
      }
		term = term * i;
      i = i+2;
		term = term / i;
		term = term / m;
      term = term / m;
	}
   return *this;
}

// helper routines: To Do
// Use these to simplify the scalar mult/div routines below

// Multiply two 2 8-digit numbers
// Require: a, b < radix 
// Assure:  c, d < radix, c is the more significant part of the result
void mult(unsigned int a, unsigned int b, unsigned int* c, unsigned int* d)
{
}

// Divide 16 digit number by 8 digit number 
// Require: p, q, r < radix, p is the more significant part of the argument
//                           r is the divisor 
// Assure:  s, t < radix, s is the result and t is the remainder
void div(unsigned int p, unsigned int q, unsigned int r, unsigned int* s, unsigned int* t)
{
}


BigInt& BigInt::operator* (unsigned long n)  /* multiply by scalar */
// Assumption: 0 <= n < radix
{
   unsigned long i, temp, carry=0;
   unsigned long *pp = this->arr + locations - 1;
   for (i=0; i < locations; i++) {
      temp = n * (*pp) + carry;
      carry = temp/radix;
      *pp = temp % radix;
      pp--;
   }
   return *this;
}

BigInt& BigInt::operator/ (unsigned long n) /* divide by scalar */
// Assumption: 0 < n < radix
{
   unsigned long i, temp, carry=0;
   unsigned long *pp = this->arr;
   for (i=0; i < locations; i++) {
	temp = carry * radix + *pp;
	*pp = temp/n;
	carry = temp % n;
        pp++;
   }
   return(*this);
}

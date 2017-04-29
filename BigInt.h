#ifndef __BIGINT_H
#define __BIGINT_H

class BigInt {
public:
   BigInt(unsigned int ndigits); // specify number of decimal digits of precision desired
   BigInt(const BigInt&);
   ~BigInt();
   BigInt& operator= (const BigInt&);
   BigInt& operator+ (const BigInt&);
   BigInt& operator- (const BigInt&);
   BigInt& operator* (unsigned long n);
   BigInt& operator/ (unsigned long n);
   BigInt& ArcTan(unsigned int m, unsigned int ndigits, BigInt& term);
   void print(unsigned int n) const;
private:
   BigInt(); // do not allow
   unsigned long *arr;
   unsigned long radix;
   unsigned int digits_per_location;
   unsigned int locations;
};

#endif 

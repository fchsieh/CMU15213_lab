/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y)
{
    // (~(~x & y)) = (x | y)
    // (~(x & y)) = (~x | ~y)
    // => x ^ y = (x | y) & (~x | ~y)
    return (~(~x & ~y)) & (~(x & y));
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void)
{
    return (1 << 31);
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    /*
     * (~x) ^ (x+1) is 0 if x is either Tmax or -1 (0xffffffff).
     * We would need this one to check if x is Tmax.
     * But first, we need to block out the edge case (-1):
     * (x ^ (~0)) is 0 only if x is -1, we can check if this is non-zero (!!)
     * Then combine together (using bit &), we get the answer.
     */
    int isNotNegativeOne    = (!!(x ^ (~0)));
    int isTmaxOrNegativeOne = (!((~x) ^ (x + 1)));

    return isNotNegativeOne & isTmaxOrNegativeOne;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    int allOdds = ((0xAA << 24) | (0xAA << 16) | (0xAA << 8) | (0xAA));
    // mask all odd bits of x, and check if the mask result is = allOdds
    return !((x & allOdds) ^ allOdds);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    return ((~x) + 0x1);
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x)
{
    int GEQ_30 = !((x + (~0x30) + 1) >> 31);  //  >= 30
    int LT_3a  = !!((x + (~0x3a) + 1) >> 31); // < 3a (<= 39)
    return (GEQ_30 & LT_3a);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    int xIsTrue = !!x;
    // xIsTrue    -> 0x1 -> ~(0x1) + 1 = 0xffffffff
    // (!xIsTrue) -> 0x0 -> ~(0x0) + 1 = 0x0
    int retY = (~xIsTrue + 1) & y;
    int retZ = (~(!xIsTrue) + 1) & z;
    return retY | retZ;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    int diffSign          = !(x >> 31) ^ !(y >> 31);
    int X_LEQ_Y           = !((y + (~x) + 1) >> 31);
    int diffSign_X_is_Neg = (diffSign & (x >> 31));
    int sameSign_X_LEQ_Y  = ((~diffSign) & (X_LEQ_Y));
    return diffSign_X_is_Neg | sameSign_X_LEQ_Y;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
    // compress until last bit, and check if it is 0x1 (means that at least 1 bit in x)
    int comp_16 = (x >> 16) | x;
    int comp_8  = (comp_16 >> 8) | comp_16;
    int comp_4  = (comp_8 >> 4) | comp_8;
    int comp_2  = (comp_4 >> 2) | comp_4;
    int comp_1  = (comp_2 >> 1) | comp_2;

    return (comp_1 ^ 0x1) & 0x1; // inverse: 0x1 -> 0x0, 0x0 -> 0x1 (neg)
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x)
{
    int sign = x >> 31;
    int bit16, bit8, bit4, bit2, bit1, bit0;

    // find ans of negative number X is the same as finding inverse X
    x = (sign & ~x) | (~sign & x);

    // check if x is > 2^16, then move to right half (ex: 10100000 => xxxx1010)
    // if so, we add N by 16
    bit16 = (!!(x >> 16)) << 4;
    x >>= bit16;
    // check if x is > 2^8
    bit8 = !!(x >> 8) << 3;
    x >>= bit8;
    // check if x is > 2^4
    bit4 = !!(x >> 4) << 2;
    x >>= bit4;
    // check if x is > 2^2
    bit2 = !!(x >> 2) << 1;
    x >>= bit2;
    // check if x is > 2^1
    bit1 = !!(x >> 1) << 0;
    x >>= bit1;
    // last bit
    bit0 = x;

    // we need N+1 to represent
    return bit16 + bit8 + bit4 + bit2 + bit1 + bit0 + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned isNaN = (uf == 0x7f800000);

    unsigned SIGN     = (uf & 0x80000000);
    unsigned EXP      = (uf & 0x7f800000);
    unsigned FRACTION = (uf & 0x007fffff);

    if (EXP == 0)
        FRACTION <<= 1;
    else if (EXP != 0x7f800000) // if EXP is not 0xFF, then add EXP by 1
        EXP += 0x00800000;

    if (isNaN)
        return uf;
    return SIGN | EXP | FRACTION;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
    int f          = uf;
    int SIGN       = !!(f >> 31);
    int EXP        = (f >> 23) & 0xff;
    int FRAC       = (f & 0x007fffff);
    int OutOfRange = 0x80000000u;

    if (EXP == 0xff) // NaN and INF
        return OutOfRange;
    if (EXP < 127) // will be 0.xxxx
        return 0;

    EXP = EXP - 127;
    if (EXP >= 31) // overflow
        return OutOfRange;

    // 2^(exp) * (sum(i->23)b_{23-i}2^{-i})
    if (EXP >= 23) // this means that we need to multiply fraction by x (exp-23)
        FRAC <<= (EXP - 23);
    else // this means that we need to divide fraction by x (x = 23-exp)
        FRAC >>= (23 - EXP);

    // add back 1 (in the part of '1' + sum(i->23)b_{23-i}2^{-i})
    FRAC += (1 << EXP);

    if (SIGN)
        FRAC = -FRAC;

    return FRAC;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x)
{
    unsigned INF = 0x7f800000;
    unsigned EXP;

    if (x >= 0)
    {
        EXP = (x + 0x7f);
        if (EXP > 0xff)
            return INF;
        return (EXP << 23);
    }
    else
    {
        if (x < -149)
            return 0;
        if (x < -126) // using only the fraction part (-127 ~ -149)
            return (1 << (23 - (-x - 126)));
        // using only the EXP part (E - 127 = x)
        return ((x + 0x7f) & 0xff) << 23;
    }

    return 0;
}

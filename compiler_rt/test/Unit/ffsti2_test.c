//===-- ffsti2_test.c - Test __ffsti2 -------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file tests __ffsti2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//

#if __x86_64

#include "int_lib.h"
#include <stdio.h>

// Returns: the index of the least significant 1-bit in a, or
// the value zero if a is zero. The least significant bit is index one.

si_int __ffsti2(ti_int a);

int test__ffsti2(ti_int a, si_int expected)
{
    si_int x = __ffsti2(a);
    if (x != expected)
    {
        twords at;
        at.all = a;
        printf("error in __ffsti2(0x%llX%.16llX) = %d, expected %d\n",
               at.s.high, at.s.low, x, expected);
    }
    return x != expected;
}

char assumption_1[sizeof(ti_int) == 2*sizeof(di_int)] = {0};

#endif

int main()
{
#if __x86_64
    if (test__ffsti2(0x00000000, 0))
        return 1;
    if (test__ffsti2(0x00000001, 1))
        return 1;
    if (test__ffsti2(0x00000002, 2))
        return 1;
    if (test__ffsti2(0x00000003, 1))
        return 1;
    if (test__ffsti2(0x00000004, 3))
        return 1;
    if (test__ffsti2(0x00000005, 1))
        return 1;
    if (test__ffsti2(0x0000000A, 2))
        return 1;
    if (test__ffsti2(0x10000000, 29))
        return 1;
    if (test__ffsti2(0x20000000, 30))
        return 1;
    if (test__ffsti2(0x60000000, 30))
        return 1;
    if (test__ffsti2(0x80000000uLL, 32))
        return 1;
    if (test__ffsti2(0x0000050000000000uLL, 41))
        return 1;
    if (test__ffsti2(0x0200080000000000uLL, 44))
        return 1;
    if (test__ffsti2(0x7200000000000000uLL, 58))
        return 1;
    if (test__ffsti2(0x8000000000000000uLL, 64))
        return 1;
    if (test__ffsti2(make_ti(0x8000000800000000uLL, 0), 100))
        return 1;
    if (test__ffsti2(make_ti(0x8000000000000000uLL, 0), 128))
        return 1;

#else
    printf("skipped\n");
#endif
   printf("PASS\n");
    return 0;
}

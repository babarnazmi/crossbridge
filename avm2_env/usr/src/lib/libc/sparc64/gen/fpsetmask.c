/*
 * Written by J.T. Conklin, Apr 10, 1995
 * Public domain.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: src/lib/libc/sparc64/gen/fpsetmask.c,v 1.2.36.1.6.1 2010/12/21 17:09:25 kensmith Exp $");

#include <machine/fsr.h>
#include <ieeefp.h>

fp_except_t
fpsetmask(mask)
	fp_except_t mask;
{
	fp_except_t old;
	fp_except_t new;

	__asm__("st %%fsr,%0" : "=m" (old));

	new = old;
	new &= ~FSR_TEM_MASK;
	new |= FSR_TEM(mask & FSR_EXC_MASK);

	__asm__("ld %0,%%fsr" : : "m" (new));

	return (FSR_GET_TEM(old));
}

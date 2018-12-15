/*
 * median.c
 *
 * Created: 15/12/2018 01.01.39
 *  Author: M.A.S
 */ 

#include "median.h"

#define swap(a,b) a^=b; b^=a; a^=b;
#define sort(a,b) if (a>b){swap(a,b);}
	
int median5(int a, int b, int c, int d, int e) {
	sort(a,b);
	sort(d,e);
	sort(a,c);
	sort(b,c);
	sort(a,d);
	sort(c,d);
	sort(b,e);
	sort(b,c);
	// this last one is obviously unnecessary for the median
	//sort(d,e);
	
	return c;
}
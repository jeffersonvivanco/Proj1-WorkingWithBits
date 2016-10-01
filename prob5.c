/*
 * TODO: implement your solution to problem 5 in this file.
 * Author: Jefferson Vivanco
 * prob5.c: This program is the runnable progam that prints information about single precision float numbers. Functions
 						from the proj1.c file are used in this program. For the functions that return a pointer to something, we free the
						pointer we make them equal to when we are done using those functions.
 *NOTE: For the value of infnity, please enter INFINITY or NAN when running the program.
 */

#include "proj1.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


int main (int argc, char *argv[] ) {

	//----------------------------------------------------------------------------//GETTING USER FLOAT NUMBER

	float userF = 0.0f;

	printf("Please enter a floating point number: ");//
	scanf("%f",&userF);

	//----------------------------------------------------------------------------//PRINTING OUT RESULTS
	//------------------------------------------//Printing out the all bits line

	printf("%-11s%e\n","Value:",userF);
	char * allBits = get_bits_float(userF);
	printf("%-24s%s\n","All bits:", allBits);
	free(allBits);
	//------------------------------------------//Printing out the exp with the bit rep of the exp
	unsigned int *expp  = get_exp(userF);
	int expp2 = *expp;
	char * expp2Bits = get_bits_int(expp2);
	printf("%-11s%11u%34s\n","exp",*expp,expp2Bits);
	free(expp);
	free(expp2Bits);
	//-----------------------------------------//Printing out the frac with the bit rep of the frac
	unsigned int *frac = get_frac(userF);
	int frac2 = *frac;
	char * frac2Bits = get_bits_int(frac2);
	printf("%-11s%11u%34s\n","frac",*frac,frac2Bits);
	free(frac);
	free(frac2Bits);
	//-----------------------------------------//Printing out the sign with the bit rep of the sign
	unsigned int *sign = get_sign(userF);
	int sign2 = *sign;
	char * sign2Bits = get_bits_int(sign2);
	printf("%-11s%11u%34s\n","sign",*sign, sign2Bits);
	free(sign);
	free(sign2Bits);
	//-----------------------------------------//Printing out whether is normalized or denormalized
	if(is_normalized(userF))
	{
		printf("%e is normalized\n",userF );
	}
	else if(is_denormalized(userF))
	{
		printf("%e is denormalized\n",userF );
	}
	else if(is_special(userF))
	{
		printf("%e is special\n",userF );
	}
	else
		printf("\n");
	//------------------------------------------//Printing out E
	printf("E = %i\n", get_E(userF) );
	//------------------------------------------//Printing out M
	char * M = get_M(userF);
	printf("M = %s\n", M);
	free(M);
	//-------------------------------------------//Printing out s
	printf("s = %i\n", get_s(userF));
	return 0;
}

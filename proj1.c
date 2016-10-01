#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

/*
 * TODO: add your funcitons in this file.
 * Make sure that you document the code.
 * Author: Jefferson Vivanco
 * proj1.c: This C files defines all the functions from proj1.h. Please look at that file for a more thorough definition
            of what the functions actually do. The functions are used througout this file to help compute values for
            other functions. The function are also used in prob1.c, prob2.c and prob5.c
 */


char* get_bits_int ( int n ) {//------------------------------------------------//GET BITS INT
    //allocate memory to store the string
    int num_of_bits =  sizeof(int) * 8;  //*8 since there are 8 bits per byte
    char * bits_of_numbers = (char*) malloc( num_of_bits + 1);

    short bit ;

    int i;
    //convert value of n to bits
    for ( i = 0; i < num_of_bits; i++ ) {
        bit = n & 1; //grab the last bit
        bits_of_numbers[num_of_bits-i-1] = '0' + bit;
        n = n>>1;    //remove the last bit
    }

    bits_of_numbers[num_of_bits] = '\0'; //end with a null character
    return bits_of_numbers;
}


char* get_bits_float ( float f ) {//--------------------------------------------//GET BITS FLOAT
    //allocate memory to store the string
    int num_of_bits =  sizeof(float) * 8;  //*8 since there are 8 bits per byte
    char * bits_of_numbers = (char*) malloc( num_of_bits + 1);

    //interpret the bits as int (this is not equivalent to casting to int)
    int  p = *((int*) (&f) );
    short bit ;

    int i;
    //convert value of n to bits
    for ( i = 0; i < sizeof(float)*8; i++ ) {
        bit = p & 1;  //grab the last bit
        bits_of_numbers[num_of_bits-i-1] = '0' + bit;
        p = p>>1;    //remove the last bit
    }

    bits_of_numbers[num_of_bits] = '\0'; //end with a null character
    return bits_of_numbers;

}
char * convert_to_string ( int text[] , int size )//----------------------------//CONVERT TO STRING
{
  //allocate memory to store the string
  char * string  = (char *) malloc(size * sizeof(int));

  int indexString=0;
  int i;
  int shifInt = sizeof(int)*2;//This value is equal to 8, since each char is 8 bits, when we shift we want to shift
                              //by 8 so we can get each char
  //In this for loop, we loop through  the int text array. For each int, we get each byte and convert it to a char.
  //Then we add each char to a string, which will be the message.
  for(i=0; i<size; i++)
  {
    int number = text[i];
    int n;
    for(n=0; n<4; n++)
    {
      int byte = (number >> (shifInt*n)) & 0xFF;//Shifting to get each byte
      char letter = (char) byte;//converting each byte to a char
      string[indexString] = letter;//adding each char to the string "string"
      indexString++;
    }
  }
  return string;//returning the string
}
int convert_to_int (char * text)//----------------------------------------------//CONVERTING TO INT
{
  int shifInt = (sizeof(int) *2);
  int num = (int) (text[0] << (shifInt*0));//To get the first char in the string text, casting it to an int and adding it
  //to the int num
  int textIndex=1;
  int n=1;
  while(text[textIndex] != '\0')
  {
    num = (int) num | (text[textIndex] << (n*shifInt));//Getting other chars and adding the bits to the int num;
    textIndex++;
    n++;
  }
  return num;

}
int get_most_significant_byte ( int num )//-------------------------------------//GETTING MOST SIGNIFICANT BYTE
{
  int shifInt = sizeof(int)*2;
  int byte = (num >> (shifInt*3))& 0xFF;//Shifting by 24 to get the most significant byte which is at the far right
  return byte;
}
int get_least_significant_byte ( int num )//------------------------------------//GETTING LEAST SIGNIFICANT BYTE
{
  int shifInt = sizeof(int)*2;
  int byte = (num >> (shifInt*0))& 0xFF;//Shifting by 0 to get the least significant byte which is at the far left
  return byte;
}
unsigned int * get_exp ( float f ){//-------------------------------------------//GETTING EXPONENT INT REP.

  char * bits = get_bits_float(f);//getting the string bit representation of the float
  //allocate memory to store the unsigned int
  unsigned int * total = (unsigned int *)malloc(sizeof(unsigned int));
  int num;//This is where we are storing the int value of the bit
  double exponent=7;//Since the exponent is 8 bits long, when we iterate through it, the first value is going to be
                    //bit * 2^7.
  int value;//This is where we are storing the value of pow()
  int i;
  for(i =0; i<8; i++)
  {
    num = ((int)bits[i+1]) - 48;
    value = (pow(2, exponent))*num;
    exponent--;//Decrementing exponent as we go through the bits
    * total += value;
  }

  *total = (*total << 23);//Since the exponent value has the bits all the way to the left, I shifted the bits to the left
                          //by 23, to leave a space for the 0
  free(bits);//freeing the memory bits
  return total;
}
unsigned int * get_frac ( float f )//-------------------------------------------//GETTING FRAC INT REP.
{
  char * bits = get_bits_float(f);//Getting the string bit representation of the float
  //Allocating memory to the unsigned int
  unsigned int * total  = (unsigned int *)malloc(sizeof(unsigned int));
  int num;
  double exponent=22;//Since the bit where the frac starts is 2^22
  int value;
  int i;
  for(i =9; i<32; i++)
  {
    num = ((int)bits[i]) - 48;
    value = (pow(2, exponent))*num;
    exponent--;//Decrementing to get the values of the other bits, 2^21,2^20....
    *total += value;

  }
  free(bits);//freeing bits
  return total;
}
unsigned int * get_sign ( float f )//-------------------------------------------//GETTING SIGN INT REP
{
  char * bits = get_bits_float(f);//Getting the bit representation of the float
  //Allocating memory for the unsigned int
  unsigned int * bit = (unsigned int *)malloc(sizeof(unsigned int));
  * bit = (bits[0] - 48);
  * bit = (*bit << 31);//Shifting by 31 since the bit representation has the sign bit to the far left
  free(bits);//freeing bits
  return bit;

}
int is_normalized ( float f ) {//-----------------------------------------------//IS NORMALIZED

  unsigned int * floatExp = get_exp(f);//getting the exponent unsigned int value
  int floatExp2 = *floatExp;
  char * bits  = get_bits_int(floatExp2);//getting the bit representation of the exponent value
  //printf("The bits of the is normalized are %s\n",bits );
  int index0=0;
  int index1=0;
  int i;
  //This loops counts the number of 1s or 0s in the bits, if they are all 1s or all 0s, then one of them has to
  //to have 8 elements
  for(i=1; i<9; i++)
  {
    if(bits[i] == '0'){
      index0++;
    }
    if(bits[i] =='1'){
      index1++;
    }
  }
  free(floatExp);//freeing floatExp
  free(bits);//freeing bits
  //Checks if any had 8, if it did, then it returns 0, else it returns 1
  if(index0 == 8){
    return 0;
  }
  else if(index1 == 8)
    return 0;
  else{
    return 1;
  }

}
int is_denormalized ( float f )//-----------------------------------------------//IS DENORMALIZED
{
  unsigned int * floatExp = get_exp(f); //Getting the unsigned int representation of the exp of the float
  int floatExp2 = *floatExp;
  //Checking if it equals 0, if it does then it returns 1. If it equals to 0 then it has all of its bits equal to 0
  if(floatExp2 == 0){
    free(floatExp);//freeing bits
    return 1;
  }
  return 0;

}
int is_special ( float f ) {//--------------------------------------------------//IS SPECIAL
  unsigned int * floatExp = get_exp(f);//Getting the exp unsigned int value of the exponent of the float
  int floatExp2 = *floatExp;
  //If it is all 1s, then its equal to this big value, if so it returns 1
  if(floatExp2==2139095040){
    free(floatExp);
    return 1;
  }
  return 0;
}
int get_E ( float f )//---------------------------------------------------------//GET E
{

  unsigned int * expp = get_exp(f);//We get the expoenent value of f
  //Since we need the int representation of only the bits of the int, we shift it by 23, to get the bits of the expp
  //to the far right
  *expp = (*expp>>23);
  int E;
  //Computing bias = (2^k-1)-1 , k is # of exponent bits
  int bias = (pow(2, 7))-1;
  //E = exp - bias
  E = (*expp)  - bias;
  free(expp);
  return E;
}
char * get_M ( float f )//------------------------------------------------------//GET M
{
  //Allocating memory for a string
  char * M = (char *)malloc(sizeof(char)*26);
  char * bitsFrac;

  //If normalized then we add 1. to the char array M
  if(is_normalized(f))
  {
    M[0] = '1';
    M[1] = '.';
    unsigned int * frac = (unsigned int *)malloc(sizeof(unsigned int));//Getting the frac int representation
    frac = get_frac(f);
    int frac2 = *frac; //casting it to int so it can
    bitsFrac = get_bits_int(frac2);//Getting the bit string of the frac
    int i;
    int j=9;
    for(i=2; i<25; i++)
    {
      M[i] = bitsFrac[j++];
    }
    M[25] = '\0';
    //Freeing frac and bitsFrac
    free(frac);
    free(bitsFrac);
    return M;
  }
  //If denormalized, then we add 0. to the char array M
  else if(is_denormalized(f))
  {

    M[0] = '0';
    M[1] = '.';
    //Allocating memory for an unsigned int
    unsigned int * frac = (unsigned int *)malloc(sizeof(unsigned int));
    frac = get_frac(f);
    //Casting frac to int so it can be passed to get bits int
    int frac2 = *frac;
    bitsFrac = get_bits_int(frac2);//Getting string bits of frac
    int i;
    int j=9;
    for(i=2; i<25; i++)
    {
      M[i] = bitsFrac[j++];//Adding string bits to M
    }
    M[25] = '\0';
    free(frac); //freeing frac
    free(bitsFrac); //freeing bitsFrac
    return M;
  }
  else{
    //Else we return an empty array
    return M;
  }
}
int get_s ( float f )//---------------------------------------------------------//GET S
{
  //Getting unsigned int value of sign of the float f
  unsigned int * s = get_sign(f);
  //Shifting s by 31 since we want the int bit value of only the sign bit
  *s = (*s>>31);
  int s2 = *s;
  free(s);//freeing s
  return s2;

}

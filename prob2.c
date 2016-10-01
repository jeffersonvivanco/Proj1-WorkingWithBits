/*
 * TODO: implement your solution to problem 2 in this file.
 * Author: Jefferson Vivanco
 * prob2.c: This program does the reverse of prob1.c. The user passes two command line arguments, one is a file with the
            message that the user wants to be coded and the other one is the name of the output file, where the coded
            message would be written to. The convert_to_int function used in this program is defined in proj1.c.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj1.h"
int main (int argc, char *argv[] )  {
    if(argc != 3)//CHECKING IF THE USER ENTER A COMMAND
    {
        printf("ERROR: MAKE SURE YOU ENTERED AN INPUT AND OUTPUT FILE NAME\n");
        exit(0);
    }

    FILE * file = fopen(argv[1],"r");//READING FILE
    if(file==0)//CHECKING IF FILE CAN BE READ
    {
        printf("ERROR: FILE COULD NOT BE READ\n");
        exit(0);
    }
    FILE * wFile = fopen(argv[2],"w");//WRITING TO FILE THE USER ENTERED TO WRITE ON
    if(wFile ==0)//CHECKING IF FILE WAS CREATED
    {
      printf("ERROR: FILE COULD NOT BE CREATED\n");
      exit(0);
    }
    //READING FILE LINE BY LINE
    char tmp[5];//This is where we will store 4 characters
    int array[100];
    int indextmp=0;//This index keeps track of how many chars have been added to the tmp array. The tmp array gets casted
                  //to a char*. This pointer is passed to the convert_to_int function to be converted to an int
    int indexarr=0;//This is the index of the array array, we store here the ints that we get from the convert_to_int function
    char *str; //We set the tmp array equal to this char * and then we pass this char *
    char c;//We set fgetc equal to this char, when this char equals EOF,we know thats the end of the file

    while(1){//We set this while loop to always be true so it can traverse the file, when c = EOF, we have a break that
            //breaks the loop
        c = fgetc(file);
        if(c!=EOF)
        {
            if(indextmp<4) {
                tmp[indextmp] = c;
                indextmp++;
            }
            else{
                tmp[indextmp] = '\0';//We terminate the char array tmp
                str = tmp;
                int tmp2 = convert_to_int(str);
                array[indexarr] = tmp2;
                fprintf(wFile, "%i\n",tmp2);//writing the int to the file
                indexarr++;
                indextmp=0;

                tmp[indextmp] = c;
                indextmp++;

            }
        }
        else{
            if(indextmp!=0)//possiblity of a tmp array less than 4 chars, we pass the tmp anyways to convert_to_int
            {
                tmp[indextmp] = '\0';
                str = tmp;
                int tmp2 = convert_to_int(str);
                array[indexarr] = tmp2;
                fprintf(wFile, "%i\n",tmp2);
            }
            break;//No other possiblity and c=EOF, we break
        }
    }
    return 0;
}

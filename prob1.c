/*
 * TODO: implement your solution to problem 1 in this file.
 * Author: Jefferson Vivanco
 * prob1.c:This prob1.c file is the runnanble program for the first problem. This program asks the user
           to enter a file name. This file name is a text file that has a message encoded in ints.This
           program converts all the integers to a single string. This string is the message and it gets
           printed to the console at the end of the program. The convert_to_string function used in this
           program is defined in proj1.c.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj1.h"

int main (int argc, char *argv[] )  {

    if(argc != 2)//CHECKING IF THE USER ENTER A COMMAND
    {
        printf("ERROR: RUN AGAIN AND ENTER A FILE NAME!\n");
        exit(0);
    }

    FILE * file = fopen(argv[1],"r");//READING FILE
    if(file==0)//CHECKING IF FILE CAN BE READ
    {
        printf("ERROR: FILE COULD NOT BE READ\n");
        exit(0);
    }

    //READING FILE LINE BY LINE
    char line[12];//Creating a char array to store the line that would be read.The line is an integer
                  //We use the sscanf function to convert the string int to an actual int, afterwards,
                  //we store that int in an integer array which will be passed to the convert_to_string
                  //function.
    int text[1000];
    int index=0;
    int number=0;
    while(1){
        if(fgets(line, 12, file) == NULL ) break;//Reading each line
        sscanf(line, "%i", &number);//converting line to int
        text[index] = number;//adding int to int array
        index++;
    }

    char * string;
    string  = convert_to_string(text,index);
    printf("%s\n",string);
    free(string);//freeing stirng
    return 0;
}

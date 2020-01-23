/*
Author: Nathan Brown
Class: CptS 122, Spring, 2019; Lab Section 3
Date: January 22, 2020
Description: Reads data from a CSV file and performs some calculations with it.
*/

#include "fitbit.h"

int main(void)
{
	FitbitData day_data[1500] = { 0 };
	char* buff = (char*)malloc(6 * sizeof(char));
	strcpy(buff, "ABCDE");

	//Prepare to open file
	FILE* infile = NULL;

	//Read in data
	read_csv(day_data, infile);

	return 0;
}
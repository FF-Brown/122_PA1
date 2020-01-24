

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum sleep
{
	NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} Sleep;

/*
	char patient[10];
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;
*/
typedef struct fitbit
{
	char patient[10];
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;
} FitbitData;
/*
	Function: read_csv()
	Description: Reads and parses records from .csv. Runs cleaning functions on each row.
	Preconditions: FILE* defined and passed in. Struct array defined.
	Postconditions: Array filled with data.
*/
void read_csv(FitbitData data[], FILE* infile);
/*
	Function: clean_row()
	Description: Checks a row of data for double commas or dangling commas to correct empty fields. Runs insertion function when necessary. Returns 1 if any issues were corrected to allow for it to be re-run to confirm the absence of further errors.
	Preconditions: Row of data residing in buffer.
	Postconditions: Called insert() if necessary. Returns 1 if error corrected, 0 otherwise.
*/
int clean_row(char* buff);
/*
	Function: insert()
	Description: Shifts string elements to the right and inserts a 0 to fill empty field.
	Preconditions: Row of data saved in buffer. Insert point determined. Size of string determined.
	Postconditions: 0 inserted in string.
*/
void insert(char buff[], int insert_pt, int size);
/*
	Function: calc_calories()
	Description: Calculates total calories burned
	Preconditions: Data read, cleaned, and parsed
	Postconditions: Returns total calories burned
*/
double calc_calories(FitbitData data[]);
/*
	Function: calc_distance()
	Description: Calculates total distance walked in miles
	Preconditions: Data read, cleaned, and parsed
	Postconditions: Returns total distance walked
*/
double calc_distance(FitbitData data[]);
/*
	Function: calc_floors()
	Description: Calculates total floors walked
	Preconditions: Data read, cleaned, and parsed
	Postconditions: Returns total floors walked
*/
int calc_floors(FitbitData data[]);
/*
	Function: calc_steps()
	Description: Calculates total steps taken
	Preconditions: Data read, cleaned, and parsed
	Postconditions: Returns total steps taken
*/
int calc_steps(FitbitData data[]);
/*
	Function: calc_avg_heartRate()
	Description: Calculates average heartrate
	Preconditions: Data read, cleaned, and parsed
	Postconditions: Returns average heartrate
*/
double calc_avg_heartRate(FitbitData data[]);
/*
	Function: max_steps()
	Description: Finds max number of steps in one minute
	Preconditions: Data read, cleaned, and parsed
	Postconditions: Returns max value
*/
int max_steps(FitbitData data[]);
/*
	Function: poor_sleep()
	Description: Finds greatest period of poor sleep based on severity of sleep deficiency (sum of values), not just length of time.
	Preconditions: Data read, cleaned, and parsed
	Postconditions: Returns indices of beginning and end of sleep deficient period via pointers
*/
void poor_sleep(FitbitData data[], int* begin_index, int* end_index);



#include "fitbit.h"

/*
	Function: read_csv()
	Description: Reads and parses records from .csv. Runs cleaning functions on each row.
	Preconditions: FILE* defined and passed in. Struct array defined. 
	Postconditions: Array filled with data.
*/
void read_csv(FitbitData data[], FILE* infile)
{
	char delim[] = ",";
	int i = 0, result = 0, record_count = 0;
	char* token = '\0';
	infile = fopen("FitbitData.csv", "r");

	//Check for success
	if (infile != NULL)
		printf("File opened successfully.\n");
	else {
		printf("Error opening file.\n");
		return 1;
	}

	//Allocate space for buffer
	char* buff = (char*)malloc(100 * sizeof(char));

	//Verify allocation
	if (buff == NULL) {
		printf("Memory not allocated.\n");
		return 1;
	}
	
	//Read in records
	while (fgets(buff, 90, infile)) {

	restart:
		
		//Clean data row
		do {
			result = clean_row(buff);
		} while (result == 1);
		
		//Get first token
		token = strtok(buff, delim);

		//Confirm patient ID for row
		if (strcmp(token, "12cx7") != 0) {
			fgets(buff, 90, infile);
			token = strtok(buff, delim);
		}

		//One record
		while (token != NULL) {

			//Patient
			strcpy(data[i].patient, token);
			printf("Patient: %s\n", data[i].patient);
			token = strtok(NULL, delim);			

			//Minute
			strcpy(data[i].minute, token);

			//Check for duplicate row
			if (!strcmp(data[i].minute, data[i - 1].minute)) {
				fgets(buff, 90, infile);
				goto restart;
			}
			printf("Minute: %s\n", data[i].minute);
			token = strtok(NULL, delim);

			//Calories
			data[i].calories = atof(token);
			printf("Calories: %lf\n", data[i].calories);
			token = strtok(NULL, delim);

			//Distance
			data[i].distance = atof(token);
			printf("Distance: %lf\n", data[i].distance);
			token = strtok(NULL, delim);

			//Floors
			data[i].floors = atoi(token);
			printf("Floors: %d\n", data[i].floors);
			token = strtok(NULL, delim);

			//Heartrate
			data[i].heartRate = atoi(token);
			printf("Heartrate: %d\n", data[i].heartRate);
			token = strtok(NULL, delim);

			//Steps
			data[i].steps = atoi(token);
			printf("Steps: %d\n", data[i].steps);
			token = strtok(NULL, delim);

			//Sleep Level
			data[i].sleepLevel = (Sleep)atoi(token);
			printf("Sleep Level: %d\n", data[i].sleepLevel);
			token = strtok(NULL, delim);
		}
		++record_count;
		++i;
	};
	printf("%d records parsed.\n", record_count);

	//Close file
	fclose(infile);
}
/*
	Function: clean_row()
	Description: Checks a row of data for double commas or dangling commas to correct empty fields. Runs insertion function when necessary. Returns 1 if any issues were corrected to allow for it to be re-run to confirm the absence of further errors.
	Preconditions: Row of data residing in buffer.
	Postconditions: Called insert() if necessary. Returns 1 if error corrected, 0 otherwise.
*/
int clean_row(char* buff)
{
	int size = strlen(buff);
	int found = 0;

	//Check row
	for (int i = 0; i < size; i++) {
		//Find commas
		if (*(buff + i) == ',') {
			//If followed by comma, newline, or null
			if (*(buff + i + 1) == ',' || *(buff + i + 1) == '\n' || *(buff + i + 1) == '\0') {
				//Insert -1 at this position
				insert(buff, i + 1, size);
				found = 1;
			}
		}
	}
	return found;
}
/*
	Function: insert()
	Description: Shifts string elements to the right and inserts a 0 to fill empty field.
	Preconditions: Row of data saved in buffer. Insert point determined. Size of string determined.
	Postconditions: 0 inserted in string.
*/
void insert(char buff[], int insert_pt, int size)
{
	//Shift elements right 1 space, up to insertion point.
	for (int i = size; i >= insert_pt; i--) 
		buff[i + 1] = buff[i];

	//Insert value
	buff[insert_pt] = '0';
}
/*
	Function: calc_calories()
	Description: Calculates total calories burned
	Preconditions: Data read, cleaned, and parsed
	Postconditions: Returns total calories burned
*/
double calc_calories(FitbitData data[])
{
	double total = 0.0;

	for (int i = 0; i < 1440; ++i) {
		total += data[i].calories;
	}
	return total;
}
/*
	Function: calc_distance()
	Description: Calculates total distance walked in miles
	Preconditions: Data read, cleaned, and parsed
	Postconditions: Returns total distance walked
*/
double calc_distance(FitbitData data[])
{
	double total = 0.0;

	for (int i = 0; i < 1440; ++i) {
		total += data[i].distance;
	}
	return total;
}
/*
	Function: calc_floors()
	Description: Calculates total floors walked
	Preconditions: Data read, cleaned, and parsed
	Postconditions: Returns total floors walked
*/
int calc_floors(FitbitData data[])
{
	int total = 0;

	for (int i = 0; i < 1440; ++i) {
		total += data[i].floors;
	}
	return total;
}
/*
	Function: calc_steps()
	Description: Calculates total steps taken
	Preconditions: Data read, cleaned, and parsed
	Postconditions: Returns total steps taken
*/
int calc_steps(FitbitData data[])
{
	int total = 0;

	for (int i = 0; i < 1440; ++i) {
		total += data[i].steps;
	}
	return total;
}
/*
	Function: calc_avg_heartRate()
	Description: Calculates average heartrate
	Preconditions: Data read, cleaned, and parsed
	Postconditions: Returns average heartrate
*/
double calc_avg_heartRate(FitbitData data[])
{
	int total = 0;
	double avg = 0.0;
	int count = 0;

	for (int i = 0; i < 1440; ++i) {
		if (data[i].heartRate > 0) {
			total += data[i].heartRate;
			++count;
		}
	}
	avg = total / (double)count;
	return avg;
}
/*
	Function: max_steps()
	Description: Finds max number of steps in one minute
	Preconditions: Data read, cleaned, and parsed
	Postconditions: Returns max value
*/
int max_steps(FitbitData data[])
{
	int max = data[0].steps;

	for (int i = 0; i < 1440; ++i) {
		if (data[i].steps >= max)
			max = data[i].steps;
	}
	return max;
}
/*
	Function: poor_sleep()
	Description: Finds greatest period of poor sleep based on severity of sleep deficiency (sum of values), not just length of time.
	Preconditions: Data read, cleaned, and parsed
	Postconditions: Returns indices of beginning and end of sleep deficient period via pointers
*/
void poor_sleep(FitbitData data[], int* begin_index, int* end_index)
{
	int begin_candidate = 0, end_candidate = 0;
	int sum = 0, max = 0;

	//Run through records
	for (int i = 0; i < 1440; ++i) {

		//Check for 2's or 3's
		if (data[i].sleepLevel > 1)	{
			begin_candidate = i;
			//Find end of range
			while (data[i].sleepLevel > 1) {
				++i;
				//Mark end of range
				if (data[i].sleepLevel == 1) {
					end_candidate = i;
				}
			}
		}
		//Sum range
		for (int j = begin_candidate; j < end_candidate; ++j) {
			sum += data[j].sleepLevel;
		}
		//If max, set begin/end markers
		if (sum > max) {
			max = sum;
			*begin_index = begin_candidate;
			*end_index = end_candidate;
		}
	}
}

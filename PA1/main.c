

#include "fitbit.h"

int main(void)
{
	FitbitData day_data[1500] = { 0 };
	char* token;
	int i = 0;
	char temp = '\0';
	char delim[] = ",";

	//Open file
	FILE* infile = NULL;
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

	//Read in records
	while (fgets(buff, 90, infile)) {

		token = strtok(buff, delim);

		//Confirm patient ID for row
		if (strcmp(token, "12cx7") != 0) {
			fgets(buff, 90, infile);
			token = strtok(buff, delim);
		}

		//One record
		while (token != NULL) {

			//Patient
			strcpy(day_data[i].patient, token);
			printf("%s\n", day_data[i].patient);
			token = strtok(NULL, delim);

			//Minute
			strcpy(day_data[i].minute, token);
			printf("%s\n", day_data[i].minute);
			token = strtok(NULL, delim);

			//Calories
			day_data[i].calories = atof(token);
			printf("%f\n", day_data[i].calories);
			token = strtok(NULL, delim);

			//Distance
			day_data[i].distance = atof(token);
			printf("%f\n", day_data[i].distance);
			token = strtok(NULL, delim);

			//Floors
			day_data[i].floors = atoi(token);
			printf("%d\n", day_data[i].floors);
			token = strtok(NULL, delim);

			//Heartrate
			day_data[i].heartRate = atoi(token);
			printf("%d\n", day_data[i].heartRate);
			token = strtok(NULL, delim);

			//Steps
			day_data[i].steps = atoi(token);
			printf("Steps: %d\n", day_data[i].steps);
			token = strtok(NULL, delim);

			//Sleep Level
			day_data[i].sleepLevel = (Sleep)atoi(token);
			printf("%d\n", day_data[i].sleepLevel);
			token = strtok(NULL, delim);
		}
		++i;
	};



	return 0;
}
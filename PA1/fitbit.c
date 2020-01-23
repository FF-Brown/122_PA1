

#include "fitbit.h"

void read_csv(FitbitData data[], FILE* infile)
{
	char delim[] = ",";
	int i = 0, result = 0;
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

		//Clean data row
		//printf("%s\n", buff);
		do {
			result = clean_row(buff);
		} while (result == 1);
		//printf("%s\n", buff);
		//return 0;
		
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
		++i;
	};

}
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
void insert(char buff[], int insert_pt, int size)
{
	//Allocate space for two new elements
	realloc(buff, sizeof(char) * (3 + size));

	//Shift elements right 2 spaces, up to insertion point.
	for (int i = size; i >= insert_pt; i--) {
		buff[i + 2] = buff[i];
	}

	//Insert value
	buff[insert_pt] = '-';
	buff[insert_pt + 1] = '1';
}
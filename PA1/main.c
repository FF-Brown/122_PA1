/*
Author: Nathan Brown
Class: CptS 122, Spring, 2019; Lab Section 3
Date: January 22, 2020
Description: Reads data from a CSV file and performs some calculations with it.
*/

#include "fitbit.h"

int main(void)
{
	double calories = 0.0, distance = 0.0;
	int floors = 0, steps = 0, maxSteps = 0;
	double avg_heartRate = 0.0;
	int sleep_start = 0, sleep_end = 0;
	FitbitData day_data[1500] = { 0 };

	//Prepare to open file
	FILE* infile = NULL;

	//Read in data
	read_csv(day_data, infile);

	//Calculate: 
	//Total calories
	calories = calc_calories(day_data);
	printf("\nCalories: %lf\n", calories);

	//Total distance walked
	distance = calc_distance(day_data);
	printf("Distance: %lf\n", distance);

	//Total floors walked
	floors = calc_floors(day_data);
	printf("Floors: %d\n", floors);

	//Total steps taken
	steps = calc_steps(day_data);
	printf("Steps: %d\n", steps);

	//Average heartrate
	avg_heartRate = calc_avg_heartRate(day_data);
	printf("Avg heartrate: %lf\n", avg_heartRate);

	//Max steps in one minute
	maxSteps = max_steps(day_data);
	printf("Max steps: %d\n", maxSteps);

	//Longest range of poor sleep
	poor_sleep(day_data, &sleep_start, &sleep_end);
	printf("Begin sleep: %s\nEnd sleep: %s\n", day_data[sleep_start].minute, day_data[sleep_end - 1].minute);

	//Output results
	FILE* outfile = NULL;
	outfile = fopen("Results.csv", "w");
	if (outfile == NULL) {
		perror("Failed: ");
		return 1;
	}
	else
		printf("File opened successfully.\n");

	fprintf(outfile, "Total Calories, Total Distance, Total Floors, Total Steps, Avg Heartrate, Max Steps, Sleep\n");
	fprintf(outfile, "%lf, %lf, %d, %d, %lf, %d, %s:%s", calories, distance, floors, steps, avg_heartRate, maxSteps, day_data[sleep_start].minute, day_data[sleep_end - 1].minute);

	//Close file
	fclose(outfile);

	return 0;
}
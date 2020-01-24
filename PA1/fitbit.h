

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
void read_csv(FitbitData data[], FILE* infile);
int clean_row(char* buff);
void insert(char buff[], int insert_pt, int size);
double calc_calories(FitbitData data[]);
double calc_distance(FitbitData data[]);
int calc_floors(FitbitData data[]);
int calc_steps(FitbitData data[]);
double calc_avg_heartRate(FitbitData data[]);
int max_steps(FitbitData data[]);
void poor_sleep(FitbitData data[], int* begin_index, int* end_index);

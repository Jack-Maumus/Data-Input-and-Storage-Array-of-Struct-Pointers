/**
 * This method read a set of vehicle values from a text file and
 *  prints them to an outfile in readable form.
 *
 *  routine: vehicleInput
 *
 *  return type: 
 *
 *  parameters:
 *
 *  @author Jack Maumus
 *  @since 3/27/22
 *
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Utilities.h" 
#include "VehicleStruct.h"

void InputVehicle(FILE* inFile, vehicle *Vehicle[], int pos, int type);
void OutputInfo(FILE* outFile, vehicle *Vehicle[], int pos);
int FindVehicleType(FILE* inFile);
void VehicleBubbleSort(vehicle *Vehicle[], int pos);
void SwapVehicles(int one, int two, vehicle *Vehicle[]);
int VehicleCmp(vehicle *one, vehicle *two);

int main(void) {
	
	vehicle *Vehicle[500];
	int vehicle;
	int pos;

	printf("Opening TestInput.txt...\n");
	FILE* inFile = 	fopen("./TestInput.txt", "r");
	printf("Opening out.txt...\n");
	FILE* outFile = fopen("out.txt", "w");
	printf("Reorganizing TestInput.txt to out.txt in a more readable form...\n");
	
	//determining if vehicle is a truck, boat, or car once before the loop
	vehicle = FindVehicleType(inFile);
	
	while (!feof(inFile)) {
		InputVehicle(inFile, Vehicle, pos, vehicle);
		
		//determining if the vehicle is a car, truck, or boat within in the loop
		vehicle = FindVehicleType(inFile);
		pos++;
		if (pos == 500) break;
	}
	
	//Sorts by year and prints to output
	VehicleBubbleSort(Vehicle, pos);
	OutputInfo(outFile, Vehicle, pos);

	printf("Input file read and reorganized in out.txt\n");
	printf("Closing input and output files and deallocating memory...\n");
	
	for (int i = 0; i < pos; i++) {
		free(Vehicle[i]->vehicleMake);
		free(Vehicle[i]->vehicleModel);
		if (Vehicle[i]->vehicleType == CAR) free(Vehicle[i]->type.car.carRearConfig);
		if (Vehicle[i]->vehicleType == BOAT) free(Vehicle[i]->type.boat.boatMotorType);
		free(Vehicle[i]);
	}

	fclose(inFile);
	fclose(outFile);

	return 0;
}

void InputVehicle(FILE* inFile, vehicle *Vehicle[], int pos, int type) {
	vehicle *temp = (vehicle*) malloc(sizeof(vehicle));
	char *stringTemp = (char*) malloc (sizeof(char*) * 51);
	int len = 0;
	
	//Vehicle's make
	InputString(inFile, stringTemp);
	len = strlen(stringTemp) + 1;
	temp->vehicleMake = (char*) malloc(sizeof(char*) * len);
	strcpy(temp->vehicleMake, stringTemp);

	//vehicle's model
	InputString(inFile, stringTemp);
	len = strlen(stringTemp) + 1;
	temp->vehicleModel = (char*) malloc(sizeof(char*) * len);
	strcpy(temp->vehicleModel, stringTemp);

	//vehicle's year
	temp->vehicleYear = InputInteger(inFile);

	//vehicle's VIN
	InputString(inFile, temp->vehicleVIN);

	switch(type) {
		case CAR :
			//car's number of doors
		       temp->type.car.vehicleNumDoors = InputInteger(inFile);
		       //car's rear configuration
		       InputString(inFile, stringTemp);
		       len = strlen(stringTemp) + 1;
		       temp->type.car.carRearConfig = (char*) malloc(sizeof(char*) * len);
		       strcpy(temp->type.car.carRearConfig, stringTemp);

		       temp->vehicleType = CAR;
		       break;
		case TRUCK :
		       //truck's number of doors
		       temp->type.truck.vehicleNumDoors = InputInteger(inFile);
		       //truck's tow limit
		       temp->type.truck.truckTowLimit = InputFloat(inFile);

		       temp->vehicleType = TRUCK;
		       break;
		case BOAT :
		       //boat's motor type
		       InputString(inFile, stringTemp);
		       len = strlen(stringTemp) + 1;
		       temp->type.boat.boatMotorType = (char*) malloc(sizeof(char*) * len);
		       strcpy(temp->type.boat.boatMotorType, stringTemp);

		       temp->vehicleType = BOAT;
		       break;
	}

	Vehicle[pos] = temp;
	return;
}

void OutputInfo(FILE* outFile, vehicle *Vehicle[], int pos) {
	vehicle *temp = NULL;
	
	for (int i = 0; i < pos; i++) {
		temp = Vehicle[i];
		fprintf(outFile, "%d %s %s\nVIN: %s\n", temp->vehicleYear, temp->vehicleMake, temp->vehicleModel, temp->vehicleVIN);

		if (temp->vehicleType == BOAT) {
			fprintf(outFile, "Motor: %s\n\n", temp->type.boat.boatMotorType);
		} else if (temp->vehicleType == CAR) {
			fprintf(outFile, "Doors: %d\nRear Configuration: %s\n\n", temp->type.car.vehicleNumDoors, temp->type.car.carRearConfig);
		} else {
			fprintf(outFile, "Doors: %d\nMax Towing Capacity: %.1f\n\n", temp->type.truck.vehicleNumDoors, temp->type.truck.truckTowLimit);
		}
	}

	return;
}

int FindVehicleType (FILE* inFile) {
	char buf[MAXSTRINGINPUT];
	int vehicle = 0;
	InputString(inFile, buf);
	if (! strcmp(buf, "truck")) {
		vehicle = TRUCK;
	} else if (! strcmp(buf, "boat")) {
		vehicle = BOAT;
	} else {
		vehicle = CAR;
	}
	return vehicle;
}

void VehicleBubbleSort(vehicle *Vehicle[], int pos) {
	for (int i = 0; i < pos - 1; i++) {
		for (int j = 0; j < pos - i - 1; j++) {
			if (!VehicleCmp(Vehicle[j], Vehicle[j+1])) {
				SwapVehicles(j, j+1, Vehicle);
			}
		}
	}
	return;
}

int VehicleCmp(vehicle *one, vehicle *two) {
	return one->vehicleYear < two->vehicleYear;
}

void SwapVehicles(int one, int two, vehicle *Vehicle[]) {
	vehicle *temp = Vehicle[one];
	Vehicle[one] = Vehicle[two];
	Vehicle[two] = temp;
	return;
}


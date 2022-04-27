#ifndef VEHICLE_H
#define VEHICLE_H

typedef struct boat {
	char *boatMotorType;
} Boat_s;

typedef struct car {
	int vehicleNumDoors;
	char *carRearConfig;
} Car_s;

typedef struct truck {
	int vehicleNumDoors;
	float truckTowLimit;
} Truck_s;

typedef struct vehicle_struct {
	int vehicleYear;
	int vehicleNumDoors;
	int vehicleType;
	char *vehicleMake;
	char *vehicleModel;
	char vehicleVIN[18];
	char printInfo;
	union VehicleTypeStruct {
		Boat_s boat;
		Car_s car;
		Truck_s truck;
	} type;
} vehicle;
#endif

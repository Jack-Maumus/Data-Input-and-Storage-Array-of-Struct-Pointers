/**
 * Contains useful functions
 * Use of functions can be found in .h file
 *
 * @author: Jack Maumus
 * @since: 4-13-22
 */


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include "Utilities.h"

FILE* inFile;
char InString[MAXSTRINGINPUT];
char buf[INT_MAX-1];

int RemoveEndingWhiteSpace(char TheString[]) {
	TheString[strcspn(TheString, "\n")] = 0;
	int len = strlen(TheString);
	return len;
}

int InputInteger(FILE* inFile) {
	int input;
	fgets(buf, MAXSTRINGINPUT, inFile);
	RemoveEndingWhiteSpace(buf);
	input = atoi(buf);
	return input;
}

float InputFloat(FILE* inFile) {
	float input;
	fgets(buf, MAXSTRINGINPUT, inFile);
	RemoveEndingWhiteSpace(buf);
	input = atof(buf);
	return input;
}

int InputString(FILE* inFile, char InString[]) {
	fgets(InString, MAXSTRINGINPUT, inFile);
	InString[strcspn(InString, "\n")] = 0;
	return strlen(InString);
}

void SwapElements(int element1, int element2, char** charArray) {
	char* temp = charArray[element1];
	charArray[element1] = charArray[element2];
	charArray[element2] = temp;
	//strcpy(temp, charArray[element1]);
	//strcpy(charArray[element1], charArray[element2]);
	//strcpy(charArray[element2], temp);
	return;
}

void BubbleSort(char** charArray, int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (strcmp(charArray[j], charArray[j+1]) > 0) {
				SwapElements(j, j+1, charArray);
			}
		}
	}
	return;
}

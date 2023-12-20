#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUMBER_OR_ITEMS 128
#define ITEM_NAME_SIZE 128

#define MAX(a,b) (((a) > (b))?(a):(b))

void knapsack(char** nArr, int* wArr, int* vArr, int maxW) {

	int arr[NUMBER_OR_ITEMS][maxW+1];

	memset(arr, 0, sizeof(arr));

	for (int i = 1; i < NUMBER_OR_ITEMS; i++) {
		for (int j = 0; j < maxW+1; j++) {
			if (wArr[i] > j) {
				arr[i][j] = arr[i-1][j];
			} else {
				arr[i][j] = MAX(arr[i-1][j], arr[i-1][j-wArr[i]] + vArr[i]);
			}
		}
	}

	/*
	int j = maxW;
	int nextV = arr[NUMBER_OR_ITEMS-1][j];
	int iVal = 0;
	int finalWeight = 0;

	for (int i = NUMBER_OR_ITEMS-1; i > 0; i--) {
		//printf("...%d (%d, %d) ?= %d\n", arr[i][j], i, j, arr[i-1][j]);
		if (arr[i][j] != arr[i-1][j]) {
			iVal = arr[i][j] - arr[i-1][j];
			//printf(" IVAL: %d\n", iVal);
			for (int k = NUMBER_OR_ITEMS-1; k >= 0; k--) {
				if (vArr[k] == iVal) {
					printf("%s, %d, %d", nArr[k], wArr[k], vArr[k]);
					finalWeight += wArr[k];
					break;
				}
			}
			nextV -= arr[i][j];
			for (int k = j; k > 0; k--) {
				//printf("%d (%d, %d) == %d\n", arr[i][k]);
				if (arr[i][k] == nextV) {
					j = k;
					//printf("%d\n", j);
					break;
				}
			}
			//printf("%d\n", arr[i][j]);
		}
	}*/


	int i = NUMBER_OR_ITEMS-1;
	int j = maxW;

	int iArr[NUMBER_OR_ITEMS];
	memset(iArr, 0, sizeof(iArr));

	while (i > 0 && j > 0) {
		//printf("I: %d | J: %d\n", i, j);
		//printf("bot: %d | top: %d\n", arr[i][j], arr[i-1][j]);
		if (arr[i][j] == arr[i-1][j]) {
			// item is not in knapsack
			i--;
		} else {
			// item is in knapsack
			iArr[i] = 1;
			//printf("%s, %d, %d", nArr[i], wArr[i], vArr[i]);
			j -= wArr[i];
			i--;
		}
	}

	for (int i = 0; i < NUMBER_OR_ITEMS; i++) {
		if (iArr[i]) {
			printf("%s, %d, %d", nArr[i], wArr[i], vArr[i]);
		}
	}

	printf("\nfinal weight: %d\nfinal value: %d\n", (maxW-j), arr[NUMBER_OR_ITEMS-1][maxW]);
	
	// for printing table
	/*
	for (int i = 0; i < NUMBER_OR_ITEMS; i++) {
		printf("\n");
		for (int j = 0; j < maxW+1; j++) {
			printf("%d ", arr[i][j]);
		}
	}*/
	
	
}

int main() {

	clock_t start = clock();
	double timeSeconds = 0;
	double timeMicroseconds = 0;

	int maxWeight = 0;
	char** itemNameArr = calloc(NUMBER_OR_ITEMS, sizeof(char*));
	for (int i = 0; i < NUMBER_OR_ITEMS; i++) {
		itemNameArr[i] = calloc(ITEM_NAME_SIZE, sizeof(char));
	}

	int* weightArr = calloc(NUMBER_OR_ITEMS, sizeof(int));
	int* valueArr = calloc(NUMBER_OR_ITEMS, sizeof(int));

	// read input
	scanf("%d\n", &maxWeight);

	char temp;
	int j;
	for (int i = 0; i < NUMBER_OR_ITEMS; i++) {
		j = 0;
		while (j <= ITEM_NAME_SIZE) {
			scanf("%c", &temp);
			if (temp == ';') {
				break;
			}
			itemNameArr[i][j] = temp;
			j++;
		}
		scanf("%d;%d", &weightArr[i], &valueArr[i]);
	}

	knapsack(itemNameArr, weightArr, valueArr, maxWeight);

	// clean-up
	free(itemNameArr);
	free(weightArr);
	free(valueArr);

	timeSeconds = (double)(clock() - start) / CLOCKS_PER_SEC;
	timeMicroseconds = timeSeconds * 1000000.0;
	printf("time taken in microseconds: %f\n", timeMicroseconds);
	return 0;
}
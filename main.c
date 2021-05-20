/**
 * @file main.c
 * @author Bruno Silva
 * 
 * @brief Provides an example program that tests the quality of the 
 * "hashing" of a hash function, by simulating the distribution of randomly 
 * generated hashing keys (int type) into a hash table.
 * 
 * Please note that it is not guaranteed the generation of unique keys 
 * (the insertion of which does not result in collision). 
 * Anyway, the probability is low, given the range of values used. 
 * 
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define PRINTTABLE true /* print resulting hashtable? */
#define NUMBER_GENERATED_KEYS 10000

/* Values to vary during experimentation: */

#define MULTIPLIER 3
#define HASHTABLE_SIZE 51

/* No need to change anything below this line. */

int generateRandomKey();
int hashFunction(int key, int tableSize);

/* the insertion of the elements in the different buckets will be
 simulated through a table (array) of counters!*/
int main() {
	srand(time(NULL));

	int hashtable[HASHTABLE_SIZE] = { 0 };

	/* Number of detected collisions */
	int collisions = 0;

	/* Generates random keys, calls hash function and increases the 
	corresponding counter (simulating) an insertion*/
	for (int i = 0; i < NUMBER_GENERATED_KEYS; i++) {
		int key = generateRandomKey();
		int bucket = hashFunction(key, HASHTABLE_SIZE);

		if (hashtable[bucket] > 0) collisions++;
		
		hashtable[bucket]++;
	}
	
	/* Prints the counters, showing efectively the number of 
	keys distributed per "bucket" (e.g., table position) */
	if (PRINTTABLE) {
		printf("HASHTABLE DISPERSION COUNTER: \n");
		for (int i = 0; i < HASHTABLE_SIZE; i++) {
			printf("\tBucket: %d -> Keys: %d \n", i, hashtable[i]);
		}
		printf("----------------------------- \n");
	}
		
	/*Some statistical calculations will be performed in order to be more 
	objective instead of just observing the obtained dispersion.*/
	double mean = 0, std = 0;
	int emptyBuckets = 0;
	for (int i = 0; i < HASHTABLE_SIZE; i++) {
		mean += hashtable[i];
		if (hashtable[i] == 0) emptyBuckets++; /* take advantage of this cycle*/
	}
	mean /= HASHTABLE_SIZE;

	for (int i = 0; i < HASHTABLE_SIZE; i++) {
		std += (mean - hashtable[i]) * (mean - hashtable[i]);
	}
	std /= HASHTABLE_SIZE-1; 
	std = sqrt(std);
	
	printf("STATS: \n");
	printf("Collisions: %d | Empty: %d | Mean: %.3f | Standard Deviation: %.3f \n", collisions, emptyBuckets, mean, std);
	
	return EXIT_SUCCESS;
}

int generateRandomKey() {
	/* vamos gerar chaves no intervalo [0, 9999999]*/
	return rand() % 10000000;
}
int hashFunction(int key, int tableSize) {
	return (key * MULTIPLIER) % tableSize;
}
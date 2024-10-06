#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "lcg.h"

int main(void)
{
	struct lcg my_lcg;
	uint32_t num_iterations = 10;
	float mean = 0.0;
	float stddev = 1.0;

	/* Initialize the LCG */
	lcg_init(&my_lcg, NULL);

	printf("Linear Congruential Generator Test\n");
	printf("-----------------------------------\n");

	/* Generate and print a few random integer values */
	printf("Random integer values:\n");
	for (int i = 0; i < num_iterations; i++)
		printf("%u\n", lcg_next(&my_lcg));

	/* Generate and print a few random real values in [0, 1) */
	printf("\nRandom real values in [0, 1):\n");
	for (int i = 0; i < num_iterations; i++)
		printf("%f\n", lcg_next_real(&my_lcg));

	/* Generate and print a few random Gaussian values */
	printf("\nRandom Gaussian values with mean %f and stddev %f:\n", mean,
	       stddev);
	for (int i = 0; i < num_iterations; i++)
		printf("%f\n", lcg_next_gaussian(&my_lcg, mean, stddev));

	return 0;
}

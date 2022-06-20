#include <stdio.h>

void main() {
	int i, j;
	int num_partition, process_size;
	int smallest, largest, best_fit_i, worst_fit_i;
	int partition[25];

	printf("Enter no of partitions : ");
	scanf("%d", &num_partition);

	printf("Enter process size for first fit : ");
	scanf("%d", &process_size);

	printf("Enter size of blocks one by one\n");
	for(i=0; i<num_partition; i++) {
		scanf("%d", &partition[i]);
	}

	for(i=0; i<num_partition; i++) {
		if (partition[i] >= process_size) {
			break;
		}
	}

	if(i<num_partition) {
		partition[i] = partition[i] - process_size;

		printf("Process size found in partition %d for first fit\n", i);
	} else {
		printf("No required partition size found for first fit\n");
	}

	printf("Enter the process size for best fit : ");
	scanf("%d", &process_size);

	for(i=0; i<num_partition; i++) {
		if(partition[i] >= process_size) {
			smallest = partition[i];
			best_fit_i = i;
			break;
		}
	}

	if(i==num_partition) {
		printf("No required partition size found for best fit\n");
	} else {
		for(j=i; j<num_partition; j++) {
			if(partition[j] == process_size) {
				best_fit_i = j;
				break;
			} else if(partition[j] > process_size) {
				if(partition[j] < smallest) {
					smallest = partition[j];
					best_fit_i = j;
				}
			}
		}

		partition[j] = partition[j] - process_size;
		printf("Process size found in partition %d for best fit\n", best_fit_i);
	}

	printf("Enter process size for worst fit : ");
	scanf("%d", &process_size);

	for(i=0; i<num_partition; i++) {
		if (partition[i] >= process_size) {
			largest = partition[i];
			worst_fit_i = i;
			break;
		}
	}

	if(i==num_partition) {
		printf("No required partition size found for worst fit\n");
	} else {
		for(j=i; j<num_partition; j++) {
			if(partition[j] > largest) {
				largest = partition[j];
				worst_fit_i = j;
			}
		}

		partition[j] = partition[j] - process_size;
		printf("Process size found in partition %d for worst fit\n", worst_fit_i);
	}
}

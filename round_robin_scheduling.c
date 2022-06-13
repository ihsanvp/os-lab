#include<stdio.h>
#include<stdlib.h>

void shift_left(int, int);
void readjust(void);

int arr[100], burst[100];
int num_process;

int main() {

	int i, slice,t, ttime;
	int tot_num_process;
	int waiting[100], turnaround[100];
	float tt_avg, wt_avg, tt_sum=0, wt_sum=0;

	printf("Enter the number of processes:");
	scanf("%d", &num_process);

	printf("Enter the burst time of each process\n");

	for(i=0; i<num_process; i++) {
		scanf("%d", &burst[i] );
	}

	printf("Enter the quantum slice:");
	scanf("%d", &slice);

	for(i=0; i<num_process; i++) {
		arr[i] = i;
	}

	tot_num_process = num_process;
	waiting[0] = 0;

	for(i=0; i<num_process; i++) {
		turnaround[i] = 0;
	}

	// finding out the waiting times of the processes
	for(i=1; i<num_process; i++) {

		if( burst[i-1] > slice) {
			ttime = slice;
		} else {
			ttime = burst[i-1];
		}

		waiting[i] = waiting[i-1] + ttime;
	}

	while (1) {
		if((t = (burst[arr[0]] - slice)) > 0) {
			shift_left(t, arr[0]);

			for (i=0; i < num_process ; i++) {
				turnaround[arr[i]] += slice;
			}
		} else {
			turnaround[arr[0]] += burst[arr[0]];

			for (i=1; i < num_process ; i++) {
				turnaround[arr[i]] += burst[arr[0]];
			}
			
			burst[arr[0]] = 0;
			num_process = num_process -1;
			readjust();
		}

		if(num_process == 0) {
			break;
		}
	}

	for (i=0; i<tot_num_process; i++) {
		wt_sum += waiting[i];
		tt_sum += turnaround[i];
	}

	wt_avg = wt_sum / tot_num_process;
	tt_avg = tt_sum / tot_num_process;

	printf("process num\twaiting time\tturnaround time\n" );
	for(i=0; i<tot_num_process; i++) {
		printf("%d\t\t%d\t\t%d\n", i, waiting[i], turnaround[i]);
	}

	printf("Average turnaround time : %f\n", tt_avg);
	printf("Average waiting time : %f\n", wt_avg);
}
void shift_left(int _t, int h) {

	int i;

	for( i =0; i <num_process -1; i++) {
		arr[i] = arr[i+1];
	}

	arr[num_process -1] = h;
	burst[h] = _t;
}

void readjust() {

	int i;

	for(i=0; i < num_process; i++) {
		arr[i] = arr[i+1];
	}
}

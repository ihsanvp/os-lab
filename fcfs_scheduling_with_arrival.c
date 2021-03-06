#include <stdio.h>

typedef struct ProcessStruct {
	int pid;
	int bt;
	int at;
	int ct;
	int tt;
	int wt;
} process ;

void main() {
	int n, i, j;
	float tt_avg, wt_avg, tt_sum = 0, wt_sum = 0;
	process temp;

	printf("Enter no of process :");
	scanf("%d", &n);
	printf("\n");

	process p[n];

	// Read Burst Time
	printf("Enter BURST TIME\n");
	for (i=0; i<n; i++) {
		p[i].pid = i+1;
		printf("p%d (burst time) :", p[i].pid);
		scanf("%d", &p[i].bt);
	}
	printf("\n");

	// Read Arrival Time
	printf("Enter ARRIVAL TIME\n");
	for (i=0; i<n; i++) {
		printf("p%d (arrival time) :", p[i].pid);
		scanf("%d", &p[i].at);
	}
	printf("\n");

	// Sort based on AT
	for (i=0; i<n; i++) {
		for (j=0; j<n-i-1; j++) {
			if (p[j].at > p[j+1].at) {
				temp = p[j + 1];
				p[j + 1] = p[j];
				p[j] = temp;	
			}
		}
	}

	// Calculate  Completion Time
	p[0].ct = p[0].bt;
	for (i=1; i<n; i++) {
		p[i].ct = p[i-1].ct + p[i].bt;
	}
	
	// Calculate Turnaround Time
	for (i=0; i<n; i++) {
		p[i].tt = p[i].ct - p[i].at;
		tt_sum += p[i].tt;
	}

	// Calculate Waiting Time
	for (i=0; i<n; i++) {
		p[i].wt = p[i].tt - p[i].bt;
		wt_sum += p[i].wt;
	}

	// Calculate Average
	tt_avg = tt_sum / n;
	wt_avg = wt_sum / n;

	// Print Output
	printf("%-10s %-10s %-10s %-10s %-10s %-10s\n", "PID", "BT", "AT", "TT", "WT", "CT");
	for (i=0; i<n; i++) {
		printf("%-10d %-10d %-10d %-10d %-10d %-10d\n", p[i].pid, p[i].bt, p[i].at, p[i].tt, p[i].wt, p[i].ct);
	}
	printf("---------------------------------\n");
	printf("Avg TT : %f\n", tt_avg);
	printf("Avg WT : %f\n", wt_avg);
}

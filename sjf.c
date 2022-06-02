#include <stdio.h>

typedef struct process_struct {
	int pid;
	int bt;
	int ct;
	int tt;
	int wt;
} process ;

void main() {
	printf("SJF\n");

	int n, i, j;
	float tt_avg, wt_avg, tt_sum = 0, wt_sum = 0;
	process temp;

	printf("Enter no of process :");
	scanf("%d", &n);

	process p[n];

	// read process id
	printf("Enter %d id :", n);
	for (i=0; i<n; i++) {
		scanf("%d", &p[i].pid);
	}

	// read burst time
	printf("Enter %d burst time :", n);
	for (i=0; i<n; i++) {
		scanf("%d", &p[i].bt);
	}

	// sort based on burst time
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			if (p[j].bt > p[j+1].bt) {
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;		
			}
		}
	}

	// calculate completion time
	p[0].ct = p[0].bt;
	for (i=1; i<n; i++) {
		p[i].ct = p[i-1].ct + p[i].bt;
	}

	// calculate turnaround time	
	for (i=0; i<n; i++) {
		p[i].tt = p[i].ct;
		tt_sum += p[i].tt;
	}

	// calculate waiting time
	for (i=0; i<n; i++) {
		p[i].wt = p[i].tt - p[i].bt;
		wt_sum += p[i].wt;
	}

	// calculate average
	tt_avg = tt_sum / n;
	wt_avg = wt_sum / n;

	// Print Output
	printf("------------------------------------------------\n");
	printf("%-10s %-10s %-10s %-10s %-10s\n", "PID", "BT", "TT", "WT", "CT");
	for (i=0; i<n; i++) {
		printf("%-10d %-10d %-10d %-10d %-10d\n", p[i].pid, p[i].bt, p[i].tt, p[i].wt, p[i].ct);
	}
	printf("------------------------------------------------\n");
	printf("Avg TT : %f\n", tt_avg);
	printf("Avg WT : %f\n", wt_avg);


	
}

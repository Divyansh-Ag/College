#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
struct process{
	int burst_time, priority, arrival_time, flag, rem_time, ct, tat, wt, cpu, rt, id, cot;
}p[10];

void main(){
	int i, n, tot_time = 0, highest;
	printf("Enter the number of processes\t");
	a:scanf("%d", &n);
	if(n>8 && n<1)
		goto a;
	for(i=0;i<n;i++){
		printf("Enter Arrival time for %d\t", i+1);
		scanf("%d", &p[i].arrival_time);
		printf("Enter burst time for %d\t\t", i+1);
		scanf("%d", &p[i].burst_time);
		p[i].rem_time = p[i].burst_time;
		printf("Enter priority for %d\t\t", i+1);
		scanf("%d", &p[i].priority);
		tot_time += p[i].burst_time;
		tot_time += p[i].arrival_time;
		p[i].flag = -1;
		p[i].id = i+1;
		p[i].cot = 0;
	}
	
	
	int j;
	struct process temp;
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++){
			if(p[i].arrival_time > p[j].arrival_time){
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
	
	
	p[9].priority = 999;
	p[9].rem_time = 9999;
	p[9].flag = -1;
	int prev_id, first = 1;
	int last = 0;
	system("CLS");
	printf("GHANTT CHART\n\n");
	int cur_time = p[0].arrival_time;
	printf("\n|");
	while(cur_time < 100){
		highest = 9;
		
		for(i=0;i<n;i++){                                       	 									//priority increase 
			if(cur_time - p[i].cot >= 2){
				if(p[i].flag == -2){
					p[i].priority -= 2;	
				}
			}
		}
		
		for(i=0;i<n;i++){  																				//process selection
			if(p[i].rem_time > 0){
				if(p[i].priority < p[highest].priority){
					if(p[i].arrival_time <= cur_time){
						highest = i;
					}
				}
			}
		}
		
		//printf("Selected P%d\n", p[highest].id);
		
		if(p[highest].flag == -2){
			p[highest].flag = -1;
		}
		
		if(p[highest].id != p[prev_id].id){
			p[prev_id].flag = -2;
			p[prev_id].cot = cur_time;
			if(p[highest].id != 0)
				printf("%d - |", cur_time);
			cur_time += 2;
		}
		
		if(p[highest].flag == -1){
			p[highest].flag = 0;
			p[highest].cpu = cur_time;
		}
		
		if(p[highest].id != 0)
			printf("%d P%d |", cur_time, p[highest].id);
		
		prev_id = highest;
		p[highest].rem_time--;
		cur_time++;
		
		//printf("Current time %d\n", cur_time);
		
		if(p[highest].rem_time == 0 && p[highest].id != 0){
			p[highest].flag = 1;
			p[highest].ct = cur_time;
			p[highest].tat = p[highest].ct - p[highest].arrival_time;
			p[highest].wt = p[highest].tat - p[highest].burst_time;
			p[highest].rt = p[highest].cpu - p[highest].arrival_time;
			last = highest;
			continue;
		}
	}
	printf("%d", p[last].ct);
	printf("\n\n\nProcess\t\tAT\tBT\tCT\tTAT\tWT\tRT\n");
	for(i=0;i<n;i++){
		printf("%d\t\t%d\t%d\t%d\t%d\t%d\t%d\n", i+1, p[i].arrival_time, p[i].burst_time, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
	}
}

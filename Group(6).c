#include<stdio.h>

//Function prototype
int MainMenu_Function (void);
int Sub_Menu_Func_1(void);
int Sub_Menu_Func_2(void);
float RR(int, int [], int, int, int);
float outcome(int, int [], int [], int [], int [], int []);
float SJF(int , int [] , int, int[]);
float outcomeSJF(int, int[], int[], int[], int[], int []);
float avg_turnaround_waiting(int [], int);
void algo_comparison_outcome(int [], float []);


int main(void)
{
	//Declare universal variable
    int MainMenu_choice;

    do
	{
        int SubMenu_1, SubMenu_2, SubMenu3;
        int processID[20] = {0};//for SJF
        int process, num_of_processes, time_quantum;
        int static arrival_time = 0;
        int arr_burst_time[20] = {0}, arr_arrival_time[20] = {0};
        int arr_schedule_algo[3] = {0}; //[0] - SJF, [1] - RR no overhead, [2] - RR with overhead
        float avg_turnaround_time[3] = {0}; //[0] - store avg turnaround of SJF, [1] - RR no overhead, [2] - RR with overhead

        system("cls"); //Clear screen
        MainMenu_choice = MainMenu_Function();

        if (MainMenu_choice == 4)
        {
        	break;
        }
        else if (MainMenu_choice == 1) //Main Menu -> Option 1 sub menu
		{
			SubMenu_1 = Sub_Menu_Func_1();

			//can be converted into a function for user input by using pointer
            //user input for the no. of process, burst time & quantum time
            if(SubMenu_1 == 4)
			{
				continue;
			}
			else
			{
				arr_schedule_algo[SubMenu_1 - 1] = 1;
			}
		}
		else
		{
			//assume MainMenu_choice == 3 first
			int a = 0;
			do
			{
				arr_schedule_algo[a] = 1;
				a++;
			} while (a < 4);

			if (MainMenu_choice == 2) //Main Menu -> Option 2 sub menu
            {
				SubMenu_2 = Sub_Menu_Func_2();

	            if(SubMenu_2 == 4)
				{
					continue;
				}
				else
				{
					if (SubMenu_2 == 1) // SFJ && RR without
					{
						arr_schedule_algo[2] = 0;
					}
					else if (SubMenu_2 == 2) // SFJ && RR with
					{
						arr_schedule_algo[1] = 0;
					}
					else // both RR
					{
						arr_schedule_algo[0] = 0;
					}
				}
            }
		}

		printf("\n-------------------");

		//User input number of process
		do
		{
			printf("\nEnter the number of process: ");
			scanf("%d", &num_of_processes); //program will crash if key in non numeric input

			if (num_of_processes < 1)
			{
				printf("Sorry, invalid input.\n");
			}
			else if (num_of_processes > 20)
			{
				printf("Sorry the number of processes exceeded the max workload limit.\n");
			}
		} while (num_of_processes > 10 || num_of_processes < 1);

		//Get burst time
	    for(process = 0; process < num_of_processes; process++)
	    {
	    	printf("\nWhat is the Burst Time for Process %d?\n", process + 1);

		    printf("Burst Time: ");
		    scanf("%d", &arr_burst_time[process]);

		    processID[process] = process+1;
	    }

	    if (arr_schedule_algo[1] == 1 || arr_schedule_algo[2] == 1)
	    {
	    	printf("\nHow long is the Time Quantum? ");
			scanf("%d", &time_quantum);
	    }

	    system("cls"); //Clear screen

		printf("Arrival time of all workload is at time = 0.\n");
		printf("\n-------------------\n");
		
	    if (arr_schedule_algo[1] == 1) //RR without overhead
	    {
			avg_turnaround_time[1] = RR(num_of_processes, arr_burst_time, arrival_time, time_quantum, 0);
	    }

	    if (arr_schedule_algo[2] == 1) //RR with overhead
    	{
	    	avg_turnaround_time[2] = RR(num_of_processes, arr_burst_time, arrival_time, time_quantum, 1);
    	}
    	
    	if (arr_schedule_algo[0] == 1) // SJF
	    {
  		 	avg_turnaround_time[0] = SJF(num_of_processes, arr_burst_time, arrival_time, processID);
	    }

		//Compare algorithms
		if (MainMenu_choice != 1)
		{
			algo_comparison_outcome(arr_schedule_algo, avg_turnaround_time);
		}

		printf("Do you want to exit?\n\n");
		printf("Option 1: Exit\n");
		printf("Option 2: Restart\n");

		do
		{
			printf("\nPlease make a selection: ");
   			scanf("%d", &MainMenu_choice);  //program will crash if key in non numeric input

	   		if (MainMenu_choice < 1 || MainMenu_choice > 2)
	   		{
	   			printf("Invalid option\n");
	   		}
		} while (MainMenu_choice < 1 || MainMenu_choice > 2);

		if (MainMenu_choice == 1)
		{
			MainMenu_choice = 4;
		}

    } while(MainMenu_choice !=4); //end program
}


//Main Menu function
int MainMenu_Function(void)
{
	int MainMenu_choice;

    printf("------ MAIN MENU ------");

    printf("\nHow many Process Scheduling Algorithms do you want to use to handle the workload?\n");

    printf("\nOption 1: Run on 1 process scheduling algorithm.\n");
    printf("Option 2: Run on 2 process scheduling algorithms.\n");
    printf("Option 3: Run on 3 process scheduling algorithms and compare.\n");
    printf("Option 4: EXIT\n");

	do
	{
		printf("\nPlease make a selection: ");
   		scanf("%d", &MainMenu_choice);  //program will crash if key in non numeric input

   		if (MainMenu_choice < 1 || MainMenu_choice > 4)
   		{
   			printf("Invalid option\n");
   		}
	} while (MainMenu_choice < 1 || MainMenu_choice > 4);

    return MainMenu_choice;
}


//Main Menu -> Option 1 sub menu function
int Sub_Menu_Func_1(void)
{
	int SubMenu_1 = 0;

	printf("\n-------------------\n");
    printf("Which Process Scheduling Algorithms do you want to use to handle the workload?\n");
    printf("\nOption 1: Shortest Job First (SJF) Non-Preemptive Version\n");
    printf("Option 2: Round Robin (RR) without Overhead\n");
    printf("Option 3: Round Robin (RR) with Overhead\n");
    printf("Option 4: Go back to Main Menu\n");

	do
	{
		printf("\nPlease make a selection: ");
   		scanf("%d", &SubMenu_1);  //program will crash if key in non numeric input

   		if (SubMenu_1 < 1 || SubMenu_1 > 4)
   		{
   			printf("Invalid option\n");
   		}
	} while (SubMenu_1 < 1 || SubMenu_1 > 4);

    return SubMenu_1;
}


//Main Menu -> Option 2 sub menu function
int Sub_Menu_Func_2(void)
{
	int SubMenu_2 = 0;

	printf("\n-------------------\n");
    printf("Which combination of 2 Process Scheduling Algorithms do you want to use to handle the workload?\n");
    printf("\nOption 1: Shortest Job First (SJF) Non-Preemptive Version & Round Robin (RR) without Overhead\n");
    printf("Option 2: Shortest Job First (SJF) Non-Preemptive Version & Round Robin (RR) with Overhead\n");
    printf("Option 3: Round Robin (RR) with Overhead & Round Robin (RR) without Overhead\n");
    printf("Option 4: Go back to Main Menu\n");

	do
	{
		printf("\nPlease make a selection: ");
   		scanf("%d", &SubMenu_2);  //program will crash if key in non numeric input

   		if (SubMenu_2 < 1 || SubMenu_2 > 4)
   		{
   			printf("Invalid option\n");
   		}
	} while (SubMenu_2 < 1 || SubMenu_2 > 4);

    return SubMenu_2;
}


//RR
float RR(int num_of_processes, int burst_time[], int arrival_time, int time_quantum, int overhead)
{
	int process, time = 0, no_process_done = 0;
	int static overhead_time = 10;
	int waiting_time[20] = {0}, remainding_time[20] = {0}, completion_time[20] = {0}, turnaround_time[20] = {0}, completion_order[20] = {0};
	float avg_turnaround_time;

	for (process = 0; process < num_of_processes; process++)
	{
		remainding_time[process] = burst_time[process];
	}

	do
	{
		for (process = 0; process < num_of_processes; process++)
		{
			if (remainding_time[process] == burst_time[process]) //First cycle of process
			{
				waiting_time[process] = time;
			}

			if (remainding_time[process] > time_quantum) //Not last cycle of process
			{
				remainding_time[process] -= time_quantum;
				time += time_quantum;
				if (overhead == 1) //RR with overhead
				{
					time += overhead_time;
				}
			}
			else if (remainding_time[process] != 0) //Last cycle of process
			{
				time += remainding_time[process];
				completion_time[process] = time;
				turnaround_time[process] = completion_time[process] - arrival_time; //Calculate turnaround time
				remainding_time[process] = 0;
				if (overhead == 1) //RR with overhead
				{
					time += overhead_time;
				}

				completion_order[no_process_done] = process+1; //keep track of the order of process that are completed

				no_process_done++; //counter to keep track the number of processes are completed
			}
		}
	} while (no_process_done != num_of_processes);

	//Display output
	if (overhead == 0)
	{
		printf("Round Robin without Overhead");
	}
	else
	{
		printf("Round Robin with Overhead\n");
		printf("Overhead time = 10 (fixed in this program)");
	}
	printf("\nTime Quantum = %d", time_quantum);
	
	avg_turnaround_time = outcome(num_of_processes, burst_time, waiting_time, completion_time, turnaround_time, completion_order);

	return avg_turnaround_time;
}

//SJF
float SJF(int num_of_processes, int burst_time[], int arrival_time, int ID[])
{
	int x, y, first = 0, process, i, j, swap;
	int waiting_time[20] = {0}, turnaround_time[20] = {0}, completion_time[20] = {0};
	float avg_turnaround_time;

	//sort burst time
	//bubble sort
	for (x = 0; x < num_of_processes - 1; x++)
	{
		for (y= 0; y < num_of_processes - x - 1; y++)
		{
			if (burst_time[y] > burst_time[y+1])
			{			
				//swap the burst_time
				swap = burst_time[y];
				burst_time[y] = burst_time[y+1];
				burst_time[y+1] = swap;

				//swap the ID
				swap = ID[y];
				ID[y] = ID[y+1];
				ID[y+1] = swap;
			}
		}
	}

	waiting_time[first] = 0;//waiting time for first process is always zero

	//calculate waiting time
	for (i = 1; i < num_of_processes; i++)
	{
		waiting_time[i] = 0;
		for (j=0; j < i; j++)
		{
			waiting_time[i] += burst_time[j];
		}
	}

	//Calculate turnaround time and completion time
	for (process = 0; process < num_of_processes; process++)
	{
		turnaround_time[process] = burst_time[process] + waiting_time[process];
		completion_time[process] = burst_time[process] + waiting_time[process] + arrival_time;
	}

	//Display output
	printf("Shortest Job First (SJF) Non-Preemptive Version\n\n");

	avg_turnaround_time = outcomeSJF(num_of_processes, burst_time, waiting_time, completion_time, turnaround_time, ID);
	
	return avg_turnaround_time;
}


//Display output
float outcomeSJF(int num_of_processes, int burst_time[], int waiting_time[], int completion_time[], int turnaround_time[], int ID[])
{
	int process;
	float avg_time, avg_turnaround_time;

	printf("\t\tBurst Time\tWaiting Time\tCompletion Time\t   Turnaround Time\n");
	for (process = 0; process < num_of_processes; process++)
	{
		printf("Process %d\t%d\t\t%d\t\t%d\t\t   %d\n", ID[process], burst_time[process], waiting_time[process], completion_time[process], turnaround_time[process]);
	}

	avg_turnaround_time = avg_turnaround_waiting(turnaround_time, num_of_processes);
	printf("\nAverage Turnaround Time: %.4f", avg_turnaround_time);

	avg_time = avg_turnaround_waiting(waiting_time, num_of_processes);
	printf("\nAverage Waiting Time: %.4f\n\n", avg_time);
	printf("___________________\n");
	
	return avg_turnaround_time;
}


//Display output
float outcome(int num_of_processes, int burst_time[], int waiting_time[], int completion_time[], int turnaround_time[], int ID[])
{
	int count, process;
	float avg_turnaround_time;

	printf("\n\n\t\tBurst Time\tWaiting Time\tCompletion Time\t   Turnaround Time\n");
	for (count = 0; count < num_of_processes; count++)
	{
		process = ID[count] - 1;
		printf("Process %d\t%d\t\t%d\t\t%d\t\t   %d\n", process + 1, burst_time[process], waiting_time[process], completion_time[process], turnaround_time[process]);
	}

	avg_turnaround_time = avg_turnaround_waiting(turnaround_time, num_of_processes);
	//Calculate average turnaround time
	printf("\nAverage Turnaround Time: %.4f", avg_turnaround_time);

	//Calculate average waiting time
	printf("\nAverage Waiting Time: %.4f\n\n", avg_turnaround_waiting(waiting_time, num_of_processes));
	printf("___________________\n");

	return avg_turnaround_time;
}


//Calculate average turnaround/waiting time
float avg_turnaround_waiting(int time[], int num_of_processes)
{
	int process;
	float avg = 0;

	for (process = 0; process < num_of_processes; process++)
	{
		avg += time[process];
	}

	return avg/num_of_processes;
}


//Algorithm comparison
//Only compare average turnaround time, as TAT increases as waiting time increases (TAT = waiting time + burst time)
void algo_comparison_outcome(int algo[], float avg_turnaround_time[])
{
	int counter, best;

	//Get first scheduling algorithm that is being compared
	for (counter = 0; counter < 3; counter++)
	{
		if (algo[counter] == 1)
		{
			best = counter;
			break;
		}
	}

	//Compare average time
	for (counter = best+1; counter < 3; counter++)
	{
		if (algo[counter] == 1)
		{
			if (avg_turnaround_time[best] > avg_turnaround_time[counter])
			{
				best = counter;
			}
		}
	}

	printf("\nThe best algorithm for this workload: ");
	switch (best)
	{
		case 0: printf("Shortest Job First (SJF) Non-Preemptive Version"); break;
		case 1: printf("Round Robin without Overhead"); break;
		case 2: printf("Round Robin with Overhead");
	}

	printf("\n\n-------------------\n");
}

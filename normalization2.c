// program to normalize the link speed

//Input Link Speed Limits
#define INPUT_LINK1_SPEED 20
#define INPUT_LINK2_SPEED 16
#define INPUT_LINK3_SPEED 15
#define INPUT_LINK4_SPEED 12
#define INPUT_LINK5_SPEED 10
#define INPUT_LINK6_SPEED 6

//Output Link Speed Limits
#define OUTPUT_LINK1_SPEED 20
#define OUTPUT_LINK2_SPEED 10
#define OUTPUT_LINK3_SPEED 5
#define OUTPUT_LINK4_SPEED 14
#define OUTPUT_LINK5_SPEED 13
#define OUTPUT_LINK6_SPEED 6

//Static sleep time for Thread 1
//#define THREAD1_SLEEP 10

#include<stdio.h>
#include "cn2simulator.h"
#include "read_input_file.h"

int input_thread1_slp_time = 10;
int input_thread2_slp_time = 0;
int input_thread3_slp_time = 0;
int input_thread4_slp_time = 0;
int input_thread5_slp_time = 0;
int input_thread6_slp_time = 0;

int output_thread1_slp_time = 10;
int output_thread2_slp_time = 0;
int output_thread3_slp_time = 0;
int output_thread4_slp_time = 0;
int output_thread5_slp_time = 0;
int output_thread6_slp_time = 0;

pthread_t input_thread1, input_thread2, input_thread3, input_thread4, input_thread5, input_thread6;

void calculate_threads_slp_times()
{
	short total_rate = 0, total_input_rate = 0, total_output_rate;

	total_input_rate = INPUT_LINK1_SPEED + INPUT_LINK2_SPEED + INPUT_LINK3_SPEED + INPUT_LINK4_SPEED + INPUT_LINK5_SPEED + INPUT_LINK6_SPEED;
	total_output_rate = OUTPUT_LINK1_SPEED + OUTPUT_LINK2_SPEED + OUTPUT_LINK3_SPEED + OUTPUT_LINK4_SPEED + OUTPUT_LINK5_SPEED + OUTPUT_LINK6_SPEED;
	total_rate = total_input_rate + total_output_rate;

	if (0==total_rate)
	{
		fprintf(logfile, "All Link speed 0, nothing can be processed, Exiting Simulator...\n");
		exit(0);
	}

	input_thread2_slp_time = (INPUT_LINK1_SPEED/INPUT_LINK2_SPEED) * input_thread1_slp_time;
	input_thread3_slp_time = (INPUT_LINK1_SPEED/INPUT_LINK3_SPEED) * 	input_thread1_slp_time;
	input_thread4_slp_time = (INPUT_LINK1_SPEED/INPUT_LINK4_SPEED) * input_thread1_slp_time;
	input_thread5_slp_time = (INPUT_LINK1_SPEED/INPUT_LINK5_SPEED) * input_thread1_slp_time;
	input_thread6_slp_time = (INPUT_LINK1_SPEED/INPUT_LINK6_SPEED) * input_thread1_slp_time;

	output_thread2_slp_time = (OUTPUT_LINK1_SPEED/OUTPUT_LINK2_SPEED) * output_thread1_slp_time;
	output_thread3_slp_time = (OUTPUT_LINK1_SPEED/OUTPUT_LINK3_SPEED) * output_thread1_slp_time;
	output_thread4_slp_time = (OUTPUT_LINK1_SPEED/OUTPUT_LINK4_SPEED) * output_thread1_slp_time;
	output_thread5_slp_time = (OUTPUT_LINK1_SPEED/OUTPUT_LINK5_SPEED) * output_thread1_slp_time;
	output_thread6_slp_time = (OUTPUT_LINK1_SPEED/OUTPUT_LINK6_SPEED) * output_thread1_slp_time;

	printf("input_thread1_slp_time :%d\n", input_thread1_slp_time);
	printf("input_thread2_slp_time :%d\n", input_thread2_slp_time);
	printf("input_thread3_slp_time :%d\n", input_thread3_slp_time);
	printf("input_thread4_slp_time :%d\n", input_thread4_slp_time);
	printf("input_thread5_slp_time :%d\n", input_thread5_slp_time);
	printf("input_thread6_slp_time :%d\n", input_thread6_slp_time);

	printf("output_thread1_slp_time :%d\n", output_thread1_slp_time);
	printf("output_thread2_slp_time :%d\n", output_thread2_slp_time);
	printf("output_thread3_slp_time :%d\n", output_thread3_slp_time);
	printf("output_thread4_slp_time :%d\n", output_thread4_slp_time);
	printf("output_thread5_slp_time :%d\n", output_thread5_slp_time);
	printf("output_thread6_slp_time :%d\n", output_thread6_slp_time);


}

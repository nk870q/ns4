/*
 ============================================================================
 Name        : simulatorCN2.c
 Author      : saroj
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "cn2simulator.h"
#include "read_input_file.h"

int input_thread1_slp_time = 0;
int input_thread2_slp_time = 0;
int input_thread3_slp_time = 0;

int output_thread1_slp_time = 0;
int output_thread2_slp_time = 0;
int output_thread3_slp_time = 0;

//3 Threads to simulate 3 links and process data from the 3 buffers
pthread_t input_thread1, input_thread2, input_thread3;

FILE *logfile=NULL;

void log_message()
{

}


/*This function calculates the relative speed of each link based on rate
 * limit input and transfers that to packet limit processing at a time from
 * each link
 */
void calculate_threads_slp_times()
{
	short total_rate =0, total_input_rate =0, total_output_rate;

	total_input_rate = INPUT_LINK1_SPEED + INPUT_LINK2_SPEED + INPUT_LINK3_SPEED;
	total_output_rate = OUTPUT_LINK1_SPEED + OUTPUT_LINK2_SPEED + OUTPUT_LINK3_SPEED;
	total_rate = total_input_rate + total_output_rate;

	if (0==total_rate)
	{
		fprintf(logfile, "All Link speed 0, nothing can be processed, Exiting Simulator...\n");
		exit(0);
	}

	input_thread1_slp_time = (total_rate/INPUT_LINK1_SPEED) * MULTIPLIER;
	input_thread2_slp_time = (total_rate/INPUT_LINK2_SPEED) * MULTIPLIER;
	input_thread3_slp_time = (total_rate/INPUT_LINK3_SPEED) * MULTIPLIER;

	output_thread1_slp_time = (total_rate/OUTPUT_LINK1_SPEED) * MULTIPLIER;
	output_thread2_slp_time = (total_rate/OUTPUT_LINK2_SPEED) * MULTIPLIER;
	output_thread3_slp_time = (total_rate/OUTPUT_LINK3_SPEED) * MULTIPLIER;

	printf("input_thread1_slp_time :%d\n", input_thread1_slp_time);
	printf("input_thread2_slp_time :%d\n", input_thread2_slp_time);
	printf("input_thread3_slp_time :%d\n", input_thread3_slp_time);

	printf("output_thread1_slp_time :%d\n", output_thread1_slp_time);
	printf("output_thread2_slp_time :%d\n", output_thread2_slp_time);
	printf("output_thread3_slp_time :%d\n", output_thread3_slp_time);


}

//Assigned - Navneet

/* Process each Ipv4 Packet - Navneet
 * Based on destination Ip, check the Ipv4 routing table and process the packet

*/

//Assigned - Navneet
int process_ipv4Packet(ipv4Packet *packet)
{
	int tbl_exist = FALSE;
	ipv4RoutingTable *ipv4Entry;
	if (ipv4Entry == NULL)
	{
		printf("No Routing Table, Unable to Process Packet\n");
		return tbl_exist;
	}
	else
	{
		ipv4Entry = ipv4RoutingTbl;
		while (ipv4Entry !=NULL)
		{
/*Check if there is an entry in Routing Table for the destination address in the packet
 *
 */
			if((ipv4Entry->info.dst_ntwrk[0] == packet->dest_ip[0] ) && \
			(ipv4Entry->info.dst_ntwrk[1] == packet->dest_ip[1]) && \
			(ipv4Entry->info.dst_ntwrk[2] == packet->dest_ip[2]) && \
			(ipv4Entry->info.dst_ntwrk[3] == packet->dest_ip[3]))
			{
				ipv4Enqueue((int)ipv4Entry->info.output_port_queue, packet);
				tbl_exist = TRUE;

			}
			else
				ipv4Entry = ipv4Entry->next;

		}
	}
	return tbl_exist;
}

/* Process each Ipv6 Packet -
 * Based on destination Ip, check the Ipv6 routing table and process the packet
 Assigned - Navneet
 */
int process_ipv6Packet(ipv6Packet *packet)
{
	return TRUE;
}



int main(void) {

	int status;

//Open the logfile for logging messages
	logfile  = fopen("log.txt", "w");
	if(NULL == logfile)
	{
		printf("No Disk space for logging, Exiting Simulator...\n");
		exit(0);

	}

	calculate_threads_slp_times();

//Read  3 files and store thr content in array
	Populate_Buffers();
	

	Populate_Routing_Tbls();
	
	printf("Starting Input Threads\n");
	status = start_input_threads();
	if (FALSE == status)
		printf("Could Not Start The Threads \n");

	pthread_join( input_thread1, NULL);
	pthread_join( input_thread2, NULL);
	pthread_join( input_thread3, NULL);


	return 0;
}

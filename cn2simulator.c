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
//#include "read_input_file.h"

int input_thread1_slp_time = 0;
int input_thread2_slp_time = 0;
int input_thread3_slp_time = 0;

int output_thread1_slp_time = 0;
int output_thread2_slp_time = 0;
int output_thread3_slp_time = 0;

//3 Threads to simulate 3 links and process data from the 3 buffers
pthread_t input_thread1, input_thread2, input_thread3;

FILE *outfile1 = NULL;
FILE *outfile2 = NULL;
FILE *outfile3 = NULL;

FILE *logfile=NULL;

FILE *pkt = NULL;

extern ipv4RoutingTable *ipv4RoutingTbl;
extern ipv6RoutingTable *ipv6RoutingTbl;

//Semaphore Names for each IPV4 Queue
extern sem_t ipv4_queue1_sem;
extern sem_t ipv4_queue2_sem;
extern sem_t ipv4_queue3_sem;

extern pthread_t output_thread1;
extern pthread_t output_thread2;
extern pthread_t output_thread3;


//Mutexes For each IPV4 Queue
extern pthread_mutex_t ipv4_queue1_mutex;
extern pthread_mutex_t ipv4_queue2_mutex;
extern pthread_mutex_t ipv4_queue3_mutex;




/*Packet counters for each thread to keep track of where to start processing
 * Next Packet. It will start from 0 and each tile incremented by pkt_lim
 * of that link till all the packets from that link is processed.
 */
int input_link1_pkt_count;
int input_link2_pkt_count;
int input_link3_pkt_count;

/*
char Buffer1[MAX_FILE1_SIZE][PACKECT_SIZE];
char Buffer2[MAX_FILE2_SIZE][PACKECT_SIZE];
char Buffer3[MAX_FILE3_SIZE][PACKECT_SIZE];

*/


unsigned char Buffer1[MAX_FILE1_SIZE][PACKECT_SIZE];
unsigned char Buffer2[MAX_FILE2_SIZE][PACKECT_SIZE];
unsigned char Buffer3[MAX_FILE3_SIZE][PACKECT_SIZE];


int readFile(char *fname, unsigned char buffer[][PACKECT_SIZE], int maxsize)
//int readFile(char *fname, char buffer[][PACKECT_SIZE], int maxsize)
{
	int pkt_count = 0;
	FILE *fptr=NULL;

//Open The Input File To Read in Binary Mode.
	fptr = fopen(fname, "rb");
	if(NULL==fptr)
	{
		printf("Could not open %s\n", fname);
		exit(0);
	}
	else
	{
		if (pkt_count < maxsize )
		{
			/*
			printf("Allocating Memory for buffer[%d]\n", pkt_count);

			buffer[pkt_count] = (char *)malloc(PACKECT_SIZE * sizeof(char));
			printf("Allocated Memory for buffer[%d]\n", pkt_count);

			*/

//			while(fread(buffer[pkt_count], sizeof(char), PACKECT_SIZE, fptr))
			while(fread(buffer[pkt_count], sizeof(unsigned char), PACKECT_SIZE, fptr))
			{
				printf("buffer[%d] : %s", pkt_count, buffer[pkt_count]);
				pkt_count++;
			}
		}
		else
		{
			printf("%s has more packets than defined, Ignoring extra Packets\n", fname);
		}
		if (0 == pkt_count)
		{
			printf("%s is empty", fname);
		}
		printf("Total No of Packets in %s : %d\n", fname, pkt_count);
	}

	return pkt_count;

}

//This function will read each input file till end of file is encountered
//and populate each buffer with the packets from the file.
void Populate_Buffers()
{

	input_link1_pkt_count = readFile(INPUT_FILE1_NAME, Buffer1, MAX_FILE1_SIZE);
	input_link2_pkt_count = readFile(INPUT_FILE2_NAME, Buffer2, MAX_FILE2_SIZE);
	input_link3_pkt_count = readFile(INPUT_FILE3_NAME, Buffer3, MAX_FILE3_SIZE);

	printf("input_link1_pkt_count :%d\n", input_link1_pkt_count);
	printf("input_link2_pkt_count :%d\n", input_link2_pkt_count);
	printf("input_link3_pkt_count :%d\n", input_link3_pkt_count);


}

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

void initialize_output_files()
{

	//Open The Output Files To Write in Binary Mode.
	outfile1 = fopen(IPV4_OUTPUT_FILE1_NAME, "wb");
	if(NULL == outfile1)
	{
		printf("Could not open %s\n", IPV4_OUTPUT_FILE1_NAME);
		exit(0);
	}

	outfile2 = fopen(IPV4_OUTPUT_FILE2_NAME, "wb");
	if(NULL == outfile2)
	{
		printf("Could not open %s\n", IPV4_OUTPUT_FILE2_NAME);
		exit(0);
	}
	outfile3 = fopen(IPV4_OUTPUT_FILE3_NAME, "wb");
	if(NULL == outfile1)
	{
		printf("Could not open %s\n", IPV4_OUTPUT_FILE3_NAME);
		exit(0);
	}
	//Open The Output Files To Write in Binary Mode.
	pkt = fopen("Packet", "wb");
	if(NULL == pkt)
	{
		printf("Could not open Packet\n");
		exit(0);
	}
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

	ipv4Entry = ipv4RoutingTbl;
	if (ipv4Entry == NULL)
	{
		printf("No Routing Table, Unable to Process Packet\n");
		return tbl_exist;
	}
	while (ipv4Entry !=NULL)
	{
/*Check if there is an entry in Routing Table for the destination address in the packet
 *
 */
/*		fprintf(pkt, "ipv4Entry->info.dst_ntwrk[0] : %02x\n", (unsigned) (unsigned char)ipv4Entry->info.dst_ntwrk[0]);
		fprintf(pkt, "packet->dest_ip[0] : %02x\n", packet->dest_ip[0]);
		
		fprintf(pkt, "ipv4Entry->info.dst_ntwrk[1] : %02x\n", (unsigned) (unsigned char)ipv4Entry->info.dst_ntwrk[1]);
		fprintf(pkt, "packet->dest_ip[1] : %02x\n", packet->dest_ip[1]);
		

		fprintf(pkt, "ipv4Entry->info.dst_ntwrk[2] : %02x\n", (unsigned) (unsigned char)ipv4Entry->info.dst_ntwrk[2]);
		fprintf(pkt, "packet->dest_ip[2] : %02x\n", packet->dest_ip[2]);
		
		fprintf(pkt, "ipv4Entry->info.dst_ntwrk[3] : %02x\n", (unsigned) (unsigned char)ipv4Entry->info.dst_ntwrk[3]);
		fprintf(pkt, "packet->dest_ip[3] : %02x\n", packet->dest_ip[3]);
		
		fprintf(pkt, "\n");
*/		
	/*
		
		if((ipv4Entry->info.dst_ntwrk[0] == packet->dest_ip[0] ) && \
		(ipv4Entry->info.dst_ntwrk[1] == packet->dest_ip[1]) && \
		(ipv4Entry->info.dst_ntwrk[2] == packet->dest_ip[2]) && \
		(ipv4Entry->info.dst_ntwrk[3] == packet->dest_ip[3]))
*/
		if ((packet->dest_ip[0] == (unsigned) (unsigned char)(ipv4Entry->info.dst_ntwrk[0])) && \
			(packet->dest_ip[1] == (unsigned) (unsigned char)(ipv4Entry->info.dst_ntwrk[1])) && \
			(packet->dest_ip[2] == (unsigned) (unsigned char)(ipv4Entry->info.dst_ntwrk[2])) && \
			(packet->dest_ip[3] == (unsigned) (unsigned char)(ipv4Entry->info.dst_ntwrk[3])))
		{
			printf("Found ROuting Info, Adding Packet to Queue %d\n", ipv4Entry->info.output_port_queue);
			
			if (0x01 == ((unsigned) (unsigned char)(ipv4Entry->info.output_port_queue)))
			{
				pthread_mutex_lock (&ipv4_queue1_mutex);
				ipv4Enqueue(IPV4_QUEUE_1, packet);
				pthread_mutex_unlock(&ipv4_queue1_mutex);
				sem_post(&ipv4_queue1_sem);
				
				//printf("procesed link 3 packet %d\n", (i+1));
				
			}
			if (0x02 == ((unsigned) (unsigned char)(ipv4Entry->info.output_port_queue)))
			{
				pthread_mutex_lock (&ipv4_queue2_mutex);
				ipv4Enqueue(IPV4_QUEUE_2, packet);
				pthread_mutex_unlock(&ipv4_queue2_mutex);
				sem_post(&ipv4_queue2_sem);
				
			}
			
			if (0x03 == ((unsigned) (unsigned char)(ipv4Entry->info.output_port_queue)))
			{
				pthread_mutex_lock (&ipv4_queue3_mutex);
				ipv4Enqueue(IPV4_QUEUE_3, packet);
				pthread_mutex_unlock(&ipv4_queue3_mutex);
				sem_post(&ipv4_queue3_sem);			
			}
		
			tbl_exist = TRUE;
			break;

		}
		else
		{
//			printf("Checking Other Routing Entries\n");
			ipv4Entry = ipv4Entry->next;
		}

	}
	if (tbl_exist == FALSE)
	{
		printf("Could Not Find Routing Info for Packet\n");
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

	int in_thread_status = FALSE, out_thread_status = FALSE;

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
	
	initialize_output_files();
	
	printf("Starting Input Threads\n");
	in_thread_status = start_input_threads();
	if (FALSE == in_thread_status)
		printf("Could Not Start The Input Threads \n");

//Start Output Threads
	out_thread_status = start_output_link_threads();
	if (FALSE == out_thread_status)
		printf("Could Not Start The Output Threads \n");
	
	pthread_join( input_thread1, NULL);
	
	//As input_thread1 has finished signal the corresponding output thread to exit
	sem_post(&ipv4_queue1_sem);
	
	pthread_join( input_thread2, NULL);

	//As input_thread2 has finished signal the corresponding output thread to exit
	sem_post(&ipv4_queue2_sem);
	

	pthread_join( input_thread3, NULL);
	
	//As input_thread3 has finished signal the corresponding output thread to exit
	sem_post(&ipv4_queue3_sem);

	//Main Thread waiting for all output threads to exit before exiting
	pthread_join( output_thread1, NULL);
	pthread_join( output_thread2, NULL);
	pthread_join( output_thread3, NULL);
	
	printf("All Threads Finished ...Exiting Main\n");
	
	
	fclose(pkt);
//	Print_Routing_Tbls();

	return 0;
}

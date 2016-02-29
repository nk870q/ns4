#ifndef _CN2SIMULATOR_
#define  _CN2SIMULATOR_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <semaphore.h>

#define TRUE 1
#define FALSE 0

#define DEBUG 1

#define MULTIPLIER 100

#define STANDARD_SLEEP_TIME 100
typedef unsigned short ushort;


//Input File Names
#define INPUT_FILE1_NAME "link1flow"
#define INPUT_FILE2_NAME "link2flow"
#define INPUT_FILE3_NAME "link3flow"

//Output File Names
#define IPV4_OUTPUT_FILE1_NAME "outfile1"
#define IPV4_OUTPUT_FILE2_NAME "outfile2"
#define IPV4_OUTPUT_FILE3_NAME "outfile3"

//Forwarding or Routing Table File Names
#define IPV4_ROUTING_TBL_NAME "ipv4Table"
#define IPV6_ROUTING_TBL_NAME "ipv6Table"

//Maximum No of Forwarding Table Entries
#define MAX_ROUTING_ENTRY 100

//Partitioning element size used to partition different components of the forwarding table
#define PARTITION_SIZE 1

//Maximum No of Forwarding Table Entries
#define IPV4_ROUTING_RECORD_SIZE 50
#define IPV6_ROUTING_RECORD_SIZE 100


//THis defines How many maximum records they will provide in each file
#define MAX_FILE1_SIZE 1000
#define MAX_FILE2_SIZE 1000
#define MAX_FILE3_SIZE 1000

//Input Link Speed Limits
#define INPUT_LINK1_SPEED 20
#define INPUT_LINK2_SPEED 15
#define INPUT_LINK3_SPEED 10

//Output Link Speed Limits
#define OUTPUT_LINK1_SPEED 20
#define OUTPUT_LINK2_SPEED 10
#define OUTPUT_LINK3_SPEED 5

//Each Packet size. Used to read that number of bytes from the file at a time
#define PACKECT_SIZE 500

//Buffer To store the Packets after reading from the file
/*
char * Buffer1[MAX_FILE1_SIZE];
char * Buffer2[MAX_FILE2_SIZE];
char * Buffer3[MAX_FILE3_SIZE];
*/
/*
extern unsigned char Buffer1[MAX_FILE1_SIZE][PACKECT_SIZE];
extern unsigned char Buffer2[MAX_FILE2_SIZE][PACKECT_SIZE];
extern unsigned char Buffer3[MAX_FILE3_SIZE][PACKECT_SIZE];
*/

/*
extern char Buffer1[MAX_FILE1_SIZE][PACKECT_SIZE];
extern char Buffer2[MAX_FILE2_SIZE][PACKECT_SIZE];
extern char Buffer3[MAX_FILE3_SIZE][PACKECT_SIZE];
*/

/*
int thread1_byte_counter = 0;
int thread2_byte_counter = 0;
int thread3_byte_counter = 0;
*/

/* The following global variables will hold the limit of no of packets
 * to be processed from each link calculated based on rate
 * Each thread will process that many packets at a time.
 */
/*
short thread1_pkt_lim;
short thread2_pkt_lim;
short thread3_pkt_lim;
*/

/*Packet counters for each thread to keep track of where to start processing
 * Next Packet. It will start from 0 and each tile incremented by pkt_lim
 * of that link till all the packets from that link is processed.
 */
extern int input_link1_pkt_count;
extern int input_link2_pkt_count;
extern int input_link3_pkt_count;




/*
typedef struct _ipv4RoutingInfo ipv4RoutingInfo;
typedef struct _ipv6RoutingInfo ipv6RoutingInfo;
typedef struct _ipv4RoutingTable ipv4RoutingTable;
typedef struct _ipv6RoutingTable ipv6RoutingTable;
 */

typedef enum _link_no
{
	LINK1 = 1,
	LINK2,
	LINK3
}link_no;

typedef enum _ipv4_queue_no
{
	IPV4_QUEUE_1 = 1,
	IPV4_QUEUE_2,
	IPV4_QUEUE_3
}ipv4_queue_no;

typedef enum _ipv6_queue_no
{
	IPV6_QUEUE_1 = 1,
	IPV6_QUEUE_2,
	IPV6_QUEUE_3
}ipv6_queue_no;

typedef struct _link_param
{
	short slp_time;
	link_no l_no;

}link_param;

/*
typedef struct _ipv4Packet
{

	short version;
	unsigned char source_ip[4];
	unsigned char dest_ip[4];
	unsigned char complete_packet[PACKECT_SIZE];

}ipv4Packet;
*/



typedef struct _ipv4Packet
{

	short version;
	unsigned char source_ip[4];
	unsigned char dest_ip[4];
	unsigned char *complete_packet;

}ipv4Packet;


typedef struct _ipv6Packet
{

	short version;
	unsigned char source_ip[16];
	unsigned char dest_ip[16];
	unsigned char complete_packet[PACKECT_SIZE];

}ipv6Packet;


typedef struct _ipv4RoutingInfo
{
	unsigned char src_ntwrk[4];
	unsigned char dst_ntwrk[4];
	unsigned char dst_ntwrk_mask[4];

	unsigned char nxt_hop_ip[4];
	unsigned char output_port;
	unsigned char output_port_queue;
	unsigned char future[4];

}ipv4RoutingInfo;

typedef struct _ipv6RoutingInfo
{
	unsigned char src_ntwrk[16];
	unsigned char dst_ntwrk[16];
	unsigned char dst_ntwrk_mask[16];

	unsigned char nxt_hop_ip[16];
	unsigned char output_port;
	unsigned char output_port_queue;
	unsigned char future[16];

}ipv6RoutingInfo;

typedef struct _ipv4RoutingTable ipv4RoutingTable;
typedef struct _ipv6RoutingTable ipv6RoutingTable;

struct _ipv4RoutingTable
{
	ipv4RoutingInfo info;
	ipv4RoutingTable *next;

};

struct _ipv6RoutingTable
{
	ipv6RoutingInfo info;
	ipv6RoutingTable *next;

};


extern ipv4RoutingTable *ipv4RoutingTbl ;
extern ipv6RoutingTable *ipv6RoutingTbl ;

//IPV4 Function Prototypes
int process_ipv4Packet(ipv4Packet *packet);


//IPV6 Function Prototypes
int process_ipv6Packet(ipv6Packet *packet);


void *input_link_thread_function( void *ptr );
void process_link1_packets();
void process_link2_packets();
void process_link3_packets();

void calculate_threads_slp_times();
void initialize_output_files();

#endif

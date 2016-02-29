/*
 * input_threads.c
 *
 *  Created on: Feb 27, 2016
 *      Author: saroj
 */

#ifndef INPUT_THREADS_C_
#define INPUT_THREADS_C_


#include "input_threads.h"



link_param input_link1_param, input_link2_param, input_link3_param;


/*This function calculates the relative speed of each link based on rate
 * limit for both input and output links. This then transfers that to nano
 * second sleeping for each thread
 * each link
 */


void *input_link_thread_function( void *ptr )
{
	int datetime_diff_ms;
	link_param *lp;

	struct timeval t0, t1;

	lp = (link_param *)ptr;

	printf("Thread For Link %d %s %d \n", lp->l_no, __FILE__, __LINE__);
	gettimeofday(&t0, NULL);

/*
 * To simulate speed limit, make the thread to sleep for the calculated time
 */
//	usleep(lparam->slp_time);

	switch( lp->l_no )
	{
		case LINK1:
//			printf("Thread 1 had slept for :%d\n", lparam->slp_time);
			process_link1_packets(lp);
			break;

		case LINK2:
//			printf("Thread 2 had slept for :%d\n", lparam->slp_time);
			process_link2_packets(lp);
			break;

		case LINK3:
	//		printf("Thread 2 had slept for :%d\n", lparam->slp_time);
			process_link3_packets(lp);
			break;

		default:
			printf("%s %d It should never come here \n", __FILE__, __LINE__);
			exit(0);


	}

	return ptr;
}

void process_link1_packets(link_param *lparam)
{

	int i;
	unsigned char hdr_first_byte;
	int src_counter = 0;
	int dst_counter = 0;

	ipv4Packet *ipv4Pkt;
	ipv6Packet *ipv6Pkt;

	link_param *lp;
	lp = lparam;


	for(i=0; i<input_link1_pkt_count; i++)
	{
//Sleep For Calculated time
		usleep(lp->slp_time);

		hdr_first_byte = Buffer1[i][0];
		char *pktPtr = Buffer1[i];

//		printf ("IP Header 1st Byte :%d \n", hdr_first_byte);
		if ((hdr_first_byte >> 4) == 4)
		{
//			printf("Found IPv4 Packet \n");
			ipv4Pkt = (ipv4Packet *) malloc(sizeof(ipv4Packet));
			ipv4Pkt->version = 4;

//Extract the Source Ip by moving pktPtr to the starting of Source Ip
			pktPtr = pktPtr + 12;

			strncpy(ipv4Pkt->source_ip, pktPtr, 4);


//Extract the Destination Ip by moving pktPtr to the starting of Destination Ip
			pktPtr = pktPtr + 4;
			strncpy(ipv4Pkt->dest_ip, pktPtr, 4);

// Copy the Original complete Packet
			//strncpy(ipv4Pkt->complete_packet, Buffer1[i], PACKECT_SIZE);

			ipv4Pkt->complete_packet = Buffer1[i];
			process_ipv4Packet(ipv4Pkt);

	//		sleep(10);
		//	printf("procesed link 1 packet %d\n", (i+1));


			//Sleep For Calculated time
			usleep(lp->slp_time);

		}
		else if ((hdr_first_byte >> 4) == 6)
			printf("Found IPv6 Packet \n");



	}
	printf("Processed all %d Link1 Packets\n", i);
}

void process_link2_packets(link_param *lparam)
{

	int i;
	unsigned char hdr_first_byte;
	int src_counter = 0;
	int dst_counter = 0;

	ipv4Packet *ipv4Pkt;
	ipv6Packet *ipv6Pkt;

	link_param *lp = lparam;


	for(i=0; i<input_link2_pkt_count; i++)
	{


		hdr_first_byte = Buffer2[i][0];
		char *pktPtr = Buffer2[i];

//		printf ("IP Header 1st Byte :%d \n", hdr_first_byte);
		if ((hdr_first_byte >> 4) == 4)
		{
//			printf("Found IPv4 Packet \n");
			ipv4Pkt = (ipv4Packet *) malloc(sizeof(ipv4Packet));
			ipv4Pkt->version = 4;

	//Extract the Source Ip by moving pktPtr to the starting of Source Ip
			pktPtr = pktPtr + 12;

			strncpy(ipv4Pkt->source_ip, pktPtr, 4);


	//Extract the Destination Ip by moving pktPtr to the starting of Destination Ip
			pktPtr = pktPtr + 4;
			strncpy(ipv4Pkt->dest_ip, pktPtr, 4);

	// Copy the Original complete Packet
			//strncpy(ipv4Pkt->complete_packet, Buffer2[i], PACKECT_SIZE);
			ipv4Pkt->complete_packet = Buffer2[i];

			process_ipv4Packet(ipv4Pkt);

	//		sleep(10);
		//	printf("procesed link 2 packet %d\n", (i+1));
			//Sleep For Calculated time
			usleep(lp->slp_time);

		}
		else if ((hdr_first_byte >> 4) == 6)
		{
			printf("Found IPv6 Packet \n");
		}



	}
	printf("Processed all %d Link2 Packets\n", i);
}

void process_link3_packets(link_param *lparam)
{

	int i;
	unsigned char hdr_first_byte;
	int src_counter = 0;
	int dst_counter = 0;


	ipv4Packet *ipv4Pkt;
	ipv6Packet *ipv6Pkt;

	link_param *lp = lparam;


	for(i=0; i<input_link3_pkt_count; i++)
	{


		hdr_first_byte = Buffer3[i][0];
		char *pktPtr = Buffer3[i];

//		printf ("IP Header 1st Byte :%d \n", hdr_first_byte);
		if ((hdr_first_byte >> 4) == 4)
		{
//			printf("Found IPv4 Packet \n");
			ipv4Pkt = (ipv4Packet *) malloc(sizeof(ipv4Packet));
			ipv4Pkt->version = 4;

	//Extract the Source Ip by moving pktPtr to the starting of Source Ip
			pktPtr = pktPtr + 12;

			strncpy(ipv4Pkt->source_ip, pktPtr, 4);
	/*
				for (src_counter =0; src_counter <=3; src_counter++)
					printf("Source Ip[%d] :%02x\n", src_counter, ipv4Pkt->source_ip[src_counter]);
	*/

	//Extract the Destination Ip by moving pktPtr to the starting of Destination Ip
			pktPtr = pktPtr + 4;
			strncpy(ipv4Pkt->dest_ip, pktPtr, 4);

	// Copy the Original complete Packet
	//		strncpy(ipv4Pkt->complete_packet, Buffer3[i], PACKECT_SIZE);
			ipv4Pkt->complete_packet = Buffer3[i];
			process_ipv4Packet(ipv4Pkt);

	//		sleep(10);
		//	printf("procesed link 3 packet %d\n", (i+1));

			//Sleep For Calculated time
			usleep(lp->slp_time);

		}
		else if ((hdr_first_byte >> 4) == 6)
		{
			printf("Found IPv6 Packet \n");
		}

	}
	printf("Processed all %d Link3 Packets %s %d\n", i, __FILE__, __LINE__);
}

int start_input_threads()
{

	 int  iret1, iret2, iret3;

//Set TEach Thread Parameters
	 input_link1_param.l_no = LINK1;
	 input_link1_param.slp_time = input_thread1_slp_time;

	 input_link2_param.l_no = LINK2;
	 input_link2_param.slp_time = input_thread2_slp_time;

	 input_link3_param.l_no = LINK3;
	 input_link3_param.slp_time = input_thread3_slp_time;


//	 calculate_rate_limit();

	 iret1 = pthread_create( &input_thread1, NULL, input_link_thread_function, (void *)&input_link1_param );
	 if (iret1)
	 {
		 printf("Error - pthread_create() thread1 return code: %d\n",iret1);
		 return FALSE;
	 }

	 iret2 = pthread_create( &input_thread2, NULL, input_link_thread_function, (void *)&input_link2_param);
	 	 if (iret2)
	 	 {
	 		 printf("Error - pthread_create() thread2 return code: %d\n",iret2);
	 		 return FALSE;
	 	 }

		 iret3 = pthread_create( &input_thread2, NULL, input_link_thread_function, (void *)&input_link3_param );
		 if (iret3)
		 {
			 printf("Error - pthread_create() thread3 return code: %d\n",iret3);
			 return FALSE;
		 }

		 return TRUE;
}

#endif /* INPUT_THREADS_C_ */

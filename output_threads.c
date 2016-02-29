/*
 * Output_threads.c
 *
 *  Created on: Feb 27, 2016
 *      Author: saroj
 */

#ifndef INPUT_THREADS_C_
#define INPUT_THREADS_C_


#include "output_threads.h"

int q1_pkt_count = 0, q2_pkt_count = 0, q3_pkt_count = 0;

//Output Queue Link Thread Parameters
ipv4_queue_param ipv4_queue1_param, ipv4_queue2_param, ipv4_queue3_param;

//Semaphore Names for each IPV4 Queue
sem_t ipv4_queue1_sem, ipv4_queue2_sem, ipv4_queue3_sem;

//Mutexes For each IPV4 Queue
pthread_mutex_t ipv4_queue1_mutex;
pthread_mutex_t ipv4_queue2_mutex;
pthread_mutex_t ipv4_queue3_mutex;

 pthread_t output_thread1;
 pthread_t output_thread2;
 pthread_t output_thread3;

extern FILE *outfile1;
extern FILE *outfile2;
extern FILE *outfile3;


void initialize_sem_mutex()
{
	pthread_mutex_init(&ipv4_queue1_mutex, NULL);
	pthread_mutex_init(&ipv4_queue2_mutex, NULL);
	pthread_mutex_init(&ipv4_queue3_mutex, NULL);
	
	sem_init(&ipv4_queue1_sem, 0, 0);
	sem_init(&ipv4_queue2_sem, 0, 0);
	sem_init(&ipv4_queue3_sem, 0, 0);
		
}



/*This function calculates the relative speed of each link based on rate
 * limit for both input and output links. This then transfers that to nano
 * second sleeping for each thread
 * each link
 */


void *ipv4_output_queue_thread_function( void *ptr )
{
	int datetime_diff_ms;
	ipv4_queue_param *qp;

	struct timeval t0, t1;

	qp = (ipv4_queue_param *)ptr;

	printf("Thread For Queue %d\n", qp->q_no);
	gettimeofday(&t0, NULL);

/*
 * To simulate speed limit, make the thread to sleep for the calculated time
 */
//	usleep(qp->slp_time);

	switch( qp->q_no )
	{
		case IPV4_QUEUE_1:
//			printf("Output Thread 1 had slept for :%d\n", qparam->slp_time);
			process_ipv4_queue1_packets(qp);
			break;

		case IPV4_QUEUE_2:
//			printf("Output Thread 2 had slept for :%d\n", qparam->slp_time);
			process_ipv4_queue2_packets(qp);
			break;

		case IPV4_QUEUE_3:
//			printf("Output Thread 3 had slept for :%d\n", qparam->slp_time);
			process_ipv4_queue3_packets(qp);
			break;

		default:
			printf("%s %d It should never come here \n", __FILE__, __LINE__);
			exit(0);


	}

	return ptr;
}

void process_ipv4_queue1_packets(ipv4_queue_param *qp)
{

	ipv4Packet *ipv4Pkt = NULL;
	ipv4_queue_param *qparam = qp;
	
	while(TRUE)
	{
	
	//Wait For Packets To Arrive In the Queue To be Processed
		sem_wait(&ipv4_queue1_sem);
	
	//Got Signal, Now Lock The queue and takeout one packet
		pthread_mutex_lock (&ipv4_queue1_mutex);
		ipv4Pkt = (ipv4Packet *)ipv4Dequeue(IPV4_QUEUE_1);
	//Unlock The Queue
		pthread_mutex_unlock(&ipv4_queue1_mutex);
		
		if (NULL == ipv4Pkt)
		{
	//Nothing in the Queue, this is a signal to exit from the thread
			printf("Total Packet Processed in output_thread1 :%d %s %d\n", q1_pkt_count, __FILE__, __LINE__);
			fclose(outfile1);
			pthread_exit(0);
		}
		else
		{
			//Write The Packet to the file
			printf("Writing To File outfile1 %s %d\n", __FILE__, __LINE__);
			//fwrite(ipv4Pkt->complete_packet, sizeof(char), PACKECT_SIZE, outfile1);
			//fwrite(ipv4Pkt->complete_packet, sizeof(unsigned char), PACKECT_SIZE, outfile1);
			fwrite(ipv4Pkt->complete_packet, 1, PACKECT_SIZE, outfile1);
			q1_pkt_count++;
			usleep(qparam->slp_time);
			
		}
	}
	fclose(outfile1);
	return;
}
	
void process_ipv4_queue2_packets(ipv4_queue_param *qp)
{

	ipv4Packet *ipv4Pkt = NULL;
	ipv4_queue_param *qparam = qp;
	
	while(TRUE)
	{
	
	//Wait For Packets To Arrive In the Queue To be Processed
		sem_wait(&ipv4_queue2_sem);
	
	//Got Signal, Now Lock The queue and takeout one packet
		pthread_mutex_lock (&ipv4_queue2_mutex);
		ipv4Pkt = (ipv4Packet *)ipv4Dequeue(IPV4_QUEUE_2);
	//Unlock The Queue
		pthread_mutex_unlock(&ipv4_queue2_mutex);
		
		if (NULL == ipv4Pkt)
		{
	//Nothing in the Queue, this is a signal to exit
			printf("Total Packet Processed in output_thread2 :%d %s %d\n", q2_pkt_count, __FILE__, __LINE__);
			
			fclose(outfile2);
			pthread_exit(0);
		}
		else
		{
			printf("Writing To File outfile2 %s %d\n", __FILE__, __LINE__);
			//Write The Packet to the file
	//		fwrite(ipv4Pkt->complete_packet, sizeof(char), PACKECT_SIZE, outfile2);
			//fwrite(ipv4Pkt->complete_packet, sizeof(unsigned char), PACKECT_SIZE, outfile2);
			
			fwrite(ipv4Pkt->complete_packet, 1, PACKECT_SIZE, outfile2);
			q2_pkt_count++;
			usleep(qparam->slp_time);
			
		}
	}
	fclose(outfile2);
	return;
	
}

void process_ipv4_queue3_packets(ipv4_queue_param *qp)
{

	ipv4Packet *ipv4Pkt = NULL;
	ipv4_queue_no q_no = IPV4_QUEUE_3;
	ipv4_queue_param *qparam = qp;
	
	while(TRUE)
	{
	
	//Wait For Packets To Arrive In the Queue To be Processed
		sem_wait(&ipv4_queue3_sem);
	
	//Got Signal, Now Lock The queue and takeout one packet
		pthread_mutex_lock (&ipv4_queue3_mutex);
		ipv4Pkt = (ipv4Packet *)ipv4Dequeue(IPV4_QUEUE_3);
	//Unlock The Queue
		pthread_mutex_unlock(&ipv4_queue3_mutex);
		
		if (NULL == ipv4Pkt)
		{
	//Nothing in the Queue, this is a signal to exit
			
			printf("Total Packet Processed in output_thread3 :%d\n", q3_pkt_count);
			fclose(outfile3);
			pthread_exit(0);
			
		}
		else
		{
			printf("Writing To File outfile3 %s %d\n", __FILE__, __LINE__);
			//Write The Packet to the file
			//fwrite(ipv4Pkt->complete_packet, sizeof(char), PACKECT_SIZE, outfile3);
			//fwrite(ipv4Pkt->complete_packet, sizeof(unsigned char), PACKECT_SIZE, outfile3);
			fwrite(ipv4Pkt->complete_packet, 1, PACKECT_SIZE, outfile3);
			q3_pkt_count++;
			usleep(qparam->slp_time);
		}
	}
	return;
	fclose(outfile3);
}


int start_output_link_threads()
{

	 int  iret1, iret2, iret3;

//Set Each Thread Parameters
	 ipv4_queue1_param.q_no = IPV4_QUEUE_1;
	 ipv4_queue1_param.slp_time = output_thread1_slp_time;

	 ipv4_queue2_param.q_no = IPV4_QUEUE_2;
	 ipv4_queue2_param.slp_time = output_thread2_slp_time;

	 ipv4_queue3_param.q_no = IPV4_QUEUE_3;
	 ipv4_queue3_param.slp_time = output_thread2_slp_time;



//	 calculate_rate_limit();

	 iret1 = pthread_create( &output_thread1, NULL, ipv4_output_queue_thread_function, (void *)&ipv4_queue1_param );
	 if (iret1)
	 {
		 printf("Error - pthread_create() output_thread1 return code: %d\n",iret1);
		 return FALSE;
	 }

	 iret2 = pthread_create( &output_thread2, NULL, ipv4_output_queue_thread_function, (void *)&ipv4_queue2_param);
	 	 if (iret2)
	 	 {
	 		 printf("Error - pthread_create() output_thread2 return code: %d\n",iret2);
	 		 return FALSE;
	 	 }

		 iret3 = pthread_create( &output_thread3, NULL, ipv4_output_queue_thread_function, (void *)&ipv4_queue3_param );
		 if (iret3)
		 {
			 printf("Error - pthread_create() output_thread3 return code: %d\n",iret3);
			 return FALSE;
		 }

		 return TRUE;
}

#endif /* INPUT_THREADS_C_ */

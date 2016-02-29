/*
 * input_threads.h
 *
 *  Created on: Feb 27, 2016
 *      Author: saroj
 */

#ifndef INPUT_THREADS_H_
#define INPUT_THREADS_H_

#include <semaphore.h>
#include "cn2simulator.h"


typedef struct _ipv4_queue_param
{
	short slp_time;
	ipv4_queue_no q_no;

}ipv4_queue_param;


extern int output_thread1_slp_time;
extern int output_thread2_slp_time ;
extern int output_thread3_slp_time ;


void *ipv4_output_queue_thread_function( void *ptr );
void process_ipv4_queue1_packets();
void process_ipv4_queue2_packets();
void process_ipv4_queue3_packets();

void initialize_sem_mutex();
void initialize_output_files();


#endif /* INPUT_THREADS_H_ */

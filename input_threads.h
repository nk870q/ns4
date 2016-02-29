/*
 * input_threads.h
 *
 *  Created on: Feb 27, 2016
 *      Author: saroj
 */

#ifndef INPUT_THREADS_H_
#define INPUT_THREADS_H_

#include "cn2simulator.h"
#include <semaphore.h>

typedef struct _link_param
{
	short slp_time;
	link_no l_no;

}link_param;

extern int input_thread1_slp_time;
extern int input_thread2_slp_time ;
extern int input_thread3_slp_time ;

extern int output_thread1_slp_time;
extern int output_thread2_slp_time ;
extern int output_thread3_slp_time ;

extern pthread_t input_thread1, input_thread2, input_thread3;


void calculate_rate_limit();
void *input_link_thread_function( void *ptr );
void process_link1_packets(link_param *);
void process_link2_packets(link_param *);
void process_link3_packets(link_param *);


#endif /* INPUT_THREADS_H_ */

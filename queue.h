/*
 * queue.h
 *
 *  Created on: Feb 27, 2016
 *      Author: saroj
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "cn2simulator.h"

typedef struct _ipv4Node ipv4Node;
typedef struct _ipv6Node ipv6Node;

struct _ipv4Node {
	ipv4Packet *ipv4Pkt;
	ipv4Node *next;
};


struct _ipv6Node {
	ipv6Packet *ipv6Pkt;
	ipv6Node *next;
};

void ipv4Enqueue(ipv4_queue_no q_no, ipv4Packet *ipv4Pkt);
ipv4Packet * ipv4Dequeue(ipv4_queue_no q_no);

void ipv6Enqueue(ipv6_queue_no q_no, ipv6Packet *ipv6Pkt);
ipv6Packet * ipv6Dequeue(ipv6_queue_no q_no);

#endif /* QUEUE_H_ */

/*
 * queue.c
 *
 *  Created on: Feb 26, 2016
 *      Author: saroj
 */


#include "queue.h"

ipv4Node *ipv4Queue1_front = NULL;
ipv4Node *ipv4Queue1_rear = NULL;

ipv4Node *ipv4Queue2_front = NULL;
ipv4Node *ipv4Queue2_rear = NULL;

ipv4Node *ipv4Queue3_front = NULL;
ipv4Node *ipv4Queue3_rear = NULL;



// To Enqueue an integer
void ipv4Enqueue(ipv4_queue_no q_no, ipv4Packet *ipv4Pkt)
{
	ipv4Node *temp = (ipv4Node *)malloc(sizeof(ipv4Node));
	temp->ipv4Pkt = ipv4Pkt;

	temp->next = NULL;

	switch(q_no)
	{
	case IPV4_QUEUE_1:
		if(ipv4Queue1_front == NULL && ipv4Queue1_rear == NULL)
		{
			ipv4Queue1_front = ipv4Queue1_rear = temp;
			return;
		}
		ipv4Queue1_rear->next = temp;
		ipv4Queue1_rear = temp;

		break;

	case IPV4_QUEUE_2:
		if(ipv4Queue2_front == NULL && ipv4Queue2_rear == NULL)
		{
			ipv4Queue2_front = ipv4Queue2_rear = temp;
			return;
		}
		ipv4Queue2_rear->next = temp;
		ipv4Queue2_rear = temp;
		break;

	case IPV4_QUEUE_3:
		if(ipv4Queue3_front == NULL && ipv4Queue3_rear == NULL)
		{
			ipv4Queue3_front = ipv4Queue3_rear = temp;
			return;
		}
		ipv4Queue3_rear->next = temp;
		ipv4Queue3_rear = temp;
		break;
	}

}

ipv4Packet * ipv4Dequeue(ipv4_queue_no q_no)
{
	ipv4Node *temp = NULL;
	ipv4Packet *ipv4Pkt = NULL;

	switch(q_no)
	{
	case IPV4_QUEUE_1:
		if(ipv4Queue1_front == NULL)
		{
			printf("ipv4Queue 1 is Empty\n");
			return NULL;
		}
		temp = ipv4Queue1_front;

		if(ipv4Queue1_front == ipv4Queue1_rear)
		{
			ipv4Queue1_front = ipv4Queue1_front = NULL;

		}
		else
		{
			ipv4Queue1_front = ipv4Queue1_front->next;
		}

		break;

	case IPV4_QUEUE_2:
		if(ipv4Queue2_front == NULL)
		{
			printf("ipv4Queue 2 is Empty\n");
			return NULL;
		}
		temp = ipv4Queue2_front;

		if(ipv4Queue2_front == ipv4Queue2_rear)
		{
			ipv4Queue2_front = ipv4Queue2_rear = NULL;

		}
		else
		{
			ipv4Queue2_front = ipv4Queue2_front->next;
		}

		break;

	case IPV4_QUEUE_3:
		if(ipv4Queue3_front == NULL)
		{
			printf("ipv4Queue 3 is Empty\n");
			return NULL;
		}
		temp = ipv4Queue3_front;

		if(ipv4Queue3_front == ipv4Queue3_rear)
		{
			ipv4Queue3_front = ipv4Queue3_rear = NULL;

		}
		else
		{
			ipv4Queue3_front = ipv4Queue3_front->next;
		}

		break;
	}
	ipv4Pkt = temp->ipv4Pkt;
	free(temp);
	return ipv4Pkt;
}

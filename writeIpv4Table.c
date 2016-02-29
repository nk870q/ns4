/*
 * writeIpv4Table.c
 *
 *  Created on: Feb 25, 2016
 *      Author: saroj
 */

#include "cn2simulator.h"

#define DELIM " "

#define IPV4_ROUTING_TBL_NAME "ipv4Table"

/*
Link 1 Destination Ip: dd 6f b4 f1
Link 1 Source Ip:6f 70 71 72



Link 2 Destination Ip: de 70 c0 ca
Link 2 Source Ip:79 7a 7b 7c

Link 3 Destination Ip:  df 71 84 f3

Link 3 Source Ip:83 84 85 86

*/


ipv4RoutingInfo ipv4Info1, ipv4Info2, ipv4Info3;

void prepare_info1()
{


	ipv4Info1.src_ntwrk[0] = 0x6f;
	printf("Info1.src_ntwrk[0] :%02x\n", ipv4Info1.src_ntwrk[0] );
	ipv4Info1.src_ntwrk[1] = 0x70;
	ipv4Info1.src_ntwrk[2] = 0x71;
	ipv4Info1.src_ntwrk[3] = 0x72;

	ipv4Info1.dst_ntwrk[0] = 0xdd;
	ipv4Info1.dst_ntwrk[1] = 0x6f;
	ipv4Info1.dst_ntwrk[2] = 0xb4;
	ipv4Info1.dst_ntwrk[3] = 0xf1;

	ipv4Info1.dst_ntwrk_mask[0] = 0xff;
	ipv4Info1.dst_ntwrk_mask[1] = 0xff;
	ipv4Info1.dst_ntwrk_mask[2] = 0xff;
	ipv4Info1.dst_ntwrk_mask[3] = 0xff;

	ipv4Info1.nxt_hop_ip[0] = 0xff;
	ipv4Info1.nxt_hop_ip[1] = 0xff;
	ipv4Info1.nxt_hop_ip[2] = 0xff;
	ipv4Info1.nxt_hop_ip[3] = 0xff;

	ipv4Info1.output_port = 0x01;
	ipv4Info1.output_port_queue = 0x01;

	ipv4Info1.future[0] = 0xff;
	ipv4Info1.future[1] = 0xff;
	ipv4Info1.future[2] = 0xff;
	ipv4Info1.future[3] = 0xff;

}

void prepare_info2()
{


	ipv4Info2.src_ntwrk[0] = 0x79;
	ipv4Info2.src_ntwrk[1] = 0x7a;
	ipv4Info2.src_ntwrk[2] = 0x7b;
	ipv4Info2.src_ntwrk[3] = 0x7c;

	ipv4Info2.dst_ntwrk[0] = 0xde;
	ipv4Info2.dst_ntwrk[1] = 0x70;
	ipv4Info2.dst_ntwrk[2] = 0xc0;
	ipv4Info2.dst_ntwrk[3] = 0xca;

	ipv4Info2.dst_ntwrk_mask[0] = 0xff;
	ipv4Info2.dst_ntwrk_mask[1] = 0xff;
	ipv4Info2.dst_ntwrk_mask[2] = 0xff;
	ipv4Info2.dst_ntwrk_mask[3] = 0xff;

	ipv4Info2.nxt_hop_ip[0] = 0xff;
	ipv4Info2.nxt_hop_ip[1] = 0xff;
	ipv4Info2.nxt_hop_ip[2] = 0xff;
	ipv4Info2.nxt_hop_ip[3] = 0xff;

	ipv4Info2.output_port = 0x02;
	ipv4Info2.output_port_queue = 0x02;

	ipv4Info2.future[0] = 0xff;
	ipv4Info2.future[1] = 0xff;
	ipv4Info2.future[2] = 0xff;
	ipv4Info2.future[3] = 0xff;

}

void prepare_info3()
{


	ipv4Info3.src_ntwrk[0] = 0x83;
	ipv4Info3.src_ntwrk[1] = 0x84;
	ipv4Info3.src_ntwrk[2] = 0x85;
	ipv4Info3.src_ntwrk[3] = 0x86;

	ipv4Info3.dst_ntwrk[0] = 0xdf;
	ipv4Info3.dst_ntwrk[1] = 0x71;
	ipv4Info3.dst_ntwrk[2] = 0x84;
	ipv4Info3.dst_ntwrk[3] = 0xf3;

	ipv4Info3.dst_ntwrk_mask[0] = 0xff;
	ipv4Info3.dst_ntwrk_mask[1] = 0xff;
	ipv4Info3.dst_ntwrk_mask[2] = 0xff;
	ipv4Info3.dst_ntwrk_mask[3] = 0xff;

	ipv4Info3.nxt_hop_ip[0] = 0xff;
	ipv4Info3.nxt_hop_ip[1] = 0xff;
	ipv4Info3.nxt_hop_ip[2] = 0xff;
	ipv4Info3.nxt_hop_ip[3] = 0xff;

	ipv4Info3.output_port = 0x03;
	ipv4Info3.output_port_queue = 0x03;

	ipv4Info3.future[0] = 0xff;
	ipv4Info3.future[1] = 0xff;
	ipv4Info3.future[2] = 0xff;
	ipv4Info3.future[3] = 0xff;

}

void write_space(FILE *fptr)
{
	fwrite(DELIM, sizeof(char), sizeof(char), fptr);
}

/*
void write_to_file_fprintf(ipv4RoutingInfo *info, FILE *fptr)
{
	printf("sizeof(info->src_ntwrk) :%d\n", sizeof(info->src_ntwrk));
	fprintf(info->src_ntwrk, sizeof(unsigned char), sizeof(info->src_ntwrk), fptr);
	write_space(fptr);

	printf("sizeof(info->dst_ntwrk) :%d\n", sizeof(info->dst_ntwrk));
	fwrite(info->dst_ntwrk, sizeof(unsigned char), sizeof(info->dst_ntwrk), fptr);
	write_space(fptr);

	printf("sizeof(info->dst_ntwrk_mask) :%d\n", sizeof(info->dst_ntwrk_mask));
	fwrite(info->dst_ntwrk_mask, sizeof(unsigned char), sizeof(info->dst_ntwrk_mask), fptr);
	write_space(fptr);

	printf("sizeof(info->nxt_hop_ip) :%d\n", sizeof(info->nxt_hop_ip));
	fwrite(info->nxt_hop_ip, sizeof(unsigned char), sizeof(info->nxt_hop_ip), fptr);
	write_space(fptr);

	printf("sizeof(info->output_port) :%d\n", sizeof(info->output_port));
	fwrite(&(info->output_port), sizeof(unsigned char), sizeof(info->output_port), fptr);
	write_space(fptr);

	printf("sizeof(info->output_port_queue) :%d\n", sizeof(info->output_port_queue));
	fwrite(&(info->output_port_queue), sizeof(unsigned char), sizeof(info->output_port_queue), fptr);
	write_space(fptr);

	printf("sizeof(info->future) :%d\n", sizeof(info->future));
	fwrite(info->future, sizeof(unsigned char), sizeof(info->future), fptr);
	fwrite("\n", sizeof(char), sizeof(char), fptr);

}

*/

void write_to_file_fwrire(ipv4RoutingInfo *info, FILE *fptr)
{

	printf("sizeof(info->src_ntwrk) :%d\n", sizeof(info->src_ntwrk));
	fwrite(info->src_ntwrk, sizeof(unsigned char), sizeof(info->src_ntwrk), fptr);
	write_space(fptr);

	printf("sizeof(info->dst_ntwrk) :%d\n", sizeof(info->dst_ntwrk));
	fwrite(info->dst_ntwrk, sizeof(unsigned char), sizeof(info->dst_ntwrk), fptr);
	write_space(fptr);

	printf("sizeof(info->dst_ntwrk_mask) :%d\n", sizeof(info->dst_ntwrk_mask));
	fwrite(info->dst_ntwrk_mask, sizeof(unsigned char), sizeof(info->dst_ntwrk_mask), fptr);
	write_space(fptr);

	printf("sizeof(info->nxt_hop_ip) :%d\n", sizeof(info->nxt_hop_ip));
	fwrite(info->nxt_hop_ip, sizeof(unsigned char), sizeof(info->nxt_hop_ip), fptr);
	write_space(fptr);

	printf("sizeof(info->output_port) :%d\n", sizeof(info->output_port));
	fwrite(&(info->output_port), sizeof(unsigned char), sizeof(info->output_port), fptr);
	write_space(fptr);

	printf("sizeof(info->output_port_queue) :%d\n", sizeof(info->output_port_queue));
	fwrite(&(info->output_port_queue), sizeof(unsigned char), sizeof(info->output_port_queue), fptr);
	write_space(fptr);

	printf("sizeof(info->future) :%d\n", sizeof(info->future));
	fwrite(info->future, sizeof(unsigned char), sizeof(info->future), fptr);

//	fwrite(info, 1, sizeof(ipv4RoutingInfo), fptr);
	fwrite("\n", sizeof(char), sizeof(char), fptr);

}


void write_ipv4()
{
	int pkt_count = 0;
	FILE *fptr=NULL;



//Open The Input File To Read in Binary Mode.
	fptr = fopen(IPV4_ROUTING_TBL_NAME, "wb");
	if(NULL==fptr)
	{
		printf("Could not open %s\n", IPV4_ROUTING_TBL_NAME);
		exit(0);
	}
	else
	{
		write_to_file_fwrire(&ipv4Info1, fptr);
		write_to_file_fwrire(&ipv4Info2, fptr);
		write_to_file_fwrire(&ipv4Info3, fptr);


	}
}

int main()
{
	prepare_info1();
	prepare_info2();
	prepare_info3();
	write_ipv4();
	return 0;
}

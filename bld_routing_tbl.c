/*
 * bld_routing_tbl.c
 *
 *  Created on: Feb 24, 2016
 *      Author: saroj
 */


#include "bld_routing_tbl.h"
extern FILE *route;

//extern FILE *route;

unsigned char ipv4Record[IPV4_ROUTING_RECORD_SIZE];


ipv4RoutingTable *ipv4RoutingTbl = NULL;
ipv6RoutingTable *ipv6RoutingTbl = NULL;

void print_hex(unsigned char *ptr, int size)
{
	int i = 0;
	while (i < size)
	{
		printf("%x ", ptr[i]);
		fprintf(route, "%x ", ptr[i]);
		i++;
	}


}

void print_routing_info(ipv4RoutingInfo *info)
{
	printf("src_ntwrk :\n");
	fprintf(route, "src_ntwrk :");
	print_hex(info->src_ntwrk, 4);
	fprintf(route, "\n");


	printf("dst_ntwrk :\n");
	fprintf(route, "dst_ntwrk :");
	print_hex(info->dst_ntwrk, 4);
	fprintf(route, "\n");
	
	printf("dst_ntwrk_mask :\n");
	fprintf(route, "dst_ntwrk_mask :");
	print_hex(info->dst_ntwrk_mask, 4);
	fprintf(route, "\n");
	

	printf("nxt_hop_ip :\n");
	fprintf(route, "nxt_hop_ip :");
	print_hex(info->nxt_hop_ip, 4);
	fprintf(route, "\n");
	
	printf("output_port :%hhX\n", info->output_port);
	fprintf(route, "output_port :%x\n", info->output_port);

	printf("output_port_queue :%x\n", info->output_port_queue);
	fprintf(route, "output_port_queue :%x\n", info->output_port_queue);
	
	printf("ECN :%x\n", info->ds_ecn);
	fprintf(route, "ECN :%x\n", info->ds_ecn);

	printf("pad :\n");
	fprintf(route, "pad :");
	print_hex(info->pad, 3);
	fprintf(route, "\n");

	/*
	printf("dst_ntwrk :\n");
	print_hex(info->dst_ntwrk, 4);
	*/
}

void print_ipv4_routing_tbl(ipv4RoutingTable *tbl)
{
	int i = 1;
	ipv4RoutingTable *tmp = tbl;
	while (tmp !=NULL)
	{
		printf("Entry %d\n", i);
		fprintf(route, "Entry %d\n", i);
		print_routing_info(&(tmp->info) );
		tmp = tmp->next;
		i++;
		
	}
	fprintf(route, "Total No Of Routing Info %d\n", (i-1));


	fclose(route);
		
}

/*
 * Create a New ipv4RoutingInfo Entry
 */
ipv4RoutingTable * build_ipv4_info(char *raw_info)
{

	ipv4RoutingTable *ipv4Info,*current;
	char *parser = NULL;

	ipv4Info = (ipv4RoutingTable *)malloc(sizeof(ipv4RoutingTable));

	parser = raw_info;
	strncpy(ipv4Info->info.src_ntwrk, parser, 4);

	parser+= (4 + PARTITION_SIZE);
	strncpy(ipv4Info->info.dst_ntwrk, parser, 4);

	parser+= (4 + PARTITION_SIZE);
	strncpy(ipv4Info->info.dst_ntwrk_mask, parser, 4);

	parser+=(4 + PARTITION_SIZE);
	strncpy(ipv4Info->info.nxt_hop_ip, parser, 4);

	parser+=(4 + PARTITION_SIZE);
	strncpy(&(ipv4Info->info.output_port), parser, 1);

	parser+=(1 + PARTITION_SIZE);
	strncpy(&(ipv4Info->info.output_port_queue), parser, 1);

	parser+=(1 + PARTITION_SIZE);
	strncpy(&(ipv4Info->info.ds_ecn), parser, 1);

	parser+=(1 + PARTITION_SIZE);
	strncpy(ipv4Info->info.pad, parser, 3);


	ipv4Info->next = NULL;

	return ipv4Info;

}



int buildIpv4RoutingTbl()
{
	int pkt_count = 0;
	FILE *fptr=NULL;

	ipv4RoutingTable *new_node, *current;

//Open The Input File To Read in Binary Mode.
	fptr = fopen(IPV4_ROUTING_TBL_NAME, "rb");
	if(NULL==fptr)
	{
		printf("Could not open %s\n", IPV4_ROUTING_TBL_NAME);
		exit(0);
	}
	else
	{
		if (pkt_count < MAX_ROUTING_ENTRY )
		{

			while(fread(ipv4Record, sizeof(unsigned char), IPV4_ROUTING_RECORD_SIZE, fptr))
//			while(fgets(ipv4Record, IPV4_ROUTING_RECORD_SIZE, fptr))
			{

				  new_node = build_ipv4_info(ipv4Record);

				  new_node->next=NULL;

				  if(ipv4RoutingTbl == NULL)
				  {
					  ipv4RoutingTbl = new_node;
					  current = new_node;
				  }
				  else
				  {
					  current->next = new_node;
					  current = new_node;
				  }

				pkt_count++;
				
			}
		}
		else
		{
			printf("%s has more packets than defined, Ignoring extra Packets\n", IPV4_ROUTING_TBL_NAME);
		}
		if (0 == pkt_count)
		{
			printf("%s is empty", IPV4_ROUTING_TBL_NAME);
		}
		printf("Total No of Packets in %s : %d\n", IPV4_ROUTING_TBL_NAME, pkt_count);
//		print_routing_tbl(ipv4RoutingTbl);
	}

	return pkt_count;

}

//This function will read each input file till end of file is encountered
//and populate each buffer with the packets from the file.
void Populate_Routing_Tbls()
{

	int ret = buildIpv4RoutingTbl();


}

//This function will read each input file till end of file is encountered
//and populate each buffer with the packets from the file.
void Print_Routing_Tbls()
{

	print_ipv4_routing_tbl(ipv4RoutingTbl);


}

/*

int main()
{
	Populate_Routing_Tbls();
	Print_Routing_Tbls();
	return 0;
}
*/



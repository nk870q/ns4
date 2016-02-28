/*
 * readfile.c
 *
 *  Created on: Feb 20, 2016
 *      Author: saroj
 */

#include "cn2simulator.h"
#include "read_input_file.h"



/*Packet counters for each thread to keep track of where to start processing
 * Next Packet. It will start from 0 and each tile incremented by pkt_lim
 * of that link till all the packets from that link is processed.
 */
int input_link1_pkt_count;
int input_link2_pkt_count;
int input_link3_pkt_count;

char Buffer1[MAX_FILE1_SIZE][PACKECT_SIZE];
char Buffer2[MAX_FILE2_SIZE][PACKECT_SIZE];
char Buffer3[MAX_FILE3_SIZE][PACKECT_SIZE];

int readFile(char *fname, char buffer[][PACKECT_SIZE], int maxsize)
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

			while(fread(buffer[pkt_count], sizeof(char), PACKECT_SIZE, fptr))
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




/*
 * read_input_file.h
 *
 *  Created on: Feb 27, 2016
 *      Author: saroj
 */

#ifndef READ_INPUT_FILE_H_
#define READ_INPUT_FILE_H_

#include "cn2simulator.h"

//int readFile(char *fname, unsigned char buffer[][PACKECT_SIZE], int maxsize);

int readFile(char *fname, char buffer[][PACKECT_SIZE], int maxsize);
void Populate_Buffers();


#endif /* READ_INPUT_FILE_H_ */

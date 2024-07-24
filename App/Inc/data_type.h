/*
 * data_type.h
 *
 *  Created on: Mar 31, 2024
 *      Author: XuXuan
 */

#ifndef INC_DATA_TYPE_H_
#define INC_DATA_TYPE_H_

#include "data_type.h"
#include "stm32f4xx_it.h"
#include "main.h"

enum Part
{
	A,
	B,
	null
};


typedef struct {
    uint32_t id;
    float x;
    float y;
    int32_t z;
    uint8_t quadrant;
} DataPacket;


void parseData(uint8_t *buffer, uint16_t length, DataPacket *dataPacket);
void do_action(DataPacket *dataPacket);

#endif /* INC_DATA_TYPE_H_ */

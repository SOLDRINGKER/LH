/*
 * data_type.c
 *
 *  Created on: Mar 31, 2024
 *      Author: XuXuan
 */
#include "main.h"
#include "usart.h"
#include "data_type.h"
#include "Emm_V5.h"
#include <string.h>
#include <stdlib.h>

extern UART_HandleTypeDef huart1;

extern int a_x;
extern int a_y;
extern int a_z;
extern int a_a;

extern int b_x;
extern int b_y;
extern int b_z;
extern int b_a;


int t = 0;
int i = 0;
uint8_t date[] = {'A', 'C', 'K'};
uint8_t RXBUFF[125] = {0};
uint8_t DATA;
uint16_t LEN = 0;
DataPacket dataPacket;
uint8_t DATA=0;

DataPacket dataPacket;
int k=70;

void parseData(uint8_t *buffer, uint16_t length, DataPacket *dataPacket) {
    char *jsonString = (char*)buffer;

    // 去除数组的方括号
    if (jsonString[0] == '[') {
        jsonString++;
    }
    if (jsonString[length - 2] == ']') {
        jsonString[length - 2] = '\0';
    }

    char *token;
    char *endPtr;

    token = strtok(jsonString, "{\":,}");
    while (token != NULL) {
        if (strcmp(token, "id") == 0) {
            token = strtok(NULL, "{\":,}");
            dataPacket->id = strtoul(token, &endPtr, 10);
        } else if (strcmp(token, "x") == 0) {
            token = strtok(NULL, "{\":,}");
            dataPacket->x = strtof(token, &endPtr);
        } else if (strcmp(token, "y") == 0) {
            token = strtok(NULL, "{\":,}");
            dataPacket->y = strtof(token, &endPtr);
        } else if (strcmp(token, "z") == 0) {
            token = strtok(NULL, "{\":,}");
            dataPacket->z = strtol(token, &endPtr, 10);
        } else if (strcmp(token, "quadrant") == 0) {
            token = strtok(NULL, "{\":,}");
            dataPacket->quadrant = (uint8_t)strtoul(token, &endPtr, 10);
        }
        token = strtok(NULL, "{\":,}");
    }
}

/**
 * @brief    位置模式
 * @param    addr：电机地址
 * @param    dir ：方向        ，0为CW，其余值为CCW
 * @param    vel ：速度(RPM)   ，范围0 - 5000RPM
 * @param    acc ：加速度      ，范围0 - 255，注意：0是直接启动
 * @param    clk ：脉冲数      ，范围0- (2^32 - 1)个
 * @param    raF ：相位/绝对标志，false为相对运动，true为绝对值运动
 * @param    snF ：多机同步标志 ，false为不启用，true为启用
 * @retval   地址 + 功能码 + 命令状态 + 校验字节
 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart1)
    {
        RXBUFF[LEN] = DATA;
        LEN++;
        if (RXBUFF[LEN - 1] == ']')
        {
            parseData(RXBUFF, LEN, &dataPacket);
            // 清理缓冲区
            memset(RXBUFF, 0, sizeof(RXBUFF));
            LEN = 0;
            t++;
            // 解析完毕后发送 ACK
			Emm_V5_Pos_Control(b_x, 1, 500, 100, dataPacket.x*k, 1, 0); // 位置模式控制
			HAL_Delay(20);
			Emm_V5_Pos_Control(b_y, 1, 500, 100, dataPacket.y*k, 1, 0); // 位置模式控制
			HAL_Delay(20);
			Emm_V5_Pos_Control(b_z, 1, 500, 100, (400-dataPacket.z)*100, 1, 0); // 位置模式控制
			HAL_Delay(50);
			Emm_V5_Pos_Control(a_x, 1, 500, 100, dataPacket.x*k, 1, 0); // 位置模式控制
			HAL_Delay(20);
			Emm_V5_Pos_Control(a_y, 1, 500, 100, dataPacket.y*k, 1, 0); // 位置模式控制
			HAL_Delay(20);
			Emm_V5_Pos_Control(a_z, 1, 500, 100, (400-dataPacket.z)*100, 1, 0); // 位置模式控制
			HAL_Delay(50);

            HAL_UART_Transmit(&huart1, &date, sizeof(date), 20);
        }
        HAL_UART_Receive_IT(&huart1, &DATA, 1);
    }
}

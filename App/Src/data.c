/*
 * data.c
 *
 *  Created on: Mar 14, 2024
 *      Author: XuXuan
 */
#include "can.h"
#include "data.h"
#include "stdio.h"
#include "main.h"
CAN_RxHeaderTypeDef rxHeader;
uint8_t rxData[8];
static CAN_TxHeaderTypeDef TX;
extern int out;

void can_SendCmd(uint8_t *date, uint8_t len) {
	uint32_t txBox;
	uint8_t txData[8]={0};
	__IO uint8_t i = 0;
	__IO uint8_t j = 0;
	__IO uint8_t k = 0;
	__IO uint8_t l = 0;
	__IO uint8_t packNum = 0;

	j = len - 2;

	while (i < j) {
		k = j - i;
		// 填充缓存
		TX.StdId = 0x00;
		TX.ExtId = ((uint32_t) date[0] << 8) | (uint32_t) packNum;
		TX.IDE = CAN_ID_EXT;
		TX.RTR = CAN_RTR_DATA;
		TX.TransmitGlobalTime = DISABLE;
		txData[0] = date[1];

		if (k < 8) {
			for (l = 0; l < k; l++, i++) {
				txData[l + 1] = date[i + 2];
			}
			TX.DLC = k + 1;
		}
		// 大于8字节命令，分包发送，每包数据最多发送8个字节
		else {
			for (l = 0; l < 7; l++, i++) {
				txData[l + 1] = date[i + 2];
			}
			TX.DLC = 8;
		}
		HAL_CAN_AddTxMessage(&hcan1, &TX, txData, &txBox);
		++packNum;
	}
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {


	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rxHeader, rxData) != HAL_OK) {
		Error_Handler();
	}
	printf("Received CAN message - ID: %lx, DLC: %ld, Data: ", rxHeader.StdId,
			rxHeader.DLC);
	for (int i = 0; i < rxHeader.DLC; ++i) {
		printf("%02X ", rxData[i]);
	}
	printf("\n");
	HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}


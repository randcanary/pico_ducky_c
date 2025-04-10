#ifndef COMM_EXTERNAL_H_
#define COMM_EXTERNAL_H_

#include "FreeRTOS.h"
#include "queue.h"

// Queue to communicate with comm_external
extern QueueHandle_t comm_external_queue;

void comm_external_init(void);

// Comm external main task, to be executed by FreeRTOS scheduler
void comm_external_task(void *pvParameters);

void send_char_as_key(char c);
void send_key(uint8_t key, uint8_t modifier);

#endif // COMM_EXTERNAL_H_
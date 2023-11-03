#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <FreeRTOS.h>
#include <os_task.h>


#include <os_semphr.h>


#define TASK_A_NAME "task A"
#define TASK_A_STACK_SIZE 512
#define TASK_A_PRIORITY 1

#define TASK_B_NAME "task B"
#define TASK_B_STACK_SIZE 512
#define TASK_B_PRIORITY 2 

#define TASK_B_QUEUE_LENGTH 10U
#define TASK_B_QUEUE_ITEM_SIZE sizeof(command_line_event_t)
#define TASK_B_QUEUE_RX_WAIT_PERIOD portMAX_DELAY
#define TASK_B_QUEUE_TX_WAIT_PERIOD 0

typedef enum {
  NULL_EVENT = 0,
  INCREMENT,
  PRINT,
  HELLO,
} command_line_event_t;

static QueueHandle_t taskBQueueHandle = NULL;
static StaticQueue_t taskBQueue;
static uint8_t taskBQueueStack[TASK_B_QUEUE_LENGTH * TASK_B_QUEUE_ITEM_SIZE];

static StackType_t taskAStack[TASK_A_STACK_SIZE];
static StaticTask_t taskA;

static StackType_t taskBStack[TASK_B_STACK_SIZE];
static StaticTask_t taskB;

static SemaphoreHandle_t xMutex;
static StaticSemaphore_t xMutexBuffer;
static void taskAFunction();
static void taskBFunction();

static volatile uint32_t x;

int main() {
  xTaskCreateStatic(taskAFunction, TASK_A_NAME, TASK_A_STACK_SIZE, NULL, TASK_A_PRIORITY, taskAStack, &taskA);
  xTaskCreateStatic(taskBFunction, TASK_B_NAME, TASK_B_STACK_SIZE, NULL, TASK_B_PRIORITY, taskBStack, &taskB);
  
  /* USER CODE START */

  // Create the queue

  /* USER CODE END */

  vTaskStartScheduler(); // give control over to the freeRTOS scheduler
  return 0; // We never make it here unless theres not enough memory for freeRTOS
}

void taskAFunction(){
  while(1){
    char inputString[11]; // Maximum length of 10 characters + 1 for null-terminator
    command_line_event_t eventToSend = {0};
    scanf("%10s", inputString);
    if(strcmp(inputString, "INCREMENT") == 0){
      eventToSend = INCREMENT;
    }
    else if (strcmp(inputString, "PRINT") == 0) {
      eventToSend = PRINT;
    }
    else if(strcmp(inputString, "HELLO") == 0){
      eventToSend = HELLO;
    } else {
      continue;
    }

    /* USER CODE START */

    // send the event to the queue to send to task B

    /* USER CODE END */

    memset(inputString, 0, sizeof(inputString));
  }
}
void taskBFunction(){
  uint32_t counter = 0;
  while(1){
    /* USER CODE START */

    // receive a command_line_event_t from the queue
    // if INCREMENT, increment the counter
    // if PRINT then print the counter value
    // if HELLO, reply by printing Hello!
  
    /* USER CODE END */
  }
}
#include <stdio.h>
#include <stdint.h>

#include <FreeRTOS.h>
#include <os_task.h>


#include <os_semphr.h>


#define TASK_A_NAME "task A"
#define TASK_A_STACK_SIZE 512
#define TASK_A_PRIORITY 1

#define TASK_B_NAME "task B"
#define TASK_B_STACK_SIZE 512
#define TASK_B_PRIORITY 1

static StackType_t taskAStack[TASK_A_STACK_SIZE];
static StaticTask_t taskA;

static StackType_t taskBStack[TASK_B_STACK_SIZE];
static StaticTask_t taskB;

static void taskAFunction();
static void taskBFunction();

static volatile uint32_t x;

int main() {
  xTaskCreateStatic(taskAFunction, TASK_A_NAME, TASK_A_STACK_SIZE, NULL, TASK_A_PRIORITY, taskAStack, &taskA);
  xTaskCreateStatic(taskBFunction, TASK_B_NAME, TASK_B_STACK_SIZE, NULL, TASK_B_PRIORITY, taskBStack, &taskB);
  vTaskStartScheduler(); // give control over to the freeRTOS scheduler
  return 0; // We never make it here unless theres not enough memory for freeRTOS
}

void taskAFunction(){
  while(1){
    x++;
    printf("%u\n", x);
    if(x==2000) vTaskSuspend(NULL);
  }
}

void taskBFunction(){
  while(1){
    x++;
    printf("%u\n", x);
    if(x==2000) vTaskSuspend(NULL);
  }
}
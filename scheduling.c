#include <stdio.h>

#include <FreeRTOS.h>
#include <os_task.h>

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

int main() {
  xTaskCreateStatic(taskAFunction, TASK_A_NAME, TASK_A_STACK_SIZE, NULL, TASK_A_PRIORITY, taskAStack, &taskA);
  xTaskCreateStatic(taskBFunction, TASK_B_NAME, TASK_B_STACK_SIZE, NULL, TASK_B_PRIORITY, taskBStack, &taskB);
  vTaskStartScheduler(); // give control over to the freeRTOS scheduler
  return 0; // We never make it here unless theres not enough memory for freeRTOS
}

static void taskAFunction(){
  printf("Hello from task A!\n");
  while(1);
}

static void taskBFunction(){
  printf("Hello from task B!\n");
  while(1); 
}
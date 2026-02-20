#include <Arduino.h>

#define LED1         PIN_D1
#define LED2         PIN_C7
#define LED3         PIN_A2

static uint32_t notInit __attribute__ ((section (".noinit")));// Purposedly uninitialized variable.

#ifdef RTOS_ENABLED
void task1(void *pvParameters) {
  (void)(pvParameters); // Suppress "unused parameter" warning
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, LOW);
  while (1) {
    digitalToggle(LED1);
    vTaskDelay(500);
  }
}

void task2(void *pvParameters) {
  (void)(pvParameters);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED2, LOW);
  while (1) {
    digitalToggle(LED2);
    vTaskDelay(300);
  }
}

void task3(void *pvParameters) {
  (void)(pvParameters);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED3, LOW);
  while (1) {
    digitalToggle(LED3);
    vTaskDelay(800);
  }
}
#endif

void setup() {
  Serial.begin(115200);// Implemented ( NOT TESTED YET )
  Serial.println("Powered UP!");
#ifdef RTOS_ENABLED
  BaseType_t xReturned;
  xReturned = xTaskCreate(
      task1,                    // Task function point
      "Task1",                  // Task name
      configMINIMAL_STACK_SIZE, // Use the minimum stack size, each take 4 bytes(32bit)
      NULL,                     // Parameters
      2,                        // Priority
      NULL);                    // Task handler
  if (xReturned != pdPASS) {
    while (1);
  }

  xReturned = xTaskCreate(task2, "Task2", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
  if (xReturned != pdPASS) {
    while (1);
  }

  xReturned = xTaskCreate(task3, "Task3", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
  if (xReturned != pdPASS) {
    while (1);
  }

  vTaskStartScheduler();
#else
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, LOW);
#endif
}

void loop() {
#ifndef RTOS_ENABLED
  delay(1000);// Implemented both, baremetal and RTOS ( NOT TESTED YET )
  notInit++;
  digitalWrite(LED1, notInit);
#endif
}

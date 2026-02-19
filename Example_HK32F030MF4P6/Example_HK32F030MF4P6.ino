#include <Arduino.h>

#define LED1         PIN_D1
#define LED2         PIN_C7
#define LED3         PIN_A2
#define LED4         PIN_A3

static uint32_t notInit __attribute__ ((section (".noinit")));// Purposedly uninitialized variable.

#ifdef RTOS_ENABLED
void task1(void *pvParameters) {
  (void)(pvParameters); // Suppress "unused parameter" warning
  while (1) {
    digitalToggle(LED1);
    vTaskDelay(500);
  }
}

void task2(void *pvParameters) {
  (void)(pvParameters);
  while (1) {
    digitalToggle(LED2);
    vTaskDelay(300);
  }
}

void task3(void *pvParameters) {
  (void)(pvParameters);
  while (1) {
    digitalToggle(LED3);
    vTaskDelay(800);
  }
}
#endif

void setup() {
  Serial.begin(115200);// Implemented ( NOT TESTED YET )
  Serial.println("Powered UP!");
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
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
#endif
}

void loop() {
  delay(1000);// Implemented both, baremetal and RTOS ( NOT TESTED YET )
  notInit++;
  digitalWrite(LED4, notInit);
}

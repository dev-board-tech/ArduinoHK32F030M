#include <Arduino.h>

// LED1: PD1
#define LED1_GPIO_PORT        GPIOD
#define LED1_GPIO_CLK         RCC_AHBPeriph_GPIOD
#define LED1_GPIO_PIN         GPIO_Pin_1
// LED2: PC7
#define LED2_GPIO_PORT        GPIOC
#define LED2_GPIO_CLK         RCC_AHBPeriph_GPIOC
#define LED2_GPIO_PIN         GPIO_Pin_7
// LED3: PA2
#define LED3_GPIO_PORT        GPIOA
#define LED3_GPIO_CLK         RCC_AHBPeriph_GPIOA
#define LED3_GPIO_PIN         GPIO_Pin_2

static uint32_t notInit __attribute__ ((section (".noinit")));

void LED_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  // Enable AHB Clock
  RCC_AHBPeriphClockCmd(LED1_GPIO_CLK | LED2_GPIO_CLK | LED3_GPIO_CLK, ENABLE);

  // LED1: Output, push-pull, speed 10Mhz
  GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);

  // LED2
  GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;
  GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);

  // LED3
  GPIO_InitStructure.GPIO_Pin = LED3_GPIO_PIN;
  GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);

  // Turn off all
  GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
  GPIO_ResetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);
  GPIO_ResetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);
}

void task1(void *pvParameters) {
  (void)(pvParameters); // Suppress "unused parameter" warning
  while (1) {
    GPIO_Toggle(LED1_GPIO_PORT, LED1_GPIO_PIN);
    vTaskDelay(500);
  }
}

void task2(void *pvParameters) {
  (void)(pvParameters);
  while (1) {
    GPIO_Toggle(LED2_GPIO_PORT, LED2_GPIO_PIN);
    vTaskDelay(300);
  }
}

void task3(void *pvParameters) {
  (void)(pvParameters);
  while (1) {
    GPIO_Toggle(LED3_GPIO_PORT, LED3_GPIO_PIN);
    vTaskDelay(800);
  }
}

void setup() {
  Serial.begin(115200);//Not implemented yet
  LED_GPIO_Config();
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
}

void loop() {
  delay(500);//Not implemented yet
  notInit++;
  GPIO_Write(LED1_GPIO_PORT, notInit);
}

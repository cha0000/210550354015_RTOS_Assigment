//Create 3 realtime tasks each with the periodcity T1=1000ms, T2=2000ms, T3=5000ms. Also create use oneshot software timer to trigger a callback function from T3 after 10000ms.//
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"



void *const timer_Id;
TimerHandle_t callback_handle;

void Callback_function(TimerHandle_t xTimer)
{
    printf("OneShot Timer callback\n");
}

void temperature_task(void *data)
{
    while(1)
    {
        printf("In Temperature Task\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS );
    }
}

void pressure_task(void *data)
{
    while(1)
    {
        printf("In Pressure task\n");
        vTaskDelay(2000 / portTICK_PERIOD_MS );
    }
}

void uart_task(void *data)
{

    
    callback_handle = xTimerCreate("my_timer",(10000 / portTICK_PERIOD_MS),pdFALSE,timer_Id,Callback_function);

    xTimerStart(callback_handle, 1); 
    while (1)
    {
        printf("In UART\n");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}


void app_main(void)
{
    
    xTaskCreate(temperature_task, "task1", 2048, NULL, 1, NULL);
    xTaskCreate(pressure_task, "task2", 2028, NULL, 2, NULL);
    xTaskCreate(uart_task, "task3", 2028, NULL, 3, NULL);
    while (1) 
    {
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

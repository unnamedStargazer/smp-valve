#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lora.h"
#include "esp_log.h"

void task_tx(void *p)
{
    bool dioPin = false;
    for(;;) {
        vTaskDelay(pdMS_TO_TICKS(5000));
        lora_send_packet((uint8_t*)"Hello", 5);
        ESP_LOGI("test", "packet sent");
    }
}

void task_lora_init()
{
    lora_init();
    lora_write_reg(REG_DIO_MAPPING_1, (1 << 6));
    lora_set_frequency(915e6);
    lora_enable_crc();
    vTaskDelete(NULL);
}

void app_main()
{
    xTaskCreate(&task_lora_init, "task_lora_init", 2048, NULL, 6, NULL);
    xTaskCreate(&task_tx, "task_tx", 2048, NULL, 5, NULL);
}

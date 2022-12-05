
#include "esp_log.h"
#include "net.c"


void set_log(){
    #ifdef DEBUG
        esp_log_level_set("*", ESP_LOG_INFO);
        esp_log_level_set("MQTT_CLIENT", ESP_LOG_VERBOSE);
        esp_log_level_set("MQTT_EXAMPLE", ESP_LOG_VERBOSE);
        esp_log_level_set("TRANSPORT_TCP", ESP_LOG_VERBOSE);
        esp_log_level_set("TRANSPORT_SSL", ESP_LOG_VERBOSE);
        esp_log_level_set("TRANSPORT", ESP_LOG_VERBOSE);
        esp_log_level_set("OUTBOX", ESP_LOG_VERBOSE);
    #else
        esp_log_level_set("*", ESP_LOG_ERROR);
        esp_log_level_set("MQTT_CLIENT", ESP_LOG_ERROR);
        esp_log_level_set("MQTT_EXAMPLE", ESP_LOG_ERROR);
        esp_log_level_set("TRANSPORT_TCP", ESP_LOG_ERROR);
        esp_log_level_set("TRANSPORT_SSL", ESP_LOG_ERROR);
        esp_log_level_set("TRANSPORT", ESP_LOG_ERROR);
        esp_log_level_set("OUTBOX", ESP_LOG_ERROR);
    #endif
}

void app_main()
{
    err_code = 0;
    err_msg = "";
    ESP_LOGI(TAG, "[APP] Startup..");
    //ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    //ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());
    set_log();
    //ESP_ERROR_CHECK(nvs_flash_init());

    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA"); 
    wifi_main();
    //xTaskCreatePinnedToCore(SENS01, "SENS01", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL, APP_CPU_NUM);
}

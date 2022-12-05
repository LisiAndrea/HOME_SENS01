#include "esp_log.h"
#include "mqtt_client.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "sensors.c"



esp_mqtt_client_handle_t client;
char rTopic[TOPIC_MAX_LEN];
int msg_id = 0;


void manage_mqtt_request(esp_mqtt_event_handle_t ev){
    client = ev->client;
    strncpy(rTopic, ev->topic + TOPIC_START_LEN, (size_t)TOPIC_MAX_LEN);
    if(strncmp(rTopic, "READ", 4) == 0){
        strncpy(rTopic, rTopic + 5, (size_t)8);
        printf("-----------------------------------------------");
        if(strncmp(rTopic, "TMP", 3) == 0){
            
            char *dt = read_sensors();
            msg_id = esp_mqtt_client_publish(client, WRITE_TMP_TOPIC, dt, 0, 0, 0);
            //ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
            
        }else if(strncmp(rTopic, "HUM", 3) == 0){
            char *dt = read_sensors();
            msg_id = esp_mqtt_client_publish(client, WRITE_HUM_TOPIC, dt, 0, 0, 0);
            //ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
            
        }else if(strncmp(rTopic, "LUX", 3) == 0){
            char *dt = read_sensors();
            msg_id = esp_mqtt_client_publish(client, WRITE_LUX_TOPIC, dt, 0, 0, 0);
            //ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
            
        }else if(strncmp(rTopic, "ALL", 3) == 0){
            char *dt = read_sensors();
            msg_id = esp_mqtt_client_publish(client, WRITE_ALL_TOPIC, dt, 0, 0, 0);
            //ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
            
        }else{
            ESP_LOGI("Undefined READ topic: %s", rTopic);
            goto END_REQ;
        }

        printf("-----------------------------------------------");
    }else if(strncmp(rTopic, "SYS", 3) == 0){
        strncpy(rTopic, rTopic + 4, (size_t)11);
        if(strncmp(rTopic, "RESTART", 11) == 0){
            printf("SYS_RESTART");
            esp_restart();
        }else if(strncmp(rTopic, "DETAIL", 10) == 0){
            printf("SYS_DETAIL");
        }else{
            ESP_LOGI("Undefined SYS topic: %s", rTopic);
            goto END_REQ;
        }
    }
    END_REQ:
        memset(rTopic, 0, sizeof rTopic);
}

static esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event)
{
    client = event->client;
    
    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
            uint8_t array_size = sizeof(sub_topic) / sizeof(sub_topic[0]);
            for(int i = 0; i<array_size; i++){
                msg_id = esp_mqtt_client_subscribe(client, sub_topic[i], 0);
                ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
            }
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            vTaskDelay(  30000 / portTICK_PERIOD_MS );
            esp_restart();
            break;

        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            //msg_id = esp_mqtt_client_publish(client, "/ready", "I'm ready", 0, 0, 0);
            ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            vTaskDelay(  30000 / portTICK_PERIOD_MS );
            esp_restart(); 
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "MQTT_EVENT_DATA");
            manage_mqtt_request(event);
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            vTaskDelay(  30000 / portTICK_PERIOD_MS );
            esp_restart();
            break;
        default:
            ESP_LOGI(TAG, "Other event id:%d", event->event_id);
            break;
    }
    return ESP_OK;
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    mqtt_event_handler_cb(event_data);
}



static void mqtt_app_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .uri = MQTT_BROKER_URL,
        .username = MQTT_CLIENT_NAME,
        .password = MQTT_CLIENT_PWD,
    };

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);
    esp_mqtt_client_start(client);
}


void mqtt_main(){
    mqtt_app_start();
    sensor_main();
}
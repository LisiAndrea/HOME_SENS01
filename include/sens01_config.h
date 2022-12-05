

/*-------------DEFINE DIRECTIVES----------*/
#define DEBUG TRUE

// GPIO PINS
#define DHT_GPIO 0
#define SDA_GPIO 4
#define SCL_GPIO 5

//#define MAX_LUX_VAL 54612

// BH1750 CAPTURE RESOLUTION
#define ADDR BH1750_ADDR_LO


// NETWORK DETAILS
#define EXAMPLE_ESP_WIFI_SSID      "SHOME-800"//CONFIG_ESP_WIFI_SSID
#define EXAMPLE_ESP_WIFI_PASS      "testnetwork"//CONFIG_ESP_WIFI_PASSWORD
#define HOSTNAME                    "SENS01"
#define EXAMPLE_ESP_MAXIMUM_RETRY  20//CONFIG_ESP_MAXIMUM_RETRY
#define WIFI_CONNECTED_BIT BIT0     // WIFI connected
#define WIFI_FAIL_BIT      BIT1     // wifi not connected after max retries 

// MQTT BROKER DETAILS
#define MQTT_CLIENT_NAME    "sens01"
#define MQTT_CLIENT_PWD     "pwd"
#define MQTT_BROKER_URL     "mqtt://192.168.8.206:1883"

// MQTT WRITE TOPCS
#define WRITE_ALL_TOPIC     "/SENS/01/WRITE/ALL"
#define WRITE_TMP_TOPIC     "/SENS/01/WRITE/TMP"
#define WRITE_HUM_TOPIC     "/SENS/01/WRITE/HUM"
#define WRITE_LUX_TOPIC     "/SENS/01/WRITE/LUX"
#define WRITE_SYS_TOPIC     "/SENS/01/SYS/RESPONSE"

/* The following are used to split reveived message topics 
    to distinguish the different requests                   */
#define TOPIC_MAX_LEN 20
#define TOPIC_START_LEN 9


static const char *ERR_NUM = "1";
static const char *TAG = "SENS01";


// MQTT SUBSCRIBE TOPICS
static char * sub_topic[] = {
    "/SENS/01/READ/ALL",
    "/SENS/01/READ/HUM",
    "/SENS/01/READ/TMP",
    "/SENS/01/READ/LUX",
    "/SENS/01/SYS/RESTART",
    "/SENS/01/SYS/DETAIL"
};


// STRUCTURE WHICH WILL BE USED TO READ DATA AND BUILD JSON
struct sens_data {
    int16_t temp;
    int16_t hum;
    uint16_t lux;
    uint16_t err_code;
    char *err_msg;
} sens_data;

static struct sens_data *rSensor = &sens_data;
//#include <stdio.h>
//#include <string.h>
#include "json.c"
#include <bh1750.h>
#include <dht.h>



// global variables
i2c_dev_t dev;
int16_t temp;
int16_t hum;
uint16_t lux;
uint16_t err_code = 0;
char *err_msg;


// functions
void read_DHT021(){
    if (dht_read_data(DHT_TYPE_AM2301, DHT_GPIO, &hum, &temp) != ESP_OK){
        //err_code = 1;
        //err_msg = "Could not read data from sensor\n";
        rSensor->err_code = 1;
        rSensor->err_msg = "Could not read data from sensor\n";
    }else{
        temp /= 10;
        hum /= 10;
        rSensor->temp =  temp;
        rSensor->hum = hum;
    }
}

void read_BH1750(){
    if (bh1750_read(&dev, &lux) != ESP_OK){
        //err_code = 1;
        //err_msg = "Could not read lux data\n";
        rSensor->err_code = 1;
        rSensor->err_msg ="Could not read lux data\n";
    }else{
        //printf("%d\n",lux);
        //lux = (lux*100) / MAX_LUX_VAL;
        //printf("%d\n",lux);
        rSensor->lux = lux;
    }
}

void initialize_BH1750(){
    ESP_ERROR_CHECK(i2cdev_init());
    memset(&dev, 0, sizeof(i2c_dev_t)); // Zero descriptor
    ESP_ERROR_CHECK(bh1750_init_desc(&dev, ADDR, 0, SDA_GPIO, SCL_GPIO));
    ESP_ERROR_CHECK(bh1750_setup(&dev, BH1750_MODE_CONTINUOUS, BH1750_RES_HIGH));
}

void finalize_BH1750(){
   
}



void print_data(){
    if(err_code == 0){
        printf("Temp: %dC, Hum: %d%%, Lux: %d lux\n",temp,hum,lux);
        printf("Temp: %dC, Hum: %d%%\n", rSensor->temp, rSensor->hum);
        printf("Lux: %d\n", rSensor->lux);
    }else{
        printf("ERROR");
    }
}


char* read_sensors(){
    read_DHT021();
    read_BH1750();
    print_data();
    /*if (err_code != 0){
        rSensor->err_code = 1;
        rSensor->err_msg = err_msg;
    }else{
        rSensor->temp =  temp;
        rSensor->hum = hum;
        rSensor->lux = lux;
        rSensor->err_code = 0;
    }*/
    char *res =build_json();
    printf("RES: %s", res); 
    return res;
}

void sensor_main(){
    initialize_BH1750();
}
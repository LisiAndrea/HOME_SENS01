#include <cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sens01_config.h"


cJSON *id_obj = NULL;
cJSON *tmp_obj = NULL;
cJSON *hum_obj = NULL;
cJSON *lux_obj = NULL;
cJSON *err_obj = NULL;
cJSON *err_num = NULL;
cJSON *sens01;
int length;
char* ttmp;
char* thum;
char* tlux;
char* jString;


char* build_json(){
    
    sens01 = cJSON_CreateObject();

    if (sens01 == NULL){
        fprintf(stderr, "Failed to create obj.\n");
        cJSON_Delete(sens01);
        return "{}";
    }

    id_obj = cJSON_CreateString("SENS01");
    if (id_obj == NULL){
        fprintf(stderr, "Failed to create string.\n");
        cJSON_Delete(sens01);
        return "{}";
    }
    cJSON_AddItemToObject(sens01, "sender", id_obj);

    if(rSensor->err_code !=0){
        err_obj = cJSON_CreateString(ttmp);
        if (err_obj == NULL){
            fprintf(stderr, "Failed to create error msg.\n");
            cJSON_Delete(sens01);
            return "{}";
        }
        cJSON_AddItemToObject(sens01, "msg", err_obj);
        err_num = cJSON_CreateString(ERR_NUM);
        if (err_num == NULL){
            fprintf(stderr, "Failed to create error.\n");
            cJSON_Delete(sens01);
            return "{}";
        }
        cJSON_AddItemToObject(sens01, "error", err_num);
    }else{
        length = snprintf( NULL, 0, "%d", rSensor->temp );
        ttmp = malloc( length + 1 );
        snprintf( ttmp, length + 1 , "%d", rSensor->temp );
        tmp_obj =  cJSON_CreateString(ttmp);//cJSON_CreateNumber((double)temp);
        if (tmp_obj == NULL){
            fprintf(stderr, "Failed to create temp.\n");
            cJSON_Delete(sens01);
            return "{}";
        }
        cJSON_AddItemToObject(sens01, "temp", tmp_obj);

        length = snprintf( NULL, 0, "%d", rSensor->hum );
        thum = malloc( length + 1 );
        snprintf( thum, length + 1 , "%d", rSensor->hum );
        hum_obj = cJSON_CreateString(thum);
        if(hum_obj == NULL){
        fprintf(stderr, "Failed to create temp.\n");
            cJSON_Delete(sens01);
            return "{}";
        }
        cJSON_AddItemToObject(sens01, "hum", hum_obj);

        length = snprintf( NULL, 0, "%d", rSensor->lux );
        tlux = malloc( length + 1 );
        snprintf( tlux, length + 1 , "%d", rSensor->lux );
        lux_obj = cJSON_CreateString(tlux);
        if(hum_obj == NULL){
        fprintf(stderr, "Failed to create temp.\n");
            cJSON_Delete(sens01);
            return "{}";
        }
        cJSON_AddItemToObject(sens01, "lux", lux_obj);

    }

    jString = cJSON_PrintUnformatted(sens01);
    cJSON_Delete(sens01);
    //free_vars();
    if (jString == NULL)
    {
        fprintf(stderr, "Failed to print json.\n");
        return "{}";
    }else{
        return jString;
    }
   
}


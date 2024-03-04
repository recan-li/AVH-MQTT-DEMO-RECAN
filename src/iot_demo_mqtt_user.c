
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "iot_demo_logging.h"
#include "logging_stack.h"
#include "aws_clientcredential.h"
#include "iot_demo_mqtt_user.h"
#include "cJSON.h"
#include "iot_threads.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"

static int g_light_id = 5;
static int g_light_id5_value = 0;
static char g_light_name[64] = "告警指示灯";

int iot_demo_mqtt_check_user_configuration(void)
{
    LogInfo( ("Test to %s with %s", clientcredentialMQTT_BROKER_ENDPOINT, clientcredentialIOT_THING_NAME) );
    if (strlen(clientcredentialMQTT_BROKER_ENDPOINT) == 0 && strlen(clientcredentialIOT_THING_NAME) == 0) {
        LogInfo( ( "Empty user configuration is detected. Please check your 'iot_demo_mqtt_config.sh' file" ) );
        while(1);
    }
    return 0;
}

int iot_demo_mqtt_data_process(const uint8_t *data, uint16_t len)
{
	int ret = 0;
	int light_id = 0;
	int light_value = 0;
	char *light_name = NULL;

    printf("incoming msg: %s\n", (char *)data);

    cJSON * root = cJSON_Parse((char *)data);
    if(root == NULL){
        LogInfo(("-----no root-----"));
        goto exit_entry;
    }

    cJSON * idx = cJSON_GetObjectItem(root, "idx");
    if(!idx){
        LogInfo(("-----no idx-----"));
        goto exit_entry;
    } else {
    	light_id = idx->valueint;
    }

    cJSON * value = cJSON_GetObjectItem(root, "nvalue");
    if(!value){
        LogInfo(("-----no value-----"));
        goto exit_entry;
    } else {
    	light_value = value->valueint;
    }

    cJSON * name = cJSON_GetObjectItem(root, "name");
    if(!name){
        LogInfo(("-----no name-----"));
        goto exit_entry;
    } else {
    	light_name = name->valuestring;
    } 

    LogInfo(("<--- light (%d) <%s> [%s]", light_id, light_name, light_value ? "ON" : "OFF"));

    if (g_light_id == light_id) {
    	g_light_id5_value = light_value;
    	memcpy(g_light_name, light_name, strlen(light_name));
    }

exit_entry:

	if (root) {
		cJSON_Delete(root);
	}

    return ret;
}

extern int mqtt_public_msg(void *data, uint16_t len);
int iot_demo_mqtt_update_device_status(int id, int value)
{
	cJSON *root = cJSON_CreateObject();
    
    cJSON_AddItemToObject(root, "idx", cJSON_CreateNumber(id));
    cJSON_AddItemToObject(root, "nvalue", cJSON_CreateNumber(value));
    char *ptr = cJSON_PrintUnformatted(root);
    LogInfo(("report msg: %s", ptr));
    mqtt_public_msg(ptr, strlen(ptr));
    cJSON_free_ex(ptr);
    cJSON_Delete(root);

    return 0;
}

static void iot_Demo_mqtt_loop_task(void *arg)
{
	int cnt = 0;

	while (1) {
		vTaskDelay( pdMS_TO_TICKS( 10000 ) );
		cnt++;
		LogInfo(("---> cnt %d", cnt));
		g_light_id5_value = !g_light_id5_value;
		LogInfo(("---> light (%d) <%s> [%s]", g_light_id5_value, g_light_name, g_light_id5_value ? "ON" : "OFF"));
		iot_demo_mqtt_update_device_status(g_light_id, g_light_id5_value);
	}
}

int iot_demo_mqtt_start(void)
{
	Iot_CreateDetachedThread(iot_Demo_mqtt_loop_task, NULL, 1, 1024 );
	return 0;
}

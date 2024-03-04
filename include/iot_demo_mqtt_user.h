
#ifndef __IOT_DEMO_MQTT_USER_H__
#define __IOT_DEMO_MQTT_USER_H__

extern int iot_demo_mqtt_start(void);
extern int iot_demo_mqtt_update_device_status(int id, int value);
extern int iot_demo_mqtt_data_process(const uint8_t *data, uint16_t len);
extern int iot_demo_mqtt_check_user_configuration(void);

#endif /* __IOT_DEMO_MQTT_USER_H__ */

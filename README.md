
# Introduce

This is an ARM based AVH mirror simulation Cortex-M7 chip platform for building an intelligent IoT terminal project. The terminal side uses the MQTT protocol to interact with the cloud, achieving reporting of terminal information and responding to control instructions issued by the cloud.

# Project file structure

```sh
├── AVH-AWS_MQTT_Demo
│   ├── amazon-freertos                     # amazon-freertos source files  
│   ├── app_main.c                          # appliacation entry source file
│   ├── avh.yml                             # avh configarution file
│   ├── AWS_MQTT_MutualAuth.IMXRT1050-EVKB_ESP8266.cprj     # MDK project file
│   ├── AWS_MQTT_MutualAuth.uvoptx                          # MDK project file
│   ├── AWS_MQTT_MutualAuth.uvprojx                         # MDK project file
│   ├── AWS_MQTT_MutualAuth.VHT_MPS2_Cortex-M7.cprj         # MDK project file
│   ├── Board                               # Board msg
│   ├── build.py                            # build python file for AVH-AWS_MQTT_Demo project
│   ├── config_files                        # AVH-AWS_MQTT_Demo configuration files
│   ├── IMXRT1050-EVKB.mex                  # IMXRT1050-EVKB mex file
│   ├── Interfaces                          # API for iot demo
│   ├── LICENSE                             # license file
│   ├── mdk_config.txt                      # mdk configuration
│   ├── README.md                           # readme for AVH-AWS_MQTT_Demo
│   ├── requirements.txt                    # python requirements file
│   ├── RTE
│   └── vht_config.txt                      # vht configuration file
├── config
│   └── iot_demo_mqtt_config.sh             # user configuration
├── include
│   ├── cJSON.h                             # cjson util header file
│   └── iot_demo_mqtt_user.h                # user demo header file
├── Makefile                                # Makefile for project building
├── README.md                               # This readme file
└── src
    ├── cJSON.c                             # cjson util source file
    └── iot_demo_mqtt_user.c                # user demog source file
```

# Steps for test this demo

1. Clone this project from github.
2. Read this README file and `make help` to get more help msg.
3. Install python tolls by `make pip`
4. Install some other tools, such as cbuild and cpackget.
5. `make all` to build this project, or make it step by step: 
   `make source` -> `make clean` -> `make build` -> `make run`
6. When you see the following logs, you are lucky to run this demo well.

```sh
Running ...
/opt/VHT/VHT_MPS2_Cortex-M7 --stat --simlimit 800 -f AVH-AWS_MQTT_Demo/vht_config.txt out/image.axf
telnetterminal0: Listening for serial connection on port 5000
telnetterminal1: Listening for serial connection on port 5001
telnetterminal2: Listening for serial connection on port 5002
[    0          1] [iot_thread] [INFO ][DEMO][1] ---------STARTING DEMO---------


[    1          9] [iot_thread] [INFO ][INIT][9] SDK successfully initialized.

[    2         17] [iot_thread] [INFO ][DEMO][17] Successfully initialized the demo. Network type for the demo: 4

[    3         29] [iot_thread] [INFO] Test to recan-li.cn with recan's demo device
[    4         36] [iot_thread] [INFO] Creating a TLS connection to recan-li.cn:1883.
[    5        105] [iot_thread] [INFO] Creating an MQTT connection to recan-li.cn.
[    6        142] [iot_thread] [INFO] Packet received. ReceivedBytes=2.
[    7        148] [iot_thread] [INFO] CONNACK session present bit not set.
[    8        156] [iot_thread] [INFO] Connection accepted.
[    9        161] [iot_thread] [INFO] Received MQTT CONNACK successfully from broker.
[   10        170] [iot_thread] [INFO] MQTT connection established with the broker.
[   11        178] [iot_thread] [INFO] An MQTT connection is established with recan-li.cn.
[   12        186] [iot_thread] [INFO] Attempt to subscribe to the MQTT topic domoticz/out.
[   13        195] [iot_thread] [INFO] SUBSCRIBE sent for topic domoticz/out to broker.
[   14        223] [iot_thread] [INFO] Packet received. ReceivedBytes=3.
[   15        230] [iot_thread] [INFO] Subscribed to the topic domoticz/out with maximum QoS 1.
[   16      10028] [iot_thread] [INFO] ---> cnt 1
[   17      10032] [iot_thread] [INFO] ---> light (1) <告警指示灯> [ON]
[   18      10040] [iot_thread] [INFO] report msg: {"idx":5,"nvalue":1}
[   19      10107] [iot_thread] [INFO] Packet received. ReceivedBytes=2.
[   20      10113] [iot_thread] [INFO] Ack packet deserialized with result: MQTTSuccess.
[   21      10122] [iot_thread] [INFO] State record updated. New state=MQTTPublishDone.
[   22      10130] [iot_thread] [INFO] PUBACK received for packet Id 2.
[   23      20047] [iot_thread] [INFO] ---> cnt 2
[   24      20051] [iot_thread] [INFO] ---> light (0) <告警指示灯> [OFF]
[   25      20059] [iot_thread] [INFO] report msg: {"idx":5,"nvalue":0}
[   26      20276] [iot_thread] [INFO] Packet received. ReceivedBytes=2.
[   27      20283] [iot_thread] [INFO] Ack packet deserialized with result: MQTTSuccess.
[   28      20291] [iot_thread] [INFO] State record updated. New state=MQTTPublishDone.
[   29      20299] [iot_thread] [INFO] PUBACK received for packet Id 3.
```


MQTT_DEMO_PATH 		:= AVH-AWS_MQTT_Demo
USER_CONFIG_PATH 	:= config
OUT_PATH 			:= out
AVH_SIMLIMIT_TIME 	:= 800

all: source clean build run

help:
	@echo "make help 	-> Show this help msg."
	@echo "make source 	-> Install env parameters."
	@echo "make build 	-> Build thie demo."
	@echo "make clean 	-> Clean object files."
	@echo "make run 	-> Run this demo."
	@echo "make debug 	-> Build & run this demo."
	@echo "make all 	-> Source & clean & build & run all together."
	@echo "make pip 	-> Install python tools by pip."

debug: build run

source:	
	@echo "Install env parameters ..."
	@dos2unix $(USER_CONFIG_PATH)/iot_demo_mqtt_config.sh; \
	. $(USER_CONFIG_PATH)/iot_demo_mqtt_config.sh; \
	cd $(MQTT_DEMO_PATH)/amazon-freertos/demos/include; \
	envsubst <aws_clientcredential.h.in >aws_clientcredential.h; \
	envsubst <aws_clientcredential_keys.h.in >aws_clientcredential_keys.h

build:
	@echo "Building ..."
	@test -e $(OUT_PATH) || mkdir -p $(OUT_PATH)
	cbuild --packs $(MQTT_DEMO_PATH)/AWS_MQTT_MutualAuth.VHT_MPS2_Cortex-M7.cprj
	@cp -rf $(MQTT_DEMO_PATH)/Objects/image.elf $(OUT_PATH)

run:
	@echo "Running ..."
	/opt/VHT/VHT_MPS2_Cortex-M7 --stat --simlimit $(AVH_SIMLIMIT_TIME) -f $(MQTT_DEMO_PATH)/vht_config.txt $(OUT_PATH)/image.elf

clean:
	@echo "Clean ..."
	rm -rf $(MQTT_DEMO_PATH)/Objects/
	rm -rf $(OUT_PATH)
	rm -rf aws_mqtt*.zip

pip:
	pip install -r $(MQTT_DEMO_PATH)/requirements.txt 

.PHONY: all source clean build run help

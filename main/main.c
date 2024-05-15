#include <stdio.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/twai.h"
#include "driver/gpio.h"

//#define CONFIG_HUMAN_READABLE 1
 
#define TWAI_TIMING_CONFIG_33_3KBITS()    {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 400000, .brp = 0, .tseg_1 = 8, .tseg_2 = 3, .sjw = 3, .triple_sampling = false}

void app_main()
{
    //Initialize configuration structures using macro initializers
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(GPIO_NUM_11, GPIO_NUM_12, TWAI_MODE_NORMAL);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_33_3KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    //Install TWAI driver
    if (twai_driver_install(&g_config, &t_config, &f_config) == ESP_OK) {
        printf("Driver installed\n");
    } else {
        printf("Failed to install driver\n");
        return;
    }




    //Start TWAI driver
    if (twai_start() == ESP_OK) {
        printf("Driver started\n");
    } else {
        printf("Failed to start driver\n");
        return;
    }

    while (1) {
        //Wait for message to be received
        twai_message_t message;
        if (twai_receive(&message, pdMS_TO_TICKS(10000)) == ESP_OK) {
            //printf("Message received\n");
        } else {
            //printf("Failed to receive message\n");
        }
        

        #ifdef CONFIG_HUMAN_READABLE 
        
        //Process received message
        if (message.extd) {
            printf("Message is in Extended Format\n");
        } else {
            printf("Message is in Standard Format\n");
        }
        printf("ID is %x\n", (int)message.identifier);
        if (!(message.rtr)) {
            for (int i = 0; i < message.data_length_code; i++) {
                printf("%x ", message.data[i]);
            }
            printf("\n");
        }
        #else

        printf("%lx,%x,%x,%x%x%x%x%x%x%x%x\n", message.identifier, message.rtr, 0, message.data[0], message.data[1], message.data[2], message.data[3], message.data[4], message.data[5], message.data[6], message.data[7]);

        #endif

    }

}
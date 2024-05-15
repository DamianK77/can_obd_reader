# ESP-IDF program for car CAN bus decoding

This program reads can messages and sends them over serial so that it can be parsed by this software from adamtheone https://github.com/adamtheone/canDrive. Written for ESP32 S3.

## Functions
- Reading CAN bus in both human-readable and machine readable form

## How to use
I am using a SN65HVD230 transciever to send the messages. it should work effortlessly as long as you connect to the right pins on your car's manufacturer's OBD2 connector. I added a definition for can timings for Opel Low Speed CAN Bus as it was needed to decode steering wheel buttons which communicate using the low speed can bus (pin 1 of obd plug on my Vectra C). You have to set your own CAN speed by replacing TWAI_TIMING_CONFIG_33_3KBITS in the t_config definition to match your car's speed.

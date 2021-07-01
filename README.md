# timer_and_led_adruino

## Scheme:
               +-(+LED-)-(R)--+
               |              |
    +--------------------------------+
    |         D5             GND     |
    |                                |
    |    Arduino Nano Atmega 328     |
    +--------------------------------+

## Notes:

    * Serial port 115200 Baud Rate
    * On this version, if the timer set command comes multiple times, last one overrides old requests.
#ifndef __DIGITAL_LED_H
#define __DIGITAL_LED_H	

#define LED_NUM1        PAout(4)
#define LED_NUM2        PAout(5)
#define LED_NUM3        PAout(6)

#define LED_SCLK        PBout(1)
#define LED_RCLK        PBout(0)
#define LED_OE          PCout(5)
#define LED_SDI         PCout(4)

void led_display(void);
void digital_led_gpio_init(void);
void digital_led_check(void);

#endif
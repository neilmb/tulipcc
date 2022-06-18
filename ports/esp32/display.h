// display.h

#ifndef __DISPLAYH__
#define __DISPLAYH__

#include "sdkconfig.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_rgb.h"
#include "esp_lcd_types.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include <time.h>
#include <string.h>
#include "esp_random.h"
#include "tulip_helpers.h"
#include "lodepng.h"
#include "driver/ledc.h"


#define RGB332



uint8_t bg_pal_color;
uint8_t tfb_fg_pal_color;
uint8_t tfb_bg_pal_color;
uint8_t ansi_active_bg_color; 
uint8_t ansi_active_fg_color; 
int16_t ansi_active_format;

#define TULIP_TEAL 9
static const uint8_t ansi_pal[256] = {
0, 128, 16, 144, 2, 130, 18, 219, 146, 224, 28, 252, 3, 227, 31, 255, 0, 1, 2, 2, 3, 3, 8, 9, 10, 10, 
11, 11, 16, 17, 18, 18, 19, 19, 20, 21, 22, 22, 23, 23, 24, 25, 26, 26, 27, 27, 28, 29, 30, 30, 31, 31, 
64, 65, 66, 66, 67, 67, 72, 73, 74, 74, 75, 75, 80, 81, 82, 82, 83, 83, 84, 85, 86, 86, 87, 87, 88, 89, 
90, 90, 91, 91, 92, 93, 94, 94, 95, 95, 128, 129, 130, 130, 131, 131, 136, 137, 138, 138, 139, 139, 144, 
145, 146, 146, 147, 147, 148, 149, 150, 150, 151, 151, 152, 153, 154, 154, 155, 155, 156, 157, 158, 158, 
159, 159, 160, 161, 162, 162, 163, 163, 168, 169, 170, 170, 171, 171, 176, 177, 178, 178, 179, 179, 180, 
181, 182, 182, 183, 183, 184, 185, 186, 186, 187, 187, 188, 189, 190, 190, 191, 191, 192, 193, 194, 194, 
195, 195, 200, 201, 202, 202, 203, 203, 208, 209, 210, 210, 211, 211, 212, 213, 214, 214, 215, 215, 216, 
217, 218, 218, 219, 219, 220, 221, 222, 222, 223, 223, 224, 225, 226, 226, 227, 227, 232, 233, 234, 234, 
235, 235, 240, 241, 242, 242, 243, 243, 244, 245, 246, 246, 247, 247, 248, 249, 250, 250, 251, 251, 252, 
253, 254, 254, 255, 255, 0, 0, 0, 36, 36, 36, 73, 73, 73, 109, 109, 109, 146, 146, 146, 146, 182, 182, 
182, 219, 219, 219, 255, 255
};


void display_set_bg_pixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b);
void display_get_bg_pixel(uint16_t x, uint16_t y, uint8_t *r, uint8_t *g, uint8_t *b);

void display_get_bg_bitmap_raw(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t *data);
void display_set_bg_bitmap_rgba(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t* data);
void display_set_bg_bitmap_raw(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t* data);

void display_load_sprite_rgba(uint32_t mem_pos, uint32_t len, uint8_t* data);
void display_load_sprite_raw(uint32_t mem_pos, uint32_t len, uint8_t* data);
void display_screenshot(char * filename);
void display_screenshot_pal(char * filename);
void display_tfb_str(char*str, uint16_t len, uint8_t format, uint8_t fg_color, uint8_t bg_color);

uint8_t display_get_clock();
void display_set_clock(uint8_t mhz);
void display_tfb_new_row();
void display_run();
void display_brightness(uint8_t amount);

void unpack_rgb_332(uint8_t px0, uint8_t *r, uint8_t *g, uint8_t *b);
void unpack_pal_idx(uint16_t pal_idx, uint8_t *r, uint8_t *g, uint8_t *b);
void unpack_ansi_idx(uint8_t ansi_idx, uint8_t *r, uint8_t *g, uint8_t *b);


extern const unsigned char font_8x12_r[256][12];

// can't use
// USB: D- = 19, D+ = 20
// 35, 36, 37 -- for quad psram
// PCLK on 38 or 13 didn't work -- bad image


// 12 -- 15.5FPS, fine
// 16 -- 18.7FPS, fine , some skips
// 18 -- 24.1FPS skips during long lines of TFB text but otherwise fine
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/_images/ESP32-S3_DevKitC-1_pinlayout.jpg

#define PIXEL_CLOCK_MHZ     18
#define BK_LIGHT_ON_LEVEL  1
#define DEFAULT_BRIGHTNESS 5 // 9 is max, 1 is min
#define BK_LIGHT_OFF_LEVEL !BK_LIGHT_ON_LEVEL
#define PIN_NUM_BK_LIGHT       39 // was 19, was 14 white
#define PIN_NUM_HSYNC          40
#define PIN_NUM_VSYNC          41
#define PIN_NUM_DE             42
#define PIN_NUM_PCLK           14 // was 38, was 20, was 13 black
#define PIN_NUM_BK_PWM		   16


// https://www.hotmcu.com/101-inch-1024x600-tft-lcd-display-with-capacitive-touch-panel-p-215.html
#define PIN_NUM_DATA0          12 //  B6, 14
#define PIN_NUM_DATA1          21 //  B7, 13

#define PIN_NUM_DATA2          8  //  G5, 23]
#define PIN_NUM_DATA3          3  // G6, 22]
#define PIN_NUM_DATA4          46 // G7, 21 pin 21 on the breakout... goes to G7...

#define PIN_NUM_DATA5         6   // R5, 31
#define PIN_NUM_DATA6         7   // R6, 30
#define PIN_NUM_DATA7         15  // R7, 29

//... We keep the rest as we have to drive them low while i have it plugged in, but i'm wroking on that...
#define PIN_NUM_DATA8          5 // B2
#define PIN_NUM_DATA9          5 // B1
#define PIN_NUM_DATA10         5 // B0
#define PIN_NUM_DATA11         5 // G2
#define PIN_NUM_DATA12         5 // G1
#define PIN_NUM_DATA13         5 // G0
#define PIN_NUM_DATA14         5 // R1
#define PIN_NUM_DATA15         5 // R0


#define PIN_NUM_DISP_EN        -1

// We can address this many moving things on screen
#define SPRITES 32
// We assume we can store 16 unique 32x32 sprite tiles, you can swap these out from RAM
#define SPRITE_RAM_BYTES (32*32*2*16) // 32KB

//These are from MCUxpresso for the HOTMCU 10.1
#define H_RES              1024
#define V_RES              600
#define HSYNC_BACK_PORCH 139
#define HSYNC_FRONT_PORCH 140
#define HSYNC_PULSE_WIDTH 20
#define VSYNC_BACK_PORCH 20
#define VSYNC_FRONT_PORCH 12
#define VSYNC_PULSE_WIDTH 20



#define SPI_LL_DATA_MAX_BIT_LEN (1 << 18)
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
extern int Cache_WriteBack_Addr(uint32_t addr, uint32_t size);
extern int Cache_Invalidate_Addr(uint32_t addr, uint32_t size);
extern uint32_t Cache_Start_DCache_Preload(uint32_t addr, uint32_t size, uint32_t order);
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))


#define OFFSCREEN_Y_PX 150
#define OFFSCREEN_X_PX 256

#ifdef RGB332
#define BYTES_PER_PIXEL 1
#else
#define BYTES_PER_PIXEL 2
#endif

#define FONT_HEIGHT 12
#define FONT_WIDTH 8
#define TFB_ROWS (V_RES/FONT_HEIGHT)
#define TFB_COLS (H_RES/FONT_WIDTH)
#define BOUNCE_BUFFER_SIZE_PX (H_RES*FONT_HEIGHT) 
#define BOUNCE_BUFFER_SIZE_BYTES (BOUNCE_BUFFER_SIZE_PX)

#define FLASH_FRAMES 12
#define ALPHA0 0x55
#define ALPHA1 0x53
#define ALPHA 0x55

#define FORMAT_INVERSE 0x80 
#define FORMAT_UNDERLINE 0x40
#define FORMAT_FLASH 0x20
#define FORMAT_BOLD 0x10 
#define FORMAT_STRIKE 0x08

#define SPRITE_IS_SPRITE 0x80
#define SPRITE_IS_LINE 0x40
#define SPRITE_IS_BEZIER 0x20
#define SPRITE_IS_ELLIPSE 0x10


uint8_t tfb_y_row; 
uint8_t tfb_x_col; 
uint8_t py_callback;
uint8_t task_screenshot;
uint8_t task_start;
uint8_t task_stop;
int32_t vsync_count;
uint8_t display_mhz;
uint8_t brightness;
float reported_fps;
float reported_gpu_usage;

// RAM for sprites and background FB
uint8_t *sprite_ram; // in IRAM
uint8_t * bg; // in SPIRAM


uint16_t *sprite_x_px;//[SPRITES]; 
uint16_t *sprite_y_px;//[SPRITES]; 
uint16_t *sprite_w_px;//[SPRITES]; 
uint16_t *sprite_h_px;//[SPRITES]; 
uint8_t *sprite_vis;//[SPRITES];
uint32_t *sprite_mem;//[SPRITES];

uint8_t *TFB;//[TFB_ROWS][TFB_COLS];
uint8_t *TFBfg;//[TFB_ROWS][TFB_COLS];
uint8_t *TFBbg;//[TFB_ROWS][TFB_COLS];
uint8_t *TFBf;//[TFB_ROWS][TFB_COLS];
uint16_t *x_offsets;//[V_RES];
uint16_t *y_offsets;//[V_RES];
int16_t *x_speeds;//[V_RES];
int16_t *y_speeds;//[V_RES];

uint32_t **bg_lines;//[V_RES];

#endif
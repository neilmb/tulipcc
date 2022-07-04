// Copyright 2018-2019 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "soc/rtc_io_periph.h"

const int rtc_io_num_map[SOC_GPIO_PIN_COUNT] = {
    RTCIO_GPIO0_CHANNEL,    //GPIO0
    RTCIO_GPIO1_CHANNEL,    //GPIO1
    RTCIO_GPIO2_CHANNEL,    //GPIO2
    RTCIO_GPIO3_CHANNEL,    //GPIO3
    RTCIO_GPIO4_CHANNEL,    //GPIO4
    RTCIO_GPIO5_CHANNEL,    //GPIO5
    RTCIO_GPIO6_CHANNEL,    //GPIO6
    RTCIO_GPIO7_CHANNEL,    //GPIO7
    RTCIO_GPIO8_CHANNEL,    //GPIO8
    RTCIO_GPIO9_CHANNEL,    //GPIO9
    RTCIO_GPIO10_CHANNEL,   //GPIO10
    RTCIO_GPIO11_CHANNEL,   //GPIO11
    RTCIO_GPIO12_CHANNEL,   //GPIO12
    RTCIO_GPIO13_CHANNEL,   //GPIO13
    RTCIO_GPIO14_CHANNEL,   //GPIO14
    RTCIO_GPIO15_CHANNEL,   //GPIO15
    RTCIO_GPIO16_CHANNEL,   //GPIO16
    RTCIO_GPIO17_CHANNEL,   //GPIO17
    RTCIO_GPIO18_CHANNEL,   //GPIO18
    RTCIO_GPIO19_CHANNEL,   //GPIO19
    RTCIO_GPIO20_CHANNEL,   //GPIO20
    RTCIO_GPIO21_CHANNEL,   //GPIO21
    -1,//GPIO22
    -1,//GPIO23
    -1,//GPIO24
    -1,//GPIO25
    -1,//GPIO26
    -1,//GPIO27
    -1,//GPIO28
    -1,//GPIO29
    -1,//GPIO30
    -1,//GPIO31
    -1,//GPIO32
    -1,//GPIO33
    -1,//GPIO34
    -1,//GPIO35
    -1,//GPIO36
    -1,//GPIO37
    -1,//GPIO38
    -1,//GPIO39
    -1,//GPIO40
    -1,//GPIO41
    -1,//GPIO42
    -1,//GPIO43
    -1,//GPIO44
    -1,//GPIO45
    -1,//GPIO46
    -1,//GPIO47
};

//Reg,Mux,Fun,IE,Up,Down,Rtc_number
const rtc_io_desc_t rtc_io_desc[SOC_RTCIO_PIN_COUNT] = {
    /*REG                    MUX select                    function select               Input enable                 Pullup                    Pulldown                  Sleep select                   Sleep input enable           Sleep output enable           PAD hold   Pad force hold              Mask of drive capability  Offset                    gpio number */
    {RTC_IO_TOUCH_PAD0_REG,  RTC_IO_TOUCH_PAD0_MUX_SEL_M,  RTC_IO_TOUCH_PAD0_FUN_SEL_S,  RTC_IO_TOUCH_PAD0_FUN_IE_M,  RTC_IO_TOUCH_PAD0_RUE_M,  RTC_IO_TOUCH_PAD0_RDE_M,  RTC_IO_TOUCH_PAD0_SLP_SEL_M,   RTC_IO_TOUCH_PAD0_SLP_IE_M,  RTC_IO_TOUCH_PAD0_SLP_OE_M,   0,         RTC_CNTL_TOUCH_PAD0_HOLD_M,  RTC_IO_TOUCH_PAD0_DRV_V,  RTC_IO_TOUCH_PAD0_DRV_S,  RTCIO_CHANNEL_0_GPIO_NUM}, //0
    {RTC_IO_TOUCH_PAD1_REG,  RTC_IO_TOUCH_PAD1_MUX_SEL_M,  RTC_IO_TOUCH_PAD1_FUN_SEL_S,  RTC_IO_TOUCH_PAD1_FUN_IE_M,  RTC_IO_TOUCH_PAD1_RUE_M,  RTC_IO_TOUCH_PAD1_RDE_M,  RTC_IO_TOUCH_PAD1_SLP_SEL_M,   RTC_IO_TOUCH_PAD1_SLP_IE_M,  RTC_IO_TOUCH_PAD1_SLP_OE_M,   0,         RTC_CNTL_TOUCH_PAD1_HOLD_M,  RTC_IO_TOUCH_PAD1_DRV_V,  RTC_IO_TOUCH_PAD1_DRV_S,  RTCIO_CHANNEL_1_GPIO_NUM}, //1
    {RTC_IO_TOUCH_PAD2_REG,  RTC_IO_TOUCH_PAD2_MUX_SEL_M,  RTC_IO_TOUCH_PAD2_FUN_SEL_S,  RTC_IO_TOUCH_PAD2_FUN_IE_M,  RTC_IO_TOUCH_PAD2_RUE_M,  RTC_IO_TOUCH_PAD2_RDE_M,  RTC_IO_TOUCH_PAD2_SLP_SEL_M,   RTC_IO_TOUCH_PAD2_SLP_IE_M,  RTC_IO_TOUCH_PAD2_SLP_OE_M,   0,         RTC_CNTL_TOUCH_PAD2_HOLD_M,  RTC_IO_TOUCH_PAD2_DRV_V,  RTC_IO_TOUCH_PAD2_DRV_S,  RTCIO_CHANNEL_2_GPIO_NUM}, //2
    {RTC_IO_TOUCH_PAD3_REG,  RTC_IO_TOUCH_PAD3_MUX_SEL_M,  RTC_IO_TOUCH_PAD3_FUN_SEL_S,  RTC_IO_TOUCH_PAD3_FUN_IE_M,  RTC_IO_TOUCH_PAD3_RUE_M,  RTC_IO_TOUCH_PAD3_RDE_M,  RTC_IO_TOUCH_PAD3_SLP_SEL_M,   RTC_IO_TOUCH_PAD3_SLP_IE_M,  RTC_IO_TOUCH_PAD3_SLP_OE_M,   0,         RTC_CNTL_TOUCH_PAD3_HOLD_M,  RTC_IO_TOUCH_PAD3_DRV_V,  RTC_IO_TOUCH_PAD3_DRV_S,  RTCIO_CHANNEL_3_GPIO_NUM}, //3
    {RTC_IO_TOUCH_PAD4_REG,  RTC_IO_TOUCH_PAD4_MUX_SEL_M,  RTC_IO_TOUCH_PAD4_FUN_SEL_S,  RTC_IO_TOUCH_PAD4_FUN_IE_M,  RTC_IO_TOUCH_PAD4_RUE_M,  RTC_IO_TOUCH_PAD4_RDE_M,  RTC_IO_TOUCH_PAD4_SLP_SEL_M,   RTC_IO_TOUCH_PAD4_SLP_IE_M,  RTC_IO_TOUCH_PAD4_SLP_OE_M,   0,         RTC_CNTL_TOUCH_PAD4_HOLD_M,  RTC_IO_TOUCH_PAD4_DRV_V,  RTC_IO_TOUCH_PAD4_DRV_S,  RTCIO_CHANNEL_4_GPIO_NUM}, //4
    {RTC_IO_TOUCH_PAD5_REG,  RTC_IO_TOUCH_PAD5_MUX_SEL_M,  RTC_IO_TOUCH_PAD5_FUN_SEL_S,  RTC_IO_TOUCH_PAD5_FUN_IE_M,  RTC_IO_TOUCH_PAD5_RUE_M,  RTC_IO_TOUCH_PAD5_RDE_M,  RTC_IO_TOUCH_PAD5_SLP_SEL_M,   RTC_IO_TOUCH_PAD5_SLP_IE_M,  RTC_IO_TOUCH_PAD5_SLP_OE_M,   0,         RTC_CNTL_TOUCH_PAD5_HOLD_M,  RTC_IO_TOUCH_PAD5_DRV_V,  RTC_IO_TOUCH_PAD5_DRV_S,  RTCIO_CHANNEL_5_GPIO_NUM}, //5
    {RTC_IO_TOUCH_PAD6_REG,  RTC_IO_TOUCH_PAD6_MUX_SEL_M,  RTC_IO_TOUCH_PAD6_FUN_SEL_S,  RTC_IO_TOUCH_PAD6_FUN_IE_M,  RTC_IO_TOUCH_PAD6_RUE_M,  RTC_IO_TOUCH_PAD6_RDE_M,  RTC_IO_TOUCH_PAD6_SLP_SEL_M,   RTC_IO_TOUCH_PAD6_SLP_IE_M,  RTC_IO_TOUCH_PAD6_SLP_OE_M,   0,         RTC_CNTL_TOUCH_PAD6_HOLD_M,  RTC_IO_TOUCH_PAD6_DRV_V,  RTC_IO_TOUCH_PAD6_DRV_S,  RTCIO_CHANNEL_6_GPIO_NUM}, //6
    {RTC_IO_TOUCH_PAD7_REG,  RTC_IO_TOUCH_PAD7_MUX_SEL_M,  RTC_IO_TOUCH_PAD7_FUN_SEL_S,  RTC_IO_TOUCH_PAD7_FUN_IE_M,  RTC_IO_TOUCH_PAD7_RUE_M,  RTC_IO_TOUCH_PAD7_RDE_M,  RTC_IO_TOUCH_PAD7_SLP_SEL_M,   RTC_IO_TOUCH_PAD7_SLP_IE_M,  RTC_IO_TOUCH_PAD7_SLP_OE_M,   0,         RTC_CNTL_TOUCH_PAD7_HOLD_M,  RTC_IO_TOUCH_PAD7_DRV_V,  RTC_IO_TOUCH_PAD7_DRV_S,  RTCIO_CHANNEL_7_GPIO_NUM}, //7
    {RTC_IO_TOUCH_PAD8_REG,  RTC_IO_TOUCH_PAD8_MUX_SEL_M,  RTC_IO_TOUCH_PAD8_FUN_SEL_S,  RTC_IO_TOUCH_PAD8_FUN_IE_M,  RTC_IO_TOUCH_PAD8_RUE_M,  RTC_IO_TOUCH_PAD8_RDE_M,  RTC_IO_TOUCH_PAD8_SLP_SEL_M,   RTC_IO_TOUCH_PAD8_SLP_IE_M,  RTC_IO_TOUCH_PAD8_SLP_OE_M,   0,         RTC_CNTL_TOUCH_PAD8_HOLD_M,  RTC_IO_TOUCH_PAD8_DRV_V,  RTC_IO_TOUCH_PAD8_DRV_S,  RTCIO_CHANNEL_8_GPIO_NUM}, //8
    {RTC_IO_TOUCH_PAD9_REG,  RTC_IO_TOUCH_PAD9_MUX_SEL_M,  RTC_IO_TOUCH_PAD9_FUN_SEL_S,  RTC_IO_TOUCH_PAD9_FUN_IE_M,  RTC_IO_TOUCH_PAD9_RUE_M,  RTC_IO_TOUCH_PAD9_RDE_M,  RTC_IO_TOUCH_PAD9_SLP_SEL_M,   RTC_IO_TOUCH_PAD9_SLP_IE_M,  RTC_IO_TOUCH_PAD9_SLP_OE_M,   0,         RTC_CNTL_TOUCH_PAD9_HOLD_M,  RTC_IO_TOUCH_PAD9_DRV_V,  RTC_IO_TOUCH_PAD9_DRV_S,  RTCIO_CHANNEL_9_GPIO_NUM}, //9
    {RTC_IO_TOUCH_PAD10_REG, RTC_IO_TOUCH_PAD10_MUX_SEL_M, RTC_IO_TOUCH_PAD10_FUN_SEL_S, RTC_IO_TOUCH_PAD10_FUN_IE_M, RTC_IO_TOUCH_PAD10_RUE_M, RTC_IO_TOUCH_PAD10_RDE_M, RTC_IO_TOUCH_PAD10_SLP_SEL_M,  RTC_IO_TOUCH_PAD10_SLP_IE_M, RTC_IO_TOUCH_PAD10_SLP_OE_M,  0,         RTC_CNTL_TOUCH_PAD10_HOLD_M, RTC_IO_TOUCH_PAD10_DRV_V, RTC_IO_TOUCH_PAD10_DRV_S, RTCIO_CHANNEL_10_GPIO_NUM}, //10
    {RTC_IO_TOUCH_PAD11_REG, RTC_IO_TOUCH_PAD11_MUX_SEL_M, RTC_IO_TOUCH_PAD11_FUN_SEL_S, RTC_IO_TOUCH_PAD11_FUN_IE_M, RTC_IO_TOUCH_PAD11_RUE_M, RTC_IO_TOUCH_PAD11_RDE_M, RTC_IO_TOUCH_PAD11_SLP_SEL_M,  RTC_IO_TOUCH_PAD11_SLP_IE_M, RTC_IO_TOUCH_PAD11_SLP_OE_M,  0,         RTC_CNTL_TOUCH_PAD11_HOLD_M, RTC_IO_TOUCH_PAD11_DRV_V, RTC_IO_TOUCH_PAD11_DRV_S, RTCIO_CHANNEL_11_GPIO_NUM}, //11
    {RTC_IO_TOUCH_PAD12_REG, RTC_IO_TOUCH_PAD12_MUX_SEL_M, RTC_IO_TOUCH_PAD12_FUN_SEL_S, RTC_IO_TOUCH_PAD12_FUN_IE_M, RTC_IO_TOUCH_PAD12_RUE_M, RTC_IO_TOUCH_PAD12_RDE_M, RTC_IO_TOUCH_PAD12_SLP_SEL_M,  RTC_IO_TOUCH_PAD12_SLP_IE_M, RTC_IO_TOUCH_PAD12_SLP_OE_M,  0,         RTC_CNTL_TOUCH_PAD12_HOLD_M, RTC_IO_TOUCH_PAD12_DRV_V, RTC_IO_TOUCH_PAD12_DRV_S, RTCIO_CHANNEL_12_GPIO_NUM}, //12
    {RTC_IO_TOUCH_PAD13_REG, RTC_IO_TOUCH_PAD13_MUX_SEL_M, RTC_IO_TOUCH_PAD13_FUN_SEL_S, RTC_IO_TOUCH_PAD13_FUN_IE_M, RTC_IO_TOUCH_PAD13_RUE_M, RTC_IO_TOUCH_PAD13_RDE_M, RTC_IO_TOUCH_PAD13_SLP_SEL_M,  RTC_IO_TOUCH_PAD13_SLP_IE_M, RTC_IO_TOUCH_PAD13_SLP_OE_M,  0,         RTC_CNTL_TOUCH_PAD13_HOLD_M, RTC_IO_TOUCH_PAD13_DRV_V, RTC_IO_TOUCH_PAD13_DRV_S, RTCIO_CHANNEL_13_GPIO_NUM}, //13
    {RTC_IO_TOUCH_PAD14_REG, RTC_IO_TOUCH_PAD14_MUX_SEL_M, RTC_IO_TOUCH_PAD14_FUN_SEL_S, RTC_IO_TOUCH_PAD14_FUN_IE_M, RTC_IO_TOUCH_PAD14_RUE_M, RTC_IO_TOUCH_PAD14_RDE_M, RTC_IO_TOUCH_PAD14_SLP_SEL_M,  RTC_IO_TOUCH_PAD14_SLP_IE_M, RTC_IO_TOUCH_PAD14_SLP_OE_M,  0,         RTC_CNTL_TOUCH_PAD14_HOLD_M, RTC_IO_TOUCH_PAD14_DRV_V, RTC_IO_TOUCH_PAD14_DRV_S, RTCIO_CHANNEL_14_GPIO_NUM}, //14
    {RTC_IO_XTAL_32P_PAD_REG, RTC_IO_X32P_MUX_SEL_M,        RTC_IO_X32P_FUN_SEL_S,        RTC_IO_X32P_FUN_IE_M,        RTC_IO_X32P_RUE_M,        RTC_IO_X32P_RDE_M,        RTC_IO_X32P_SLP_SEL_M,         RTC_IO_X32P_SLP_IE_M,        RTC_IO_X32P_SLP_OE_M,         0,         RTC_CNTL_X32P_HOLD_M,        RTC_IO_X32P_DRV_V,        RTC_IO_X32P_DRV_S,        RTCIO_CHANNEL_15_GPIO_NUM}, //15
    {RTC_IO_XTAL_32N_PAD_REG, RTC_IO_X32N_MUX_SEL_M,        RTC_IO_X32N_FUN_SEL_S,        RTC_IO_X32N_FUN_IE_M,        RTC_IO_X32N_RUE_M,        RTC_IO_X32N_RDE_M,        RTC_IO_X32N_SLP_SEL_M,         RTC_IO_X32N_SLP_IE_M,        RTC_IO_X32N_SLP_OE_M,         0,         RTC_CNTL_X32N_HOLD_M,        RTC_IO_X32N_DRV_V,        RTC_IO_X32N_DRV_S,        RTCIO_CHANNEL_16_GPIO_NUM}, //16
    {RTC_IO_PAD_DAC1_REG,    RTC_IO_PDAC1_MUX_SEL_M,       RTC_IO_PDAC1_FUN_SEL_S,       RTC_IO_PDAC1_FUN_IE_M,       RTC_IO_PDAC1_RUE_M,       RTC_IO_PDAC1_RDE_M,       RTC_IO_PDAC1_SLP_SEL_M,        RTC_IO_PDAC1_SLP_IE_M,       RTC_IO_PDAC1_SLP_OE_M,        0,         RTC_CNTL_PDAC1_HOLD_M,       RTC_IO_PDAC1_DRV_V,       RTC_IO_PDAC1_DRV_S,       RTCIO_CHANNEL_17_GPIO_NUM}, //17
    {RTC_IO_PAD_DAC2_REG,    RTC_IO_PDAC2_MUX_SEL_M,       RTC_IO_PDAC2_FUN_SEL_S,       RTC_IO_PDAC2_FUN_IE_M,       RTC_IO_PDAC2_RUE_M,       RTC_IO_PDAC2_RDE_M,       RTC_IO_PDAC2_SLP_SEL_M,        RTC_IO_PDAC2_SLP_IE_M,       RTC_IO_PDAC2_SLP_OE_M,        0,         RTC_CNTL_PDAC2_HOLD_M,       RTC_IO_PDAC2_DRV_V,       RTC_IO_PDAC2_DRV_S,       RTCIO_CHANNEL_18_GPIO_NUM}, //18
    {RTC_IO_RTC_PAD19_REG,   RTC_IO_PAD19_MUX_SEL_M,       RTC_IO_PAD19_FUN_SEL_S,       RTC_IO_PAD19_FUN_IE_M,       RTC_IO_PAD19_RUE_M,       RTC_IO_PAD19_RDE_M,       RTC_IO_PAD19_SLP_SEL_M,        RTC_IO_PAD19_SLP_IE_M,       RTC_IO_PAD19_SLP_OE_M,        0,         RTC_CNTL_PAD19_HOLD_M,       RTC_IO_PAD19_DRV_V,       RTC_IO_PAD19_DRV_S,       RTCIO_CHANNEL_19_GPIO_NUM}, //19
    {RTC_IO_RTC_PAD20_REG,   RTC_IO_PAD20_MUX_SEL_M,       RTC_IO_PAD20_FUN_SEL_S,       RTC_IO_PAD20_FUN_IE_M,       RTC_IO_PAD20_RUE_M,       RTC_IO_PAD20_RDE_M,       RTC_IO_PAD20_SLP_SEL_M,        RTC_IO_PAD20_SLP_IE_M,       RTC_IO_PAD20_SLP_OE_M,        0,         RTC_CNTL_PAD20_HOLD_M,       RTC_IO_PAD20_DRV_V,       RTC_IO_PAD20_DRV_S,       RTCIO_CHANNEL_20_GPIO_NUM}, //20
    {RTC_IO_RTC_PAD21_REG,   RTC_IO_PAD21_MUX_SEL_M,       RTC_IO_PAD21_FUN_SEL_S,       RTC_IO_PAD21_FUN_IE_M,       RTC_IO_PAD21_RUE_M,       RTC_IO_PAD21_RDE_M,       RTC_IO_PAD21_SLP_SEL_M,        RTC_IO_PAD21_SLP_IE_M,       RTC_IO_PAD21_SLP_OE_M,        0,         RTC_CNTL_PAD21_HOLD_M,       RTC_IO_PAD21_DRV_V,       RTC_IO_PAD21_DRV_S,       RTCIO_CHANNEL_21_GPIO_NUM}, //21
};

#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

// MCU + OS
#define CFG_TUSB_MCU              OPT_MCU_RP2040
//#define CFG_TUSB_OS               OPT_OS_FREERTOS
#define CFG_TUSB_DEBUG            0

// USB mode: device only
#define CFG_TUSB_RHPORT0_MODE     OPT_MODE_DEVICE
#define CFG_TUD_ENDPOINT0_SIZE    64

// Class drivers
#define CFG_TUD_HID               1
#define CFG_TUD_CDC               0
#define CFG_TUD_MSC               0
#define CFG_TUD_MIDI              0
#define CFG_TUD_VENDOR            0

// HID class driver config
#define CFG_TUD_HID_EP_BUFSIZE    64
#define CFG_TUD_HID_REPORT_BUFSIZE 64

#endif // _TUSB_CONFIG_H_

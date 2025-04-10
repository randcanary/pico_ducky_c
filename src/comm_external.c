// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// Pico SDk includes
#include "pico/stdlib.h"
#include "bsp/board.h"

// General C includes
#include "stdio.h"

// TinyUSB includes
#include "tusb.h"

// Project includes
#include "comm_external.h"
#include "task_internal.h"
#include "usb_descriptors.h"

// Report size defined by tinyUSB
#define KEY_REPORT_SIZE 6

void comm_external_init(void)
{
    board_init();
    tusb_init();
}

void send_key(uint8_t key, uint8_t modifier)
{
    uint8_t key_report[KEY_REPORT_SIZE] = {0};
    key_report[0] = key;
    tud_hid_keyboard_report(0, modifier, key_report);
    vTaskDelay(pdMS_TO_TICKS(10));  // key press time
    tud_hid_keyboard_report(0, 0, 0);
    vTaskDelay(pdMS_TO_TICKS(5));
}

void send_char_as_key(char c)
{
    uint8_t keycode = 0;
    uint8_t modifier = 0;

    if (c >= 'a' && c <= 'z') {
        keycode = HID_KEY_A + (c - 'a');
    }
    else if (c >= 'A' && c <= 'Z') {
        keycode = HID_KEY_A + (c - 'A');
        modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
    }
    else {
        // Handle basic punctuation/symbols
        switch (c) {
            case '0': keycode = HID_KEY_0; break;
            case '1': keycode = HID_KEY_1; break;
            case '2': keycode = HID_KEY_2; break;
            case '3': keycode = HID_KEY_3; break;
            case '4': keycode = HID_KEY_4; break;
            case '5': keycode = HID_KEY_5; break;
            case '6': keycode = HID_KEY_6; break;
            case '7': keycode = HID_KEY_7; break;
            case '8': keycode = HID_KEY_8; break;
            case '9': keycode = HID_KEY_9; break;


            case ' ': keycode = HID_KEY_SPACE; break;
            case '\n': keycode = HID_KEY_ENTER; break;

            case '.': keycode = HID_KEY_PERIOD; break;
            case ',': keycode = HID_KEY_COMMA; break;
            case '/': keycode = HID_KEY_SLASH; break;
            case '?': keycode = HID_KEY_SLASH; modifier = KEYBOARD_MODIFIER_LEFTSHIFT; break;

            case ';': keycode = HID_KEY_SEMICOLON; break;
            case ':': keycode = HID_KEY_SEMICOLON; modifier = KEYBOARD_MODIFIER_LEFTSHIFT; break;

            case '\'': keycode = HID_KEY_APOSTROPHE; break;
            case '\"': keycode = HID_KEY_APOSTROPHE; modifier = KEYBOARD_MODIFIER_LEFTSHIFT; break;

            case '[': keycode = HID_KEY_BRACKET_LEFT; break;
            case '{': keycode = HID_KEY_BRACKET_LEFT; modifier = KEYBOARD_MODIFIER_LEFTSHIFT; break;

            case ']': keycode = HID_KEY_BRACKET_RIGHT; break;
            case '}': keycode = HID_KEY_BRACKET_RIGHT; modifier = KEYBOARD_MODIFIER_LEFTSHIFT; break;

            case '\\': keycode = HID_KEY_BACKSLASH; break;
            case '|': keycode = HID_KEY_BACKSLASH; modifier = KEYBOARD_MODIFIER_LEFTSHIFT; break;

            case '-': keycode = HID_KEY_MINUS; break;
            case '_': keycode = HID_KEY_MINUS; modifier = KEYBOARD_MODIFIER_LEFTSHIFT; break;

            case '=': keycode = HID_KEY_EQUAL; break;
            case '+': keycode = HID_KEY_EQUAL; modifier = KEYBOARD_MODIFIER_LEFTSHIFT; break;

            case '`': keycode = HID_KEY_GRAVE; break;
            case '~': keycode = HID_KEY_GRAVE; modifier = KEYBOARD_MODIFIER_LEFTSHIFT; break;

            case '!': keycode = HID_KEY_1; modifier = KEYBOARD_MODIFIER_LEFTSHIFT; break;
            case '@': keycode = HID_KEY_2; modifier = KEYBOARD_MODIFIER_LEFTSHIFT; break;
            case '#': keycode = HID_KEY_3; modifier = KEYBOARD_MODIFIER_LEFTSHIFT; break;
            case '$': keycode = HID_KEY_4; modifier = KEYBOARD_MODIFIER_LEFTSHIFT; break;
            case '%': keycode = HID_KEY_5; modifier = KEYBOARD_MODIFIER_LEFTSHIFT; break;
            case '^': keycode = HID_KEY_6; modifier = KEYBOARD_MODIFIER_LEFTSHIFT; break;
            case '&': keycode = HID_KEY_7; modifier = KEYBOARD_MODIFIER_LEFTSHIFT; break;
            case '*': keycode = HID_KEY_8; modifier = KEYBOARD_MODIFIER_LEFTSHIFT; break;
            case '(': keycode = HID_KEY_9; modifier = KEYBOARD_MODIFIER_LEFTSHIFT; break;
            case ')': keycode = HID_KEY_0; modifier = KEYBOARD_MODIFIER_LEFTSHIFT; break;

            default:
                return; // unknown char, skip
        }
    }

    send_key(keycode, modifier);
}

void comm_external_task(void *pvParameters)
{
    comm_external_init();

    while(1)
    {
        // No task delay needed, tud_task should already do the work for us.
        tud_task();
    }
}
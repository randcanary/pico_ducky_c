#ifndef SCRIPT_YOUTUBE_H_
#define SCRIPT_YOUTUBE_H_

const char* rick_roll_payload[] = {
    "DELAY 1000", // wait a second for the usb protocol to finish startup
    "LGUI", // Left gui
    "DELAY 100", // wait for gui to open
    "STRING terminal", // search for terminal
    "DELAY 100", // wait for options to appear
    "ENTER", // open terminal
    "DELAY 100", // wait for options to appear
    "STRING brave-browser https://www.youtube.com/watch?v=dQw4w9WgXcQ", // rick roll
    "ENTER", // execute
    NULL  // End of script
};

#endif // SCRIPT_YOUTUBE_H_


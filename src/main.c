#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "FreeRTOS.h"
#include "task_internal.h"
#include "comm_external.h"
#include "task.h"

#include "runner.h"

int main() {
    stdio_init_all();

    xTaskCreate(runner_task,
        "comm_external",
        TASK_DEFS);

    xTaskCreate(comm_external_task,
        "comm_external",
        TASK_DEFS);

    vTaskStartScheduler();

    while (1); // Should never reach here
    return 0;
}

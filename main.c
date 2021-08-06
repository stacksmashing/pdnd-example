#include <stdio.h>
#include <string.h>

#include "tusb.h"
#include "pdnd/pdnd.h"
#include "pdnd/pdnd_display.h"

#include "hello.h"

void display_inputs() {
    cls(false);
    pprintf("Hello World\nInputs:");
    char inputs[32] = "";

    // Iterate all inputs and display them.
    for(int i=7; i >= 0; i--) {
        if(pdnd_in(i)) {
            strcat(inputs, "1 ");
        } else {
            strcat(inputs, "0 ");
        }
    }
    pprintfxy(0, 40, inputs);
}

int main() {
    // Initialize USB-UART as STDIO
    stdio_init_all();

    // Initialize pico-debug-n-dump lib
    pdnd_initialize();

    // Initialize display
    pdnd_display_initialize();
    
    // At this point in time, the buffers are off:
    // Both outputs and inputs are in high-impedance mode.

    // Display an image on the screen
    // hello comes from hello.h and was created using make_screen
    // (part of pdnd-lib)
    pdnd_display_screen(pdnd_global_display, &hello);
    sleep_ms(3000);

    // Next, we enable the buffers.
    pdnd_enable_buffers(1);


    while(1) {
        display_inputs();
        sleep_ms(1000);
    }
    
    return 0;
}

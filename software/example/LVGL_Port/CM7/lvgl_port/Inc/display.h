#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include <stdint.h>

#define DISPLAY_ALREADY_INIT                -300
#define DISPLAY_INIT_ERROR                  -301
#define DISPLAY_TRANSFER_BUFFER_ERROR       -302

int32_t displayInit(void);

#endif // INC_DISPLAY_H_

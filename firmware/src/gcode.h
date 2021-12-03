#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define GCODE_PARSE_SUCCESS (0)
#define GCODE_PARSE_ERROR (1)
#define GCODE_PARSE_UNKNOWN (2)

typedef enum {
    G01, // Linear motion
    G28, // Go home/calibrate 0
    // G400, // Enable jog mode
    // G401, // Disable jog mode
    M400, // Actuate solenoid (begin suction)
    M401, // De-actuate solenoid (end suction)
} gcode_command_type_e;

typedef struct {
    gcode_command_type_e type;

    union {
        struct G01_args_s {
            int32_t x;
            int32_t y;
            int32_t z;
        } g01;
        struct G28_args_s {
            bool x;
            bool y;
            bool z;
        } g28;
        struct G400_args_s {
            // Empty
        } g400;
        struct G401_args_s {
            // Empty
        } g401;
        struct M400_args_s {
            // Empty
        } m400;
        struct M401_args_s {
            // Empty
        } m401;
    };
} gcode_command_s;

int gcode_parse(char* raw, size_t len, gcode_command_s* cmd);

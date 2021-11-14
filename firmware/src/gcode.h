#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define GCODE_PARSE_SUCCESS (0)
#define GCODE_PARSE_ERROR (1)
#define GCODE_PARSE_UNKNOWN (2)

typedef enum {
    G01,
    M400,
    M401,
} gcode_command_type_e;

typedef struct {
    gcode_command_type_e type;

    union {
        struct G01_args_s {
            int32_t x;
            int32_t y;
            int32_t z;
        } g01;
        struct M400_args_s {
            bool on;
        } m400;
        struct M401_args_s {
            bool on;
        } m401;
    };
} gcode_command_s;

int gcode_parse(char* raw, size_t len, gcode_command_s* cmd);

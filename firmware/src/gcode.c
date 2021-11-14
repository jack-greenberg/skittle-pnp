#include "gcode.h"

static void parse_Gxx(char* raw, size_t len, gcode_command_s* cmd) {
    raw++;  // Skip letter
}

static void parse_Mxx(char* raw, size_t len, gcode_command_s* cmd) {
    raw++;  // Skip letter
}

int gcode_parse(char* raw, size_t len, gcode_command_s* cmd) {
    char type = raw[0];

    switch (type) {
        case 'G': {
            parse_Gxx(raw, len, cmd);
        } break;
        case 'M': {
            parse_Mxx(raw, len, cmd);
        } break;
        default: {
            return GCODE_PARSE_UNKNOWN;
        } break;
    }

    return GCODE_PARSE_SUCCESS;
}

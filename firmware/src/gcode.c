#include "gcode.h"
#include <string.h>

static int parse_Gxx(char* raw, size_t len, gcode_command_s* cmd) {
    raw++;  // Skip letter

    int subcmd = atoi(raw);

    switch (subcmd) {
        case 1: {
            cmd->type = G01;
        } break;
        default: {
            return GCODE_PARSE_UNKNOWN;
        }
    }

    while ((raw = strchr(raw, ' ')) != NULL) {
        raw++; // Skip the space

        switch (*raw) {
            case 'X': {
                cmd->g01.x = atoi(raw + 1);
            } break;
            case 'Y': {
                cmd->g01.y = atoi(raw + 1);
            } break;
            case 'Z': {
                cmd->g01.z = atoi(raw + 1);
            } break;
//             case 'F': {
// 
//             } break;
            default: {
                return GCODE_PARSE_ERROR;
            } break;
        }
    }
    return GCODE_PARSE_SUCCESS;
}

static int parse_Mxx(char* raw, size_t len, gcode_command_s* cmd) {
    raw++;  // Skip letter

    int subcmd = atoi(raw);

    switch (subcmd) {
        case 400: {
            cmd->type = M400;
        } break;
        case 401: {
            cmd->type = M401;
        } break;
        default: {
            return GCODE_PARSE_UNKNOWN;
        }
    }
    return GCODE_PARSE_SUCCESS;
}

int gcode_parse(char* raw, size_t len, gcode_command_s* cmd) {
    char type = raw[0];

    switch (type) {
        case 'G': {
            return parse_Gxx(raw, len, cmd);
        } break;
        case 'M': {
            return parse_Mxx(raw, len, cmd);
        } break;
        default: {
            return GCODE_PARSE_UNKNOWN;
        } break;
    }

    // unreachable!
    return GCODE_PARSE_SUCCESS;
}

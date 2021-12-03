#include "gcode.h"

#include <string.h>

static int parse_Gxx(char* raw, size_t len, gcode_command_s* cmd) {
    raw++;  // Skip letter

    int subcmd = atoi(raw);

    switch (subcmd) {
        case 1: {
            cmd->type = G01;

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
                    default: {
                        return GCODE_PARSE_ERROR;
                    } break;
                }
            }
        } break;
        case 28: {
            cmd->type = G28;

            while ((raw = strchr(raw, ' ')) != NULL) {
                raw++;

                switch (*raw) {
                    case 'X': {
                        cmd->g28.x = true;
                    }
                    case 'Y': {
                        cmd->g28.y = true;
                    }
                    case 'Z': {
                        cmd->g28.z = true;
                    }
                    default: {
                        return GCODE_PARSE_ERROR;
                    } break;
                }
            }
            if (!(cmd->g28.x || cmd->g28.y || cmd->g28.z)) {
                // None specified, so move all back to zero
                cmd->g28.x = true;
                cmd->g28.y = true;
                cmd->g28.z = true;
            }
        } break;
        default: {
            return GCODE_PARSE_UNKNOWN;
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

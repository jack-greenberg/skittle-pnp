#pragma once
#include <stdint.h>
#include <stdlib.h>

//char* response_ok = "ok\n";

/*
 * G01 -> move()
 * M400 -> vacuum_on()
 * M401 -> vacuum_off()
 */

typedef enum {
  G01,
  M400,
} type_e;

typedef struct {
  type_e type;
  union {
    struct G01_args {
      float x;
      float y;
      float z;
    } g01_args;
    struct M400_args {
      bool vacuum_on;
    } m400_args;
  };
} command_s;

/*
 * Parses command string to get the type
 * 
 * The string
 * 
 * Returns 0 if successful or 1 if not
 */
int parse_command(char* s, command_s* cmd);

/*
 * Creates a char* response, returns the size of the string
 */
//int create_response(char* data, response_s* resp);

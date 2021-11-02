#pragma once
#include <stdint.h>

typedef struct {
  char type;
  uint16_t arg0;
  uint16_t arg1;
} command_s;

typedef struct {
  uint16_t ready;
  uint16_t xpos; // skittle coordinate
  uint16_t ypos; // skittle coordinate (0 for prototype 1)
  uint16_t zpos; // 0 or 1 (for prototype 1)
  uint16_t vacuum; // 0 or 1
} response_s;

/*
 * Parses command into an action
 */
int parse_command(char* data, int length, command_s* cmd);

/*
 * Creates a char* response, returns the size of the string
 */
int create_response(char* data, response_s* resp);

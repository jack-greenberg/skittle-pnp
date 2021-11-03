#include "command.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static int g_parser(char* s, command_s* cmd) {
  char* ptr = s;
  int subcmd = atoi(ptr);

  switch (subcmd) {
    case 1: {
      cmd->type = G01;
    } break;
  }

  while ((ptr = strchr(ptr, ' ')) != NULL) {
    ptr++; // move past the space
    switch (*ptr) {
      case 'X': {
        cmd->g01_args.x = atof(ptr + 1);
      } break;
      case 'Y': {
        cmd->g01_args.y = atof(ptr + 1);
      } break;
      case 'Z': {
        cmd->g01_args.z = atof(ptr + 1);
      } break;
      case 'F': {
        // unimplemented!();
      } break;
    }
  }

  return 0;
}

int parse_command(char* s, command_s* cmd) {
  int rc = 0;

  switch (*s) {
    case 'G': {
      rc = g_parser(s, cmd);
    } break;
    case 'M': {

    } break;
    default: {
      rc = 1;
    } break;
  }

  return rc;
}

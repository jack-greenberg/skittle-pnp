#include "command.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int parse_command(char* data, int length, command_s* cmd) {
  int rc = 0;
  char* cursor = data;

  switch (data[0]) {
    case 'm': {
      cmd->type = 'm';
      cursor++;

      char* s;
      s = strtok(cursor, ",");
      cmd->arg0 = atoi(s);

      s = strtok(NULL, ",");
      cmd->arg1 = atoi(s);
    } break;
    case 'z': {
      cmd->type = 'z';
      cursor++;

      cmd->arg0 = atoi(cursor);
    } break;
    case 'v': {
      cmd->type = 'v';
      cursor++;

      cmd->arg0 = atoi(cursor);
    } break;
    default: {
      rc = 1; // Invalid command
    } break;
  }

  return rc;
}

int create_response(char* data, response_s* resp) {
  return sprintf(data, "%i,%i,%i,%i,%i\r\n",
    resp->ready,
    resp->xpos,
    resp->ypos,
    resp->zpos,
    resp->vacuum
  );
}

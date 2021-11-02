#include "command.h"
#include "motor.h"
#include <Servo.h>

#define STEP_PIN (10)
#define DIR_PIN (9)
#define TRAVEL_FACTOR (10)

#define Z_UP (0)
#define Z_DOWN (1)
#define SERVO_UP (135)
#define SERVO_DOWN (45)

char data[64];
int msg_size = 0;

Servo z_ax;

static void cmd_move(uint16_t x, uint16_t y) {
  for (int i = 0; i < x; i++) {
    digitalWrite(STEP_PIN,HIGH);
    delayMicroseconds(500);
    digitalWrite(STEP_PIN,LOW);
    delayMicroseconds(500);
  }
}
static void cmd_z(uint16_t z) {
  if (z == Z_DOWN) {
    z_ax.write(SERVO_DOWN);
  } else {
    z_ax.write(SERVO_UP);
  }
}
static void cmd_v(uint16_t v) {
  if (v) {
    // turn on vacuum
  } else {
    // turn off vacuum
  }
}

void run(command_s* cmd) {
  switch (cmd->type) {
    case 'm': {
      cmd_move(cmd->arg0, cmd->arg1);
    } break;
    case 'z': {
      // Servo control for up/down
      cmd_z(cmd->arg0);
    } break;
    case 'v': {
      // Vacuum control
      cmd_v(cmd->arg0);
    } break;
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(STEP_PIN,OUTPUT); 
  pinMode(DIR_PIN,OUTPUT);

  z_ax.attach(11);
  z_ax.write(SERVO_UP);
}

void loop() {
  int cmd_ready = -1;

  if (Serial.available()) {
    char c = Serial.read();

    if (c == '\r') {
      data[msg_size] = '\0';
      cmd_ready = 0;
    } else if (c == '\n') {
    } else {
      if (msg_size == 63) {
        data[msg_size] = '\0';
        cmd_ready = 0;
      } else {
        data[msg_size] = c;
        msg_size++;
      }
    }
  }

  if (cmd_ready == 0) {
    command_s cmd;
    int valid = parse_command(data, msg_size, &cmd);

//    Serial.print("Got command: ");
//    Serial.print(cmd.type); Serial.print(",");
//    Serial.print(cmd.arg0); Serial.print(",");
//    Serial.println(cmd.arg1);

    run(&cmd);
    
    msg_size = 0;
  }

//  digitalWrite(dirPin,LOW);
//
//  for(int x = 0; x < 800; x++) {
//    digitalWrite(stepPin,HIGH);
//    delayMicroseconds(500);
//    digitalWrite(stepPin,LOW);
//    delayMicroseconds(500);
//  }
}

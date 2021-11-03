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

static void cmd_move(float x, float y, float z) {
  if (x > 0) {
    digitalWrite(DIR_PIN, HIGH);
  } else {
    digitalWrite(DIR_PIN, LOW);
  }

  for (int i = 0; i < abs(x); i++) {
    digitalWrite(STEP_PIN,HIGH);
    delayMicroseconds(500);
    digitalWrite(STEP_PIN,LOW);
    delayMicroseconds(500);
  }

  z_ax.write(-z);
}

void run(command_s* cmd) {
  switch (cmd->type) {
    case G01: {
      cmd_move(cmd->g01_args.x, cmd->g01_args.y, cmd->g01_args.z);
    } break;
    case M400: {
      // Vacuum control
//      cmd_v(0);
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

    if (c == '\n') {
      data[msg_size] = '\0';
      cmd_ready = 0;
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
    parse_command(data, &cmd);

    Serial.print("Got command: ");
    Serial.print(cmd.type); Serial.print(", ");
    Serial.print(cmd.g01_args.x); Serial.print(", ");
    Serial.print(cmd.g01_args.y); Serial.print(", ");
    Serial.println(cmd.g01_args.z);

    run(&cmd);

    Serial.print("ok\n");
    
    msg_size = 0;
  }
}

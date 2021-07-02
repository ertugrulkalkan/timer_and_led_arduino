#include <Arduino.h>

#define LED_PIN 5

// its not right to use variables like this

// read buffer and command buffer
String buffer;
String command;

// delay time and end millisecond timestamp
unsigned long delay_time = 0;
unsigned long end_time = 0;

void command_handler()
{
  // get type of command
  switch (command[0])
  {
  // led command
  case 'L':
    if (command[1] == '0')
    {
      digitalWrite(LED_PIN, LOW);
    }
    else if (command[1] == '1')
    {
      digitalWrite(LED_PIN, HIGH);
    }
    // send last state anyway
    Serial.print("L");
    Serial.println(digitalRead(LED_PIN));
    break;
  // timer command
  case 'T':
    // calculate the end time
    delay_time = command.substring(1).toInt();
    if (delay_time)
    {
      end_time = millis() + delay_time;
      Serial.println("TS");
    }
  // invalid commands
  default:
    break;
  }
  // clean the command buffer
  command = "\0";
}

void setup()
{
  // set baud rate
  Serial.begin(115200);

  // led pin
  pinMode(LED_PIN, OUTPUT);
  // initial state
  digitalWrite(LED_PIN, LOW);

  command[0] = '\0';
}

void loop()
{
  // timer done, write message
  if (delay_time && millis() >= end_time)
  {
    delay_time = 0;
    Serial.println("TE");
  }

  // read byte if available
  if (Serial.available())
  {
    char c;

    if ((c = Serial.read()) >= 0)
    {
      // read byte if not '\n'
      // else command is finished
      if (c != '\n')
        buffer += c;
      else
      {
        buffer += '\0';
        command = buffer;
        buffer = "\0";
      }
    }
  }

  // if there is a command handle it
  if (command.length() > 0)
    command_handler();
}
#include <Arduino.h>

#define LED_PIN 5
#define BUFFER_LENGTH 255

// its not right to use variables like this

// read buffer and command buffer
String buffer;
String command;

// counting flag and millisecond
bool counting = false;
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
    Serial.print("L");
    Serial.println(digitalRead(LED_PIN));
    break;
  // timer command
  case 'T':
    // calculate the end time
    end_time = millis() + command.substring(1).toInt();
    // flag
    counting = true;
    Serial.println("TS");
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
  if (counting && millis() >= end_time)
  {
    counting = false;
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
/***************************************************************************/
// File        [bluetooth.h]
// Author     [Erik Kuo]
// Synopsis   [Code for bluetooth communication]
// Functions  [ask_BT, send_msg, send_byte]
// Modify     [2020/03/27 Erik Kuo]
/***************************************************************************/
#define DEBUG;
/*if you have no idea how to start*/
/*check out what you have learned from week 2*/
#include<SoftwareSerial.h>
enum BT_CMD {
  NOTHING,
  // TODO: add your own command type here
  START,
  END,
  ADVANCE,
  U_TURN,
  TURN_RIGHT,
  TURN_LEFT,
  HALT
};

BT_CMD ask_BT()
{
    // Serial.println("Start asking BT!");
    BT_CMD message=NOTHING;
    char cmd;
    // Serial.println(BT.available());
    
    if(BT.available())
    {
      //Serial.println("BT available!");
      // TODO:
      // 1. get cmd from SoftwareSerial object: BT
      cmd = BT.read();
      // 2. link bluetooth message to your own command type
      switch(cmd)
      {
        case 's':
          message = START;
          break;
        case 'e':
          message = END;
          break;
        case '1':
          message = ADVANCE;
          break;
        case '2':
          message = U_TURN;
          break;
        case '3':
          message = TURN_RIGHT;
          break;
        case '4':
          message = TURN_LEFT;
          break;
        case '5':
          message = HALT;
          break;
        default:
          message = NOTHING;
      }
      #ifdef DEBUG
      Serial.print("cmd : ");
      Serial.println(cmd);
      //Serial.println("Sway is so Wet");
      #endif
    }
    return message;
}// ask_BT

// send msg back through SoftwareSerial object: BT
// can use send_byte alternatively to send msg back
// (but need to convert to byte type)
void send_msg(const char& msg)
{
     // TODO:
     BT.write(msg);
}// send_msg

// send UID back through SoftwareSerial object: BT
void send_byte(byte *id, byte& idSize) {
  for (byte i = 0; i < idSize; i++) {  // Send UID consequently.
    BT.write(id[i]);
  }
  #ifdef DEBUG
  Serial.print("Sent id: ");
  for (byte i = 0; i < idSize; i++) {  // Show UID consequently.
    Serial.print(id[i], HEX);
  }
  Serial.println();
  #endif
}// send_byte

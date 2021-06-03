#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

MFRC522::MIFARE_Key key;
const int groonnLed0 = 6; //Definerer dPins til forskjellige komponenter
const int roodLed0 = 7;
const int groonnLed1 = 2; //Definerer dPins til forskjellige komponenter
const int roodLed1 = 3;
const int groonnLed2 = 4; //Definerer dPins til forskjellige komponenter
const int roodLed2 = 5;
const int statusButton = 8;
int statusState = 0;
int buttonState;
boolean slot1Opptatt = false;
boolean slot2Opptatt = false;
boolean slot1OpptattPrev = false;
boolean slot2OpptattPrev = false;
String slot1Person = "";
String slot2Person = "";
boolean person1Status = false;
boolean person2Status = true;
String person = "";
int val1;                        // variable for reading the pin status
int val2;                       // variable for reading the delayed status
int Mode = 0;
int personInput1;
int personInput2;
int slot1 = 0;
int slot2;
int teller = 0;


void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card

  pinMode(roodLed0, OUTPUT); //Setter I/O
  pinMode(groonnLed0, OUTPUT);
  pinMode(roodLed1, OUTPUT); //Setter I/O
  pinMode(groonnLed1, OUTPUT);
  pinMode(roodLed2, OUTPUT); //Setter I/O
  pinMode(groonnLed2, OUTPUT);
  pinMode(statusButton, INPUT);
  pinMode(A0, INPUT_PULLUP);


  digitalWrite(roodLed0, LOW); //LEDer lyser under setup for aa sjekke at de fungerer
  digitalWrite(groonnLed0, HIGH);
  digitalWrite(roodLed1, LOW); //LEDer lyser under setup for aa sjekke at de fungerer
  digitalWrite(groonnLed1, LOW);
  digitalWrite(roodLed2, LOW); //LEDer lyser under setup for aa sjekke at de fungerer
  digitalWrite(groonnLed2, LOW);

  digitalWrite(roodLed1, HIGH);
  digitalWrite(groonnLed1, LOW);




  // Prepare the key (used both as key A and as key B)
  // using FFFFFFFFFFFFhex which is the default at chip delivery from the factory
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("Scan a MIFARE Classic PICC to demonstrate read and write."));
  Serial.print(F("Using key (for A and B):"));
  dump_byte_array(key.keyByte, MFRC522::MF_KEY_SIZE);
  Serial.println();

  Serial.println(F("BEWARE: Data will be written to the PICC, in sector #1"));
}

void loop() {


  val1 = digitalRead(statusButton);      // read input value and store it in val
  delay(10);                         // 10 milliseconds is a good amount of time
  val2 = digitalRead(statusButton);     // read the input again to check for bounces
  if (val1 == val2) {                 // make sure we got 2 consistant readings!
    if (val1 == HIGH) {                // check if the button is pressed
      if (Mode == 0) {
        Mode = 1;
      } else {
        if (Mode == 1) {
          Mode = 0;
        }
      }
    }               // save the new state in our variable
  }

  if (Mode == 0) { // all-off
    digitalWrite(roodLed0, LOW);
    digitalWrite(groonnLed0, HIGH);
  }

  if (Mode == 1) {
    digitalWrite(roodLed0, HIGH);
    digitalWrite(groonnLed0, LOW);
  }




  slot2 = analogRead(A5);
  Serial.println("Slot1");
  Serial.println(slot1);

  

  //Serial.println("Analog value 1: ");
  //Serial.println(slot1);
  Serial.println("Analog value 2: ");
  Serial.println(slot2);

  if (slot1 < 20) {
    slot1Opptatt = true;
  } else {
    slot1Opptatt = false;
    if (teller == 0) {
      delay(5000);
      digitalWrite(roodLed1, LOW);
      digitalWrite(groonnLed1, HIGH);
      teller = 1;
    }

  }

  if (slot2 < 20) {
    slot2Opptatt = true;
  } else {
    slot2Opptatt = false;
  }


  /*
    if (slot1Opptatt == false) { //Hvis slotten er ledig
      digitalWrite(roodLed1, LOW);
      digitalWrite(groonnLed1, LOW);
      //slot1Person = "";
      slot1OpptattPrev = false;
      //Serial.println("Slot1 Ledig");
    }
  */
  if (slot2Opptatt == false) {
    digitalWrite(roodLed2, LOW);
    digitalWrite(groonnLed2, LOW);
    //slot2Person = "";
    slot2OpptattPrev = false;
    //Serial.println("Slot2 Ledig");
  }

  /*
    if (slot1Opptatt == true) { //Hvis slotten nettopp ble tatt og før var åpen, kjør koden
    if (slot1OpptattPrev == false) {
      if (person.equals("Person1") || person.equals("Person2")) {
        slot1Person = person;
        person = "";
        slot1OpptattPrev = true;
        Serial.println("Ny person i slot1 " + slot1Person);
      }

    }
    }
  */

  if (slot2Opptatt == true) {
    if (slot2OpptattPrev == false) {
      if (person.equals("Person1") || person.equals("Person2")) {
        slot2Person = person;
        person = "";
        slot2OpptattPrev = true;
        Serial.println("Ny person i slot2 " + slot2Person);
      }

    }
  }
  /*
    if (slot1Opptatt == true) { //Hvis slotten er tatt
      if (slot1OpptattPrev == true) {
        if (slot1Person.equals("Person1")) {
          if (person1Status == true) {
            digitalWrite(roodLed1, LOW);
            digitalWrite(groonnLed1, HIGH);
          } else if (person1Status == false) {
            digitalWrite(roodLed1, HIGH);
            digitalWrite(groonnLed1, LOW);
          }
        } else if (slot1Person.equals("Person2")) {
          if (person2Status == true) {
            digitalWrite(roodLed1, LOW);
            digitalWrite(groonnLed1, HIGH);
          } else if (person2Status == false) {
            digitalWrite(roodLed1, HIGH);
            digitalWrite(groonnLed1, LOW);
          }
        }
      }
    }
  */
  if (slot2Opptatt == true) { //Hvis slotten er tatt
    if (slot2OpptattPrev == true) {
      if (slot2Person.equals("Person1")) {
        if (person1Status == true) {
          digitalWrite(roodLed2, LOW);
          digitalWrite(groonnLed2, HIGH);
        } else if (person1Status == false) {
          digitalWrite(roodLed2, HIGH);
          digitalWrite(groonnLed2, LOW);
        }
      } else if (slot2Person.equals("Person2")) {
        if (person2Status == true) {
          digitalWrite(roodLed2, LOW);
          digitalWrite(groonnLed2, HIGH);
        } else if (person2Status == false) {
          digitalWrite(roodLed2, HIGH);
          digitalWrite(groonnLed2, LOW);
        }
      }
    }
    slot1 = 100;
  }


  if (person != "") {
    Serial.println(person);
  }




  if ( mfrc522.PICC_IsNewCardPresent()) {
    if ( mfrc522.PICC_ReadCardSerial()) {
      // Show some details of the PICC (that is: the tag/card)
      Serial.print(F("Card UID:"));
      dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
      Serial.println();
      Serial.print(F("PICC type: "));
      MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
      Serial.println(mfrc522.PICC_GetTypeName(piccType));

      // Check for compatibility
      if (    piccType != MFRC522::PICC_TYPE_MIFARE_MINI
              &&  piccType != MFRC522::PICC_TYPE_MIFARE_1K
              &&  piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
        Serial.println(F("This sample only works with MIFARE Classic cards."));
        return;
      }


      byte dataBlock1[]    = {
        0x01, 0x01, 0x01, 0x01, //  1,  2,   3,  4,
        0x01, 0x01, 0x01, 0x01, //  5,  6,   7,  8,
        0x01, 0x01, 0x01, 0x01, //  9, 10, 255, 11,
        0x01, 0x01, 0x01, 0x01  // 12, 13, 14, 15
      };

      byte dataBlock2[]    = {
        0x02, 0x02, 0x02, 0x02, //  1,  2,   3,  4,
        0x02, 0x02, 0x02, 0x02, //  5,  6,   7,  8,
        0x02, 0x02, 0x02, 0x02, //  9, 10, 255, 11,
        0x02, 0x02, 0x02, 0x02  // 12, 13, 14, 15
      };


      // In this sample we use the second sector,
      // that is: sector #1, covering block #4 up to and including block #7
      byte sector         = 1;
      byte blockAddr      = 4;
      byte trailerBlock   = 7;
      MFRC522::StatusCode status;
      byte buffer[18];
      byte size = sizeof(buffer);

      // Authenticate using key A
      Serial.println(F("Authenticating using key A..."));
      status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
      if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }

      // Show the whole sector as it currently is
      Serial.println(F("Current data in sector:"));
      mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
      Serial.println();

      // Read data from the block
      Serial.print(F("Reading data from block ")); Serial.print(blockAddr);
      Serial.println(F(" ..."));
      status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockAddr, buffer, &size);
      if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Read() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
      }
      Serial.print(F("Data in block ")); Serial.print(blockAddr); Serial.println(F(":"));
      dump_byte_array(buffer, 16); Serial.println();
      Serial.println();

      // Authenticate using key B
      Serial.println(F("Authenticating again using key B..."));
      status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
      if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }

      // Check that data in block is what we have written
      // by counting the number of bytes that are equal
      Serial.println(F("Checking result..."));
      byte count1 = 0;
      byte count2 = 0;
      for (byte i = 0; i < 16; i++) {
        // Compare buffer (= what we've read) with dataBlock (= what we've written)
        if (buffer[i] == dataBlock1[i]) {
          count1++;
        } else if (buffer[i] == dataBlock2[i]) {
          count2++;
        }

      }
      if (count1 == 16) {
        Serial.println(F("Person1 oppdaget"));
        person = "";
        person = "Person1";
      } else if (count2 == 16) {
        Serial.println(F("Person2 oppdaget"));
        person = "";
        person = "Person2";
      } else {
        Serial.println(F("Ingen person oppdaget"));
      }
      Serial.println();

      // Dump the sector data
      Serial.println(F("Current data in sector:"));
      mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
      Serial.println();

      // Halt PICC
      mfrc522.PICC_HaltA();
      // Stop encryption on PCD
      mfrc522.PCD_StopCrypto1();
    }
  }
}



void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

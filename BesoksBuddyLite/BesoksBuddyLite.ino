
const int groonnLed0 = 7; //Definerer dPins til forskjellige komponenter
const int roodLed0 = 8;

const int outputStatus = 2;

const int statusButton = 13;
int statusState = 0;
int buttonState;

int val1;                        // variable for reading the pin status
int val2;                       // variable for reading the delayed status
int Mode = 0;

void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  pinMode(roodLed0, OUTPUT); //Setter I/O
  pinMode(groonnLed0, OUTPUT);
  pinMode(statusButton, INPUT);
  pinMode(outputStatus, OUTPUT);
  

  digitalWrite(roodLed0, LOW); //LEDer lyser under setup for aa sjekke at de fungerer
  digitalWrite(groonnLed0, HIGH);
}

void loop() {
  val1 = digitalRead(statusButton);      // read input value and store it in val
  delay(10);                         // 10 milliseconds is a good amount of time
  val2 = digitalRead(statusButton);
  // read the input again to check for bounces
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
    digitalWrite(outputStatus, HIGH);
  }

  if (Mode == 1) {
    digitalWrite(roodLed0, HIGH);
    digitalWrite(groonnLed0, LOW);
    digitalWrite(outputStatus, LOW);
  }
}

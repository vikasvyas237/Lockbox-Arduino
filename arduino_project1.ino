#include <Keypad.h> //Include Keypad library
#include <Servo.h>  //Include Servo library

Servo servoblue; //The servo is called "servoblue" from now on

char* password = "123"; //We set the password. In this case it is "123"
int position = 0;
const byte ROWS = 4; //In these two lines we define how many rows and columns
const byte COLS = 3; //our keypad has four rows and three columns
char keys[ROWS][COLS] = { //The characters on the keys are defined here

{'#', '0', '*'},
{'9', '8', '7'},
{'6', '5', '4'},
{'3', '2', '1'}
};

byte rowPins[ROWS] = {5, 6, 7, 8}; //The connection with the arduino is
byte colPins[COLS] = {2, 3, 4}; //listed here

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //create and object and map the keys

void setup() {
        servoblue.attach(11); //The servo is connected to pin 11
        setLocked(true);
}

void loop() {
      char key = keypad.getKey();
      if (key == '*' || key == '#')  {     //If the lock is open it can be locked again by pushing "*" or "#" on the keypad 
             position = 0;
             setLocked(true); //The command to close the lock after „*“ or „#“ is pushed
       }

      if (key == password[position]) {
        position ++;
      }

       if (position == 3) {     //This part defines how many digits our code will have.In this case we have 3 digits(123).
       setLocked(false);
      }

      delay(100);

    }

    void setLocked(int locked)  {
      if (locked) {   // If the lock is closed..
      servoblue.write(270); //and the servo should turn to a 90 degree position.
      }

      else {    //if the lock is open..
      servoblue.write(2); //..and the servo should turn to a 0 degree position.
 }

}



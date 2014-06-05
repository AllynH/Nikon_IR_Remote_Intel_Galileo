/*

  This program will generate an Infra-Red command for a Nikon camera which will take a picture.
  The Camera's shutter mode must be set to remote control:
    Nikon: Info button -> release mode -> Quick-response remote.
  
  Created by: Allyn Hunt http://www.allynh.com/blog/

  Acknowledgements - 
  This project was made possible using information from the following projects:
    http://www.bigmike.it/ircontrol/
    http://sebastian.setz.name/arduino/my-libraries/multi-camera-ir-control/
    http://www.sbprojects.com/projects/nikon/

  Connecting the IR-LED to the GPIO:
    Only the dedicated GPIO pins 2 or 3 can be used for this project.
      see http://allynh.com/blog/?p=33 for more information on GPIO speeds.

*/

// Creat an array for the pulse values:
int nikonCommand[16] = {76, 1058, 15, 61, 15, 137, 15, 1078, 76, 1058, 15, 61, 15, 137, 15, 1078};

// Setup the pin used for the IR LED:
int pinIR_LED = 2;

// Set a delay between pictures:
int delaySeconds = 5;

// Setup pin to fast mode:
void setup(){
    pinMode(pinIR_LED, OUTPUT_FAST);

  Serial.begin(9600);
  Serial.println("Setup..." );

}

void takePicNikon()
{
for(int x=0; x<sizeof(nikonCommand)/sizeof(int); x++)
  {
    int y = x + 1;
      pulseLoop(nikonCommand[x], (y%2));
  }

}

void loop()
{

  Serial.println("Taking picture: " );
  
  // This calls the main function:
  takePicNikon();
  
  // Delay for a given time before taking another picture:
  delay((delaySeconds * 1000));
}

// This function generates teh actual pulses used to make the command:
// Note: Putting any print statements in here will cause the pulses to become skewed and unstable.
void pulseLoop(int pulses, int SHINE)
{
  // Integers for loops:
  int i;
  int n;

  // delayValue is used to delay the clock from 460KHz to 38.4KHz:
  int delayValue = 12;

  register int x = 0;

  // Loop to control the number of pulses created
  // Number is multiplied by 2 to create both the low and high period of the pulse:
  for(n=0; n<(pulses*2); n++)
  {
    // Loop to delay the digitalWrite to 38.4KHz:
    for(i=0; i<delayValue; i++)
      {
        // SHINE only activates the IR LED when we are supposed to pulse, deactivates for the delay:
        digitalWrite(2, (x & SHINE));
      }
    x =!x;
 }
}

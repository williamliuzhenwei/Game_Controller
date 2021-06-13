/*
 * Global variables
 */
// Acceleration values recorded from the readAccelSensor() function
int ax = 0; int ay = 0; int az = 0;
int ppg = 0;        // PPG from readPhotoSensor() (in Photodetector tab)
int sampleTime = 0; // Time of last sample (in Sampling tab)
bool sending;
//Button
const int BUTTON_PIN =15; 
const int BUTTON_PIN1 = 14;
const int BUTTON_PIN2 = 16;
const int BUTTON_PIN3 = 17;
const int LED_PIN = 13;
int message;
//Motor
int buzz_state=0;
unsigned long buzz_time;
unsigned long curr_time;
//
int lives =4;
int x=0;
/*
 * Initialize the various components of the wearable
 */
void setup() {
  setupAccelSensor();
  setupCommunication();
  setupDisplay();
  setupMotor();
  setupPhotoSensor();
  sending = false;
  pinMode(BUTTON_PIN,INPUT);
  pinMode(BUTTON_PIN1,INPUT);
  pinMode(BUTTON_PIN2,INPUT);
  pinMode(LED_PIN,OUTPUT);
  writeDisplay("Ready...", 1, true);
  writeDisplay("Set...", 2, false);
  writeDisplay("Play!", 3, false);
}

/*
 * The main processing loop
 */
void loop() {
  // Parse command coming from Python (either "stop" or "start")
  String command = receiveMessage();
  if(command == "stop") {
    sending = false;
    writeDisplay("Controller: Off", 0, true);
  }
  else if(command == "start") {
    sending = true;
    writeDisplay("Controller: On", 0, true);
    lives =4;
    writeDisplay("LIVES: 4", 1, true);
    
  }
  //if the ship being attacked, then python send a "buzz" message, motor will buzz for 0.1 second
  else if(command == "buzz"){
    activateMotor(255);//motor buzzing
    buzz_time = millis();// count the time to contorl the motor
    lives --;
    digitalWrite(LED_PIN,HIGH);
    
   
    String L = "LIVES: " + String(lives);
    writeDisplay( L.c_str(), 1, false);
    if(lives<0){
      lives =0;
      
    }
    if(lives==0){
       writeDisplay("GAME OVER",2,true);
       
       x=1;
      
    }
  }
  else{
     writeDisplay(command.c_str(), 2, false);
     
  }

 if(x==1){
       writeDisplay("Controller: On", 0, true);
       writeDisplay("LIVES: 4", 1, true);
       lives = 4;
 }
 


  
  // make motor buzz for half second
  if(millis() - buzz_time >= 500){
      deactivateMotor();
      digitalWrite(LED_PIN,LOW);
    }
  if(digitalRead(BUTTON_PIN)==LOW){
    message = 2;
  }
  else if(digitalRead(BUTTON_PIN1)==LOW){
    message = 5;
  }
  else if(digitalRead(BUTTON_PIN2)==LOW){
    message = 6;
      
  }
  else if(digitalRead(BUTTON_PIN3)==LOW){
    message = 7;
      
  }
 
  else{
    message = getOrientation();
  }
  // Send the orientation of the board
  if(sending && sampleSensors()) {
    
    sendMessage(String(message));
  }
 
}

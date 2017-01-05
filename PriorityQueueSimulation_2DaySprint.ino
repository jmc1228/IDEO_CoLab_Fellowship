const int ledPin =  13;    
int ledState = LOW;


//all caps for global variables 
const int user1_machine = 2; 
const int user2_machine = 3; 

const int redPin_user1 = 4; 
const int yellowPin_user1 = 5; 
const int greenPin_user1 = 6; 

const int redPin_user2 = 7; 
const int yellowPin_user2 = 8; 
const int greenPin_user2 = 9; 


unsigned long user1_machine_stamp = NULL; 
unsigned long user2_machine_stamp = NULL;  

int jobtime = 5000; 


int redButtonState_user1 = 0;          
int yellowButtonState_user1 = 0;         
int greenButtonState_user1 = 0;          
int redButtonState_user2 = 0;          
int yellowButtonState_user2 = 0;          
int greenButtonState_user2 = 0;                     
 
unsigned long previousMillis = 0;         

       

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(user1_machine, OUTPUT); 
  pinMode(user2_machine, OUTPUT); 
  
  pinMode(redPin_user1, INPUT);
  pinMode(yellowPin_user1, INPUT);
  pinMode(greenPin_user1, INPUT);

  pinMode(redPin_user2, INPUT);
  pinMode(yellowPin_user2, INPUT);
  pinMode(greenPin_user2, INPUT);

  Serial.begin(9600); 
}

void loop() {
  redButtonState_user1 = digitalRead(redPin_user1);
  yellowButtonState_user1 = digitalRead(yellowPin_user1);
  greenButtonState_user1 = digitalRead(greenPin_user1);

  redButtonState_user2 = digitalRead(redPin_user2);
  yellowButtonState_user2 = digitalRead(yellowPin_user2);
  greenButtonState_user2 = digitalRead(greenPin_user2);

 
  
  assignJobs(); 
  runJobs(); 
}

void assignJobs(){  
  //green always runs motor immediately
 
  if(greenButtonState_user1 == HIGH){
    user1_machine_stamp = millis(); 
  }
  if(greenButtonState_user2 == HIGH){
    user2_machine_stamp = millis(); 
  }
  
  //red always runs motor immediately if no other motor is running 
  if(redButtonState_user1 == HIGH && user1_machine_stamp == NULL && user2_machine_stamp == NULL){
    user1_machine_stamp = millis(); 
  }

  if(redButtonState_user2 == HIGH && user1_machine_stamp == NULL && user2_machine_stamp == NULL){
    user2_machine_stamp = millis(); 
  }
  
  
  if(redButtonState_user1 == HIGH && (user2_machine_stamp != NULL)){
    user1_machine_stamp = user2_machine_stamp + jobtime + 1000; 
  }

  if(redButtonState_user2 == HIGH && (user1_machine_stamp != NULL)){
    user2_machine_stamp = user1_machine_stamp + jobtime + 1000; 
  }

  
}

//'user' object that encapsulates all user variables. function takes in the user as a parameter

//void runMachine(user#)
void runJobs(){
    unsigned long currentMillis = millis();
    //Serial.println(user2_machine_stamp); 
    if(user1_machine_stamp && (currentMillis > user1_machine_stamp) && (currentMillis < (user1_machine_stamp + jobtime))){ 
        digitalWrite(user1_machine, HIGH); 
    } 
    else{
      digitalWrite(user1_machine, LOW); 
      
      if(currentMillis > user1_machine_stamp){
        user1_machine_stamp = NULL; 
      }
    }
    
    if(user2_machine_stamp && (currentMillis > user2_machine_stamp) && (currentMillis < (user2_machine_stamp + jobtime))){
        digitalWrite(user2_machine, HIGH); 
    } 
    else{
      digitalWrite(user2_machine, LOW); 
      if(currentMillis > user2_machine_stamp){
        user2_machine_stamp = NULL; 
      }
    }
    // Serial.println(digitalRead(user2_machine));
}







 

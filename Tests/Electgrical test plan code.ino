//Electromagnet pins
int magnet_FL = 22;
int magnet_FR = 24;
int magnet_RL = 26;
int magnet_RR = 28;


void setup() {
  // put your setup code here, to run once:
  pinMode(magnet_FL, OUTPUT); //FL
  pinMode(magnet_FR, OUTPUT); //FR
  pinMode(magnet_RL, OUTPUT); //RL
  pinMode(magnet_RR, OUTPUT); //RR
  
  
  digitalWrite(magnet_FL, LOW); 
  digitalWrite(magnet_FR, LOW); 
  digitalWrite(magnet_RL, LOW); 
  digitalWrite(magnet_RR, LOW); 
  
  //#1 Simple electromagnet
  digitalWrite(magnet_FL, HIGH);
  delay(2000);
  digitalWrite(magnet_FL, LOW); 
  delay(2000);

  digitalWrite(magnet_FR, HIGH);
  delay(2000);
  digitalWrite(magnet_FR, LOW); 
  delay(2000);

  digitalWrite(magnet_RL, HIGH);
  delay(2000);
  digitalWrite(magnet_RL, LOW); 
  delay(2000);

  digitalWrite(magnet_RR, HIGH);
  delay(2000);
  digitalWrite(magnet_RR, LOW); 
  delay(2000);
  
  //#2 2 electromagnets
  digitalWrite(magnet_FL, HIGH);
  digitalWrite(magnet_FL, HIGH);
  delay(2000);
  digitalWrite(magnet_FR, LOW); 
  digitalWrite(magnet_FR, LOW); 
  delay(2000);

  digitalWrite(magnet_RL, HIGH);
  digitalWrite(magnet_RL, HIGH);
  delay(2000);
  digitalWrite(magnet_RR, LOW); 
  digitalWrite(magnet_RR, LOW); 
  delay(2000);

  //#3 All electromagnets
  digitalWrite(magnet_FL, HIGH); 
  digitalWrite(magnet_FR, HIGH); 
  digitalWrite(magnet_RL, HIGH); 
  digitalWrite(magnet_RR, HIGH); 
  delay(5000);
  digitalWrite(magnet_FL, LOW); 
  digitalWrite(magnet_FR, LOW); 
  digitalWrite(magnet_RL, LOW); 
  digitalWrite(magnet_RR, LOW); 

  //#4 Simple angular servos


  //#5 All angular servos


  //#6 All electromagnets and simple servos
    //#3 All electromagnets
  digitalWrite(magnet_FL, HIGH); 
  digitalWrite(magnet_FR, HIGH); 
  digitalWrite(magnet_RL, HIGH); 
  digitalWrite(magnet_RR, HIGH); 
  delay(5000);

  //REDO TEST #4
  
  digitalWrite(magnet_FL, LOW); 
  digitalWrite(magnet_FR, LOW); 
  digitalWrite(magnet_RL, LOW); 
  digitalWrite(magnet_RR, LOW); 

}

void loop() 
{

}

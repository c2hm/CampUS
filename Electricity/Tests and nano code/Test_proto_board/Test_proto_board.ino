void setup() {
  // put your setup code here, to run once:
  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(28, OUTPUT);
  
  
  digitalWrite(22, LOW); 
  digitalWrite(24, LOW); 
  digitalWrite(26, LOW); 
  digitalWrite(28, LOW); 
  
  //TEST UN AIMANT À LA FOIS
  digitalWrite(22, HIGH);
  delay(1000);
  digitalWrite(22, LOW); 
  delay(1000);
  
  digitalWrite(24, HIGH);
  delay(1000);
  digitalWrite(24, LOW); 
  delay(1000);
  
  digitalWrite(26, HIGH);
  delay(1000);
  digitalWrite(26, LOW); 
  delay(1000);
  
  digitalWrite(28, HIGH);
  delay(1000);
  digitalWrite(28, LOW); 
  delay(1000);
  
  //TEST 4 AIMANTS À LA FOIS
  digitalWrite(22, HIGH); 
  digitalWrite(24, HIGH); 
  digitalWrite(26, HIGH); 
  digitalWrite(28, HIGH); 
  delay(5000);
  
  digitalWrite(22, LOW); 
  digitalWrite(24, LOW); 
  digitalWrite(26, LOW); 
  digitalWrite(28, LOW); 

}

void loop() {


  //TEST 2 AIMANTS À LA FOIS, 
  //PUIS LES DEUX AUTRES EN BOUCLE
  digitalWrite(24, HIGH); 
  digitalWrite(26, HIGH); 
  delay(2000);

  digitalWrite(24, LOW); 
  digitalWrite(26, LOW);
  delay(2000);

  digitalWrite(22, HIGH); 
  digitalWrite(28, HIGH); 
  delay(2000);

  digitalWrite(22, LOW); 
  digitalWrite(28, LOW);
  delay(2000);


}


int in_1 = 3;
int in_2 = 4;
int in_3 = 5;
int in_4 = 6;

int out_1 = 9;
int out_2 = 10;
int out_3 = 11;
int out_4 = 12;

void setup() {
  // put your setup code here, to run once:

  pinMode(in_1, INPUT);
  pinMode(in_2, INPUT);
  pinMode(in_3, INPUT);
  pinMode(in_4, INPUT);

  pinMode(out_1, OUTPUT);
  pinMode(out_2, OUTPUT);
  pinMode(out_3, OUTPUT);
  pinMode(out_4, OUTPUT);
  
  
  digitalWrite(out_1, LOW); 
  digitalWrite(out_2, LOW); 
  digitalWrite(out_3, LOW); 
  digitalWrite(out_4, LOW); 

}

void loop() {

  if(digitalRead(in_1) == HIGH)
  {
    digitalWrite(out_1, HIGH); 
  }
  else
  {
    digitalWrite(out_1, LOW); 
  }

  if(digitalRead(in_2) == HIGH)
  {
    digitalWrite(out_2, HIGH); 
  }
  else
  {
    digitalWrite(out_2, LOW); 
  }

  if(digitalRead(in_3) == HIGH)
  {
    digitalWrite(out_3, HIGH); 
  }
  else
  {
    digitalWrite(out_3, LOW); 
  }

  if(digitalRead(in_4) == HIGH)
  {
    digitalWrite(out_4, HIGH); 
  }
  else
  {
    digitalWrite(out_4, LOW); 
  }
}

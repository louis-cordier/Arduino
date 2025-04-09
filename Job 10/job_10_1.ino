int pot;
void setup()
{
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop()
{
  pot = analogRead(A5);
  analogWrite(10 , pot/4);
  analogWrite(11 , 1023-(pot/4));
             
}
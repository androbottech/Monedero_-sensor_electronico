int contador =0;
void setup() 
{
  Serial.begin(9600);
  pinMode(12,INPUT);
}
void loop() 
{
  if(digitalRead(12)==0)
    {
      contador++;
      delay(50);
      Serial.println(contador);
    }
}


void setup()
{
  Serial.begin(115200);
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);
}

void loop()
{
  char r = 0;
  char g = 0;
  char b = 0;
  while(!Serial.available()) ;
  char c = Serial.read();
  digitalWrite(13,HIGH);
  for(int x=0; x < 640; x++)
  {
    for(int y=0; y < 480; y++)
    {
      Serial.write(r);
      Serial.write(g);
      Serial.write(b);
      g++;
      r+=2;
    }
    r++;
  }
  digitalWrite(13, LOW);
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
}

int num = 1;
void loop() {
  // put your main code here, to run repeatedly:

  Serial.println(num);

  num++;
  if (num > 12) num = 1;
  
  delay(10000);  
}

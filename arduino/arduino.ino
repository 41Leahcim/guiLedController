void setup() {
  // initialize the USART
  Serial.begin(9600);

  // initialize the led pins
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  // wait until the USART has been initialized
  while(!Serial);
}

void loop() {
  // wait for and read the next char
  char c = Serial.read();

  // change the leds to the selected value, if the char was between '0' and '7'
  if(c >= '0' && c <= '7'){
    digitalWrite(8, c & 1);
    digitalWrite(9, (c >> 1) & 1);
    digitalWrite(10, (c >> 2) & 1);
  }
}

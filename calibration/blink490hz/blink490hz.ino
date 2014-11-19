void setup()
{
  pinMode(6, OUTPUT);
  analogReference(DEFAULT);
  analogWrite(6, 127);   // this starts our PWM 'clock' with a 50% duty cycle
}

void loop() {
}

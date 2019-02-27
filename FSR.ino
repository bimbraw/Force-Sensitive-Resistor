const int FSR_PIN = A0; //Pin connected to FSR/resistor divider

const float VCC = 5; //Voltage of Ardunio 5V line
const float R_DIV = 3300; //Resistance of 3.3k resistor

void setup() 
{
  Serial.begin(9600);
  pinMode(FSR_PIN, INPUT);
}

void loop() 
{
  int fsrADC = analogRead(FSR_PIN);
  float fsrV = fsrADC * VCC / 1023.0;
  
  // Use voltage and static resistor value to 
  // calculate FSR resistance:
  float fsrR = R_DIV * (VCC / fsrV - 1.0);
  Serial.println("Resistance: " + String(fsrR) + " ohms");
  
  float force;
  float fsrG = 1.0 / fsrR; // Calculate conductance
  
  // Break the calibration curve to two linear slopes:
  if (fsrR <= 600) 
    force = (fsrG - 0.00075) / 0.00000032639;
  else
    force =  fsrG / 0.000000642857;
  
  force = force * 0.00980665;
  
  force = force * (6.96/17.70); //based on experimentation
  
  //printing force
  Serial.println(force);
  
  delay(10);
}

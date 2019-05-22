
int tempPin = A1;   // the output pin of LM35
int fan = 9;       // the pin where fan is
int led = 13;        // led pin
int temp;
int tempMin = 25;   // the temperature to start the fan 0%
int tempMax = 35;   // the maximum temperature when fan is at 100%
int fanSpeed;
int fanLCD;

void setup() {
  pinMode(fan, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(tempPin, INPUT);  
  Serial.begin(9600);
}

void loop() 
{  
   temp = readTemp();     // get the temperature
   
   if(temp < tempMin)     // if temp is lower than minimum temp
   {   
       fanSpeed = 0;      // fan is not spinning
       analogWrite(fan, fanSpeed); 
       fanLCD=0;
       digitalWrite(fan, LOW);       
   } 
   if((temp >= tempMin) && (temp <= tempMax)) // if temperature is higher than minimum temp
   {  
       fanSpeed = temp;//map(temp, tempMin, tempMax, 0, 100); // the actual speed of fan//map(temp, tempMin, tempMax, 32, 255);
       fanSpeed=1.5*fanSpeed;
       fanLCD = map(temp, tempMin, tempMax, 50, 100);  // speed of fan to display on LCD100
       analogWrite(fan, fanSpeed);  // spin the fan at the fanSpeed speed
   } 
   
   if(temp > tempMax) // if temp is higher than tempMax
     {        
     digitalWrite(led, HIGH);  // turn on led 
     } 
   else               // else turn of led
     {                    
     digitalWrite(led, LOW); 
     }
   
   Serial.println("TEMP: ");
   Serial.println(temp);      // display the temperature
   Serial.println("C ");
   
   Serial.println("FANSPEED PERCENTAGE: ");
   Serial.println(fanLCD);    // display the fan speed
   
   delay(10000);

}

int readTemp() {  // get the temperature and convert it to celsius
  temp = analogRead(tempPin);
  return temp * 0.48828125;
 
}

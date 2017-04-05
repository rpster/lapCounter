//Two-digit 7-segment LapCounter on Arduino Mega 2560
//
//            dB                dA
// 
//           segH              segA
//          ------            ------
//         |segN  |segJ      |segF  |segB
//         |      |          |      |
//          ------ segP       ------ segG
//         |segM  |          |segE  |
//         |      |segK      |      |segC
//          ------            ------
//           segL              segD
//


//**NOTE**
//Relay module requires reverse inputs
//I.E. High = Low, Low = High

int a = 22;  //For displaying segment "a"
int b = 23;  //For displaying segment "b"
int c = 24;  //For displaying segment "c"
int d = 25;  //For displaying segment "d"
int e = 26;  //For displaying segment "e"
int f = 27;  //For displaying segment "f"
int g = 28;  //For displaying segment "g"

int h = 30;  //For displaying segment "h"
int j = 31;  //For displaying segment "j"
int k = 32;  //For displaying segment "k"
int l = 33;  //For displaying segment "l"
int m = 34;  //For displaying segment "m"
int n = 35;  //For displaying segment "n"
int p = 36;  //For displaying segment "p"

//remote interrupt values
const byte upButton = 2;
const byte downButton = 3;

int dA = 0; //Right digit value
int dB = 0; //Left digit value

int newCount = LOW; //new input signaled
int lapsLeft = 0; //count of laps left

//blink values
int blinkState = LOW;
unsigned long previousBlink = 0;  // will store last blink
const long blinkOn = 50;   // milliseconds of on-time
const long blinkOff = 1950;  // milliseconds of off-time

//spin values
const int spin = 150;
unsigned long previousSpin = 0;
int compA = LOW;
int compB = LOW;
int compC = LOW;
int compD = HIGH;

//flash O values
const int flash = 150;
unsigned long previousFlash = 0;
int flashState = LOW;

//prime values
const int prime = 300;
unsigned long previousPrime = 0;
int primeState = LOW;


void setup() {
 //inputs
 pinMode(upButton, INPUT);
 pinMode(downButton, INPUT);

//interrupts
attachInterrupt(digitalPinToInterrupt(upButton), addLap, FALLING);
attachInterrupt(digitalPinToInterrupt(downButton), minusLap, FALLING);

  //dA - Right digit
  pinMode(a, OUTPUT);  //A
  pinMode(b, OUTPUT);  //B
  pinMode(c, OUTPUT);  //C
  pinMode(d, OUTPUT);  //D
  pinMode(e, OUTPUT);  //E
  pinMode(f, OUTPUT);  //F
  pinMode(g, OUTPUT);  //G

  //dB - Left digit
  pinMode(h, OUTPUT);  //H
  pinMode(j, OUTPUT);  //J
  pinMode(k, OUTPUT);  //K
  pinMode(l, OUTPUT);  //L
  pinMode(m, OUTPUT);  //M
  pinMode(n, OUTPUT);  //N
  pinMode(p, OUTPUT);  //P

  alloff();
  digitalWrite(g,LOW);
  digitalWrite(p,LOW);
  
  Serial.begin(9600);
}

void displayDA(int dA) //Display Right digit
{
 //Conditions for displaying segment a
 if(dA !=1 && dA != 4)
 digitalWrite(a,LOW);
 
 //Conditions for displaying segment b
 if(dA != 5 && dA != 6)
 digitalWrite(b,LOW);
 
 //Conditions for displaying segment c
 if(dA !=2)
 digitalWrite(c,LOW);
 
 //Conditions for displaying segment d
 if(dA != 1 && dA !=4 && dA !=7)
 digitalWrite(d,LOW);
 
 //Conditions for displaying segment e 
 if(dA == 2 || dA ==6 || dA == 8 || dA==0)
 digitalWrite(e,LOW);
 
 //Conditions for displaying segment f
 if(dA != 1 && dA !=2 && dA !=3 && dA !=7)
 digitalWrite(f,LOW);

 //Conditions for displaying segment g
 if (dA !=0 && dA !=1 && dA !=7)
 digitalWrite(g,LOW);
}

void displayDB(int dB) //Display Left digit
{
 //Conditions for displaying segment h
 if(dB !=1 && dB != 4)
 digitalWrite(h,LOW);
 
 //Conditions for displaying segment j
 if(dB != 5 && dB != 6)
 digitalWrite(j,LOW);
 
 //Conditions for displaying segment k
 if(dB !=2)
 digitalWrite(k,LOW);
 
 //Conditions for displaying segment l
 if(dB != 1 && dB !=4 && dB !=7)
 digitalWrite(l,LOW);
 
 //Conditions for displaying segment m 
 if(dB == 2 || dB == 6 || dB == 8 || dB ==0)
 digitalWrite(m,LOW);
 
 //Conditions for displaying segment n
 if(dB != 1 && dB !=2 && dB !=3 && dB !=7)
 digitalWrite(n,LOW);
 
 //Conditions for displaying segment p
 if (dB!=0 && dB!=1 && dB !=7)
 digitalWrite(p,LOW);
}

void digitMath()
{
  dA = (lapsLeft/1) % 10;
  dB = (lapsLeft/10) % 10;
}

void displayDigits()
{
  displayDA(dA);
  if(lapsLeft > 9)
  {
    displayDB(dB);
  }
}

void alloff() //digits off
{
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
  
  digitalWrite(h,HIGH);
  digitalWrite(j,HIGH);
  digitalWrite(k,HIGH);
  digitalWrite(l,HIGH);
  digitalWrite(m,HIGH);
  digitalWrite(n,HIGH);
  digitalWrite(p,HIGH);
}

void addLap() //add lap 
{
  newCount = HIGH;
  lapsLeft++;
  alloff();
  digitMath();
  displayDigits();
  Serial.println(lapsLeft);
}

void minusLap() //minus lap
{
  if(lapsLeft >= 0)
  {
  newCount = HIGH;
  lapsLeft--;
  alloff();
  digitMath();
  displayDigits();
  Serial.println(lapsLeft);
  }
}

void spinner()
{
  unsigned long currentMillis = millis();
  const int spin = 75;
  if(currentMillis - previousSpin >= spin && compD == HIGH)
  {
    alloff();
    digitalWrite(a,LOW);
    digitalWrite(l,LOW);
    previousSpin = currentMillis;
    compD = LOW;
    compA = HIGH;
  }
  if(currentMillis - previousSpin >= spin && compA == HIGH)
  {
    alloff();
    digitalWrite(b,LOW);
    digitalWrite(m,LOW);
    previousSpin = currentMillis;
    compA = LOW;
    compB = HIGH;
  }
  if(currentMillis - previousSpin >= spin && compB == HIGH)
  {
    alloff();
    digitalWrite(c,LOW);
    digitalWrite(n,LOW);
    previousSpin = currentMillis;
    compB = LOW;
    compC = HIGH;
  }
  if(currentMillis - previousSpin >= spin && compC == HIGH)
  {
    alloff();
    digitalWrite(d,LOW);
    digitalWrite(h,LOW);
    previousSpin = currentMillis;
    compC = LOW;
    compD = HIGH;
  }
}

void resetSpinner()
{
  compA = LOW;
  compB = LOW;
  compC = LOW;
  compD = HIGH;
}

void flashO()
{
  unsigned long currentMillis = millis();
  if(currentMillis - previousFlash >= flash)
  {
    previousFlash = currentMillis;  // Remember the time
    if (flashState == LOW)
    {
      digitalWrite(a,LOW);
      digitalWrite(b,LOW);
      digitalWrite(c,LOW);
      digitalWrite(d,LOW); 
      digitalWrite(h,LOW);
      digitalWrite(l,LOW);
      digitalWrite(m,LOW);
      digitalWrite(n,LOW);
      flashState = HIGH;
    }
    else
    {
      alloff();
      flashState = LOW;
    }
  }
}

void primes()
{
  unsigned long currentMillis = millis();
  if(currentMillis - previousPrime >= prime)
  {
    previousPrime = currentMillis;  // Remember the time
    if (primeState == LOW)
    {
      digitalWrite(e,LOW);
      digitalWrite(g,LOW);
      digitalWrite(h,LOW);
      digitalWrite(j,LOW); 
      digitalWrite(m,LOW);
      digitalWrite(n,LOW);
      digitalWrite(p,LOW);
      primeState = HIGH;
    }
    else
    {
      alloff();
      primeState = LOW;
    }
  }
}

void blink()
{
  unsigned long currentMillis = millis();
  if((blinkState == HIGH) && (currentMillis - previousBlink >= blinkOn))
  {
    blinkState = LOW;  // Turn it off
    previousBlink = currentMillis;  // Remember the time
    alloff();
  }
  else if ((blinkState == LOW) && (currentMillis - previousBlink >= blinkOff))
  {
    blinkState = HIGH;  // turn it on
    previousBlink = currentMillis;   // Remember the time
    digitalWrite(g,LOW);
    digitalWrite(p,LOW);
  }
}

void loop() {
  if(lapsLeft <= 0){
    flashO();
  }
  if((lapsLeft > 0) && (newCount == HIGH)){
    newCount = 0;
    resetSpinner();
  }
  
}


/*
 For node J which has light intensity sensor 

 This example code is in the public domain.
 */
 //7E 00 0E 10 01 00 13 A2 00 41 24 23 DC FF FE 00 00 D8
 #include <SoftwareSerial.h>
 

SoftwareSerial mySerial(5, 6); // RX, TX

long randNumber;

uint8_t temp_data = 0 , soil_data = 0 , light_data = 0 , nst =0, ned =30;
int state = 0;


  int i = 0; int count = 0; 
 
  int n = 2;           // number of nodes
  int index=0;         // index of next neighbor to connect

int counter = 0;
boolean start_timer = false;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  mySerial.begin(9600);
  randomSeed(analogRead(A2));
  
  read_send();
}

// the loop routine runs over and over again forever:
void loop() {
  int i;
 // byte (end1high);
  // read the input on analog pin 0:





if (nst == ned){
      // Serial.println("iteration " + String(count));
      // send message to neighbor
      ned = random(500);
      Serial.print("ned=");
      Serial.println(ned);
      nst = 0;
      for(int v = 0; v<5; v++)
      {
      read_send();
      Serial.print("Iteration no:");
      Serial.println(v);
      
      delay(200);
      mySerial.flush();
      }
    }
    
      nst++;
      Serial.println(nst);
      delay(200);
     // mySerial.flush();

  
if (mySerial.available() >=10) {

 if (mySerial.read()== 0x7E) 
  {
 for (uint8_t i=1; i<8 ; i++)
    {
//Serial.print(mySerial.read(),HEX);
//Serial.print(',');
      
      byte discardByte = mySerial.read();
      if(discardByte == 0x89)
      {
        Serial.println("got status");
        mySerial.flush();
        serialFlush();
      }
   }
int   t=mySerial.read();
int   n=mySerial.read();
//int   m=mySerial.read();

//   for (int k=1; k<10;k++)
//   {
//    byte discardByte = mySerial.read();
//   }

  Serial.println(t,HEX);
  Serial.println(n,HEX);
//  delay(100);
//  //}
//
 if(t == 0x01)
  {

temp_data = n;
Serial.println("temperature data stored");
    serialFlush();
    
  }
  if( t == 0x02)
  {
    soil_data = n;
    Serial.println("ldr data stored");
   serialFlush();

  }
if( t == 0x03)
 {
   light_data = n;
    Serial.println("soil moisture data stored");
   serialFlush();
  }
//  //while(1);
//  //Serial.write(sensorValue);
// // delay(3000);        // delay in between reads for stability
}
}
//delay(500);
//read_send();
}



void read_send(){
  
int litValue= analogRead(A0);

    litValue = map(litValue,0,1023,0,10);
   
   if(litValue < 0) litValue=0;



// int soilValue = analogRead(A0);
 Serial.println(litValue);
//  float val = float (soilValue)/ float(1024);
//  float soil_per = float(val) * float(100);
  byte lit = litValue;
  Serial.print(lit); 
  Serial.println("%");
  



  
 
 Serial.print("lit value = ");
 Serial.println(light_data);
   Serial.print(" post light value = ");
   litValue = (lit + light_data)/2; 
  light_data = litValue;
  
 Serial.println(light_data);
 Serial.print("Average sensor value = ");
 Serial.println(light_data);
 randNumber = random(4);
  Serial.println(randNumber);
  // print out the value you read:
  //7E 00 10 10 01 00 13 A2 00 41 24 1F A1 FF FE 00 00 68 69 46
  //for (i=0;i<1;i++)
//Serial.println(sensorValue,HEX);
//7E 00 0E 10 01 00 13 A2 00 41 62 FF F9 FF FE  - B node
//7E 00 0D 00 01 00 13 A2 00 41 63 0C 3F 00 02 12 46    f7
 int b= 0x1A1 + temp_data;// + 0x01;// {
 int b1 = 0x1A2 + soil_data; //+ 0x02;
 int b2 = 0x1A3 + light_data; //+ 0x03;
 
// 7E 00 0D 00 01 00 13 A2 00 41 63 0C 3D 00 01 12 49
 int c= 0x1A4 + temp_data ;//+ 0x01;
 int c1 = 0x1A5 + soil_data; // + 0x02;
 int c2 = 0x1A6 + light_data ; //+ 0x03;

//7E 00 0D 00 01 00 13 A2 00 41 63 0C 49 00 01 12 3D

 int d= 0x1B0 + temp_data ;//+ 0x01;
 int d1 = 0x1B1 + soil_data; // + 0x02;
 int d2 = 0x1B2 + light_data ; //+ 0x03;
 //Serial.println(b,HEX);
 byte checksumb = b;  
 byte checksumb1 = b1;  
 byte checksumb2 = b2;  
 
 
 byte checksumc = c;
 byte checksumc1 = c1;
 byte checksumc2 = c2;
 
 
 byte checksumd = d;
 byte checksumd1 = d1;
 byte checksumd2 = d2;
 
 //Serial.println(count,HEX);
checksumb = 0xFF - checksumb;
checksumb1 = 0xFF - checksumb1;
checksumb2 = 0xFF - checksumb2;

checksumc = 0XFF - checksumc;
checksumc1 = 0xFF - checksumc1;
checksumc2 = 0xFF - checksumc2;

checksumd = 0XFF - checksumd;
checksumd1 = 0xFF - checksumd1;
checksumd2 = 0xFF - checksumd2;

//Serial.println(count,HEX);
//b= 0xFF - b;

//7E 00 0E 10 01 00 13 A2 00 41 62 FF F9 FF FE  - B node
//7E 00 10 10 01 00 13 A2 00 41 62 FF F9 FF FE 00 00 01 12 8E
//7E 00 10 10 01 00 13 A2 00 41 62 FF F9 FF FE 00 00 01 00 A0
//7E 00 10 10 01 00 13 A2 00 41 63 0C 72 FF FE 00 00 01 00 19
//7E 00 0D 00 01 00 13 A2 00 41 63 0C 3F 00 02 12 46
//7E 00 0D 00 01 00 13 A2 00 41 63 0C 3A 00 01 12 4C
// ------------------------------------------------------------------ Frames for node I -------------------------------------------------------------
byte end1core[] = {0x7E,0x00,0x0D,0x00,0x01,0x00,0x13,0xA2,0x00,0x41,0x63,0x0C,0x3A,0x00,0x01,temp_data,checksumb};
byte end1guest1[] = {0x7E,0x00,0x0D,0x00,0x01,0x00,0x13,0xA2,0x00,0x41,0x63,0x0C,0x3A,0x00,0x02,soil_data,checksumb1};
byte end1guest2[] = {0x7E,0x00,0x0D,0x00,0x01,0x00,0x13,0xA2,0x00,0x41,0x63,0x0C,0x3A,0x00,0x03,light_data,checksumb2};

//-------------------------------------------------------------------Frames for node C --------------------------------------------------------------
 // 7E 00 0F 10 01 00 13 A2 00 41 63 0C 49 FF FE 00 00 F3 50
 //7E 00 0D 00 01 00 13 A2 00 41 63 0C 3D 00 01 12 49
 byte end2core[] = {0x7E,0x00,0x0D,0x00,0x01,0x00,0x13,0xA2,0x00,0x41,0x63,0x0C,0x3D,0x00,0x01,temp_data,checksumc}; 
 byte end2guest1[] = {0x7E,0x00,0x0D,0x00,0x01,0x00,0x13,0xA2,0x00,0x41,0x63,0x0C,0x3D,0x00,0x02,soil_data,checksumc1};
 byte end2guest2[] = {0x7E,0x00,0x0D,0x00,0x01,0x00,0x13,0xA2,0x00,0x41,0x63,0x0C,0x3D,0x00,0x03,light_data,checksumc2}; 
 
//-------------------------------------------------------------------Frames for node N --------------------------------------------------------------
 // 7E 00 0F 10 01 00 13 A2 00 41 63 0C 49 FF FE 00 00 F3 50
 //7E 00 0D 00 01 00 13 A2 00 41 63 0C 49 00 01 12 3D
 byte end3core[] = {0x7E,0x00,0x0D,0x00,0x01,0x00,0x13,0xA2,0x00,0x41,0x63,0x0C,0x49,0x00,0x01,temp_data,checksumd}; 
 byte end3guest1[] = {0x7E,0x00,0x0D,0x00,0x01,0x00,0x13,0xA2,0x00,0x41,0x63,0x0C,0x49,0x00,0x02,soil_data,checksumd1};
 byte end3guest2[] = {0x7E,0x00,0x0D,0x00,0x01,0x00,0x13,0xA2,0x00,0x41,0x63,0x0C,0x49,0x00,0x03,light_data,checksumd2}; 
 
 
 
 
 if(randNumber == 1)
 {
  mySerial.write(end1core,17);
  Serial.println(" sending to node 1 sample 1");
  delay(400);
  mySerial.write(end1guest1,17);
  Serial.println(" sending to node 1 sample 2");
  delay(400);
  mySerial.write(end1guest2,17);
  Serial.println(" sending to node 1 sample 3");
 
  serialFlush();
   delay(1000);

 }
 if(randNumber == 2)
 { 
  mySerial.write(end2core,17);
  Serial.println(" sending to node 2 sample 1");
  delay(400);
  mySerial.write(end2guest1,17);
  Serial.println(" sending to node 2 sample 2");
  delay(400);
  mySerial.write(end2guest2,17);
  Serial.println(" sending to node 2 sample 3");
 
 serialFlush();
  delay(1000);
 }


 if(randNumber == 3)
 { 
  mySerial.write(end3core,17);
  Serial.println(" sending to node 3 sample 1");
  delay(400);
  mySerial.write(end3guest1,17);
  Serial.println(" sending to node 3 sample 2");
  delay(400);
  mySerial.write(end3guest2,17);
  Serial.println(" sending to node 3 sample 3");
 
 serialFlush();
  delay(1000);
 }
}







void serialFlush(){
  while(mySerial.available() > 0) {
    char t = mySerial.read();
  }
}   

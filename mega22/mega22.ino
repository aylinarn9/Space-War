#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SHOOT_BUTTON 5 
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

int ledpin1=8;
int ledpin2=9;
int ledpin3=10;
int ledpincan1=19;
int ledpincan2=17;
int ledpincan3=18;
int randNumber;
int yeniNumber;
bool kontrol=false;
int silah_hakki=3;
int can_hakki=3;
int degisken=1;
int skor;
int k1,k2,k3;
int pinldr=A2;
 int sensordeger;
#define OLED_RESET    4 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define SCREEN_ADDRESS 0x3D
uint8_t ball_x , ball_y;
unsigned long ball_update;
  bool ateskontrol = false;
void drawCourt();
int selected = 0;
int entered = -1;
uint8_t uzaygemisi_X =0;
uint8_t uzaygemisi_y = 32;
int pot = A0;
int potdeger2=10;
int potdeger=0;
uint8_t new_x;
uint8_t new_y; 
int buzzer=7;
bool gosterge=false;
int matris[SCREEN_WIDTH][SCREEN_HEIGHT];

unsigned long simdikizaman,eskizaman=0;
unsigned long  simdikizaman1,eskizaman1=0;
  unsigned long test1;

const unsigned char epd_bitmap_uzay1 [] PROGMEM = {
	0xfe, 0x7f, 0xfe, 0x7f, 0xfd, 0xbf, 0xfc, 0x3f, 0xf5, 0xaf, 0xe3, 0xc7, 0xfc, 0x3f, 0xff, 0xff
};


class Block{
  public:
  int x,y;
  String tip;
  bool active;
 
};


Block dizi[16];


void engel()
{
 if(kontrol==false){
      for(int j=0;j<16;j++)
      {
       test1=millis();
       randNumber=(test1*41*(j+1))%54;
       if(randNumber<8){
         randNumber+=8;
       }
       if(j!=0){
         randNumber=dizi[j-1].y+20;
          randNumber=randNumber%54; 
       }
    
     dizi[j].x=128;
     dizi[j].y=randNumber;
     if(j%2==0){
      dizi[j].tip="x";
     }
     else
     {
       dizi[j].tip="z";
     }


    dizi[j].active=false;
  }  
   

 kontrol=true;
 
  }

}
void engelfonk()
{
  
  ateskontrol |= (digitalRead(SHOOT_BUTTON) == LOW);
   
 if(degisken==1){
 engel();

 }
 
   // bu kısımda engelleri yazdırıyoruz
  display.setTextColor(WHITE);
  display.setTextSize(1);
for(int i=0;i<2;i++)
{
   display.setCursor(dizi[i].x,dizi[i].y);
   display.println(dizi[i].tip);
}
  if(degisken>=2 && dizi[2].active==true){
 for(int i=2;i<4;i++)
{
   display.setCursor(dizi[i].x,dizi[i].y);
   display.println(dizi[i].tip);
}
  } 
    if(degisken>=3 && dizi[4].active==true){
 for(int i=4;i<6;i++)
{
   display.setCursor(dizi[i].x,dizi[i].y);
   display.println(dizi[i].tip);
}
  } 
   if(degisken>=4 && dizi[6].active==true){
 for(int i=6;i<8;i++)
{
   display.setCursor(dizi[i].x,dizi[i].y);
   display.println(dizi[i].tip);
}
  } 
   if(degisken>=5 && dizi[8].active==true){
 for(int i=8;i<10;i++)
{
   display.setCursor(dizi[i].x,dizi[i].y);
   display.println(dizi[i].tip);
}
  } 

 if(degisken>=6 && dizi[10].active==true){
 for(int i=10;i<12;i++)
{
   display.setCursor(dizi[i].x,dizi[i].y);
   display.println(dizi[i].tip);
}
  } 
  
   if(degisken>=7 && dizi[12].active==true){
 for(int i=12;i<14;i++)
{
   display.setCursor(dizi[i].x,dizi[i].y);
   display.println(dizi[i].tip);
}
  } 
   if(degisken>=8 && dizi[14].active==true){
 for(int i=14;i<16;i++)
{
  if(i==14&& gosterge==false){
  silah_hakki++;
  gosterge=true;
  digitalWrite(ledpin3,HIGH);
  }
   display.setCursor(dizi[i].x,dizi[i].y);
   display.println(dizi[i].tip);
}
  } 
  
//engeli asagı indiriyoruz
  display.setTextColor(WHITE);
  display.setTextSize(1);
for(int i=0;i<16;i++){
   simdikizaman=millis();
   if(simdikizaman-eskizaman>=1000){
     eskizaman=millis();
     display.clearDisplay();
    //engel();
    
  for(int j=0;j<2;j++){
      dizi[j].x-=8;
      dizi[j].active=true;
    display.setCursor(dizi[j].x,dizi[j].y);
     display.println(dizi[j].tip); 
  }
  if(degisken>=2){
  for(int j=2;j<4;j++){
      dizi[j].x-=8;
      dizi[j].active=true;
    display.setCursor(dizi[j].x,dizi[j].y);
     display.println(dizi[j].tip);
    
  }
 }
 
   if(degisken>=3){
  for(int j=4;j<6;j++){
      dizi[j].x-=8;
      dizi[j].active=true;
    display.setCursor(dizi[j].x,dizi[j].y);
     display.println(dizi[j].tip);
    
  }
 }
   if(degisken>=4){
  for(int j=6;j<8;j++){
      dizi[j].x-=8;
      dizi[j].active=true;
    display.setCursor(dizi[j].x,dizi[j].y);
     display.println(dizi[j].tip);
    
  }
 }
   if(degisken>=5){
  for(int j=8;j<10;j++){
      dizi[j].x-=8;
      dizi[j].active=true;
    display.setCursor(dizi[j].x,dizi[j].y);
     display.println(dizi[j].tip);
    
  }
 }
  if(degisken>=6){
  for(int j=10;j<12;j++){
      dizi[j].x-=8;
      dizi[j].active=true;
    display.setCursor(dizi[j].x,dizi[j].y);
     display.println(dizi[j].tip);
    
  }
 }
  if(degisken>=7){
  for(int j=12;j<14;j++){
      dizi[j].x-=8;
      dizi[j].active=true;
    display.setCursor(dizi[j].x,dizi[j].y);
     display.println(dizi[j].tip);
    
  }
 }
  if(degisken>=8){
  for(int j=14;j<16;j++){
      dizi[j].x-=8;
      dizi[j].active=true;
    display.setCursor(dizi[j].x,dizi[j].y);
     display.println(dizi[j].tip);
    
  }
 }
  degisken++;
   }

}
}
void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  //pinMode(7, INPUT_PULLUP);
  pinMode(buzzer,OUTPUT);
  pinMode(pinldr,OUTPUT);
 
  //display.begin(SSD1306_SWITCHCAPVCC,  0x3D); // 0x3c ile görüntü alamazsanız ı2c scannerdan adresinize bakınız
  pinMode(pot,INPUT);
    pinMode(SHOOT_BUTTON, INPUT_PULLUP);
    digitalWrite(SHOOT_BUTTON,1);
   
    pinMode(ledpin1,OUTPUT);
    pinMode(ledpin2,OUTPUT);
    pinMode(ledpin3,OUTPUT);

    pinMode(ledpincan1,OUTPUT);
    pinMode(ledpincan2,OUTPUT);
    pinMode(ledpincan3,OUTPUT);

    digitalWrite(ledpin1,HIGH);
    digitalWrite(ledpin2,HIGH);
    digitalWrite(ledpin3,HIGH);

    digitalWrite(ledpincan1,HIGH);
    digitalWrite(ledpincan2,HIGH);
    digitalWrite(ledpincan3,HIGH);


pinMode(22,OUTPUT);
pinMode(23,OUTPUT);
pinMode(24,OUTPUT);
pinMode(25,OUTPUT);
pinMode(26,OUTPUT);
pinMode(27,OUTPUT);
pinMode(28,OUTPUT);
///
pinMode(29,OUTPUT);
pinMode(30,OUTPUT);
pinMode(31,OUTPUT);
pinMode(32,OUTPUT);
pinMode(33,OUTPUT);
pinMode(34,OUTPUT);
pinMode(35,OUTPUT);
///
pinMode(36,OUTPUT);
pinMode(37,OUTPUT);
pinMode(38,OUTPUT);
pinMode(39,OUTPUT);
pinMode(40,OUTPUT);
pinMode(41,OUTPUT);
pinMode(42,OUTPUT);
  Serial.begin(9600);
   if(!display.begin(SSD1306_SWITCHCAPVCC,SCREEN_ADDRESS)){
    Serial.println(F("fmgkgfg"));
    for(;;);
  }
  display.clearDisplay();
  // Draw a single pixel in white
  display.drawPixel(118, 10, SSD1306_WHITE);
  display.display();

    //display.clearDisplay();
    //display.display();
     
}

void loop() {



displaymenu();
  
     if(can_hakki>0){
     for(int i=0;i<16;i++){
       if(abs(dizi[i].y-uzaygemisi_y)<=3 && dizi[i].x<uzaygemisi_X && dizi[i].tip!=""){
         can_hakki=can_hakki-1;
         
       }
     }
      
       if(can_hakki<=2){
       digitalWrite(ledpincan1,LOW);
          delay(500);
     }
     if(can_hakki<=1){
       digitalWrite(ledpincan2,LOW);
          delay(500);
     }
     if(can_hakki<=0){
      digitalWrite(ledpincan3,LOW);
          delay(500);
        }
     }
  

 }

void displaymenu(void) {

  int asagi = digitalRead(3);
  int yukari = digitalRead(2);
  int secim = digitalRead(6);
  //int geri = digitalRead(7);

  if (yukari == LOW && asagi == LOW) {
  };
  if (yukari == LOW) {
    selected = selected + 1;
    delay(200);
  };
  if (asagi == LOW) {
    selected = selected - 1;
    delay(200);
  };
  if (secim == LOW) {
    entered = selected;
  };

  const char *options[2] = {
    " Baslat",
    " Zorluk Seviyesi",
    
  };

  if (entered == -1) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("ana menu"));
    display.println("");
    for (int i = 0; i < 2; i++) {
      if (i == selected) {
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        display.println(options[i]);
      } else if (i != selected) {
        display.setTextColor(SSD1306_WHITE);
        display.println(options[i]);
      }
    }
    //baslat secenegi
  } else if (entered == 0) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

// oyunun kısmı 
int sensordeger=analogRead(A2);
 Serial.println(sensordeger);


if(sensordeger==10){
    Serial.println(7);
  display.invertDisplay(false);
    
  }
else{
  display.invertDisplay(true);
  
}

//bool ledkontrol=false;
engelfonk();

    static bool a1=false;
     potdeger= map(analogRead(pot),0,1023,0,512);
    display.drawBitmap(uzaygemisi_X,uzaygemisi_y,epd_bitmap_uzay1,8,8,WHITE);

      if(potdeger<256){
        if(potdeger2!=potdeger){
        if(uzaygemisi_y>0){
          a1=true;

            display.drawBitmap(uzaygemisi_X,uzaygemisi_y,epd_bitmap_uzay1,8,8,BLACK);
          
             uzaygemisi_y -= 8; 
             skor+=1;
             k1=skor%10;
             k2=skor%100;
             k2=k2/10;
             k3=skor/100;
             segmentgosterim(k1);
            segmentgosterim1(k2);
             segmentgosterim2(k3);
            delay(50);
          }
        }
         potdeger2=potdeger;
   }
     
      
  
      if(potdeger>256 && potdeger<512){
       if(potdeger2!=potdeger){
      if(uzaygemisi_y<50)
      { 
          a1=true;
           display.drawBitmap(uzaygemisi_X,uzaygemisi_y,epd_bitmap_uzay1,8,8,BLACK);
          uzaygemisi_y += 8;
               skor+=1;
             k1=skor%10;
             k2=skor%100;
             k2=k2/10;
             k3=skor/100;
             segmentgosterim(k1);
            segmentgosterim1(k2);
             segmentgosterim2(k3);
              delay(50);
      }   
        }
         potdeger2=potdeger;
      }
    if(a1=true){  
    display.drawBitmap(uzaygemisi_X,uzaygemisi_y,epd_bitmap_uzay1,8,8,WHITE);
    display.display();

    }


    if(ateskontrol){
       if(silah_hakki>0){
     ateset(uzaygemisi_X,uzaygemisi_y,silah_hakki);
     for(int i=0;i<16;i++){
       if(abs(dizi[i].y-uzaygemisi_y)<3){
          display.setTextColor(BLACK);
          display.setTextSize(1);
        display.setCursor(dizi[i].x,dizi[i].y);
        dizi[i].tip="";
        break;
       }
     }
    
       silah_hakki=silah_hakki-1;
        ateskontrol=false;
       
        if(silah_hakki<=2){
          digitalWrite(ledpin1,LOW);
          delay(500);
         
        }
        if(silah_hakki<=1){
          digitalWrite(ledpin2,LOW);
          delay(500);
         
        }
        if(silah_hakki<=0 || gosterge==true){
          digitalWrite(ledpin3,LOW);
          delay(500);
          
        }
        
     }
     
  }
   
   a1=false;

   

  } // zorluk seviyesi secenegi

  else if (entered == 1) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("zorluk seviyesi 1"));
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 20);
    display.println(F("zorluk seviyesi 2"));
  }
  
  display.display();
}
void ateset(uint8_t uzaygemisi_X,uint8_t uzaygemisi_y,int silah_hakki)
 {
 new_x=uzaygemisi_X+8;
 new_y=uzaygemisi_y+3;

  for(int i=0;i<16;i++){
       new_x=new_x+8;
       new_y=new_y;
  display.drawPixel(new_x,new_y,WHITE);
  display.display();
  display.clearDisplay();
  engelfonk();
  display.drawBitmap(uzaygemisi_X,uzaygemisi_y,epd_bitmap_uzay1,8,8,WHITE);
  
      }
    
 
 }
  
void segmentgosterim(int k1){
 switch(k1){
  case 0:
digitalWrite(36,HIGH);
digitalWrite(37,HIGH);
digitalWrite(38,HIGH);
digitalWrite(39,HIGH);
digitalWrite(40,HIGH);
digitalWrite(41,HIGH);
digitalWrite(42,LOW);

break;

  case 1:
digitalWrite(36,LOW);
digitalWrite(37,HIGH);
digitalWrite(38,HIGH);
digitalWrite(39,LOW);
digitalWrite(40,LOW);
digitalWrite(41,LOW);
digitalWrite(42,LOW);

break;
  case 2:
digitalWrite(36,HIGH);
digitalWrite(37,HIGH);
digitalWrite(38,LOW);
digitalWrite(39,HIGH);
digitalWrite(40,HIGH);
digitalWrite(41,LOW);
digitalWrite(42,HIGH);

break;
  case 3:
digitalWrite(36,HIGH);
digitalWrite(37,HIGH);
digitalWrite(38,HIGH);
digitalWrite(39,HIGH);
digitalWrite(40,LOW);
digitalWrite(41,LOW);
digitalWrite(42,HIGH);

break;
  case 4:
digitalWrite(36,LOW);
digitalWrite(37,HIGH);
digitalWrite(38,HIGH);
digitalWrite(39,LOW);
digitalWrite(40,LOW);
digitalWrite(41,HIGH);
digitalWrite(42,HIGH);

break;
  case 5:
digitalWrite(36,HIGH);
digitalWrite(37,LOW);
digitalWrite(38,HIGH);
digitalWrite(39,HIGH);
digitalWrite(40,LOW);
digitalWrite(41,HIGH);
digitalWrite(42,HIGH);

break;
  case 6:
digitalWrite(36,HIGH);
digitalWrite(37,LOW);
digitalWrite(38,HIGH);
digitalWrite(39,HIGH);
digitalWrite(40,HIGH);
digitalWrite(41,HIGH);
digitalWrite(42,HIGH);

break;
  case 7:
digitalWrite(36,HIGH);
digitalWrite(37,HIGH);
digitalWrite(38,HIGH);
digitalWrite(39,LOW);
digitalWrite(40,LOW);
digitalWrite(41,LOW);
digitalWrite(42,HIGH);

break;
  case 8:
digitalWrite(36,HIGH);
digitalWrite(37,HIGH);
digitalWrite(38,HIGH);
digitalWrite(39,HIGH);
digitalWrite(40,HIGH);
digitalWrite(41,HIGH);
digitalWrite(42,HIGH);

break;
  case 9:
digitalWrite(36,HIGH);
digitalWrite(37,HIGH);
digitalWrite(38,HIGH);
digitalWrite(39,HIGH);
digitalWrite(40,LOW);
digitalWrite(41,HIGH);
digitalWrite(42,HIGH);

break;


 }


}
  
void segmentgosterim1(int k2){
 switch(k2){
  case 0:
digitalWrite(29,HIGH);
digitalWrite(30,HIGH);
digitalWrite(31,HIGH);
digitalWrite(32,HIGH);
digitalWrite(33,HIGH);
digitalWrite(34,HIGH);
digitalWrite(35,LOW);

break;
  case 1:
digitalWrite(29,LOW);
digitalWrite(30,HIGH);
digitalWrite(31,HIGH);
digitalWrite(32,LOW);
digitalWrite(33,LOW);
digitalWrite(34,LOW);
digitalWrite(35,LOW);

break;
  case 2:
digitalWrite(29,HIGH);
digitalWrite(30,HIGH);
digitalWrite(31,LOW);
digitalWrite(32,HIGH);
digitalWrite(33,HIGH);
digitalWrite(34,LOW);
digitalWrite(35,HIGH);

break;
  case 3:
digitalWrite(29,HIGH);
digitalWrite(30,HIGH);
digitalWrite(31,HIGH);
digitalWrite(32,HIGH);
digitalWrite(33,LOW);
digitalWrite(34,LOW);
digitalWrite(35,HIGH);

break;
  case 4:
digitalWrite(29,LOW);
digitalWrite(30,HIGH);
digitalWrite(31,HIGH);
digitalWrite(32,LOW);
digitalWrite(33,LOW);
digitalWrite(34,HIGH);
digitalWrite(35,HIGH);

break;
  case 5:
digitalWrite(29,HIGH);
digitalWrite(30,LOW);
digitalWrite(31,HIGH);
digitalWrite(32,HIGH);
digitalWrite(33,LOW);
digitalWrite(34,HIGH);
digitalWrite(35,HIGH);

break;
  case 6:
digitalWrite(29,HIGH);
digitalWrite(30,LOW);
digitalWrite(31,HIGH);
digitalWrite(32,HIGH);
digitalWrite(33,HIGH);
digitalWrite(34,HIGH);
digitalWrite(35,HIGH);

break;
  case 7:
digitalWrite(29,HIGH);
digitalWrite(30,HIGH);
digitalWrite(31,HIGH);
digitalWrite(32,LOW);
digitalWrite(33,LOW);
digitalWrite(34,LOW);
digitalWrite(35,HIGH);

break;
  case 8:
digitalWrite(29,HIGH);
digitalWrite(30,HIGH);
digitalWrite(31,HIGH);
digitalWrite(32,HIGH);
digitalWrite(33,HIGH);
digitalWrite(34,HIGH);
digitalWrite(35,HIGH);

break;
  case 9:
digitalWrite(29,HIGH);
digitalWrite(30,HIGH);
digitalWrite(31,HIGH);
digitalWrite(32,HIGH);
digitalWrite(33,LOW);
digitalWrite(34,HIGH);
digitalWrite(35,HIGH);

break;


 }


}
void segmentgosterim2(int k3){
 switch(k3){
  case 0:
 digitalWrite(22,HIGH);
digitalWrite(23,HIGH);
digitalWrite(24,HIGH);
digitalWrite(25,HIGH);
digitalWrite(26,HIGH);
digitalWrite(27,HIGH);
digitalWrite(28,LOW);

break;
  case 1:
digitalWrite(22,LOW);
digitalWrite(23,HIGH);
digitalWrite(24,HIGH);
digitalWrite(25,LOW);
digitalWrite(26,LOW);
digitalWrite(27,LOW);
digitalWrite(28,LOW);

break;

  case 2:
digitalWrite(22,HIGH);
digitalWrite(23,HIGH);
digitalWrite(24,LOW);
digitalWrite(25,HIGH);
digitalWrite(26,HIGH);
digitalWrite(27,LOW);
digitalWrite(28,HIGH);

break;
  case 3:
digitalWrite(22,HIGH);
digitalWrite(23,HIGH);
digitalWrite(24,HIGH);
digitalWrite(25,HIGH);
digitalWrite(26,LOW);
digitalWrite(27,LOW);
digitalWrite(28,HIGH);

break;
  case 4:
digitalWrite(22,LOW);
digitalWrite(23,HIGH);
digitalWrite(24,HIGH);
digitalWrite(25,LOW);
digitalWrite(26,LOW);
digitalWrite(27,HIGH);
digitalWrite(28,HIGH);

break;
  case 5:
digitalWrite(22,HIGH);
digitalWrite(23,LOW);
digitalWrite(24,HIGH);
digitalWrite(25,HIGH);
digitalWrite(26,LOW);
digitalWrite(27,HIGH);
digitalWrite(28,HIGH);

break;
  case 6:
digitalWrite(22,HIGH);
digitalWrite(23,LOW);
digitalWrite(24,HIGH);
digitalWrite(25,HIGH);
digitalWrite(26,HIGH);
digitalWrite(27,HIGH);
digitalWrite(28,HIGH);

break;
  case 7:
digitalWrite(22,HIGH);
digitalWrite(23,HIGH);
digitalWrite(24,HIGH);
digitalWrite(25,LOW);
digitalWrite(26,LOW);
digitalWrite(27,LOW);
digitalWrite(28,HIGH);

break;
  case 8:
digitalWrite(22,HIGH);
digitalWrite(23,HIGH);
digitalWrite(24,HIGH);
digitalWrite(25,HIGH);
digitalWrite(26,HIGH);
digitalWrite(27,HIGH);
digitalWrite(28,HIGH);

break;
  case 9:
digitalWrite(22,HIGH);
digitalWrite(23,HIGH);
digitalWrite(24,HIGH);
digitalWrite(25,HIGH);
digitalWrite(26,HIGH);
digitalWrite(27,HIGH);
digitalWrite(28,HIGH);

break;


 }


}

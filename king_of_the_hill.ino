    #include <NewTone.h>
    #include <LiquidCrystal_I2C.h>

    const int RedPin = 12;
    const int GreenPin = 11;
    const int BluePin = 10;
    const int BuzzerPin = 9;
    const int Team1Pin = 2;
    const int Team2Pin = 3;
    const int SettingPin = A1;
    const int PotPin = A7;
    int teamvar=0;
    int maxtime=600;
    int t1time=0;
    int t2time=0;
    bool initvar=1;LiquidCrystal_I2C lcd(0x27,16,2);

    
void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Airsoft V1.0");
  lcd.setCursor(0,1);
  lcd.print("King of the hill");
  pinMode(Team1Pin, INPUT_PULLUP);
  pinMode(Team2Pin, INPUT_PULLUP);
  pinMode(SettingPin, INPUT_PULLUP);
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);
  digitalWrite(BuzzerPin, LOW);
  delay(1000);
  attachInterrupt(digitalPinToInterrupt(Team1Pin),team1press,FALLING);
  attachInterrupt(digitalPinToInterrupt(Team2Pin),team2press,FALLING);
  NewTone(BuzzerPin,500,100);
  delay(1000);
  teamvar=0;
}

void loop() {
  
  unsigned long time1 = millis();
  initvar=0;

  
  while(digitalRead(SettingPin)==0){ //##################SETTINGS#####################
    lcd.clear();
    lcd.print("Settings");
    attachInterrupt(digitalPinToInterrupt(Team1Pin),team1press,FALLING);
    attachInterrupt(digitalPinToInterrupt(Team2Pin),team2press,FALLING);
    t1time=0;
    t2time=0;
    teamvar=0;
    digitalWrite(RedPin,HIGH);
    digitalWrite(GreenPin,LOW);
    digitalWrite(BluePin,LOW);
    int pot=analogRead(PotPin);
    lcd.setCursor(0,1);
    lcd.print("Time: ");
    if(pot<128){
      maxtime=300;
    } 
    if(pot>=128&&pot<256){
      maxtime=600;
    }
    if(pot>=256&&pot<384){
      maxtime=900;
    }
    if(pot>=384&&pot<512){
      maxtime=1200;
    }
    if(pot>=512&&pot<640){
      maxtime=1800;
    }
    if(pot>=640&&pot<768){
      maxtime=2400;
    }
    if(pot>=768){
      maxtime=3600;
    }
    lcd.print(maxtime/60);
    lcd.print(":00");
  delay(100);
  }
  

  
  if(teamvar==1){ //##################TEAM 1 CAPTURED#####################
    t1time++;
    if(t1time>=maxtime){
      while(digitalRead(SettingPin)==1){ //##################TEAM 1 WIN#####################
        lcd.clear();
        lcd.print("GREEN team wins!");
        lcd.setCursor(0,1);
        lcd.print("BLUE: ");
        if (((maxtime-t2time)/60)<10) lcd.print("0");
        lcd.print((maxtime-t2time)/60);
        lcd.print(":");
        if (((maxtime-t2time)%60)<10) lcd.print("0");
        lcd.print((maxtime-t2time)%60);
        detachInterrupt(digitalPinToInterrupt(Team1Pin));
        detachInterrupt(digitalPinToInterrupt(Team2Pin));
        digitalWrite(RedPin,LOW);
        digitalWrite(GreenPin,HIGH);
        NewTone( BuzzerPin,500,200);
        delay(300);
        digitalWrite(RedPin,HIGH);
        digitalWrite(GreenPin,LOW);
        delay(300);

      }
    }
  }

  
  if(teamvar==2){ //##################TEAM 2 CAPTURED#####################
    t2time++;
    if(t2time>=maxtime){
      while(digitalRead(SettingPin)==1){ //##################TEAM 2 WIN#####################
        lcd.clear();
        lcd.print("GREEN: ");
        if (((maxtime-t1time)/60)<10) lcd.print("0");
        lcd.print((maxtime-t1time)/60);
        lcd.print(":");
        if (((maxtime-t1time)%60)<10) lcd.print("0");
        lcd.print((maxtime-t1time)%60);
        lcd.setCursor(0,1);
        lcd.print("BLUE team wins!");
        
        
        detachInterrupt(digitalPinToInterrupt(Team1Pin));
        detachInterrupt(digitalPinToInterrupt(Team2Pin));
        digitalWrite(RedPin,LOW);
        digitalWrite(BluePin,HIGH);
        NewTone( BuzzerPin,500,200);
        delay(300);
        digitalWrite(RedPin,HIGH);
        digitalWrite(BluePin,LOW);
        delay(300);
      }
    }
  }
  //##############################DISPLAY TIMES#######################################
  lcd.clear();
  lcd.print("GREEN: ");
  if (((maxtime-t1time)/60)<10) lcd.print("0");
  lcd.print((maxtime-t1time)/60);
  lcd.print(":");
  if (((maxtime-t1time)%60)<10) lcd.print("0");
  lcd.print((maxtime-t1time)%60);

  lcd.setCursor(0,1);
  lcd.print("BLUE: ");
  if (((maxtime-t2time)/60)<10) lcd.print("0");
  lcd.print((maxtime-t2time)/60);
  lcd.print(":");
  if (((maxtime-t2time)%60)<10) lcd.print("0");
  lcd.print((maxtime-t2time)%60);
  
  if(teamvar!=0){ //###########TICKING SOUND############
    digitalWrite(BuzzerPin,HIGH);
    delay(1);
    digitalWrite(BuzzerPin,LOW);
  }

  
  int delaytime=1000+time1-millis();
  if(delaytime>0)
    delay(delaytime);
 }

void team1press(){ //##################TEAM 1 PRESS#####################
  if (initvar==0&&digitalRead(Team1Pin)==LOW){
  //NewTone(BuzzerPin,500,100);
  digitalWrite(RedPin,LOW);
  digitalWrite(GreenPin,HIGH);
  digitalWrite(BluePin,LOW);
  teamvar=1;
  }
  }
void  team2press(){ //##################TEAM 2 PRESS#####################
  if (initvar==0&&digitalRead(Team2Pin)==LOW){
  //NewTone(BuzzerPin,500,100);
  digitalWrite(RedPin,LOW);
  digitalWrite(GreenPin,LOW);
  digitalWrite(BluePin,HIGH);
  teamvar=2;
  }
  }

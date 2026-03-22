#define RIGHT 4
#define CENTER 3
#define LEFT 2 //라인트레이서

#define R1 12
#define R2 11
#define L1 10
#define L2 9 //L298

int mode=0;
int count=0;
int next=0;

int pre_R;
int pre_C;
int pre_L;

void stop() { //정지
  analogWrite(R1, 0);
  analogWrite(R2, 0);
  analogWrite(L1, 0);
  analogWrite(L2, 0);
}

void forward() { //전진
  analogWrite(R1, 0);
  analogWrite(R2, 248);
  analogWrite(L1, 0);
  analogWrite(L2, 248);
}

void FullSpeed() { //전속력 직진
  analogWrite(R1, 0); 
  analogWrite(R2, 254);
  analogWrite(L1, 0);
  analogWrite(L2, 254);
}

void Lturn() { //왼쪽 회전
  while(digitalRead(CENTER) != LOW) {
    analogWrite(R1, 0); 
    analogWrite(R2, 245);
    analogWrite(L1, 0);
    analogWrite(L2, 0);
  }
}


void Rturn() { //오른쪽 회전
  while(digitalRead(CENTER) != LOW) {
    analogWrite(R1, 0); 
    analogWrite(R2, 0);
    analogWrite(L1, 0);
    analogWrite(L2, 245);
  }
}



void line() { //라인트레이싱
  if(digitalRead(RIGHT)== LOW && digitalRead(CENTER) == HIGH && digitalRead(LEFT) == HIGH && mode==0 ){ //오른쪽에 감지
    Rturn();       
  }       
  else if(digitalRead(RIGHT)== HIGH && digitalRead(CENTER) == HIGH && digitalRead(LEFT) == LOW && mode==0){ //왼쪽에 감지
    Lturn();      
  }
  else if(digitalRead(RIGHT)== HIGH && digitalRead(CENTER) == LOW && digitalRead(LEFT) == HIGH && mode==0){ //흰검흰
    forward();       
  }
  else if(digitalRead(RIGHT)== HIGH && digitalRead(CENTER) == HIGH && digitalRead(LEFT) == HIGH && mode==0){ //흰흰흰
    forward();   
  }
  else if(digitalRead(RIGHT)== LOW && digitalRead(CENTER) == LOW && digitalRead(LEFT) == LOW && mode==0){ //검검검 
    forward(); 
  } 
}

void setup() { // 핀 모드 설정
  pinMode(RIGHT, INPUT);
  pinMode(CENTER, INPUT);
  pinMode(LEFT, INPUT);
  
  pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);


  
  Serial.begin(9600); 
}

void loop() {
 

    
  if (digitalRead(RIGHT)== HIGH || digitalRead(CENTER) ==HIGH || digitalRead(LEFT) ==HIGH) {   
    if(pre_R ==LOW  && pre_C ==LOW && pre_L ==LOW && count<3 ){
      count++;
    }   
  }  

  if (count==1&&mode==0) {
    forward();    
  }    
  else if (count==2&&mode==0) {
    line();      
  }       
  else if (count==3&&mode==0) {
    if(next==0) {
      analogWrite(R1, 0); 
      analogWrite(R2, 250);
      analogWrite(L1, 0);
      analogWrite(L2, 250); 
      delay(3000); //약간 비틀어서 올라감
      next=1;
    }
    if (next==1) {
      analogWrite(R1, 0); 
      analogWrite(R2, 250);
      analogWrite(L1, 0);
      analogWrite(L2, 250);    
      if (digitalRead(LEFT) == HIGH && digitalRead(CENTER) == HIGH && digitalRead(RIGHT) == HIGH) {
        next=2;
      }            
    } 
    if (next==2) {
       stop();
       if (digitalRead(RIGHT)== LOW || digitalRead(CENTER) ==LOW || digitalRead(LEFT) == LOW) {
        next=3;  
       }
    }
    if (next==3) {
      
      if (digitalRead(LEFT) == LOW && digitalRead(CENTER) == LOW && digitalRead(RIGHT)==LOW) {
      FullSpeed();
      }
      else if (digitalRead(LEFT) == HIGH && digitalRead(CENTER) == HIGH && digitalRead(RIGHT) == HIGH) {     
        analogWrite(R1, 255); 
        analogWrite(R2, 0);
        analogWrite(L1, 255);
        analogWrite(L2, 0); 
        delay(1000);
        analogWrite(R1, 0); 
        analogWrite(R2, 250);
        analogWrite(L1, 250);
        analogWrite(L2, 0); 
        delay(900);   
      }
      else if (digitalRead(LEFT) == HIGH && digitalRead(CENTER) == LOW && digitalRead(RIGHT)==LOW) {
        analogWrite(R1, 100); 
        analogWrite(R2, 0);
        analogWrite(L1, 0);
        analogWrite(L2, 250);
        delay(1400);       
      }
      else if (digitalRead(LEFT) == LOW && digitalRead(CENTER) == LOW && digitalRead(RIGHT)==HIGH) {
        analogWrite(R1, 0); 
        analogWrite(R2, 250);
        analogWrite(L1, 100);
        analogWrite(L2, 0);
        delay(1400);
      }
      
    } 
  
  } 
     
  pre_L=digitalRead(LEFT);
  pre_C=digitalRead(CENTER);
  pre_R=digitalRead(RIGHT);
  delay(1);  
}        

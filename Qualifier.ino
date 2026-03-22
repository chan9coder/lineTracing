#define RIGHT 6
#define CENTER 5
#define LEFT 4 //라인트레이서

#define R1 8
#define R2 22
#define L1 9
#define L2 23 //L298

int mode=0;
int count=0;
int next=0;

int pre_R;
int pre_C;
int pre_L;


void forward() { //전진
  analogWrite(R1, 0);
  analogWrite(R2, 253);
  analogWrite(L1, 0);
  analogWrite(L2, 253);
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
    analogWrite(R2, 250);
    analogWrite(L1, 0);
    analogWrite(L2, 0);
  }
}


void Rturn() { //오른쪽 회전
  while(digitalRead(CENTER) != LOW) {
    analogWrite(R1, 0); 
    analogWrite(R2, 0);
    analogWrite(L1, 0);
    analogWrite(L2, 250);
  }
}

void Rturn2() { //오른쪽 회전
  analogWrite(R1, 20); 
  analogWrite(R2, 0);
  analogWrite(L1, 0);
  analogWrite(L2, 210);
}

void line() { //라인트레이싱
  if(digitalRead(RIGHT)== LOW && digitalRead(CENTER) == HIGH && digitalRead(LEFT) == HIGH && mode==0 ){ //흰흰검
    Rturn();       
  }       
  else if(digitalRead(RIGHT)== HIGH && digitalRead(CENTER) == HIGH && digitalRead(LEFT) == LOW && mode==0){ //검흰흰
    Lturn();      
  }
  else if(digitalRead(RIGHT)== HIGH && digitalRead(CENTER) == LOW && digitalRead(LEFT) == HIGH && mode==0){ //흰검흰
    forward();       
  }
  else if(digitalRead(RIGHT)== HIGH && digitalRead(CENTER) == HIGH && digitalRead(LEFT) == HIGH && mode==0){ //흰흰흰
    forward();   
  }
  /*else if(digitalRead(RIGHT)== HIGH && digitalRead(CENTER) == LOW && digitalRead(LEFT) == LOW && mode==0){ //검검흰
    Lturn();  
  }*/
  
  else if(digitalRead(RIGHT)== LOW && digitalRead(CENTER) == LOW && digitalRead(LEFT) == LOW && mode==0){ //검검검 
    forward(); 
  }
  else if(digitalRead(LEFT) == HIGH && digitalRead(CENTER) == LOW && digitalRead(RIGHT)== LOW && mode==1) { //흰검검 우회전
    Rturn2();   
  }
  else if(digitalRead(LEFT) == HIGH && digitalRead(CENTER) == HIGH && digitalRead(RIGHT)== LOW &&mode==1) { //흰흰검 우회전
    Rturn2();
  }
  else if(digitalRead(LEFT) == LOW && digitalRead(CENTER) == LOW && digitalRead(RIGHT)== LOW &&mode==1) { //검검검 직진
    forward();
  }
  else if(digitalRead(LEFT) == HIGH && digitalRead(CENTER) == HIGH && digitalRead(RIGHT)==HIGH&& mode==1){ //흰흰흰 mode=2
    mode=2; 
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
      analogWrite(L2, 245);    
      delay(1800); //약간 비틀어서 올라감  
      analogWrite(R1, 0); 
      analogWrite(R2, 230);
      analogWrite(L1, 0);
      analogWrite(L2, 0); 
      delay(760); //좌회전
      next=1;        
    }
    if (next==1) {
     forward(); //직진
      if (digitalRead(LEFT) ==HIGH) {
        mode=1;  
      } 
    }
    if (next==2) {
      line();     
    }
  }  
  else if(count==3&&mode==1) {
      line();      
  } 
    
  else if (count==3&& mode==2) {
    analogWrite(R1, 0); 
    analogWrite(R2, 200);
    analogWrite(L1, 0);
    analogWrite(L2, 0);
    delay(1400); //좌회전, 1. 1300
    forward();
    delay(800); // 1500?
    next=2;
    mode=0; // mode==0되는지 확인하고 수정
  }     
  pre_L=digitalRead(LEFT);
  pre_C=digitalRead(CENTER);
  pre_R=digitalRead(RIGHT);
  delay(1);
   
}        

//검은색 없는 곳에서 출발

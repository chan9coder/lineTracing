#define in1 4//오른쪽
#define in2 5
#define in3 6//왼쪽
#define in4 7

#define Tr1 A5
#define Ec1 A4  
#define Tr2 A2
#define Ec2 A1

#define L 8 // 라인트레이싱센서 L
#define C 9 // 라인트레이싱센서 C
#define R 10 // 라인트레이싱센서 R

int a=0;
int i=0; // 카운트변수
int level= 0; //조건식
int num=0;
int OnHC=0; 
int stage =0;

void Board(){
  unsigned long millisTime = millis(); // 1초 단위면 millisTime = millis()/1000;
  int m,s,ss;
  int ss2 = (millisTime/10)%10;
  int ss1 = (millisTime/100)%10;
  int s2 = (millisTime/1000)%10;
  int s1 = (millisTime/10000)%6;
  int m2 = (millisTime/60000)%10;
  int m1= (millisTime/600000)%10;
  
  Serial.print("level:");
  Serial.print(level);
  Serial.print(" LTS:");
  Serial.print(digitalRead(L));
  Serial.print(digitalRead(C));
  Serial.print(digitalRead(R));
  Serial.print(" HC1:");
  Serial.print(HC(Tr1,Ec1),0);
  Serial.print("mm");
  Serial.print(" 교차로:");
  Serial.print(i);
  Serial.print(" 위치:");
    if(level==0) Serial.print("라인(1단계)");
    else if(level ==2)  Serial.print("라인(3단계)");
    else  Serial.print("경기장(2단계)");
  Serial.print(" Timer:");
  Serial.print(m1);
  Serial.print(m2); 
  Serial.print(":");
  Serial.print(s1);
  Serial.print(s2);
  Serial.print(":");
  Serial.print(ss1);
  Serial.println(ss2);
}
void motor(int a, int b, int c, int d){ //모터제어함수 
  analogWrite(in3, a);//왼쪽
  analogWrite(in4, b); 
  analogWrite(in1, c);//오른쪽
  analogWrite(in2, d);
}
void forward(){ //전진 (오른, 왼)
  motor(0,250,0,250);//
}
void right(){ //좌 스윙턴
  motor(50,0,0,250);
}
void left() { //우 스윙턴
  motor(0,250,50,0);
}
void p_left(){//좌 포인트턴
  motor(250,0,0,250);
}
void p_right(){//우 포인트턴
  motor(0,250,250,0);
}
void stop(){
  while(1) motor(0,0,0,0);
}
double HC(int Tr, int Ec){//초음파센서 거리계산 함수
  unsigned long x;
  digitalWrite(Tr,HIGH);//Tr
  delayMicroseconds(10);
  digitalWrite(Tr, LOW);//Tr
  x = pulseIn(Ec, HIGH, 30000UL);//Ec
  return x * 0.17;
}
double IRS(int Vo) {//적외선센서 함수
  double voltage, distance;
  voltage=5.0/1023.0*double(analogRead(Vo));
  return 27.588 * pow(voltage, -1.198);
}
void setup(){
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  pinMode(L,INPUT);
  pinMode(C,INPUT);
  pinMode(R,INPUT);

  pinMode(Ec1,INPUT);//Ec
  pinMode(Tr1,OUTPUT);//Tr
  pinMode(Ec2,INPUT);//Ec
  pinMode(Tr2,OUTPUT);//Tr
  
  Serial.begin(9600);
}
void line(int j,int v) { //라인트레이싱
  if(j==1){
    if(i==3 && v==1) level =1;
    if(i==8) stop(); 
    if(!digitalRead(L)&& digitalRead(C) && !digitalRead(R)) forward();//010 전진 
    else if(!digitalRead(L)&& !digitalRead(C) && digitalRead(R)) left();//001
    else if(!digitalRead(L)&& digitalRead(C) && digitalRead(R)) motor(0,250,0,100);//011
    else if(digitalRead(L)&& !digitalRead(C) && !digitalRead(R)) right();//100
    else if(digitalRead(L)&& digitalRead(C) && !digitalRead(R))  motor(0,100,0,250);//110
    else if(digitalRead(L)&& digitalRead(C) && digitalRead(R)){//교차로
      forward();
      delay(200);
      i+=1;
      if(!digitalRead(L)&& !digitalRead(C) && !digitalRead(R)) forward();//000
    } 
  }
  else if(j==2){
    if(digitalRead(L)&& digitalRead(C) && digitalRead(R)) forward();//111
    else if(digitalRead(L)&& digitalRead(C) && !digitalRead(R)) motor(0,100,0,250);//right();//110
    else if(digitalRead(L)&& !digitalRead(C) && !digitalRead(R)) right();//100
    else if(!digitalRead(L)&& !digitalRead(C) && !digitalRead(R)){
      motor(0,250,0,50);
      delay(2200);
      forward();
      delay(300);
      level =3;
    }
  }
  else if(j==3 && v==0){
    if(digitalRead(L)&& digitalRead(C) && digitalRead(R)) forward();//111
    else if(!digitalRead(L) || !digitalRead(C) || !digitalRead(R)){
    p_right();
    delay(1550);
    }
  }
}
void loop() {

 forward();
  delay(1800);
  p_right();
  delay(1550);//180도회전
  stop();
}//loop

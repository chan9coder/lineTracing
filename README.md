
# 🤖 Autonomous Line-Tracing & Combat Robot

## 📌 Project Summary

라인트레이싱 기반 자율주행 로봇을 설계 및 제작하고, 경기 환경에서 장애물 회피 및 상대 로봇 대응 전략을 구현한 프로젝트입니다.

하드웨어 설계부터 회로 구성, 임베디드 프로그래밍까지 전 과정을 수행하며 **실제 환경에서의 문제 해결 능력**을 향상시켰습니다.

---

## 🧑‍💻 My Role

* 로봇 시스템 전체 설계 및 통합
* Arduino 기반 제어 로직 구현
* 센서 데이터 기반 주행 알고리즘 설계
* 테스트 및 문제 원인 분석, 개선 반복

---

## ⚙️ Tech Stack

* **Hardware**: Arduino Mega2560, DC Motor, L298N Driver
* **Sensors**: Line Tracking Sensor, Ultrasonic Sensor (HC-SR04)
* **Software**: Arduino IDE (C/C++)
* **Design**: 2D/3D 설계 (아크릴 가공 기반 구조 설계)

---

## 🧠 Key Features

### 1. Line Tracing System

* 적외선 센서를 활용한 라인 인식
* 교차점 카운팅 기반 경로 제어
* 안정적인 주행을 위한 센서 위치 최적화

### 2. Obstacle Avoidance

* 초음파 센서를 활용한 장애물 감지
* 감지 시 회피 경로 자동 생성

### 3. Combat Strategy (Final Round)

* 상대 로봇 감지 시 전진 및 밀어내기
* 경기장 이탈 방지를 위한 색상 감지 기반 방향 전환

---

## 🏗️ System Architecture

```
Sensor Input → Arduino → Motor Driver → Motor Control
```

* 센서 데이터를 기반으로 실시간 의사결정 수행
* 모듈 단위 설계로 유지보수 및 디버깅 효율 향상

---

## 🚧 Challenges & Solutions

### ⚠️ 1. 실제 환경에서의 주행 불안정

* **문제**: 시뮬레이션과 달리 마찰, 경사, 라인 인식 오류 발생
* **해결**:

  * 센서 높이 및 위치 재설계
  * 바퀴 간 거리 및 무게 중심 조정

---

### ⚠️ 2. 센서 오작동 (초음파 인식 실패)

* **문제**: 경기 중 객체 인식 실패로 전략 수행 불가
* **해결**:

  * 센서 보호를 위한 내부 배치 설계
  * 노이즈 최소화를 위한 배선 정리

---

### ⚠️ 3. 복잡한 배선 구조

* **문제**: 유지보수 어려움 및 디버깅 시간 증가
* **해결**:

  * I/O Map 설계 및 라벨링 적용
  * 배선 정리 및 구조 개선

---

## 📊 Result

* 라인트레이싱 및 자율주행 기능 구현 완료
* 실제 경기 환경 테스트 및 개선 반복 경험 확보
* 센서 기반 로봇 제어 시스템 전체 구현 경험

👉 단순 구현을 넘어 **문제 발생 → 원인 분석 → 설계 개선**의 반복 경험 확보

---

## 💡 What I Learned

* 하드웨어 + 소프트웨어 통합 설계 역량
* 센서 기반 실시간 제어 시스템 이해
* 실제 환경에서의 변수 대응 능력
* 팀 프로젝트에서의 협업 및 커뮤니케이션 중요성

---

## 📷 Demo / Images

(여기에 로봇 사진 or 영상 넣으면 완성도 확 올라감)
# Video
https://www.youtube.com/watch?v=Iflqe6Bg7Ws
---

## 📁 Repository Structure

```bash
├── code/        # Arduino source code
├── circuit/     # Circuit diagrams
├── design/      # Mechanical design files
├── images/      # Project images
└── README.md
```

---

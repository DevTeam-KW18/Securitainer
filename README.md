# Securitainer
IoT와 블록체인을 활용한 컨테이너의 지능화 구현

<br>

```
📌 기존 컨테이너에 내부 장비를 부착하여 지능화 기능을 구현

📌 블록체인 기술을 이용한 보안강화

📌 실시간 모니터링을 통한 컨테이너 정보 확인 및 위치 추적

📌 DB, 전상망 정보 기록을 통해 정보 접근성이 높아짐
```

<br>

### 🎞실행 동영상

* https://www.youtube.com/watch?v=9gsWZcCO_Ps

<br>

### 💫 Main Function
#### SW

- **컨테이너 정보 조회 웹**
  - 컨테이너 정보 조회 웹을 이용하여 데이터 조회가 가능하도록 설계
  - 해당 컨테이너 정보, 알람, 컨테이너의 현재 온습도, 위치 등을 제공
  
- **블록체인**
  - 데이터를 블록체인 기술을 이용하여 저장함으로써 신뢰도를 높임
  - mySQL DB에 저장되는 data를 블록체인의 블록으로 구현함으로써 기존 DB를 블록체인화
  - putty를 이용하여 프로젝트에 사용되는 서버인 Oracle EC2에 접근하여 ethereum을 이용하여 블록체인을 구현
  
- **컨테이너 내부 통신**
  - 컨테이너 내부가 서로 통신하여 온습도에 따라 저전력 냉방기를 가동함으로써 내부 온습도를 일정하게 조정
  - 컨테이너 안의 물품에 따라 따로 조정이 가능

- **컨테이너 정보 전송**
  - 아두이노와 와이파이 쉴드를 결합하여 wifi를 이용해 아두이노와 서버가 통신하고, php를 통해 서버와 블록체인이 연동 
  - 아두이노에서 입력된 온습도 값이 서버에 전달되면 서버는 해당 값을 블록체인에 저장하여 관리

#### HW

- **상태 감지 및 제어**
  - 컨테이너 내부의 온도, 습도, CO2를 감지
  - 온습도나 CO2의 값이 조정할 필요가 있다고 판단되면, 저전력 냉방기를 가동시켜 내부 상태를 조정

<br>

### 🔨 Architecture

#### SW
<img width="515" alt="1" src="https://user-images.githubusercontent.com/55692557/98470981-83cba980-222c-11eb-8540-dc360c1b1e72.png">

#### HW
<img width="746" alt="2" src="https://user-images.githubusercontent.com/55692557/98470982-85956d00-222c-11eb-846e-7216c5d0ed80.png">

<br>


### 💻Server

* AWS EC2 - 클라우드 컴퓨팅 시스템

<br>


### 👭 Members
| 김영은 | 김현아 | 문지은 | 이화경 |

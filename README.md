# 🍎 사과게임 (FruitGame)

## 🙍‍♂️ 팀 정보
SCSA 24기 C/C++ 프로젝트 2조  
조완진, 김혜민

---

## 🎯 프로젝트 목표
웹에 구현된 [사과게임(Fruit Box)](https://www.gamesaien.com/game/fruit_box_a/)을
로컬 C++ 기반 GUI 응용프로그램으로 재구현합니다.

---

## ⚙️ 기능 목록
| 번호 | 기능 설명 |
|------|-----------|
| 1 | 게임 시작 버튼으로 게임 실행 |
| 2 | 마우스 드래그 GUI로 영역 직사각형 표시 |
| 3 | 60초 제한 타이머 |
| 4 | 사과에 적힌 수의 합이 10이면 사과 제거 & 점수 증가 |
| 5 | 최종 점수 출력 |
| 6 | (추가기능) 1/3 비율로 등장하는 보라색 과일로만 10을 만들면 점수 2배|
| 7 | (추가기능) 배경음악 삽입 |

---

## 📅 일정 계획
| Day | 내용 |
|-----|------|
| Day 1 | 프로젝트 계획서 작성, 개발 환경 결정, SFML 설치 및 설정 |
| Day 2 | 백/프론트 연결용 헤더파일 작성, 역할 분담 및 기능 구현 |
| Day 3 | 백/프론트 통합 연결, 발표 자료 준비 |

---

## 💻 개발 환경

| 항목 | 내용 |
|------|------|
| 언어 | C++17 |
| IDE | VS Code |
| OS | Windows 10 |
| GUI 프레임워크 | SFML (Graphics, Audio) |

---

## 🧩 구현 주요 흐름 (코드 기반 설명)
- `Fruit` 클래스: 과일 타입, 숫자, 도형(`CircleShape`) 포함
- `fill_board`: 랜덤으로 보드 배치
- `fruit_pop`: 선택된 영역 합산이 10이면 제거, 점수 계산
- `main`: SFML 창 관리, 게임 상태, 버튼, 타이머, 배경음악 재생

배경음악(`apple_bgm.wav`)은 반복 재생되며, 폰트(`Roboto-VariableFont_wdth,wght.ttf`)가 없으면 즉시 종료됩니다.

---
## 🌟 프로젝트 장점

✅ **직관적인 GUI 조작**  
- 마우스 드래그로 영역 선택, 실시간 시각화로 범위 확인 용이

✅ **실시간 점수 & 타이머**  
- 남은 시간과 점수를 실시간 표시해 몰입감 유지

✅ **안정적인 구조와 흐름**  
- 과일(Fruit) 클래스로 관리해 유지보수 용이  
- SFML 도형/폰트/오디오 연동으로 그래픽과 사운드 결합

✅ **몰입도 있는 환경 제공**  
- BGM 반복 재생, 선택 시 색상 변화로 게임 완성도 향상

---

## 🗂️ 권장 폴더 구조
```
프로젝트/
 ├── main.cpp
 ├── FruitGame.exe (빌드 후)
 ├── Roboto-VariableFont_wdth,wght.ttf
 ├── apple_bgm.wav
 ├── drum.wav
 ├── game_over.wav
 ├── tap.wav
 ├── SFML-3.0.0/
 │   ├── include/
 │   ├── lib/
 │   ├── bin/ (DLL 파일)
```

✅ `폰트`와 `음악 파일`은 반드시 실행파일과 같은 폴더에 있어야 합니다.  
✅ `SFML/bin`의 DLL 파일도 `.exe`와 같은 폴더에 복사해야 합니다.

---

## ⚡ 빌드 방법 (PowerShell)
```powershell
g++ main.cpp -o FruitGame.exe ^
  -I./SFML-3.0.0/include ^
  -L./SFML-3.0.0/lib ^
  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

DLL 복사:
```powershell
Copy-Item .\SFML-3.0.0\bin\*.dll .\
```

---

## 🚀 실행 방법
```powershell
.\FruitGame.exe
```

---

## ✅ 실행 팁
- 콘솔로 실행해 에러 메시지를 확인하세요.
- 폰트, 음악 파일, DLL이 없으면 실행되지 않습니다.
- `std::cout`로 디버그 메시지를 추가하면 로직을 쉽게 추적할 수 있습니다.

---

## 📊 기대 효과
- C/C++ 자료구조 실습 (클래스 등)
- GUI 프레임워크 연동 연습
- 빌드 및 디버깅 경험

---

## 📎 참고 자료
- [Fruit Box 원작 게임](https://www.gamesaien.com/game/fruit_box_a/)
- [나무위키 - 프루츠박스](https://namu.wiki/w/%E3%83%95%E3%83%AB%E3%83%BC%E3%83%84%E3%83%9C%E3%83%83%E3%82%AF%E3%82%B9)

---

## 🔧 기술 스택
<p align="left">
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/cplusplus/cplusplus-original.svg" width="50"/>
  <img src="https://www.sfml-dev.org/download/goodies/sfml-icon-mini.png" width="50"/>
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/vscode/vscode-original.svg" width="50"/>
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/windows8/windows8-original.svg" width="50"/>
</p>

**C++17**, **SFML 3.0**, **VS Code**, **Windows 10**, **MinGW**

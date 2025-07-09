# 🍎 사과게임 (Fruit Box Clone)

## 📌 프로젝트 개요
- 일본 웹 게임 [Fruit Box](https://www.gamesaien.com/game/fruit_box_a/)을 로컬 **C++** 기반 GUI 프로그램으로 구현한 프로젝트입니다.  
- **SCSA 24기 C/C++ 프로젝트 2조**의 실습 과제로, SFML 프레임워크를 사용하여 그래픽과 인터랙션을 구현했습니다.

---

## 🎯 주요 기능
| 번호 | 기능 설명 |
|------|-----------|
| 1 | 게임 시작/종료 버튼으로 플레이 상태 관리 |
| 2 | 마우스 드래그로 사각형 영역 선택 가능 |
| 3 | 타이머(60초 제한) |
| 4 | 숫자의 합이 10이 되면 사과 제거 & 점수 증가 |
| 5 | 최종 점수 출력 및 다시 시작 가능 |

---

## 🧩 주요 구현 요소
- **언어/환경** : C++17, Windows 10, VS Code
- **프레임워크** : SFML 3.0 (Graphics, Window, Audio 모듈 사용)
- **자료구조** : `Fruit` 클래스, 2차원 벡터 기반 보드 구성
- **입력 처리** : SFML의 `Mouse` 이벤트와 `RectangleShape`로 영역 선택 구현
- **점수 로직** : 선택된 영역 내 숫자 합산 → 합이 10이면 제거 및 점수 계산

---

## 🖥️ 실행 방법
1. **환경 구축**
   - [SFML 3.0](https://www.sfml-dev.org/) 설치
   - `Roboto-VariableFont_wdth,wght.ttf` 폰트를 실행 파일과 같은 경로에 배치

2. **빌드 & 실행**
   ```bash
   g++ main.cpp -o FruitGame -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
   ./FruitGame
   ```

3. **게임 방법**
   - `START` 버튼 클릭 → 타이머 시작
   - 마우스로 사과 영역 드래그하여 숫자의 합이 10이 되도록 선택
   - 제한 시간 내 최대 점수를 획득하세요!

---

## 🗓️ 개발 일정
| Day | 내용 |
|-----|------|
| 1일차 | 프로젝트 계획서 작성, SFML 설치 |
| 2일차 | GUI/로직 분리 및 클래스 구조 설계 |
| 3일차 | 완성 후 발표 자료 준비 |

---

## ✅ 기대 효과
- C++ 자료구조 및 클래스 활용 연습
- SFML로 GUI/이벤트 처리 실습
- 빌드/디버깅을 통한 프로젝트 완성 경험

---

## 📎 참고 자료
- [Fruit Box 원작 게임](https://www.gamesaien.com/game/fruit_box_a/)
- [나무위키 참고](https://namu.wiki/w/%E3%83%95%E3%83%AB%E3%83%BC%E3%83%84%E3%83%9C%E3%83%83%E3%82%AF%E3%82%B9)
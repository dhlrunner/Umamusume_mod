# Umamusume_mod

**리팩터링 중**

## WIP
[umamusume-localify-develop](https://github.com/dhlrunner/umamusume-localify-develop)의 코드 개선 및 구조 변경 중입니다.

## 적용법
1. 명령 프롬프트 검색 -> 관리자 권한 실행
2. `reg add "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options" /v DevOverrideEnable /t REG_DWORD /d 1`  복붙후 엔터
3. 컴퓨터 재부팅
4. 말딸 프로그램 (umamusume.exe) 있는 폴더 안에 umamusume.exe.local 폴더 생성
5. 릴리즈 파일을 다운로드 후 압축 풀어서 방금 만든 폴더안에 전부 넣음 (apphelp.dll, config.json)
6. DMM 실행후 말딸 켜기
7. 알수없는 영어들이 지나가는 콘솔창이 뜨면 성공.

## 원상복귀
1. 명령 프롬프트 검색 -> 관리자 권한 실행
2. `reg delete "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options" /v DevOverrideEnable /f` 복붙후 엔터
3. 컴퓨터 재부팅
4. 위에서 만든 umamusume.exe.local 폴더 제거

# 주의
- 이미 다른 모드(한글패치 등)가 적용된 경우는 명령 프롬프트 실행, 재부팅 단계, 원상복귀 단계를 건너뛰어도 됨
- 이미 다른 모드를 적용했다면 원래 있던 umamusume.exe.local 폴더를 어딘가 백업해두고 빈 상태로 만든 뒤에 적용할것
- DMM에서 실행이 안될때는 DMM 플레이어를 종료 후 재실행 후 말딸 다시 실행

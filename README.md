# Assignment04

C++ Pawn 클래스 및 컴포넌트 구성
- Pawn 클래스 생성
- 컴포넌트 추가 (CapsuleComponent, SkeletalMeshComponent, SpringArmComponent, CameraComponent)
- 계층 구조 설정 (충돌 컴포넌트를 RootComponent로 설정, 나머지 컴포넌트 부착)
- DefaultPawn 설정
- Physics 설정

Enhanced Input 매핑 & 바인딩
- 입력 액션(IA) 생성 (IA_Move, IA_Look)
- IMC 매핑
- 액션 바인딩

이동 및 회전 로직 구현
- 프레임 독립성 (DeltaTime을 사용)
- 이동 구현 (WASD 입력에 따라 Pawn이 움직이도록 작성)
- 회전 구현 (Yaw와 Pitch 직접 계산하여 구현)
- 평면 상에서의 이동과 회전만 처리. 중력이나 낙하 효과는 고려하지 않는다.

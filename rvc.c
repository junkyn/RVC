#include <stdio.h>
#include <Windows.h>
#include <process.h>
#define TEST // For Test

int Obstacle[3] = { 0,0,0 }; // {왼쪽, 오른쪽, 앞쪽} 0이 장애물 x, 1이 장애물 o
int Motor[2] = { 0,0 }; // {왼쪽, 오른쪽} 0이 전방, 1이 후방
int Dust = 0;
int tick = 88; // 5tick 후 45도 회전
int MoveForward = 0;
int MoveBackward = 0;
int CleanerCommand = 1; // 0 : off 1 : on 2 : powerup

unsigned _stdcall Sensor(void* arg);
unsigned _stdcall DustSensor(void* arg);
unsigned _stdcall MotorControl(void* arg);
unsigned _stdcall CleanerControl(void* arg);
int isDust();
int LeftSensor();
int RightSensor();
int FrontSensor();
int* TurnLeft();
int* TurnRight();
int* SetMotor(int L, int R);
int SetCleaner(int Level);
int LeftMotorControl(int dir);
int RightMotorControl(int dir);


#ifdef TEST
void SetObstacleForTest(int l, int f, int r);
void SetDustForTest(int dust);

int TestObstacle[3] = { 0,0,0 }; // Left Front Right
int TestDust = 0;
int TestMotor[2] = { 0,0 };
int TestCleaner = 0;
#endif
int main() {
	_beginthreadex(NULL, 0, Sensor, 0, 0, NULL);
	_beginthreadex(NULL, 0, DustSensor, 0, 0, NULL);
	_beginthreadex(NULL, 0, MotorControl, 0, 0, NULL);
	_beginthreadex(NULL, 0, CleanerControl, 0, 0, NULL);
	while (1) {
		if (MoveBackward) {
			if (Obstacle[0] && Obstacle[1]) MoveBackward = 1;
			else if (!Obstacle[0]) {
				MoveBackward = 0;
				do {
					TurnLeft();
				} while (Obstacle[2]);
			}
			else if (Obstacle[0] && !Obstacle[1]) {
				MoveBackward = 0;
				do {
					TurnRight();
				} while (Obstacle[2]);
			}
		}
		else {
			if (!Obstacle[2]) {
				MoveForward = 1;
				if (Dust) CleanerCommand = 2;
				else CleanerCommand = 1;
			}
			else if (Obstacle[2] && !Obstacle[0]) {
				MoveForward = 0;
				CleanerCommand = 0;
				TurnLeft();
			}
			else if (Obstacle[0] && !Obstacle[1] && Obstacle[2]) {
				MoveForward = 0;
				CleanerCommand = 0;
				TurnRight();
			}
			else if (Obstacle[0] && Obstacle[1] && Obstacle[2]) {
				MoveForward = 0;
				CleanerCommand = 0;
				MoveBackward = 1;
			}
		}
		printf("%d", TestCleaner);


	}
}



unsigned _stdcall Sensor(void* arg) {
	int SensorResult[3] = { 0,0,0 };
	while (1) {
		SensorResult[0] = LeftSensor();
		SensorResult[1] = RightSensor();
		SensorResult[2] = FrontSensor();
		for (int i = 0; i < 3; i++) {
			Obstacle[i] = SensorResult[i];
		}
	}
}
unsigned _stdcall DustSensor(void* arg) {
	while (1) {
		Dust = isDust();
	}
}
unsigned _stdcall MotorControl(void* arg) {
	// 두 모터의 속력은 항상 같다.
	while (1) {
		if (MoveForward) SetMotor(0, 0);
		else if (MoveBackward) SetMotor(1, 1);
		else SetMotor(Motor[0], Motor[1]);
	}
}
unsigned _stdcall CleanerControl(void* arg) {
	while (1) {
		if (CleanerCommand == 0) SetCleaner(0);
		else if (CleanerCommand == 1) SetCleaner(1);
		else if (CleanerCommand == 2) SetCleaner(2);
	}
}
int SetCleaner(int Level) {
	//Level이 0이면 흡입 중단, 1이면 흡입력 중간으로 흡입, 2이면 흡입력 강하게 흡입
	switch (Level) {
	case 0:
		//off
#ifdef TEST
		TestCleaner = 0;
#endif
		return 0;
	case 1:
		//on
#ifdef TEST
		TestCleaner = 1;
#endif
		return 1;
	case 2:
		//power up
#ifdef TEST
		TestCleaner = 2;
#endif
		return 2;
	default:
		//ERROR
#ifdef TEST
		TestCleaner = -1;
#endif
		return -1;
	}
}
int* SetMotor(int L, int R) {
	int MotorState[2] = {LeftMotorControl(L),RightMotorControl(R) };
	return MotorState;
}
int LeftMotorControl(int dir) {
	//왼쪽 모터를 dir이 0이면 전진, dir이 1이면 후진
	switch (dir) {
	case 0:
		//Forward
#ifdef TEST
		TestMotor[0] = 0;
#endif
		return 0;
	case 1:
		//Backward
#ifdef TEST
		TestMotor[0] = 1;
#endif
		return 1;
	default:
		//ERROR
#ifdef TEST
		TestMotor[0] = -1;
#endif
		return -1;
	}
}
int RightMotorControl(int dir) {
	//오른쪽 모터를 dir이 0이면 전진, dir이 1이면 후진
	switch (dir) {
	case 0:
		//Forward
#ifdef TEST
		TestMotor[1] = 0;
#endif
		return 0;
	case 1:
		//Backward
#ifdef TEST
		TestMotor[1] = 1;
#endif
		return 1;
	default:
		//ERROR
#ifdef TEST
		TestMotor[1] = -1;
#endif
		return -1;
	}
}
int LeftSensor() {
	//RVC의 왼쪽에 달려있는 센서가 장애물을 감지하면 1을 return, 감지하지 못하면 0을 return
#ifdef TEST
	if (TestObstacle[0] == 0) {
		return 0;
	}
	else if (TestObstacle[0] == 1) {
		return 1;
	}
	else 
	{
		return -1;
	}
#else
	return -1; // 센서가 아직 할당되지 않았으니 -1 리턴
#endif
}
int RightSensor() {
	//RVC의 오른쪽에 달려있는 센서가 장애물을 감지하면 1을 return, 감지하지 못하면 0을 return
#ifdef TEST
	if (TestObstacle[2] == 0) {
		return 0;
	}
	else if (TestObstacle[2] == 1) {
		return 1;
	}
	else {
		return -1;
	}
#else
	return -1; // 센서가 아직 할당되지 않았으니 -1 리턴
#endif

}
int FrontSensor() {
	//RVC의 앞쪽에 달려있는 센서가 장애물을 감지하면 1을 return, 감지하지 못하면 0을 return
#ifdef TEST
	if (TestObstacle[1] == 0) {
		return 0;
	}
	else if (TestObstacle[1] == 1) {
		return 1;
	}
	else {
		return -1;
	}
#else
	return -1; // 센서가 아직 할당되지 않았으니 -1 리턴
#endif

}
int isDust() {
	//RVC의 먼지 감지 센서가 먼지를 감지하면 1을 return, 감지하지 못하면 0을 return
#ifdef TEST
	if (TestDust == 0) {
		return 0;
	}
	else if (TestDust == 1) {
		return 1;
	}
	else {
		return -1;
	}
#else
	return -1; // 센서가 아직 할당되지 않았으니 -1 리턴
#endif
}
int* TurnLeft() {
	for (int i = 0; i < 5; i++) {
		Motor[0] = 1; Motor[1] = 0;
		Sleep(tick);
	}
	int MotorState[2] = { Motor[0],Motor[1] };
	return MotorState;
}
int* TurnRight() {
	for (int i = 0; i < 5; i++) {
		Motor[0] = 0; Motor[1] = 1;
		Sleep(tick);
	}
	int MotorState[2] = { Motor[0],Motor[1] };
	return MotorState;
}
#ifdef TEST
void SetObstacleForTest(int l, int f, int r) { // 테스트용 장애물 설정
	TestObstacle[0] = l;
	TestObstacle[1] = f;
	TestObstacle[2] = r;
}
void SetDustForTest(int dust) { // 테스트용 먼지 설정
	TestDust = dust;
}

#endif

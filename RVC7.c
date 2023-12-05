#include <stdio.h>
#include <Windows.h>
#include <process.h>

unsigned _stdcall Sensor(void* arg);
unsigned _stdcall DustSensor(void* arg);
unsigned _stdcall MotorControl(void* arg);
unsigned _stdcall CleanerControl(void* arg);
int isDust();
void TurnLeft();
void TurnRight();
void SetMotor(int L, int R);
void SetCleaner(int Level);
void LeftMotorControl(int dir);
void RightMotorControl(int dir);

int Obstacle[3] = {0,0,0}; // {왼쪽, 오른쪽, 앞쪽} 0이 장애물 x, 1이 장애물 o
int Motor[2] = {0,0}; // {왼쪽, 오른쪽} 0이 전방, 1이 후방
int Dust = 0;
int tick = 88; // 5tick 후 45도 회전
int MoveForward = 0;
int MoveBackward = 0;
int CleanerCommand = 0; // 0 : off 1 : on 2 : powerup
int main(){
	_beginthreadex(NULL,0,Sensor,0,0,NULL);
	_beginthreadex(NULL,0,DustSensor,0,0,NULL);
	_beginthreadex(NULL,0,MotorControl,0,0,NULL);
	_beginthreadex(NULL,0,CleanerControl,0,0,NULL);
	while(1){
		if(MoveBackward){
			CtrlMoveBackward();
		}	
		else{
			CtrlMoveNotBackward();
		}
		Sleep(10);
	}
}



unsigned _stdcall Sensor(void* arg){
	int SensorResult[3]={0,0,0};
	while(1){
		SensorResult[0] = LeftSensor();
		SensorResult[1] = RightSensor();
		SensorResult[2] = FrontSensor();
		for(int i = 0; i<3; i++){
			Obstacle[i] = SensorResult[i];
		}
		Sleep(10);
	}
}
unsigned _stdcall DustSensor(void* arg){
	while(1){
		Dust = isDust();
		Sleep(10);
	}
}
unsigned _stdcall MotorControl(void* arg){
	// 두 모터의 속력은 항상 같다.
	while(1){
		if(MoveForward) SetMotor(0,0);
		else if(MoveBackward) SetMotor(1,1);
		else SetMotor(Motor[0],Motor[1]);
		Sleep(10);
	}
}
unsigned _stdcall CleanerControl(void* arg){
	while(1){
		if(CleanerCommand == 0) SetCleaner(0);
		else if(CleanerCommand == 1) SetCleaner(1);
		else if(CleanerCommand == 2) SetCleaner(2);
		Sleep(10);
	}
}
void CtrlMoveBackward(){
		if(Obstacle[0] && Obstacle[1]) MoveBackward = 1;
		else if(!Obstacle[0]){
			MoveBackward = 0;
			do{
				TurnLeft();
			}while(Obstacle[2]);
		}else if(Obstacle[0] && !Obstacle[1]){
			MoveBackward = 0;
			do{
				TurnRight();
			}while(Obstacle[2]);
		}
}
void CtrlMoveNotBackward(){
		if(!Obstacle[2]) {
			MoveForward = 1;
			if(Dust) CleanerCommand = 2;
			else CleanerCommand = 1;
		}
		else if(Obstacle[2] && !Obstacle[0]){
			MoveForward = 0;
			CleanerCommand = 0;
			TurnLeft();
		}else if(Obstacle[0] && !Obstacle[1] && Obstacle[2]){
			MoveForward = 0;
			CleanerCommand = 0;
			TurnRight();
		}else if(Obstacle[0] && Obstacle[1] && Obstacle[2]){
			MoveForward = 0;
			CleanerCommand = 0;
			MoveBackward = 1;
		}
}
void SetCleaner(int Level){
	//Level이 0이면 흡입 중단, 1이면 흡입력 중간으로 흡입, 2이면 흡입력 강하게 흡입
}
void SetMotor(int L, int R){
	LeftMotorControl(L);
	RightMotorControl(R);
}
void LeftMotorControl(int dir){
	//왼쪽 모터를 dir이 0이면 전진, dir이 1이면 후진
}
void RightMotorControl(int dir){
	//오른쪽 모터를 dir이 0이면 전진, dir이 1이면 후진
}
int LeftSensor(){
	//RVC의 왼쪽에 달려있는 센서가 장애물을 감지하면 1을 return, 감지하지 못하면 0을 return, 오류 시 -1을 return
	return -1;
}
int RightSensor(){
	//RVC의 오른쪽에 달려있는 센서가 장애물을 감지하면 1을 return, 감지하지 못하면 0을 return, 오류 시 -1을 return
	return -1;
}
int FrontSensor(){
	//RVC의 앞쪽에 달려있는 센서가 장애물을 감지하면 1을 return, 감지하지 못하면 0을 return, 오류 시 -1을 return
	return -1;
}
int isDust(){
	//RVC의 먼지 감지 센서가 장애물을 감지하면 1을 return, 감지하지 못하면 0을 return, 오류 시 -1을 return
	return -1;
}
void TurnLeft(){
	for(int i = 0; i<5; i++){
		Motor[0] = 1; Motor[1] = 0;
		Sleep(tick);	
	}
}
void TurnRight(){
	for(int i = 0; i<5; i++){
		Motor[0] = 0; Motor[1] = 1;
		Sleep(tick);	
	}
}

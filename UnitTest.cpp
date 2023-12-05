#include "pch.h"
#include "CppUnitTest.h"
#include "../../RVCUT/RVCUT/rvc.c"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		TEST_METHOD(TestLeftSensor1) // L, F, R 장애물 X
		{

			SetObstacleForTest(0, 0, 0);
			int Expect = 0;
			Assert::AreEqual(Expect, LeftSensor());
		}
		TEST_METHOD(TestLeftSensor2) // L 장애물, F,R 장애물 X
		{
			SetObstacleForTest(1, 0, 0); 
			int Expect = 1;
			Assert::AreEqual(Expect, LeftSensor());
		}
		TEST_METHOD(TestLeftSensor3) // L,F 장애물, R 장애물 X 
		{
			SetObstacleForTest(1, 1, 0); 
			int Expect = 1;
			Assert::AreEqual(Expect, LeftSensor());
		}
		TEST_METHOD(TestLeftSensor4)  //F 장애물, L,R 장애물 X
		{
			SetObstacleForTest(0, 1, 0); 
			int Expect = 0;
			Assert::AreEqual(Expect, LeftSensor());
		}
		TEST_METHOD(TestLeftSensor5)  //F,R 장애물, L 장애물 X
		{
			SetObstacleForTest(0, 1, 1);
			int Expect = 0;
			Assert::AreEqual(Expect, LeftSensor());
		}
		TEST_METHOD(TestLeftSensor6)  // R 장애물, L,R 장애물 X
		{
			SetObstacleForTest(0, 0, 1);
			int Expect = 0;
			Assert::AreEqual(Expect, LeftSensor());
		}
		TEST_METHOD(TestLeftSensor7)  // L,R 장애물, F 장애물 X
		{
			SetObstacleForTest(1, 0, 1);
			int Expect = 1;
			Assert::AreEqual(Expect, LeftSensor());
		}
		TEST_METHOD(TestLeftSensor8)  // L,F,R 장애물
		{
			SetObstacleForTest(1, 1, 1);
			int Expect = 1;
			Assert::AreEqual(Expect, LeftSensor());
		}
		TEST_METHOD(TestRightSensor1) // L, F, R 장애물 X
		{
			SetObstacleForTest(0, 0, 0);
			int Expect = 0;
			Assert::AreEqual(Expect, RightSensor());
		}
		TEST_METHOD(TestRightSensor2) // L 장애물, F,R 장애물 X
		{
			SetObstacleForTest(1, 0, 0);
			int Expect = 0;
			Assert::AreEqual(Expect, RightSensor());
		}
		TEST_METHOD(TestRightSensor3) // L,F 장애물, R 장애물 X 
		{
			SetObstacleForTest(1, 1, 0);
			int Expect = 0;
			Assert::AreEqual(Expect, RightSensor());
		}
		TEST_METHOD(TestRightSensor4)  //F 장애물, L,R 장애물 X
		{
			SetObstacleForTest(0, 1, 0);
			int Expect = 0;
			Assert::AreEqual(Expect, RightSensor());
		}
		TEST_METHOD(TestRightSensor5)  //F,R 장애물, L 장애물 X
		{
			SetObstacleForTest(0, 1, 1);
			int Expect = 1;
			Assert::AreEqual(Expect, RightSensor());
		}
		TEST_METHOD(TestRightSensor6)  // R 장애물, L,R 장애물 X
		{
			SetObstacleForTest(0, 0, 1);
			int Expect = 1;
			Assert::AreEqual(Expect, RightSensor());
		}
		TEST_METHOD(TestRightSensor7)  // L,R 장애물, F 장애물 X
		{
			SetObstacleForTest(1, 0, 1);
			int Expect = 1;
			Assert::AreEqual(Expect, RightSensor());
		}
		TEST_METHOD(TestRightSensor8)  // L,F,R 장애물
		{
			SetObstacleForTest(1, 1, 1);
			int Expect = 1;
			Assert::AreEqual(Expect, RightSensor());
		}
		TEST_METHOD(TestFrontSensor1) // L, F, R 장애물 X
		{
			SetObstacleForTest(0, 0, 0);
			int Expect = 0;
			Assert::AreEqual(Expect, FrontSensor());
		}
		TEST_METHOD(TestFrontSensor2) // L 장애물, F,R 장애물 X
		{
			SetObstacleForTest(1, 0, 0);
			int Expect = 0;
			Assert::AreEqual(Expect, FrontSensor());
		}
		TEST_METHOD(TestFrontSensor3) // L,F 장애물, R 장애물 X 
		{
			SetObstacleForTest(1, 1, 0);
			int Expect = 1;
			Assert::AreEqual(Expect, FrontSensor());
		}
		TEST_METHOD(TestFrontSensor4)  //F 장애물, L,R 장애물 X
		{
			SetObstacleForTest(0, 1, 0);
			int Expect = 1;
			Assert::AreEqual(Expect, FrontSensor());
		}
		TEST_METHOD(TestFrontSensor5)  //F,R 장애물, L 장애물 X
		{
			SetObstacleForTest(0, 1, 1);
			int Expect = 1;
			Assert::AreEqual(Expect, FrontSensor());
		}
		TEST_METHOD(TestFrontSensor6)  // R 장애물, L,R 장애물 X
		{
			SetObstacleForTest(0, 0, 1);
			int Expect = 0;
			Assert::AreEqual(Expect, FrontSensor());
		}
		TEST_METHOD(TestFrontSensor7)  // L,R 장애물, F 장애물 X
		{
			SetObstacleForTest(1, 0, 1);
			int Expect = 0;
			Assert::AreEqual(Expect, FrontSensor());
		}
		TEST_METHOD(TestFrontSensor8)  // L,F,R 장애물
		{
			SetObstacleForTest(1, 1, 1);
			int Expect = 1;
			Assert::AreEqual(Expect,FrontSensor());
		}
		TEST_METHOD(TestLeftMotor1) // 우회전 시 좌측 모터
		{
			// 우회전
			int LDir = 0;
			int RDir = 1;
			int Expect = 0;
			Assert::AreEqual(Expect, SetMotor(LDir, RDir)[0]);
		}
		TEST_METHOD(TestLeftMotor2) // 좌회전 시 좌측 모터
		{
			// 좌회전
			int LDir = 1;
			int RDir = 0;
			int Expect = 1;
			Assert::AreEqual(Expect, SetMotor(LDir, RDir)[0]);
		}
		TEST_METHOD(TestLeftMotor3) // 직진 시 좌측 모터
		{
			// 직진
			int LDir = 0;
			int RDir = 0;
			int Expect = 0;
			Assert::AreEqual(Expect, SetMotor(LDir, RDir)[0]);
		}
		TEST_METHOD(TestLeftMotor4) // 후진 시 좌측 모터
		{
			// 후진
			int LDir = 1;
			int RDir = 1;
			int Expect = 1;
			Assert::AreEqual(Expect, SetMotor(LDir, RDir)[0]);
		}
		TEST_METHOD(TestRightMotor1) // 우회전 시 우측 모터
		{
			// 우회전
			int LDir = 0;
			int RDir = 1;
			int Expect = 1;
			Assert::AreEqual(Expect, SetMotor(LDir, RDir)[1]);
		}
		TEST_METHOD(TestRightMotor2) // 좌회전 시 좌측 모터
		{
			// 좌회전
			int LDir = 1;
			int RDir = 0;
			int Expect = 0;
			Assert::AreEqual(Expect, SetMotor(LDir, RDir)[1]);
		}
		TEST_METHOD(TestRightMotor3) // 직진 시 우측 모터
		{
			// 직진
			int LDir = 0;
			int RDir = 0;
			int Expect = 0;
			Assert::AreEqual(Expect, SetMotor(LDir, RDir)[1]);
		}
		TEST_METHOD(TestRightMotor4) // 후진 시 우측 모터
		{
			// 후진
			int LDir = 1;
			int RDir = 1;
			int Expect = 1;
			Assert::AreEqual(Expect, SetMotor(LDir, RDir)[1]);
		}
		TEST_METHOD(TestDustSensor1) // 먼지 X
		{
			SetDustForTest(0);
			int Expect = 0;
			Assert::AreEqual(Expect, isDust());
		}
		TEST_METHOD(TestDustSensor2) // 먼지 O
		{
			SetDustForTest(1);
			int Expect = 1;
			Assert::AreEqual(Expect, isDust());
		}
		TEST_METHOD(TestErrorLeftSensor1) // 0과 1이 아닌 값이 들어왔을 때 좌측 센서
		{
			SetObstacleForTest(-3, 0, 0);
			int Expect = -1;
			Assert::AreEqual(Expect, LeftSensor());
		}
		TEST_METHOD(TestErrorLeftSensor2) // 0과 1이 아닌 값이 들어왔을 때 좌측 센서
		{
			SetObstacleForTest(5, 0, 0);
			int Expect = -1;
			Assert::AreEqual(Expect, LeftSensor());
		}
		TEST_METHOD(TestErrorFrontSensor1)// 0과 1이 아닌 값이 들어왔을 때 전방 센서
		{
			SetObstacleForTest(0, -4, 0);
			int Expect = -1;
			Assert::AreEqual(Expect, FrontSensor());
		}
		TEST_METHOD(TestErrorFrontSensor2)// 0과 1이 아닌 값이 들어왔을 때 전방 센서
		{
			SetObstacleForTest(0, 4, 0);
			int Expect = -1;
			Assert::AreEqual(Expect, FrontSensor());
		}
		TEST_METHOD(TestErrorRightSensor1)// 0과 1이 아닌 값이 들어왔을 때 우측 센서
		{
			SetObstacleForTest(0, 0, -3);
			int Expect = -1;
			Assert::AreEqual(Expect, RightSensor());
		}
		TEST_METHOD(TestErrorRightSensor2)// 0과 1이 아닌 값이 들어왔을 때 우측 센서
		{
			SetObstacleForTest(0, 0, 6);
			int Expect = -1;
			Assert::AreEqual(Expect, RightSensor());
		}
		TEST_METHOD(TestErrorDustSensor1)// 0과 1이 아닌 값이 들어왔을 때 먼지 센서
		{
			SetDustForTest(-3);
			int Expect = -1;
			Assert::AreEqual(Expect, isDust());
		}
		TEST_METHOD(TestErrorDustSensor2)// 0과 1이 아닌 값이 들어왔을 때 먼지 센서
		{
			SetDustForTest(3);
			int Expect = -1;
			Assert::AreEqual(Expect, isDust());
		}
		TEST_METHOD(TestTurnLeft)// TurnLeft 함수 실행 시 모터 반환값
		{
			int Expect[2] = { 1,0 };
			Assert::AreEqual(Expect[0], TurnLeft()[0]);
			Assert::AreEqual(Expect[1], TurnLeft()[1]);
		}
		TEST_METHOD(TestTurnRight)// TurnRight 함수 실행 시 모터 반환값
		{
			int Expect[2] = { 0,1 };
			Assert::AreEqual(Expect[0], TurnRight()[0]);
			Assert::AreEqual(Expect[1], TurnRight()[1]);
		}
		TEST_METHOD(TestCleaner1) // Off 상태의 먼지 흡입 기능 반환값
		{
			int State = 0;
			int Expect = 0;
			Assert::AreEqual(Expect, SetCleaner(State));
		}
		TEST_METHOD(TestCleaner2) // On 상태의 먼지 흡입 기능 반환값
		{
			int State = 1;
			int Expect = 1;
			Assert::AreEqual(Expect, SetCleaner(State));
		}
		TEST_METHOD(TestCleaner3) // Power Up 상태의 먼지 흡입 기능 반환값
		{
			int State = 2;
			int Expect = 2;
			Assert::AreEqual(Expect, SetCleaner(State));
		}
		TEST_METHOD(TestCleaner4)  // 0,1,2가 아닌 상태의 먼지 흡입 기능 반환값
		{
			int State = -2;
			int Expect = -1;
			Assert::AreEqual(Expect, SetCleaner(State));
		}
		TEST_METHOD(TestCleaner5) // 0,1,2가 아닌 상태의 먼지 흡입 기능 반환값
		{
			int State = 3;
			int Expect = -1;
			Assert::AreEqual(Expect, SetCleaner(State));
		}
	};
}

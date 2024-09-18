#include <iostream>
#include <windows.h>
#include <thread>
#include <atomic>
#include <mutex>
#include <queue>

/*
	두개의 2차원 배열순회 코드이다.
	첫번째 코드보다 두번쨰 코드가 2~3배 느리게 걸리는 것을 알 수 있다.
	이것은 CPU의 캐시와 관련된 속도 차이 이다.
	CPU에서 메모리까지 접근하여 메모리에 담겨있는 값을 가저오는 행위가 CPU가 ALU에서 연산작업을하는 것에 비해 cpu 자원(시간) 이 좋지 않다.
	그래서 CPU안에 cache메모리라는 작은 저장소에서 메모리에서 사용할 값을 미리 저장하여 사용한다.
	이 cache메모리 안에는 당연히 여러종류가 있고 피라미드 계급처럼 중요한 것 일수록 cpu와 가깝게 위치해 있다.

	이 프로그램에서는 2차원 배열을 읽어올때 메모리에는 [0][1]->[0][[2] 이렇게 다음 메모리 주소번지 가 이어서 붙어저있을 것이다.
	그래서 cache메모리에 한번 메모리에서 읽어올때 인접해서 다음에도 바로 읽어올만한 데이터를 어느정도 한꺼번에 캐시 메모리에 저장하고 빠르게 읽고 사용하는 것이 가능하다.

	캐시의 철학에는 
	1.TEMPORAL LOCALITY (시간) 방금 주문한 테이블에서 추가 주문 확률이 높음.
	2.SPATIAL LOCALITY  (공간) 방금 주문한 사람 근처에 있는 사람이 추가 주문 확률이 높음.
	에 따라 캐시메모리에서 얼만큼 무슨 데이터를  가저와서 캐시메모리에 적재해놓을지 정하게 된다.


*/

using namespace std;
using int32 = __int32;
using int64 = __int64;
using uint64 = unsigned __int64;


int32 buffer[10000][10000];

int main()
{
	memset(buffer, 0, sizeof(buffer));
	{
		uint64 start = GetTickCount64();

		int64 sum = 0;
		for (int32 i = 0; i < 10000; i++)
			for (int32 j = 0; j < 10000; j++)
				sum += buffer[i][j];

		uint64 end = GetTickCount64();
		cout << "걸린 시간 : " << (end - start) << '\n';
	}
	{
		uint64 start = GetTickCount64();

		int64 sum = 0;
		for (int32 i = 0; i < 10000; i++)
			for (int32 j = 0; j < 10000; j++)
				sum += buffer[j][i];

		uint64 end = GetTickCount64();
		cout << "걸린 시간 : " << (end - start) << '\n';
	}

}






#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;
int cache[100][100] = { 0, };

int combination(int n, int k)
{
	if (k == 0 || n == k)
		return 1;
	int& ret = cache[n][k];
	if (ret != -1)
		return ret;

	return ret = combination(n - 1, k - 1) + combination(n - 1, k);
}

int main()
{
	::memset(cache, -1, sizeof(cache));
	__int64 start = GetTickCount64();
	int lotto = combination(45, 6);
	__int64 end = GetTickCount64();
	cout << "result - " << lotto << endl;
	cout << end - start <<"ms";


}
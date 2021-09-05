#include<stdio.h>
#include<string.h>
#define Modulo 1000000
int n, cache[5005];
char arr[5005];

int getCount(int idx) {
	if (idx >= n) return 1;

	int& ret = cache[idx];
	if (ret != -1) return ret;
	ret = 0;
	if (arr[idx] >= '1')
	{
		ret = (ret + getCount(idx + 1)) % Modulo;

		if (idx + 1 < n)
		{
			if (arr[idx] == '1' || (arr[idx] == '2' && arr[idx + 1] <= '6'))
				ret = (ret + getCount(idx + 2)) % Modulo;
		}
	}

	return ret % Modulo;
}
int main() {

	scanf("%s", arr);
	n = strlen(arr);
	memset(cache, -1, sizeof(cache));
	printf("%d\n", getCount(0));

	return 0;

}
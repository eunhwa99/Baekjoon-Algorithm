
#include<stdio.h>
int strCmp(const char* str1, const char* str2) {
	int idx = 0;
	while (str1[idx] && str1[idx] == str2[idx]) idx++;

	return str2[idx] - str1[idx];

}
int n;
char str[1000001][12];
int main() {

	scanf("%d ", &n);


	for (int i = 0; i < n; ++i) {
		gets(str[i]);
	
	}
	qsort(str, n, 12, strCmp);
	
	for (int i = 0; i < n; i++)
	{
		int j = 0, k = 0;
		for (j = 0; str[i][j] != ' '; j++);
		for (k = 0; str[i + k][j + 1] == 'l'; k++);
		if (k)i += k * 2 - 1; 
		// 예를 들어, 특정 사람이 leave 했다면 
		// 그 다음 문자열은 무조건 같은 사람이 enter 한 문자열 (정렬했으므로)
		// 이므로 이 문자열을 뛰어 넘어야 한다.

		else { 
			str[i][j] = 0; // 문자열 끝
			puts(str[i]);
		}
	}
}

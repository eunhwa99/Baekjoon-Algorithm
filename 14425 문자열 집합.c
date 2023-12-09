
#include <stdio.h>

int n, m, i, num = 0, cmp, start, mid, end;
char list[10000][501], temp[501];
int strCmp(const char* str1, const char* str2) {
	int idx = 0;
	while (str1[idx] && str1[idx] == str2[idx]) idx++;

	return str1[idx] - str2[idx]; // 핵심!
}
int main(void) {
	scanf("%d %d ", &n, &m);
	for (i = 0; i < n; i++) {
		gets(list[i]);
	}

	qsort(list, n, sizeof(char) * 501, strCmp);

	for (i = 0; i < m; i++) {
		gets(temp);

		start = 0;
		end = n - 1;

		while (start <= end) {
			mid = (start + end) >> 1;
			cmp = strCmp(temp, list[mid]);


			if (!cmp) {
				num++;
				break;
			}
			else if (cmp < 0) end = mid - 1;
			else start = mid + 1;
		}
	}

	printf("%d", num);
}

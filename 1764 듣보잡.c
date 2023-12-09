#include <stdio.h>

int n, m, i, num = 0, cmp, start, mid, end;
char list1[500001][21], list2[50001][21];
int idx[500001];
int strCmp(const char* str1, const char* str2) {
	int idx = 0;
	while (str1[idx] && str1[idx] == str2[idx]) idx++;

	return str1[idx] - str2[idx]; // 핵심!
}
int main(void) {
	scanf("%d %d", &n, &m);
	for (i = 0; i < n; i++) {
		scanf("%s", list1[i]);
	}

	qsort(list1, n, sizeof(char) * 21, strCmp);

	for (i = 0; i < m; i++) {
		scanf("%s", list2[i]);
	}
	qsort(list2, m, sizeof(char) * 21, strCmp);

	for (i = 0; i < m; i++) {
		start = 0;
		end = n - 1;

		while (start <= end) {
			mid = (start + end) >> 1;
			cmp = strCmp(list2[i], list1[mid]);


			if (!cmp) {
				idx[num++] = i;
				break;
			}
			else if (cmp < 0) end = mid - 1;
			else start = mid + 1;
		}
	}

	printf("%d\n", num);
	for (int i = 0; i < num; ++i)
		puts(list2[idx[i]]);

}

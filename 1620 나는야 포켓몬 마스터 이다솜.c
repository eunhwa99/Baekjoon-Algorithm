#include <stdio.h>
struct Pocket {
	char name[21];
	int index;
}input[100001];
char tmp[100001][21];
char c[100001];
int n, m;

int strCmp(const struct Pocket* a,const struct Pocket* b) {
	int idx = 0;
	while (a->name[idx] != '\0') {
		if (a->name[idx] == b->name[idx]) ++idx;
		else break;
	}
	return a->name[idx] - b->name[idx];
}

int strCmp2(const char* a, const char* b) {
	int idx = 0;
	while (a[idx] != '\0') {
		if (a[idx] == b[idx]) ++idx;
		else break;
	}
	return a[idx] - b[idx];
}
void strCpy(char* dest, const char* src) {
	char* org = dest;

	while (*src != '\0') {
		*dest = *src;
		++dest;
		++src;
	}
	*dest = '\0'; // 문자열 마지막에 delimiter 추가!!
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i) {
		scanf("%s", input[i].name);
		strCpy(tmp[i], input[i].name);
		input[i].index = i;
	}

	qsort(input, n, sizeof(input[0]), strCmp);

	for (int i = 0; i < m; ++i) {
		int start = 0, end = n - 1, mid, cmp;
		scanf("%s", c);

		if (c[0] >= '0' && c[0] <= '9')
			printf("%s\n", tmp[atoi(c)-1]);
		else {
			while (start <= end) {
				mid = (start + end) >> 1;
				cmp = strCmp2(c, input[mid].name);


				if (!cmp) {
					printf("%d\n", input[mid].index + 1);
					break;
				}
				else if (cmp < 0) end = mid - 1;
				else start = mid + 1;
			}
		}
	}


}

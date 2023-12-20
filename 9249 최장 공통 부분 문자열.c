#include<stdio.h>
#define Max 400002

char string[Max], string2[Max>>1];
int N;

int suffixArr[Max],
ord[Max], nord[Max], cnt[Max], aux[Max],
rank[Max],
lcp[Max];


void getSuffixArr() {
	
	
	ord[N] = 0; // 공백의 그룹이 항상 젤 빠르다 !! (처음에 26으로 초기화 했다가 틀림)
	//2. 정렬
	int t = 1, gcnt = 1;
	int count = N > 27 ? N : 27; 
	while (t < N) {

		for (int i = 0; i <= count; ++i) cnt[i] = 0; 
		for (int i = 0; i < N; ++i) cnt[ord[i + t > N ? N : i + t]]++;
		for (int i = 1; i <= count; ++i) cnt[i] += cnt[i - 1];
		for (int i = N - 1; i >= 0; --i) aux[--cnt[ord[i + t > N ? N : i + t]]] = i;

		for (int i = 0; i <= count; ++i) cnt[i] = 0;
		for (int i = 0; i < N; ++i) cnt[ord[i]]++;
		for (int i = 1; i <= count; ++i) cnt[i] += cnt[i - 1];
		for (int i = N - 1; i >= 0; --i) suffixArr[--cnt[ord[aux[i]]]] = aux[i];
		
		if (gcnt == N-1) break;
		gcnt = 1;
		nord[suffixArr[0]] = gcnt;
		for (int i = 1; i < N; ++i) {
			if (ord[suffixArr[i - 1]] != ord[suffixArr[i]] || ord[suffixArr[i - 1] + t] != ord[suffixArr[i] + t]) ++gcnt;
			nord[suffixArr[i]] = gcnt;
		}

		for (int i = 0; i < N; ++i) ord[i] = nord[i];
		ord[N] = 0;
		count = N > gcnt ? N : gcnt;
		t <<= 1; 
		
	}

}

void getLCP() {
	for (int i = 0; i < N; ++i)
		rank[suffixArr[i]] = i;

	int h = 0;

	for (int i = 0; i < N; ++i) {
		if (rank[i]) {
			int prev = suffixArr[rank[i] - 1];
			while (string[prev + h] == string[i + h]) ++h;
			lcp[rank[i]] = h;

			if (h) --h;
		}

	}

	

}

void strCat(char* dest, const char* src) {
	char* org = dest;

	while (*dest != '\0') ++dest;

	while (*src != '\0') {
		*dest = *src;
		++dest;
		++src;
	}
	*dest = '\0'; // 문자열 마지막에 delimiter 추가!!
}

int main() {
	scanf("%s", string);
	
	for (N = 0; string[N]; N++)
		suffixArr[N] = N,
		ord[N] = string[N] - 'a' + 1;
	
	string[N] = 'z' + 1;
	string[N + 1] = '\0';

	int m = N;
	
	scanf("%s", string + m + 1);

	for (N; string[N]; N++) {
		suffixArr[N] = N,
		ord[N] = string[N] - 'a' + 1;
	}

	getSuffixArr();
	getLCP();

	int ans[2] = { 0,0 };
	for (int i = 2; i < N; i++) {
		if ((suffixArr[i] < m) ^ (suffixArr[i - 1] < m) && ans[0] < lcp[i])ans[0] = lcp[i], ans[1] = suffixArr[i];
	}
	printf("%d\n", ans[0]);
	for (int i = ans[1]; i < ans[1] + ans[0]; ++i)printf("%c", string[i]);
	return 0;
}

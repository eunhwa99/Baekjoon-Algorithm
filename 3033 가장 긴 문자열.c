#include<stdio.h>
#define Max 200002

char string[Max];
int N;

int suffixArr[Max],
ord[Max], nord[Max], cnt[Max], aux[Max],
rank[Max];


void getSuffixArr() {

	for (N = 0; string[N]; N++)
		suffixArr[N] = N,
		ord[N] = string[N] - 'a' + 1;
	
	ord[N] = 0; 
	int t = 1, gcnt = 1;
	int count = N > 26 ? N : 26; 
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

	int h = 0, max = 0;

	for (int i = 0; i < N; ++i) {
		if (rank[i]) {
			int prev = suffixArr[rank[i] - 1];
			while (string[prev + h] == string[i + h]) ++h;
			
			max = max < h ? h : max;

			if (h) --h;
		}

	}

	printf("%d\n", max);
}


int main() {
	scanf("%d", &N);
	scanf("%s", string);


	getSuffixArr();
	getLCP();

	

	return 0;
}

// 카운팅 소트 (716ms)

#include<stdio.h>
#define Max 500002

char string[Max];
int N;

int suffixArr[Max],
ord[Max], nord[Max], cnt[Max], aux[Max],
rank[Max],
lcp[Max];


void getSuffixArr() {
	
	for (N = 0; string[N]; N++)
		suffixArr[N] = N,
		ord[N] = string[N] - 'a' + 1;  
	ord[N] = 0; // 공백의 그룹이 항상 젤 빠르다 !! (처음에 26으로 초기화 했다가 틀림)
	//2. 정렬
	int t = 1, gcnt = 1;
	int count = N > 26 ? N : 26; // 여기 주의!! (처음에 그냥 26으로만 초기화 했다가 틀림)
	// 그룹 개수가 총 알파벳 개수보다 많아질 수 있음!
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

	for (int i = 0; i < N; ++i)
		printf("%d ", suffixArr[i]+1);
	printf("\n");
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

	printf("x ");
	for (int i = 1; i < N; ++i) {
		printf("%d ", lcp[i]);
	}

}

int main() {
	scanf("%s", string);
	getSuffixArr();
	getLCP();
	return 0;
}


// 퀵 소트: 600ms (카운팅보다 빠름) 
/*
#include<stdio.h>
#define Max 500001

char string[Max];
int N;

int suffixArr[Max],
group[Max],
newgroup[Max],
rank[Max],
lcp[Max];

int cmp(int small, int big, int t) {
	if (group[small] != group[big])
		return group[small] < group[big]; // 그룹이 다르면 그룹번호가 작은 것이 앞으로
	else // 그룹이 같으면 t번째 문자로 정렬
		return group[small + t] < group[big + t];
	// 정확히 말하면, t번째 문자로 시작하는 접미사 배열의 그룹 번호로 정렬
}

void quick(int above, int below, int t) {
	if (above >= below)
		return;

	int left = above - 1,
		right = below + 1,
		pivot = suffixArr[left + (right - left) / 2];
	while (left < right) {
		while (cmp(suffixArr[++left], pivot, t));
		while (cmp(pivot, suffixArr[--right], t));
		if (left >= right)break;
		int temp = suffixArr[left];
		suffixArr[left] = suffixArr[right];
		suffixArr[right] = temp;
	}
	quick(above, left - 1, t);
	quick(right + 1, below, t);
}

void getSuffixArr() {
	//1.초기화 , 그룹, suffixArr
	for (N = 0; string[N]; N++)
		suffixArr[N] = N,
		group[N] = string[N] - 'a'; // 문자 1개로 grouping (t=0)
	group[N] = -1; // 문자가 없는 부분 ('\0')

	//2. 정렬
	int t = 1;
	while (t < N) {
		quick(0, N - 1, t);

		// 임시 배열에 그룹 갱신
		// suffixArr의 0번째 접미사 배열의 그룹 넘버는 0으로 시작
		newgroup[suffixArr[0]] = 0;
		newgroup[N] = -1;

		for (int i = 1; i < N; i++)
			if (cmp(suffixArr[i - 1], suffixArr[i], t)) // 두 접미사 배열의 t 번째 문자 비교
				newgroup[suffixArr[i]] = newgroup[suffixArr[i - 1]] + 1;
			else // t번째 문자가 같다면 같은 그룹
				newgroup[suffixArr[i]] = newgroup[suffixArr[i - 1]];

		//3. 그룹최신화
		for (int i = 0; i < N; i++)
			group[i] = newgroup[i];
		t <<= 1; // t *=2;
	}

	for (int i = 0; i < N; ++i)
		printf("%d ", suffixArr[i]+1);
	printf("\n");
}

void getLCP() {
	for (int i = 0; i < N; ++i)
		rank[suffixArr[i]] = i;

	int h = 0;

	for (int i = 0; i < N; ++i) {
		if (rank[i]) {
			int prev = suffixArr[rank[i] - 1];
			while (string[prev + h] == string[i + h])++h;
			lcp[rank[i]] = h;

			if (h) h--;
		}

	}

	printf("x ");
	for (int i = 1; i < N; ++i) {
		printf("%d ", lcp[i]);
	}

}

int main() {
	scanf("%s", string);
	getSuffixArr();
	getLCP();
	return 0;
}


*/

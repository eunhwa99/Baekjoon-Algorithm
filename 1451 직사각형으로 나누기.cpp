#include<stdio.h>
int N, M;
int map[101][101];
int total, sum1, sum2;
long long maxV, mux;
/*
* #include <cstdio>
#include <algorithm>
using namespace std;
#pragma warning(disable:4996)
 
int arr[101][101];
long long dp[101][101];
 
int main() {
    int N, M;
    scanf("%d%d", &N, &M);
 
    for (int i = 1; i <= N; i++) {
        for (int k = 1; k <= M; k++) {
            scanf("%1d", &arr[i][k]);
        }
    }
 
    for (int i = 1; i <= N; i++)
        for (int k = 1; k <= M; k++)
            dp[i][k] = dp[i - 1][k] + dp[i][k - 1] - dp[i - 1][k - 1] + arr[i][k];
 
    long long ans = 0;
    long long f, s, t;
    
    // case:1
    for (int i = 1; i <= M - 2; i++) {
        f = dp[N][i];
        for (int k = i + 1; k <= M - 1; k++) {
            s = dp[N][k] - f;
            t = dp[N][M] - s - f;
            ans = max(ans, f * s * t);
        }
    }
 
    // case:2
    for (int i = 1; i <= N - 2; i++) {
        f = dp[i][M];
        for (int k = i + 1; k <= N - 1; k++) {
            s = dp[k][M] - f;
            t = dp[N][M] - s - f;
            ans = max(ans, f * s * t);
        }
    }
 
    // case:3
    for (int i = 1; i <= M - 1; i++) {
        f = dp[N][i];
        for (int k = 1; k <= N - 1; k++) {
            s = dp[k][M] - dp[k][i];
            t = dp[N][M] - f - s;
            ans = max(ans, f * s * t);
        }
    }
 
    // case:4
    for (int i = 1; i <= M - 1; i++) {
        for (int k = 1; k <= N - 1; k++) {
            f = dp[k][i];
            s = dp[N][i] - f;
            t = dp[N][M] - f - s;
            ans = max(ans, f * s * t);
        }
    }
 
    // case:5
    for (int i = 1; i <= N - 1; i++) {
        f = dp[i][M];
        for (int k = 1; k <= M - 1; k++) {
            s = dp[N][k] - dp[i][k];
            t = dp[N][M] - f - s;
            ans = max(ans, f * s * t);
        }
    }
 
    // case:6
    for (int i = 1; i <= N - 1; i++) {
        for (int k = 1; k <= M - 1; k++) {
            f = dp[i][k];
            s = dp[i][M] - f;
            t = dp[N][M] - f - s;
            ans = max(ans, f * s * t);
        }
    }
 
    printf("%lld", ans);
    return 0;
}
*/

void solve() {

	
	//Case 1 111
	for (int k = 1; k < M; k++) { //가장 왼쪽 사각형의 가로 길이 정해주기
		sum1 = 0;
		for (int j = 0; j < k; j++) {
			for (int i = 0; i < N; i++) {
				sum1 += map[i][j];
			}		
		}

		
		for (int l = 1; k+l < M; l++) { //중간 사각형의 가로 길이 정해주기
			mux = sum1;
			sum2 = 0;
			for (int j = k; j < k + l; j++) {
				for (int i = 0; i < N; i++) {
					sum2 += map[i][j];
				}

			}
			mux *= (sum2 * (total - sum1 - sum2)); //마지막 사각형의 합은 전체 - sum1 - sumw
			maxV = maxV > mux ? maxV : mux;
		}
	}


	//Case 2 E
	for (int k = 1; k < N ; k++) { // 가장 위쪽 사각형의 세로 길이 정하기
		sum1 = 0;
		for (int i = 0; i < k; i++) { 
			for (int j = 0; j < M; j++) {
				sum1 += map[i][j];
			}
		}

		for (int l = 1; l + k < N; l++) { // 중간 사각형의 세로 길이 정하기
			mux = sum1;
			sum2 = 0;
			for (int i = k; i < k + l; i++) {
				for (int j = 0; j < M; j++) {
					sum2 += map[i][j];
				}
				
			}
			mux *= (sum2 * (total - sum1 - sum2));
			maxV = maxV > mux ? maxV : mux;
		}
	}


	//Case 3 1=
	for (int k = 1; k < M ; k++) { //세로 사각형의 가로 길이 정하기
	
		sum1 = 0;
		for (int j = 0; j < k; j++) { //가로 길이
			for (int i = 0; i < N; i++) { //밑으로 다 더하기
				sum1 += map[i][j];
			}
		}

		for (int l = 1; l < N ; l++) { // 가로 사각형의 가장 위쪽 사각형의 세로 길이 정하기
			mux = sum1;
			sum2 = 0;
			for (int i = 0; i < l; i++) {
				for (int j = k; j < M; j++) {
					sum2 += map[i][j];
				}
			}
			mux *= (sum2 * (total - sum1 - sum2));
			maxV = maxV > mux ? maxV : mux;
		}
	}

	//Case 4 =1
	for (int k = 1; k < M ; k++) { // 세로 사각형의 가로길이
		mux = 1, sum1 = 0;
		for (int j = M - 1; j > M - 1 - k; j--) { //가로 길이
			for (int i = 0; i < N; i++) { //밑으로 다 더하기
				sum1 += map[i][j];
			}
		}
		for (int l = 1; l < N ; l++) { // 가로 사각형의 가장 위쪽 사각형의 세로 길이 정하기
			mux = sum1;
			sum2 = 0;
			for (int i = 0; i < l; i++) {
				for (int j = 0; j <= M - 1 - k; j++) {
					sum2 += map[i][j];
				}
			}
			mux *= (sum2 * (total - sum1 - sum2));
			maxV = maxV > mux ? maxV : mux;
		}
	}

	//Case 5 ㅠ
	for (int k = 1; k < N ; k++) { // 가로 사각형의 세로 길이
		sum1 = 0;
		for (int i = 0; i < k; i++) { //세로 길이
			for (int j = 0; j < M; j++) { //옆으로 다 더하기
				sum1 += map[i][j];
			}
		}
		
		for (int l = 1; l < M ; l++) { //세로 사각형의 가장 왼쪽 사각형의 가로 길이
			mux = sum1;
			sum2 = 0;
			for (int j = 0; j < l; j++) {
				for (int i = k; i < N; i++) {
					sum2 += map[i][j];
				}
			}
			mux *= (sum2 * (total - sum1 - sum2)); //마지막 사각형의 합은 전체 - sum1 - sum2
			maxV = maxV > mux ? maxV : mux;
		}
	}

	//Case 6 ㅛ
	for (int k = 1; k < N ; k++) {
		sum1 = 0;

		for (int i = N - 1; i > N - 1 - k; i--) { //세로 길이
			for (int j = 0; j < M; j++) { //옆으로 다 더하기
				sum1 += map[i][j];
			}
		}
	
		for (int l = 1; l < M ; l++) { //세로 사각형의 가장 왼쪽 사각형의 가로 길이
			mux = sum1;
			sum2 = 0;
			for (int j = 0; j < l; j++) {
				for (int i = 0; i < N - k; i++) {
					sum2 += map[i][j];
				}
			}
			mux *= (sum2 * (total - sum1 - sum2)); //마지막 사각형의 합은 전체 - sum1 - sumw
			maxV = maxV > mux ? maxV : mux;
		}
	}
}

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%1d", &map[i][j]);
			total += map[i][j];
		}
	}
	solve();

	printf("%lld\n", maxV);
}

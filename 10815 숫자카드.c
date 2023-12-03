#include<string.h>
#include<stdio.h>
#include<stdlib.h>
// https://www.acmicpc.net/problem/10815
int main() {
    char* bitMap = (char*)malloc(2500001 * sizeof(char));
    memset(bitMap, 0, 2500001 * sizeof(char));
    int N, bitMapIndex, bitIndex;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int num;
        scanf("%d", &num);
        num += 10000000;
        bitMapIndex = num >> 3;
        bitIndex = num & 7;
        bitMap[bitMapIndex] |= (1 << bitIndex);
    }

    int M;
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int num;
        scanf("%d", &num);
        num += 10000000;
        bitMapIndex = num >> 3;
        bitIndex = num & 7;
        if (bitMap[bitMapIndex] & (1 << bitIndex)) {
            printf("1 ");
        }
        else {
            printf("0 ");
        }
    }

  free(bitMap);
}

#include <stdio.h>
char check[12500001];

int main ( void )
{
    long v;
    int a, b, cnt = 0;
    scanf( "%d %d", &a, &b );
    for( int i = 0; i < a; ++ i )
    {
        scanf( "%ld", &v );
		check[v >> 3] |= (1 << (v & 7)); // 1<< (v%8)
    }
    for( int i = 0; i < b; ++ i )
    {
        scanf( "%ld", &v );
        if(check[v >> 3] & (1 << (v&7)))
            cnt++;
    }
    
    printf( "%d", a + b - 2 * cnt );
    return 0;
}


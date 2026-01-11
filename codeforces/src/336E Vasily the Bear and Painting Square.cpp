#include <cstring>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define Rep(i,l,r) for(i=(l);i<=(r);i++)
#define Rev(i,r,l) for(i=(r);i>=(l);i--)
#define inc(a,b) {a+=b;if(a>=ansmod)a-=ansmod;}

using namespace std;
const int  ansmod  = 1000000007 ;

int N , K ;
int g[16][10][16] = {0} ;
int h[5][10][2][2][16] = {0} ;
int f[401][210][16] = {0} ;
int num[16] ;

int i , j , k , A , B , use , last , first , now1 , now2 , cnt , can , Time , ans ;
int col[4] = {0} ;

int main() {
    fast;
    Rep (A,0,16-1) {
        num[B=A] = 0 ;
        while (B) num[A]+=(B&1) , B>>=1 ;
    }
    Rep (A,0,16-1) {
        memset(h , 0 , sizeof h) ;
        h[1][0][0][0][A]=h[1][1][1][0][A|1]=h[1][2][1][1][A|1]=h[1][1][0][1][A|1]=1;
        if (!(A&1)) h[1][1][1][1][A|1]=1;
        Rep (i,1,3) Rep (use,0,8) Rep (last,0,1) Rep (first,0,1)
            Rep (B,0,16-1) if (h[i][use][last][first][B])
                Rep (now1,0,1) Rep (now2,0,1) {
                    if (!now1 && !now2 && !((B>>i)&1))
                        inc(h[i+1][use+1][1][first][B|(1<<i)],h[i][use][last][first][B]);
                    inc(h[i+1][use+now1+now2][now2][first][B|((now1|now2)<<i)],h[i][use][last][first][B]) ;
                    if (!last && !now1)
                        inc(h[i+1][use+1+now2][now2][first][B|(1<<i)|(1<<(i-1))],h[i][use][last][first][B]);
                    if (!now1 && !now2 && !((B>>i)&1) && !((B>>(i-1))&1))
                        inc(h[i+1][use+1][1][first|(i==1)][B|(1<<i)|(1<<(i-1))],h[i][use][last][first][B]);
                }
        Rep (use,0,8) Rep (B,0,16-1)
            inc(h[4][use+1][1][1][B|9],h[4][use][0][0][B]) ;
        Rep (use,0,8) Rep (B,0,16-1) if (!(B&1)&&!(B&8))
            inc(h[4][use+1][1][1][B|9],h[4][use][0][0][B]) ;
        Rep (use,0,8) Rep (last,0,1) Rep (first,0,1) Rep (B,0,16-1)
            inc(g[A][use][B],h[4][use][last][first][B]) ;
    }
    Rep (A,0,16-1) Rep(B,0,16-1) {
        col[0]=col[1]=col[2]=col[3]=0;
        cnt = 0 ;
        Rep (i , 0 , 4-1)
            col[i] = ((A>>i)&1) , cnt += col[i] ;
        can = true ;
        Rep (i,0,4-1) if ((B>>i)&1) {
            if (col[i] || col[(i+1)%4]) can = false ;
            col[i] = col[(i+1)%4] = true ;
            cnt ++ ;
        }
        if (!can) continue ;
        K = 0 ;
        Rev (i,4-1,0)
            K = (K<<1)|col[i] ;
        f[0][cnt][K] ++ ;
    }
    Rep (i,0,400-1) Rep (j,0,200) Rep (A,0,16-1)
        if (f[i][j][A]) {
            if (i&1) {
                Rep (k,0,8)
                        Rep (B,0,16-1)
                            inc(f[i+1][j+k][B],(ll)f[i][j][A]*g[A][k][B]%ansmod) ;
            } else {
                Rep (k,0,16-1)
                    inc(f[i+1][j+num[k]][A|k],f[i][j][A]) ;
            }
        }
    cin >> Time ;
    while (Time --> 0) {
        cin >> N >> K;
        ans = 0 ;
        Rep (A,0,16-1)
            inc(ans,f[2*N][K][A]) ;
        Rep (i,1,K)
            ans = (ll)ans*i%ansmod ;
        cout << ans << '\n';
    }
    return 0 ;
}
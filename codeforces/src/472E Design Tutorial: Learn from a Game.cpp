//
// Created by Psy.C on 2026/2/14.
//

#include <bits/stdc++.h>
#define ii pair<int,int>
#define read(x) scanf("%d",&(x))
using namespace std;

constexpr int N=35;
vector<int> sx[N*N];
int head[N*N];

int n,m;
int a[N][N],_a[N][N];
inline int P(const int x, const int y) { return (x-1)*m+y; }
inline int X(const int x){ return (x-1)/m+1; }
inline int Y(const int x){ return (x-1)%m+1; }

int b[N];
inline bool check(int n){
    for (int i=1;i<=n;i++) if (b[i]!=i) return false; return true;
}
inline void work(){
    if (n==1){
        for (int i=1;i<=m;i++){
            for (int j=1;j<=m;j++) b[j]=a[1][j];
            for (int j=i;j<=m;swap(b[j],b[j+1]),j++)
                if (check(m)){
                    printf("%d\n",j-i);
                    for (int k=i;k<=j;k++) printf("%d %d\n",1,k);
                    return;
                }
            for (int j=1;j<=m;j++) b[j]=a[1][j];
            for (int j=i;j;swap(b[j],b[j-1]),j--)
            if (check(m)){
                printf("%d\n",i-j);
                for (int k=i;k>=j;k--) printf("%d %d\n",1,k);
                return;
            }
        }
    } else {
        for (int i=1;i<=n;i++){
            for (int j=1;j<=n;j++) b[j]=a[j][1];
            for (int j=i;j<=n;swap(b[j],b[j+1]),j++)
                if (check(n)){
                    printf("%d\n",j-i);
                    for (int k=i;k<=j;k++) printf("%d %d\n",k,1);
                    return;
                }
            for (int j=1;j<=n;j++) b[j]=a[j][1];
            for (int j=i;j;swap(b[j],b[j-1]),j--)
                if (check(n)){
                    printf("%d\n",i-j);
                    for (int k=i;k>=j;k--) printf("%d %d\n",k,1);
                    return;
                }
        }
    }
    printf("-1\n");
}

vector<ii> ans;
#define pt(x,y) (ans.emplace_back(x,y))
int nx,ny;
int pos[N*N];

inline void Swap(const int x1, const int y1, const int x2, const int y2){
    swap(a[x1][y1],a[x2][y2]);
    swap(pos[a[x1][y1]],pos[a[x2][y2]]);
}
inline void jump(int x,int y){
    if (x==nx && y==ny) return;
    pt(x,y); Swap(nx,ny,x,y); nx=x; ny=y;
}
inline void jump(const int p){ jump(X(p),Y(p)); }

int fl,fr;
int Q[N*N],l,r;
int pre[N*N];
int vst[N*N];

constexpr int dx[]={0,0,1,-1,1,1,-1,-1}, dy[]={1,-1,0,0,1,-1,1,-1};

int ins[N*N];

inline void bfs(const int S, const int T){
    l=r=-1;
    Q[++r]=S; ins[S]=1;
    int x,y,sx,sy;
    while (l<r){
        ++l; x=X(Q[l]),y=Y(Q[l]);
        for (int k=0;k<8;k++){
          sx=x+dx[k],sy=y+dy[k];
          if (sx<1 || sy<1 || sx>n || sy>m || vst[a[sx][sy]] || ins[P(sx,sy)]) continue;
          Q[++r]=P(sx,sy); ins[P(sx,sy)]=1; pre[P(sx,sy)]=P(x,y);
          if (P(sx,sy)==T) {
              for (int i=0;i<=r;i++) ins[Q[i]]=0;
              return;
          }
        }
    }
}

int lst[N*N],pnt;

inline void moveto(const int x, const int y){
    if (nx==x && ny==y) return;
    bfs(P(nx,ny),P(x,y));
    int t=P(x,y); pnt=0; while (t!=P(nx,ny)) lst[++pnt]=t,t=pre[t]; lst[++pnt]=t;
    reverse(lst+1,lst+pnt+1);
    for (int i=2;i<=pnt;i++) jump(lst[i]);
}

int path[N*N],tot;

inline void move(const int x1, const int y1, const int x2, const int y2){
    vst[a[x1][y1]]=1;
    bfs(P(x1,y1),P(x2,y2));
    int t=P(x2,y2);
    tot=0; while (t!=P(x1,y1)) path[++tot]=t,t=pre[t]; path[++tot]=t;
    reverse(path+1,path+tot+1);
    for (int i=2;i<=tot;i++){
        moveto(X(path[i]),Y(path[i]));
        jump(X(path[i-1]),Y(path[i-1]));
    }
}

inline void Solve(int n,int m){
    if (n==2 && m==2){
        if (pos[P(2,2)]!=P(2,2)) jump(2,2),jump(pos[P(2,2)]);
        if (pos[P(2,1)]!=P(2,1)) jump(2,1),jump(pos[P(2,1)]);
        if (pos[P(1,2)]!=P(1,2)) jump(1,2),jump(pos[P(1,2)]);
        return;
    }
    if (n>=m){
        int t;
        for (int i=1;i<=m-2;i++){
            if ((t=pos[P(n,i)])!=P(n,i)) move(X(t),Y(t),n,i);
            vst[P(n,i)]=1;
        }
        if ((t=pos[P(n,m-1)])!=P(n,m)) move(X(t),Y(t),n,m);
        vst[P(n,m-1)]=1;
        if ((t=pos[P(n,m)])!=P(n-1,m)) move(X(t),Y(t),n-1,m);
        vst[P(n,m)]=1; moveto(n,m-1);
        jump(n,m); jump(n-1,m);
        Solve(n-1,m);
    } else {
        int t;
        for (int i=1;i<=n-2;i++){
            if ((t=pos[P(i,m)])!=P(i,m)) move(X(t),Y(t),i,m);
            vst[P(i,m)]=1;
        }
        if ((t=pos[P(n-1,m)])!=P(n,m)) move(X(t),Y(t),n,m);
        vst[P(n-1,m)]=1;
        if ((t=pos[P(n,m)])!=P(n,m-1)) move(X(t),Y(t),n,m-1);
        vst[P(n,m)]=1; moveto(n-1,m);
        jump(n,m); jump(n,m-1);
        Solve(n,m-1);
    }
}

int main(){
    freopen("t.in","r",stdin);
    freopen("t.out","w",stdout);
    read(n); read(m);
    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) read(a[i][j]);
    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) read(_a[i][j]),sx[_a[i][j]].emplace_back(P(i,j));
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++){
            head[a[i][j]]++;
            if (head[a[i][j]]>(int)sx[a[i][j]].size()) return printf("-1\n"),0;
            a[i][j]=sx[a[i][j]][head[a[i][j]]-1];
        }
    if (n==1 || m==1) { work(); return 0; }
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++){
            if (a[i][j]==1) pt(i,j),nx=i,ny=j;
            pos[a[i][j]]=P(i,j);
        }
    Solve(n,m);
    printf("%d\n",ans.size()-1);
    for (auto &[fst, snd] : ans) printf("%d %d\n",fst,snd);
    return 0;
}
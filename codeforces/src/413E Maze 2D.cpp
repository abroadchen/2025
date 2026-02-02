//
// Created by Psy.C on 2026/2/2.
//
/**
* 距离矩阵：dist[2][2] 存储4个距离值（从(0,0), (0,1), (1,0), (1,1)之间的最短距离）
重载操作符：方便通过 [] 访问距离数组
 *
*合并逻辑：计算两个区间合并后的最短路径
Floyd-Warshall思想：通过中间点k更新最短路径
+1操作：路径长度加1（跨区间连接）  +1表示跨区间连接需要一步
 *
*当 x 或 y 大于 n 时，意味着它们在第二行（下标从 n+1 开始）
x>n 的结果是布尔值（0 或 1）：
如果 x <= n，返回 0（第一行）
如果 x > n，返回 1（第二行）
y>n 的结果也是布尔值：
如果 y <= n，返回 0（第一行）
如果 y > n，返回 1（第二行）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

#define gc c=getchar()//读取一个字符并赋值给变量 c
#define r(x) read(x)
#define ls (rt<<1)//线段树左儿子节点
#define rs (rt<<1|1)

template<typename T>
void read(T&x){
    x=0;T k=1;char gc;
    while(!isdigit(c)){if(c=='-')k=-1;gc;}
    while(isdigit(c)){x=x*10+c-'0';gc;}x*=k;
}

const int INF=1e9;

const int N=2e5;

char s[2][N];//两行字符数据

struct seg{
    int dist[2][2];
    //常量版本的下标操作符
    const int* operator [](const int &x)const{
        return dist[x];
    }
    //非常量版本的下标操作符
    int* operator [](const int &x){
        return dist[x];
    }

}tr[N<<2];

//合并操作符，用于合并两个线段树节点
inline seg operator +(const seg &a,const seg &b){
    seg ret;
    for(int i=0;i<2;++i){
        for(int j=0;j<2;++j){
            ret[i][j]=INF;
            for(int k=0;k<2;++k)ret[i][j]=min(ret[i][j],a[i][k]+b[k][j]+1);
        }
    }
    return ret;
}

inline void build(int rt,int l,int r){
    if(l==r){//单个位置的距离矩阵
        tr[rt][0][0]=tr[rt][0][1]=tr[rt][1][1]=tr[rt][1][0]=INF;
        if(s[0][l]=='.'){//位置 l 在第一行是可通行的
            tr[rt][0][0]=0;//从第一行到第一行的距离为0（自己到自己的距离）
            //位置 l 在第二行也是可通行的，则从第一行到第二行的距离为1（可以通过垂直移动到达）
            if(s[1][l]=='.')tr[rt][0][1]=1;
        }
        if(s[1][l]=='.'){//位置 l 在第二行是可通行的
            tr[rt][1][1]=0;
            //位置 l 在第一行也是可通行的，则从第二行到第一行的距离为1（可以通过垂直移动到达）
            if(s[0][l]=='.')tr[rt][1][0]=1;
        }
        return;
    }
    int mid=(l+r)>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    tr[rt]=tr[ls]+tr[rs];
}

inline seg query(int rt,int l,int r,int x,int y){
    if(x<=l&&r<=y)return tr[rt];
    int mid=(l+r)>>1;
    if(y<=mid)return query(ls,l,mid,x,y);
    if(x>mid)return query(rs,mid+1,r,x,y);
    return query(ls,l,mid,x,y)+query(rs,mid+1,r,x,y);
}

int n,m;

inline int Query(int x,int y){
    //将1D坐标转换为线段树中的位置索引
    int l=(x-1)%n+1;//x 映射到 [1,n] 范围
    int r=(y-1)%n+1;
    if(l>r)swap(l,r),swap(x,y);
    return query(1,1,n,l,r)[x>n][y>n];
}

int main(){
    r(n),r(m);
    scanf("%s",s[0]+1);
    scanf("%s",s[1]+1);
    build(1,1,n);
    for(int a,b;m;--m){
        r(a),r(b);
        int ans=Query(a,b);
        if(ans==INF)ans=-1;
        printf("%d\n",ans);
    }
}

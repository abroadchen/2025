//
// Created by Psy.C on 2026/4/19.
//
/**
n, m: 矩阵大小
k: 数据集数量
len[i]: 第i个数据集的长度
x[i][j], y[i][j], w[i][j]: 第i个数据集第j个点的坐标和权重
q: 查询数量
cnt: 矩形查询的数量
qx1,qy1,qx2,qy2: 矩形查询的四个坐标
c[i]: 操作类型（0=查询，非0=切换）
ans[i][j]: 第i个数据集在第j个矩形查询下的结果
flag[i]: 标记第i个数据集是否被禁用

读入k个数据集，每个数据集包含若干个点
A: 矩形查询操作，记录矩形坐标
其他: 切换操作，读入数据集编号
对每个数据集：
将其所有点加入树状数组
计算所有矩形查询的结果
从树状数组中移除这些点（恢复原状）

预处理: O(k × max(len[i]) × log²(n×m))
查询处理: O(q × k)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define low_bit(x) (x&-x)
#define ll long long
using namespace std;

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

constexpr int N = 2007, M = 1e6+7;
ll T[N+50][N+50];
void add(int x, int y, int w) {/// 在(x,y)位置添加权重w
    for (int i = x; i <= N; i += low_bit(i))
        for (int j = y; j <= N; j += low_bit(j))
            T[i][j] += w;
}

///查询(1,1)到(x,y)的矩形区域内所有元素的和
ll get(int x, int y) {
    ll res = 0;
    for (int i = x; i; i -= low_bit(i))
        for (int j = y; j; j -= low_bit(j))
            res += T[i][j];
    return res;
}

int n, m, k, len[N], x[N][N], y[N][N], w[N][N], q, cnt;
int qx1[N], qy1[N], qx2[N], qy2[N], c[M];
ll ans[N][N];
bool flag[N];
char op[2];
int main() {
    rd(n);rd(m);rd(k);
    for(int i=1;i<=k;i++) {
        rd(len[i]);
        for(int j=1;j<=len[i];j++) {
            rd(x[i][j]);rd(y[i][j]);rd(w[i][j]);
        }
    }
    rd(q);
    for(int i=1;i<=q;i++) {
        char opt[2]; scanf("%s",opt);
        if(opt[0]=='A') {
            ++cnt;
            rd(qx1[cnt]);rd(qy1[cnt]);rd(qx2[cnt]);rd(qy2[cnt]);
        }
        else { rd(c[i]); }
    }
    for(int i=1;i<=k;i++) {
        for(int j=1;j<=len[i];j++) {
            add(x[i][j],y[i][j],w[i][j]);
        }
        for(int j=1;j<=cnt;j++) {
            ans[i][j]=get(qx2[j],qy2[j])+get(qx1[j]-1,qy1[j]-1)
            -get(qx1[j]-1,qy2[j])-get(qx2[j],qy1[j]-1);
        }
        for(int j=1;j<=len[i];j++) {
            add(x[i][j],y[i][j],-w[i][j]);
        }
    }
    for(int i=1,tot=1;i<=q;i++) {
        if(c[i]) { flag[c[i]]^=1; }//切换数据集启用/禁用状态
        else {
            ll res=0;
            for(int j=1;j<=k;j++) {
                if(!flag[j]) res+=ans[j][tot];//只累加未被禁用的数据集
            }
            printf("%lld\n",res);
            tot++;
        }
    }
    return 0;
}
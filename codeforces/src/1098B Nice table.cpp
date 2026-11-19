//
// Created by Psy.C on 2026/11/19.
//

/**
真正学会的起点..
f 是一个标记：直接对数组整体翻转后，n/m 互换但数据布局已是转置后，输出前若 f 为真需再转一次恢复原方向
d=当前数据(按行优先线性存储)，b=转置中间缓冲
把 (行x, 列y) 映射成线性下标。注意用的是 m（列数）。
返回 0 基下标，at 用它定位
返回 d[idx] 的引用，使 mt.at(i,j)=c 可直接赋值。
前提：此时数组按当前 (n,m) 布局，且下标合法
把 (n,m) 矩阵转置为 (m,n)。因为 idx/at 用的是 m，转置后 m 已变，所以 at 的定位自动按新布局来。
(j-1)*n+i-1 是旧布局 b 中"列 j、行 i"的线性下标（旧矩阵列数=n），正是转置所需的反向映射。
f = !f：记录"现在坐标系与原始用户输入相比是否转置过"
保证最终按用户输入时的原始 n×m 方向输出。
若内部恰好在转置坐标（f 真），先 reverse() 恢复，再逐格打印，每行末换行
复制规模、翻转状态和全部数据，供 ans = ret 使用
cur = (i&1)<<1：若 i 是奇数行，cur=0；偶数行 cur=2。这是因为矩阵被分成 两行一组：奇数行用 t[0],t[1]，偶数行用 t[2],t[3]（这是 2×2 模板的"前半/后半"）。
内层对某行 i，枚举两种列相位 k（决定列上是 t[cur],t[cur+1] 还是 t[cur+1],t[cur] 交替）。
mt.d[(i-1)*m+j-1] 取输入 mt 的 (i,j) 原字符；
目标字符是 t[cur+(j&1)^k]：j&1 决定列奇偶，^k 翻转相位。所以每格期望颜色在两种相位间互换。
统计与目标不一致的格数 cnt，选 cnt 更小的相位 best。
累加该行改动到 ret（ret+=mn），并按 best 相位把本行理想字符写进 at(i,j)（结果存进自身矩阵，供输出）。
返回 total。
读入 n、m 与全部字符，f=0（未转置）
枚举 A/G/C/T 的 24 种排列，每种跑一遍 calc（即以该排列为 2×2 模板重填矩阵），记录总改动最少的那次对应的结果矩阵 ans。
next_permutation 从升序开始遍历全部排列
先对原矩阵、再对转置矩阵各做一次 get，因为有些最优模式在转置视角下等价但能取到更小改动。两次比较取全局最小 mn，ans 保存最优结果。
ans.out() 保证按用户原始方向输出最优填充
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 3e5+5, inf = 0x3f3f3f3f;

struct mtx {
    int m, n;
    char d[N], b[N];
    bool f;
    int idx(int x, int y) { return (x-1)*m+y-1; }
    char& at(int x, int y) { return d[idx(x,y)]; }
    void reverse() {
        //先备份旧数据到 b
        memcpy(b, d, sizeof(char)*n*m); swap(n,m);//行/列互换
        rep(i,n) rep(j,m) at(i,j) = b[(j-1)*n+i-1];//转置：旧 (j,i) → 新 (i,j)
        f = !f;//翻转状态取反
    }
    void out() {
        if (f) reverse();//若标记为已转置，先转回来
        rep(i,n) rep(j,m) cout << at(i,j) << (j==m?"\n":"");
    }
    mtx& operator=(const mtx &o) {
        n = o.n, m = o.m, f = o.f;
        memcpy(d, o.d, sizeof(char)*n*m);
        return *this;
    }
    int calc(const mtx &mt, const char *t) {
        f = mt.f; n = mt.n; m = mt.m;//继承输入矩阵的规模和状态
        int ret = 0;
        rep(i,n) {
            //奇偶行决定首字符来自 t 的偏移(0 或 2)
            int cur = (i&1)<<1, mn = inf, best = -1;
            for (int k = 0; k < 2; k++) {//k=0 或 1 两种列相位
                int cnt = 0;
                rep(j,m) if (mt.d[(i-1)*m+j-1] != t[cur+(j&1)^k]) cnt++;
                if (cnt < mn) mn = cnt, best = k;
            }
            ret += mn;
            rep(j,m) at(i,j) = t[cur+(j&1)^best];//按最优相位写入本行
        }
        return ret;//返回本矩阵全部改动总数
    }
    void in() {
        f = 0; cin >> n >> m;
        rep(i,n) rep(j,m) cin >> at(i,j);
    }
} ans, res;//ans=最优结果，res=输入矩阵

int mn = inf;//当前最小改动数
void get(const mtx &o) {
    char t[] = "AGCT";
    mtx ret;
    do {
        int tmp = ret.calc(o, t);
        if (tmp < mn) mn = tmp, ans = ret;
    } while (next_permutation(t,t+4));
}

int main() {
    fast;
    res.in(); get(res); res.reverse(); get(res); ans.out();
    return 0;
}
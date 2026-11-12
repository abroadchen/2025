//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
按 (x, y) 字典序排序，sgn 用 eps 处理浮点比较误差
3×3 矩阵乘法，pw[j] = pw[j-1]^2（2 的幂次的预计算）
cur：当前状态向量；pw：转移矩阵的2的幂次
把点排序后，维护上凸包，st[1..tp] 存凸包上的点下标。get(p,x)=p.x*x+p.y 是直线的函数值——点 (x,y) 代表斜率为 x、截距为 y 的一条线，凸包用于在凸壳上取最优的"线"来求极值（本质是凸包 + 分治查极值 / CHT 凸壳技巧）
每个输入项 (a[i], b[i], p[i]) 生成一个点 (p[i], a[i]*p[i])，X 存所有 b[i]*p[i] 的最大值
cur 是状态行向量，cur.a[1][3]=1 把常数项置 1（用于仿射变换）。
id 是当前最优选项（通过凸包与阈值比较选出）。
pw[0] 是根据 id 构建的 单步转移矩阵（与 p[id]、a[id]、X 有关）。
内部 for 用矩阵快速幂中的倍增法：从大到小枚举 2 的幂次，只要"跳这步后仍保持当前最优决策不变"，就累加步数并更新 cur，最长能跳 2^37 步。这大大减少了循环次数——有多少次"最优决策切换"就跑多少次外层循环，而非 t 次。
由于 break 判 now==t，当完全跳满后退出，输出 cur.a[1][1]（最终状态的期望值）

M=38：因为 2^37 > 1e11（即满足任意 t 的二进制位数），用于矩阵快速幂的幂次层级
模板函数：若 a < b，把 a 更新为 b 并返回 true；否则返回 false。
用途：维护最大值（配合逗号表达式 a = b, true）。这里用来维护 X = max(b[i]*p[i])
返回 -1（负）、0（近似零）、1（正）。
用 eps 容忍微小误差，避免直接用 ==0 比较浮点数
3×3 矩阵，下标用 1..3。
operator*：标准矩阵乘（累加 a[i][j]*o.a[j][k]）。
cur：当前的状态"矩阵/向量"（此处用作行向量，只有 cur.a[1][*] 有效）。
pw[M]：转移矩阵的 2 的幂次 数组，pw[j] = A^(2^j)
每点保存 (x, y) 和一个 id（记住它来自哪个输入项）。
operator<：字典序排序（x 第一，y 第二），供凸包排序用
st[1..tp]：上凸包上的点的下标序列
sort：全部点按 x 增序（x 相同按 y 增序）。
for (i=1; i<=n; i=j+1)：按相同 x 分组，每组处理一次。
内层 while：因为点已按 x 排序，把 j 推到当前 x 组的最右端（P[i].x == P[j].x）。j-- 得到该组最右点。
上凸包维护的 while：比较 (st[tp]→st[tp-1]) 与 (st[tp]→j) 两条向量的叉积符号。叉积 < 0 表示出现"下拐"，不满足上凸包，于是 --tp 弹出栈顶点。
这等价于：(Δy1)·(Δx2) < (Δx1)·(Δy2)，即凹点剔除。
st[++tp] = j：把当前组最右点压栈。由于每组 x 值相同取 y 最大的（j 是该组最后也就是 y 最大的），所以凸包上的每个 x 只留一个代表点。
结果：st 存储上凸包顶点序列，tp 为顶点数。凸包作用：每个点代表直线 y = x·(斜率) + y0，凸包用于在凸壳分界处快速比较哪条线更优
计算直线 y = p.x * x + p.y 在横坐标 x 处的值。
也就是"第 p 条线/决策在 x 轴取值 z 时的高度"，用于比较哪个决策更优
t：总共要走的步数。
对每个 i：读入 (a[i], b[i], p[i])，构造点 (p[i], a[i]*p[i])。
chkmax(X, b[i]*p[i])：X 是 b[i]*p[i] 的最大值。
calc()：建好凸包
cur 作为行向量，初始为 (0,0,1)（第三位 1 提供常数项，供仿射变换）
s：由当前步数 now 与当前状态 cur.a[1][1] 算出的阈值（与 X 相关）。[推]
while：在凸包上从当前位置 i 向右推进，只要后一个凸包点满足线性不等式（即切换到后一个更优），就 i++。这是在凸壳上单调推进找到分段最优的区间（CHT 的经典两指针推进）。
id = P[st[i]].id：当前最优决策对应的原始下标
填充转移矩阵（按 a[行][列]）成如下 3×3（下标1..3，第1行是"新状态=旧×A"里的目标行）
[ 1-p[id]      0       0  ]
[ p[id]*X      1       0  ]
[ p[id]*a[id]  1       1  ]
这与概率有关：[推] 第 1 行代表某种"失败/保持不变"的权重 1-p[id]；第 2 行含 p[id]*X；第 3 行含 p[id]*a[id] 且对角线有 1（累加 buffer）。
由于 cur.a[1][k] 才是我们关心的状态行，实际乘法用 cur * pw[0] 等价于 new[1][k] = cur[1][1]*pw[0][1][k]+cur[1][2]*pw[0][2][k]+cur[1][3]*pw[0][3][k]
pw[j] = A^(2^j)：pw[j-1]^2 即平方递推，得到矩阵快速幂所需的幂次矩阵
for (j = M-2; j>=0; --j)：从最高位到最低位尝试跳。
if (now + (1<<j) < t)：保证跳完不超过总步数 t。
mtx o = cur*pw[j]：假设用当前转移矩阵跳过 2^j 步，得到中间状态 o。
z = X*o.a[1][2] - o.a[1][1]：计算跳完后将用的新阈值。
if (i==tp || get(P[st[i]], z) > get(P[st[i+1]], z))：判断跳完后当前最优决策是否仍然不变（仍选 st[i]）：
若 i 已在凸包末位（i==tp），没有更后面的决策，必然不变；
否则比较凸包上相邻两点在 z 处的线值，若 st[i] 的值大于 st[i+1]，说明下一个决策还没变优，可安全跳。
条件成立则 now += 1<<j, cur = o：真正跳过去（用一次性跳 2^j 步的矩阵代替跑 2^j 次单步）。
这一步把 "最优决策不变期间的大量单步" 合并成一次矩阵乘 —— 这是整体 O(t) → O(切换次数·log t) 的关键。
cur = cur*pw[0]：真正执行一次单步转移（pw[0] = 矩阵 A）。
now++：步数 +1。
if (now==t) break：正好走满 t 步，跳出外层循环。
输出 cur.a[1][1]：最终状态的第一个分量（[推] 即所求的期望值），保留 10 位小数。
因为外层 for 没有终止条件本身，靠 break 退出；而倍增跳步保证 now 总能恰好到达 t
*/
#include <bits/stdc++.h>
#define rep(i,j,k) for (int i=j; i<=k; ++i)
#define db double
#define ld long double
#define ll long long
#define eps 1e-12
using namespace std;

template<typename T>
bool chkmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

constexpr int N = 1e5+10, M = 38;

int sgn(ld x) { return x < -eps ? -1 : x < eps ? 0 : 1; }

struct mtx {
    ld a[4][4]{};
    mtx() { rep(i,1,3) rep(j,1,3) a[i][j] = 0; }
    mtx operator* (const mtx &o) const {
      mtx res;
      rep(i,1,3) rep(j,1,3) rep(k,1,3) res.a[i][k] += a[i][j]*o.a[j][k];
      return res;
    }
} cur, pw[M];

struct pt {
    ld x, y; int id;
    bool operator<(const pt &o) const {
      if (sgn(x-o.x)) return sgn(x-o.x) < 0;
      return sgn(y-o.y) < 0;
    }
} P[N];

int n, tp, st[N];
void calc() {
    sort(P+1, P+n+1);
    for (int i = 1, j; i <= n; i = j+1) {
      j = i;
      while (!sgn(P[i].x-P[j].x)) j++;//跳到下一组 x 的起点
      j--;//j 是本组 x 的最后一位
      while (tp > 1 && (P[st[tp]].y-P[st[tp-1]].y)*(P[j].x-P[st[tp]].x) <
           (P[st[tp]].x-P[st[tp-1]].x)*(P[j].y-P[st[tp]].y)) --tp;//叉积条件
      st[++tp] = j;//记录第 j 个（每组x最后一个） 压入本组最后一个点
    }
}
ld get(pt p, ld x) { return p.x*x+p.y; }

ll t;
int a[N], b[N];
ld p[N], X;
int main() {
    scanf("%d%lld",&n,&t);
    rep(i,1,n) {
       scanf("%d%d%Lf",&a[i],&b[i],&p[i]);
       P[i] = {p[i], a[i]*p[i], i};//点 = (p[i], a[i]*p[i])，id 记录原下标
       chkmax(X, b[i]*p[i]);
    }
    calc();
    //当前步数=0，状态行向量 cur = (0,0,1)
    ll now = 0; cur.a[1][3] = 1;//cur 初始为行向量 (0,0,1)，代表某种初始状态
    for (int i = 1; ; ) {
        ld s = X*now-cur.a[1][1];//当前阈值
        //凸包上线性不等式
        while (i < tp && (P[st[i+1]].y-P[st[i]].y) >=
            -s*(P[st[i+1]].x-P[st[i]].x)) i++;//在凸包上推进到最优 id
        int id = P[st[i]].id;//选中的决策（哪个 p[i]）
        //构建单步转移矩阵 A
        pw[0].a[1][1] = 1-p[id]; pw[0].a[1][2] = 0; pw[0].a[1][3] = 0;
        pw[0].a[2][1] = p[id]*X; pw[0].a[2][2] = 1; pw[0].a[2][3] = 0;
        pw[0].a[3][1] = p[id]*a[id]; pw[0].a[3][2] = 1; pw[0].a[3][3] = 1;
        rep(j,1,M-2) pw[j] = pw[j-1]*pw[j-1];//预计算 A^(2^j)
        for (int j = M-2; ~j; j--) if (now+(1ll<<j) < t) {//倍增跳步
            mtx o = cur*pw[j];
            ld z = X*o.a[1][2]-o.a[1][1];
            if (i == tp || get(P[st[i]], z) > get(P[st[i+1]], z))//决策仍最优
                now += 1ll<<j, cur = cur*pw[j];
        }
        cur = cur*pw[0]; now++;//执行最基础一步
        if (now == t) break;
    }
    printf("%.10Lf\n",cur.a[1][1]);
    return 0;
}
//
// Created by Psy.C on 2026/9/25.
//
/**
int t1[N], t2[N];  // t1 = r 的数位，t2 = l 的数位
int l1, l2;        // r、l 各自的位数
int lcp;           // r 和 l 从高位起的公共前缀长度（longest common prefix）
int c[10];         // 当前枚举的某种"各数字出现次数"（长度 len 的一位候选重排）
int cl[10], cr[10];// 左/右边界对该位段的计数约束
把 l、r 拆成数位数组（t1[]=r，t2[]=l）。
求两者的公共前缀长度 lcp：while (lcp<l1 && t1[lcp+1]==t2[lcp+1]) ++lcp;
若 lcp == l1 说明 l == r，答案就是 1（只一个数）

c[i] 表示数字 i 在这个长度为 len 的段内出现的次数，总和 = len。
十重循环枚举所有可能的 (c[0..9]) 分布。
对每个分布调用 check()，判断这个"各数字出现次数"能否构成一个落在 [l, r] 范围内、且满足某种整除/边界条件的合法数（每次 ans+1，说明该组合贡献一个合法答案）

check 判定：给定各数字出现次数 c，能否在固定公共前缀（前 lcp 位）‍之后、通过排列剩余数字，构造出一个严格落在 (t2[lcp], t1[lcp]) 之间或贴合边界的合法数。

第 1 步：[lcp] 这一位如果能填一个介于 t2[lcp] 和 t1[lcp] 之间的数字（i 在开区间内且 c[i]>0），那么剩余位数随便排都必然在 [l, r] 内，直接合法。
第 2 步：若该位填 t1[lcp]（尽量贴右界），则剩余 len-1 位必须能排成字典序不小于右边界后缀的排列 —— 通过比较 c（当前剩余分布）与 cr（右边界后缀需要的计数）逐位判断（从高位到低位，看是否所有中间位都能填满使整体 ≥ 右界）。若可行则合法。
第 3 步：对称地，若该位填 t2[lcp]（贴左界），检查剩余能否排成字典序不大于左边界后缀的排列（从高位到低位与 cl 比较）。可行则合法。
也就是：固定 l、r 的公共前缀，在其后的一位通过"填中间值 / 贴右界 / 贴左界"三种情况，判定给定数字-次数组合能否形成介于 [l,r] 的可重排数。合法的组合累计到 ans。


构造右边界（r）后缀和左边界（l）后缀所需的、按数字分组的计数约束 cr[]、cl[]，供 check 做字典序比较（判断剩余数字能否填成 ≥右界 或 ≤左界 的排列）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define rep(i,j,k) for (i=(j); i <= (k); ++i)
using namespace std;

constexpr int N = 30;

int t1[N], t2[N], lcp, c[10], cl[10], cr[10];
inline bool check() {
    //1) 在公共前缀之后、t2[lcp] 与 t1[lcp] 之间的"空闲位"上，能否放一个非零的数
    for (int i = t2[lcp]+1; i < t1[lcp]; ++i)
        if (c[i]) return 1;
    //2) 尝试让该位取 t1[lcp]（贴右边界），检查剩余数字分布是否仍能塞满（cr 约束)
    if (c[t1[lcp]]) {
        bool flag = 0; --c[t1[lcp]];
        for (int i = 0; i < 10; ++i) {//逐位比较剩余分布与 cr 的字典序
            if (c[i] > cr[i]) return ++c[t1[lcp]], 1;
            if (cr[i] > c[i]) { flag = 1; break; }
        }
        ++c[t1[lcp]];
        if (!flag) return 1;
    }
    //3) 对称地，尝试让该位取 t2[lcp]（贴左边界），检查剩余分布与 cl 的字典序
    if (c[t2[lcp]]) {
        --c[t2[lcp]];
        bool flag = 0;
        for (int i = 9; ~i; --i) {
            if (c[i] > cl[i]) return ++c[t2[lcp]], 1;
            if (cl[i] > c[i]) { flag = 1; break; }
        }
        ++c[t2[lcp]];
        if (!flag) return 1;
    }
    return 0;
}

int l1, l2;
void init() {
    l1 = l2 = 0;
    memset(c, 0, sizeof(c));
    memset(cl, 0, sizeof(cl)); lcp = 0;
    memset(cr, 0, sizeof(cr));
    memset(t1, 0, sizeof(t1));
    memset(t2, 0, sizeof(t2));
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

template<typename T,typename... Args>
void read(T& t,Args&... args) {
    read(t); read(args...);
}

int l, r;
signed main() {
    fast;
    init(); read(l, r);
    while (r) t1[++l1] = r%10, r/=10;
    while (l) t2[++l2] = l%10, l/=10;
    reverse(t1+1, t1+l1+1);
    reverse(t2+1, t2+l1+1);
    while (lcp < l1 && t1[lcp+1] == t2[lcp+1]) ++lcp;
    if (lcp == l1) { cout << 1 << '\n'; return 0; }
    ++lcp;//lcp 已 ++，指向第一个不同的位
    if (lcp < l1) ++cl[t2[lcp+1]], ++cr[t1[lcp+1]];
    for (int i = lcp+2; i <= l1; ++i) {//构造右边界后缀的"计数下界"cr
        if (t1[i] >= t1[i-1]) ++cr[t1[i]];
        else {
            cr[t1[i-1]] = 0, cr[t1[i-1]-1] += 1;
            break;
        }
    }
    for (int i = lcp+2; i <= l1; ++i) {//构造左边界后缀的"计数上界"cl
        if (t2[i] <= t2[i-1]) ++cl[t2[i]];
        else {
            cl[t2[i-1]+1] += 1, cl[t2[i-1]] = 0;
            break;
        }
    }
    int ans = 0, len = l1 - lcp + 1;
    memset(c, 0, sizeof(c));
    rep(c[0], 0, len) rep(c[1], 0, len-c[0])
        rep(c[2], 0, len-c[0]-c[1]) rep(c[3], 0, len-c[0]-c[1]-c[2])
            rep(c[4], 0, len-c[0]-c[1]-c[2]-c[3])
                rep(c[5], 0, len-c[0]-c[1]-c[2]-c[3]-c[4]) rep(c[6], 0, len-c[0]-c[1]-c[2]-c[3]-c[4]-c[5])
                    rep(c[7], 0, len-c[0]-c[1]-c[2]-c[3]-c[4]-c[5]-c[6])
                        rep(c[8], 0, len-c[0]-c[1]-c[2]-c[3]-c[4]-c[5]-c[6]-c[7]) {
        c[9] = len - c[0] - c[1] - c[2] - c[3] - c[4] - c[5] - c[6] - c[7] - c[8];
        ans += check();
    }
    cout << ans << '\n';
    return 0;
}
//
// Created by Psy.C on 2025/11/28.
//
/*
*n: 游戏轮数
h[N], g[N]: 数组，用于存储前缀和
a, b: 两个玩家的策略字符串
ans, sum: 计数器，ans记录a获胜次数，sum记录b获胜次数
*0：平局（相同手势）
1：玩家1获胜
-1：玩家2获胜
*l, r：分别获取两个字符串的长度
cnt, t：循环索引，用于遍历字符串
d：两个长度的最大公约数
lcm：两个长度的最小公倍数
 *
*循环处理一个完整周期（长度为lcm）：
调用 ok 函数判断当前轮次结果
根据结果更新计数器
循环索引递增，如果到达字符串末尾则重置为0
记录前缀和到数组 h 和 g
 *
*完整周期数：n / lcm
余下轮数：n % lcm
总结果 = 完整周期结果 + 余下轮数结果
输出：sum（玩家2获胜次数）和 ans（玩家1获胜次数）
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define sz(x) (static_cast<int>((x).size()))
using namespace std;

typedef long long ll;
constexpr int N = 1e6+1000;
int n, h[N], g[N];
string a, b;
ll ans = 0, sum = 0;

//判断石头剪刀布游戏中玩家1是否获胜
int ok(const char c1, const char c2) {
    if (c1 == c2) return 0;
    if (c1 == 'R' && c2 == 'S') return 1;
    if (c1 == 'S' && c2 == 'P') return 1;
    if (c1 == 'P' && c2 == 'R') return 1;
    return -1;
}

int main() {
    fast;
    cin >> n >> a >> b;
    int l = sz(a), r = sz(b), cnt = 0, t = 0;
    const int d = __gcd(l, r), lcm = l * r / d;
    for (int i = 1; i <= lcm; ++i) {
        const int cur = ok(a[cnt], b[t]);
        if (cur == 1) ans++;
        else if (cur == -1) sum++;
        t++, cnt++;
        if (t == r) t = 0;
        if (cnt == l) cnt = 0;
        h[i] = static_cast<int>(ans); g[i] = static_cast<int>(sum);
    }
    sum *= n / lcm; ans *= n / lcm;
    sum += g[n % lcm]; ans += h[n % lcm];
    cout << sum << ' ' << ans;
    return 0;
}
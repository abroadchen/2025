//
// Created by Psy.C on 2026/10/20.
//
/**
读入 n、k1、k2，然后 k1 += k2，把两次可用的"步数"合并成一个总步数 k1（因为调整 a 的方式对 k1、k2 没区别，只看总步数）。
读数组 a、b。
对每个位置 i，把绝对值差 abs(a[i]-b[i]) 放入最大堆 q
重复 k1 次（总步数）：
取出堆顶（当前最大差值的绝对值 t）。
if (t > 0) t--; else t++;：若 t>0，把差值减 1（让 a 与 b 更接近）；若 t==0，则差值加 1（t==0 时只能往远离的方向走 1，下一次再拉回来）。
放回堆。
贪心正确性：因为目标是 Σ差值² 最小，而平方函数是凸的、增长随差值增大而加速，所以每次把最大的差值减小 1 收益最大（"shrink the largest gap first"），这是经典贪心。当最大差值已经到 0 时，减不动，只能 +1 再在下次抵消
把堆里最终的 n 个差值逐个取出，累加平方和 ans += t*t。
1ll*t*1ll*t 用 long long 防溢出。
输出 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 1e3+5;

int n, k1, k2, a[N], b[N], t;
priority_queue<int> q;
ll ans;
int main() {
    fast;
    cin >> n >> k1 >> k2; k1 += k2;
    rep(i,n) cin >> a[i];
    rep(i,n) cin >> b[i];
    rep(i,n) q.push(abs(a[i] - b[i]));
    rep(i,k1) {
        t = q.top(); q.pop();
        if (t > 0) t--; else t++;
        q.push(t);
    }
    rep(i,n) {
        t = q.top(); q.pop();
        ans += 1ll*t*1ll*t;
    }
    cout << ans;
    return 0;
}
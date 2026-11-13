//
// Created by Psy.C on 2026/11/13.
//

/**
真正学会的起点..
前缀和数组 sum[i] 存的是 pair<int,int>（横纵坐标）。构建：

if (s[i-1]=='U') { x 不变, y+1 }
if (s[i-1]=='D') { x 不变, y-1 }
if (s[i-1]=='L') { x-1, y 不变 }
if (s[i-1]=='R') { x+1, y 不变 }
因此 sum[len] 就是执行整串指令后的最终位置
sum[r] - sum[l-1]：区间 [l, r] 内指令产生的净位移（若改掉这段，这段贡献就不算了）。
减去这段后，剩下的位移 (fixedX, fixedY) 是无法改变的"固定位移"。
目标是最终到达 t=(x,y)，所以需要在 [l,r] 这一段内凑出的剩余位移是 (x - fixedX, y - fixedY)。
这一段长度是 len = r-l+1。我们可以任意改写这段 len 条指令（每条贡献一个单位的横或纵位移）。
能否凑出：需要凑的曼哈顿距离 |dx| + |dy| 必须 ≤ 段长 len，且与段长同奇偶（因为改变总步数的奇偶性受限）。
注意：这里的 check 里没有显式地检查同奇偶，但主函数在一开始对整串判断时用了奇偶判断（见下），意味着能匹配的条件主要靠双指针推进
前置可行性判断（对整串改）：
若目标距离 |x|+|y| 大于总指令数 len，改不完。
若 |x|+|y| 与 len 的奇偶性不同（(...-len) & 1 恒成立），则不可能——因为每一步位移改变量的奇偶与步数强相关
l 左指针、r 右指针（滑动窗口）。
当 [l, r] 满足 check（能在段内改写凑到目标）：
记录 r-l+1 作为候选最短长度；
左移 l（收缩），看能不能更短，直到不再满足。
不满足时右移 r（扩大区间），继续。
因为整串的判断已经保证"存在可行解"（ans=inf 事件后输出即可），最终 ans 为最短可修改区间的长度
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ii pair<int, int>
using namespace std;

constexpr int N = 2e5+5, inf = 1<<30;

ii t, sum[N];
int len;
bool check(int l, int r) {
    return abs(t.first-(sum[len].first-sum[r].first+sum[l-1].first)) +
        abs(t.second-(sum[len].second-sum[r].second+sum[l-1].second)) <= r-l+1;
}

char s[N];
int main() {
    fast;
    cin >> len >> s;
    rep(i,len) {
        if (s[i-1] == 'U') sum[i].first = sum[i-1].first, sum[i].second = sum[i-1].second + 1;
        if (s[i-1] == 'D') sum[i].first = sum[i-1].first, sum[i].second = sum[i-1].second - 1;
        if (s[i-1] == 'L') sum[i].first = sum[i-1].first-1, sum[i].second = sum[i-1].second;
        if (s[i-1] == 'R') sum[i].first = sum[i-1].first+1, sum[i].second = sum[i-1].second;
    }
    int x, y; cin >> x >> y;
    if (abs(x) + abs(y) > len || abs(abs(x)+abs(y)-len)&1) { cout << "-1\n"; return 0; }
    t = {x, y};
    int l = 1, r = 0, ans = inf;
    while (r <= len) {
        while (check(l,r)) { ans = min(ans, r-l+1); l++; }
        r++;
    }
    cout << ans << '\n';
    return 0;
}
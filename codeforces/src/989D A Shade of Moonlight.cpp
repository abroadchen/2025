//
// Created by Psy.C on 2026/10/25.
//

/**
真正学会的起点..
车长 l，速度 w。
车右端 vs 右行人(x2, 向左走 v=2)，车左端 vs 左行人(x1, 向右走 v=1)

设车长 l，车速 w。考虑车在穿梭两行人之间的时刻。

令事件：车刚好能"卡"在两个行人之间通过而不被撞。设经过某参考时间后：

右行人（a 中 x1）已经向右走，左行人（b 中 x2）向左走。两者相向而行会相遇。
车需要在它们相遇之前通过它们中间的间隙。
这个不等式本质是判断"车的速度 w 和长度 l"是否允许在左侧行人到达之前穿过。abs(x1+x2+l) 是一个"相遇时间坐标"的量，右边 (x2+l-x1)*w 是"车能跑的距离×速度"。

结论：check(x1, x2) 为真 ⇔ 车可以安全地从右侧行人 x2 与左侧行人 x1 之间的间隙通过，不与任何人相撞（在这个模型中）。

因此 ans 统计的是：所有满足"车能安全通过"的 (左行人b, 右行人a) 配对数量

每个行人：坐标 x、速度 v。
v==1 → 存入 a（右行行人坐标集）。
其他（如 v==2）→ 存入 b（左行行人坐标集）
两组坐标各自升序排列
对每个 b 中的坐标 x2：

二分上界 h：lower_bound(a, x2) - 1，即从 a 中取出小于 x2 的那些坐标（位置 < x2），只在这些坐标上二分。
二分查找：找到最大的 p 使得 check(a[p], x2) 为真。check 单调性上，一旦为真则更大下标也为真（因为 check 随 x1 增大而... 需验证单调性，这里假定 check 关于 x1 单调递增使得二分成立）。
ans += p + 1：统计满足条件的 a 的数量（下标 0..p 共 p+1 个）

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int l, w;
bool check(int x1, int x2) {
    return abs(x1+x2+l) < 1ll*(x2+l-x1)*w;
}

int n;
vector<int> a, b;
int main() {
    fast;
    cin >> n >> l >> w;
    for (int i = 1, x, v; i <= n; i++) {
        cin >> x >> v;
        if (v == 1) a.push_back(x); else b.push_back(x);
    }
    ll ans = 0;
    ranges::sort(a); ranges::sort(b);
    for (auto &x2 : b) {
        int low = 0, h = lower_bound(a.begin(), a.end(), x2) - a.begin() - 1, p = -1;
        while (low <= h) {
            int mid = (low + h)>>1;
            if (check(a[mid], x2)) p = mid, low = mid + 1;
            else h = mid - 1;
        }
        ans += p + 1;
    }
    cout << ans << '\n';
    return 0;
}
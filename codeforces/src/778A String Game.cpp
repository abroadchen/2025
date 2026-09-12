//
// Created by Psy.C on 2026/9/12.
//
/**
s：主串；t：模式串。
a[i]：删除顺序——第 i 步删除 s[ a[i]-1 ] 这个位置。
目标是：求最多能删除多少个位置，使得删除后 t 仍是 s 的子序列
复制 s 到 s2，把前 x 个被删位置置为空格 ' '（占位符，模拟删除）。
用双指针贪心扫 s2：cnt 记录已匹配到 t 的字符数；只要 s2[i] == t[cnt] 就匹配一个。
注意 if (cnt > t.size()) break——当 cnt == t.size() 后，访问 t[cnt] 越界？实际上 cnt 加到 t.size() 时循环退出（if (cnt == t.size()) return true）。这里的 cnt > t.size() 是防止下一轮访问 t[t.size()]（越界）的保险。
若能匹配完整个 t（cnt == t.size()），返回 true。
也就是：删除前 x 个指定位置后，t 是否仍是 s 的子序列
check(x) 具有单调性：删除越多，t 越难成为子序列。check(mid) 为真则说明 mid 步可行，可尝试更多（ans=mid, l=mid+1）；否则减少（r=mid-1）。
最终 ans = 最大的可删除步数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 2e5+10;

string s, t;
int a[N];
bool check(int x) {
    string s2 = s;
    for (int i = 0; i < x; ++i) s2[a[i]-1] = ' ';
    int cnt = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s2[i] == t[cnt]) cnt++;
        if (cnt > t.size()) break;
    }
    if (cnt == t.size()) return true;
    return false;
}

int ans = 0;
int main() {
    fast;
    cin >> s >> t;
    for (int i = 0; i < s.size(); ++i) cin >> a[i];
    int l = 0, r = s.size()-1;
    while (l <= r) {
        int mid = (l+r)/2;
        if (check(mid)) { ans = mid; l = mid + 1; }
        else r = mid - 1;
    }
    cout << ans << '\n';
    return 0;
}
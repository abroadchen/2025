//
// Created by Psy.C on 2026/11/27.
//

/**
真正学会的起点..
n	数组长度
a[N]	数组，元素非 0 即 1
ans	当前累加的连续 1 的个数
mx	历史最大值
lst	记录开头那段连续 1 的个数（用于处理环首尾相接）
p	标记是否已经记录过开头那段
ans++	累加当前连续 1 的数量
i == n	到达数组末尾
a[1]==1	第 1 个元素也是 1（环形，末尾可以和开头接上）
ans += lst	把开头连着的连续 1 段拼到末尾段上（形成跨越环的整段）
mx = max(mx, ans)	更新答案
关键点：环形数组的末尾和开头可以连接，所以最后一段 1 可以与开头一段 1 拼在一起，得到跨越整个"断点"的最大连续段。
mx = max(mx, ans)	这段 1 结束了，记录它的长度
p == 0	这是第一次遇到 0（说明开头是一串 1）
lst = ans	把开头这串 1 的长度记为 lst
p = 1	以后不再重复记录
ans = 0	重置，开始计下一段
lst 之所以只在第一次遇到 0 时记录，是因为只有紧邻数组开头的那段连续 1 才能在环上与尾部段相接。p 则保证这段只被记一次
全 1 时 mx 初始为 0，且不进入 else，mx 一直是 0。所以全为 1 时输出 0——这其实需要一个特判，但这版代码没有处理（可能题目保证有 0，或有其他约定）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 2e5+10;
int n, a[N], ans, mx, lst, p;
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    rep(i,n) {
        if (a[i]) {
            ans++;
            if (i == n) {
                if (a[1] == 1) ans += lst;
                mx = max(mx, ans);
            }
        } else {
            mx = max(mx, ans);
            if (p == 0) lst = ans;
            p = 1; ans = 0;
        }
    }
    cout << mx << '\n';
    return 0;
}
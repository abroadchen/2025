//
// Created by Psy.C on 2026/4/15.
//
/**
n：人数
d：天数
ans：标记数组，ans[i]=1表示第i天有人不满意
s：二维字符数组，存储每天每个人的状态
初始化ans[i] = 0（默认当天所有人都满意）
读取第d天的状态字符串
检查当天每个人的满意度，如果有任何人不满意('0')，则标记ans[i]=1
res：记录最长连续不满意天数
now：当前连续不满意天数
ans[d] = -1：哨兵值，用于边界处理
主循环：
如果当天有人不满意(ans[i]=1)，连续天数now++
否则，更新最大值，重置当前连续天数
最后检查：处理结尾处的连续段
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 105;
int n, d, ans[N];
char s[N][N];
int main() {
    fast;
    cin >> n >> d;
    for (int i = 0; i < d; ++i) {
        ans[i] = 0;
        cin >> s[d];
        for (int j = 0; j < n; ++j)
            if (s[d][j] == '0') {
                ans[i] = 1;
                break;
            }
    }
    int res = 0, now = 0; ans[d] = -1;
    for (int i = 0; i < d; ++i) {
        if (ans[i]) now++;
        else {
            if (now > res) res = now;
            now = 0;
        }
    }
    if (now > res) res = now;
    cout << res << '\n';
    return 0;
}
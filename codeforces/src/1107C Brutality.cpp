//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
读入 n 个数的值 v[i]。
读入字符串 s，然后 s[n]='#'。这个 '#' 充当哨兵，用来在循环 i=n 时触发"结束一组、结算"的逻辑
q：大顶堆（priority_queue<int> 默认最大堆），维护当前组内的元素。
c：记住"当前组"的字符。开始时 c = s[0]。
循环从 i=0 到 i=n（n+1 次，利用 i=n 时的哨兵做最后一次结算）
更新 c = s[i]，开始新组。
cnt = 1，然后 从堆里弹出前 k 个最大元素加入 sum（cnt<=k 控制最多取 k 个）。
把堆里剩下的（第 k+1 个及以后的所有较小元素）全部 pop() 清空——即本组只保留前 k 大，其余丢弃。
之后 q.push(v[i]) 把当前元素放入新组的堆。
若字符没变（c == s[i]）‍，不做结算，直接把 v[i] 压入当前组堆。

③ 结算细节
因为循环到 i = n 时，s[n] = '#' 与最后一个字符不同，会触发最后一次分组结算，把最后一组（含 v[n-1]）的前 k 大也加入 sum。这样所有组都被正确处理
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
#define int long long
using namespace std;

constexpr int N = 2e5+5;

vector v(N,0);
int sum;
signed main() {
    fast;
    int n, k; cin >> n >> k;
    rep(i,n) cin >> v[i];
    string s; cin >> s; s[n] = '#';
    priority_queue<int> q; char c = s[0];
    rep(i,n+1) {
        if (c != s[i]) {
            c = s[i];
            int cnt = 1;
            while (!q.empty() && cnt <= k) {
                sum += q.top(); q.pop();
                cnt++;
            }
            while (!q.empty()) q.pop();
        }
        q.push(v[i]);
    }
    cout << sum << '\n';
    return 0;
}
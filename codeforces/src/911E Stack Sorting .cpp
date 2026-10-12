//
// Created by Psy.C on 2026/10/12.
//
/**
a[i] 存前 k 个数（给定前缀）。
v[x] 记录数 x 是否已被使用。
定义 cnt：下一个"应当出栈"的最小正整数（即当前已连续弹出的最大数 + 1，初始为 1）。
每放进一个数，就检查栈顶是否等于 cnt，是则弹出并 cnt++，直到栈顶不是 cnt
栈非空时：
从 s.top()-1 递减到 cnt，把每个未使用过的数逐个补进前缀后（a[++k]），并标记已用。
如果某个数已经被用过（v[i]），说明无法构成合法排列 → 输出 -1 结束。
之后把 cnt 设为 s.top()+1，弹出栈顶。
效果：把当前栈顶下方"应补"的、比 cnt 大、比栈顶小的一整段数，按从大到小补进去。这是关键——递减补数是为了保持栈的合法性并达到字典序最大
栈清空后，把从 n 到 cnt 之间所有未使用的数，从大到小补到末尾。
因为这些都是未用、且大于等于 cnt 的数，直接递减补入是合法的，也让字典序尽量大
输出补全后的完整排列（前 k 个是给定的，后面是补的）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 2e5+5;

int n, k, a[N], v[N], cnt(1);
stack<int> s;
int main() {
    fast;
    cin>>n>>k;
    for (int i = 1; i <= k; ++i) {
        cin >> a[i]; v[a[i]] = 1; s.push(a[i]);
        //若栈顶就是"下一个该出栈的数"
        while (!s.empty() && s.top() == cnt) { cnt++; s.pop(); }
    }
    while (!s.empty()) {
        for (int i = s.top()-1; i >= cnt; --i) {
            if (v[i]) { cout << -1; return 0; }
            a[++k] = i; v[i] = 1;
        }
        cnt = s.top()+1; s.pop();
    }
    for (int i = n; i >= cnt; --i) a[++k] = i;
    for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
    return 0;
}
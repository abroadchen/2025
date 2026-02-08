//
// Created by Psy.C on 2026/2/8.
//
/**
cnt: 栈不为空
stk[cnt-1] >= stk[cnt]: 栈顶第二个元素≥栈顶元素
stk[cnt] <= x: 栈顶元素≤当前输入值x

--cnt: 栈顶指针减1（弹出栈顶元素）
min(stk[cnt], x): 取栈顶元素和当前值x的最小值
将当前值x压入栈（先将栈顶指针+1，再赋值）
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 300005
using namespace std;

int n, stk[N], cnt = 0;//栈指针，表示当前栈中元素个数
ll ans;

int main() {
    fast;
    cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        while (cnt && stk[cnt-1] >= stk[cnt] && stk[cnt] <= x)
            ans += min(stk[--cnt], x);
        stk[++cnt] = x;
    }
    sort(stk + 1, stk + cnt + 1);
    ///累加除了最大两个元素外的所有元素
    for (int i = 1; i < cnt - 1; ++i) ans += stk[i];
    cout << ans;
    return 0;
}
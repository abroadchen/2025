//
// Created by Psy.C on 2026/3/19.
//
/**
递归终止条件，当区间只有一个元素时
a[l]/2：数组元素除以2
t：表达式中使用的变量（未定义，在实际运行中会报错）
表达式计算 a[l]/2 * (abs(abs(t-l)-1) - (abs(t-l)-1))
分治合并，返回左右子树结果的和

int n：表示输入的数据数量
int x[N], y[N]：存储x坐标和y坐标的数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 55;

string dfs(int a[], int l, int r) {
    if (l == r)
        return "(" + to_string(a[l]/2) + "*(abs((abs((t-" + to_string(l) +
            "))-1))-(abs((t-" + to_string(l) + "))-1)))";
    int mid = (l + r) / 2;
    return "(" + dfs(a, l, mid) + "+" + dfs(a, mid+1, r) + ")";
}

int n, x[N], y[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1, r; i <= n; ++i) cin >> x[i] >> y[i] >> r;
    cout << dfs(x, 1, n) << '\n' << dfs(y, 1, n) << '\n';
    return 0;
}
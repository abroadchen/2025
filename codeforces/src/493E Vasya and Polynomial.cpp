//
// Created by Psy.C on 2026/2/19.
//
/**
ans: 解的计数器
w[]: 记录解的每一位值
tot: 当前记录的位数
a, b, c: 方程参数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int ans, a, b, w[110], tot;
bool dfs(const int s1, const int s2) {
    if (s1 == 0 || s2 == 0) {
        if (s1 == 0 && s2 == 0) { ++ans; return true; }//找到一个解
        return false;
    }
    if (const int x = s2%b) {//有余数
        if ((s1-x)%a == 0) {///只有当 (s1-x) 能被 a 整除时，才允许继续递归
            w[++tot] = x;//记录当前位的值
            return dfs((s1-x)/a, (s2-x)/b);//递归处理商
        }
        return false;
    }
    bool flag = false;
    const int k = ++tot;//获取当前栈顶位置的新索引，同时更新栈顶指针
    if (s1%a == 0) {
        w[k] = 0;
        flag = dfs(s1/a, s2/b);
    }
    if (s1 == b && s2 == b) {
        ++ans;
        if (!flag) { w[k] = b; tot = k; }//更新记录
        return true;
    }
    return flag;
}

int c;
int main() {
    fast;
    cin >> a >> b >> c; tot = -1; ans = 0;
    if (b == 1) {
        cout << (c == 1 ? (a == 1 ? "inf" : "1") : "0") << '\n';
        return 0;
    }
    dfs(b, c);
    cout << ans << '\n';
    return 0;
}
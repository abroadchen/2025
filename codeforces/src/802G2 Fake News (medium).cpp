//
// Created by Psy.C on 2026/9/18.
//
/**
a、b：两个字符串。
c：一个字符（从 'A' 开始递增）
基例：

x == 1：c='A'，a=""，b="A"。
x == 2：c='B'，a="B"，b="AB"。
递归（奇数 x）‍：dfs(x>>1)（即 dfs(x/2) 向下取整），然后 c++（字符序号 +1），

a = a + c + c（旧的 a，两侧包上新字符 c：ac c，即 a + c + c）
b = b + c（旧的 b 追加一个 c）
递归（偶数 x）‍：dfs(x/2 - 1)，然后 c++，

a = c + a + c + c（c 放最前，再旧 a，再 c c）
b = b + c
核心：递归深度决定了 c 递增的层数，而每次递归回返会把当前层的新字符 c 以某种对称方式拼接进 a、b。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string a, b;
char c;
void dfs(int x) {
    if (x == 1) {
        c = 'A'; a = ""; b = c;
        return;
    }
    if (x == 2) {
        c = 'B'; a = "B"; b = "AB";
        return;
    }
    if (x&1) {
        dfs(x>>1); c++;
        a = a+c+c; b = b+c;
    } else {
        dfs((x>>1)-1); c++;
        a = c+a+c+c; b = b+c;
    }
}

int n;
int main() {
    fast;
    cin >> n; dfs(n);
    cout << b+a << ' ' << b;
    return 0;
}
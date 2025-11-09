//
// Created by Psy.C on 2025/9/22.
//

#include <ios>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

inline int nxt() {
    int x; cin >> x;// 读取一个整数
    return x;
}

void solve() {
    int n = nxt(), k = nxt();// 读取基础网格大小n和递归层数k
    vector<string> a(n);// 创建大小为n的字符串向量
    for (int i = 0; i < n; ++i) cin >> a[i];// 读取n行字符串，构成基础网格
    int nn = 1;// 初始化最终网格大小
    for (int i = 0; i < k; ++i) nn *= n;// nn = n^k，计算最终网格的边长

    auto f = [&](int i, int j) {// 定义lambda函数，获取位置(i,j)的字符
        int x = nn;// 初始化x为最终网格大小
        for (int p = 0; p < k; ++p) {// 进行k层递归检查
            x /= n;// 每层的网格大小
            if (a[i / x][j / x] == '*') return '*';
            i %= x;// 更新i坐标
            j %= x;
        }
        return '.';// 默认返回'.'
    };

    for (int i = 0; i < nn; ++i) {// 遍历最终网格的每一行
        string s(nn, '?');
        for (int j = 0; j < nn; ++j)
            s[j] = f(i, j);// 获取位置(i,j)的字符
        cout << s << '\n';// 输出整行
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}
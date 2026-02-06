//
// Created by Psy.C on 2026/2/6.
//
/**
d: 包含在x的二进制表示中的数字
o: 不包含在x的二进制表示中的数字
tag: 标记是否找到有效解
x&(1<<(i-1)): 检查x的第(i-1)位是否为1

按行填充ans矩阵：
i&1: 如果i是奇数，使用d数组；否则使用o数组
j&1: j的奇偶性决定使用d或o的哪个元素
检查当前行是否符合约束条件：
如果a[i][j]不为0且与ans[i][j]不同，跳出
如果j > m说明整行都符合，继续下一行
尝试另一种填充方式（翻转奇偶性）：
^1: 异或1，翻转奇偶性
如果仍然不匹配，设置tag=0
如果找到有效解，输出并退出

类似第一个循环，但这次是按列处理：
j&1: j的奇偶性决定使用d还是o
i&1: i的奇偶性决定d或o的索引

 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1010
#define rep(i,n) for (i=1; i<=n; ++i)
using namespace std;

int get(int x) {//x的二进制表示中1的个数
    int ans = 0;
    while (x) ans += x&1, x>>=1;
    return ans;
}

int n, m, i, j, ans[N][N];
void out() {
    rep(i,n) {
        rep(j,m) cout << ans[i][j];
        cout << '\n';
    }
}

int main() {
    fast;
    cin >> n >> m;
    char op;
    int a[N][N]{};
    rep(i,n) rep(j,m) cin >> op, a[i][j] = op - '0';//转换为数字矩阵
    ///遍历3到12之间二进制表示中有2个1的数字（3, 5, 6, 9, 10, 12）
    for (int x = 3; x <= 12; ++x) if (get(x) == 2) {
        vector<int> d, o;
        int tag = 1;
        rep(i,4) x&(1<<(i-1)) ? d.push_back(i) : o.push_back(i);
        rep(i,n) {
            rep(j,m) ans[i][j] = i&1 ? d[j&1] : o[j&1];
            rep(j,m) if (a[i][j] && a[i][j] != ans[i][j]) break;
            if (j > m) continue;
            rep(j,m) ans[i][j] = i&1 ? d[(j&1)^1] : o[(j&1)^1];
            rep(j,m) if (a[i][j] && a[i][j] != ans[i][j]) break;
            if (j <= m) tag = 0;
        }
        if (tag) out(), exit(0);
    }
    for (int x = 3; x <= 12; ++x) if (get(x) == 2) {
        vector<int> d, o;
        int tag = 1;
        rep(i,4) x&(1<<(i-1)) ? d.push_back(i) : o.push_back(i);
        rep(j,m) {
            rep(i,n) ans[i][j] = j&1 ? d[i&1] : o[i&1];
            rep(i,n) if (a[i][j] && a[i][j] != ans[i][j]) break;
            if (i > n) continue;
            rep(i,n) ans[i][j] = j&1 ? d[(i&1)^1] : o[(i&1)^1];
            rep(i,n) if (a[i][j] && a[i][j] != ans[i][j]) break;
            if (i <= n) tag = 0;
        }
        if (tag) out(), exit(0);
    }
    cout << 0;
    return 0;
}
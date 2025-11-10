//
// Created by Psy.C on 2025/11/10.
//
/*
*k：限制参数
pw[15][1005]：预计算的幂次表
x[1005]：某种递推序列
t：测试用例数量
 *
*check函数：检查字符串s是否包含相邻距离≤k的'4'或'7'
lst：上一个'4'或'7'的位置
p：当前位置
如果发现相邻'4'/'7'距离≤k，返回true
 *
*lst：上一个'4'或'7'的位置
n：字符串长度
p：当前位置
f1：标记是否已找到相邻符合条件的'4'/'7'
ans：结果计数
 *遍历字符串每一位，对每一位小于当前数字的值进行计算
*模拟放置数字j的情况
更新临时状态llst和f2
*根据状态计算贡献：
如果已满足条件(f2=true)：加上所有可能的后续组合
否则：计算不满足条件的组合并减去
 *更新实际状态：如果当前位是'4'或'7'，更新位置和标记
 *加上字符串s本身是否满足条件
 *
 *pw[i][j] = i^j % mod
*计算数组x：表示某种满足条件的数字计数
使用递推关系计算
 *
 *n-p 从位置p到字符串末尾还有多少位
 *k-len 还能容纳多少位来满足距离要求
 *min(n-p, max(0, k-len)) 剩余位数与可容纳位数的最小值
 *
 *
 *pw[10][n-p]
*从当前位置到末尾的所有可能数字组合总数
因为每位可以是0-9中任意一个数字
 *len2位只能放非'4''7'数字的方案数
 *
*x[i-1] * 8 % mod
在长度为i-1的满足条件的数字后面添加一个非'4''7'数字
有8种选择（0,1,2,3,5,6,8,9)
** 2：
乘以2
代表有两种选择：放置'4'或'7'
*当i ≤ k+1：只要有一个'4'或'7'就满足条件
当i > k+1：需要考虑多个'4'/'7'之间的距离关系，所以计算方式更复杂
 *
** x[i-k-1]：
乘以数组x的第i-k-1项
表示长度为i-k-1的满足条件数字个数
 *
*pw[8][k]：
预计算的8的k次幂，即 8^k % mod
表示k个位置可以放置非'4''7'数字的方案数
 *
*pw[8][3] = 8^3 = 512
前3位放置非'4''7'数字的方案数
* 2 = 1024
第4位放置'4'或'7'的方案数
* x[2] = 1024 * x[2]
后2位放置满足条件数字的方案数
 */
#include <iostream>
#include <algorithm>
using namespace std;
const int mod = 1e9 + 7;

typedef long long ll;
int k, pw[15][1005], x[1005], t;
string l, r;

void add(int& x, int y) { x = x + y >= mod ? x + y - mod : x + y; }
bool check(string s) {
    int lst = -1000, p(0);
    for (auto i : s) {
        p++;
        if (i == '4' || i == '7') {
            if (p - lst <= k) return 1;
            lst = p;
        }
    }
    return 0;
}

int f(string s) {
    int lst = -1000, n = s.length(), p(0), f1(0), ans(0);
    for (auto i : s) {
        i -= '0'; p++;
        for (int j = 0; j < i; ++j) {
            int llst(lst), f2(f1);
            if (j == 4 || j == 7) {
                if (p - llst <= k) f2 = 1;
                llst = p;
            }
            if (f2) add(ans, pw[10][n-p]);
            else {
                int len = p - llst, len2 = min(n-p, max(0, k-len));
                add(ans, ((pw[10][n-p]-(1ll*pw[8][len2]*x[n-p-len2]%mod))%mod+mod)%mod);
            }
        }
        if (i == 4 || i == 7) { if (p - lst <= k) f1 = 1; lst = p; }
    }
    ans += check(s);
    return ans;
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> t >> k;
    for (int i = 1; i <= 10; ++i) {
        pw[i][0] = 1;
        for (int j = 1; j <= 1001; ++j)
            pw[i][j] = 1ll*pw[i][j-1]*i%mod;
    }
    x[0] = 1;
    for (int i = 1; i <= 1001; ++i) {
        x[i] = 1ll*x[i-1]*8%mod;
        if (i <= k + 1) add(x[i], pw[8][i-1]*2%mod);
        else add(x[i], 1ll*pw[8][k]*2%mod*x[i-k-1]%mod);
    }
    while (t--) {
        cin >> l >> r;
        cout << ((f(r) - f(l) + check(l)) % mod + mod) % mod << '\n';
    }
    return 0;
}
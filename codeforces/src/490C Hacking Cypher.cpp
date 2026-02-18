//
// Created by Psy.C on 2026/2/18.
//
/**
num[N]: 存储输入数字字符串
a, b: 两个除数
c[N]: 标记数组，记录前缀是否能被a整除

x == 0: 前缀能被a整除
i < len-1: 不是最后一个字符
num[i+1] != '0': 后面不以0开头（避免前导零）
c[i] = 1: 标记位置i

p = 0: 分割点位置
flag = 0: 标记是否找到解
k = 1: 权值（10的幂次）

x == 0: 后缀能被b整除
c[i-1]: 前缀num[0..i-1]能被a整除
num[i] != '0': 当前位不是0（避免前导零）
flag = 1; p = i; break;: 找到解，记录位置并退出

时间复杂度：O(len)
空间复杂度：O(len)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1000001;
char num[N];
int a, b, c[N];
int main() {
    fast;
    cin >> num;
    cin >> a >> b;
    //获取数字长度
    int len = strlen(num), x = 0, i;
    for (i = 0; i < len; ++i) {// 计算前缀num[0..i] mod a的值
        x *= 10;
        x += num[i] - '0';
        x %= a;
        if (x == 0 && i < len-1 && num[i+1] != '0') c[i] = 1;
    }
    int p = 0, flag = 0, k = 1; x = 0;
    for (i = len-1; i >= 0; --i) {//计算后缀num[i..len-1] mod b
        x += (num[i] - '0') * k;
        x %= b;
        if (x == 0 && c[i-1] && num[i] != '0') {
            flag = 1; p = i; break;
        }
        k *= 10; k %= b;// 更新权值
    }
    if (flag) {
        cout << "YES\n";
        for (i = 0; i < p; ++i) cout << num[i];
        cout << "\n";
        for (i = p; i < len; ++i) cout << num[i];
        cout << "\n";
    } else cout << "NO\n";
    return 0;
}
//
// Created by Psy.C on 2025/10/18.
//
/*
*typedef long long ll;: 定义long long类型的别名为ll，简化代码书写
const int N = 5, M = 3;: 定义常量N=5（数组大小），M=3（操作符数量）
ll a[N], ans(1e18);: 声明长度为5的long long数组a[]，以及初始化为1e18（极大值）的答案变量ans
char ch[M];: 声明长度为3的字符数组ch[]，用于存储运算符
 *
*这是回溯函数bt的定义：

参数h表示当前处理到第几个运算符（0~2）
参数b[N]是当前状态下的数值数组
如果h等于3，说明已经进行了3次运算，此时数组中只剩一个数b[0]，将其与当前最小值ans比较并更新ans
*ll c[N];: 创建临时数组c用于保存当前状态
双重循环遍历所有可能的两个数的组合(i,k)，其中i<k
4-h表示当前剩余的数字个数（随着运算进行，数字越来越少）
将当前状态b复制到临时数组c中
*将第k个位置之后的所有元素向前移动一位，覆盖掉第k个元素
递归调用bt函数处理下一个运算符(h+1)
 *
 */
#include <ios>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 5, M = 3;
ll a[N], ans(1e18);
char ch[M];

void bt(int h, ll b[N]) {
    if (h == 3) { ans = min(ans, b[0]); return; }
    ll c[N];
    for (int i = 0; i < 4 - h; ++i) {
        for (int k = i + 1; k < 4 - h; ++k) {
            for (int j = 0; j < 5; ++j) c[j] = b[j];
            if (ch[h] == '*') c[i] = c[i] * c[k];
            else c[i] = c[i] + c[k];
            for (int j = k; j < 4; ++j) c[j] = b[j + 1];
            bt(h + 1, c);
        }
    }
}




int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    for (int i = 0; i < 4; ++i) cin >> a[i];
    a[4] = 0;
    for (int i = 0; i < 3; ++i) cin >> ch[i];
    bt(0, a);
    cout << ans << endl;
    return 0;
}
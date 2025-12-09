//
// Created by Psy.C on 2025/12/8.
//
/*
*s[N]：存储输入字符串
res[N]：存储结果字符串
sum[N]：前缀和数组，用于统计'['字符数量
top：栈顶指针
stk[N]：栈数组，存储不匹配字符的位置
 *
*遍历字符串每个位置
如果当前字符是'['，则sum[i]加1
sum[i] += sum[i-1]：累加前面的'['字符数量
这样sum[i]表示从位置1到位置i中'['字符的总数
 *
*遍历字符串每个位置
如果栈为空，将当前位置入栈
如果栈不为空：
检查栈顶字符与当前字符是否匹配（()或[]）
如果匹配，栈顶指针减1（出栈）
如果不匹配，将当前位置入栈
最终栈中剩下的是无法匹配的字符位置
 *
*寻找包含最多'['字符的区间：
ans：最大'['字符数量，初始化为-1
L, R：最优区间的左右边界
遍历栈中相邻的两个位置，形成一个区间
l = stk[i-1]：区间左边界
r = ：区间右边界
sum[r] - sum[l]：该区间中'['字符的数量
如果找到更大的数量，更新答案和边界
 *
*输出最大'['字符数量ans
将最优区间[L,R]的字符复制到结果数组res
res[R + 1] = 0：添加字符串结束符
输出结果字符串res
 *
*时间复杂度：O(n)
空间复杂度：O(n)
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100010
using namespace std;

char s[N], res[N];
int sum[N], top, stk[N];

int main() {
    fast;
    scanf("%s", s + 1); const int len = static_cast<int>(strlen(s + 1));
    for (int i = 1; i <= len; ++i) {
        if (s[i] == '[') sum[i]++;
        sum[i] += sum[i - 1];
    }
    for (int i = 1; i <= len; ++i) {
        if (!top) stk[++top] = i;
        else {
            if ((s[stk[top]] == '(' && s[i] == ')') ||
                (s[stk[top]] == '[' && s[i] == ']')) top--;
            else stk[++top] = i;
        }
    }
    stk[++top] = len + 1;//在栈末尾添加哨兵元素，便于后续区间处理
    int ans = -1, L = 0, R = 0;
    for (int i = 1; i <= top; ++i) {
        const int l = stk[i - 1], r = stk[i] - 1;
        if (sum[r] - sum[l] > ans) {
            ans = sum[r] - sum[l];
            L = l + 1, R = r;
        }
    }
    cout << ans << '\n';
    for (int i = L; i <= R; ++i)  res[i - L] = s[i];
    res[R + 1] = 0;
    cout << res << '\n';
    return 0;
}
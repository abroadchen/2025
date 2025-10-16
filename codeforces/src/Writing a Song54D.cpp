//
// Created by Psy.C on 2025/10/16.
//
/*
*n: 目标字符串长度
k: 字母表大小
m: 模式串长度
nw: 用于KMP算法的指针
lps[N]: KMP算法中的最长相同前后缀数组
nx[N][M]: 自动机状态转移表
dp[N][N]: 动态规划记忆化数组
*s: 模式串
t: 约束字符串
ans: 结果字符串
 *
 *递归函数f，参数nw为当前位置，p为自动机状态
 *递归终止条件：如果到达字符串末尾，返回1（成功）
 *记忆化搜索：如果该状态已计算过，直接返回结果
 *声明下一状态np，初始化返回值为0（失败）
 *
*尝试所有可能的字符(0到k-1)：
计算转移到的新状态np
如果不是完全匹配状态且后续可以成功，则返回成功
 *
*计算转移状态np
如果达到完全匹配状态：需要检查约束条件t，并转移到lps状态
否则直接转移到新状态np
 *
 *
 *回溯函数bt，用于构造实际解
 *递归终止条件：到达字符串末尾则返回
 *
 *找到第一个可行的字符并递归处理后续位置
 *
 *
*处理约束条件：对于t中为'1'的位置，强制设置对应的模式串字符
如果出现冲突，输出"No solution"并退出
 *
 *
*nx：状态转移表，nx[state][char] 表示在状态state遇到字符char时转移到的新状态
lps[i-1]：KMP算法中的最长相同前后缀数组，表示模式串前i个字符的最长相等前后缀长度
j：当前处理的字符（已转换为数字0-25）
具体含义：
nx[lps[i-1]][j] 表示：当在状态i遇到字符j不匹配时，应回退到状态lps[i-1]，然后在该状态遇到字符j的转移结果。
 *
 *
 *
 *
 *nw：检查nw是否非零（即还有可以回退的位置）
 *
 *
 *
 */
#include <ios>
#include <iostream>
#include <cstring>
using namespace std;
const int N = 105, M = 26;
int n, k, m, nw, lps[N], nx[N][M], dp[N][N];
string s, t, ans;


int f(int nw, int p) {
    if (nw == n) return 1;
    int& ret = dp[nw][p];
    if (ret != -1) return ret;
    int np; ret = 0;
    if (ans[nw] == -1) {//如果当前位置未确定字符
        for (int i = 0; i < k; ++i) {
            np = nx[p][i];
            if (np != m && f(nw + 1, np))
                return ret = 1;
        }
    } else {//如果当前位置已确定字符
        np = nx[p][ans[nw]];
        if (np == m)
            ret = t[nw - m + 1] == '1' && f(nw + 1, lps[m - 1]);
        else
            ret = f(nw + 1, np);
    }
    return ret;
}

void bt(int nw, int p) {
    if (nw == n) return;
    int np;
    if (ans[nw] == -1) {
        for (int i = 0; i < k; ++i) {
            np = nx[p][i];
            if (np != m && f(nw + 1, np)) {
                ans[nw] = i;
                bt(nw + 1, np);
                return;
            }
        }
    } else {
        np = nx[p][ans[nw]];
        if (np == m) bt(nw + 1, lps[m - 1]);
        else bt(nw + 1, np);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n >> k >> s; m = s.size();
    for (auto& i : s) i -= 'a';//将字符转换为数字(0-25)
    cin >> t;
    for (int i = 1; i <= n; ++i) ans.push_back(-1);
    for (int i = 0; i < t.size(); ++i) if (t[i] == '1') {
        for (int j = 0; j < m; ++j) {
            if (ans[i + j] != -1) {
                if (ans[i + j] != s[j])
                    return cout << "No solution\n", 0;
            }
            ans[i + j] = s[j];
        }
    }
    for (int i = 1; i < m; ++i) {//构建KMP算法的lps数组（最长相同前后缀）
        while (nw && s[i] != s[nw]) nw = lps[nw - 1];
        if (s[i] == s[nw]) lps[i] = ++nw;
    }
    nx[0][s[0]] = 1;//构建KMP自动机的状态转移表nx
    for (int i = 1; i < m; ++i) {
        for (int j = 0; j < k; ++j) {
            if (j == s[i]) nx[i][j] = i + 1;
            else nx[i][j] = nx[lps[i - 1]][j];
        }
    }
    memset(dp, -1, sizeof(dp));
    if (!f(0, 0)) return cout << "No solution\n", 0;
    bt(0, 0);
    for (auto& i : ans) i += 'a';//将数字转换回字符并输出结果
    cout << ans << '\n';
    return 0;
}
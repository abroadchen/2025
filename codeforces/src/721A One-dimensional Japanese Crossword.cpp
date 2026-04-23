//
// Created by Psy.C on 2026/4/23.
//
/**
n：读入的整数（虽然代码中没有使用）
s：输入的字符串
res：存储结果的向量，用于记录连续'B'的长度
cnt：统计连续'B'段的数量
t：临时计数器，记录当前连续'B'的数量
in：标志位，1表示正在处理连续'B'段，0表示不在处理
循环遍历字符串s的每一个字符
如果当前字符是'B'：
如果已经在连续'B'段中(in为1)，则t计数器加1
如果之前不是连续'B'段(in为0)，则开始新的连续段：t=1，in=1
如果当前字符不是'B'（是其他字符）：
如果之前在连续'B'段中(in为1)：
将当前连续'B'的长度t加入结果向量
重置in=0，表示不再处于连续'B'段
cnt计数器加1，统计连续段数量
循环结束后，如果仍在连续'B'段中(in为1)：
说明字符串以'B'结尾，需要处理最后一段连续的'B'
将最后一个连续'B'段的长度加入结果
更新计数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
string s;
vector<int> res;
int main() {
    fast;
    cin >> n >> s;
    int cnt = 0, t = 0, in = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == 'B') {
            if (in) t++;
            else { t = 1; in = 1; }
        } else {
            if (in) {
                res.push_back(t); in = 0;
                cnt++;
            }
        }
    }
    if (in) {
        res.push_back(t); in = 0;
        cnt++;
    }
    cout << cnt << '\n';
    for (int re : res) cout << re << ' ';
    cout << '\n';
    return 0;
}
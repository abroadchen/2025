//
// Created by Psy.C on 2026/3/30.
//
/**ch[x][y]: Trie节点x的第y个子节点（y=025对应az）
cnt: 节点计数器
flag[x]: 标记节点x是否为某个单词的结尾，若为结尾则存储单词编号
将单词s插入Trie
大小写字母统一处理为小写
在单词结尾标记编号k

d[i]: 表示字符串前缀[0,i]能否被完美分割
d[i] = k (k>0): 表示位置i以单词w[k]结尾
从位置i向前扫描，检查以str[j]开头的子串
i-j+1 是当前子串长度
i-(i-j+1) 是当前子串前面的结束位置
d[i-(i-j+1)] 检查前面部分是否能被完美分割

flag[x]: 当前子串是某个单词
i-(i-j+1)<0: 子串前面没有字符（从开头开始）
d[i-(i-j+1)]: 子串前面的部分可以被完美分割

构建Trie: O(词典总字符数)
DP过程: O(n²) (n为输入字符串长度)
总体: O(n² + 词典总字符数)

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5, M = 1e5+5;

int ch[N][26], cnt, flag[N];
void insert(const char *s, int k) {
    int x = 0, y;
    for (int i = 0; s[i]; ++i) {
        if (s[i] >= 'A' && s[i] <= 'Z')
            y = s[i] - 'A';
        else y = s[i] - 'a';
        if (ch[x][y] == 0) ch[x][y] = ++cnt;
        x = ch[x][y];
    }
    flag[x] = k;
}

string w[N];
int d[M];
void dfs(int n) {
    if (n < 0) return;
    dfs(n - w[d[n]].length());//递归处理前面部分
    cout << w[d[n]] << ' ';//输出当前单词
}

int n, m;
char str[M];
int main() {
    fast;
    cin >> n >> str >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> w[i];
        insert(w[i].c_str(), i);
    }
    for (int i = 0, x, y; i < n; ++i) {
        x = 0;
        for (int j = i; j >= 0; --j) {
            y = str[j] - 'a';
            if (ch[x][y] == 0) break;
            x = ch[x][y];
            if (flag[x] && (i-(i-j+1)<0 || d[i-(i-j+1)])) {
                d[i] = flag[x];
                break;
            }
        }
    }
    dfs(n-1);
    return 0;
}
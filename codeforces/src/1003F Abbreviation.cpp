//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
s[i]：读入第 i 个词。
map<string,int> m：给每个不同词分配唯一编号 t（1 开始），去重计数 cnt。
len：累加 len(s[i])+1 = 所有词总长 + 分隔符数量（n 个词之间有 n-1 个分隔符，这里累加 n 个 +1，后面再微调）。
h 是关键：每个词用一个编号 t，编码成两个字节：
字节1 = t | 128（把最高位置 1，用于区分并保证 0 不出现在首字节）；
字节2 = t >> 7（高位信息）。
h += 字节1 + 字节2，即每种词固定占 2 字节。
这样 h 就是一个长度 2n 的字节串，每个词对应其中的连续 2 字节"指纹"，可用来做模式匹配
外层 i：子序列起点。
内层 j：子序列终点。t 表示从 i..j 这段词的编码模式（长度 2×(j-i+1)）。
ts：该子序列的词内容的总字节长度（非编码，是原词长度和）。
res 初始为 ts-1，表示这段本身可省的分隔符数。
关键策略：在 h 中从位置 j*2 开始往后查字节串 t 再次出现的位置，每出现一次就 res += ts-1——意味着这段模式每多出现"一段"，就多省一个分隔符长。
若总节省 res > ts-1，更新最大 ans。
本质：对每个可能的"可合并块"，统计它在 h 中能出现多少次（除自身外），估计合并该块最多能压缩掉多少长度，取全局最大
len 是"所有词总长 + 空格数"的初始总长；
ans 是最大可节省长度；
输出 len - ans 即最小总长度
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; i++)
using namespace std;

constexpr int N = 3.1e2;

int n, i, len(-1), cnt, ans;
string s[N], h;
map<string, int> m;
int main() {
    fast;
    cin >> n;
    rep(i,n) {
        cin >> s[i]; len += s[i].size() + 1;
        int &t = m[s[i]];
        if (!t) t = ++cnt;//给每个不同词编号（1..cnt）
        h += string(1, t|128) + string(1, t>>7);
    }
    rep(i,n) {
        string t;
        for (int j = i, ts = 0; j <= n; j++) {
            t += h.substr(j*2-2, 2);//取第 j 个词的 2 字节编码
            ts += s[j].size();//累计这词的字节长
            int res = ts - 1;
            for (int k = h.find(t,j*2); k != string::npos; k = h.find(t,k+t.size()))
                res += ts - 1;
            if (res > ts-1) ans = max(ans, res);
        }
    }
    cout << len - ans;
    return 0;
}
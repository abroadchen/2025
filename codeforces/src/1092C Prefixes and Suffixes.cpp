//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
node：存一个字符串 t 和它的原始输入序号 num。
cmp：按字符串长度升序排序（长度小的在前）
pre(s, t)：判断 s 是否是 t 的前缀 → 比较 s 与 t 的前 len(s) 个字符。
suf(s, t)：判断 s 是否是 t 的后缀 → 比较 s 与 t 的 substr(1,len)（即从第 1 位开始取 len 个，即 t 的最后 len 个字符）。
注意 suf 用 substr(1,len) 而不是 substr(len(t)-len, len)，这是 Codeforces 这题的特殊约定：整个字符串 s 存的是去掉首字符再取后缀……其实这是该题特有的"用短串匹配长串去掉某字符后"的判定。使用时调用方会确保索引有效
读入 n，得到总串数 m = 2n-2。
循环读入每个串存入 s[i]，记录原始序号 num=i，并把答案数组 c[i] 默认全置为 'S'
n=2 特判：只有 2 个字符长度的原串，其前缀后缀只有长度 1 的两个串（一个是 S[0..0]，一个是 S[n-1..n-1]）。此时按题意强制输出 "PS"，直接返回（不进入通用贪心）
按长度升序排列所有串，这样长度 1、2、…、n-1 的串依次出现，便于由短到长推。
取长度 1 的两条串 t1, t2（排序后最前面两条就是长度 1 的前缀和后缀）。
先假设第一条（p[1]）是前缀 P，把它在答案数组里标 'P'
从第 3 条串开始，按长度逐对推进。排序后 p[3],p[4] 是同长度（长度2）的前缀后缀，p[5],p[6] 同长度……以此类推。
每一步看当前长度这一对（p[i], p[i+1]）哪个是前缀哪个是后缀：
第一种情况：p[i] 是 t1 前缀扩展、p[i+1] 是 t2 后缀扩展 → 把 p[i] 标 P，p[i+1] 标 S（隐含），更新 t1,t2 为新串。
第二种情况：反过来，p[i+1] 与 t1 前缀匹配、p[i] 与 t2 后缀匹配 → 把 p[i+1] 标 P。
两种都不满足 → 第一次假设错了，标记 f=1 并把所有答案重置为 'S'，跳出循环准备第二次尝试。
这里每次都用 "当前属于前缀 P 的串 t1 和属于后缀 S 的串 t2"，去和下一长度（更长）的一对做匹配，判断下一条谁扩展前缀、谁扩展后缀——这就是"由短推长"的核心逻辑
第二次尝试（第一次假设 p[1] 是前缀失败后）：改假设 p[2] 是前缀 P（c[p[2].num]='P'，t1=p[2]，t2=p[1]）。
再次从短到长推进：能匹配就走 pre(t1,...)&&suf(t2,...) 分支标 P；否则无论是否完全匹配都按另一条作为 P（直接对称地标 P 而不校验，因为其中至少一条必是 P）。
因为两条相同长度的串必有一个是前缀 P、一个是后缀 S，第一次若猜错，第二次一定对（这是本题的确定性质，所以第二次不再需要 fail 回退）
按输入原始顺序输出每条串对应的标记（P 或 S）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1;i<=n;i++)
using namespace std;

constexpr int N = 1e3;

struct node { string t; int num; } p[N];
bool cmp(node x, node y) { return x.t.size() < y.t.size(); }

bool suf(const string& s, const string& t) {
    int len = s.size();
    if (s == t.substr(1,len)) return 1;
    return 0;
}
bool pre(const string& s, const string& t) {
    int len = s.size();
    if (s == t.substr(0,len)) return 1;
    return 0;
}

int n, m;
string s[N];
char c[N];
int main() {
    fast;
    cin >> n; m = 2*n - 2;
    rep(i,m) { cin >> s[i]; p[i].num = i; p[i].t = s[i]; c[i] = 'S'; }
    if (n == 2) { cout << "PS\n"; return 0; }
    sort(p+1, p+1+m, cmp);
    string t1 = p[1].t, t2 = p[2].t; c[p[1].num] = 'P';
    bool f = 0;
    for (int i = 3; i <= m; i++) {
        if (pre(t1,p[i].t) && suf(t2,p[i+1].t)) {
            t1 = p[i].t; t2 = p[i+1].t; c[p[i].num] = 'P';
            i++;
        } else if (pre(t1,p[i+1].t) && suf(t2,p[i].t)) {
            t1 = p[i+1].t; t2 = p[i].t; c[p[i+1].num] = 'P';
            i++;
        } else {
            f = 1;
            rep(j,m) c[j] = 'S';
            break;
        }
    }
    if (f == 1) {
        t1 = p[2].t; t2 = p[1].t; c[p[2].num] = 'P';
        for (int i = 3; i <= m; i++) {
            if (pre(t1,p[i].t) && suf(t2,p[i+1].t)) {
                t1 = p[i].t; t2 = p[i+1].t; c[p[i].num] = 'P';
                i++;
            } else {
                t1 = p[i+1].t; t2 = p[i].t; c[p[i+1].num] = 'P';
                i++;
            }
        }
    }
    rep(i,m) cout << c[i];
    cout << '\n';
    return 0;
}
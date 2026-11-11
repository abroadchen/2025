//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
string ans;                                    // 当前构造的"目标子串"（答案）
string pre[2], nxt[2], str[17];                // pre/nxt：匹配两端；str[i]：Fibonacci 词
ll d[N], h[N], mg[2][2], f[N];                 // d/h：走向记录；mg：跨段匹配贡献；f：计数
int n;                                         // 主程序里的 n（递归步数）
ll k;                                          // 第 k 小
int m;                                         // 答案长度上限（输出前 m 位）

str[i] 满足 Fibonacci 拼接：str[i] = str[i-2] + str[i-1]。
d[i]、h[i] 记录 str[i] 是由哪两个基础段组合——这里其实只是记录奇偶性/来源索引，但代码里 str 只建到 15，n 可能大于 15，所以用 d/h 记录递归来源以在 mg 里复用。
f[i] 表示 ans 在 str[i] 里出现的次数。递推式 f[i] = f[i-1] + f[i-2] + mg[...] 的物理意义：
出现在左半段（str[i-2]）的次数 f[i-2]
出现在右半段（str[i-1]）的次数 f[i-1]
但跨过左右交界处且横跨边界的 ans 需要额外数——这就是 mg[d[i]][h[i]] = calc(nxt[..] + pre[..]) 的作用（只取边界附近的片段拼接检查）。
潜在 bug：mg[d[i]][h[i]] 依赖 d[i]/h[i] 的赋值，但 d[i]=d[i-2], h[i]=h[i-1]——这两个"继承"是否真对应 str[i] = str[i-2]+str[i-1] 的两半来源？从赋值看 d 取 i-2 那条链、h 取 i-1 那条链，且初始 d[14]=h[14]=0, d[15]=h[15]=1。这确实模拟了左右来源——但 mg 只存了 14/15 两种基础类型（索引 0/1），而 d[i]/h[i] 会一直延续索引只在 {0,1} 之间，正确——因为 Fibonacci 拼接本质就是 str[i] 只由 14、15 的某种组合重复产生。方向对，但 mg 只预计算了 4 种（0/0,0/1,1/0,1/1）组合，覆盖了所有情况，逻辑自洽。
suf[i+1] 是按起点分组的 string[N*10]，但排序的是 suf[1..len] 每个串（这些是单字符，因为每次只 push 一个字符 str[n][j]）。这里逻辑混乱：

suf[i+1].push_back(str[n][j]) 把字符追加到 suf[i+1]，所以 suf[1]、suf[2]... 攒的是不同终点的子串？
实际上 i 是起点、j 从 i 到末尾，suf[i+1] 会不断追加，最后 suf[i+1] = 从位置 i 到末尾的后缀。
sort(suf+1, ..., cmp) 排的是这些后缀串。
然后 suf[k] 取第 k 个后缀并输出前 min(m, len) 位


*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; i++)
#define ll long long
using namespace std;

constexpr int N = 220;

inline bool cmp(const string &a, const string &b) {
    rep(i,0,min(a.length(), b.length())-1) {//逐字符比较到两个串中较短者末尾
        if (a[i] == b[i]) continue;//相同则继续
        if (a[i] < b[i]) return 1;//a 的字符更小 → a 排在 b 前
        return 0;
    }
    return a.length() < b.length();//前缀相同 → 短的排前（标准字典序）
}

string ans;
int calc(const string &a) {
    int res = 0;
    rep(i,0,a.length()-1) {//枚举 a 中每个起点 i
        if (i+ans.length()-1 >= a.length()) break;//剩余长度不够放下 ans → 停止
        bool flg = 1;
        rep(j,0,ans.length()-1)//逐字符比较
            if (a[i+j] != ans[j]) flg = 0;//一旦不匹配，flg=0
        res += flg;//完全匹配则计数 +1
    }
    return res;
}

string pre[2], nxt[2], str[17];
ll d[N], h[N], mg[2][2], f[N];
int n;
ll solve() {
    int len = ans.length();//目标子串长度
    pre[0].clear(); pre[1].clear(); nxt[0].clear(); nxt[1].clear();//清空两段的前缀 清空两段的后缀
    d[14] = h[14] = 0; d[15] = h[15] = 1;
    //pre[i]：str[14]/str[15] 的"前缀+ans长度-1位"窗口
    rep(i,0,len-2) pre[0].push_back(str[14][i]), pre[1].push_back(str[15][i]);
    //nxt[i]：str[14]/str[15] 的"最后 len-1 位"后缀
    rep(i,1,len-1) nxt[0].push_back(str[14][str[14].length()-len+i]);
    rep(i,1,len-1) nxt[1].push_back(str[15][str[15].length()-len+i]);
    rep(i,0,1) rep(j,0,1) mg[j][i] = calc(nxt[j]+pre[i]);//mg[j][i]：跨段边界处新增的匹配数
    f[14] = calc(str[14]); f[15] = calc(str[15]);//初始 Fibonacci 项的直接计数
    rep(i,16,n) {//DP 递推
        //继承左右段的"类型"
        h[i] = h[i-1]; d[i] = d[i-2]; f[i] = f[i-1] + f[i-2];//匹配次数 = 左+右（近似）
        f[i] += mg[d[i]][h[i]];//加上跨段边界新增的匹配
        if (f[i] > 1e18) return f[i];//溢出保护
    }
    return f[n];
}

ll k;
int m;
string suf[N*10];
int main() {
    fast;
    cin >> n >> k >> m; str[0] = "0"; str[1] = "1";
    rep(i,2,15) str[i] = str[i-2] + str[i-1];
    if (n <= 15) {
        rep(i,0,str[n].length()-1) rep(j,i,str[n].length()-1)
            suf[i+1].push_back(str[n][j]);//收集所有子串（按起点分组放 suf）
        sort(suf+1, suf+str[n].length()+1, cmp);//字典序排序所有子串
        rep(i,0,min(m,(int)suf[k].length())-1) cout << suf[k][i];//输出第 k 个子串的前 m 位
        return 0;
    }
    rep(i,1,m) {//大 n 情况：贪心逐位构造
        ans.push_back('0');//先试当前位置放 0
        ll z = solve();//算放 0 时的总匹配计数
        if (z < k) { k -= z; ans.pop_back(); ans.push_back('1'); }//0 不够 → 改放 1
        if (k == 0) {//k 归零 → 已找到，输出
            rep(j,0,ans.length()-1) cout << ans[j];
            return 0;
        }
    }
    rep(i,0,ans.length()-1) cout << ans[i];//循环内没返回 → 输出已构造的前缀
    return 0;
}
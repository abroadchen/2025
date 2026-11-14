//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
双模数 + 随机底数的 pair 哈希
它们让 ii 能像普通 hash 一样直接用 +,-,* 组合
int lst=1;          // 当前自动机状态（上一个后缀指针），初始为根1
int len[N];         // 每个节点代表的最长回文串长度
int fa[N];          // fail（失配）指针
int ch[N][26];      // 转移边（26个字符）
int tot=1;          // 节点总数，节点0/1 是两根空后缀（len=-1/0）
int pos[N];         // pos[i] = 字符串第i位插入后所在的节点
int r[N];           // r[node] = 该节点代表回文在字符串中最右出现的结束位置
int anc[20][N];     // 倍增表，anc[0]=fail 链 → 用于快速跳最长回文后缀
extend(int n, int c) —— 单字符插入
新字符 s[n]，从当前节点沿 fail 上调，直到 s[n-len[p]-1] == s[n]（即 p 的前一个字符等于新字符，此时能形成一个更长的回文）
标准 PAM 插入，维护 fail（link）、长度、最右出现位置。
建出整串的 PAM，并预处理 fail 链的二进制倍增（用于之后快速求"长度≤某值的最大回文后缀"）
A, B：正串 a、b 的 PAM。
RA, RB：翻转后 a、b 的 PAM（用于判断"反转后是否仍是回文"、拼接回文判等
标准区间哈希：h[r] - h[l-1] * base^(r-l+1)，O(1) 取任意子串哈希（pair 版）

读入，建双哈希幂次与两个前缀哈希数组
A.tot-1 = a 中不同回文子串个数（去掉两个哨兵根），B.tot-1 同理。第一步：所有回文子串对的乘积，之后再减重叠
map_fa 存 a 的每种完整回文串哈希的出现次数；map_ga 存"满足 len[i] <= 2*len[fail]"时，去掉 fail 对应那一节后的剩余后缀哈希计数
map_fb：b 的完整回文串哈希计数。
map_gb：b 的"去 fail 节"后缀哈希计数
第一根大剪刀 —— 对某些由"较短回文+延长"构成的回文，它在之前被多算过 map_gb[hash] 次，这里扣除。
如果 l..r 本身已经是回文后缀，直接跳过后续去重（该类前面已处理）
若"翻转后仍满足延长条件"，且拼接出的回文串在 b 里存在 → 减去 1（去重）。continue 后走另一分支
用不同的拼接方式（lps vs lpp），同样若拼接串存在于 b，则 --ans。

这段整体就是在做"拼接去重"：很多回文是"某回文 + 反转"拼出来的，这类会在两串相乘时重复，需要用翻转自动机 + 拼接哈希精确判断并扣掉。
与 A 段完全对称：对 b 的每个回文节点做同型去重，用 map_ga/map_fa 那个方向。
重新统计"去 fail 节"哈希在两串各自的出现次数，然后按相同哈希值对应相乘累加进 ans——把真正两者相同的"剩余块"配对数加回来
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; i++)
#define ii pair<int, int>
#define ll long long
using namespace std;

constexpr int N = 2e5+10, p1 = 998244353, p2 = 998244853, base = 131;

ii operator+(const ii &a, const ii &b) { return {(a.first+b.first)%p1, (a.second+b.second)%p2}; }//两分量模加
ii operator-(const ii &a, const ii &b) { return {(a.first-b.first+p1)%p1, (a.second-b.second+p2)%p2}; }//模减（防负）
ii operator*(const ii &a, const ii &b) { return {1ll*a.first*b.first%p1, 1ll*a.second*b.second%p2}; }//哈希串相乘
ii operator*(const ii &a, int b) { return {1ll*a.first*b%p1, 1ll*a.second*b%p2}; }//哈希乘底数
ii operator+(const ii &a, int b) { return {(a.first+b)%p1, (a.second+b)%p2}; }//哈希加字符值

struct PAM {
    int lst = 1, len[N], fa[N], ch[N][26], tot = 1, pos[N], r[N], anc[20][N];
    char s[N];
    void extend(int n, int c) {
        int p = lst;
        while (s[n-len[p]-1] != s[n]) p = fa[p];
        if (!ch[p][c]) {//没有这个转移 → 新建节点
            int v = ++tot; len[v] = len[p] + 2;//新回文长度 = p长+2（两边各包一个新字符）
            int k = fa[p];//再从 p 的fail开始找 v 的fail
            while (s[n-len[k]-1] != s[n]) k = fa[k];
            //v 的fail = 从 k 跳出来的转移
            fa[v] = ch[k][c]; ch[p][c] = v;
        }
        //当前节点 = 转移后节点 记录第n位对应节点 该回文最右结束位置 = n
        lst = ch[p][c]; pos[n] = lst; r[lst] = n;
    }
    void build(char *t) {
        int n = strlen(t+1);
        rep(i,0,n+1) s[i] = t[i];//复制进内部数组
        fa[0] = fa[1] = 1, len[1] = -1;//两个空后缀根互相指（哨兵） 根1代表"长度-1"的空串（奇数回文根）
        rep(i,1,n) extend(i, s[i]-'a');//逐个字符构建
        rep(i,0,tot) anc[0][i] = fa[i];//倍增第0层 = fail
        rep(i,1,18) rep(j,0,tot) anc[i][j] = anc[i-1][anc[i-1][j]];// 预处理倍增表
    }
    int jump(int r, int l) {//返回位置 r 处、长度 ≤ l 的最长回文后缀的长度
        int u = pos[r];//位置 r 处的最长回文节点
        if (len[u] <= l) return len[u];//如果本身长度不超过l，直接返回（它就是最长符合的）
        for (int i = 18; ~i; i--) if (len[anc[i][u]] > l) u = anc[i][u];//沿倍增向上跳到仍 >l 的祖先
        return len[fa[u]];//最后一个仍>l的节点的 fail，其长度必 ≤ l 且最长
    }
    bool check(int r, int l) { return jump(r,l) == l; }//判断位置 r 是否存在长度恰好等于 l 的回文后缀
} A, B, RA, RB;

ii pw[N];
ii get(ii *h, int l, int r) { return h[r] - h[l-1] * pw[r-l+1]; }

char a[N], b[N];
ii ha[N], hb[N];
ll ans;
map<ii,int> fa, fb, ga, gb;
int main() {
    fast;
    scanf("%s", a + 1), scanf("%s", b + 1);
    int n = strlen(a + 1), m = strlen(b + 1); pw[0] = {1,1};
    for (int i = 1; i <= n || i <= m; i++) pw[i] = pw[i-1]*base;
    rep(i,1,n) ha[i] = ha[i-1]*base+(a[i]-'a'+1);//a 的前缀哈希
    rep(i,1,m) hb[i] = hb[i-1]*base+(b[i]-'a'+1);
    A.build(a), B.build(b);//a、b 的 PAM
    reverse(a+1, a+n+1); reverse(b+1, b+m+1);
    RA.build(a), RB.build(b);//翻转串的 PAM
    ans = 1ll*(A.tot-1)*(B.tot-1);//初始答案 = 两串回文数之积
    rep(i,2,A.tot) {//遍历 a 每个回文节点
        ++fa[get(ha,A.r[i]-A.len[i]+1, A.r[i])];//该回文子串[起点,终点]哈希记数
        int p = A.fa[i];//fail
        if (p < 2) continue;//跳过哨兵根
        //len[i] <= 2*len[fail] 记录"砍掉 fail 那一节"后剩余后缀的哈希
        if (A.len[i] <= A.len[p]<<1) ++ga[get(ha,A.r[i]-(A.len[i]-A.len[p])+1,A.r[i])];
    }
    rep(i,2,B.tot) {
        ++fb[get(hb, B.r[i] - B.len[i] + 1, B.r[i])];
        int p = B.fa[i];
        if(p < 2) continue;
        if(B.len[i] <= (B.len[p] << 1)) ++gb[get(hb, B.r[i] - B.len[i] + 1, B.r[i] - B.len[p])];
    }
    rep(i,2,A.tot) {
        int p = A.fa[i];
        if(p < 2) continue;
        // l..r = 节点i代表回文串中，去掉[开头]fail那一节后的... 实际上这里是:
        // 区间长度 = len[i]-len[p]（去掉fail那节剩余的长度）
        int l = A.r[i] - (A.len[i] - A.len[p]) + 1, r = A.r[i];
        ans -= gb[get(ha, l, r)];//减去"这个去fail节段也出现在b的g类型里"的重复计数
        int lps = A.jump(r, r - l + 1);//r处长度≤(r-l+1)的最长回文后缀
        if(lps == r - l + 1) continue;//若整个l..r本身是回文后缀 → 跳过(后面分支不适用)
        if(RA.check(n - l + 1, r - l + 1 - lps)) {
            // RA = 翻转后 a；n-l+1 对应翻转后下标。
            // check: 翻转后的位置是否有长度=(区间长-lps)的回文后缀
            //拼接 := [l,r]整段延长 [lps节] 拼接，若它在 b 里能作为某完整回文
            if(fb.contains(get(ha, l, r)*pw[r - l + 1 - lps] + get(ha, l, r - lps))) --ans;
            continue;
        }
        int lpp = RA.jump(n - l + 1, r - l + 1);
        if(A.check(r, r - l + 1 - lpp)) { if(fb.count(get(ha, l, r)*pw[lpp] + get(ha, l, l + lpp - 1))) --ans; }
    }
    rep(i,2,B.tot) {
        int p = B.fa[i];
        if(p < 2) continue;
        int l = B.r[i] - B.len[i] + 1, r = B.r[i] - B.len[p];
        ans -= ga[get(hb, l, r)];
        int lps = B.jump(r, r - l + 1);
        if(lps == r - l + 1) continue;
        if(RB.check(m - l + 1, r - l + 1 - lps)) {
            if(fa.count(get(hb, r - lps + 1, r)*pw[r - l + 1] + get(hb, l, r))) --ans;
            continue;
        }
        int lpp = RB.jump(m - l + 1, r - l + 1);
        if(B.check(r, r - l + 1 - lpp)) { if(fa.count(get(hb, l + lpp, r)*pw[r - l + 1] + get(hb, l, r))) --ans; }
    }
    ga.clear(), gb.clear();
    rep(i,2,A.tot) {
        int p = A.fa[i];
        if(p < 2) continue;
        ++ga[get(ha, A.r[i] - (A.len[i] - A.len[p]) + 1, A.r[i])];
    }
    rep(i,2,B.tot) {
        int p = B.fa[i];
        if(p < 2) continue;
        ++gb[get(hb, B.r[i] - B.len[i] + 1, B.r[i] - B.len[p])];
    }
    for (auto [fst, snd] : ga) ans += 1ll*snd*gb[fst];
    cout << ans;
    return 0;
}
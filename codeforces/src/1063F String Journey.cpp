//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
标准 SAM 在线插入：cur 为新状态，len 为状态对应最长串长度，fa（link）指向后缀链接。
含经典的 q 分裂（c=++tot 复制 q）操作。
用的是 a[p].ch[x] 转移
读入 n 和字符串，反转字符串后建 SAM。reverse 是这类"后缀前缀互转"题目的常见处理
双指针（用 k 表示窗口大小）配合 SAM 状态推进：

now、l、r 三个 SAM 节点对应窗口的"状态"，随 k 增减、i 前进而沿 SAM 转移移动。
o[]（是否访问过）与 g[]（某状态的某种阈值/最长值）用于 chk() 判断窗口是否"合法"。
upd 沿 fa 链标记访问；go(j) 记录位置 j 的信息。
不足时 --k 缩小窗口并回退 SAM 状态，f[i]=k 记下位置 i 的最优窗口大小
对每个位置取最优的 k（窗口大小），输出最大值

N = 5e5+10：字符串最大长度+缓冲。
node：SAM 的一个状态（节点）。
ch[26]：该状态的转移（transitions），ch[c] 表示读入字符 c 后跳转到的状态（0 表示无该转移）。
len：该状态代表的所有字符串中最长的那个的长度。
fa（link，后缀链接）：指向该状态"最长真后缀"所在的状态。
a[N<<1]：SAM 节点数组，开辟两倍空间（SAM 节点数 ≤ 2n-1）
tot: 已建节点数; lst: 最后插入的节点(用于在线构建)
cur：新建一个状态代表"整个新串"。
当前串比上一个多一个字符，所以 len 递推 +1。
lst 更新为 cur。
从 lst 沿 fa（后缀链接）向上走。
对每个"还没有 x 转移"的祖先，把它们指向 x 的转移设为 cur。
直到遇到一个已有 x 转移的祖先 p，或走到根（p==0）为止
情况A（p==0）：走到了根，说明所有前缀转移都指向 cur，则 cur.fa = 根。
情况B：q.len == p.len+1 恰好符合后缀关系，直接 cur.fa = q。
情况C：q.len > p.len+1，q 同时代表多个长度，需要分裂出状态 c 复制 q，调整链接并重定向转移。

now：指向窗口末尾字符对应的 SAM 状态 = 根沿第一个字符转移。
l、r：双指针的左右两端对应的 SAM 状态，初始都为根（状态 1）
i：当前处理到的右端点位置。
k：当前窗口大小（尝试扩展的步长）。
p[i]：存下位置 i 对应的 SAM 状态，供后续 go 使用
判定 lambda chk：判断当前窗口 [i-k, i] 是否与已覆盖部分"冲突"。
o[x]：状态 x 是否已被访问过。
g[x]：状态 x 在滑动中累计的某种"步数/长度"值。
只要 l 或 r 的一端访问过、或某端的 g 值达到 k-1，就认为该窗口不合法（需要收缩）
upd：从状态 x 开始，沿 fa（后缀链接）向上递归标记 o[x]=1。
作用：把某个状态及其所有后缀祖先标记为"已覆盖/已访问"。
递归到 x==0（越界）或已访问过则停止
go：处理下标 j 处的状态信息。
取 p[j]（j 对应的 SAM 状态 x）。
g[x] = max(g[x], f[j]) 更新状态 x 的长度记录。
upd(a[x].fa)：沿 x 的后缀链标记访问
当 chk() 为真（冲突）且 k>1 时，收缩窗口：
--k 减小窗口长度。
随着窗口变小，SAM 状态可能需沿 fa 上移缩短串（由 len 判断是否恰好为想保留的长度）。
go(i-k) 处理刚被移出窗口的位置 i-k，把它标记为已覆盖
f[i]=k：记录位置 i 的最优可扩展长度 k。
i+1 右移、k+1 尝试更大窗口。
now、r 接收下一个字符 s[i] 的转移；l 接收字符 s[i-1] 的转移，维持窗口两端状态
遍历所有位置，取 f[i] 的最大值作为答案输出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 5e5+10;

struct node { int ch[26], len, fa; } a[N<<1];

int tot(1), lst(1);
void ins(int x) {//x: 要插入的字符(0~25)
    //新状态 len = 原来最后状态 len + 1
    int cur = ++tot, p = lst; a[cur].len = a[lst].len + 1; lst = cur;//更新 lst 为新状态
    for (; p && !a[p].ch[x]; p = a[p].fa) a[p].ch[x] = cur;
    if (!p) a[cur].fa = 1;//情况A: 一路上到根, cur 的 fa 设为根(1号)
    else {
        int q = a[p].ch[x];//q: p 沿 x 能到的状态
        if (a[q].len == a[p].len + 1) a[cur].fa = q;//情况B: 直接连
        else {//情况C: 需要分裂 q → c
            int c = ++tot; a[c] = a[q]; a[c].len = a[p].len + 1; a[q].fa = a[cur].fa = c;
            for (; p && a[p].ch[x] == q; p = a[p].fa) a[p].ch[x] = c;
        }
    }
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<class T>
T chkmax(T &x, T y) { return x = x > y ? x : y; }

int n, p[N], o[N<<1], g[N<<1], f[N], ans;
char s[N];
int main() {
    fast;
    read(n); scanf("%s", s+1); reverse(s+1, s+n+1);
    for (int i = 1; i <= n; i++) ins(s[i]-'a');
    int l = 1, r = 1, now = a[1].ch[s[1]-'a'];
    for (int i = 1, k = 1; i <= n; ) {
        p[i] = now;
        auto chk = [&]() {
            return o[l] || o[r] || g[l] >= k-1 || g[r] >= k-1;
        };
        function<void(int)> upd = [&](int x) {
            if (x == 0 || o[x]) return;
            o[x] = 1; upd(a[x].fa);
        };
        auto go = [&](int j) {
            int x = p[j]; chkmax(g[x], f[j]);
            upd(a[x].fa);
        };
        while (k > 1 && !chk()) {
            --k;
            if (a[a[now].fa].len == k) now = a[now].fa;//now 沿 fa 上移
            if (a[a[l].fa].len == k-1) l = a[l].fa;//l 上移
            if (a[a[r].fa].len == k-1) r = a[r].fa;//r 上移
            go(i-k);//处理被"让出"的位置
        }
        f[i] = k; ++i; ++k;//记录最优 k, 指针前进
        if (i > n) break;
        //now 沿新字符转移 r 沿新字符转移 l 沿新字符转移
        now = a[now].ch[s[i]-'a']; r = a[r].ch[s[i]-'a']; l = a[l].ch[s[i-1]-'a'];
    }
    for (int i = 1; i <= n; i++) chkmax(ans, f[i]);
    cout << ans << '\n';
    return 0;
}
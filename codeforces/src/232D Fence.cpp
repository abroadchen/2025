//
// Created by Psy.C on 2025/12/10.
//
/*
*c[N]: 计数数组，用于基数排序
n: 字符串长度
rk[N]: rank数组，rk[i]表示后缀i在所有后缀中的排名
s[N]: 原始字符串数组
sa[N]: suffix array，sa[i]表示排名第i的后缀起始位置
trk[N]: 临时rank数组
tsa[N]: 临时suffix array
h[N]: height数组，h[i]表示sa[i]和sa[i-1]的最长公共前缀长度
 *
*基数排序构造初始后缀数组：
初始化计数数组
给每个字符分配rank
计算前缀和
根据rank排序得到sa数组
  */
#include <iostream>
#include <algorithm>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200005
#define rep(i,n) for(int i=1;i<=n;++i)
#define lb(x) (x&(-x))
using namespace std;

constexpr int inf = 1e9;

int c[N], n, rk[N], s[N], sa[N], trk[N], tsa[N], h[N];
void get(int mx=256) {//构造后缀数组 mx是字符集大小
    int p;//不同的rank值数量
    for (int i = 0; i <= mx; ++i) c[i] = 0;//计数数组
    rep(i,n) c[(rk[i] = s[i])]++;//对每个位置i，将s[i]作为初始rank值赋给rk[i]，并在c数组中计数
    for (int i = 2; i <= mx; ++i) c[i] += c[i-1];//计算计数数组的前缀和，用于基数排序
    for (int i = n; i; --i) sa[c[rk[i]]--] = i;//从后往前扫描，根据rank值将后缀位置放入sa数组（稳定排序）
    trk[sa[1]] = p = 1;//更新rank数组，处理相同字符的情况 初始化第一个后缀的临时rank为1，p记录rank种类数
    for (int i = 2; i <= n; ++i) {//遍历排序后的后缀
        if (rk[sa[i]] != rk[sa[i-1]]) p++;//当前后缀与前一个后缀的rank不同，rank种类数p增加
        trk[sa[i]] = p;//给当前后缀分配新的临时rank值
    }
    rep(i,n) rk[i] = trk[i];//将临时rank数组复制回正式rank数组
    for (int k = 1; p < n; k <<= 1, mx = p) {//倍增过程，k是当前比较的长度 当rank种类数<p时继续 mx更新为当前rank种类数
        p = 0;//构造新的sa数组 重置rank种类计数器
        for (int i = n - k + 1; i <= n; ++i) tsa[++p] = i;//长度不足k的后缀 放入临时sa数组开头
        rep(i,n) if (sa[i] > k) tsa[++p] = sa[i] - k;//其他后缀 与其前k个字符组成的后缀一起排序
        for (int i = 0; i <= mx; ++i) c[i] = 0;//基数排序 清空计数数组
        rep(i,n) trk[i] = rk[tsa[i]];//根据临时sa数组中的位置，获取对应的rank值存入临时rank数组
        rep(i,n) c[trk[i]]++;//对临时rank值进行计数
        for (int i = 2; i <= mx; ++i) c[i] += c[i-1];//计算前缀和
        for (int i = n; i; --i) sa[c[trk[i]]--] = tsa[i];//根据临时rank值对临时sa数组进行稳定排序，结果存入sa数组
        trk[sa[1]] = p = 1;//更新rank数组 重新初始化rank计数器
        for (int i = 2; i <= n; ++i) {
            if (rk[sa[i]] != rk[sa[i-1]] ||
                rk[sa[i]+k] != rk[sa[i-1]+k]) p++;//前k个字符或后k个字符上不同
            trk[sa[i]] = p;//分配新的rank值
        }
        rep(i,n) rk[i] = trk[i];//更新正式rank数组
    }
    for (int i = 1, k = 0; i <= n; ++i) {//计算height数组
        const int j = sa[rk[i]-1];//找到其在sa中的前一个后缀j
        while (s[i+k] == s[j+k]) k++;//计算这两个后缀的最长公共前缀长度k
        h[rk[i]] = k;//存入h[rk[i]]
        if (k > 0) k--;//由于相邻后缀的LCP长度通常相似，k可以复用（k--优化）
    }
}
//ST表，f[i][j]表示从位置i开始长度为2^j的区间的最小值
int f[N][20], lg[N];//预处理log值
void rmq() {//O(1)查询区间最小值
    rep(i,n) f[i][0] = h[i];//初始化ST表第一列
    for (int i = 2; i <= n; ++i) lg[i] = lg[i>>1] + 1;//预处理log值：lg[i] = floor(log2(i))
    //构建ST表 将区间分为两半，取两半最小值的较小者 对于每个区间长度2^j
    rep(j,lg[n]) for (int i = 1; i + (1<<j) - 1 <= n; ++i) {
        f[i][j] = min(f[i][j-1], f[i + (1<<(j-1))][j-1]);
    }
}

struct node { int l, r, id; } st[N];//查询节点
int ans[N];
void add(const int x, const int v) {
    for (int i = x; i <= n; i += lb(i)) ans[i] += v;//沿着lowbit路径向上更新
}
int sum(const int x) {//查询[1,x]区间和
    int res = 0;
    for (int i = x; i; i -= lb(i)) res += ans[i];//沿着lowbit路径向下累加
    return res;
}

int query(const int l, const int r) {//RMQ查询区间[l,r]的最小值
    const int k = lg[r - l + 1];
    return min(f[l][k], f[r-(1<<k)+1][k]);//用ST表查询两个重叠区间的最小值
}
//在sa数组中查找LCP长度≥k的区间
int find(const int pos, const int k) {//查找满足条件的区间并计算树状数组区间和
    int tl = pos + 1, tr = pos - 1,//目标区间的左右边界
    l = pos + 1, r = n, mid;//二分查找的范围
    while (l <= r) {//向右二分查找最远的满足条件位置
        mid = (l + r) >> 1;
        if (query(pos + 1, mid) >= k) l = mid + 1, tr = mid;
        else r = mid - 1;
    }
    l = 1; r = pos;//重置二分范围，向左查找
    while (l <= r) {//向左二分查找最近的满足条件位置
        mid = (l + r) >> 1;
        if (query(mid + 1, pos) >= k) r = mid - 1, tl = mid;
        else l = mid + 1;
    }
    return sum(tr) - sum(tl-1);//树状数组区间和查询结果[tl,tr]
}

int main() {
    fast;
    int m, a[N], res[N], q; cin>>m;
    rep(i,m) cin>>a[i];//读入原数组元素
    rep(i,m-1) s[i] = a[i+1] - a[i]; s[m] = inf;//构造差分数组作为字符串，最后添加inf作为分隔符
    rep(i,m-1) s[i+m] = -s[i];//添加差分数组的相反数
    n = (m << 1) - 1;//总长度：2*m-1
    memcpy(a, s, (n + 1) << 2);//离散化处理（<<2是因为int占4字节）
    sort(a + 1, a + n + 1);
    const int cnt = static_cast<int>(unique(a + 1, a + n + 1) - a - 1);//不同值的个数
    rep(i,n) s[i] = static_cast<int>(lower_bound(a + 1, a + cnt + 1, s[i]) - a);//离散化：将原值映射为排名
    get(cnt); rmq();
    cin >> q;
    rep(i,q) {
        cin >> st[i].l >> st[i].r;
        st[i].r -= st[i].l; st[i].id = i;//将区间[l,r]转换为起点l和长度r-l 记录查询编号
    }
    sort(st + 1, st + q + 1, [](const node& aa, const node& b) {
        return aa.l + aa.r < b.l + b.r;//按l+r排序查询
    });
    for (int j = m - 1, i = q; i; --i) {
        for (; j > 1 && j > st[i].l + st[i].r; --j) add(rk[j+m], 1);//动态维护树状数组
        res[st[i].id] += find(rk[st[i].l], st[i].r);//查询满足条件的后缀数量
    }
    sort(st + 1, st + q + 1, [](const node& aa, const node& b) {
        return aa.l - aa.r < b.l - b.r;//按l-r重新排序查询
    });
    memset(ans, 0, (n + 1) << 2);//清空树状数组
    for (int j = 1, i = 1; i <= q; ++i) {//第二轮处理查询
        for (; j < m && j + st[i].r < st[i].l; ++j) add(rk[j+m], 1);
        res[st[i].id] += find(rk[st[i].l], st[i].r);
        if (!st[i].r) res[st[i].id] = m - 1;
    }
    rep(i,q) cout << res[i] << '\n';
    return 0;
}
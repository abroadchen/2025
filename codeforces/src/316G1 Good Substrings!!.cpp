//
// Created by Psy.C on 2026/1/6.
//
/**
*len 存储字符串总长度
a[N] 存储字符串的字符转为数字后的数组
ord 用于分配新字符的ASCII值
 *
*cnt[] 计数数组
sa[i] 排名第i的后缀的起始位置
rk[i] 起始位置为i的后缀的排名
ht[i] 排名相邻的两个后缀的最长公共前缀长度
st[20][N] ST表用于RMQ查询
lg[N] 预计算的log值
p[], tmp[] 排序用的临时数组
 *
 *init() 方法：基数排序初始化，对单字符进行排序
 *sort() 方法：倍增法构建后缀数组，逐步增加比较长度
 *height() 方法：计算height数组，即相邻排名后缀的最长公共前缀
 *get() 方法：构建ST表，用于快速查询区间最小值
 *lcp() 方法：查询两个排名相邻后缀的最长公共前缀长度
*ok() 函数：检查以id位置开始，长度为x的子串是否满足上界条件
使用二分查找找到满足LCP≥x的区间[al,ar]
检查每个模式串在该区间内的出现次数是否不超过上界
 *ok2() 函数：检查下界条件，每个模式串在区间内的出现次数是否不小于下界
 *
*读入主字符串和模式串数量
将主字符串转为数字数组，并添加分隔符
*读入每个模式串及其出现次数范围
将所有模式串添加到数组中，用不同分隔符分隔
*构建后缀数组相关数据结构
tag[i] 标记排名为i的后缀是否来自原主字符串
 *构建前缀和数组，统计每个模式串在各位置的出现次数
*对每个来自主串的后缀进行处理
使用二分查找确定满足上下界条件的长度范围
累加符合条件的子串数量
 *
*从位置 j 开始，长度为 2^i 的区间的右端点：
区间起始位置：j
区间长度：2^i（即 1 << i）
区间结束位置：j + (1 << i) - 1
*长度为 2^i 的区间 [j, j+2^i-1] 可以分解为：
区间 1：[j, j+2^(i-1)-1] （前半部分）
区间 2：[j+2^(i-1), j+2^i-1] （后半部分）
 *
 */
#include <iostream>
#include <cmath>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 500005
#define rep(i,n) for (int i=1; i<=n; ++i)
#define sz(x) (static_cast<int>((x).size()))
#define ii pair<int, int>
using namespace std;

int len, a[N], ord='z';
struct node {
    int cnt[N]{}, sa[N]{}, rk[N]{}, ht[N]{}, st[20][N]{}, lg[N]{};
    pair<ii, int> p[N], tmp[N];
    void init() {
        memset(cnt, 0, sizeof(cnt));
        rep(i,len) ++cnt[a[i]];//统计每个字符出现的次数
        rep(i,ord) cnt[i] += cnt[i - 1];//计算前缀和，得到计数排序的边界
        rep(i,len) rk[i] = cnt[a[i] - 1] + 1;//根据计数排序结果计算初始排名
    }
    void sort() {
        for (int l = 1, id; l <= len; l <<= 1) {//l 为当前比较的长度
            //构造排序对，包含当前和后l位置的排名，以及原始位置
            rep(i,len) p[i] = {{rk[i], i + l > len ? 0 : rk[i + l]}, i};
            memset(cnt, id=0, sizeof(cnt));
            rep(i,len) ++cnt[p[i].first.second];//对第二关键字进行基数排序（后 l 个字符的排名）
            rep(i,len) cnt[i] += cnt[i - 1];
            for (int i = len; i >= 1; --i) tmp[cnt[p[i].first.second]--] = p[i];
            //从后往前遍历，保证了相同关键字的元素保持原有相对顺序
            //计数减 1 确保下一个相同关键字的元素被放置到前一个位置
            rep(i,len) p[i] = tmp[i];
            memset(cnt, 0, sizeof(cnt));
            rep(i,len) ++cnt[p[i].first.first];//对第一关键字进行基数排序（前 l 个字符的排名）
            rep(i,len) cnt[i] += cnt[i - 1];
            for (int i = len; i >= 1; --i) tmp[cnt[p[i].first.first]--] = p[i];
            rep(i,len) p[i] = tmp[i];
            rep(i,len) {//根据排序结果更新排名数组
                if (i == 1 || p[i].first != p[i - 1].first) ++id;
                rk[p[i].second] = id;
            }
            if (id == len) break;//所有后缀都有唯一排名，则结束排序
        }
        rep(i,len) sa[rk[i]] = i;//根据排名数组构建后缀数组
    }
    void height() {
        for (int i = 1, k = 0; i <= len; ++i) {
            if (rk[i] == 1) { ht[i] = k = 0; continue; }
            if (k) --k;//k 值至少为 k-1
            int j = sa[rk[i] - 1];//获取排名前一位的后缀的起始位置
            while (i + k <= len && j + k <= len && a[i + k] == a[j + k]) ++k;//公共前缀长度
            ht[i] = k;//保存 height 值
        }
    }
    void get() {
        rep(i,len) st[0][i] = ht[sa[i]], lg[i] = __lg(i);
        for (int i = 1; 1<<i <= len; ++i) {
            for (int j = 1; j + (1<<i) - 1 <= len; ++j)
                st[i][j] = min(st[i-1][j], st[i-1][j+(1<<(i-1))]);
        }
    }
    int lcp(int l, const int r) const {
        if (l == r) return len - sa[l] + 1;//两个位置相同，返回后缀长度
        ++l;//ST 表从排名 2 开始计算
        const int k = lg[r - l + 1];//区间长度的 log 值
        return min(st[k][l], st[k][r-(1<<k)+1]);//区间最小值
    }
} sf;

int n, sum[11][N], qr[N];
bool ok(const int id, const int x) {//从排名为 id 的后缀开始，长度为 x 的子串是否满足条件
    int l = 1, r = id, al = 0, ar = 0;
    while (l <= r) {//二分查找左边界 找到最大的 l 使得 LCP(l, id) >= x
        const int mid = (l + r) >> 1;
        if (sf.lcp(mid, id) >= x) al = mid, r = mid - 1; else l = mid + 1;
    }
    l = id, r = len;
    while (l <= r) {//二分查找右边界：找到最小的 r 使得 LCP(id, r) >= x
        const int mid = (l + r) >> 1;
        if (sf.lcp(id, mid) >= x) ar = mid, l = mid + 1; else r = mid - 1;
    }
    //每个模式串在区间 [al, ar] 内的出现次数是否超过上界
    rep(i,n) if (sum[i][ar] - sum[i][al - 1] > qr[i]) return false;
    return true;
}

int ql[N];
bool ok2(const int id, const int x) {
    int l = 1, r = id, al = 0, ar = 0;
    while (l <= r) {
        const int mid = (l + r) >> 1;
        if (sf.lcp(mid, id) >= x) al = mid, r = mid - 1; else l = mid + 1;
    }
    l = id, r = len;
    while (l <= r) {
        const int mid = (l + r) >> 1;
        if (sf.lcp(id, mid) >= x) ar = mid, l = mid + 1; else r = mid - 1;
    }
    //每个模式串在区间内的出现次数是否不低于下界
    rep(i,n) if (sum[i][ar] - sum[i][al - 1] < ql[i]) return false;
    return true;
}

int main() {
    fast;
    //k 存储主字符串长度，siz 存储模式串长度，hd 存储模式串在数组中的起始位置
    string s; int k, siz[N], hd[N];
    cin >> s >> n; len = k = sz(s);
    rep(i,len) a[i] = static_cast<unsigned char>(s[i - 1]);
    a[++len] = ++ord;//添加分隔符，增加长度
    rep(i,n) {
        cin >> s >> ql[i] >> qr[i];//读入每个模式串及其上下界
        siz[i] = sz(s); hd[i] = len + 1;
        for (int j = 0; j < siz[i]; ++j) a[++len] = static_cast<unsigned char>(s[j]);
        for (int j = len; j > len - siz[i]; --j) a[++len] = ++ord;
    }
    sf.init(); sf.sort(); sf.height(); sf.get();
    bool tag[N];
    rep(i,len) if (sf.sa[i] <= k) tag[i] = true;//标记来自原主字符串的后缀
    rep(i,n) for (int j = hd[i]; j < hd[i] + siz[i]; ++j) sum[i][sf.rk[j]] = 1;//在排名位置标记模式串出现
    rep(i,len) rep(j,n) sum[j][i] += sum[j][i-1];//构建前缀和数组
    ll ans = 0;
    for (int i = 1, la = 0; i <= len; ++i) {//遍历所有后缀
        if (!tag[i]) continue;//跳过不属于原主字符串的后缀
        int l = (la ? sf.lcp(la, i) : 0) + 1, //计算最小可能长度（考虑与前一个后缀的公共前缀）
        r = k - sf.sa[i] + 1;//计算最大可能长度（后缀的剩余长度）
        int al = -1, ar = -1;
        while (l <= r) {//二分查找满足上界条件的最短长度
            const int mid = (l + r) >> 1;
            if (ok(i, mid)) al = mid, r = mid - 1; else l = mid + 1;
        }
        l = (la ? sf.lcp(la, i) : 0) + 1, r = k - sf.sa[i] + 1; la = i;
        while (l <= r) {//二分查找满足下界条件的最长长度
            const int mid = (l + r) >> 1;
            if (ok2(i, mid)) ar = mid, l = mid + 1; else r = mid - 1;
        }
        if (al == -1 || ar == -1) continue;//找不到满足条件的长度则跳过
        if (al > ar) continue;//最小长度大于最大长度则跳过
        ans += ar - al + 1;//累加满足条件的子串数量
    }
    cout << ans;
    return 0;
}
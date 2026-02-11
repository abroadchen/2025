//
// Created by Psy.C on 2026/2/11.
//
/**
时间复杂度
预处理：O(n log n)
初始化树状数组：O(n log n)
主循环：O(n log n)
总体：O(n log n)
空间复杂度
O(n)：存储数组和树状数组

逆序对变种问题
计算有多少对(i,j)，其中i < j，且在区间[i+1,j]中a[j]的出现次数 > 在区间[1,i]中a[i]的出现次数
 */
#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define N 1000005
using namespace std;

struct BIT {
    static constexpr int mx = N;
    int tr[mx];
    static int low_bit(const int x) { return x&-x; }//树状数组索引计算
    void add(const int idx, const int x) {//在位置idx增加x
        for (int pos = idx; pos < mx; pos += low_bit(pos))
            tr[pos] += x;
    }
    [[nodiscard]] int query(const int n) const {//查询前n项的前缀和
        int ans = 0;
        for (int pos = n; pos; pos -= low_bit(pos))
            ans += tr[pos];
        return ans;
    }
    [[nodiscard]] int query(const int a, const int b) const {//查询区间[a,b]的和
        return query(b) - query(a - 1);
    }
    void init(const int n) {
        for (int i = 0; i <= n+2; ++i) tr[i] = 0;
    }
} tree;

int n, a[N], num[N];//每个位置上元素的出现次数
void out() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    map<int, int> mp;
    for (int i = n; i >= 1; --i) {
        mp[a[i]]++;
        num[i] = mp[a[i]];//a[i]在区间[i,n]中的出现次数
    }
    for (int i = 1; i <= n; ++i) tree.add(num[i], 1);//将所有num[i]插入树状数组
    map<int, int> st;
    int ans = 0;
    for (int i = 1; i < n; ++i) {
        tree.add(num[i], -1);//从树状数组中移除num[i]
        st[a[i]]++;//统计a[i]在区间[1,i]中的出现次数
        const int op = st[a[i]];
        ans += tree.query(op - 1);//小于op的元素个数
    }
    cout << ans << '\n';
}

signed main() {
    fast;
    out();
    return 0;
}
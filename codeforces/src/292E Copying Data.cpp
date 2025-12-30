/**
 *
*M：用于存储大于等于n的最小2的幂（线段树的起始位置）
tag[N<<1]：懒惰标记数组，大小为2*N，用于区间更新的标记传播
 *
*update(l, r, k)：将区间[l,r]标记为k
l = l + M - 1, r = r + M + 1：将区间映射到线段树的叶子节点位置
l ^ r ^ 1：判断l和r是否相邻（当l^r==1时循环结束）
~l & 1：检查l是否为偶数，如果是偶数则tag[l^1] = k
r & 1：检查r是否为奇数，如果是奇数则tag[r^1] = k
l >>= 1, r >>= 1：向上移动到父节点
 *
*b[N], a[N]：两个输入数组
pa[N], pb[N]：记录操作参数的数组
query(x)：查询位置x的值
从叶子节点x+M开始向上遍历，收集所有标记
返回最大标记对应的操作结果
 *
*对于区间[y, y+k-1]中的任意位置tx：

tx在目标区间中的偏移量 = tx - y
该偏移量对应的源数组位置 = x + (tx - y)
即：a[x + tx - y] → b[tx]
用我们的变量表示：

x = pa[i] (源起始位置)
y = pb[i] (目标起始位置)
tx = 查询位置
所以：a[pa[i] + tx - pb[i]] → b[tx]
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200005
using namespace std;

int M, tag[N<<1];
void update(int l, int r, const int k) {
    for (l = l + M - 1, r = r + M + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
        if (~l & 1) tag[l^1] = k;
        if (r & 1) tag[r^1] = k;
    }
}

int b[N], a[N], pa[N], pb[N];
int query(int x) {
    int mx = 0;
    const int tx = x;
    x = x + M;//将x映射到线段树叶子节点
    while (x) {//向上遍历到根节点
        mx = max(mx, tag[x]);
        x >>= 1;//移动到父节点
    }
    if (mx == 0) return b[tx];//返回b数组对应值
    return a[pa[mx] + tx - pb[mx]];//b数组中位置tx的值来源于a数组中的哪个位置
}



int main() {
    fast;
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    for (M = 1; M < n; M <<= 1) {}//大于等于n的最小2的幂
    for (int i = 1, t, x, y, k; i <= m; ++i) {
        cin >> t;
        if (t == 1) {
            cin >> x >> y >> k;//x(源位置), y(目标位置), k(长度)
            update(y, y + k - 1, i);//在目标区间[y, y+k-1]打上标记i
            pa[i] = x; pb[i] = y;//记录操作i的参数
        } else {
            cin >> x;//读入查询位置
            cout << query(x) << '\n';
        }
    }
    return 0;
}
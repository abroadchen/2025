//
// Created by Psy.C on 2025/12/20.
//
/*
 *hsx数组存储x坐标的离散化值，tx是有效元素个数
 *g是每个节点的向量数组，用于存储y坐标
 *更新线段树：将点(x,y)插入到对应的节点中
 *对每个节点内的y坐标进行排序
*查询在矩形区域[x1,x2]×[y1,y2]内的点数
利用二分查找统计y坐标在[y1,y2]范围内的点数
 *提供对外查询接口
 *将整数转换为带小数点的格式输出
 *
 *乘以2是为了处理半整数坐标
 *将坐标值存入离散化数组
 *读入9个数字
 *对坐标数组进行排序和去重，完成离散化
*将所有点插入线段树
统计前缀和数组
 *对线段树内数据进行排序
 *计算前缀和
 *对9个数字进行全排列枚举
 *计算各行各列的总和
 *根据行和查找对应的x坐标分割线
 *根据列和查找对应的y坐标分割线
 *验证四个角区域的点数是否符合要求
 *如果找到符合条件的解，输出结果并退出
 *
*lower_bound(hsx + 1, hsx + tx + 1, x[i])：

在已排序的数组hsx中搜索x[i]应该插入的第一个位置，以保持数组顺序
搜索范围：从hsx[1]到hsx[tx]（因为hsx + 1指向索引1，而hsx + tx + 1指向最后一个元素的下一个位置）
返回指向找到位置的指针
lower_bound(...) - hsx：

将lower_bound返回的指针转换为数组索引
由于hsx是数组的基地址，减去它就得到了实际的索引值
 */
#include <iostream>
#include <algorithm>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200007
using namespace std;

int hsx[N], tx;
struct sgt {
    vector<int> g[N<<2];
    void update(const int x, const int y, const int l, const int r, const int rt) {
        g[rt].push_back(y);
        if (l == r) return;
        const int mid = (l + r) >> 1;
        if (x <= hsx[mid]) update(x, y, l, mid, rt<<1);
        else update(x, y, mid+1, r, rt<<1|1);
    }
    void dfs(const int l, const int r, const int rt) {
        sort(g[rt].begin(), g[rt].end());
        if (l == r) return;
        const int mid = (l + r) >> 1;
        dfs(l, mid, rt<<1); dfs(mid+1, r, rt<<1|1);
    }
    int query(const int x1, const int x2, const int y1, const int y2, const int l, const int r, const int rt) {
        if (hsx[l] > x2 || hsx[r] < x1 || x1 > x2 || y1 > y2) return 0;
        if (x1 <= hsx[l] && hsx[r] <= x2) {
            return static_cast<int>(upper_bound(g[rt].begin(), g[rt].end(), y2) -
                lower_bound(g[rt].begin(), g[rt].end(), y1));
        }
        const int mid = (l + r) >> 1;
        return query(x1, x2, y1, y2, l, mid, rt<<1) +
            query(x1, x2, y1, y2, mid+1, r, rt<<1|1);
    }
    int get(const int x1, const int x2, const int y1, const int y2) {
        return query(x1, x2, y1, y2, 1, tx, 1);
    }
} tr;

void out(const int x) {
    if (x & 1) cout << x / 2 << ".5";
    else cout << x / 2 << ".0";
}

constexpr int inf = 2000000010;

int main() {
    fast;
    int n, x[N], y[N], hsy[N], ty = 0, a[N], prex[N], prey[N];
    cin>>n;
    for (int i = 1; i <= n; ++i) {
        cin>>x[i]>>y[i];
        x[i] *= 2; y[i] *= 2;
        hsx[++tx] = x[i];
        hsy[++ty] = y[i];
    }
    for (int i = 1; i <= 9; ++i) cin>>a[i];
    sort(hsx + 1, hsx + tx + 1);
    tx = static_cast<int>(unique(hsx + 1, hsx + tx + 1) - hsx - 1);
    sort(hsy + 1, hsy + ty + 1);
    ty = static_cast<int>(unique(hsy + 1, hsy + ty + 1) - hsy - 1);
    for (int i = 1; i <= n; ++i) {
        tr.update(x[i], y[i], 1, tx, 1);
        prex[lower_bound(hsx + 1, hsx + tx + 1, x[i]) - hsx]++;//将连续坐标映射到离散索引
        prey[lower_bound(hsy + 1, hsy + ty + 1, y[i]) - hsy]++;
    }
    tr.dfs(1, tx, 1);
    for (int i = 1; i <= tx; ++i) prex[i] += prex[i-1];
    for (int i = 1; i <= ty; ++i) prey[i] += prey[i-1];
    sort(a + 1, a + 10);
    do {
        const int r1 = a[1] + a[2] + a[3], r2 = a[4] + a[5] + a[6],
        r3 = a[7] + a[8] + a[9], c1 = a[1] + a[4] + a[7],
        c2 = a[2] + a[5] + a[8], c3 = a[3] + a[6] + a[9];
        int px = static_cast<int>(lower_bound(prex + 1, prex + 1 + tx, r1) - prex);
        if (px > tx || prex[px] != r1) continue;
        const int x1 = hsx[px] + 1;
        px = static_cast<int>(lower_bound(prex + 1, prex + 1 + tx, r1 + r2) - prex);
        if (px > tx || prex[px] != r1 + r2) continue;
        const int x2 = hsx[px] + 1;
        px = static_cast<int>(lower_bound(prex + 1, prex + 1 + tx, r1 + r2 + r3) - prex);
        if (px > tx || prex[px] != r1 + r2 + r3) continue;
        int py = static_cast<int>(lower_bound(prey + 1, prey + 1 + ty, c1) - prey);
        if (py > ty || prey[py] != c1) continue;
        const int y1 = hsy[py] + 1;
        py = static_cast<int>(lower_bound(prey + 1, prey + 1 + ty, c1 + c2) - prey);
        if (py > ty || prey[py] != c1 + c2) continue;
        const int y2 = hsy[py] + 1;
        py = static_cast<int>(lower_bound(prey + 1, prey + 1 + ty, c1 + c2 + c3) - prey);
        if (py > ty || prey[py] != c1 + c2 + c3) continue;
        if (tr.get(-inf, x1, -inf, y1) != a[1]) continue;
        if (tr.get(-inf, x1, y2, inf) != a[3]) continue;
        if (tr.get(x2, inf, -inf, y1) != a[7]) continue;
        if (tr.get(x2, inf, y2, inf) != a[9]) continue;
        out(x1); cout << ' '; out(x2); cout << '\n';
        out(y1); cout << ' '; out(y2); cout << '\n';
        return 0;
    } while (next_permutation(a + 1, a + 10));
    cout << "-1" << '\n';
    return 0;
}
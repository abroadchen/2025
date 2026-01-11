/**
*N：矩形数量上限
M：点数量上限（4*N）
K：坐标范围上限
L：邻接表大小上限
 *
 *x, y, u, d, l, r：坐标和四个方向的距离信息
*p[M]：点数组
*ed：指向唯一化后数组末尾的指针 标识有效元素的边界
st[K]：栈数组
*sub()：计算点的 x-y 值（斜率相关）常量引用避免拷贝
eq()：判断两点是否在同一斜线上
minn()：返回 u 和 r 的最小值
*n：矩形数量
i, j, k：循环变量
x1[N], x2[N], y1[N], y2[N]：矩形坐标数组 左下和右上

左下角：(x1[i], y1[i])
左上角：(x1[i], y2[i])
右下角：(x2[i], y1[i])
右上角：(x2[i], y2[i])


s[K][K]：前缀和数组 从(1,1)到(i,j)矩形区域内1的数量
t[K][K]：点索引映射数组
*生成矩形的四个角点
s[j][k] = 1：标记矩形内部的点
 *按x坐标优先，y坐标次之排序
*unique()：去除相邻重复元素
返回去重后的末尾指针
 *将点坐标映射到其在去重数组中的索引
*a[i][j]：点i的第j个邻居
num[i]：点i的邻居数量
为每个矩形的四个角点建立相邻关系
 *
*如果x坐标相同：更新u值（向上距离）
否则：更新r值（向右距离）
*如果x坐标相同：更新d值（向下距离）
否则：更新l值（向左距离）
*先按斜率（x-y）排序
斜率相同时按坐标排序
 *
 *
*j = x1[i] + 1：从矩形内部开始（不包括边界）
j <= x2[i]：到矩形右边界（不包括）
k = y1[i] + 1：y坐标从内部开始
k <= y2[i]：到上边界（不包括）
 *
*s[i][j-1]：左边区域的和
s[i-1][j]：上方区域的和
s[i-1][j-1]：重复计算的左上角区域，需要减去一次
 *
*ed - p：计算有效点的数量
i--：先使用i的值，然后i减1（直到i变为0）
t[p[i].x][p[i].y] = i：建立坐标到索引的映射
这样可以通过坐标快速找到点在数组中的位置
 *
*每个点与其相邻的两个点连接
例如：左下角与左上角和右下角相连
num[...]++：先使用当前数量，然后数量加1
 *
*外层循环：遍历所有点
for (j = num[i]; j--;)：遍历点i的所有邻居
if (p[a[i][j]].x == p[i].x)：如果x坐标相同（在同一条竖线上）
p[i].u = max(...)：更新向上可达距离
p[a[i][j]].u+p[a[i][j]].y-p[i].y：邻居的u值加上纵坐标差
else：如果在同一条横线上
p[i].r = max(...)：更新向右可达距离
 *
*外层循环：按斜率分组处理点
i = j：每次将i设置为下一组的起始位置
int top = 1：栈顶指针，初始为1
st[0] = p[i]：将当前组的第一个点压入栈
*内层循环：处理当前斜率组的所有点
j < ed - p：确保不越界
eq(p[i], p[j])：检查是否在同一斜率线上
*单调栈操作：弹出不符合条件的栈顶元素
top && top > 0：确保栈不为空
minn(st[top-1])+st[top-1].x < p[j].x：判断是否满足单调性条件
*top > 0：栈不为空
min(minn(st[top-1]), min(p[j].d, p[j].l)) >= p[j].x-st[top-1].x：距离条件
前缀和公式：验证矩形区域内是否全为1
(p[j].x-st[top-1].x)*(p[j].y-st[top-1].y)：矩形面积
*int ans = 0：符合条件的矩形数量
int rect_count[N]：存储符合条件的矩形编号
循环检查每个矩形是否包含当前找到的区域
k + 1：转换为1基索引
*如果找到符合条件的矩形
输出"YES"和矩形数量
输出所有符合条件的矩形编号
return 0：程序结束
*继续单调栈操作
将当前点压入栈
*如果没有找到符合条件的区域，输出"NO"
return 0：正常结束程序
 */
#include <algorithm>
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 100005, M = 400005, K = 3005, L = 10;
struct pt {
    int x, y, u, d, l, r;
    bool operator<(const pt &o) const {
        return x < o.x || (x == o.x && y < o.y);
    }
    bool operator==(const pt &o) const {//判断两个点坐标是否相同
        return x == o.x && y == o.y;
    }
    bool operator<=(const pt &o) const {
        return x < o.x || (x == o.x && y <= o.y);
    }
} p[M], *ed, st[K];

int sub(const pt &x) { return x.x - x.y; }
bool eq(const pt &u, const pt &v) { return sub(u) == sub(v); }
int minn(const pt &x) { return min(x.u, x.r); }

int main() {
    fast;
    int n, i, j = 0, k, x1[N], x2[N], y1[N], y2[N], s[K][K], t[K][K];
    cin >> n;

    // 初始化s数组
    for (i = 0; i < K; ++i)
        for (j = 0; j < K; ++j)
            s[i][j] = 0;

    for (i = 0; i < n; i++) {
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
        p[i<<2] = {x1[i], y1[i], 0, 0, 0, 0};
        p[i<<2|1] = {x1[i], y2[i], 0, 0, 0, 0};
        p[i<<2|2] = {x2[i], y1[i], 0, 0, 0, 0};
        p[i<<2|3] = {x2[i], y2[i], 0, 0, 0, 0};
        for (j = x1[i] + 1; j <= x2[i]; j++)
            for (k = y1[i] + 1; k <= y2[i]; k++) {
                s[j][k] = 1;
            }
    }

    for (i = 1; i < K; ++i)
        for (j = 1; j < K; ++j) {
            s[i][j] += s[i][j-1] + s[i-1][j] - s[i-1][j-1];
        }

    sort(p, p + (n<<2), [](const pt &a, const pt &b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    });
    ed = unique(p, p + (n<<2));

    // 初始化t数组
    for (i = 0; i < K; ++i)
        for (j = 0; j < K; ++j)
            t[i][j] = 0;

    for (i = static_cast<int>(ed - p); i--;)
        t[p[i].x][p[i].y] = i;

    int a[M][L], num[M] = {};

    for (i = 0; i < n; i++) {
        a[t[x1[i]][y1[i]]][num[t[x1[i]][y1[i]]]++] = t[x1[i]][y2[i]];
        a[t[x1[i]][y1[i]]][num[t[x1[i]][y1[i]]]++] = t[x2[i]][y1[i]];
        a[t[x1[i]][y2[i]]][num[t[x1[i]][y2[i]]]++] = t[x1[i]][y1[i]];
        a[t[x1[i]][y2[i]]][num[t[x1[i]][y2[i]]]++] = t[x2[i]][y2[i]];
        a[t[x2[i]][y1[i]]][num[t[x2[i]][y1[i]]]++] = t[x1[i]][y1[i]];
        a[t[x2[i]][y1[i]]][num[t[x2[i]][y1[i]]]++] = t[x2[i]][y2[i]];
        a[t[x2[i]][y2[i]]][num[t[x2[i]][y2[i]]]++] = t[x1[i]][y2[i]];
        a[t[x2[i]][y2[i]]][num[t[x2[i]][y2[i]]]++] = t[x2[i]][y1[i]];
    }

    for (i = static_cast<int>(ed - p); i--;)
        for (j = num[i]; j--;) {
            if (p[a[i][j]].x == p[i].x)
                p[i].u = max(p[i].u, p[a[i][j]].u+p[a[i][j]].y-p[i].y);
            else
                p[i].r = max(p[i].r, p[a[i][j]].r+p[a[i][j]].x-p[i].x);
        }

    for (i = 0; i < ed - p; ++i)
        for (j = num[i]; j--;) {
            if (p[a[i][j]].x == p[i].x)
                p[i].d = max(p[i].d, p[a[i][j]].d-p[a[i][j]].y+p[i].y);
            else
                p[i].l = max(p[i].l, p[a[i][j]].l-p[a[i][j]].x+p[i].x);
        }

    sort(p, ed, [](const pt &u, const pt &v) {
        return sub(u) != sub(v) ? sub(u) < sub(v) : u<=v;
    });

    for (i = 0; i < ed - p; i = j) {
        int top = 1;
        st[0] = p[i];
        for (j = i + 1; j < ed - p && eq(p[i], p[j]); ++j) {
            while (top && top > 0 && minn(st[top-1])+st[top-1].x < p[j].x) --top;

            if (top > 0 && min(minn(st[top-1]), min(p[j].d, p[j].l)) >= p[j].x-st[top-1].x &&
                s[p[j].x][p[j].y]-s[st[top-1].x][p[j].y]-s[p[j].x][st[top-1].y]+s[st[top-1].x][st[top-1].y]==
                (p[j].x-st[top-1].x)*(p[j].y-st[top-1].y)) {

                int ans = 0;
                int rect_count[N];

                for (k = 0; k < n; k++) {
                    if (x1[k] < p[j].x && y1[k] < p[j].y && x2[k] > st[top-1].x && y2[k] > st[top-1].y) {
                        rect_count[ans++] = k + 1;  // 1-indexed
                    }
                }

                if (ans > 0) {  // 只有当找到矩形时才输出
                    cout << "YES " << ans << "\n";

                    for (int idx = 0; idx < ans; idx++) {
                        if (idx > 0) cout << ' ';
                        cout << rect_count[idx];
                    }
                    cout << '\n';
                    return 0;
                }
            }
            while (top && top > 0 && minn(st[top-1])+st[top-1].x <= p[j].x+minn(p[j])) --top;
            st[top++] = p[j];
        }
    }

    cout << "NO\n";
    return 0;
}
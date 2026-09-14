//
// Created by Psy.C on 2026/9/14.
//
/**
交互格式：向裁判输出询问 0 x y，然后读回一个整数 res。
fflush(stdout)：刷新缓冲区，保证交互立即生效。
关键：ask(x, y) 返回的 res 表示"点 (x,y) 到某条目标线的距离/方向信息"——通常这样定义：

res = 0：点 (x,y) 恰好在目标线上（命中）。
res > 0：点在线的一侧，数值表示距离（用于二分）。
这里我们读 ask(mid, mid)，即查询对角线点 (mid, mid)
在 [-inf, inf] 上二分搜索。
查询对角线点 (mid,mid)：
若 res == 0（命中）→ 记录 mid 到 ans，并把 res 设为 1（作为边界偏移）。
否则把 mid 记到 no（记录一个"非命中"的参考点）。
递归分治：dfs(l, mid-res) 和 dfs(mid+res, r)。
含义：通过二分不断缩小范围，找到目标线上所有满足条件的 x 坐标（提交到 ans），同时保留一个"未命中"的参考点 no。

no 的作用：它是不在目标线上的一个点坐标，后面用它作为"参照物"去测试其他点
对 ans 里每个候选点 an：
ask(an, no)：测试点 (an, no) 是否命中（==0）→ 命中则 an 属于 X 组（横坐标方向）。
ask(no, an)：测试点 (no, an) 是否命中 → 命中则 an 属于 Y 组（纵坐标方向）。
逻辑：通过固定一个"非命中参考点 no"，分别把 an 放在 x 坐标和 y 坐标位置测试，就能判定该候选 belongs 到竖直线还是水平线
交互协议：最终输出 1（表示提交答案），后面接两组大小和具体坐标。
X 是一组、Y 是一组
*/
#include <bits/stdc++.h>
using namespace std;
constexpr int inf = 1e8;

int ask(int x, int y) {
    printf("0 %d %d\n", x, y); fflush(stdout);
    int res; scanf("%d", &res);
    return res;
}

vector<int> ans;
int no;
void dfs(int l, int r) {
    if (l > r) return;
    int mid = (l+r)>>1, res = ask(mid, mid);
    if (res == 0) ans.push_back(mid), res = 1;
    else no = mid;
    dfs(l, mid-res), dfs(mid+res, r);
}

vector<int> X, Y;
int main() {
    dfs(-inf, inf);
    for (int an : ans) {
        if (ask(an, no) == 0) X.push_back(an);
        if (ask(no, an) == 0) Y.push_back(an);
    }
    printf("1 %d %d\n", X.size(), Y.size());
    for (int i = 0; i < X.size(); ++i)
        printf("%d%c", X[i], i==X.size()-1?'\n':' ');
    for (int i = 0; i < Y.size(); ++i)
        printf("%d%c", Y[i], i==Y.size()-1?'\n':' ');
    return 0;
}
//
// Created by Psy.C on 2025/11/6.
//
/*
*x, y: 网格的行数和列数
w: 废弃地块的数量
q: 查询次数
c[1002][2]: 存储废弃地块的坐标（最多1002个）
a[3][10]: 作物名称数组，包含"Carrots", "Kiwis", "Grapes"
*c[i][0]表示第i个废弃地块的行坐标
c[i][1]表示第i个废弃地块的列坐标
 *
 *
 *时间复杂度：O(q×w)，空间复杂度：O(w)
 */
#include <cstdio>
using namespace std;

int x, y, w, q, c[1002][2];
char a[3][10] = {
    "Carrots",//胡萝卜
    "Kiwis",//猕猴桃
    "Grapes"//葡萄
};

int main() {
    scanf("%d %d %d %d", &x, &y, &w, &q);
    for (int i = 0; i < w; ++i) scanf("%d %d", &c[i][0], &c[i][1]);
    while (q--) {
        int u, v; scanf("%d %d", &u, &v);
        int num = (u - 1) * y + v - 1;//二维坐标转换为一维编号
        for (int i = 0; i < w; ++i) {
            if (c[i][0] < u) num--;//废弃地块在当前查询位置的上方行
            else if (c[i][0] == u && c[i][1] < v) num--;//废弃地块在同行但更左侧
            else if (c[i][0] == u && c[i][1] == v) {//查询位置正好是废弃地块
                printf("Waste\n");
                goto down;
            }
        }
        printf("%s\n", a[num % 3]);
        down:;
    }
    return 0;
}
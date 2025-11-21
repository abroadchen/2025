//
// Created by Psy.C on 2025/11/21.
//
/*
 *最大值从位置r移动到最右边n-1位置需要 (n-1-r) 步
 *最小值从位置l移动到最左边0位置需要 l 步
 *如果最小值位置在最大值位置的左边，说明在交换过程中会有一次重叠
 *即一次交换同时帮助了两个目标，所以总步数减1
 *
 *mn: 数组中的最小值
 *mx: 数组中的最大值
 *l: 最小值的最靠右位置索引
 *r: 最大值的最靠右位置索引
 *交换过程中有一次机会可以让两个元素都向目标方向移动，节省一步
 */
#include <cstdio>
using namespace std;

int main() {
    int n; scanf("%d\n",&n);
    int cur(0), mn(101), mx(0), l(100), r(0);
    for (int i = 0; i < n; ++i) {
        scanf("%d",&cur);
        if (cur > mx) { r = i; mx = cur; }//更新最大值的位置为当前索引
        if (cur <= mn) { l = i; mn = cur; }
    }
    int ans = r + (n - 1 - l);
    if (l < r) --ans;
    printf("%d\n",ans);
    return 0;
}
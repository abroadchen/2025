//
// Created by Psy.C on 2025/12/19.
//
/*
 *c1和c2(分别计数a和b数组中的元素个数
*循环读入n组数据，每组包括颜色col和值val。
如果颜色为1(真)，则存储到数组b中，并增加计数器c2。
如果颜色为0(假)，则存储到数组a中，并增加计数器c1。
每个元素的id设为当前循环索引i。
 *
 *初始化指针变量：l1和l2用于遍历数组a和b，id1和id2用于记录最近处理过的元素ID
*当两个数组都还有未处理元素时继续循环。
记录当前处理元素的ID。
如果a[l1]的值小于b[l2]的值：
输出配对信息(较小值的全部被消耗)
从b[l2]中减去a[l1]的值
移动a数组指针，如果a数组已处理完，则也移动b数组指针
否则(包括相等的情况)：
输出配对信息(较小值的全部被消耗)
从a[l1]中减去b[l2]的值
移动b数组指针，如果b数组已处理完，则也移动a数组指针
 *处理a数组中剩余的元素，与之前处理过的b数组最后一个元素配对
 *处理b数组中剩余的元素，与之前处理过的a数组最后一个元素配对
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;

struct node {
    int val, id;
    bool operator<(const node& rhs) const {
        return val < rhs.val;
    }
} a[N], b[N];

int main() {
    fast;
    int n, c1 = 0, c2 = 0; cin>>n;
    for (int i = 1, col, val; i <= n; ++i) {
        cin>>col>>val;
        if (col) { b[c2].id = i; b[c2++].val = val; }
        else { a[c1].id = i; a[c1++].val = val; }
    }
    sort(a, a + c1); sort(b, b + c2);
    int l1 = 0, l2 = 0, id1 = 0, id2 = 0;
    while (l1 < c1 && l2 < c2) {
        id1 = a[l1].id; id2 = b[l2].id;
        if (a[l1].val < b[l2].val) {
            cout << a[l1].id << ' ' << b[l2].id << ' ' <<
                a[l1].val << '\n';
            b[l2].val -= a[l1].val;
            l1++;
            if (l1 >= c1) l2++;
        } else {
            cout << a[l1].id << ' ' << b[l2].id << ' ' <<
                b[l2].val << '\n';
            a[l1].val -= b[l2].val;
            l2++;
            if (l2 >= c2) l1++;
        }
    }
    while (l1 < c1) {
        cout << id2 << ' ' << a[l1].id << ' ' <<
            a[l1].val << '\n';
        l1++;
    }
    while (l2 < c2) {
        cout << id1 << ' ' << b[l2].id << ' ' <<
            b[l2].val << '\n';
        l2++;
    }
    return 0;
}
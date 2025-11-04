//
// Created by Psy.C on 2025/11/4.
//
/*
 *声明向量div用于存储g的所有约数
*只需要遍历到√g即可
如果i是g的约数，那么g/i也是g的约数
特殊情况：当i*i=g时，只添加一次（避免重复添加√g）
 *对约数向量进行升序排序
 *
*upper_bound找到第一个大于r的位置
--移动到前一个位置（即不大于r的最大元素）
*解引用得到该元素的值
 *
*预处理：O(√g + d log d)，其中d是约数个数
每次查询：O(log d)
总体：O(√g + d log d + q log d)
 */
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int gcd(int a,int b) { return b==0?a:gcd(b,a%b);}
int main() {

    int a, b; scanf("%d %d\n",&a,&b);
    int g = gcd(a,b);
    vector<int> div;
    for (int i = 1; i * i <= g; ++i) {
        if (g % i == 0) {
            div.push_back(i);
            if (i * i < g) div.push_back(g / i);
        }
    }
    sort(div.begin(), div.end());

    int q; scanf("%d",&q);
    while (q--) {
        int l, r; scanf("%d %d",&l,&r);
        int ans = *(--(upper_bound(div.begin(), div.end(), r)));
        printf("%d\n", ans >= l ? ans : -1);
    }
    return 0;
}
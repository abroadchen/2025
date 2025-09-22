//
// Created by Psy.C on 2025/9/22.
//

#include <algorithm>
#include <cstdio>
using namespace std;

int main() {

    int n; scanf("%d",&n);
    int* len = new int[n];

    for (int i = 0; i < n; ++i) scanf("%d",&len[i]);// 读取n个整数到数组中
    sort(len,len+n);

    int num = 0, curl = 0, curh = 1, maxh = 1;
    for (int i = 0; i < n; ++i) {
        if (len[i] == curl) {// 如果当前元素等于正在统计的数值
            curh++;// 当前数值出现次数加1
            if (curh > maxh) maxh = curh;// 更新最大出现次数
        } else {// 如果遇到新数值
            curl = len[i];// 更新当前处理的数值
            curh = 1;// 重置当前数值出现次数为1
            num++;// 不同数值个数加1
        }
    }

    printf("%d %d\n",maxh, num);

    return 0;
}
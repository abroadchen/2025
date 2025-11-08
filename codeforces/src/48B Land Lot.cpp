//
// Created by Psy.C on 2025/10/11.
//
/*
 *初始化变量mm为n*m+1，作为最小值的初始值（确保任何实际和都比它小）
 *
*第一个双重循环，处理地毯以l×w的尺寸放置的情况：
外层循环遍历可能的起始行(i从0到n-l，确保地毯能放下)
内层循环遍历可能的起始列(j从0到m-w，确保地毯能放下)
对每个可能的位置，计算该区域内的数值和：
使用cnt变量累加该l×w区域内的所有元素值
通过双重循环遍历这个区域内的每个元素
更新最小值mm，保留当前找到的最小和
 *
*第二个双重循环，处理地毯以w×l的尺寸放置的情况（旋转90度）：
与上面类似，但这次是w×l的尺寸
同样计算每个可能位置的数值和，并更新最小值mm
 *
 */
#include <cstdio>
#include <vector>
using namespace std;

int main() {

    long n, m; scanf("%ld %ld",&n,&m);
    vector<vector<int>> mp(n, vector<int>(m, 0));
    for (long i = 0; i < n; ++i)
        for (long j = 0; j < m; ++j)
            scanf("%d",&mp[i][j]);
    long l, w; scanf("%ld %ld",&l,&w);
    long mm(n * m + 1);

    for (long i = 0; i + l <= n; ++i) {
        for (long j = 0; j + w <= m; ++j) {
            long cnt(0);
            for (long r = i; r < i + l; ++r) {
                for (long c = j; c < j + w; ++c)
                    cnt += mp[r][c];
            }
            mm = (mm < cnt) ? mm : cnt;
        }
    }

    for (long i = 0; i + w <= n; ++i) {
        for (long j = 0; j + l <= m; ++j) {
            long cnt(0);
            for (long r = i; r < i + w; ++r) {
                for (long c = j; c < j + l; ++c)
                    cnt += mp[r][c];
            }
            mm = (mm < cnt) ? mm : cnt;
        }
    }

    printf("%ld\n", mm);
    return 0;
}
//
// Created by Psy.C on 2025/11/4.
//
/*
*n：输入数据的个数
x：目标值
cnt：计数器
m[N]：布尔数组，标记输入中出现的数字
p[N]：布尔数组，用于埃拉托斯特尼筛法标记合数
 *
 *对于每个读入的数字a，如果小于N，则在m[a]位置标记为true，表示该数字在输入中存在
 *如果x小于等于2，输出"0"并结束程序（特殊情况处理）
 *如果数字1在输入中存在，输出"1"并结束程序（因为1是特殊数字）
 *如果x过大（大于等于N），输出"-1"并结束程序（超出处理范围）
 *
*从2到x-1进行类似筛法的处理：
如果i没有被标记为合数（!p[i]，即i是"素数"）
检查输入中是否包含数字i（m[i]）
如果输入中不包含i，输出"-1"并结束（缺少必要的数字）
将i的所有倍数标记为合数：对j = 2i, 3i, 4i, ... 设置p[j] = 1
计数器加1
 *输出最终的计数结果并结束程序
 *
 */
#include <cstdio>
using namespace std;

const int N = 2000006;
int n, x, cnt;
bool m[N], p[N];

int main() {

    scanf("%d%d", &n, &x);
    for (int i = 0, a; i < n; ++i) {
        scanf("%d", &a);
        if (a < N) m[a] = 1;
    }
    if (x <= 2) return !printf("0");
    if (m[1]) return !printf("1");
    if (x >= N) return !printf("-1");
    for (int i = 2; i < x; ++i) {
        if (!p[i]) {
            if (!m[i]) return !printf("-1");
            for (int j = i + i; j < N; j += i) p[j] = 1;
            cnt++;
        }
    }
    return !printf("%d", cnt);
}
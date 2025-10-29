//
// Created by Psy.C on 2025/10/28.
//
/*
*n: 字符串数量
m: 字符集合大小
vis[N]: 布尔数组，标记哪些字符是有效的
s[M], s2[M]: 字符数组，用于存储字符串
sum: 长整型变量，用于累计结果
 *
 *定义结构体Node，包含字符s和位置索引id，用于存储字符及其位置信息
*定义比较函数cmp，用于结构体排序：
首先按字符值升序排列
如果字符相同，则按位置索引升序排列
 *定义绝对值函数sgn，返回x的绝对值
 *定义搜索函数search，参数为字符z和位置num
 *初始化二分搜索的左右边界l和r，中间变量mid，以及结果ret(初始化为大值)
*如果中间字符大于目标字符，搜索左半部分
如果中间字符小于目标字符，搜索右半部分
*计算当前位置与目标位置的距离
如果距离更小，则更新最小距离
 *继续搜索，寻找更近的位置
 *
 *
 *遍历字符集合中的每个字符
*标记字符为有效
将字符和位置信息存储到结构体数组f中
 *
 *读取待检测字符串到s2
 *遍历待检测字符串的每个字符
*如果字符在有效集合中，则加上搜索得到的最小距离
否则加上字符串长度
 *
 *输出当前字符串的总距离
 */
#include <ios>
#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;
const int N = 777, M = 2e6+9;
int n, m;
bool vis[N];
char s[M], s2[M];
ll sum;

struct Node { char s; int id; } f[M];
bool cmp(Node a, Node b) {
    if (a.s != b.s) return a.s < b.s;
    else return a.id < b.id;
}

int sgn(int x) { return x < 0 ? -x : x; }

int search(char z, int num) {
    int l(0), r(m - 1), mid, ret(999999);
    while (l <= r) {
        mid = (l + r) / 2;
        if (f[mid].s > z) r = mid - 1;
        else if (f[mid].s < z) l = mid + 1;
        else {//如果找到目标字符
            int t = sgn(num - f[mid].id);
            if (ret > t) ret = t;
            if (f[mid].id > num) r = mid - 1;
            else l = mid + 1;
        }
    }
    return ret;
}

int main() {

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(vis, 0, sizeof(vis));
        scanf("%s", s);
        for (int i = 0; s[i]; ++i) {
            vis[s[i]] = 1;
            f[i].s = s[i];
            f[i].id = i;
        }
        sort(f, f+m, cmp);
        for (int i = 0; i < n; ++i) {
            sum = 0;
            scanf("%s", s2);
            ll len = strlen(s2);
            for (int j = 0; s2[j]; ++j) {
                if (vis[s2[j]]) sum += search(s2[j], j);
                else sum += len;
            }
            cout << sum << "\n";
        }
    }
    return 0;
}
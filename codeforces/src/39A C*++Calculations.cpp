//
// Created by Psy.C on 2025/9/24.
//
/*
*now初始化为1，表示当前操作符状态（正/负）
cnt初始化为0，用于计数已读取的节点数量
*x：数值
flag：标记位（1表示"after"，0表示"before"）
*solve()函数用于解析输入表达式
pre初始化为-1，用于标记操作类型
x初始化为0，存储解析出的数值
读取第一个字符
*如果第一个字符是'a'，表示"after"操作，x设为1，pre设为1
如果第一个字符是'+'，表示"before"操作，x设为1，pre设为0
连续读取两个字符（跳过"after"或"before"的剩余字符）
*否则，解析数字：
将第一个字符转换为数字
继续读取后续字符，如果是数字则累加到x中
*读取操作符后的字符
如果是'a'，表示"after"操作，pre设为1
如果是'+'，表示"before"操作，pre设为0
*根据now的值决定存储正数还是负数
设置当前节点的flag标记
 *
 *
 *
 */
#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1234+10;
int now(1), cnt(0);

struct Node {
    int x, flag;
    bool friend operator<(Node a, Node b) { return a.x < b.x; }
} a[N];

void solve() {
    int pre(-1), x(0); char c(getchar());
    if (c == 'a') {
        x = 1;
        pre = 1;
        c = getchar();
        c = getchar();
    } else if (c == '+') {
        x = 1;
        pre = 0;
        c = getchar();
        c = getchar();
    } else {
        x = c - '0';
        while (c = getchar()) {
            if (c >= '0' && c <= '9') x = x * 10 + (c - '0');
            else break;
        }
        c = getchar();
        if (c == 'a') {
            pre = 1;
            c = getchar();
            c = getchar();
        } else if (c == '+') {
            pre = 0;
            c = getchar();
            c = getchar();
        }
    }
    if (now) a[++cnt].x = x;
    else a[++cnt].x = -x;
    a[cnt].flag = pre;
}

int main() {

    int n; scanf("%d",&n);
    getchar();
    char c;
    while (1) {
        solve();
        if (c = getchar()) {
            if (c == '\n') break;
            else if (c == '+') now = 1;
            else now = 0;
        }
    }
    sort(a + 1, a + 1 + cnt);

    int ans(0);
    for (int i = 1; i <= cnt; ++i) {
        if (a[i].flag == 1) {
            ans += a[i].x * n;
            n++;
        } else {
            n++;
            ans += a[i].x * n;
        }
    }
    printf("%d\n", ans);
    return 0;
}
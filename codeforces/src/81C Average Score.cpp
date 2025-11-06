//
// Created by Psy.C on 2025/11/6.
//
/*
*n：元素的数量
a 和 b：控制分配逻辑的两个参数
 *特殊情况：当a等于b时，简单地将前a个元素分配给组1，其余分配给组2
 *
*创建一个向量的向量，用来按优先级值对元素索引进行分组
对于每个元素，读取其优先级值x，并将它的索引存储在v[x]中
 *
*创建结果数组s来存储分配结果（1或2）
初始化计数器x为值a
*当a > b时，按优先级从低到高（0到9）处理
对于每个优先级组，当x > 0时将元素分配给组1，否则分配给组2
每分配一个元素就减少x的值
 *当a <= b时，按优先级从高到低（9到0）处理
 */
#include <cstdio>
#include <vector>
#define rep(i,n) for(int i=0;i<(n);++i)
using namespace std;

const int N = 10;

int main() {
    int n, a, b; scanf("%d", &n);
    scanf("%d %d", &a, &b);
    if (a == b) { rep(i,n) printf("%d ", i < a ? 1 : 2); }
    else {
        vector<vector<int>> v(N);
        rep(i,n) {
            int x; scanf("%d", &x);
            v[x].push_back(i);
        }
        vector<int> s(n);
        int x(a);
        if (a > b) {
            rep(i,N) rep(j,v[i].size()) {
                int pos = v[i][j];
                s[pos] = x > 0 ? 1 : 2;
                --x;
            }
        } else {
            for (int i = N - 1; i >= 0; --i) {
                rep(j,v[i].size()) {
                    int pos = v[i][j];
                    s[pos] = x > 0 ? 1 : 2;
                    --x;
                }
            }
        }
        rep(i,n) printf("%d ", s[i]);
    }
    puts("");
    return 0;
}
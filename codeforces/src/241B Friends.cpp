//
// Created by Psy.C on 2025/12/13.
//
/*
*son[2]: 指向左右子节点的指针数组，分别代表二进制位0和1
sum: 以此节点为根的子树中包含的数字个数
b[M]: 统计每一位上1的个数
构造函数初始化指针为空，sum为0，b数组元素全为0
创建节点数组my，以及相关指针变量
 *
*从最高位开始处理
如果当前位对应的子节点不存在，则创建新节点
移动到对应子节点
增加该节点的计数
更新每一位上1的统计数量
 *
*n: 数组长度
a[N]: 存储输入数组
m: 第m大的值
ans: 累计答案
res: 结果值
 *
*将所有查询指针初始化指向Trie树根节点
将m左移一位（乘以2），因为每对会被计算两次
 *从最高位开始逐位处理，直到m为0或处理完所有位
*对于每个数组元素，检查是否存在与其在当前位相反的路径
如果存在，累加该子树的节点数
 *如果当前位为1的对数不超过m
*如果当前元素有相反位的路径，则计算其贡献
否则继续沿相同位路径走
*对于每一位，如果当前数该位为1，则贡献为(总数-该位1的个数)
如果当前数该位为0，则贡献为该位1的个数
乘以对应的位权值累加到答案
 *移动指针并减少m值
*如果当前位为1的对数超过m：
在结果中设置当前位为1
所有指针转向相反位的路径
 *
*总贡献加上剩余m倍的结果值
除以2（因为每对被计算了两次）
取模后输出

val>>i&1 的作用是提取val的二进制表示中从右往左数第i位的值

 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 50100
#define mod 1000000007
using namespace std;

constexpr int M = 30;

struct node {
    node *son[2]{};
    int sum, b[M]{};
    node() {
        son[0] = son[1] = nullptr; sum = 0;
        for (int& i : b) i = 0;
    }
} my[N*M], *mem = my, *trie, *q[N];

void insert(const int val) {
    node *cur = trie;
    for (int i = M - 1; i >= 0; --i) {
        if (!cur->son[val>>i&1]) cur->son[val>>i&1] = mem++;
        cur = cur->son[val>>i&1];
        cur->sum++;
        for (int j = 0; j < M; ++j) cur->b[j] += val>>j&1;
    }
}


int n, a[N];
ll m, ans, res;
void init() {
    trie = mem++;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        insert(a[i]);
    }
}

void out() {
    for (int i = 1; i <= n; ++i) q[i] = trie;
    m <<= 1;
    for (int i = M - 1; m && i >= 0; --i) {
        ll s = 0;
        for (int j = 1; j <= n; ++j) {
            if (q[j] && q[j]->son[!(a[j]>>i&1)])
                s += q[j]->son[!(a[j]>>i&1)]->sum;
        }
        if (s <= m) {
            for (int j = 1; j <= n; ++j) {
                if (!q[j]) continue;
                const node *cur = q[j]->son[!(a[j]>>i&1)];
                if (!cur) {
                    q[j] = q[j]->son[a[j]>>i&1];
                    continue;
                }
                for (int k = 0; k < M; ++k) {
                    ans += (1ll * ((a[j]>>k&1) ? cur->sum - cur->b[k] : cur->b[k])) << k;
                }
                q[j] = q[j]->son[a[j]>>i&1];
            }
            m -= s;
        } else {
            res |= 1<<i;
            for (int j = 1; j <= n; ++j) if (q[j]) {
                q[j] = q[j]->son[!(a[j]>>i&1)];
            }
        }
    }
    cout << ((ans + res * m) / 2) % mod << '\n';
}



int main() {
    fast;
    init(); out();
    return 0;
}
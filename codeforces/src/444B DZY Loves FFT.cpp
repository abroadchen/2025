//
// Created by Psy.C on 2026/2/8.
//
/**
x: 随机数种子
get(): 伪随机数生成函数，使用线性同余方法
a数组填充为[1,2,3,...,n]
洗牌算法随机打乱数组a
get()%(i+1): 生成0到i之间的随机索引
swap(a[i], a[get()%(i+1)]): 交换元素
b数组前d个元素设为1，其余为0
洗牌算法随机打乱数组b 使得1和0随机分布

a[N]: 整数数组，用于存储排列
n: 数组长度
d: 重要参数（表示b数组中1的个数）
b[N]: 二进制数组，包含d个1和(n-d)个0


pos[N]: 存储值i在数组a中的位置
p[N]: 存储b数组中值为1的元素位置
cnt: 计数器，记录p数组的有效元素数
c[N]: 结果数组

i-pos[j] >= 0确保索引非负，b[i-pos[j]]检查该位置在b中是否为1
i-p[j]：当我们处理位置i时，i-p[j]表示从i向左移动p[j]个位置
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100010
#define rep(i,n) for (i=0; i<n; ++i)
using namespace std;

ll x;
ll get() {
    x = (x*37+10007)%1000000007;
    return x;
}

ll a[N], n, d, b[N];
void init() {
    int i;
    rep(i,n) a[i] = i + 1;
    rep(i,n) swap(a[i], a[get()%(i+1)]);
    rep(i,n)
        if (i < d) b[i] = 1; else b[i] = 0;
    rep(i,n) swap(b[i], b[get()%(i+1)]);
}

int pos[N], p[N], cnt, c[N];

int main() {
    fast;
    cin >> n >> d >> x; init();
    int i;
    rep(i,n) {
        pos[a[i]] = i;
        if (b[i]) p[++cnt] = i;
    }
    rep(i,n) {
        bool flag = false;
        for (int j = n; j >= max(1ll, n-50); --j)
            if (i-pos[j] >= 0 && b[i-pos[j]]) {
                c[i] = j;
                flag = true;
                break;
            }
        if (!flag)
            for (int j = 1; j <= cnt && i - p[j] >= 0; ++j)
                c[i] = max(c[i], static_cast<int>(a[i-p[j]]));
    }
    rep(i,n) cout << c[i] << '\n';
    return 0;
}
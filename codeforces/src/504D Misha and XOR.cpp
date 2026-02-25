//
// Created by Psy.C on 2026/2/25.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2001, M = 666;

bitset<N> x;//大整数的二进制表示
char s[M];//十进制字符串
void get() {//将十进制字符串转换为二进制bitset
    x.reset();//清空
    int len = strlen(s), pos = 0;//二进制位位置
    for (int i = 0; i < len; ++i) s[i] -= '0';//将字符数组转换为数字数组
    while (len) {
        constexpr ll base = 1ll<<50;//每次处理50位二进制数
        ll r = 0;//余数
        int p = 0;//新字符串长度
        for (int i = 0; i < len; ++i) {
            const ll sum = r*10+s[i];//当前处理的数值
            if (sum >= base || p) s[p++] = sum/base;//商（进位）
            r = sum%base;//余数
        }
        for (int i = 0; i < 50; ++i)//将余数转换为50位二进制存入bitset
            x[pos++] = r&1, r >>= 1;
        len = p;//更新长度
    }
}

int n, f[N];//每个向量的主元位置
///当前解的系数向量
///基向量
///对应的系数向量
bitset<N> ans, r[N], w[N];
int main() {
    fast;
    cin >> n;//输入数量
    for (int k = 0; k < n; ++k) {
        cin >> s; get();
        ans.reset(); ans.set(k);//设置第k位为1（表示当前向量的系数为1）
        for (int i = 0; i < k; ++i)
            if (x.test(f[i]))//当前向量在主元位置有1
                x ^= r[i], ans ^= w[i];//异或消元操作
        if (x.any()) {//消元后向量不全为0
            cout << "0\n";//线性无关
            ///找到当前向量的第一个1的位置作为主元
            for (int i = 0; i < N; ++i) if (x[i]) {
                f[k] = i;
                break;
            }
            ///保存当前基向量和对应的系数向量
            r[k] = x; w[k] = ans;
            int p = k;
            while (p && f[p] < f[p-1]) {//保持主元位置递增排列
                swap(f[p], f[p-1]);
                swap(w[p], w[p-1]);
                swap(r[p], r[p-1]);
                p--;
            }
        } else {
            cout << ans.count()-1;//相关向量的数量（减1是因为不包括自身）
            for (int i = 0; i < k; ++i)
                if (ans.test(i)) cout << ' ' << i;//所有相关向量的索引
            cout << '\n';
        }
    }
    return 0;
}
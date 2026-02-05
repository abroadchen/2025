//
// Created by Psy.C on 2026/2/5.
//
/*
// s: 当前处理的字符串总长度
// z[]: Z数组，存储Z算法的结果（每个位置的最长公共前缀长度）
// c[]: 拼接后的字符串数组，大小约为5*N（N<<2 = N*4，加上N再+1/5）

c[i+z[i]]: 从位置i开始，第z[i]+1个字符
c[1+z[i]]: 从字符串开头，第z[i]+1个字符
比较目的: 检查从位置i开始的子串是否继续与开头的字符串匹配

段A1 (a[i...n]): 长度 n-i+1，位置 1 到 n-i+1
分隔符1 (!): 位置 n-i+2
段A2 (a[1...n]): 长度 n，位置 n-i+3 到 n-i+2+n = 2*n-i+2
分隔符2 (@): 位置 2*n-i+3
段B (b[1...m]): 长度 m，位置 2*n-i+4 到 2*n-i+3+m

 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 5000
#define inf 0x3f3f3f3f
using namespace std;

int s, z[(N<<2)+N+1], c[(N<<2)+N+5];
void init() {//计算每个位置的最长公共前缀
    int l = 0, r = 0;//维护当前已知最远右端点的区间
    for (int i = 2; i <= s; ++i) {//位置1不需要计算
        if (r < i) {//当前位置超出了已知区间
            z[i] = 0;//初始化匹配长度为0
            while (i + z[i] <= s && c[i+z[i]] == c[1+z[i]]) z[i]++;
            if (z[i]) l = i, r = i + z[i] - 1;
        }
        //在区间内，利用对称性质
        else if (i+z[i-l+1] <= r) z[i] = z[i-l+1]; else {//超出区间右端，需要扩展
            z[i] = r - i + 1;//初始化为已知匹配的部分
            while (i + z[i] <= s && c[i+z[i]] == c[1+z[i]]) z[i]++;//继续匹配
            l = i; r = i + z[i] - 1;//更新区间
        }
    }
}

int main() {
    fast;
    char a[N+5]{}, b[N+5]{}; string s1, s2; cin >> s1 >> s2;
    //将s1复制到a数组中，从索引1开始
    strcpy(a + 1, s1.data()); strcpy(b + 1, s2.data());
    //获取字符串a的有效长度
    const int n = static_cast<int>(strlen(a + 1)), m = static_cast<int>(strlen(b + 1));
    int ans = inf, b1[N+1]{}, b2[N+1]{};//计数数组
    for (int i = 1; i <= n; ++i) {//枚举字符串a的所有起始位置
        s = 0;//重置拼接字符串的长度
        //先复制a[i...n]（a从位置i到末尾）
        for (int j = i; j <= n; ++j) c[++s] = static_cast<unsigned char>(a[j]);
        c[++s] = '!';//添加分隔符
        //再复制完整的a字符串
        for (int j = 1; j <= n; ++j) c[++s] = static_cast<unsigned char>(a[j]);
        c[++s] = '@';
        //最后复制完整的b字符串
        for (int j = 1; j <= m; ++j) c[++s] = static_cast<unsigned char>(b[j]);
        c[s+1] = 0;//添加字符串结束符
        init();//计算z数组
        memset(b1, 0, sizeof b1); memset(b2, 0, sizeof b2);
        //统计在第二个a段中的Z值（这部分对应a的循环移位与a的匹配）
        for (int j = n-i+3; j <= 2*n-i+2; ++j) b1[z[j]]++;
        //统计在b段中的Z值（这部分对应与b的匹配）
        for (int j = 2*n-i+4; j <= s; ++j) b2[z[j]]++;
        for (int j = n-i+1; j; --j) {
            //j长度在两处都恰好出现一次，则更新答案
            if (b1[j] == 1 && b2[j] == 1) ans = min(ans, j);
            b1[j-1] += b1[j]; b2[j-1] += b2[j];//累加计数（前缀和思想）
        }
    }
    cout << (ans < inf ? ans : -1);
    return 0;
}
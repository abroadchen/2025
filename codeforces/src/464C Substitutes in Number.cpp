//
// Created by Psy.C on 2026/2/12.
//
/**
n: 规则数量
d[N]: 存储规则左边的数字（被替换的数字）
str: 输入的原始字符串
s[N]: 存储每个规则右边的字符串（替换后的内容）
c[N]: 临时字符数组，用于读取输入
val[10]: 存储0-9每个数字对应的实际值
Pow[10]: 存储0-9每个数字对应的位权（乘数）
 */
#include <bits/stdc++.h>
#define ll long long
#define N 100005
#define mod 1000000007
using namespace std;

int n, d[N];
string str, s[N];
char c[N];
ll val[10], Pow[10];

int main() {
    cin>>str;
    scanf("%d", &n);
    for(int i = 0; i<n; i++) {
        scanf("%d->", &d[i]);//读取规则左边的数字
        gets(c);//读取箭头后的字符串内容
        s[i] = c;
    }
    for(int i = 0; i<10; i++) {
        val[i] = i;//0-9每个数字的值为其本身
        Pow[i] = 10;
    }
    for(int i = n-1; i>=0; i--) {//后面的规则会影响前面的
        ll p = 1, v = 0;//当前规则的位权和值
        const int len = s[i].size();
        for(int j = 0; j<len; j++) {//遍历规则右边的字符串s[i]
            const int tmp = s[i][j]-'0';//当前字符对应的数字
            p = p*Pow[tmp]%mod;//整体的位权（长度相乘）
            v = v*Pow[tmp]%mod;//当前值乘以位权
            v = (v+val[tmp])%mod;//加上当前数字的值
        }
        val[d[i]] = v;//更新被替换数字的值和位权
        Pow[d[i]] = p;
    }
    const int len = str.size();
    ll ans = 0;
    for(int i = 0; i<len; i++) {//遍历原字符串每一位
        //原有结果乘以当前位的位权 加上当前位的值
        ans = (ans*Pow[str[i]-'0']%mod+val[str[i]-'0'])%mod;
    }
    printf("%lld\n", ans);
    return 0;
}
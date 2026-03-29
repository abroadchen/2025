//
// Created by Psy.C on 2026/3/28.
//
/**
s: 目标和
x: 目标异或值
n = s - x：计算进位相关的部分
如果n < 0，说明x > s，不可能存在满足条件的a,b
如果n是奇数，由于每次进位会同时影响和与异或的关系，n必须是偶数
m = n>>1：将n右移一位，相当于除以2，得到实际的进位位模式
ans = 1：初始化答案为1

循环逐位检查x和m：
第一条件：if (x&1 && m&1)
当x的当前位为1且m的当前位也为1时，输出0
原因：如果x的某一位是1，说明a和b在这一位上不同（一个0一个1），那么a+b在这一位不应该产生进位，所以m的对应位应该是0
第二条件：if (x&1) ans<<=1
当x的当前位为1时，ans乘以2
原因：x的这一位为1表示a和b在这一位上不同（一个0一个1），有两种可能：(a的该位=0,b的该位=1) 或 (a的该位=1,b的该位=0)
移位操作：x>>=1; m>>=1;
继续处理下一位

如果n=0，意味着s=x，即a+b = a⊕b，这表示没有进位
在这种情况下，我们排除了a=0,b=x和a=x,b=0这两种情况（因为题目可能要求a,b都大于0，或者为了避免重复计算）
实际上，当n=0时，a+b=a⊕b，只有当a和b的二进制表示没有相同位置都为1时才成立


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll s, x;
int main() {
    fast;
    cin >> s >> x;
    ll n = s - x;
    if (n < 0 || n%2) {
        cout << "0\n";
        return 0;
    }
    ll m = n>>1, ans = 1;
    while (x) {
        if (x&1 && m&1) {
            cout << "0\n";
            return 0;
        }
        if (x&1) ans<<=1;
        x>>=1; m>>=1;
    }
    if (!n) ans -= 2;
    cout << ans << '\n';
    return 0;
}
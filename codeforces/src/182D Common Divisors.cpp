//
// Created by Psy.C on 2025/12/1.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define sz(x) (static_cast<int>((x).size()))
using namespace std;

constexpr int ha = 157, mod = 1e18+7;
int get(const string& s) {//计算字符串的哈希值，参数为常量引用避免拷贝
    const int n = sz(s);
    int res = 0;
    for (int i = 0; i < n; ++i) {//遍历字符串中的每个字符
        res *= ha;//乘以基数
        res %= mod;
        res += s[i] - 'a';//字符转换为数字('a'=0, 'b'=1, ...)加到哈希值中
    }
    return res % mod;
}

string f(string s, const int c) {//将字符串s重复c次后返回
    const string s1 = s;//保存原始字符串s的副本
    int cs = sz(s);
    const int len = cs, mb = c * cs;//len保存原字符串长度，mb是目标长度(c倍原长度)
    while (cs < mb) {//当前长度小于目标长度时继续扩展
        if (cs * 2 < mb) cs *= 2, s += s;//两倍当前长度仍小于目标长度，则将字符串翻倍
        else cs += len, s += s1;//直接加上原始字符串长度，并追加原始字符串
    }
    return s;//返回扩展后的字符串
}

signed main() {
    fast;
    string a, b; cin >> a >> b;
    string s;//临时字符串s用于构建前缀
    const int n = min(sz(a), sz(b)), la = sz(a), lb = sz(b),
    h1 = get(a), h2 = get(b); int ans = 0;
    for (int i = 0; i < n; ++i) {//遍历可能的前缀长度(从1到n)
        s += b[i];//将b的第i个字符添加到前缀s中
        if (la % (i + 1) == 0 && lb % (i + 1) == 0) {//当前前缀长度(i+1)是否能整除两个字符串的长度
            string s1 = f(s, la / (i + 1)),//构造两个新字符串：s1是前缀重复la/(i+1)次，s2是前缀重复lb/(i+1)次
                s2 = f(s, lb / (i + 1));
            const int t1 = get(s1), t2 = get(s2);
            if (t1 != h1 || t2 != h2) continue;//构造的字符串哈希值不匹配原字符串
            ans++;//符合条件的前缀计数加1
        }
    }
    cout << ans;
    return 0;
}
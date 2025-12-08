//
// Created by Psy.C on 2025/12/8.
//
/*
*n：字符串长度
m：可用颜色种类数（字母A到A+m-1）
cnt：修改次数计数器
 *
*寻找一个不同于字符a和b的有效字符
循环遍历从'A'到'A'+m-1的所有可用字符
跳过与a或b相同的字符
返回第一个不同的有效字符
如果找不到则返回0
 *
*n1：计算将字符串改为ABAB...模式需要的修改次数
n2：计算将字符串改为BABA...模式需要的修改次数
通过比较每个位置字符与理想模式的差异来统计
 *
*选择修改次数较少的模式输出：
如果n1更小，采用ABAB...模式
如果n2更小或相等，采用BABA...模式
输出修改次数和重构的字符串
然后直接返回，不执行后面的通用算法
 *
*从第二个字符开始遍历字符串
如果当前字符与前一个字符相同：
调用ok函数找到一个不同于前后字符的新字符替换当前字符
跳过下一个字符（i+=2），因为修改当前字符后不会影响下一个字符
增加修改计数器
如果当前字符与前一个字符不同，则继续检查下一个字符
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m, cnt;

char ok(const char a, const char b) {
    for (char i = 'A'; static_cast<int>(i) <= 'A' + m - 1; ++i) {
        if (i == a || i == b) continue;
        return i;
    }
    return 0;
}

int main() {
    fast;
    cin >> n >> m;
    string s; cin >> s;
    if (m == 2) {
        int n1 = 0, n2 = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] != 'A' + (i % 2)) n1++;
            else n2++;
        }
        if (n2 > n1) {
            cout << n1 << '\n';
            for (int i = 0; i < n; ++i) {
                if (i % 2 == 0) cout << 'A';
                else cout << 'B';
            }
        } else {
            cout << n2 << '\n';
            for (int i = 1; i <= n; ++i) {
                if (i % 2 == 0) cout << 'A';
                else cout << 'B';
            }
        }
        cout << '\n';
        return 0;
    }
    for (int i = 1; i < s.size();) {
        if (s[i] == s[i-1]) {
            s[i] = ok(s[i-1], s[i+1]);
            i += 2;
            cnt++;
        } else i++;
    }
    cout << cnt << '\n' << s << '\n';
    return 0;
}

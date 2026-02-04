//
// Created by Psy.C on 2026/2/3.
//
/**
* 时间复杂度：O(n)，其中n是字符串长度
空间复杂度：O(n)，用于存储字符串

回文性质：正读和反读相同
镜像性质：只包含上下或左右对称的字母（这些字母在镜子中看起来相同）
符合条件的字母 A,H,I,M,O,T,U,V,W,X,Y 都具有垂直对称轴，可以在垂直镜面中形成镜像
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100050
using namespace std;


int main() {
    fast;
    char c[N]; cin>>c;
    const int len = static_cast<int>(strlen(c));
    int flag = 0;
    for (int i = 0; i <= len>>1; ++i) {
        if (c[i] != c[len-1-i] || (c[i] != 'A' && c[i] != 'H' && c[i] != 'I'
            && c[i] != 'M' && c[i] != 'O' && c[i] != 'T' && c[i] != 'U'
            && c[i] != 'V' && c[i] != 'W' && c[i] != 'X' && c[i] != 'Y')) {
            flag = 1; break;
        }
    }
    if (flag) cout << "NO\n"; else cout << "YES\n";
    return 0;
}
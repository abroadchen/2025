#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define N 5010
using namespace std;

int g[N];
bool b[N];//最小未出现的非负整数
int dfs(const int len) {
    if (g[len] != -1) return g[len];
    memset(b,false,sizeof(b));
    b[dfs(len - 2)] = true;//删除中间一个元素后剩余的SG值标记
    for (int i = 1; i + i < len; ++i) b[dfs(i-1)^dfs(len-i-2)] = true;
    for (int i = 0; i < N; ++i) if (!b[i]) return g[len] = i;
    return 0;
}

char s[N];
int out (const int l, const int r) {
    int sum = 0;
    for (int i = l + 1; i <= r - 1; ++i) {
        if (s[i + 1] == s[i - 1]) {//对称位置
            int len = 0;
            while (s[i + 1] == s[i - 1] && i <= r - 1) i++, len++;//连续的对称段 统计长度
            sum ^= g[len];
        }
    }
    return sum;
}


int main() {
    fast;
    memset(g,-1,sizeof(g)); g[0] = 0, g[1] = 1;
    for (int i = 2; i < N; ++i) if (g[i] == -1) g[i] = dfs(i);//预计算所有长度的SG值
    while (scanf("%s", s) != EOF) {
        bool ok = true;
        for (int i = 1, len = strlen(s); i < len - 1; ++i) {//遍历字符串中每个位置作为删除点
            if (s[i - 1] != s[i + 1]) continue;
            if (out(0, i - 1) ^ out(i + 1, len - 1)) continue;//删除位置左右
            cout << "First\n" << i + 1 << '\n', ok = false;//删除位置
            break;
        }
        if (ok) cout << "Second\n";
    }
    return 0;
}
//
// Created by Psy.C on 2025/11/22.
//
/*
 *a:主串, b:模式串
 *n:模式串个数, la:主串长度, lb:模式串长度
 *nxt:KMP失败函数, f:匹配函数, ans:答案计数
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

constexpr int N = 1e5+10;
char a[N], b[N];
int n, la, lb, nxt[2][N], f[2][N], ans;

//构建KMP算法的失败函数(next数组)
void get(const char *p, const int k) {
    nxt[k][1] = 0;//第一个字符的失败函数值为0
    for (int i = 2, j = 0; i <= lb; ++i) {
        while (j > 0 && p[i] != p[j+1]) j = nxt[k][j];//当字符不匹配时，根据失败函数回退
        if (p[i] == p[j+1]) j++;//如果字符匹配，增加匹配长度
        nxt[k][i] = j;//记录当前位置的失败函数值
    }
}

void kmp(const char *s, const char *p, const int k) {
    for (int i = 1, j = 0; i <= la; ++i) {//遍历主串
        while (j > 0 && (j == lb || s[i] != p[j+1])) j = nxt[k][j];//当不匹配时，根据失败函数调整匹配位置
        if (s[i] == p[j+1]) j++;//如果字符匹配，增加匹配长度
        f[k][i] = j;//记录主串前i个字符与模式串的最大匹配长度
    }
}

int main() {
    scanf("%s", a + 1); scanf("%d", &n); la = strlen(a + 1);
    for (int i = 1; i <= n; ++i) {//处理每个模式串
        scanf("%s", b + 1); lb = strlen(b + 1);//读取第i个模式串b
        if (lb == 1) continue;//如果模式串长度为1
        get(b, 0); kmp(a, b, 0);//正向处理
        reverse(a + 1, a + la + 1); reverse(b + 1, b + lb + 1);
        get(b, 1); kmp(a, b, 1);//构建反向的失败函数
        for (int j = 1; j <= la; ++j) {//对匹配结果取前缀最大值
            f[0][j] = max(f[0][j-1], f[0][j]);//正向匹配的前缀最大值
            f[1][j] = max(f[1][j-1], f[1][j]);//反向匹配的前缀最大值
        }
        bool flag(false);//检查是否存在合法的删除方案
        for (int j = 1; j < la; ++j) {
            const int x = la - j;//后半部分长度
            if (!f[0][j] || !f[1][x]) continue;//如果前j个字符中有匹配且后x个字符中有匹配
            if (f[0][j] + f[1][x] >= lb) { flag = true; break; }//如果前后两部分的匹配长度之和≥模式串长度，说明可以构造
        }
        if (flag) ans++;//如果可以构造，计数器加1
        reverse(a + 1, a + la + 1);//恢复主串的原始顺序
    }
    printf("%d\n", ans);
    return 0;
}
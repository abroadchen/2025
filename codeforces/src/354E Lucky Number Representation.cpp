//
// Created by Psy.C on 2026/1/17.
//
/**
* c[10]: 记录每个个位数能被表示的方法数量
h[10][33]: 存储每个个位数对应的表示方法，h[digit][index]存储具体表示方式
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int c[10], h[10][33];
void init() {
    memset(c, 0, sizeof(c));
    for (int i = 0; i <= 6; ++i) for (int j = 0; i + j <= 6; ++j) {
        const int t = (i*4 + j*7) % 10;//计算个位数
        h[t][c[t]++] = i + j * 10;//存储这种表示方式
    }
}

char s[20];//输入字符串
bool flag;//是否找到解
int ans[20], m;//每位置的答案 字符串长度
void dfs(const int d, const int ca) {//d:当前处理的位置, ca:进位
    if (d == -1) {//已处理完所有位置
        if (ca == 0) flag = true;//找到了解
        return;
    }
    int k = s[d] - '0' - ca, p = 0;//当前位置需要的数值，减去进位
    if (k < 0) {
        if (d == 0) return;//最左边一位
        p = 1;//借位标志
        k = (k + 10) % 10;//调整k值
    }
    for (int i = 0; i < c[k]; ++i) {//遍历所有可能的表示方法
        if (flag) return;//找到解
        const int t = h[k][i];//获取第i种表示方法
        ans[m - 1 - d] = t;//存储当前位的表示方法
        dfs(d - 1, p + ((t/10)*7+(t%10)*4)/10);//递归处理下一位，计算新的进位
    }
}

void out() {
    if (flag == false) {//没找到解
        cout << "-1\n"; return;
    }
    char a[6][25] = {};
    for (int i = 0; i < m; ++i) {//对每一位进行处理
        int x = ans[i] % 10, y = ans[i] / 10;//x:4的个数, y:7的个数
        for (auto& j : a) {//遍历6行数组
            if (x-- > 0) j[i] = '4';//还有4可用
            else if (y-- > 0) j[i] = '7';
            else j[i] = '0';
        }
    }
    for (int j, i = 0; i < 6; ++i) {//输出6个数字
        for (j = m - 1; j >= 0 && (a[i][j]==0||a[i][j]=='0'); --j) {}//找到有效数字的最高位
        if (j < 0) cout << '0'; else {
            for (; j >= 0; --j) cout << a[i][j];//从高位到低位输出
        }
        cout << ' ';//数字间空格分隔
    }
    cout << '\n';
}


int main() {
    fast;
    init();
    int n; cin >> n;
    while (n--) {
        cin >> s; m = static_cast<int>(strlen(s));
        memset(ans, 0, sizeof(ans));
        flag = false;//重置flag
        dfs(m - 1, 0);//从最后一位开始DFS，初始进位为0
        out();
    }
    return 0;
}
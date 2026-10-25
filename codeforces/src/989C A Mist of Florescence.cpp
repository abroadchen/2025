//
// Created by Psy.C on 2026/10/25.
//

/**
真正学会的起点..
s：50×50 网格（+边界预留）。
init(x,y,ch)：把以 (x,y) 为左上角的 25×25 子块全部填充为 ch。这里 x、y 是"偏移基准"，实际左上角是 (x+1, y+1)（因为 rep 从1开始）。
get(x,y,ch,num)：在以 (x,y) 为基准的 25×25 区域内，用间隔2的行列（i=1,3,5,...25，j=1,3,...）逐个位置填 ch，共填 num 个（填满即停）。这些是间隔点，用于切分底色
读入 4 个数 num[1..4]，对应 A、B、C、D 的目标连通块数，并各自减1。

用 init 铺四块底色：

init(0,0,'C')：左上 25×25 填 C（实际区域 1..25 × 1..25）

init(0,25,'D')：右上填 D

init(25,25,'A')：右下填 A

init(25,0,'B')：左下填 B

每块初始是单一颜色的一大块连通块（1块）。所以一开始 A/B/C/D 各有 1 个连通块。
num[i]--：因为我们后面要往别的大块里"加"该颜色的块，目标是 num[i]（减过1以后的）——即需要在初始1块的基础上再增加 num[i] 块

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=(n); i++)
using namespace std;

constexpr int N = 57;

char s[N][N];
void init(int x, int y, char ch) {
    int i, j;
    rep(i,25) rep(j,25) s[x+i][y+j] = ch;
}
void get(int x, int y, char ch, int num) {
    for (int i = 1; i <= 25 && num; i += 2)
        for (int j = 1; j <= 25 && num; j += 2) {
            s[x+i][y+j] = ch;
            num--;
        }
}

int num[7], i, j;
int main() {
    fast;
    rep(i,4) cin >> num[i], num[i]--;
    init(0, 0, 'C'); init(0,25,'D'); init(25,25,'A'); init(25,0,'B');
    get(0,0,'A',num[1]); get(0,25,'B',num[2]);
    get(25,25,'C',num[3]); get(25,0,'D',num[4]);
    cout << "50 50\n";
    rep(i,50) {
        rep(j,50) cout << s[i][j];
        cout << '\n';
    }
    return 0;
}
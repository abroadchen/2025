//
// Created by Psy.C on 2025/11/14.
//
/*
*re 将所有字符转换为小写
将'u','d','l','r'分别替换为指定的字符U,D,L,R
 *
*dfs 在n×m网格上从点(a,b)到点(c,d)的最短距离，使用特定规则：
规范化坐标以确保一致的排序
处理1×m、2×2等特殊情况
根据网格属性（奇偶维度、奇偶性）返回不同的公式
 *
 *nxt 按照螺旋或边界遍历模式计算下一个位置
 *rev 反转路径字符串并相应地调整方向
*solve 在n×m网格上生成从点(a,b)到点(c,d)的路径，使用多种策略：
主要策略：
坐标规范化：确保一致的方向
特殊情况处理：
单行网格（简单水平移动）
两行网格的特定约束
分治法：
水平或垂直分割网格
寻找最佳分割点
边界遍历：对于边缘情况，沿着网格边界移动
螺旋模式：对于较大的网格，使用螺旋遍历模式
对称性利用：使用反射来简化复杂情况
 *
*读取网格维度和起始/结束位置
调用solve生成路径
输出路径长度和路径中的所有坐标
 *
 *
 *
 */
#include <algorithm>
#include <iostream>
#define rep(i,n) for(int i=1;i<=(n);++i)
#define sz(x) ((int)(x).size())
using namespace std;


string re(string s, char U, char D, char L, char R) {
    for_each(s.begin(), s.end(), [&](char& x) {
        x += 'a' - 'A';
    });
    replace(s.begin(), s.end(), 'u', U);
    replace(s.begin(), s.end(), 'd', D);
    replace(s.begin(), s.end(), 'l', L);
    replace(s.begin(), s.end(), 'r', R);
    return s;
}

int dfs(int n, int m, int a, int b, int c, int d) {
    if (n > m) return dfs(m, n, b, a, d, c);
    if (a > c) return dfs(n, m, n - a + 1, b, n - c + 1, d);//沿水平中线翻转网格
    if (b > d) return dfs(n, m, a, m - b + 1, c, m - d + 1);//沿垂直中线翻转网格
    if (a == c && b == d) return 0;//起点和终点相同
    if (n == 1) return abs(b - d);//只有一行，距离就是列坐标的绝对差值
    //2行网格且不在同一行且列差不超过1
    if (n == 2 && a != c && d - b <= 1) return max(b + d - 1, m + m - b - d + 1);
    //如果网格总面积为奇数，返回n*m-1-((a+b)的奇偶性)-((c+d)的奇偶性)
    if ((n*m)&1) return n*m - 1 - ((a + b)&1) - ((c + d)&1);
    if (n == 3 && ((a+b+c+d)&1) && ((d - b >= 2 && ((a+b)&1)) ||
        (a == 2 && c == 2 && (b&1)))) return n * m - 3;
    return n*m - 1 - !((a+b+c+d)&1);
}
//计算当前位置(a,b)的下一个位置，ty是类型参数
void nxt(int ty, int n, int m, int a, int b, int& c, int& d, char& dir) {
    c = a, d = b;//初始化下一个位置为当前位置
    //如果在第一行或最后一行，且不在角落位置
    if ((a == 1 && (b != (!ty ? m : 1))) || (a == n && (b != (!ty ? 1 : m)))) {
        if (ty ^ (a == 1)) ++d, dir = 'R';//根据ty值和行号决定向右或向左移动
        else --d, dir = 'L';
    } else {//在第一列或最后一列，决定向上或向下移动
        if (ty ^ (b == 1)) --c, dir = 'U';
        else ++c, dir = 'D';
    }
}

string rev(string s) {//上下颠倒，左右颠倒
    reverse(s.begin(), s.end());
    return re(s, 'D', 'U', 'R', 'L');
}
//生成从(a,b)到(c,d)的路径
string solve(int n, int m, int a, int b, int c, int d) {
    int v = dfs(n, m, a, b, c, d);//计算最短距离保存在v中
    //如果行数大于列数，交换行列参数递归调用，并转换方向字符
    if (n > m) return re(solve(m, n, b, a, d, c), 'L', 'R', 'U', 'D');
    //起点行号大于终点行号，沿水平中线翻转后递归调用
    if (a > c) return re(solve(n, m, n-a+1, b, n-c+1, d), 'D', 'U', 'L', 'R');
    //起点列号大于终点列号，沿垂直中线翻转后递归调用
    if (b > d) return re(solve(n, m, a, m-b+1, c, m-d+1), 'U', 'D', 'R', 'L');
    if (n == 1) return string(d - b, 'R');//只有1行，直接返回向右移动(d-b)步的字符串
    //如果是2行且不在同一行且列差不超过1，根据比较结果返回两种不同的路径
    if (n == 2 && a != c && abs(b - d) <= 1) {
        if (b + d - 1 > m + m - b - d + 1) return string(b - 1, 'L') + "D" + string(d - 1, 'R');
        return string(m - b, 'R') + "D" + string(m - d, 'L');
    }
    //尝试水平分割网格，在第i行处分割，找到最优分割点j，递归生成上下两部分路径
    for (int i = a; i < c; ++i) rep(j,m) {
        if (dfs(i, m, a, b, i, j) + dfs(n - i, m , 1, j, c - i, d) + 1 == v)
            return solve(i, m, a, b, i, j) + "D" + solve(n - i, m, 1, j, c - i, d);
    }
    //尝试垂直分割网格，在第i列处分割，找到最优分割点j，递归生成左右两部分路径
    for (int i = b; i < d; ++i) rep(j,n) {
        if (dfs(n, i, a, b, j, i) + dfs(n, m - i, j, 1, c, d - i) + 1 == v)
            return solve(n, i, a, b, j, i) + "R" + solve(n, m - i, j, 1, c, d - i);
    }
    int f1 = (a == 1 || a == n || b == 1 || b == m),
        f2 = (c == 1 || c == n || d == 1 || d == m);//判断起点和终点是否在网格边界上
    if ((f1 || f2) && n > 3) {//如果起点或终点在边界上且行数大于3
        int fl = 0;
        //如果起点不在边界而终点在边界，则交换起点终点
        if (!f1 && f2) swap(f1, f2), fl = 1, swap(a, c), swap(b, d);
        string S;
        int ty = (a == 1 && b == 2) || (a == 2 && b == m) || (a == n && b == m - 1) ||
            (a == n - 1 && b == 1), ta = a, tb = b;//初始化字符串S和类型参数ty，保存原始位置ta,tb
        while (1) {//沿着边界移动直到回到起点附近，记录路径
            int ox, oy; char dir;
            nxt(ty, n, m, a, b, ox, oy, dir);
            if (ox == ta && oy == tb) {
                if (a == 1) ++a, S += "D";
                else if (a == n) --a, S += "U";
                else if (b == 1) ++b, S += "R";
                else --b, S += "L";
                break;
            }
            a = ox, b = oy, S += dir;
        }
        //递归解决内部(n-2)×(m-2)子网格问题，根据fl标志决定是否反转结果
        S += solve(n - 2, m - 2, a - 1, b - 1, c - 1, d - 1);
        return fl ? rev(S) : S;
    }
    if (n != 3) {//如果不是3行网格，初始化字符串S，如果n是偶数则交换行列参数
        string S; int fl = !(n&1);
        if (fl) swap(n, m), swap(a, b), swap(c, d);
        //如果起点行号在下半部分，则翻转后递归调用
        if (a > ((n + 1) >> 1)) return re(solve(n, m, n - a + 1, b, n - c + 1, d), 'D', 'U', 'L', 'R');
        //生成螺旋状路径：向上a-1步，向右m-b步，向下n-1步，向左m-1步，向上n-1步，向右1步
        S += string(a - 1, 'U'); S += string(m - b, 'R');
        S += string(n - 1, 'D'); S += string(m - 1, 'L');
        S += string(n - 1, 'U'); S += "R";
        //重复添加向右(b-3)步、向下1步、向左(b-3)步、向下1步的模式
        rep(i,a>>1) S += string(b - 3, 'R') + "D" + string(b - 3, 'L') + "D";
        //重复添加向下、向右、向上、向右/向上的模式
        rep(i,(m>>1)-1) S += string(n - a - 2, 'D') + "R" + string(n - a - 2, 'U') + (i != (m>>1)-1?"R":"U");
        //重复添加向上、向左、向下、向左的模式
        rep(i,(m-b-1)>>1) S += string(a - 2, 'U') + "L" + string(a - 2, 'D') + (i != ((m-b-1)>>1)?"L":"");
        //如果之前交换过行列参数，则转换方向字符后返回
        return fl ? re(S, 'L', 'R', 'U', 'D') : S;
    }
    //如果起点在第3行或特定条件，通过对角线翻转后递归调用
    if (a == 3 || (a == 2 && c == 3)) return rev(re(solve(n, m, n-c+1, m-d+1, n-a+1, m-b+1), 'D', 'U', 'R', 'L'));
    //如果起点在第1行且在同一列，采用特定分割策略
    if (a == 1 && b == d && dfs(n, b - 1, 1, b - 1, c ^ 1, b - 1) + dfs(n, m - b, c ^ 1, 1, c, 1) + 4 == v) {
        return "L" + solve(n, b - 1, 1, b - 1, c ^ 1, b - 1) + "RR" + solve(n, m - b, c ^ 1, 1, c, 1) + "L";
    }
    //另一种特定分割策略
    if (a == 1 && b == d && dfs(n, m - b, 1, 1, c ^ 1, 1) + dfs(n, b - 1, c ^ 1, b - 1, c, b - 1) + 4 == v) {
        return "R" + solve(n, m - b, 1, 1, c ^ 1, 1) + "LL" + solve(n, b - 1, c ^ 1, b - 1, c, b - 1) + "R";
    }
    //默认情况：生成蛇形路径模式
    string S; S += string(m - b, 'R'); S += "D";
    rep(i,(m-b-1)>>1) S += "DLUL"; S += "L";
    rep(i,(b-1)>>1) S += "LULD"; S += "D"; S += string(b, 'R');
    return S;
}


int main() {
    int n, m, a, b, c, d; scanf("%d%d%d%d%d%d", &n, &m, &a, &b, &c, &d);
    string res = solve(n, m, a, b, c, d);
    printf("%d\n", sz(res) + 1);//输出路径步数加1（包括起始位置）
    for (int i = 0, x = a, y = b; i <= sz(res); ++i) {
        if (i) {//如果不是第一个位置，则根据前一步的方向字符更新当前位置
            if (res[i - 1] == 'U') --x;
            else if (res[i - 1] == 'D') ++x;
            else if (res[i - 1] == 'L') --y;
            else ++y;
        }
        printf("%d %d\n", x, y);//输出当前位置坐标
    }
    return 0;
}
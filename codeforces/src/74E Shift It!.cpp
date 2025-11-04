//
// Created by Psy.C on 2025/11/4.
//
/*
*定义常量N为6（表示6x6矩阵）
定义二维数组a存储矩阵元素
定义字符串向量res存储操作步骤
*sw1函数：生成向上和水平移动的操作序列
将行列索引转换为字符('1'-'6')
*重复3次ULUR模式，最后再加一个U操作
这些操作会使某个位置的元素在不改变其他元素相对位置的情况下移动
*sw2函数：生成向右和垂直移动的操作序列
重复3次RURD模式，最后再加一个R操作
 *
*读取6x6矩阵的数据：
如果是数字字符('0'-'9')，转换为0-9的数值
如果是字母字符('A'-'F')，转换为10-15的数值
这表明输入是十六进制格式
 *
*对于目标位置(i,j)，其应该放置的值为i*N+j（即0-35）
在当前矩阵中查找该值的位置(x,y)
 *
*水平移动：将元素从当前位置y移动到目标位置j
通过循环左移的方式，每次将元素向左移动一位
调用sw1生成相应的操作步骤
 *
*垂直移动：将元素从当前位置x移动到目标位置i
通过循环上移的方式，每次将元素向上移动一位
调用sw2生成相应的操作步骤
 *
*输出总操作步数
依次输出每一步操作
 */
#include <algorithm>
#include <iostream>
#include <vector>
#define rep(i,n) for(int i=0;i<(n);++i)
using namespace std;

typedef long long ll;
const ll N = 6;
ll a[N][N];
vector<string> res;

void sw1(ll i, ll j) {
    string x(""); x += (char)(i + '1');
    string y(""); y += (char)(j + '1');
    rep(p,3) {
        res.push_back("U" + y);
        res.push_back("L" + x);
        res.push_back("U" + y);
        res.push_back("R" + x);
    }
    res.push_back("U" + y);
}

void sw2(ll i, ll j) {
    string x(""); x += (char)(i + '1');
    string y(""); y += (char)(j + '1');
    rep(p,3) {
        res.push_back("R" + x);
        res.push_back("U" + y);
        res.push_back("R" + x);
        res.push_back("D" + y);
    }
    res.push_back("R" + x);
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    rep(i,N) rep(j,N) {
        char c; cin>>c;
        if (c >= '0' && c <= '9') a[i][j] = c-'0';
        else a[i][j] = c - 'A' + 10;
    }
    rep(i,N) rep(j,N) {
        ll x(-1), y(-1);
        rep(k,N) rep(l,N) {
            if (a[k][l] == i * N + j) {
                x = k; y = l; break;
            }
        }
        while (y != j) {
            ll nxt = (y - 1 + N) % N;
            swap(a[x][y], a[x][nxt]);
            sw1(x, nxt);
            y = nxt;
        }
        while (x != i) {
            ll nxt = (x - 1 + N) % N;
            swap(a[x][y], a[nxt][y]);
            sw2(nxt, y);
            x = nxt;
        }
    }
    cout << res.size() << "\n";
    for (auto u : res) cout << u << "\n";
    return 0;
}
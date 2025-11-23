//
// Created by Psy.C on 2025/11/22.
//
/*
 *dp[l][r][i][j] 表示区间[l,r]两端着色为i和j的方案数
 *0-未着色，1-红色，2-蓝色
 */
#include <iostream>
#include <map>
#include <stack>
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;

typedef long long ll;
constexpr int N = 705, mod = 1000000007;
string str;//括号字符串
stack<int> s;//匹配括号
map<int, int> pos;//括号匹配位置
ll dp[N][N][3][3];

void get() {//找出每个括号的匹配位置
    rep(i,str.size()) {
        if (str[i] == '(') s.push(i);//左括号入栈
        else {
            pos[i] = s.top();//右括号匹配栈顶左括号
            pos[s.top()] = i;//左括号匹配当前右括号
            s.pop();//弹出已匹配的左括号
        }
    }
}

void dfs(const int l, const int r) {
    if (l + 1 == r) {//相邻的括号对
        dp[l][r][0][1] = dp[l][r][1][0] = 1;//一端红色一端未着色
        dp[l][r][0][2] = dp[l][r][2][0] = 1;//一端蓝色一端未着色
        return;
    }
    if (pos[l] == r) {//如果l和r是匹配的括号对
        dfs(l + 1, r - 1);//递归处理内部区间
        rep(i,3) rep(j,3) {//根据内部状态更新当前区间状态
            if (j != 1) dp[l][r][0][1] = (dp[l][r][0][1]+dp[l+1][r-1][i][j])%mod;//左端不是红色时，右端可以是红色
            if (j != 2) dp[l][r][0][2] = (dp[l][r][0][2]+dp[l+1][r-1][i][j])%mod;//左端不是蓝色时，右端可以是蓝色
            if (i != 1) dp[l][r][1][0] = (dp[l][r][1][0]+dp[l+1][r-1][i][j])%mod;//右端不是红色时，左端可以是红色
            if (i != 2) dp[l][r][2][0] = (dp[l][r][2][0]+dp[l+1][r-1][i][j])%mod;//右端不是蓝色时，左端可以是蓝色
        }
        return;
    }
    const int mid = pos[l]; dfs(l, mid); dfs(mid + 1, r);//分治情况：l与中间某位置mid匹配
    //合并两个区间的状态 不能相邻同色（k==1&&p==1表示都是红色，k==2&&p==2表示都是蓝色）
    rep(i,3) rep(j,3) rep(k,3) rep(p,3) if (!(k==1&&p==1) && !(k==2&&p==2)) {
        dp[l][r][i][j] = (dp[l][r][i][j]+dp[l][mid][i][k]*dp[mid+1][r][p][j])%mod;//左区间右端色k，右区间左端色p，且不冲突
    }
}

int main() {
    ostream::sync_with_stdio(false);
    cin >> str; get(); dfs(0, static_cast<int>(str.size())-1);
    ll ans = 0;
    rep(i,3) rep(j,3) ans = (ans + dp[0][str.size()-1][i][j])%mod;
    cout << ans << '\n';
    return 0;
}
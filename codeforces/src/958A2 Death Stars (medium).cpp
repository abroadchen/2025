//
// Created by Psy.C on 2026/10/20.
//
/**
a 是 n×m，b 是 m×n
外层 rep(i, n-m+1)：i 从 1 到 n-m+1（因为要有连续 m 行，起点最多 n-m+1）。
对每个起点 i，构造一个 vector<char> v，内容是 a 中第 i..i+m-1 行、第 1..m 列这一整块 m×m 的字符，按行拼接成的一维序列。
把 mp[v] = i —— 用整个 m×m 块的内容（拼成 vector）作为 key，起点行号 i 作为 value 存入 map
外层 rep(i, n-m+1)：i 作为列起点（1..n-m+1）。
构造 v：取 b 中第 i..i+m-1 列、第 1..m 行的 m×m 块。注意拼接顺序：外层 rep(j,m) 遍历行 j（1..m），内层 for (int k=i; k<=i+m-1; ++k) 遍历列——所以是按"先第 j 行的 i..i+m-1 列"逐行放入。
如果这个 v 在 map 里能找到（mp.contains(v)），即与 a 中某个块的字符序列完全相同，则输出 mp[v]（a 中块的起点行号）和 i（b 中块的起点列号），程序结束。
找不到任何匹配，则什么都不输出（正常退出）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

constexpr int N = 2e3+10;

int n, m;
char a[N][N], b[N][N];
map<vector<char>, int> mp;
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) rep(j,m) cin >> a[i][j];
    rep(i,m) rep(j,n) cin >> b[i][j];
    rep(i,n-m+1) {
        vector<char> v;
        for (int j = i; j <= m+i-1; ++j) rep(k,m)
            v.push_back(a[j][k]);
        mp[v] = i;
    }
    rep(i,n-m+1) {
        vector<char> v;
        rep(j,m) for (int k = i; k <= i+m-1; ++k)
            v.push_back(b[j][k]);
        if (mp.contains(v)) {
            cout << mp[v] << ' ' << i;
            return 0;
        }
    }
    return 0;
}

/**

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
constexpr int N = 2e3 + 10;
constexpr ull B = 911382323ull, C = 972663749ull;

int n, m;
char a[N][N], b[N][N], bt[N][N];

// 行方向滚动哈希: 输入 mat(n×m char, 1-indexed)，输出行哈希 rowHash[i][j]
// rowHash[i][j] = hash(mat[i][1..j])
void rowHash(char mat[N][N], ull h[N][N]) {
    for (int i = 1; i <= n; i++) {
        h[i][0] = 0;
        for (int j = 1; j <= m; j++)
            h[i][j] = h[i][j-1] * B + (ull)(mat[i][j] - 'a' + 1);
    }
}

// 由行哈希构造每个 m×m 块的二维哈希: blkVal[r][c] 表示左上角 (r,c) 的 m×m 块哈希值
// 需要 pw 幂表、powC 用于纵向合并
void buildBlock(ull rowHash[N][N], ull pw[], ull pwC[], int rmax, int cmax,
                ull blk[N][N]) {
    // 先在"扩展列"上用行哈希算出每个横向 m 段的哈希（存到临时 col 矩阵）
    static ull col[N][N]; // col[r][c] = 以 r 为行、c 起始的横向 m 字符段哈希
    for (int r = 1; r <= n; r++)
        for (int c = 1; c + m - 1 <= cmax; c++)
            col[r][c] = rowHash[r][c+m-1] - rowHash[r][c-1] * pw[m];

    // 再纵向合并 m 行，得到块哈希
    for (int r = 1; r + m - 1 <= rmax; r++)
        for (int c = 1; c + m - 1 <= cmax; c++)
            blk[r][c] = 0;
    // 纵向滚动: 先放第一行, 再逐行平移
    for (int c = 1; c + m - 1 <= cmax; c++) {
        ull cur = 0;
        for (int r = 1; r <= m; r++)
            cur = cur * C + col[r][c];          // 先填前 m 行
        blk[1][c] = cur;
        for (int r = 2; r + m - 1 <= rmax; r++) {
            cur = cur * C + col[r+m-1][c]
                - col[r-1][c] * powC[m];
            blk[r][c] = cur;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    cin >> n >> m;

    // 读矩阵（本题保证 b 是 m×n）
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> a[i][j];
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) cin >> b[i][j];

    // 把 b 转置为 bt (n×m)：bt[x][y] = b[y][x]
    for (int x = 1; x <= n; x++)
        for (int y = 1; y <= m; y++) bt[x][y] = b[y][x];

    // 预处理幂表
    ull pw[N];  // B 的幂
    ull pwC[N]; // C 的幂
    pw[0] = pwC[0] = 1;
    for (int i = 1; i <= N-1; i++) { pw[i] = pw[i-1] * B; pwC[i] = pwC[i-1] * C; }

    // 计算 a 和 bt 的块哈希
    ull rowA[N][N], rowB[N][N], blkA[N][N], blkB[N][N];
    rowHash(a, rowA);  rowHash(bt, rowB);
    buildBlock(rowA, pw, pwC, n, m, blkA);
    buildBlock(rowB, pw, pwC, n, m, blkB);

    // 把 a 的所有 m×m 块哈希放入 map（值记录左上角行、列）
    unordered_map<ull, pair<int,int>> mp;
    int lim = n - m + 1;
    for (int r = 1; r <= lim; r++)
        for (int c = 1; c <= lim; c++)
            mp[blkA[r][c]] = {r, c};

    // 扫描 bt 的所有块，命中即输出
    for (int r = 1; r <= lim; r++)
        for (int c = 1; c <= lim; c++)
            if (mp.count(blkB[r][c])) {
                auto [ar, ac] = mp[blkB[r][c]];
                cout << ar << ' ' << ac << ' ' << r << ' ' << c << '\n';
                return 0;
            }

    cout << "No match\n";
    return 0;
}



// 转置：把 n×m 的 b 转成 m×n，便于统一为"横向滑动"
void transpose() {
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) b[i][j] = b[i][j];
}

// 判断 a 中以 (r,c) 为左上角、b 中以 (r,c) 为左上角的 m×m 块是否相等
bool blockEqual(int r, int c) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            if (a[r+i][c+j] != b[r+i][c+j]) return false;
    return true;
}

// 朴素：枚举所有可能的左上角 (r,c)，范围 1..n-m+1
pair<int,int> solve() {
    for (int r = 1; r + m - 1 <= n; r++)
        for (int c = 1; c + m - 1 <= n; c++)
            if (blockEqual(r, c)) return {r, c};
    return {-1, -1};
}

 */
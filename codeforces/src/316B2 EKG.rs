use std::io;

fn find(fa: &mut Vec<usize>, x: usize) -> usize {//fa 数组的可变引用，查找的节点 x
    if fa[x] != x { fa[x] = find(fa, fa[x]); }
    fa[x]//返回根节点
}
//从节点 x 到环的路径    fa 数组引用、当前节点、当前距离、要修改的 site 和 color、节点总数
fn dfs(fa: &Vec<usize>, x: usize, dis: i32, site: &mut i32, color: &mut usize, n: usize) {
    if fa[x] == x { *color = x; *site = dis; return; }//自己指向自己
    dfs(fa, fa[x], dis + 1, site, color, n);
}

fn main() {
    let stdin = io::stdin();
    let mut input = String::new();
    stdin.read_line(&mut input).unwrap();
    let parts: Vec<usize> = input.trim().split_whitespace()
        .map(|x| x.parse().unwrap()).collect();
    let n = parts[0];//节点总数
    let x = parts[1];//目标节点
    let mut fa = vec![0; n + 1];
    input.clear();
    stdin.read_line(&mut input).unwrap();
    let nums: Vec<i32> = input.trim().split_whitespace()
        .map(|x| x.parse().unwrap()).collect();
    for i in 1..=n {
        fa[i] = nums[i - 1] as usize;
        if fa[i] == 0 { fa[i] = i; }//如果父节点为0（表示没有父节点），设置自己为父节点（形成自环）
    }
    let mut site = 0;//到目标环的距离
    let mut color = 0;//环的标识
    dfs(&fa, x, 1, &mut site, &mut color, n);
    for i in 1..=n { find(&mut fa, i); }//将每个节点直接连接到根节点
    let mut h = vec![0; 10_005];
    for i in 1..=n {
        if fa[i] != color { h[fa[i]] += 1; }//如果节点不在目标环中，统计其所属环的节点数量
    }
    let mut t = 0;//不同环的数量
    let mut a = vec![0; 1_005];//每个环的大小
    for i in 1..=n { if h[i] != 0 { t += 1; a[t] = h[i]; } }//非零的环大小存入数组 a
    let mut dp = vec![vec![false; 1_050]; 1_050];
    dp[0][0] = true;//不选择任何元素的状态可达
    for i in 1..=t {//环遍历每个环
        for j in 0..=n {//遍历所有可能的和
            if dp[i-1][j] {//如果之前状态 dp[i-1][j] 可达，则当前状态 dp[i][j] 也可达
                dp[i][j] = true;
                if j + a[i] <= n { dp[i][j + a[i]] = true; }//加上当前环大小不超过限制
            }
        }
    }
    for i in 0..=n {//遍历所有可达的状态
        if dp[t][i] { println!("{}", i + site as usize); }
    }
}
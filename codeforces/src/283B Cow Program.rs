/**
x：当前位置
j：当前状态（true或false）
vis：访问标记数组的可变引用
dp：DP数组的可变引用
a：输入数组的不可变引用
n：数组长度

根据当前状态j计算下一个位置y
如果j为true，向右移动a[x]步
如果j为false，向左移动a[x]步

如果y超出边界（≤0或>n），设置DP值为a[x]
否则继续递归

如果从位置y、状态!j可以到达边界
则当前位置x、状态j的DP值为从y开始的值加上a[x]
否则DP值保持为-1
*/
use std::io;

const N: usize = 200009;
fn dfs(x: usize, j: bool, vis: &mut [[bool; 2]; N], dp: &mut [[i64; 2]; N], a: &[i32], n: usize) {
    if vis[x][j as usize] { return; }
    vis[x][j as usize] = true;
    let y = if j { x as i32 + a[x] } else { x as i32 - a[x] };
    if y <= 0 || y > n as i32 { dp[x][j as usize] = a[x] as i64; }
    else {
        let y = y as usize;
        dfs(y, !j, vis, dp, a, n);
        if dp[y][(!j) as usize] != -1 {
            dp[x][j as usize] = dp[y][(!j) as usize] + a[x] as i64;
        }
    }
}

fn main() {
    loop {
        let mut input = String::new();
        if io::stdin().read_line(&mut input).is_err() { break }
        let n: usize = match input.trim().parse() {
            Ok(num) => num,//如果解析成功，赋值给n
            Err(_) => break
        };
        let mut dp = [[-1i64; 2]; N];
        let mut vis = [[false; 2]; N];
        let mut a = [0i32; N];
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let v: Vec<i32> = input.trim().split_whitespace()
            .map(|s| s.parse().unwrap()).collect();
        for (i, &val) in v.iter().enumerate() { a[i + 2] = val; }
        for i in 2..=n { dfs(i, false, &mut vis, &mut dp, &a, n); }
        for i in 2..=n {//对每个位置，如果DP值有效，加上额外的步数（i-1）
            if dp[i][0] != -1 { dp[i][0] += (i - 1) as i64; }
            println!("{}", dp[i][0]);
        }
    }
}
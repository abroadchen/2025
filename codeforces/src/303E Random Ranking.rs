/**
f[x][y] *= upp[i]: 如果第 i 个区间取值在其区间上半部分，那么状态 (x,y) 保持不变，但概率乘以 upp[i]
f[x][y] += f[x-1][y] * low[i]: 如果第 i 个区间取值在其区间左半部分，那么它应该被计入 x 类，所以从 (x-1,y) 状态转移过来
f[x][y] += f[x][y-1] * eq[i]: 如果第 i 个区间取值在其区间中间部分，那么它应该被计入 y 类，所以从 (x,y-1) 状态转移过来
*/
use std::io;

const EPS: f64 = 1e-9;
const N: usize = 80;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    let mut l = [0; N];
    let mut r = [0; N];
    let mut val = [0; N<<1];
    for i in 0..n {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let parts: Vec<i32> = input.trim().split_whitespace()
            .map(|s| s.parse().unwrap()).collect();
        l[i] = parts[0]; r[i] = parts[1];
        val[i<<1] = l[i]; val[i<<1|1] = r[i];//将所有区间端点存入 val 数组
    }
    val[..n*2].sort();
    let m = {//去重后的端点数量
        let mut uv = Vec::new();
        for &v in &val[..n*2] {
            if uv.is_empty() || *uv.last().unwrap() != v { uv.push(v); }
        }
        val[..uv.len()].copy_from_slice(&uv);
        uv.len()
    };
    let mut lo = [0.; N];//区间概率分布
    let mut eq = [0.; N];
    let mut h = [0.; N];
    let mut f = [[0.; N]; N];
    let mut ans = [[0.; N]; N];
    for s in 0..m - 1 {
        let sl = val[s];//遍历所有相邻端点形成的区间
        let sr = val[s + 1];
        for i in 0..n {
            if l[i] <= sl && sr <= r[i] {
                lo[i] = (sl - l[i]) as f64 / (r[i] - l[i]) as f64;
                eq[i] = (sr - sl) as f64 / (r[i] - l[i]) as f64;
                h[i] = (r[i] - sr) as f64 / (r[i] - l[i]) as f64;
            } else if r[i] <= sl { lo[i] = 1.; eq[i] = 0.; h[i] = 0.; } else {
                h[i] = 1.; eq[i] = 0.; lo[i] = 0.;
            }
        }
        for u in 0..n {
            if eq[u] < EPS { continue; }//跳过概率为0的情况
            for x in 0..n {
                for y in 0..n {
                    f[x][y] = 0.;//初始化 f 数组
                }
            }
            f[0][0] = eq[u];//设置初始状态
            let mut lim = 0i32;//考虑的区间数
            for i in 0..n {
                if u == i { continue; }
                lim += 1;
                if h[i] > 1. - EPS { continue; }//跳过上界概率为1的情况
                if lo[i] > 1. - EPS {
                    for x in (0..=lim).rev() {
                        for y in 0..=(lim - x) {
                            if x > 0 {
                                f[x as usize][y as usize] = f[x as usize - 1][y as usize];
                            } else {
                                f[x as usize][y as usize] = 0.;
                            }
                        }
                    }
                    continue;
                }
                for x in (0..=lim).rev() {
                    for y in (0..=(lim - x)).rev() {
                        f[x as usize][y as usize] *= h[i];
                        if x > 0 {
                            f[x as usize][y as usize] +=
                                f[x as usize - 1][y as usize] * lo[i]; }
                        if y > 0 { f[x as usize][y as usize] +=
                            f[x as usize][y as usize - 1] * eq[i]; }
                    }
                }
            }
            for x in 0..n {
                for y in 0..n {
                    if x + y >= n { break; }
                    let prob = f[x][y] / (y + 1) as f64;
                    ans[u][x] += prob;
                    if x + y + 1 < n { ans[u][x + y + 1] -= prob; }
                }
            }
        }
    }
    for i in 0..n {
        let mut ret = String::new();
        ret.push_str(&format!("{:.10}", ans[i][0]));
        for j in 1..n {
            ans[i][j] += ans[i][j-1];// 将差分数组转换为前缀和 第 i 个区间在排序后位置 ≤ j 的累积概率
            ret.push_str(&format!(" {:.10}", ans[i][j]));
        }
        println!("{}", ret);
    }
}
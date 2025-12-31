use std::io::{self, BufRead};

const N: usize = 1010;
const MOD: i64 = 1_000_000_007;
fn main() {
    let mut pw = [0i64; N];
    pw[0] = 1; pw[1] = 1;
    for i in 2..N { pw[i] = (2 * pw[i-1]) % MOD; }//2^i mod MOD
    let mut c = [[0i64; N]; N];
    for i in 0..N {
        for j in 0..=i {
            if i == 0 || j == 0 || i == j { c[i][j] = 1; } else {
                c[i][j] = (c[i-1][j] + c[i-1][j-1]) % MOD;
            }
        }
    }
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    let first_line = lines.next().unwrap().unwrap();
    let parts: Vec<i32> = first_line.split_whitespace().map(|s| s.parse().unwrap()).collect();
    let n = parts[0] as usize;
    let m = parts[1] as usize;
    let second_line = lines.next().unwrap().unwrap();
    let mut a: Vec<usize> = second_line.split_whitespace().map(|s| s.parse().unwrap()).collect();
    a.insert(0, 0);//添加一个占位符，使数组从索引1开始
    a.sort();
    let mut s = n - m;
    let mut ans = 1i64;
    for i in 2..=m {
        let w = a[i] - a[i-1] - 1;//相邻元素之间的间隔
        ans = (ans * c[s][w]) % MOD;// ans = (ans * C(s,w) * 2^w) % MOD
        ans = (ans * pw[w]) % MOD;
        s -= w;
    }
    ans = (ans * c[s][a[1] - 1]) % MOD;//a[1] - 1 就是第一个特殊元素前的空位数量，需要从剩余的 s 个位置中选择这些空位
    println!("{}", ans);
}
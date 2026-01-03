use std::io;

const MOD: i64 = 1_000_000_009;
const N: usize = 4005;

fn init(n: i32, w: i32, b: i32, c: &mut [[i64; N]; N], fac: &mut [i64; N]) {
    let t = n.max(w.max(b));//n、w、b中的最大值
    for i in 0..=t { c[i as usize][0] = 1; }//任何数选0个的组合数为1
    for i in 1..=t {
        for j in 1..=i {
            c[i as usize][j as usize] = (c[(i-1) as usize][j as usize] +
                c[(i-1) as usize][(j-1) as usize]) % MOD
        }
    }
    fac[0] = 1;
    for i in 1..=w.max(b) {//从1到w和b的最大值
        fac[i as usize] = (i as i64 * fac[(i-1) as usize]) % MOD;
    }
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<i32> = input.trim().split_whitespace()
        .map(|x| x.parse().unwrap()).collect();
    let n = parts[0] as i32;
    let w = parts[1] as i32;
    let b = parts[2] as i32;
    let mut ans = 0i64;
    let mut c = [[0i64; N]; N];
    let mut fac = [0i64; N];
    init(n, w, b, &mut c, &mut fac);
    for i in 1..=b {
        let mut res = (n - i - 1) as i64;
        if res == 0 { break; }
        res = res * c[(b-1) as usize][(i-1) as usize] % MOD;
        res = res * fac[b as usize] % MOD;
        res = res * c[(w-1) as usize][(n-i-1) as usize] % MOD;
        res = res * fac[w as usize] % MOD;
        ans = (ans + res) % MOD;
    }
    println!("{}", ans);
}
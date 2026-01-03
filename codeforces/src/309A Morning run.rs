use std::io;

fn main() {
    let mut input = String::new();
    while io::stdin().read_line(&mut input).unwrap() > 0 {
        let parts : Vec<i32> = input.trim().split_whitespace()
            .map(|s| s.parse().unwrap()).collect();
        if parts.len() != 3 { break; }
        let n = parts[0] as usize;
        let l = parts[1];
        let t = parts[2];
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let vals: Vec<i32> = input.trim().split_whitespace()
            .map(|s| s.parse().unwrap()).collect();
        let mut a = vec![0i64; 2 * n];
        for i in 0..n {
            a[i] = vals[i] as i64;//将输入的第i个值赋给数组a的第i个位置
            a[i + n] = a[i] + l as i64;//创建扩展数组
        }
        let k = 2 * t / l;
        let p = 2 * t % l;
        let mut ans = (k as f64) * (n as f64) * ((n - 1) as f64);
        let mut j = 0;
        for i in 0..n {
            while j < 2 * n && a[j] - a[i] <= p as i64 { j += 1; }
            ans += (j - i - 1) as f64;
        }
        println!("{:.10}", ans / 4.);
        input.clear();
    }
}
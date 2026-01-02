//统计满足 a² + b² = c² 且 a < t, b ≥ a, c ≤ t 的勾股数三元组 (a,b,c) 的个数
use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let t: i32 = input.trim().parse().unwrap();
    let mut cnt = 0;
    for i in 1..t {
        let mut j = i;
        loop {
            let x = i * i + j * j;
            if x > t * t { break; }
            let y = (x as f64).sqrt() as i32;
            if y * y == x { cnt += 1; }
            j += 1;
        }
    }
    println!("{}", cnt);
}
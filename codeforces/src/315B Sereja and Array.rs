use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    let first_line = lines.next().unwrap().unwrap();
    let parts: Vec<i32> = first_line.split_whitespace().map(|s| s.parse().unwrap()).collect();
    let n = parts[0] as usize;
    let m = parts[1] as i32;
    let mut a = vec![0i32; 100_001];
    let l2 = lines.next().unwrap().unwrap();
    let p2: Vec<i32> = l2.split_whitespace().map(|s| s.parse().unwrap()).collect();
    for i in 1..=n { if i - 1 < p2.len() { a[i] = p2[i - 1]; } }
    let mut cnt = 0i32;
    for _ in 0..m {
        let l3 = lines.next().unwrap().unwrap();
        let p3: Vec<i32> = l3.split_whitespace().map(|s| s.parse().unwrap()).collect();
        let t = p3[0];
        match t {
            1 => {//更新数组元素
                let v = p3[1] as usize;
                let x = p3[2];
                a[v] = x - cnt;
            },
            2 => { let y = p3[1]; cnt += y; },
            3 => {
                let q = p3[1] as usize; println!("{}", a[q] + cnt);
            },
            _ => {}
        }
    }
}
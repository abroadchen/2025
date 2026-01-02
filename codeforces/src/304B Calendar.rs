/**
s[(y - 1) as usize]: 从1900年到前一年的总天数
day[(m - 1) as usize]: 从1月到前一个月的总天数
d - 1: 当月的天数（减1是因为从0开始计数）
if check(y) && m >= 3: 如果是闰年且月份≥3，需要额外加1天（因为2月29日）
*/
use std::io;

fn ok(y: i32) -> bool {
    y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)
}

fn main() {
    let mut s = [0; 2100];
    let month = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
    let mut day = [0; 13];
    let mut sum = 0;
    for i in 1900..=2040 {
        sum += if ok(i) { 366 } else { 365 };
        s[i as usize] = sum;
    }
    for i in 1..13 { day[i] = day[i - 1] + month[i]; }
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<&str> = input.trim().split(':').collect();
    let y: i32 = parts[0].parse().unwrap();
    let m: i32 = parts[1].parse().unwrap();
    let d: i32 = parts[2].parse().unwrap();
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<&str> = input.trim().split(':').collect();
    let yy: i32 = parts[0].parse().unwrap();
    let mm: i32 = parts[1].parse().unwrap();
    let dd: i32 = parts[2].parse().unwrap();
    let mut d1 = s[(y - 1) as usize] + day[(m - 1) as usize] + d - 1;
    if ok(y) && m >= 3 { d1 += 1; }//闰年且月份 >= 3，需要加1天
    let mut d2 = s[(yy - 1) as usize] + day[(mm - 1) as usize] + dd - 1;
    if ok(yy) && mm >= 3 { d2 += 1; }
    let dif = (d1 - d2).abs();
    println!("{}", dif);
}
/**
wind.chars() 将字符串转换为字符迭代器
.enumerate() 为每个字符添加索引，返回 (索引, 字符) 元组
.take(t) 限制迭代次数为 t（时间步数）
for (i, c) 同时绑定索引 i 和字符 c
*/
use std::io::{self, BufRead};

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<&str> = input.trim().split(' ').collect();
    let t: usize = parts[0].parse().unwrap();//时间步数
    let mut sx: i32 = parts[1].parse().unwrap();//起始坐标 (sx, sy)
    let mut sy: i32 = parts[2].parse().unwrap();
    let ex: i32 = parts[3].parse().unwrap();//目标坐标 (ex, ey)
    let ey: i32 = parts[4].parse().unwrap();
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let wind = input.trim();//去除风向字符串末尾的换行符
    let mut time = -1;//表示未找到解决方案
    for (i, c) in wind.chars().enumerate().take(t) {
        match c {
            'E' => { if sx < ex { sx += 1; } },//向东移动
            'S' => { if sy > ey { sy -= 1; } },
            'W' => { if sx > ex { sx -= 1; } },
            'N' => { if sy < ey { sy += 1; } },
            _ => {}
        }
        if sx == ex && sy == ey { time = (i + 1) as i32; break; }//当前位置是否与目标位置匹配
    }
    println!("{}", time);
}
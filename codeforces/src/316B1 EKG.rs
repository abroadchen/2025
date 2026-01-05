use std::collections::HashSet;
use std::io;

fn main() {
    let stdin = io::stdin();
    let mut input = String::new();
    stdin.read_line(&mut input).unwrap();
    let parts: Vec<usize> = input.trim().split_whitespace()
        .map(|x| x.parse().unwrap()).collect();
    let n = parts[0];
    let mut x = parts[1] - 1;//Convert to 0-indexed
    input.clear();
    stdin.read_line(&mut input).unwrap();
    let mut a: Vec<i32> = input.trim().split_whitespace()
        .map(|x| x.parse::<i32>().unwrap() - 1).collect();//Convert to 0-indexed
    let mut ind = vec![0; n];//每个节点的入度
    //统计每个节点有多少条边指向它
    for &val in &a { if val >= 0 { ind[val as usize] += 1; } }//每个节点指向的下一个节点
    let mut b = Vec::new();//非循环链的长度
    let mut offset = 0;
    for i in 0..n {
        if ind[i] == 0 {//只处理入度为0的节点（链的起点）
            let mut len = 0;//链长度计数器
            let mut t = i as i32;//当前节点 t，从起点 i 开始
            let mut cnt = 0;//目标节点距离计数器
            let mut hit = false;//是否遇到目标节点
            while t != -1 {//当前节点不是-1（终点）时循环
                if hit { cnt += 1; }
                if t == x as i32 { hit = true; }//当前节点是目标节点
                //安全地获取下一个节点（边界检查）
                if t >= 0 && (t as usize) < a.len() { t = a[t as usize] } else { break; };
                len += 1;
            }
            //如果这条链经过了目标节点，记录到目标节点的距离 否则，将链长度加入 b 列表
            if hit { offset = cnt; } else { b.push(len); }
        }
    }
    let mut dp: HashSet<i32> = HashSet::new();
    dp.insert(0);//不选择任何块的情况
    for &i in &b {
        let mut dpn = dp.clone();//对于每个块，创建新的 DP 集合
        for &t in dp.iter() {
            dpn.insert(t + i);//将原集合中的每个值加上当前块大小后插入新集合
        }
        dp = dpn;//更新 DP 集合
    }
    let mut res: Vec<i32> = dp.into_iter().collect();//将集合转换为向量以便排序
    res.sort();
    for i in res { println!("{}", i + 1 + offset); }//每个结果加上偏移量和1（转换回1-indexed）
}
/**
*s.get(&j).unwrap_or(&0)
从 HashMap s 中获取键为 j 的值，如果键不存在则返回 0，然后解引用得到实际的整数值
1. s.get(&j)
功能: 从 HashMap s 中查找键为 j 的条目
返回值: Option<&i32> 类型
如果键存在，返回 Some(&value)，其中 &value 是指向存储值的引用
如果键不存在，返回 None
2. .unwrap_or(&0)
功能: 如果 get 返回 None（键不存在），则使用默认值 &0
返回值: &i32 类型（一个引用）
如果键存在：返回 get 得到的引用
如果键不存在：返回指向常量 0 的引用 &0
3. * (解引用操作符)
功能: 获取引用指向的实际值
作用: 将 &i32（引用）转换为 i32（实际值）
结果: 得到一个 i32 类型的数值

1. s.entry(diff)
功能: 获取 HashMap s 中键为 diff 的条目（Entry）
返回值: Entry 枚举类型，表示键可能存在或不存在
作用: 为后续的插入或获取操作做准备
2. .or_insert(0)
功能: 如果键 diff 不存在，则插入值 0；如果存在，则获取现有值的可变引用
返回值: &mut i32 类型（指向值的可变引用）
如果键存在：返回指向现有值的可变引用
如果键不存在：插入 0，然后返回指向这个新插入值的可变引用
3. * (解引用操作符)
功能: 解引用，获取引用指向的实际值
作用: 将 &mut i32（可变引用）转换为 i32 值
结果: 得到一个 i32 类型的数值
*/
use std::collections::HashMap;
use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<i32> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    let n = parts[0] as usize;
    let k = parts[1];
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let mut a = vec![0; n + 1];
    let val: Vec<i32> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    let mut mx = 0;
    for i in 1..=n {
        a[i] = val[i - 1];
        mx = mx.max(a[i]);//最大值和 a[i] 中的较大者
    }
    let mut s: HashMap<i32, i32> = HashMap::new();//键是差值，值是该差值出现的次数
    for i in 1..=n {
        for j in i + 1..=n {
            let dif = (a[i] - a[j]).abs();//计算所有两两元素之间的绝对值差，并统计每种差值的出现次数
            *s.entry(dif).or_insert(0) += 1;
        }
    }
    if k >= n as i32 - 1 { println!("1"); return; }
    let mut ans = 0;
    let mut vis: HashMap<i32, i32> = HashMap::new();//余数是否已被使用
    for i in (n as i32 - k)..=(mx + 1) {
        if i <= 0 { continue; }//避免除以0
        let mut cnt = 0;
        let mut sgn = false;
        let mut j = i;
        while j <= mx + 1 {
            cnt += *s.get(&j).unwrap_or(&0);
            //组合数 C(k+1, 2)
            if cnt > k * (k + 1) / 2 { sgn = true; break; }//检查是否存在超过 k*(k+1)/2 个差值是 i 的倍数
            j += i;
        }
        if sgn { continue; }//如果第一个检查失败，继续下一个 i
        cnt = 0; sgn = false; vis.clear();
        for j in 1..=n {
            let res = ((a[j] % i) + i) % i;//计算每个元素对 i 的余数
            //如果余数第一次出现，将其标记为已访问；否则增加冲突计数
            if !vis.contains_key(&res) { vis.insert(res, i); } else { cnt += 1; }
            if cnt > k { sgn = true; break; }//冲突数超过 k
        }
        if sgn { continue; }
        ans = i;//设置答案并跳出循环 满足条件的最小 i 值
        break;
    }
    println!("{}", ans);
}
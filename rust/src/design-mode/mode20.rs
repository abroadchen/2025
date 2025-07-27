/**
@author: June
@since: 2025/7/28
@desc: 策略模式是一种实现关注点分离的技术，其基本思想是，
给定一个解决特定问题的算法，只在抽象层面定义算法的骨架，将具体的算法分成不同的部分
*/

//report/src/formatter.rs
use std::collections::HashMap;
pub type Data = HashMap<String, u32>;
pub trait Formatter {
    fn format(&self, data: &Data, buf: &mut String);
}
//report/src/report.rs
use crate::formatter::Formatter;
use std::collections::HashMap;

pub struct Report;

impl Report {
    pub fn generate<T: Formatter>(g: T, s: &mut String) {
        let mut data = HashMap::new();
        data.insert("one".to_string(), 1);
        data.insert("two".to_string(), 2);
        g.format(&data, s);
    }
}
//json包
use report::formatter::{Data, Formatter};

pub struct Json;
impl Formatter for Json {
    fn format(&self, data: &Data, buf: &mut String) {
        buf.push('[');
        for (k, v) in data.into_iter() {
            let entry = format!(r#"{{"{}":"{}"}}"#, k, v);
            buf.push_str(&entry);
            buf.push(',');
        }
        buf.pop(); // remove extra , at the end
        buf.push(']');
    }
}
//text包
use report::formatter::{Data, Formatter};

pub struct Text;
impl Formatter for Text {
    fn format(&self, data: &Data, buf: &mut String) {
        for (k, v) in data {
            let entry = format!("{} {}\n", k, v);
            buf.push_str(&entry);
        }
    }
}
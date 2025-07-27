/**
@author: June
@since: 2025/7/28
@desc:
*/
#[non_exhaustive]
pub struct StudentInfo {
    pub name: String,
    pub age: u32,
    pub number: u32,
}

fn main() {
    let StudentInfo {name, age, number} = bob;
}


pub struct StudentInfo {
    pub name: String,
    pub age: u32,
    pub number: u32,
    _b: (), //添加一个私有成员
}
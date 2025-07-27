/**
@author: June
@since: 2025/7/28
@desc: 把集合当成智能指针

通过为集合实现Deref trait，提供其拥有和借用的数据视图
通过实现Deref完成&Vec到&[T]的隐式解引用，从而提供借用T的集合（即&[T]）
Vec提供拥有T的集合，&[T]提供借用T的集合
*/

impl<T> Deref for Vec<T> {
    type Target = [T];
    fn deref(&self) -> &[T] {
        unsafe {
            std::slice::from_raw_parts(self.ptr.as_ptr(), self.len)
        }
    }
}
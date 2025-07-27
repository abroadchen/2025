/**
@author: June
@since: 2025/7/26
@desc:
*/

struct Stack<T> {
  data: Vec<T>,
  top: usize,
  capacity: usize,
}

impl<T> Stack<T> {
  fn new(size: usize) -> Self {
    Stack {
      data: Vec::new(),
      top: 0,
      capacity: size,
    }
  }

  fn push(&mut self, data: T) -> Result<(), String> {
    if self.top >= self.data.capacity() {
      return Err(String::from("too many items"));
    }
    self.data.push(data);
    self.top += 1;
    Ok(())
  }

  fn pop(&mut self) -> Option<T> {
    if self.top == 0 {
      return None;
    }
    self.top -= 1;
    self.data.pop()
  }

  fn top(&self) -> usize {
    self.top
  }
}


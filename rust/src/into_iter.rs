use std::{mem, ptr};
use std::alloc::{dealloc, Layout};
use std::ptr::NonNull;

/**
@author: June
@since: 2025/7/25
@desc: 
*/
struct IntoIter<T> {
  buf: NonNull<T>,
  cap: usize,
  start: *const T,
  end: *const T,
}

impl<T> Iterator for IntoIter<T> {
  type Item = T;
  fn next(&mut self) -> Option<T> {
    if self.start == self.end {
      None
    } else {
      unsafe {
        let result = ptr::read(self.start);
        self.start = self.start.offset(1);
        Some(result)
      }
    }
  }
  fn size_hint(&self) -> (usize, Option<usize>) {
    let remaining = self.end as usize - self.start as usize / mem::size_of::<T>();
    (remaining, Some(remaining))
  }
}

impl<T> DoubleEndedIterator for IntoIter<T> {
  fn next_back(&mut self) -> Option<T> {
    if self.start == self.end {
      None
    } else {
      unsafe {
        self.end = self.end.offset(-1);
        Some(ptr::read(self.end))
      }
    }
  }
}

impl<T> Drop for IntoIter<T> {
  fn drop(&mut self) {
    if self.cap != 0 {
      for _ in &mut *self {}
      let align = mem::align_of::<T>();
      let elem_size=mem::size_of::<T>();
      let num_bytes = elem_size * self.cap;

      unsafe {
        let layout: Layout = Layout::from_size_align_unchecked(num_bytes, align);
        dealloc(self.buf.as_ptr() as *mut _, layout)
      }
    }
  }
}
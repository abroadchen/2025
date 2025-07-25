use std::{mem, ptr};

/**
@author: June
@since: 2025/7/25
@desc:
*/

pub struct RawValIter<T> {
    start: *const T,
    end: *const T,
}

impl<T> Iterator for RawValIter<T> {
    type Item = T;
    fn next(&mut self) -> Option<T> {
        if self.start == self.end {
            None
        } else {
            unsafe {
                let result = ptr::read(self.start);
                self.start = if mem::size_of::<T>() == 0 {
                    (self.start as usize + 1) as *const _
                } else {
                    self.start.offset(1)
                };
                Some(result)
            }
        }
    }

    fn size_hint(&self) -> (usize, Option<usize>) {
        let elem_size = mem::size_of::<T>();
        let len = (self.end as usize - self.start as usize) / if elem_size == 0 { 1 } else { elem_size };
        (len, Some(len))
    }
}

impl<T> DoubleEndedIterator for RawValIter<T> {
    fn next_back(&mut self) -> Option<T> {
        if self.start == self.end {
            None
        } else {
            unsafe {
                self.end = if mem::size_of::<T>() == 0 {
                    (self.end as usize - 1) as *const _
                } else {
                    self.end.offset(-1)
                };
                Some(ptr::read(self.end))
            }
        }
    }
}



impl<T> RawValIter<T> {
    pub(crate) unsafe fn new(slice: &[T]) -> Self {
        unsafe {
            RawValIter {
                start: slice.as_ptr(),
                end: if mem::size_of::<T>() == 0 {
                    ((slice.as_ptr() as usize) + slice.len()) as *const _
                } else if slice.len() == 0 {
                    slice.as_ptr()
                } else {
                    slice.as_ptr().offset(slice.len() as isize)
                }
            }
        }
    }
}


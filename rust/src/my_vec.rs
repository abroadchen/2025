use std::alloc::{alloc, dealloc, handle_alloc_error, realloc, Layout};
use std::{mem, ptr, slice};
use std::ops::{Deref, DerefMut};
use std::ptr::NonNull;
/**
@author: June
@since: 2025/7/25
@desc:
*/



pub struct MyVec<T> {
    // ptr: *mut T,
    ptr: NonNull<T>,
    cap: usize,
    pub len: usize,
}

impl<T> MyVec<T> {
    fn new () -> Self {
        assert!(mem::size_of::<T>() > 0, "capacity overflow");
        MyVec {
            ptr: NonNull::dangling(),
            len: 0,
            cap: 0,
        }
    }
    fn grow(&mut self) {
        unsafe {
            let align = mem::align_of::<T>();
            let elem_size = mem::size_of::<T>();
            let layout: Layout;

            let (new_cap, ptr) = if self.cap == 0 {
                layout = Layout::from_size_align_unchecked(elem_size,align);
                let ptr = alloc(layout);
                (1, ptr)
            } else {
                let new_cap = self.cap * 2;
                let old_num_bytes = self.cap * elem_size;
                assert!(old_num_bytes <= (isize::MAX as usize) / 2, "");
                let new_num_bytes = old_num_bytes * 2;
                layout = Layout::from_size_align_unchecked(new_num_bytes,align);
                let ptr= realloc(self.ptr.as_ptr() as *mut _, layout,new_num_bytes);
                (new_cap, ptr)
            };
            if ptr.is_null() { handle_alloc_error(layout); }
            if let Some(ptr) = NonNull::new(ptr as *mut _) { self.ptr = ptr;}
            else { panic!(""); }
            self.cap = new_cap;
        }
    }

    fn push(&mut self, elem: T) {
        if self.len == self.cap { self.grow();}
        unsafe {
            ptr::write(self.ptr.as_ptr().offset(self.len as isize), elem)
        }
        self.len += 1
    }

    fn pop(&mut self) -> Option<T> {
        if self.len == 0 { None }
        else {
            self.len -= 1;
            unsafe {
                Some(ptr::read(self.ptr.as_ptr().offset(self.len as isize)))
            }
        }
    }

    fn insert(&mut self, index: usize, elem: T) {
        assert!(index <= self.len, "overflow");
        if self.cap == self.len { self.grow();}
        unsafe {
            if index < self.len {
                ptr::copy(self.ptr.as_ptr().offset(index as isize),
                          self.ptr.as_ptr().offset(index as isize + 1),
                          self.len - index);
            }
            ptr::write(self.ptr.as_ptr().offset(index as isize), elem);
            self.len += 1
        }
    }

    fn remove(&mut self, index: usize) -> T {
        assert!(index <= self.len, "overflow");
        unsafe {
            self.len -= 1;
            let result = ptr::read(self.ptr.as_ptr().offset(index as isize));
            ptr::copy(self.ptr.as_ptr().offset(index as isize + 1),
                      self.ptr.as_ptr().offset(index as isize),
                      self.len - index);
            result
        }
    }

    fn into_iter(self) -> IntoIter<T> {
        let ptr = self.ptr;
        let cap = self.cap;
        let len = self.len;

        mem::forget(self);
        unsafe {
            IntoIter {
                buf: ptr,
                cap: cap,
                start: ptr.as_ptr(),
                end: if cap == 0 {
                    ptr.as_ptr()
                } else {
                    ptr.as_ptr().offset(len as isize)
                }
            }
        }
    }

}

impl<T> Drop for MyVec<T> {
    fn drop(&mut self) {
        if self.cap != 0 {
            while let Some(_) = self.pop() {}
            let align = mem::align_of::<T>();
            let elem_size=mem::size_of::<T>();
            let num_bytes = elem_size * self.cap;
            unsafe {
                let layout: Layout = Layout::from_size_align_unchecked(num_bytes, align);
                dealloc(self.ptr.as_ptr() as *mut _, layout)
            }
        }
    }
}

impl<T> Deref for MyVec<T> {
    type Target = [T];
    fn deref(&self) -> &[T] {
        unsafe {
            slice::from_raw_parts(self.ptr.as_ptr(), self.len)
        }
    }
}

impl<T> DerefMut for MyVec<T> {
    fn deref_mut(&mut self) -> &mut [T] {
        unsafe {
            slice::from_raw_parts_mut(self.ptr.as_ptr(), self.len)
        }
    }
}

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
use std::alloc::{alloc, dealloc, handle_alloc_error, realloc, Layout};
use std::{mem, ptr, slice};
use std::ops::{Deref, DerefMut};
use std::ptr::NonNull;


/**
@author: June
@since: 2025/7/25
@desc:
*/

struct RawVec<T> {
    ptr: NonNull<T>,
    cap: usize,
}

impl<T> RawVec<T> {
    fn new() -> Self {
        // assert!(mem::size_of::<T>() <= !0, "capacity overflow");
        let cap = if mem::size_of::<T>() == 0 { !0 } else { 0 };
        RawVec {
            ptr: NonNull::dangling(),
            cap,
        }
    }

    fn grow(&mut self) {
        unsafe {
            let align = mem::align_of::<T>();
            let elem_size = mem::size_of::<T>();
            assert_ne!(elem_size, 0, "capacity mismatch");
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
}

impl<T> Drop for RawVec<T> {
    fn drop(&mut self) {
        let elem_size = mem::size_of::<T>();
        if self.cap != 0 && elem_size != 0 {
            let align = mem::align_of::<T>();
            let elem_size = mem::size_of::<T>();
            let num_bytes = self.cap * elem_size;
            unsafe {
                let layout = Layout::from_size_align_unchecked(num_bytes,align);
                dealloc(self.ptr.as_ptr() as *mut _, layout);
            }
        }
    }
}

struct MyVec<T> {
    buf: RawVec<T>,
    len: usize,
}

impl<T> MyVec<T> {
    fn ptr(&self) -> *mut T {
        self.buf.ptr.as_ptr()
    }

    fn cap(&self) -> usize {
        self.buf.cap
    }

    fn new() -> Self {
        MyVec {
            buf: RawVec::new(),
            len: 0,
        }
    }

    fn push(&mut self, value: T) {
        if self.len == self.cap() {
            self.buf.grow()
        }
        unsafe {
            ptr::write(self.ptr().offset(self.len as isize), value);
        }
        self.len += 1;
    }

    fn pop(&mut self) -> Option<T> {
        if self.len == 0 {
            None
        } else {
            self.len -= 1;
            unsafe {
                Some(ptr::read(self.ptr().offset(self.len as isize)))
            }
        }
    }

    fn insert(&mut self, index: usize, element: T) {
        assert!(index < self.len, "insert out of bounds");
        if self.len == self.cap() {
            self.buf.grow()
        }
        unsafe {
            if index < self.cap() {
                ptr::copy(self.ptr().offset(index as isize), self.ptr().offset(index as isize + 1), self.len - index);
            }
            ptr::write(self.ptr().offset(index as isize), element);
            self.len += 1;
        }
    }

    fn remove(&mut self, index: usize) -> Option<T> {
        assert!(index < self.len, "remove out of bounds");
        unsafe {
            self.len -= 1;
            let result = ptr::read(self.ptr().offset(index as isize));
            ptr::copy(self.ptr().offset(index as isize + 1), self.ptr().offset(index as isize), self.len - index);
            Some(result)
        }
    }

    fn into_iter(self) -> IntoIter<T> {
        unsafe {
            let buf = ptr::read(&self.buf);
            let len = self.len;
            mem::forget(self);
            IntoIter {

                start: buf.ptr.as_ptr(),
                end: buf.ptr.as_ptr().offset(len as isize),
                _buf: buf,
            }
        }
    }
}

impl<T> Drop for MyVec<T> {
    fn drop(&mut self) {
        while let Some(_) = self.pop() {}
    }
}

impl<T> Deref for MyVec<T> {
    type Target = [T];
    fn deref(&self) -> &[T] {
        unsafe {
            slice::from_raw_parts(self.buf.ptr.as_ptr(), self.len)
        }
    }
}

impl<T> DerefMut for MyVec<T> {
    fn deref_mut(&mut self) -> &mut [T] {
        unsafe {
            slice::from_raw_parts_mut(self.buf.ptr.as_ptr(), self.len)
        }
    }
}

struct IntoIter<T> {
    _buf: RawVec<T>,
    start: *const T,
    end: *const T,
}

impl<T> Drop for IntoIter<T> {
    fn drop(&mut self) {
        for _ in &mut *self {}
    }
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
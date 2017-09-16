# A dynarray implementation

This provides an implementation of `dynarray` which is a container is similar to a `std::array`. Some of its characteristics:

  - Its size is provided at object construction time and cannot be resized after construction.
  - Its storage is on the heap. The *Arrays TS* was hoping for compilers to be able to put it on the stack as an optimization.
  - The elements must be stored continguously.

Some incompatibilties compared to the *Arrays TS* (which has been withdrawn at this time, as far as I know):

  - [ ] Does not use an `Allocator`
  - [ ] Missing `dynarray(size_type, const <T>& value)` constructor
  - [ ] Adds  `template<InputIt> dynarray(InputIt first, InputIt last)` constructor
  - [ ] Does not specialize `std::uses_allactor`
  - [ ] Possibly incorrect implementation of `max_size()`
  - [ ] Uses `morrisonlevi` namespace instead of `std::`

Some other todo items:

  - [ ] Pick a license
  - [ ] Show examples in this README
  - [ ] Pick a test framework
  - [ ] Test the implementation against `std::array` which shares much of the same semantics
  - [ ] See how well compilers optimize the code compared to a two-pointers implementation


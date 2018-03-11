# C Foundation Library (CFL)
[![Build Status](https://travis-ci.org/skhoroshavin/cfl.svg?branch=master)](https://travis-ci.org/skhoroshavin/cfl)
[![Build Status](https://ci.appveyor.com/api/projects/status/github/skhoroshavin/cfl?branch=master&svg=true)](https://ci.appveyor.com/project/skhoroshavin/cfl)

## Index
- *core*: common useful functionality
  - *utils*: common utility used throughout project
  - *memory*: memory allocator interface with default implementation
  - *list*: generic double-linked list with sentinel node
  - *string_list*: list of strings
  - *logger*: logger interface with default and buffer implementations
- *test*: testing framework implementation
  - *context*: test context object
  - *asserts*: different assert macros to be used in tests
  - *test*: main testing implementation

## Todo
- Add explicit fixtures framework
- Implement combinatorial testing


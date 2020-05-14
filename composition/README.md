# Function Composition

category theory for programmers book says C++ does not have `.` as haskell does

however there are still techniques that emulate the composition operator in c++

## Compose Using Template

hands on FP with C++: L1408

see: compose.cpp for an implementation of the haskell-like
`.` operator (operator*), source: modern c++ programming cookbook

## Partial Application 

### Using std::bind

hands on FP with C++: L1639

### Using lambda (return lambda function)

see partial_application.cpp.

it helps to implement robust zip-tuple function template

# Lambda function

## Const-expression in capture list

see: cpp reference

can generate a variable using a const-expression in the 
capture list;

saw this in c++ stl cookbook:

```c++
[idx = 1](const auto &elem) {
    ++idx;
    // ...
}
```

## Lazy-evaluation: return lambda that captures the workload

saw this in c++ stl cookbook;

instead of processing the workload, capture it in a lamdba
and return this lambda for further composition

another good lazy-eval pattern is c++20's range library

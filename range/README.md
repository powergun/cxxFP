# Range

inspired by: hands on functional programming with C++ L/4189

## Range-v3, C++20

source: <https://github.com/ericniebler/range-v3>

see rangev3.cpp and the official examples

### Range piping & "Consume" a Range

see rangev3_piping.cpp; see the reasoning on when and where a range is "exercised"

### Range view algorithms vs STL (mutable) algorithms

see: rangev3_perf.cpp

the regionally mutable STL algorithm is 10x faster; but the range view offers FP purity

## IRange - Python's range() in C++

source: <https://theboostcpplibraries.com/boost.range-helper-classes-and-functions>

see irange.cpp, for how it enables oneliner in C++

## What is Boost Range

source: <https://theboostcpplibraries.com/boost.range-algorithms>

> You can think of a range as two iterators that refer to the beginning and end 
> of a group of elements that you can iterate over. Because all containers support 
> iterators, every container can be thought of as a range

use container as range, see count_elems.cpp

> Since all algorithms from Boost.Range expect a range as a first parameter, a 
> container like std::vector can be passed directly.
> This protects you from mistakes

boost/range/algorithm.hpp

> This header file provides access to all of the algorithms for which counterparts 
> exist in the standard library header file algorithm.

## Boost Adaptor

source: <https://theboostcpplibraries.com/boost.range-adaptors>

lazy evaluation, great for functional composition

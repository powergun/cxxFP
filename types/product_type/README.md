# Product Type

std::tuple and std::pair are useful generic types for creating quick-and-dirty
product types;

one of the most useful features of pairs and tuples is that, when you create
product types with them, you get **lexicographical comparison** operators for
free.

## Tuple

C++ template: complete guide dedicates chapter 24 on TypeList - a type-level data 
structure - and its application in algorithms 

one important aspect of TypeList is that it is heterogeneous

see: cxxTemplate/typing for the implementation details - I decide to leave them
there.

this is the basis of STL tuple

c++ template: complete guide L20721

> Boost.Fusion library provides heterogeneous list, deque, set and map,
> more important, it provides a framework for writing algorithms for 
> heterogeneous collections, using the same kinds of abstractions
> and terminology as the C++ standard library itself (e.g. iterators,
> sequences and containers)


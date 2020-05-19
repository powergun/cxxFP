# Stream

how to model Haskell's lazy stream in C++

## Build infinite stream on top of iterator

using boost's iterator facade (see guide: <https://www.boost.org/doc/libs/1_69_0/libs/iterator/doc/iterator_facade.html>),

starting with the simplest case, given a default-constructible, comparable, assignable type T, wrap a value of T in 
a forward iterator; 

it returns a const value each time when calling dereference() method; it's increment() method does nothing; 

see how this stream (iterator) interact with STL algorithms such as copy()

taking one step further, wrap a f() that returns a value of T and each time when calling dereference() method, invoke
f; this is similar to std::generate()

## Split one (infinite) stream into N substreams

inspired by a chat;

it requires a recursion to "iterate over" the tuple elements;

see: <https://stackoverflow.com/questions/1198260/how-can-you-iterate-over-the-elements-of-an-stdtuple>

iterator maybe an easier solution
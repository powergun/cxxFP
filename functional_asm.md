# Proposal, Functional Programming and Assembly Code

## Sketch

Imagine a problem of processing a collection of values using some arch-specific instructions and collect the result in
another collection (of the same or different type).

Assume the collection is a perceptually immutable (or only internally mutable).

```text
using T = ArchSpecific<...>;
using R = ArchSpecific<...>;
std::vector<T> xs(1000, init);
//... populate xs
std::vector<R> ys(xs.size(), zero);
std::transform(xs.cbegin(), xs.cend(), ys.begin(), f);

// f is where raw assembly is written:
inline R f(const T &x) {
    R out;
    #ifdef SOME_ARCH
    asm {
        mov x.attr, rax;
        ...
        call ...
        ...
        mov rax, out;
    }
    #endif
    #ifdef SOME_OTHER_ARCH
    asm {
        // ...
    }
    #endif
    return out;
}
```

The goal is that,

STL algorithm will safely set up the harness for me so that `f` has less chance of causing memory violation and since 
it is inlined the overhead is minimized.

## Test and Proof

does it work with raw assembly code at all? how does the resulting asm code look like?

test this with function objects as well as inlined free-functions and see whether inlining happens in both cases, with
and without aggressive optimization flags;

test this in gcc and clang and see if the behaviour is consistent;

# Sum Type

## std::variant

std::variant and std::visit() can mimic Haskell's sum type;
it can also simulate sum-type-based pattern matching.

see variant.cpp

c++ stl cookbook P/362

std::variant is different from std::any in the regard that we must declare what 
it shall be able to store in the form of a template type list

an instance of std::variant<A, B, C> must hold one instance of type, there is NO
possibility to hold NONE of them - which means that std::variant has no notion
of **optionality**.

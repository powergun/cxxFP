# How to build cxx actor framework

clone from: <https://github.com/actor-framework/actor-framework>

it has documented most of its cmake variables on this page:
<https://github.com/actor-framework/actor-framework/wiki/CMake-Options>

BUT it **no longer offers the option building static libraries**, so don't waste time trying.

I can add this project as a submodule to my own project and hack into its build option to enable the static library targets.

```shell
cmake -DCMAKE_C_COMPILER=gcc-10 -DCMAKE_CXX_COMPILER=g++-10 -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$(pwd)/caf ..
```

set the compiler version to match cxxFP's project settings

`make -j12 install` then copy the subdirectory `caf` to the vendor directory

# cpathtools
[![license](https://img.shields.io/badge/License-MIT-blue.svg)](http://www.apache.org/licenses/)
![Tests](https://github.com/sammnnz/cpathtools/actions/workflows/tests.yml/badge.svg)
[![codecov](https://codecov.io/github/sammnnz/cpathtools/branch/main/graph/badge.svg?token=nQZYf4CqRh)](https://codecov.io/github/sammnnz/cpathtools)

Small project for working with paths.

## Compatibility

It is supported `Windows` with `MinGW64` and `Linux` with `GCC`.

## Build and Tests

You can build shared library `libcpathtools.dll`/`libcpathtools.so` using `make`
~~~~shell
make build
~~~~

from root of this repo, or simply
~~~~shell
make
~~~~

**Note**: Latest equal the following
~~~~shell
make build
make test
make clean
~~~~

## Inputs for `make`

**coverage**: set `1` to enable `gcov` reports. Default: `0`.

**debug**: set `1` to enable debug mode (flags `-g3 -O0`). Default: `0`.

**install_directory**: set path to build shared library. Default: root of this repo.

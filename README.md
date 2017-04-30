# MandelbrotSetSRiR

## Installation guide

* `cmake .`
* `make`
* `./mandelbrot_set.exe`

## Dependencies

* mpich
* cmake

## Documents

* https://docs.google.com/document/d/1lr3Fx8s1J7NCNvii_6Qx7-RgSHLWsGauP182nUX64WY/edit#

## Wersja nierównoległa

* pliki mandelbrot_test.cpp i plot.plt napisane od zera
* kompilacja - normalnie przez g++:
* g++ mandel_test.cpp Config.cpp -fext-numeric-literals
* odpalanie: np. `/a.out -2 1 -1 1 0.003 && gnuplot plot.plt`

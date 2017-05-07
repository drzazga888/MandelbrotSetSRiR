# MandelbrotSetSRiR

## Installation guide

* `cmake .`
* `make`
* `./mandelbrot.run -2 1 -1 1 0.003 && gnuplot plot.plt`

## Dependencies

* mpich
* cmake

## Documents

* https://docs.google.com/document/d/1lr3Fx8s1J7NCNvii_6Qx7-RgSHLWsGauP182nUX64WY/edit#

## Wersja nierównoległa

* pliki mandelbrot_test.cpp i plot.plt napisane od zera
* kompilacja - normalnie przez g++:
* g++ mandel_test.cpp Config.cpp Server.cpp Client.cpp -fext-numeric-literals
* odpalanie: np. `/a.out -2 1 -1 1 0.003 && gnuplot plot.plt`

## Uwagi

* (dla systemów Mac OS X) - należy sprawdzić, czy w pliku /etc/hosts znajduje się wpisa `127.0.0.1  COMPUTER_NAME`, gdzie `COMPUTER_NAME` to nazwa hosta, która wyświetlana jest w terminala przy znaku zachęty
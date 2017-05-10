# MandelbrotSetSRiR

## Wersja równoległa - katalog parallel/

### Normalne odpalenie

* `make`
* `mpiexec -n 4 ./mandelbrot.run -2 1 -1 1 0.01`
* `gnuplot plot.plt`
* wynik: plik results.png

### Wersja z profilowaniem (logi MPE) -> używanie do profilowania

* `make mpelogs`
* `mpiexec -n 4 ./mandelbrot.run -2 1 -1 1 0.01` (to samo jak w normalnym odpaleniu...)
* `jumpshot mpe-logs.clog2`
* jumpshot automatycznie zaproponuje konwersję clog2 do formatu slog2

## Wersja nierównoległa - katalog single-process/

* `make`
* `./mandelbrot.run -2 1 -1 1 0.01`
* wynik: plik results.png

## Uwagi

* make posiada też opcję `clean`
* (dla systemów Mac OS X) - należy sprawdzić, czy w pliku /etc/hosts znajduje się wpisa `127.0.0.1  COMPUTER_NAME`, gdzie `COMPUTER_NAME` to nazwa hosta, która wyświetlana jest w terminala przy znaku zachęty

## Linki

* https://docs.google.com/document/d/1lr3Fx8s1J7NCNvii_6Qx7-RgSHLWsGauP182nUX64WY/edit#
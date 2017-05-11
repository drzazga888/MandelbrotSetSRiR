# MandelbrotSetSRiR

## Wersja równoległa - katalog /parallel

Normalne uruchomienie

* `make`
* `mpiexec -n 4 ./mandelbrot.run -2 1 -1 1 0.01`
* `gnuplot plot.plt`
* wynik: plik results.png

Wersja z profilowaniem (logi MPE)

* `make mpelogs`
* `mpiexec -n 4 ./mandelbrot.run -2 1 -1 1 0.01`
* `jumpshot mpe-logs.clog2` (jumpshot automatycznie zaproponuje konwersję clog2 do formatu slog2)

Poprawki dla taurusa

* uruchamiamy programy przez `/opt/nfs/mpich-3.2/bin/mpiexec`
* kompilacja normalna: `make CC=/opt/nfs/mpich-3.2/bin/mpicxx`
* kompilacja z profilowaniem: `make mpelogs CC=/opt/nfs/mpich-3.2/bin/mpicxx LIB_PATHS=-L/opt/nfs/mpe2-2.4.9b/lib INCL_PATHS=-I/opt/nfs/mpe2-2.4.9b/include`

## Wersja nierównoległa - katalog /single-process

* `make`
* `./mandelbrot.run -2 1 -1 1 0.01`
* wynik: plik results.png

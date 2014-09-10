rt-plotter
==========

2D realtime plot of the shared memory content.
Plotting is done using point-by-point approach.

Dependencies:
- MathGL (http://sourceforge.net/projects/mathgl/)
- FLTK (http://www.fltk.org/)
- libconfig (http://www.hyperrealm.com/libconfig/)
- pthread (http://www.gnu.org/software/hurd/libpthread.html)

Check on the repository: rt-plotter-test

Concept:
```
¦-----------------¦            ¦------------¦
¦Your application ¦            ¦ rt-plotter ¦
¦   (writing)     ¦            ¦ (reading)  |
¦-----------------¦------------¦------------¦
¦              SHARED MEMORY                ¦
¦-------------------------------------------¦
```
Contact:
manurunga@yandex.com

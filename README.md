rt-plotter
==========

2D realtime plot of the shared memory content.
Ploting is done udsing point-by-point approach.

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
¦   (wrting)      ¦            ¦ (reading)  |
¦-----------------¦------------¦------------¦
¦              SHARED MEMORY                ¦
¦-------------------------------------------¦
```
Contact:
manurunga@yandex.com
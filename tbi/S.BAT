ECHO off
set c51inc=d:\c51\inc;
set c51lib=d:\c51\lib
\c51\bin\c51 %1.c large df(POD8751) debug
\c51\bin\l51 %1.obj,startup.obj to %1.hex ramsize (256) xdata(8000H)
oh %1.hex to %1.bin

ECHO off
set c51inc=\c51\inc;
set c51lib=\c51\lib
\c51\bin\c51 %1.c small ot(6)
\c51\bin\l51 %1.obj,startup.obj to %1.hex ramsize (256) xdata(8000H)
oh %1.hex to %1.bin

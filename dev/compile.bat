@echo off

echo PRG0
..\utils\mapcnvchunk.exe ..\map\mapa.MAP prg0\map.h 320 4 0 ..\map\pallist.txt prg0\attr_precalcs.h
..\utils\mkts.exe in=..\gfx\ts.png pals=..\gfx\palts.png out=work\main_ts_patterns.bin mode=mapped tsmap=prg0\main_ts.h offset=0,0 size=16,4 metasize=2,2 label=main_ts deinterlaced silent

echo PRG1
..\utils\lzsscomp.exe work\main_ts_patterns.bin main_ts_patterns_c.h
cd ..\gfx
..\utils\mkts.exe mode=scripted in=cut_sprites.spt out=..\dev\work\main_ss_patterns.bin silent

cd ..\dev
..\utils\lzsscomp.exe work\main_ss_patterns.bin main_ss_patterns_c.h

move main_ts_patterns_c.h prg1 > nul
move main_ss_patterns_c.h prg1 > nul

echo COMPILING

cc65 -Oi game.c --add-source
ca65 crt0-unrom.s
ca65 game.s
ca65 prg1\ogt.s -o music.o

ld65 -C nes-unrom.cfg -o goddessr.nes crt0-unrom.o game.o music.o runtime.lib  -Ln labels.txt

del game.s > nul
del game.o > nul
del music.o > nul
del crt0-unrom.o > nul


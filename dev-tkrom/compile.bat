@echo off
if [%1]==[justcompile] goto :compile

..\utils\mapcnvchunk.exe ..\map\mapa_tkrom.MAP prg0001\map.h 320 4 0 ..\map\pallist_tkrom.txt prg0001\attr_precalcs.h

cd ..\gfx
..\utils\mkts.exe mode=scripted in=cut_tkrom.spt out=..\dev-tkrom\tileset.chr silent

:compile
cd ..\dev-tkrom
cc65 -Oi game.c --add-source
ca65 crt0-tkrom.s
ca65 game.s
ca65 prg02\music_full.s -o music.o

ld65 -C nes-tkrom.cfg -o goddessr.nes crt0-tkrom.o game.o music.o runtime.lib  -Ln labels.txt

rem del game.s > nul
del game.o > nul
del music.o > nul
del crt0-tkrom.o > nul

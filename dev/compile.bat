@echo off

echo PRG0
..\utils\mapcnvchunk.exe ..\map\mapa.MAP prg0\map.h 320 4 0 ..\map\pallist.txt prg0\attr_precalcs.h
..\utils\mkts.exe in=..\gfx\ts.png pals=..\gfx\palts.png out=work\main_ts_patterns.bin mode=mapped tsmap=prg0\main_ts.h offset=0,0 size=16,6 metasize=2,2 label=main_ts deinterlaced outputpallist silent

echo PRG1

..\utils\mkts.exe mode=pals pals=..\gfx\palts.png out=work\palbg0.h label=mypal_game_bg0 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palts2.png out=work\palbg1.h label=mypal_game_bg1 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palts3.png out=work\palbg2.h label=mypal_game_bg2 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palts4.png out=work\palbg3.h label=mypal_game_bg3 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palss.png out=work\palfg0.h label=mypal_game_fg0 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palssp.png out=work\palfg1.h label=mypal_game_fg1 silent
..\utils\mkts.exe mode=pals pals=..\gfx\paltsl.png out=work\paltsl.h label=mypal_light_bg silent
..\utils\mkts.exe mode=pals pals=..\gfx\palssl.png out=work\palssl.h label=mypal_light_fg silent
..\utils\mkts.exe mode=pals pals=..\gfx\palending.png out=work\palcuts.h label=mypal_ending silent
..\utils\mkts.exe mode=pals pals=..\gfx\palredbg.png out=work\palred.h label=mypal_reds silent
copy /b work\palbg0.h + work\palbg1.h + work\palbg2.h + work\palbg3.h + work\palfg0.h + work\palfg1.h + work\paltsl.h + work\palssl.h + work\palcuts.h + work\palred.h prg2\assets\palettes.h > nul


..\utils\lzsscomp.exe work\main_ts_patterns.bin main_ts_patterns_c.h
cd ..\gfx
..\utils\mkts.exe mode=scripted in=cut_sprites.spt out=..\dev\work\main_ss_patterns.bin silent
..\utils\mkts.exe mode=scripted in=cut_sprites_usa.spt out=..\dev\work\main_ss_patterns_usa.bin silent
..\utils\mkts.exe mode=chars in=chars.png pals=palts.png offset=0,14 max=32 out=..\dev\work\chars_ts_patterns.bin silent
..\utils\mkts.exe mode=chars in=mapchars.png pals=palts.png offset=0,14 max=32 out=..\dev\work\map_ts_patterns.bin silent
..\utils\mkts.exe mode=chars in=font.png pals=palts.png out=..\dev\work\font_ts_patterns.bin silent

rem cutscenes
cd fixed_screens
..\..\utils\mkts.exe mode=mapped pals=..\palts.png in=plate1_full.png tmapoffs=64 label=dum1 out=..\..\dev\work\cuts_p1_ts_patterns.bin tsmap=dum2.h offset=0,0 size=16,15 silent
..\..\utils\mkts.exe mode=mapped pals=..\palts.png in=plate2_full.png tmapoffs=64 label=dum2 out=..\..\dev\work\cuts_p2_ts_patterns.bin tsmap=dum2.h offset=0,0 size=16,15 silent
..\..\utils\mkts.exe mode=mapped pals=palending.png in=ending.png tmapoffs=64 label=dum3 out=..\..\dev\work\ending_ts_patterns.bin tsmap=dum3.h offset=0,0 size=16,15 silent
..\..\utils\mkts.exe mode=mapped pals=palending.png in=ending_usa.png tmapoffs=64 label=dum4 out=..\..\dev\work\ending_ts_patterns_usa.bin tsmap=dum4.h offset=0,0 size=16,15 silent
..\..\utils\mkts.exe mode=mapped pals=..\palts.png in=title.png tmapoffs=64 label=dum5 out=..\..\dev\work\title_ts_patterns.bin tsmap=dum5.h offset=0,0 size=16,15 silent
del dum?.h > nul
cd ..

rem these ones are for nesst

..\utils\mkts.exe mode=chars in=chars.png pals=palts.png out=..\dev\work\nesst.chr silent
..\utils\mkts.exe mode=chars in=mapchars.png pals=palts.png out=..\dev\work\mapnesst.chr silent

cd ..\dev
..\utils\lzsscomp.exe work\main_ss_patterns.bin main_ss_patterns_c.h
..\utils\lzsscomp.exe work\main_ss_patterns_usa.bin main_ss_patterns_usa_c.h
..\utils\lzsscomp.exe work\chars_ts_patterns.bin chars_ts_patterns_c.h
..\utils\lzsscomp.exe work\map_ts_patterns.bin map_ts_patterns_c.h
..\utils\lzsscomp.exe work\cuts_p1_ts_patterns.bin cuts_p1_ts_patterns_c.h
..\utils\lzsscomp.exe work\cuts_p2_ts_patterns.bin cuts_p2_ts_patterns_c.h
..\utils\bloat.exe in=work\cuts_p1_ts_patterns.bin out=work\nesst_cutsp1.chr maxsize=4096 leading=1024
..\utils\bloat.exe in=work\cuts_p2_ts_patterns.bin out=work\nesst_cutsp2.chr maxsize=4096 leading=1024
..\utils\lzsscomp.exe work\font_ts_patterns.bin font_ts_patterns_c.h
..\utils\lzsscomp.exe work\ending_ts_patterns.bin ending_ts_patterns_c.h
..\utils\lzsscomp.exe work\ending_ts_patterns_usa.bin ending_ts_patterns_usa_c.h
..\utils\bloat.exe in=work\ending_ts_patterns.bin out=work\nesst_ending.chr maxsize=4096 leading=1024
..\utils\bloat.exe in=work\ending_ts_patterns_usa.bin out=work\nesst_ending_usa.chr maxsize=4096 leading=1024
..\utils\lzsscomp.exe work\title_ts_patterns.bin title_ts_patterns_c.h
..\utils\bloat.exe in=work\title_ts_patterns.bin out=work\nesst_title.chr maxsize=4096 leading=1024

move main_ts_patterns_c.h prg1 > nul
move main_ss_patterns_c.h prg1 > nul
move main_ss_patterns_usa_c.h prg1 > nul
move chars_ts_patterns_c.h prg1 > nul
move map_ts_patterns_c.h prg1 > nul
move cuts_p1_ts_patterns_c.h prg1 > nul
move cuts_p2_ts_patterns_c.h prg1 > nul
move font_ts_patterns_c.h prg1 > nul
move ending_ts_patterns_c.h prg1 > nul
move ending_ts_patterns_usa_c.h prg1 > nul
move title_ts_patterns_c.h prg1 > nul

echo PRG2
cd ..\enems
..\utils\eneexp4.exe enems.ene ..\dev\prg2\assets\enems0.h 0 2

cd ..\text
..\utils\enctexts.exe goddess.tzt BASE str_cuts0 ..\dev\prg3\assets\texts.h index

cd ..\dev

echo COMPILING

cc65 -Oi game.c --add-source
ca65 crt0-unrom.s
ca65 game.s
ca65 prg1\ogt.s -o music.o

ld65 -C nes-unrom.cfg -o goddessr.nes crt0-unrom.o game.o music.o runtime.lib  -Ln labels.txt

rem del game.s > nul
del game.o > nul
del music.o > nul
del crt0-unrom.o > nul


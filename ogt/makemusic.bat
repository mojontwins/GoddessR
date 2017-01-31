@echo off
..\utils\nsf2data sounds.nsf -ca65 -pal
..\utils\text2data music.txt -ca65
..\utils\text2data interlude.txt -ca65
rem copy sounds.s ..\dev > nul
echo DONE!

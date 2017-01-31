.segment "ROM2"
.export _music_ROM2

; this file for FamiTone2 library generated by text2data tool
; and manually edited BEWARE!

_music_ROM2:

;this file for FamiTone2 library generated by text2data tool

interlude_music_data:
	.byte 1
	.word @instruments
	.word @samples-3
	.word @song0ch0,@song0ch1,@song0ch2,@song0ch3,@song0ch4,307,256

@instruments:
	.byte $30 ;instrument $00
	.word @env1,@env0,@env0
	.byte $00
	.byte $70 ;instrument $08
	.word @env2,@env0,@env4
	.byte $00
	.byte $70 ;instrument $09
	.word @env3,@env0,@env4
	.byte $00

@samples:
@env0:
	.byte $c0,$00,$00
@env1:
	.byte $cf,$00,$00
@env2:
	.byte $cc,$cb,$ca,$ca,$c9,$03,$c8,$03,$c7,$07,$c6,$08,$c5,$0a,$c4,$0c
	.byte $c3,$0c,$c2,$12,$c1,$19,$c0,$00,$16
@env3:
	.byte $c4,$02,$c3,$0c,$c2,$0b,$c1,$12,$c0,$00,$08
@env4:
	.byte $c0,$0f,$c1,$02,$c2,$02,$c1,$02,$c0,$c0,$c0,$00,$02


@song0ch0:
	.byte $fb,$08
@song0ch0loop:
@ref0:
	.byte $87,$84,$52,$95,$53,$54,$85,$52,$85,$53,$4b,$4e,$81
@ref1:
	.byte $83,$4f,$52,$95,$53,$54,$85,$52,$85,$4a,$85,$4e,$81
@ref2:
	.byte $87,$52,$95,$53,$54,$85,$52,$85,$53,$4b,$4e,$81
@ref3:
	.byte $83,$4f,$52,$95,$53,$54,$85,$52,$85,$54,$85,$58,$81
	.byte $fd
	.word @song0ch0loop

@song0ch1:
@song0ch1loop:
@ref4:
	.byte $82,$52,$95,$53,$54,$85,$52,$85,$53,$4b,$4e,$85,$4e,$81
@ref5:
	.byte $52,$95,$53,$54,$85,$52,$85,$4a,$85,$4e,$89
@ref6:
	.byte $52,$95,$53,$54,$85,$52,$85,$53,$4b,$4e,$85,$4e,$81
@ref7:
	.byte $52,$95,$53,$54,$85,$52,$85,$54,$85,$58,$89
	.byte $fd
	.word @song0ch1loop

@song0ch2:
@song0ch2loop:
@ref8:
	.byte $80,$30,$9d,$2c,$9d
@ref9:
	.byte $28,$9d,$2d,$2d,$45,$2d,$2d,$45,$2d,$44,$81
@ref10:
	.byte $30,$9d,$2c,$9d
	.byte $ff,$0b
	.word @ref9
	.byte $fd
	.word @song0ch2loop

@song0ch3:
@song0ch3loop:
@ref12:
	.byte $bf
@ref13:
	.byte $bf
@ref14:
	.byte $bf
@ref15:
	.byte $bf
	.byte $fd
	.word @song0ch3loop

@song0ch4:
@song0ch4loop:
@ref16:
	.byte $bf
@ref17:
	.byte $bf
@ref18:
	.byte $bf
@ref19:
	.byte $bf
	.byte $fd
	.word @song0ch4loop

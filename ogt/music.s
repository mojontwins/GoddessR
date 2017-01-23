;this file for FamiTone2 library generated by text2data tool

music_music_data:
	.byte 6
	.word @instruments
	.word @samples-3
	.word @song0ch0,@song0ch1,@song0ch2,@song0ch3,@song0ch4,307,256
	.word @song1ch0,@song1ch1,@song1ch2,@song1ch3,@song1ch4,307,256
	.word @song2ch0,@song2ch1,@song2ch2,@song2ch3,@song2ch4,307,256
	.word @song3ch0,@song3ch1,@song3ch2,@song3ch3,@song3ch4,307,256
	.word @song4ch0,@song4ch1,@song4ch2,@song4ch3,@song4ch4,307,256
	.word @song5ch0,@song5ch1,@song5ch2,@song5ch3,@song5ch4,307,256

@instruments:
	.byte $30 ;instrument $00
	.word @env2,@env0,@env0
	.byte $00
	.byte $30 ;instrument $01
	.word @env1,@env0,@env16
	.byte $00
	.byte $70 ;instrument $02
	.word @env5,@env0,@env0
	.byte $00
	.byte $30 ;instrument $03
	.word @env6,@env12,@env0
	.byte $00
	.byte $30 ;instrument $04
	.word @env7,@env14,@env0
	.byte $00
	.byte $30 ;instrument $05
	.word @env11,@env0,@env0
	.byte $00
	.byte $30 ;instrument $06
	.word @env8,@env0,@env0
	.byte $00
	.byte $30 ;instrument $07
	.word @env1,@env13,@env0
	.byte $00
	.byte $70 ;instrument $08
	.word @env3,@env0,@env17
	.byte $00
	.byte $70 ;instrument $09
	.word @env4,@env0,@env17
	.byte $00
	.byte $30 ;instrument $0a
	.word @env3,@env0,@env17
	.byte $00
	.byte $70 ;instrument $0c
	.word @env9,@env15,@env0
	.byte $00
	.byte $70 ;instrument $0d
	.word @env10,@env15,@env0
	.byte $00

@samples:
@env0:
	.byte $c0,$00,$00
@env1:
	.byte $c9,$00,$00
@env2:
	.byte $cf,$00,$00
@env3:
	.byte $cc,$cb,$ca,$ca,$c9,$03,$c8,$03,$c7,$07,$c6,$08,$c5,$0a,$c4,$0c
	.byte $c3,$0c,$c2,$12,$c1,$19,$c0,$00,$16
@env4:
	.byte $c4,$02,$c3,$0c,$c2,$0b,$c1,$12,$c0,$00,$08
@env5:
	.byte $c9,$07,$c6,$05,$c9,$07,$c9,$00,$06
@env6:
	.byte $c8,$00,$00
@env7:
	.byte $ca,$c8,$c6,$c4,$c3,$c2,$c0,$00,$06
@env8:
	.byte $c7,$c2,$c0,$00,$02
@env9:
	.byte $c8,$c8,$c7,$c7,$c6,$c6,$c5,$c5,$c4,$c4,$c3,$c2,$c1,$00,$0c
@env10:
	.byte $c7,$02,$c6,$02,$c5,$02,$c4,$c4,$c2,$00,$08
@env11:
	.byte $cd,$cb,$c9,$c7,$c5,$c4,$c3,$c2,$c0,$00,$08
@env12:
	.byte $cc,$c0,$00,$01
@env13:
	.byte $c0,$05,$bf,$be,$bd,$bc,$bb,$ba,$b9,$b8,$b7,$b6,$b5,$b4,$b3,$b2
	.byte $b1,$b0,$af,$ae,$ad,$ac,$ab,$aa,$a9,$a8,$a8,$a7,$a7,$a6,$a6,$a5
	.byte $a5,$a4,$a4,$a3,$a3,$a2,$a2,$a1,$a1,$00,$28
@env14:
	.byte $c7,$c3,$c0,$bd,$00,$02
@env15:
	.byte $c0,$c0,$c4,$c4,$c7,$c7,$00,$00
@env16:
	.byte $c0,$0e,$bf,$be,$bd,$bc,$bd,$be,$bf,$c0,$00,$02
@env17:
	.byte $c0,$0f,$c1,$02,$c2,$02,$c1,$02,$c0,$c0,$c0,$00,$02


@song0ch0:
	.byte $fb,$03
@song0ch0loop:
@ref0:
	.byte $84,$1a,$85,$32,$85,$32,$85,$1a,$85,$3c,$85,$3a,$85,$32,$85,$36
	.byte $85
@ref1:
	.byte $1e,$85,$32,$85,$1e,$85,$2e,$85,$38,$85,$32,$85,$2e,$85,$32,$85
@ref2:
	.byte $2e,$85,$00,$85,$2e,$85,$00,$85,$2e,$85,$2e,$85,$00,$85,$2e,$85
@ref3:
	.byte $32,$85,$00,$85,$32,$85,$32,$85,$34,$85,$32,$85,$16,$85,$28,$85
@ref4:
	.byte $1a,$85,$32,$85,$32,$85,$1a,$85,$3c,$85,$3a,$85,$32,$85,$36,$85
	.byte $ff,$10
	.word @ref1
	.byte $ff,$10
	.word @ref2
	.byte $ff,$10
	.word @ref3
@ref8:
	.byte $82,$4a,$9d,$46,$8d,$46,$85,$46,$85
@ref9:
	.byte $4a,$8d,$4a,$85,$46,$95,$46,$85,$46,$85
@ref10:
	.byte $84,$50,$95,$4a,$95,$46,$8d
@ref11:
	.byte $87,$4a,$95,$4a,$8d,$50,$8d
	.byte $ff,$08
	.word @ref8
	.byte $ff,$0a
	.word @ref9
	.byte $ff,$06
	.word @ref10
	.byte $ff,$07
	.word @ref11
@ref16:
	.byte $86,$32,$85,$38,$85,$3c,$85,$40,$85,$32,$85,$38,$85,$3c,$85,$40
	.byte $85
@ref17:
	.byte $2e,$85,$38,$85,$3c,$85,$40,$85,$2e,$85,$38,$85,$3c,$85,$40,$85
@ref18:
	.byte $2a,$85,$38,$85,$3c,$85,$40,$85,$2a,$85,$38,$85,$3c,$85,$40,$85
	.byte $ff,$10
	.word @ref17
@ref20:
	.byte $32,$85,$38,$85,$3c,$85,$40,$85,$32,$85,$38,$85,$3c,$85,$40,$85
	.byte $ff,$10
	.word @ref17
	.byte $ff,$10
	.word @ref18
	.byte $ff,$10
	.word @ref17
	.byte $fd
	.word @song0ch0loop

@song0ch1:
@song0ch1loop:
@ref24:
	.byte $86,$32,$85,$4a,$85,$4a,$85,$32,$85,$54,$85,$52,$85,$4a,$85,$4e
	.byte $85
@ref25:
	.byte $4e,$85,$4a,$85,$4e,$85,$46,$85,$50,$85,$4a,$85,$46,$85,$4a,$85
@ref26:
	.byte $50,$8d,$4a,$85,$4a,$85,$46,$85,$4a,$8d,$4a,$85
@ref27:
	.byte $50,$85,$54,$8d,$58,$8d,$50,$85,$50,$85,$4a,$85
@ref28:
	.byte $32,$85,$4a,$85,$4a,$85,$32,$85,$54,$85,$52,$85,$4a,$85,$4e,$85
	.byte $ff,$10
	.word @ref25
	.byte $ff,$0c
	.word @ref26
	.byte $ff,$0c
	.word @ref27
@ref32:
	.byte $84,$4a,$ad,$46,$8d
@ref33:
	.byte $4a,$95,$46,$95,$46,$8d
@ref34:
	.byte $82,$38,$95,$32,$95,$2e,$8d
@ref35:
	.byte $87,$32,$95,$32,$8d,$38,$8d
	.byte $ff,$04
	.word @ref32
	.byte $ff,$06
	.word @ref33
	.byte $ff,$06
	.word @ref34
	.byte $ff,$07
	.word @ref35
@ref40:
	.byte $84,$58,$ad,$4a,$85,$50,$85
@ref41:
	.byte $87,$4a,$a5,$4a,$85,$50,$85
@ref42:
	.byte $8f,$54,$ad
@ref43:
	.byte $5e,$8d,$54,$8d,$50,$85,$54,$95
@ref44:
	.byte $58,$ad,$4a,$85,$50,$85
	.byte $ff,$07
	.word @ref41
@ref46:
	.byte $8f,$54,$85,$50,$a5
@ref47:
	.byte $58,$85,$54,$85,$50,$85,$58,$85,$54,$85,$50,$85,$58,$85,$54,$85
	.byte $fd
	.word @song0ch1loop

@song0ch2:
@song0ch2loop:
@ref48:
	.byte $80,$32,$85,$32,$85,$32,$85,$2e,$85,$32,$85,$2e,$85,$00,$85,$32
	.byte $85
@ref49:
	.byte $00,$85,$32,$85,$32,$85,$2e,$85,$38,$85,$32,$85,$2e,$85,$32,$85
@ref50:
	.byte $38,$85,$00,$85,$38,$85,$00,$85,$38,$85,$38,$85,$38,$85,$39,$38
	.byte $81
@ref51:
	.byte $3c,$85,$3c,$85,$3c,$85,$3c,$85,$3e,$85,$3c,$85,$38,$85,$32,$85
@ref52:
	.byte $32,$85,$32,$85,$32,$85,$2e,$85,$32,$85,$2e,$85,$00,$85,$32,$85
	.byte $ff,$10
	.word @ref49
	.byte $ff,$11
	.word @ref50
	.byte $ff,$10
	.word @ref51
@ref56:
	.byte $32,$85,$32,$85,$4a,$85,$32,$85,$32,$85,$4a,$85,$32,$85,$4b,$4a
	.byte $81
@ref57:
	.byte $38,$85,$38,$85,$50,$85,$38,$85,$38,$85,$50,$85,$38,$85,$51,$50
	.byte $81
@ref58:
	.byte $3c,$85,$3c,$85,$54,$85,$3c,$85,$3c,$85,$54,$85,$3c,$85,$55,$54
	.byte $81
@ref59:
	.byte $42,$85,$42,$85,$5a,$85,$42,$85,$42,$85,$5a,$85,$42,$85,$5b,$5a
	.byte $81
	.byte $ff,$11
	.word @ref56
	.byte $ff,$11
	.word @ref57
	.byte $ff,$11
	.word @ref58
	.byte $ff,$11
	.word @ref59
	.byte $ff,$11
	.word @ref56
	.byte $ff,$11
	.word @ref57
	.byte $ff,$11
	.word @ref58
	.byte $ff,$11
	.word @ref59
	.byte $ff,$11
	.word @ref56
	.byte $ff,$11
	.word @ref57
	.byte $ff,$11
	.word @ref58
@ref71:
	.byte $42,$85,$42,$85,$5a,$85,$42,$85,$76,$74,$72,$70,$6e,$6c,$6a,$68
	.byte $66,$64,$62,$60,$5e,$5c,$5a,$58
	.byte $fd
	.word @song0ch2loop

@song0ch3:
@song0ch3loop:
@ref72:
	.byte $8a,$21,$8c,$1b,$8a,$21,$8c,$1b,$88,$21,$8c,$1b,$8a,$21,$8c,$1b
	.byte $8a,$21,$8c,$1b,$1f,$1b,$88,$21,$8c,$1b,$8a,$21,$8c,$1a,$81
@ref73:
	.byte $8a,$21,$8c,$1b,$1f,$1b,$88,$21,$8c,$1b,$8a,$21,$8c,$1b,$1f,$1b
	.byte $8a,$21,$8c,$1b,$88,$21,$8a,$21,$21,$1a,$81
@ref74:
	.byte $21,$8c,$1b,$8a,$21,$8c,$1b,$88,$21,$8c,$1b,$8a,$21,$8c,$1b,$8a
	.byte $21,$8c,$1b,$1f,$1b,$88,$21,$8c,$1b,$8a,$21,$8c,$1a,$81
@ref75:
	.byte $8a,$21,$8c,$1b,$1f,$1b,$88,$21,$8c,$1b,$8a,$21,$8c,$1b,$88,$21
	.byte $21,$03,$03,$1f,$1f,$21,$20,$81
	.byte $ff,$11
	.word @ref72
	.byte $ff,$11
	.word @ref73
	.byte $ff,$11
	.word @ref74
	.byte $ff,$11
	.word @ref75
@ref80:
	.byte $8a,$21,$8c,$1b,$8a,$21,$21,$88,$21,$8c,$1b,$8a,$21,$8c,$1b,$1f
	.byte $8a,$21,$21,$8c,$1b,$88,$21,$8c,$1b,$1f,$88,$20,$81
@ref81:
	.byte $8a,$21,$8c,$1b,$8a,$21,$21,$88,$21,$8c,$1b,$8a,$21,$8c,$1b,$1f
	.byte $8a,$21,$21,$8c,$1b,$88,$21,$8c,$1b,$88,$21,$20,$81
	.byte $ff,$11
	.word @ref80
@ref83:
	.byte $8a,$21,$8c,$1b,$8a,$21,$21,$88,$21,$8c,$1b,$8a,$21,$8c,$1b,$88
	.byte $21,$21,$03,$03,$1f,$1f,$21,$20,$81
	.byte $ff,$11
	.word @ref80
	.byte $ff,$11
	.word @ref81
	.byte $ff,$11
	.word @ref80
	.byte $ff,$11
	.word @ref83
	.byte $ff,$11
	.word @ref80
	.byte $ff,$11
	.word @ref81
	.byte $ff,$11
	.word @ref80
	.byte $ff,$11
	.word @ref83
	.byte $ff,$11
	.word @ref80
	.byte $ff,$11
	.word @ref81
@ref94:
	.byte $8a,$21,$8c,$1b,$8a,$21,$21,$88,$21,$8c,$1b,$8a,$21,$8c,$1b,$88
	.byte $21,$21,$21,$21,$8a,$21,$21,$88,$21,$8c,$1a,$81
@ref95:
	.byte $8a,$21,$8c,$1b,$88,$21,$8c,$1b,$8a,$21,$21,$88,$21,$8c,$1b,$88
	.byte $21,$21,$03,$03,$1f,$1f,$21,$20,$81
	.byte $fd
	.word @song0ch3loop

@song0ch4:
@song0ch4loop:
@ref96:
	.byte $bf
@ref97:
	.byte $bf
@ref98:
	.byte $bf
@ref99:
	.byte $bf
@ref100:
	.byte $bf
@ref101:
	.byte $bf
@ref102:
	.byte $bf
@ref103:
	.byte $bf
@ref104:
	.byte $bf
@ref105:
	.byte $bf
@ref106:
	.byte $bf
@ref107:
	.byte $bf
@ref108:
	.byte $bf
@ref109:
	.byte $bf
@ref110:
	.byte $bf
@ref111:
	.byte $bf
@ref112:
	.byte $bf
@ref113:
	.byte $bf
@ref114:
	.byte $bf
@ref115:
	.byte $bf
@ref116:
	.byte $bf
@ref117:
	.byte $bf
@ref118:
	.byte $bf
@ref119:
	.byte $bf
	.byte $fd
	.word @song0ch4loop


@song1ch0:
	.byte $fb,$06
@song1ch0loop:
@ref120:
	.byte $00,$85,$92,$45,$45,$45,$45,$43,$43,$43,$43,$41,$41,$41,$41,$43
	.byte $43,$43,$43,$45,$45,$45,$45,$4b,$4b,$4b,$4b,$49,$49,$49,$49,$43
	.byte $42,$81
@ref121:
	.byte $43,$43,$45,$45,$45,$45,$43,$43,$43,$43,$41,$41,$41,$41,$43,$43
	.byte $43,$43,$45,$45,$45,$45,$4b,$4b,$4b,$4b,$49,$49,$49,$49,$43,$42
	.byte $81
	.byte $ff,$21
	.word @ref121
@ref123:
	.byte $94,$2d,$2b,$25,$2d,$2b,$25,$2d,$2b,$2d,$2b,$25,$2d,$2b,$25,$2b
	.byte $2d,$45,$43,$3d,$45,$43,$3d,$45,$43,$45,$43,$3d,$45,$43,$3d,$5b
	.byte $5c,$81
@ref124:
	.byte $96,$45,$98,$45,$92,$45,$96,$45,$92,$45,$42,$85,$3d,$96,$43,$98
	.byte $43,$92,$43,$96,$43,$98,$43,$92,$42,$89,$96,$45,$98,$45,$92,$45
	.byte $96,$45,$92,$45,$42,$85,$3d,$96,$3d,$3d,$98,$3d,$96,$3d,$43,$43
	.byte $98,$43,$96,$42,$81
@ref125:
	.byte $00,$85,$92,$44,$89,$42,$89,$3c,$85,$4a,$89,$48,$89,$49,$49,$42
	.byte $95,$43,$43,$44,$89,$42,$89
	.byte $ff,$20
	.word @ref124
@ref127:
	.byte $82,$44,$89,$42,$89,$3c,$85,$4a,$89,$48,$89,$49,$49,$42,$95,$43
	.byte $43,$44,$89,$48,$89,$4a,$85
@ref128:
	.byte $44,$89,$48,$89,$44,$9d,$3a,$85,$44,$89,$48,$89,$40,$a5
@ref129:
	.byte $44,$89,$48,$89,$44,$85,$4e,$89,$4a,$89,$44,$85,$4e,$89,$4a,$89
	.byte $44,$85,$41,$44,$85,$44,$91
	.byte $ff,$0e
	.word @ref128
	.byte $ff,$17
	.word @ref129
	.byte $ff,$20
	.word @ref124
	.byte $ff,$16
	.word @ref125
	.byte $ff,$20
	.word @ref124
	.byte $ff,$16
	.word @ref127
@ref136:
	.byte $94,$41,$44,$85,$44,$85,$92,$49,$94,$44,$85,$41,$44,$85,$4a,$85
	.byte $44,$89,$41,$44,$85,$44,$85,$92,$49,$94,$44,$85,$41,$44,$85,$4a
	.byte $85,$4e,$89
@ref137:
	.byte $41,$44,$85,$44,$85,$92,$49,$94,$44,$85,$41,$44,$85,$4a,$85,$44
	.byte $89,$41,$44,$85,$44,$85,$92,$49,$94,$44,$85,$41,$44,$85,$4a,$85
	.byte $4e,$89
@ref138:
	.byte $82,$44,$85,$41,$44,$85,$41,$45,$41,$44,$85,$41,$44,$85,$41,$45
	.byte $41,$44,$85,$41,$44,$85,$41,$45,$41,$44,$85,$41,$44,$85,$4a,$89
@ref139:
	.byte $44,$9d,$48,$9d,$4a,$9d,$4e,$85,$4a,$85,$49,$4a,$89
	.byte $fd
	.word @song1ch0loop

@song1ch1:
@song1ch1loop:
@ref140:
	.byte $90,$45,$45,$45,$45,$43,$43,$43,$43,$41,$41,$41,$41,$43,$43,$43
	.byte $43,$45,$45,$45,$45,$4b,$4b,$4b,$4b,$49,$49,$49,$49,$43,$43,$43
	.byte $42,$81
@ref141:
	.byte $45,$45,$45,$45,$43,$43,$43,$43,$41,$41,$41,$41,$43,$43,$43,$43
	.byte $45,$45,$45,$45,$4b,$4b,$4b,$4b,$49,$49,$49,$49,$43,$43,$43,$42
	.byte $81
	.byte $ff,$21
	.word @ref141
	.byte $ff,$21
	.word @ref141
@ref144:
	.byte $44,$89,$42,$89,$3c,$85,$42,$9d,$44,$89,$42,$89,$3c,$85,$43,$44
	.byte $85,$44,$85,$42,$89
@ref145:
	.byte $44,$89,$42,$89,$3c,$85,$4a,$89,$48,$89,$49,$49,$42,$95,$43,$43
	.byte $44,$89,$42,$91
	.byte $ff,$15
	.word @ref144
@ref147:
	.byte $44,$89,$42,$89,$3c,$85,$4a,$89,$48,$89,$49,$49,$42,$95,$43,$43
	.byte $44,$89,$48,$89,$4a,$85
	.byte $ff,$0e
	.word @ref128
	.byte $ff,$17
	.word @ref129
	.byte $ff,$0e
	.word @ref128
	.byte $ff,$17
	.word @ref129
	.byte $ff,$15
	.word @ref144
	.byte $ff,$14
	.word @ref145
	.byte $ff,$15
	.word @ref144
	.byte $ff,$16
	.word @ref147
	.byte $ff,$0e
	.word @ref128
	.byte $ff,$17
	.word @ref129
@ref158:
	.byte $44,$85,$41,$44,$85,$41,$45,$41,$44,$85,$41,$44,$85,$41,$45,$41
	.byte $44,$85,$41,$44,$85,$41,$45,$41,$44,$85,$41,$44,$85,$4a,$89
@ref159:
	.byte $44,$85,$41,$44,$85,$41,$45,$41,$44,$85,$41,$44,$85,$41,$45,$41
	.byte $44,$85,$41,$44,$85,$41,$45,$41,$4e,$85,$4a,$85,$49,$4a,$89
	.byte $fd
	.word @song1ch1loop

@song1ch2:
@song1ch2loop:
@ref160:
	.byte $00,$f9,$83
@ref161:
	.byte $80,$2c,$9d,$2a,$9d,$24,$9d,$2a,$9d
@ref162:
	.byte $2c,$9d,$32,$9d,$30,$9d,$2a,$9d
@ref163:
	.byte $2c,$bd,$8e,$3c,$9d,$5d,$5b,$55,$5d,$01,$55,$5b,$5c,$81
@ref164:
	.byte $80,$2d,$2d,$45,$2d,$2d,$45,$2d,$45,$2b,$2b,$43,$2b,$2b,$43,$2b
	.byte $43,$25,$25,$3d,$25,$25,$3d,$25,$3d,$2b,$2b,$43,$2b,$2b,$43,$2b
	.byte $42,$81
@ref165:
	.byte $2d,$2d,$45,$2d,$2d,$45,$2d,$45,$33,$33,$4b,$33,$33,$4b,$33,$4b
	.byte $31,$31,$49,$31,$31,$49,$31,$49,$2b,$2b,$43,$2b,$2b,$43,$2b,$42
	.byte $81
@ref166:
	.byte $2d,$2d,$45,$2d,$2d,$45,$2d,$45,$2b,$2b,$43,$2b,$2b,$43,$2b,$43
	.byte $25,$25,$3d,$25,$25,$3d,$25,$3d,$2b,$2b,$43,$2b,$2b,$43,$2b,$42
	.byte $81
	.byte $ff,$21
	.word @ref165
@ref168:
	.byte $2c,$00,$2c,$00,$2c,$00,$2c,$00,$2c,$00,$2c,$00,$2c,$00,$2c,$44
	.byte $28,$00,$28,$00,$28,$00,$28,$00,$28,$00,$28,$00,$28,$00,$28,$40
	.byte $24,$00,$24,$00,$24,$00,$24,$00,$24,$00,$24,$00,$24,$00,$24,$3c
	.byte $28,$00,$28,$00,$28,$00,$28,$00,$28,$28,$40,$28,$28,$40,$28,$44
@ref169:
	.byte $2d,$2d,$45,$2d,$2d,$45,$2d,$44,$2c,$31,$31,$49,$31,$31,$49,$31
	.byte $48,$30,$33,$33,$4b,$33,$33,$4b,$33,$4a,$32,$37,$37,$4f,$37,$36
	.byte $36,$4e,$36,$36,$4e,$36,$52
	.byte $ff,$40
	.word @ref168
	.byte $ff,$27
	.word @ref169
	.byte $ff,$21
	.word @ref166
	.byte $ff,$21
	.word @ref165
	.byte $ff,$21
	.word @ref166
@ref175:
	.byte $2d,$2d,$45,$2d,$2d,$45,$2d,$45,$33,$33,$4b,$33,$33,$4b,$33,$4b
	.byte $31,$31,$49,$31,$31,$49,$31,$49,$44,$89,$48,$89,$4a,$85
@ref176:
	.byte $2d,$2d,$45,$2d,$2d,$45,$2d,$44,$2c,$29,$29,$41,$29,$29,$41,$29
	.byte $40,$28,$25,$25,$3d,$25,$25,$3d,$25,$3c,$24,$29,$29,$41,$29,$28
	.byte $28,$40,$28,$28,$40,$28,$44
	.byte $ff,$27
	.word @ref169
	.byte $ff,$40
	.word @ref168
@ref179:
	.byte $2c,$00,$2c,$00,$2c,$00,$2c,$00,$2c,$00,$2c,$00,$2c,$00,$2c,$44
	.byte $30,$00,$30,$00,$30,$00,$30,$00,$30,$00,$30,$00,$30,$00,$30,$48
	.byte $32,$00,$32,$00,$32,$00,$32,$00,$32,$00,$32,$00,$32,$00,$32,$4a
	.byte $36,$00,$36,$00,$36,$00,$36,$00,$8e,$4e,$4e,$66,$4e,$4e,$66,$4e
	.byte $6a
	.byte $fd
	.word @song1ch2loop

@song1ch3:
@song1ch3loop:
@ref180:
	.byte $f9,$85
@ref181:
	.byte $f9,$85
@ref182:
	.byte $f9,$85
@ref183:
	.byte $f9,$85
@ref184:
	.byte $8a,$21,$21,$88,$21,$8c,$1b,$1b,$8a,$21,$88,$21,$8c,$1b,$8a,$21
	.byte $21,$88,$21,$8c,$1b,$1b,$8a,$21,$88,$21,$8a,$21,$21,$88,$21,$8c
	.byte $1b,$1b,$8a,$21,$21,$88,$21,$8a,$21,$21,$21,$88,$21,$8c,$1b,$1b
	.byte $8a,$21,$88,$21,$8c,$1a,$81
@ref185:
	.byte $8a,$21,$21,$88,$21,$8c,$1b,$1b,$8a,$21,$88,$21,$8c,$1b,$8a,$21
	.byte $21,$88,$21,$8c,$1b,$1b,$8a,$21,$88,$21,$8a,$21,$21,$88,$21,$8c
	.byte $1b,$1b,$8a,$21,$21,$88,$21,$8a,$21,$21,$21,$88,$21,$21,$8a,$21
	.byte $21,$88,$21,$20,$81
	.byte $ff,$21
	.word @ref184
	.byte $ff,$21
	.word @ref185
@ref188:
	.byte $8a,$20,$8c,$1a,$1a,$1a,$8a,$20,$8c,$1a,$1a,$1a,$88,$20,$8c,$1a
	.byte $8a,$20,$8c,$1a,$8a,$21,$8c,$1b,$1a,$1a,$1b,$8a,$21,$8c,$1b,$88
	.byte $21,$8a,$21,$21,$8c,$1b,$8a,$20,$8c,$1a,$1a,$1a,$8a,$20,$8c,$1a
	.byte $1a,$1a,$88,$20,$8c,$1a,$1a,$1a,$8a,$21,$21,$8c,$1a,$1a,$1b,$8a
	.byte $21,$21,$88,$21,$8a,$21,$21,$8c,$1a,$81
	.byte $ff,$2f
	.word @ref188
	.byte $ff,$21
	.word @ref184
	.byte $ff,$21
	.word @ref185
	.byte $ff,$21
	.word @ref184
	.byte $ff,$21
	.word @ref185
	.byte $ff,$21
	.word @ref184
@ref195:
	.byte $8a,$21,$21,$88,$21,$8c,$1b,$1b,$8a,$21,$88,$21,$8c,$1b,$8a,$21
	.byte $21,$88,$21,$8c,$1b,$1b,$8a,$21,$88,$21,$8a,$21,$21,$88,$21,$8c
	.byte $1b,$1b,$8a,$21,$88,$21,$8c,$1b,$8a,$21,$88,$20,$9d
	.byte $ff,$21
	.word @ref184
	.byte $ff,$21
	.word @ref185
	.byte $ff,$21
	.word @ref184
	.byte $ff,$21
	.word @ref185
	.byte $fd
	.word @song1ch3loop

@song1ch4:
@song1ch4loop:
@ref200:
	.byte $f9,$85
@ref201:
	.byte $f9,$85
@ref202:
	.byte $f9,$85
@ref203:
	.byte $f9,$85
@ref204:
	.byte $f9,$85
@ref205:
	.byte $f9,$85
@ref206:
	.byte $f9,$85
@ref207:
	.byte $f9,$85
@ref208:
	.byte $f9,$85
@ref209:
	.byte $f9,$85
@ref210:
	.byte $f9,$85
@ref211:
	.byte $f9,$85
@ref212:
	.byte $f9,$85
@ref213:
	.byte $f9,$85
@ref214:
	.byte $f9,$85
@ref215:
	.byte $f9,$85
@ref216:
	.byte $f9,$85
@ref217:
	.byte $f9,$85
@ref218:
	.byte $f9,$85
@ref219:
	.byte $f9,$85
	.byte $fd
	.word @song1ch4loop


@song2ch0:
	.byte $fb,$06
@song2ch0loop:
@ref220:
	.byte $86,$43,$41,$39,$33,$2b,$29,$2f,$33,$43,$41,$39,$33,$2b,$29,$2f
	.byte $32,$81
@ref221:
	.byte $3f,$3d,$35,$2f,$27,$25,$2b,$2f,$3f,$3d,$35,$2f,$27,$25,$2b,$2e
	.byte $81
@ref222:
	.byte $3b,$39,$31,$2b,$23,$21,$27,$2b,$3b,$39,$31,$2b,$23,$21,$27,$2a
	.byte $81
	.byte $ff,$11
	.word @ref221
@ref224:
	.byte $43,$41,$39,$33,$2b,$29,$2f,$33,$43,$41,$39,$33,$2b,$29,$2f,$32
	.byte $81
	.byte $ff,$11
	.word @ref221
	.byte $ff,$11
	.word @ref222
	.byte $ff,$11
	.word @ref222
	.byte $ff,$11
	.word @ref224
	.byte $ff,$11
	.word @ref221
	.byte $ff,$11
	.word @ref222
	.byte $ff,$11
	.word @ref222
@ref232:
	.byte $5b,$51,$4d,$47,$43,$3f,$43,$47,$5b,$51,$4d,$47,$43,$3f,$43,$46
	.byte $81
	.byte $ff,$11
	.word @ref232
	.byte $ff,$11
	.word @ref232
	.byte $ff,$11
	.word @ref232
@ref236:
	.byte $84,$42,$b5,$42,$85
@ref237:
	.byte $3e,$85,$42,$8d,$3e,$9d,$3b,$3e,$81
@ref238:
	.byte $42,$85,$3a,$85,$3b,$3e,$89,$3a,$99,$3e,$81
@ref239:
	.byte $42,$8d,$3e,$8d,$42,$8d,$3e,$8d
@ref240:
	.byte $42,$b5,$42,$85
	.byte $ff,$09
	.word @ref237
@ref242:
	.byte $42,$85,$3a,$85,$3b,$3e,$89,$3a,$99,$3a,$81
@ref243:
	.byte $42,$8d,$3e,$8d,$42,$8d,$46,$8d
@ref244:
	.byte $86,$5a,$85,$50,$85,$5b,$50,$89,$5a,$85,$50,$85,$5b,$50,$89
@ref245:
	.byte $5a,$85,$50,$85,$5b,$50,$89,$5a,$85,$50,$85,$5b,$5e,$89
@ref246:
	.byte $84,$5a,$85,$50,$85,$5b,$50,$89,$5a,$85,$50,$85,$5b,$50,$89
	.byte $ff,$0e
	.word @ref245
	.byte $ff,$0e
	.word @ref244
	.byte $ff,$0e
	.word @ref245
	.byte $ff,$0e
	.word @ref246
	.byte $ff,$0e
	.word @ref245
	.byte $fd
	.word @song2ch0loop

@song2ch1:
@song2ch1loop:
@ref252:
	.byte $84,$5b,$59,$51,$4b,$43,$41,$47,$4b,$5b,$59,$51,$4b,$43,$41,$47
	.byte $4a,$81
@ref253:
	.byte $57,$55,$4d,$47,$3f,$3d,$43,$47,$57,$55,$4d,$47,$3f,$3d,$43,$46
	.byte $81
@ref254:
	.byte $53,$51,$49,$43,$3b,$39,$3f,$43,$53,$51,$49,$43,$3b,$39,$3f,$42
	.byte $81
	.byte $ff,$11
	.word @ref253
@ref256:
	.byte $82,$42,$91,$40,$85,$42,$8d,$41,$43,$40,$89
@ref257:
	.byte $3e,$95,$3d,$3e,$99,$3c,$85
@ref258:
	.byte $3a,$8d,$38,$89,$39,$3a,$8d,$34,$89,$38,$81
@ref259:
	.byte $3e,$8d,$3c,$89,$3d,$3e,$8d,$42,$8d
@ref260:
	.byte $42,$91,$40,$85,$42,$8d,$41,$43,$40,$89
	.byte $ff,$07
	.word @ref257
	.byte $ff,$0b
	.word @ref258
	.byte $ff,$09
	.word @ref259
@ref264:
	.byte $84,$5a,$85,$50,$85,$5a,$85,$01,$5b,$01,$5b,$01,$51,$5b,$5f,$50
	.byte $85
@ref265:
	.byte $5a,$85,$50,$85,$5a,$85,$01,$5b,$01,$5b,$01,$51,$5b,$5f,$50,$85
	.byte $ff,$10
	.word @ref265
	.byte $ff,$10
	.word @ref265
@ref268:
	.byte $82,$42,$b5,$42,$85
	.byte $ff,$09
	.word @ref237
	.byte $ff,$0b
	.word @ref238
	.byte $ff,$08
	.word @ref239
@ref272:
	.byte $42,$b5,$42,$85
	.byte $ff,$09
	.word @ref237
	.byte $ff,$0b
	.word @ref242
	.byte $ff,$08
	.word @ref243
@ref276:
	.byte $38,$85,$42,$85,$47,$42,$89,$46,$85,$42,$85,$38,$85,$42,$85
@ref277:
	.byte $38,$85,$42,$85,$47,$42,$89,$46,$85,$42,$85,$46,$85,$48,$85
@ref278:
	.byte $4c,$95,$4d,$49,$46,$9d
@ref279:
	.byte $4c,$95,$4d,$49,$46,$8d,$48,$8d
	.byte $ff,$0f
	.word @ref276
	.byte $ff,$0f
	.word @ref277
	.byte $ff,$06
	.word @ref278
@ref283:
	.byte $42,$8d,$46,$8d,$48,$8d,$4c,$8d
	.byte $fd
	.word @song2ch1loop

@song2ch2:
@song2ch2loop:
@ref284:
	.byte $00,$bd
@ref285:
	.byte $bf
@ref286:
	.byte $bf
@ref287:
	.byte $9f,$80,$6f,$6d,$65,$5f,$57,$55,$5b,$5e,$81
@ref288:
	.byte $2b,$01,$2a,$89,$29,$01,$2b,$01,$2a,$85,$27,$2b,$27,$21,$1c,$81
@ref289:
	.byte $20,$85,$21,$2e,$89,$21,$20,$85,$1d,$27,$01,$27,$25,$1d,$2e,$81
@ref290:
	.byte $22,$85,$22,$85,$23,$3b,$22,$85,$22,$85,$22,$85,$23,$3b,$22,$85
@ref291:
	.byte $26,$85,$26,$85,$27,$3f,$26,$85,$26,$85,$26,$85,$27,$3f,$27,$42
	.byte $81
	.byte $ff,$10
	.word @ref288
	.byte $ff,$10
	.word @ref289
	.byte $ff,$10
	.word @ref290
	.byte $ff,$11
	.word @ref291
@ref296:
	.byte $2b,$2b,$2b,$2b,$43,$2b,$2b,$2b,$2b,$2b,$2b,$2b,$43,$2b,$2b,$42
	.byte $81
@ref297:
	.byte $27,$27,$27,$27,$3f,$27,$27,$27,$27,$27,$27,$27,$3f,$27,$27,$3e
	.byte $81
@ref298:
	.byte $23,$23,$23,$23,$3b,$23,$23,$23,$23,$23,$23,$23,$3b,$23,$23,$3a
	.byte $81
	.byte $ff,$11
	.word @ref297
	.byte $ff,$11
	.word @ref296
	.byte $ff,$11
	.word @ref297
	.byte $ff,$11
	.word @ref298
	.byte $ff,$11
	.word @ref297
	.byte $ff,$11
	.word @ref296
	.byte $ff,$11
	.word @ref297
	.byte $ff,$11
	.word @ref298
	.byte $ff,$11
	.word @ref297
	.byte $ff,$11
	.word @ref296
	.byte $ff,$11
	.word @ref297
	.byte $ff,$11
	.word @ref298
	.byte $ff,$11
	.word @ref297
	.byte $ff,$11
	.word @ref296
	.byte $ff,$11
	.word @ref297
	.byte $ff,$11
	.word @ref298
	.byte $ff,$11
	.word @ref297
	.byte $fd
	.word @song2ch2loop

@song2ch3:
@song2ch3loop:
@ref316:
	.byte $bf
@ref317:
	.byte $bf
@ref318:
	.byte $bf
@ref319:
	.byte $bf
@ref320:
	.byte $8a,$21,$8c,$1b,$8a,$21,$8c,$1b,$88,$21,$8a,$21,$8c,$1b,$8a,$21
	.byte $8c,$1b,$8a,$21,$8c,$1b,$8a,$21,$88,$21,$8a,$21,$8c,$1b,$8a,$20
	.byte $81
@ref321:
	.byte $21,$21,$8c,$1b,$8a,$21,$88,$21,$8a,$21,$8c,$1b,$8a,$21,$8c,$1b
	.byte $8a,$21,$21,$21,$88,$21,$8a,$21,$88,$21,$20,$81
	.byte $ff,$11
	.word @ref320
	.byte $ff,$11
	.word @ref321
	.byte $ff,$11
	.word @ref320
	.byte $ff,$11
	.word @ref321
	.byte $ff,$11
	.word @ref320
	.byte $ff,$11
	.word @ref321
	.byte $ff,$11
	.word @ref320
	.byte $ff,$11
	.word @ref321
	.byte $ff,$11
	.word @ref320
	.byte $ff,$11
	.word @ref321
	.byte $ff,$11
	.word @ref320
	.byte $ff,$11
	.word @ref321
	.byte $ff,$11
	.word @ref320
	.byte $ff,$11
	.word @ref321
	.byte $ff,$11
	.word @ref320
	.byte $ff,$11
	.word @ref321
	.byte $ff,$11
	.word @ref320
@ref339:
	.byte $21,$21,$8c,$1b,$8a,$21,$88,$21,$8a,$21,$8c,$1b,$8a,$21,$88,$21
	.byte $21,$21,$21,$8a,$21,$21,$88,$21,$20,$81
	.byte $ff,$11
	.word @ref320
	.byte $ff,$11
	.word @ref321
	.byte $ff,$11
	.word @ref320
	.byte $ff,$11
	.word @ref339
	.byte $ff,$11
	.word @ref320
	.byte $ff,$11
	.word @ref321
	.byte $ff,$11
	.word @ref320
	.byte $ff,$11
	.word @ref339
	.byte $fd
	.word @song2ch3loop

@song2ch4:
@song2ch4loop:
@ref348:
	.byte $bf
@ref349:
	.byte $bf
@ref350:
	.byte $bf
@ref351:
	.byte $bf
@ref352:
	.byte $bf
@ref353:
	.byte $bf
@ref354:
	.byte $bf
@ref355:
	.byte $bf
@ref356:
	.byte $bf
@ref357:
	.byte $bf
@ref358:
	.byte $bf
@ref359:
	.byte $bf
@ref360:
	.byte $bf
@ref361:
	.byte $bf
@ref362:
	.byte $bf
@ref363:
	.byte $bf
@ref364:
	.byte $bf
@ref365:
	.byte $bf
@ref366:
	.byte $bf
@ref367:
	.byte $bf
@ref368:
	.byte $bf
@ref369:
	.byte $bf
@ref370:
	.byte $bf
@ref371:
	.byte $bf
@ref372:
	.byte $bf
@ref373:
	.byte $bf
@ref374:
	.byte $bf
@ref375:
	.byte $bf
@ref376:
	.byte $bf
@ref377:
	.byte $bf
@ref378:
	.byte $bf
@ref379:
	.byte $bf
	.byte $fd
	.word @song2ch4loop


@song3ch0:
	.byte $fb,$08
@song3ch0loop:
@ref380:
	.byte $01,$92,$60,$5c,$58,$54,$52,$4e,$4a,$4e,$3c,$3a,$36,$32,$30,$2c
	.byte $30,$32,$60,$5c,$58,$54,$52,$4e,$4a,$4e,$3c,$3a,$36,$32,$30,$2c
	.byte $60,$5c,$58,$54,$52,$4e,$4a,$4e,$3c,$3a,$36,$32,$30,$2c,$30,$32
	.byte $60,$5c,$58,$54,$52,$4e,$4a,$4e,$3c,$3a,$36,$32,$30,$2c,$30,$32
@ref381:
	.byte $60,$5c,$58,$54,$52,$4e,$4a,$4e,$3c,$3a,$36,$32,$30,$2c,$30,$32
	.byte $60,$5c,$58,$54,$52,$4e,$4a,$4e,$3c,$3a,$36,$32,$30,$2c,$30,$32
@ref382:
	.byte $00,$85,$52,$95,$53,$54,$85,$52,$85,$53,$4b,$4e,$85,$4f,$52,$95
	.byte $53,$54,$85,$52,$85,$4a,$85,$4e,$81
@ref383:
	.byte $87,$52,$95,$53,$54,$85,$52,$85,$53,$4b,$4e,$85,$4f,$52,$95,$53
	.byte $54,$85,$52,$85,$54,$85,$58,$81
@ref384:
	.byte $82,$53,$45,$4f,$52,$85,$45,$4f,$52,$85,$45,$4f,$52,$85,$55,$53
	.byte $4a,$89,$53,$4a,$89,$4b,$4b,$4f,$4a,$85,$48,$85,$4a,$89
@ref385:
	.byte $53,$45,$4f,$52,$85,$45,$4f,$52,$85,$45,$4f,$52,$85,$55,$53,$4a
	.byte $89,$53,$4a,$89,$4b,$4b,$4f,$4a,$85,$48,$85,$4a,$89
	.byte $fd
	.word @song3ch0loop

@song3ch1:
@song3ch1loop:
@ref386:
	.byte $90,$60,$5c,$58,$54,$52,$4e,$4a,$4e,$3c,$3a,$36,$32,$30,$2c,$30
	.byte $32,$60,$5c,$58,$54,$52,$4e,$4a,$4e,$3c,$3a,$36,$32,$30,$2c,$30
	.byte $32,$82,$48,$89,$49,$44,$85,$45,$4a,$89,$48,$89,$45,$48,$85
@ref387:
	.byte $48,$89,$49,$44,$85,$45,$4a,$85,$48,$85,$4e,$85,$52,$85,$52,$81
@ref388:
	.byte $90,$52,$95,$53,$54,$85,$52,$85,$53,$4b,$4e,$85,$4f,$52,$95,$53
	.byte $54,$85,$52,$85,$4a,$85,$4e,$89
@ref389:
	.byte $52,$95,$53,$54,$85,$52,$85,$53,$4b,$4e,$85,$4f,$52,$95,$53,$54
	.byte $85,$52,$85,$54,$85,$58,$89
	.byte $ff,$1d
	.word @ref385
	.byte $ff,$1d
	.word @ref385
	.byte $fd
	.word @song3ch1loop

@song3ch2:
@song3ch2loop:
@ref392:
	.byte $00,$bd,$80,$30,$89,$31,$2c,$85,$2d,$32,$89,$30,$89,$2d,$30,$85
@ref393:
	.byte $30,$89,$31,$2c,$85,$2d,$32,$85,$30,$85,$36,$85,$3a,$85,$3a,$81
@ref394:
	.byte $31,$49,$31,$49,$31,$49,$31,$49,$2d,$45,$2d,$45,$2d,$45,$2d,$45
	.byte $29,$41,$29,$41,$29,$41,$29,$41,$2d,$45,$2d,$45,$2d,$45,$2d,$48
	.byte $81
	.byte $ff,$21
	.word @ref394
	.byte $ff,$21
	.word @ref394
	.byte $ff,$21
	.word @ref394
	.byte $fd
	.word @song3ch2loop

@song3ch3:
@song3ch3loop:
@ref398:
	.byte $f9,$85
@ref399:
	.byte $bf
@ref400:
	.byte $8a,$20,$8c,$1a,$8a,$20,$8c,$1a,$88,$20,$8c,$1a,$8a,$20,$8c,$1a
	.byte $1a,$1a,$8a,$20,$20,$88,$20,$8c,$1a,$8a,$20,$8c,$1a,$8a,$20,$8c
	.byte $1a,$8a,$20,$8c,$1a,$88,$20,$8c,$1a,$8a,$20,$8c,$1a,$1a,$1a,$8a
	.byte $20,$20,$88,$20,$8c,$1a,$88,$20,$20,$8a,$20,$8c,$1a,$8a,$20,$8c
	.byte $1a,$88,$20,$8c,$1a,$8a,$20,$8c,$1a,$1a,$1a,$8a,$20,$20,$88,$20
	.byte $8c,$1a,$8a,$20,$8c,$1a,$8a,$20,$8c,$1a,$8a,$20,$8c,$1a,$88,$20
	.byte $8c,$1a,$8a,$20,$8c,$1a,$1a,$1a,$8a,$20,$20,$88,$20,$20,$20,$20
	.byte $ff,$40
	.word @ref400
	.byte $ff,$40
	.word @ref400
	.byte $ff,$40
	.word @ref400
	.byte $fd
	.word @song3ch3loop

@song3ch4:
@song3ch4loop:
@ref404:
	.byte $f9,$85
@ref405:
	.byte $bf
@ref406:
	.byte $f9,$85
@ref407:
	.byte $f9,$85
@ref408:
	.byte $f9,$85
@ref409:
	.byte $f9,$85
	.byte $fd
	.word @song3ch4loop


@song4ch0:
	.byte $fb,$03
@song4ch0loop:
@ref410:
	.byte $84,$34,$85,$34,$85,$35,$35,$38,$85,$38,$85,$39,$38,$81
@ref411:
	.byte $3a,$85,$3a,$85,$3b,$3b,$38,$85,$38,$85,$31,$30,$81
@ref412:
	.byte $34,$85,$34,$85,$35,$35,$38,$85,$38,$85,$39,$38,$81
@ref413:
	.byte $3e,$85,$3e,$85,$3f,$3f,$3a,$85,$3a,$85,$35,$34,$81
@ref414:
	.byte $82,$3a,$85,$3e,$95,$3e,$9d
@ref415:
	.byte $3a,$85,$3e,$8d,$44,$8d,$3e,$8d,$3b,$42,$81
@ref416:
	.byte $3e,$95,$3a,$95,$38,$8d
@ref417:
	.byte $86,$34,$85,$30,$85,$38,$85,$34,$a5
@ref418:
	.byte $82,$34,$95,$30,$a5
@ref419:
	.byte $bf
@ref420:
	.byte $84,$38,$95,$3a,$95,$3e,$8d
@ref421:
	.byte $42,$8d,$3e,$85,$43,$47,$42,$85,$3e,$85,$42,$85,$46,$85
@ref422:
	.byte $82,$4c,$95,$42,$8d,$42,$85,$52,$8d
@ref423:
	.byte $50,$ad,$4c,$85,$50,$85
@ref424:
	.byte $52,$95,$50,$95,$4c,$8d
@ref425:
	.byte $48,$85,$4c,$8d,$4c,$a5
@ref426:
	.byte $4c,$95,$42,$8d,$42,$85,$52,$8d
	.byte $ff,$06
	.word @ref423
@ref428:
	.byte $50,$bd
@ref429:
	.byte $52,$8d,$50,$8d,$4c,$8d,$50,$8d
	.byte $ff,$08
	.word @ref426
	.byte $ff,$06
	.word @ref423
	.byte $ff,$06
	.word @ref424
	.byte $ff,$06
	.word @ref425
	.byte $ff,$08
	.word @ref426
	.byte $ff,$06
	.word @ref423
@ref436:
	.byte $50,$bd
@ref437:
	.byte $86,$44,$85,$42,$85,$3e,$85,$3a,$85,$3e,$85,$42,$85,$44,$85,$42
	.byte $85
@ref438:
	.byte $84,$4c,$85,$42,$85,$50,$85,$52,$85,$50,$85,$4c,$85,$48,$85,$4c
	.byte $85
@ref439:
	.byte $4c,$85,$42,$85,$50,$85,$52,$85,$50,$85,$4c,$85,$48,$85,$4c,$85
@ref440:
	.byte $50,$85,$46,$85,$54,$85,$56,$85,$54,$85,$50,$85,$4c,$85,$50,$85
	.byte $ff,$10
	.word @ref440
	.byte $ff,$10
	.word @ref439
	.byte $ff,$10
	.word @ref439
	.byte $ff,$10
	.word @ref440
	.byte $ff,$10
	.word @ref440
@ref446:
	.byte $82,$34,$95,$42,$95,$3a,$8d
@ref447:
	.byte $87,$38,$95,$3a,$85,$53,$57,$52,$8d
@ref448:
	.byte $86,$4c,$85,$92,$34,$85,$86,$4c,$85,$50,$85,$92,$30,$85,$86,$50
	.byte $85,$52,$85,$92,$38,$85
@ref449:
	.byte $86,$52,$85,$56,$85,$92,$3a,$85,$86,$56,$85,$52,$85,$92,$42,$85
	.byte $86,$50,$85,$92,$3a,$85
	.byte $ff,$06
	.word @ref446
	.byte $ff,$09
	.word @ref447
@ref452:
	.byte $84,$42,$85,$42,$85,$42,$85,$46,$85,$46,$85,$46,$85,$48,$85,$48
	.byte $85
@ref453:
	.byte $48,$85,$4c,$85,$4c,$85,$4c,$85,$46,$85,$46,$85,$48,$85,$48,$85
@ref454:
	.byte $42,$85,$42,$85,$42,$85,$46,$85,$46,$85,$46,$85,$48,$85,$48,$85
	.byte $ff,$10
	.word @ref453
	.byte $fd
	.word @song4ch0loop

@song4ch1:
@song4ch1loop:
@ref456:
	.byte $86,$3e,$85,$3e,$85,$3f,$3f,$42,$85,$42,$85,$43,$42,$81
@ref457:
	.byte $44,$85,$44,$85,$45,$45,$42,$85,$42,$85,$3b,$3a,$81
@ref458:
	.byte $3e,$85,$3e,$85,$3f,$3f,$42,$85,$42,$85,$43,$42,$81
@ref459:
	.byte $48,$85,$48,$85,$49,$49,$44,$85,$44,$85,$3f,$3e,$81
@ref460:
	.byte $84,$3e,$95,$42,$85,$44,$95,$48,$85
@ref461:
	.byte $87,$44,$8d,$42,$8d,$44,$8d,$3b,$42,$81
	.byte $ff,$06
	.word @ref416
@ref463:
	.byte $34,$85,$30,$8d,$34,$8d,$38,$8d,$35,$38,$81
@ref464:
	.byte $34,$95,$30,$9d,$86,$3e,$85
@ref465:
	.byte $42,$85,$42,$85,$44,$85,$44,$85,$48,$85,$48,$85,$44,$85,$48,$85
@ref466:
	.byte $50,$85,$50,$85,$00,$85,$52,$85,$52,$85,$00,$85,$56,$85,$56,$85
@ref467:
	.byte $5a,$85,$5a,$85,$56,$85,$5b,$5f,$5a,$85,$56,$85,$5a,$85,$5e,$85
@ref468:
	.byte $84,$4c,$95,$42,$8d,$42,$85,$52,$8d
	.byte $ff,$06
	.word @ref423
	.byte $ff,$06
	.word @ref424
	.byte $ff,$06
	.word @ref425
	.byte $ff,$08
	.word @ref426
	.byte $ff,$06
	.word @ref423
@ref474:
	.byte $50,$bd
	.byte $ff,$08
	.word @ref429
	.byte $ff,$08
	.word @ref426
	.byte $ff,$06
	.word @ref423
	.byte $ff,$06
	.word @ref424
	.byte $ff,$06
	.word @ref425
	.byte $ff,$08
	.word @ref426
	.byte $ff,$06
	.word @ref423
@ref482:
	.byte $50,$bd
@ref483:
	.byte $52,$85,$50,$85,$4c,$85,$48,$85,$4c,$85,$50,$85,$52,$85,$50,$85
@ref484:
	.byte $82,$42,$95,$42,$85,$46,$8d,$48,$8d
@ref485:
	.byte $8f,$42,$8d,$46,$8d,$48,$8d
@ref486:
	.byte $46,$95,$46,$85,$48,$8d,$4c,$8d
@ref487:
	.byte $8f,$46,$8d,$48,$8d,$4c,$8d
@ref488:
	.byte $42,$95,$42,$85,$46,$8d,$48,$8d
	.byte $ff,$07
	.word @ref485
	.byte $ff,$08
	.word @ref486
	.byte $ff,$07
	.word @ref487
@ref492:
	.byte $84,$4c,$95,$5a,$85,$56,$85,$52,$85,$4c,$85,$52,$85
@ref493:
	.byte $87,$4c,$8d,$52,$8d,$3b,$3f,$3a,$8d
@ref494:
	.byte $90,$34,$95,$30,$95,$38,$8d
@ref495:
	.byte $87,$3a,$95,$42,$8d,$3a,$8d
@ref496:
	.byte $84,$34,$95,$42,$85,$3e,$85,$3a,$85,$34,$85,$3a,$85
@ref497:
	.byte $87,$38,$95,$3a,$8d,$3e,$8d
@ref498:
	.byte $86,$4c,$85,$4c,$85,$4c,$85,$50,$85,$50,$85,$50,$85,$52,$85,$52
	.byte $85
@ref499:
	.byte $52,$85,$56,$85,$56,$85,$56,$85,$50,$85,$50,$85,$52,$85,$52,$85
@ref500:
	.byte $4c,$85,$4c,$85,$4c,$85,$50,$85,$50,$85,$50,$85,$52,$85,$52,$85
	.byte $ff,$10
	.word @ref499
	.byte $fd
	.word @song4ch1loop

@song4ch2:
@song4ch2loop:
@ref502:
	.byte $80,$27,$27,$27,$27,$27,$27,$27,$27,$27,$27,$3f,$34,$81
@ref503:
	.byte $2d,$2d,$2d,$2d,$2d,$2d,$2d,$2d,$2d,$2d,$45,$3a,$81
@ref504:
	.byte $2b,$2b,$2b,$2b,$2b,$2b,$2b,$2b,$2b,$2b,$43,$38,$81
@ref505:
	.byte $23,$23,$23,$23,$23,$23,$23,$23,$23,$23,$3b,$30,$81
@ref506:
	.byte $26,$85,$26,$85,$28,$85,$26,$85,$26,$85,$26,$85,$26,$85,$28,$85
@ref507:
	.byte $22,$85,$22,$85,$22,$85,$26,$85,$28,$85,$22,$85,$22,$85,$22,$85
	.byte $ff,$10
	.word @ref506
@ref509:
	.byte $22,$85,$22,$85,$22,$85,$2c,$85,$28,$85,$26,$85,$22,$85,$26,$85
	.byte $ff,$10
	.word @ref506
	.byte $ff,$10
	.word @ref507
	.byte $ff,$10
	.word @ref506
	.byte $ff,$10
	.word @ref509
@ref514:
	.byte $34,$85,$34,$85,$4c,$85,$34,$85,$34,$85,$4c,$85,$34,$85,$4d,$34
	.byte $81
@ref515:
	.byte $42,$85,$42,$85,$5a,$85,$42,$85,$42,$85,$5a,$85,$42,$85,$5b,$42
	.byte $81
@ref516:
	.byte $3e,$85,$3e,$85,$56,$85,$3e,$85,$3e,$85,$56,$85,$3e,$85,$57,$3e
	.byte $81
@ref517:
	.byte $3a,$85,$3a,$85,$52,$85,$3a,$85,$3a,$85,$52,$85,$3a,$85,$53,$3a
	.byte $81
	.byte $ff,$11
	.word @ref514
	.byte $ff,$11
	.word @ref515
	.byte $ff,$11
	.word @ref516
	.byte $ff,$11
	.word @ref517
	.byte $ff,$11
	.word @ref514
	.byte $ff,$11
	.word @ref515
	.byte $ff,$11
	.word @ref516
	.byte $ff,$11
	.word @ref517
	.byte $ff,$11
	.word @ref514
	.byte $ff,$11
	.word @ref515
	.byte $ff,$11
	.word @ref516
	.byte $ff,$11
	.word @ref517
@ref530:
	.byte $2a,$95,$2e,$95,$30,$8d
@ref531:
	.byte $87,$2a,$95,$2e,$8d,$30,$8d
@ref532:
	.byte $2e,$95,$30,$95,$34,$8d
@ref533:
	.byte $87,$2e,$95,$30,$8d,$34,$8d
	.byte $ff,$06
	.word @ref530
	.byte $ff,$07
	.word @ref531
	.byte $ff,$06
	.word @ref532
	.byte $ff,$07
	.word @ref533
@ref538:
	.byte $26,$85,$26,$85,$26,$85,$26,$85,$26,$85,$26,$85,$26,$85,$3f,$34
	.byte $81
@ref539:
	.byte $2c,$85,$2c,$85,$2c,$85,$2c,$85,$2c,$85,$2c,$85,$2c,$85,$45,$3a
	.byte $81
@ref540:
	.byte $2a,$85,$2a,$85,$2a,$85,$2a,$85,$2a,$85,$2a,$85,$43,$39,$22,$85
@ref541:
	.byte $22,$85,$22,$85,$22,$85,$22,$85,$22,$85,$22,$85,$22,$85,$3b,$30
	.byte $81
	.byte $ff,$11
	.word @ref538
	.byte $ff,$11
	.word @ref539
	.byte $ff,$10
	.word @ref540
	.byte $ff,$11
	.word @ref541
@ref546:
	.byte $39,$3b,$3f,$43,$47,$49,$43,$47,$39,$3b,$3f,$43,$47,$49,$43,$46
	.byte $81
@ref547:
	.byte $51,$53,$57,$5b,$5f,$61,$5b,$5f,$69,$6b,$6f,$73,$77,$79,$73,$76
	.byte $81
	.byte $fd
	.word @song4ch2loop

@song4ch3:
@song4ch3loop:
@ref548:
	.byte $af
@ref549:
	.byte $af
@ref550:
	.byte $af
@ref551:
	.byte $88,$21,$21,$21,$21,$8a,$21,$21,$88,$21,$21,$8a,$21,$21,$88,$21
	.byte $20,$81
	.byte $ff,$11
	.word @ref72
@ref553:
	.byte $8a,$21,$8c,$1b,$1f,$1b,$88,$21,$8c,$1b,$8a,$21,$8c,$1b,$1f,$1b
	.byte $8a,$21,$8c,$1b,$88,$21,$8c,$1b,$8a,$21,$8c,$1a,$81
	.byte $ff,$11
	.word @ref72
	.byte $ff,$11
	.word @ref553
	.byte $ff,$11
	.word @ref72
	.byte $ff,$11
	.word @ref553
	.byte $ff,$11
	.word @ref72
@ref559:
	.byte $88,$21,$21,$21,$21,$8a,$21,$21,$88,$21,$21,$8a,$21,$21,$88,$21
	.byte $21,$21,$21,$8a,$21,$20,$81
	.byte $ff,$11
	.word @ref74
	.byte $ff,$11
	.word @ref553
	.byte $ff,$11
	.word @ref72
	.byte $ff,$11
	.word @ref553
	.byte $ff,$11
	.word @ref72
	.byte $ff,$11
	.word @ref553
	.byte $ff,$11
	.word @ref72
	.byte $ff,$11
	.word @ref559
	.byte $ff,$11
	.word @ref74
	.byte $ff,$11
	.word @ref553
	.byte $ff,$11
	.word @ref72
	.byte $ff,$11
	.word @ref553
	.byte $ff,$11
	.word @ref72
	.byte $ff,$11
	.word @ref553
	.byte $ff,$11
	.word @ref72
	.byte $ff,$11
	.word @ref559
@ref576:
	.byte $20,$85,$8c,$1a,$85,$8a,$20,$85,$8c,$1a,$85,$88,$20,$85,$8c,$1a
	.byte $85,$8a,$20,$85,$8c,$1a,$85
@ref577:
	.byte $8a,$20,$85,$8c,$1a,$85,$1e,$85,$1a,$85,$88,$20,$85,$8a,$20,$85
	.byte $20,$85,$8c,$1a,$85
@ref578:
	.byte $8a,$20,$85,$8c,$1a,$85,$8a,$20,$85,$8c,$1a,$85,$88,$20,$85,$8c
	.byte $1a,$85,$8a,$20,$85,$8c,$1a,$85
	.byte $ff,$10
	.word @ref577
	.byte $ff,$10
	.word @ref578
	.byte $ff,$10
	.word @ref577
	.byte $ff,$10
	.word @ref578
@ref583:
	.byte $8a,$20,$85,$8c,$1a,$85,$8a,$20,$85,$20,$85,$88,$21,$21,$21,$21
	.byte $8a,$21,$21,$88,$21,$20,$81
	.byte $ff,$11
	.word @ref72
	.byte $ff,$11
	.word @ref553
	.byte $ff,$11
	.word @ref72
	.byte $ff,$11
	.word @ref553
	.byte $ff,$11
	.word @ref72
	.byte $ff,$11
	.word @ref553
	.byte $ff,$11
	.word @ref72
	.byte $ff,$11
	.word @ref559
	.byte $ff,$11
	.word @ref559
	.byte $ff,$11
	.word @ref559
	.byte $fd
	.word @song4ch3loop

@song4ch4:
@song4ch4loop:
@ref594:
	.byte $af
@ref595:
	.byte $af
@ref596:
	.byte $af
@ref597:
	.byte $af
@ref598:
	.byte $bf
@ref599:
	.byte $bf
@ref600:
	.byte $bf
@ref601:
	.byte $bf
@ref602:
	.byte $bf
@ref603:
	.byte $bf
@ref604:
	.byte $bf
@ref605:
	.byte $bf
@ref606:
	.byte $bf
@ref607:
	.byte $bf
@ref608:
	.byte $bf
@ref609:
	.byte $bf
@ref610:
	.byte $bf
@ref611:
	.byte $bf
@ref612:
	.byte $bf
@ref613:
	.byte $bf
@ref614:
	.byte $bf
@ref615:
	.byte $bf
@ref616:
	.byte $bf
@ref617:
	.byte $bf
@ref618:
	.byte $bf
@ref619:
	.byte $bf
@ref620:
	.byte $bf
@ref621:
	.byte $bf
@ref622:
	.byte $bf
@ref623:
	.byte $bf
@ref624:
	.byte $bf
@ref625:
	.byte $bf
@ref626:
	.byte $bf
@ref627:
	.byte $bf
@ref628:
	.byte $bf
@ref629:
	.byte $bf
@ref630:
	.byte $bf
@ref631:
	.byte $bf
@ref632:
	.byte $bf
@ref633:
	.byte $bf
@ref634:
	.byte $bf
@ref635:
	.byte $bf
@ref636:
	.byte $bf
@ref637:
	.byte $bf
@ref638:
	.byte $bf
@ref639:
	.byte $bf
	.byte $fd
	.word @song4ch4loop


@song5ch0:
	.byte $fb,$06
@song5ch0loop:
@ref640:
	.byte $84,$34,$f9,$83
	.byte $fd
	.word @song5ch0loop

@song5ch1:
@song5ch1loop:
@ref641:
	.byte $86,$3e,$85,$3e,$85,$3f,$3f,$42,$85,$42,$85,$43,$43,$44,$85,$44
	.byte $85,$45,$45,$42,$85,$42,$85,$3b,$3a,$a1
	.byte $fd
	.word @song5ch1loop

@song5ch2:
@song5ch2loop:
@ref642:
	.byte $80,$27,$27,$27,$27,$27,$27,$27,$27,$27,$27,$3f,$35,$2d,$2d,$2d
	.byte $2d,$2d,$2d,$2d,$2d,$2d,$2d,$45,$3a,$a1
	.byte $fd
	.word @song5ch2loop

@song5ch3:
@song5ch3loop:
@ref643:
	.byte $f9,$85
	.byte $fd
	.word @song5ch3loop

@song5ch4:
@song5ch4loop:
@ref644:
	.byte $f9,$85
	.byte $fd
	.word @song5ch4loop
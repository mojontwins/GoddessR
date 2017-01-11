'' Simple chr viewer 
'' Just throw a chr file on the exe, sit and watch.

#include "gui.bi"

Dim As Integer fIn, x, y, pattern, row, xx, yy, plane, x0, bank
Dim As uByte d 
Dim As uByte planes (1, 7)
Dim As Integer colours (3) = { &HFF000000, &HFF555555, &HFFAAAAAA, &HFFFFFFFF }

If Command (1) = "" Then ? "$ chrview tileset.chr": System

OpenWindow 256 + 8 + 256, 256, "chrview v0.1"

fIn = FreeFile
Open Command (1) For Binary As #fIn
If Lof (fIn) = 0 Then
	Close #fIn
	Kill Command (1)
	System
End If

x0 = 0
For bank = 0 To 1
	x = x0: y = 0

	For pattern = 0 To 255
		For plane = 0 To 1
			For row = 0 To 7
				Get #fIn, , planes (plane, row)
			Next row
		Next plane

		For yy = 0 To 7
			For xx = 0 To 7
				d = 0
				If planes (0, yy) And (1 Shl (7 - xx)) Then d = d + 1
				If planes (1, yy) And (1 Shl (7 - xx)) Then d = d + 2

				Line (x + xx + xx, y + yy + yy) - (1 + x + xx + xx, 1 + y + yy + yy), colours (d), B
			Next xx
		Next yy

		x = x + 16: If x = x0 + 256 Then x = x0: y = y + 16
	Next pattern

	x0 = x0 + 256 + 8
Next

Close #fIn

While Inkey = "": Wend

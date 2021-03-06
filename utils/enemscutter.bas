Sub usage
	Print "$ enemscutter in.ene out.ene x0 y0 w h"
	Print
	Print "    x0, y0       - First screen to process"
	Print "    w, h         - Output size"
End Sub

Dim As Integer fin, fout
Dim As Integer w, h, x0, y0, i, j
Dim As Integer map_w, map_h, scr_w, scr_h, nenems
Dim As uByte d

If Command (6) = "" Then 
	usage
	End
End If

fIn = FreeFile: Open Command (1) For Binary As #fIn
fOut = FreeFile: Open Command (2) For Binary As #fOut

x0 = Val (Command (3)): y0 = Val (Command (4))
w = Val (Command (5)): h = Val (Command (6))

' Read header

' Copy 256 bytes
For i = 1 To 256
	Get #fIn, , d
	Put #fOut, , d
Next i'

' mapw, maph, scrw, scrh, nenems
Get #fIn, , d: map_w = d: d = w: Put #fOut, , d
Get #fIn, , d: map_h = d: d = w: Put #fOut, , d
Get #fIn, , d: Put #fOut, , d
Get #fIn, , d: Put #fOut, , d
Get #fIn, , d: nenems = d: Put #fOut, , d

' Enemies. 8 bytes per enemy, nenems per screen

' Skip?
If y0 > 0 Then
	' Skip nenems * y0 * map_w enemies (8 bytes per enemy)
	For i = 1 To nenems * y0 * map_w * 8
		Get #fIn, , d
	Next i
End If

' Process
For j = 1 To h
	' Skip?
	If x0 > 0 Then
		' Skip nenems * x0 enemies (8 bytes per enemy)
		For i = 1 To nenems * x0 * 8
			Get #fIn, , d
		Next i
	End If

	' Copy nenems * w enemies (8 bytes per enemy)
	For i = 1 To nenems * w * 8
		Get #fIn, , d
		Put #fOut, , d 
	Next i

	' Skip?
	If x0 + w < map_w Then
		' Skip nenems * (map_w - (x0 + w)) enemies (8 bytes per enemy)
		For i = 1 To nenems * (map_w - (x0 + w)) * 8
			Get #fIn, , d
			Put #fOut, , d
		Next i
	End If
Next j

' Skip?
If y0 + h < map_h Then
	' Skip nenems * (map_h - (y0 + h)) * map_w enemies (8 bytes per enemy)
	For i = 1 To nenems * (map_h - (y0 + h)) * map_w * 8
		Get #fIn, , d 
	Next i
End If

' Hotspots, 3 bytes per hotspot, 1 per screen

' Skip ? 
If y0 > 0 Then
	' Skip y0 * map_w hotspots (3 bytes per hotspot)
	For i = 1 To y0 * map_w * 3
		Get #fIn, , d 
	Next i
End If

For j = 1 To h
	' Skip?
	If x0 > 0 Then
		' Skip x0 hotspots (3 bytes per hotspot)
		For i = 1 To x0 * 3
			Get #fIn, , d
		Next i
	End If

	' Copy w hotspots (3 bytes per hotspot)
	For i = 1 To w * 3
		Get #fIn, , d
		Put #fOut, , d
	Next i

	' Skip?
	If x0 + w < map_w Then
		' Skip mapw - (x0 + w) hotspots (3 bytes per hotspot)
		For i = 1 To (map_w - (x0 + w)) * 3
			Get #fIn, , d
		Next i
	End If
Next j

Close

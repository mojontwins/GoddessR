' MAPCNV NES
' Converts a Mappy layer to a suitable-scrollable, Churrera-NES map.
'
' Format is:
' Map is divided in "MapChunks". 
' Each MapChunk is 24 bytes:
'
' 0001  
' 0203  
' 0405 
' 0607  
' 0809  
' 0A0B  
' 0C0D  
' 0E0F  
' 1011  
' 1213  
' 1415
' 1617

Type BOLT
	x as Integer
	y as Integer
End Type

Type OBJ
	x as integer
	y as integer
	t as integer
end type

Dim As Integer x, y, xx, yy, f1, f2, i, j, k
Dim As Integer wt, hs, rhs, rws
Dim As String mapFileName, palString, o
Dim As uByte orgMap(512, 512), d, by
Dim As uByte pal(127)
Dim As BOLT bolts(10,512)
Dim As OBJ objs(10,512)

If Val(Command(3)) = 0 Or Val(Command(4))=0 Or Command (7) ="" Then
	Print "mapcnvnes mapa.MAP mapa.h w_t h_s prefix pallist.txt precalcs.h"
	Print "   w_t: Width in tiles."
	Print "   h_s: Height in stripes."
	Print "Produces map.bin and map.h"
	System
End If

Print "mapcnvnes is converting " & Command (1);

for y = 0 to 10: for x = 0 To 512
	objs(y,x).x=255
	bolts(y,x).x=255
	objs(y,x).y=255
	bolts(y,x).y=255
next x: next y

' Read pal
f1 = FreeFile
Open Command (6) For Input as #f1
	Line Input #f1, palString
	For i = 1 To Len(palString)
		pal (i-1) = val (Mid (palString, i, 1))
	Next i
Close #f1

	f1 = FreeFile
	Open Command (7) For Output As #f1
	Print #f1, "const unsigned char precalc_attr_bits [] = {"
	For i = 0 To Len (palString) - 1 Step 16
		For j = 0 To 3
			Print #f1, "	";
			For k = 0 To 15
				Print #f1, "0x" & Hex (pal (i + k) Shl (j + j), 2);
				If k < 15 Or j < 3 Or i < (Len (palString) - 16) Then
					Print #f1, ", ";
				End If
			Next k
			Print #f1, ""
		Next j
	Next i
	Print #f1, "};"
	Close #f1

mapFileName = Command(1)
wt = Val (Command(3)) - 1
hs = Val (Command(4)) - 1
rhs = (12 * Val (Command(4))) - 1

f1 = FreeFile
Open mapFileName For Binary as #f1

' First read map
For y = 0 to rhs
	For x = 0 To wt
		Get #f1, , d
		orgMap (y, x) = d-1
	
	Next x
Next y

Close #f1

f2 = FreeFile
Open Command (2) For Output as #f2

Print #f2, "// Chunky map extracted from " & Command (1)
Print #f2, "// Copyleft 2017 The Mojon Twins"
Print #f2, ""
Print #f2, "const unsigned char map_" & Command (5) & " [] = {"

For y = 0 to hs

	For x = 0 To wt Step 2
		Print #f2, "	";
		For yy = 0 To 11
			' Column 1
			d = orgMap (12 * y + yy, x) 
			Print #f2, "0x" & Lcase (Hex (d, 2)) & ", ";
		
			' Column 2
			d = orgMap (12 * y + yy, x + 1)
			Print #f2, "0x" & Lcase (Hex (d, 2));
			If x < wt - 1 Or yy < 11 Or y < hs Then Print #f2, ", ";
		Next yy
		Print #f2, ""
	Next x

Next y

Print #f2, "};"
Close #f2

Close #f1

? " " & (hs+1)*(wt+1)*12 & " bytes written."

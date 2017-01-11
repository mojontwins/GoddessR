' mappedchunkermap.bas
' I'm running out of names!

#include "cmdlineparser.bi"
#include "mtparser.bi"

Sub usage () 
	Print "$ mappedchunkermap.exe in=mapa.map out=mapa.h smts=smts.h mapsize=w,h prefix=prefix"
	Print
	Print "Opens 'in', writes converted chunked map in 'out', and the supermetatileset to 'smts'."
	Print "Uses 'prefix' for everything. mapsize is in tiles."
End Sub

Dim As String mandatory (4) = { "in", "out", "smts", "mapsize", "prefix" }
Dim As Integer fIn, fOut
Dim As Integer mapWtiles, mapHtiles, mapWchunks, mapHstrips, stripHchunks
Dim As Integer coords (10)
Redim As Integer mapTiles (0, 0)
Redim As Integer mapSMT (0, 0)
Dim As Integer x, y, j, curSmt
Dim As uByte d
Dim As String smtsPoolS (255)
Dim As Integer smtsPoolI
Dim As String curSmtS

Print "mappedchunkermap v0.1"
Print

sclpParseAttrs

If Not sclpCheck (mandatory ()) Then usage: End

' Some calculations
parseCoordinatesString (sclpGetValue ("mapsize"), coords ())
mapWtiles = coords (0)
mapHtiles = coords (1)
stripHchunks = 6
mapWchunks = mapWtiles / 2
mapHstrips = mapHtiles / 12

Redim mapTiles (mapHtiles - 1, mapWtiles - 1)
Redim mapSMT (mapHtiles \ 2 - 1, mapWtiles \ 2 - 1)

Print "Map size = " & mapWtiles & "x" & mapHtiles & ", strips = " & mapHstrips & ", map width in chunks = " & mapWchunks

fIn = Freefile
Open sclpGetValue ("in") For Binary As #fIn

Print "Reading the whole map . . . ";
For y = 0 To mapHtiles - 1
	For x = 0 To mapWtiles - 1
		get #fIn, , d
		mapTiles (y, x) = d
	Next x
Next y
Print "read " & mapHtiles * mapWtiles & " bytes"

Close

Print "Collecting supermetatiles . . . ";

smtsPoolI = 0
For y = 0 To mapHtiles \ 2 - 1
	For x = 0 To mapWtiles \ 2 - 1
		' Build metatile
		curSmtS = _
			Hex (mapTiles (y + y, x + x), 2) & _
			Hex (mapTiles (y + y, x + x + 1), 2) & _
			Hex (mapTiles (y + y + 1, x + x), 2) & _
			Hex (mapTiles (y + y + 1, x + x + 1), 2)

		? curSmtS & " " & smtsPoolI & " " & x & "," & y

		' Find in pool
		curSmt = smtsPoolI
		For j = 0 To smtsPoolI - 1
			If smtsPoolS (j) = curSmtS then curSmt = j: Exit For
		Next j

		' If not found, add to pool'
		If curSmt = smtsPoolI Then 
			smtsPoolS (smtsPoolI) = curSmtS
			smtsPoolI = smtsPoolI + 1
		End If

		' Write chunk in map
		mapSMT (y, x) = curSmt
	Next x
Next y
Print "collected " & smtsPoolI & " sumermetatiles"

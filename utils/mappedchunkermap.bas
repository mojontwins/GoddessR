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

Print "Map size = " & mapWtiles & "x" & mapHtiles & ", strips = " & mapHstrips & ", map width in chunks = " & mapWchunks

fIn = Freefile
Open sclpGetValue ("in") For Binary As #fIn



Close

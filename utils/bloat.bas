' Bloat.bas
' Adds tons of zeroes

#include "cmdlineparser.bi"
#include "mtparser.bi"

Sub usage
	Print "bloat in=filein.bin out=fileout.bin maxsize=N [leading=M]"
End Sub

Dim As String mandatory (2) = { "in", "out", "maxsize" }
Dim As Integer leading, maxsize, i
Dim As Integer fIn, fOut 
Dim As uByte d

sclpParseAttrs
If Not sclpCheck (mandatory ()) Then usage: End

Print "Bloating " & sclpGetValue ("in") & " into " & sclpGetValue ("out") & ", size = " & sclpGetValue ("maxsize");

maxsize = Val (sclpGetValue ("maxsize"))
If leading > maxsize Then leading = maxsize

leading = Val (sclpGetValue ("leading"))
If leading > 0 Then 	
	Print " with " & sclpGetValue ("leading") & " zeroes."; 
Else 
	leading = 0 ' safe
End If


fIn = FreeFile
Open sclpGetValue ("in") For Binary As #fIn
fOut = FreeFile
Open sclpGetValue ("out") For Binary As #fOut

d = 0
If leading Then
	For i = 1 To leading
		Put #fOut, , d 
	Next i 
End If

For i = leading + 1 To maxsize
	If Not Eof (fIn) Then Get #fIn, , d Else d = 0
	Put #fOut, , d
Next i

Close

Print " DONE"

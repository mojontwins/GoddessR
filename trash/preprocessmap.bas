' Simple map preprocessor
' adds in missing stuff to the original map

' I'm the only who's always in the need of stuff like this.
' This happens 'cause I abandon nice projects, months pass, then I start over.
' And stuff needs updating

Const mapW = 320
Const mapH = 48
Const scrW = 16
Const scrH = 12

Dim As Integer fIn, fOut, x, y, nPant, xPant, yPant, mapWscr, level
Dim As uByte d, rda
Dim As uByte mapBuff (mapH - 1, mapW - 1)

mapWscr = mapW \ scrW

Print "opening orig.MAP"

fIn = FreeFile
Open "orig.MAP" For Binary As #fIn

Print "opening mapa.MAP"

fOut = FreeFile
Open "mapa.MAP" For Binary As #fOut

For y = 0 To mapH - 1
	For x = 0 To mapW - 1
		xPant = x \ scrW
		yPant = y \ scrH
		nPant = yPant * mapWscr + xPant

		level = (nPant = 0 Or nPant = 60 Or (nPant >= 57 And nPant <= 59) Or (nPant >= 76 And nPant < 79))

		Get #fIn, , d
		d = d - 1

		If d = 0 then
			rda = Int (rnd * 256)
			If level then
				If (rda And 31) = 1 Then 
					d = 45 + (Int (Rnd * 256) And 1)
				Else
					d = 44
				End If
			Else
				If (rda And 15) < 7 Then
					d = 40 + ((x + y + y) And 3)
				End If
			End If
		ElseIf d = 10 Then
			If mapBuff (y - 1, x) <> 10 Then d = 16
		End If

		mapBuff (y, x) = d

		d = d + 1
		Put #fOut, , d
	Next x
Next y

Print "closing"
Close

Print "DONE"

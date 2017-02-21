Dim As Integer subs (255), i, from, toc
Dim As uByte d

If Command (3) = "" Then
	Print "$ binsubstitutor.exe subs.txt filein.bin fileout.bin"
	Print "subs.txt contains a pair source,destination per line"
	System 
End If

' First
For i = 0 To 255: subs (i) = i: Next i

' Parse
Open Command (1) For Input As #1
While Not Eof (1)
	Input #1, from
	Input #1, toc
	subs (from) = toc
	Print "byte " & from & " to be substituted by " & toc
Wend
Close

Open Command (2) For Binary As #2
Open Command (3) For Binary As #3

While Not Eof (2)
	Get #2, , d
	d = subs (d)
	Put #3, , d
Wend

Close

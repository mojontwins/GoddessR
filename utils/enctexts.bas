' Encodes texts in a file based upon a tbl file

Dim Shared As Integer corrspVal (255)

Sub readAndParseTbl (fileName As String)
	Dim As Integer fIn
	Dim As String l
	Dim As Integer value, divider
	Dim As String character

	fIn = FreeFile
	Open fileName For Input As #fIn
	While Not Eof (fIn)
		Line Input #fIn, l
		divider = Instr	(l, "=")
		If divider > 0 Then 
			value = Val ("&H" & Left (l, divider - 1))
			character = Right (l, 1)
			corrspVal (Asc (character)) = value
		End If
	Wend
	Close fIn
End Sub

Sub usage
	Print "EncodeTexts v0.1"
	Print "Encodes a txt file upon a tbl file"
	Print
	Print "$ enctexts.exe input.txt table.tbl prefix output.h [index]"
	Print
	Print "Code in output.h is directly usable, uses 'prefix' for variable names."
	Print "'index' will generate a constant array with the pointers."
End Sub

Sub addComment (fH As Integer, s As String)
	Dim As Integer i, nothing
	Dim As String m
	nothing = -1
	For i = 1 To Len (s)
		m = Mid (s, i, 1)
		If nothing Then Print #fH, "": Print #fH, "// "; : nothing = 0
		If m = "%" Then 
			nothing = -1: Print #fH, "[NEWLINE]";
		ElseIf m = "/" Then
			nothing = -1: Print #fH, "": Print #fH, "// [NEWPAGE]";
		Else
			Print #fH, m;
		End If
	Next i
	Print #fH, ""
End Sub

Dim As Integer fIn, fOut, i, lc, byteCount
Dim As String textLine

If Command (4) = "" Then usage: End

If Command (2) = "ASCII" Then
	For i = 0 To 255: corrspVal (i) = i: Next i
	corrspVal (asc ("%")) = 1
	corrspVal (asc ("/")) = 2
ElseIf Command (2) = "BASE" Then
	For i = 32 To 95: corrspVal (i) = i - 32: Next i
	corrspVal (asc ("%")) = 1
	corrspVal (asc ("/")) = 2
	corrspVal (32) = 63
Else
	readAndParseTbl Command (2)
End If

? "enctexts - ";

fIn = FreeFile
Open Command (1) For Input As #fIn
fOut = FreeFile
Open Command (4) For Output As #fOut

Print #fOut, "// " & Command (4) & " - encoded texts. Generated by enctexts.exe"
Print #fOut, "// Copyleft 2016 by The Mojon Twins"

lc = 0: byteCount = 0
While Not Eof (fIn)
	Line Input #fIn, textLine
	addComment (fOut, textLine)
	Print #fOut, "const unsigned char " & Command (3) & "_" & Lcase (Hex (lc, 2)) & " [] = {"
	Print #fOut, "	";
	For i = 1 To Len (textLine) 
		Print #fOut, "0x" & Lcase (Hex (corrspVal (Asc (Mid (textLine, i, 1))), 2)); ", ";
		byteCount = byteCount + 1
		If Mid (textLine, i, 1) = "%" Then Print #fOut, "": Print #fOut, "	";
		If Mid (textLine, i, 1) = "/" Then Print #fOut, "": Print #fOut, "	// []": Print #fOut, "	";
	Next i
	Print #fOut, "0"
	byteCount = byteCount + 1
	Print #fOut, "};"
	lc = lc + 1
Wend

If Command (5) = "index" Then
	Print #fOut, ""
	Print #fOut, "const unsigned char * const " & Command (3) & "_index [] = {"
	Print #fOut, "	";
	For i = 0 To lc - 1
		Print #fOut, Command (3) & "_" & Lcase (Hex (i, 2));
		If i < lc - 1 Then Print #fOut, ", ";
	Next i
	Print #fOut, ""
	Print #fOut, "};"
End If

Close #fIn, #fOut

? "DONE! " & byteCount & " bytes."

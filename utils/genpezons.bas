Dim As Integer enf_y, enf_vy, en_y, en_y_old, steps
Dim As String incs, coor
Print "precalculating pezon."
Print "original uses (-)8.6 fixed point math."

enf_y = 240 Shl 6
enf_vy = -384 ' PEZON_THRUST

en_y_old = enf_y Shr 6
steps = 0
incs = "": coor = ""
Do
	enf_vy += 16  ' PEZON_G
	if enf_vy >= 256 Then enf_vy = 256 ' PEZON_FALLING_MAX
	enf_y = enf_y + enf_vy
	en_y = enf_y Shr 6
	incs = incs & (en_y - en_y_old) & ", "
	coor = coor & en_y & ", "
	en_y_old = en_y
	steps = steps + 1
Loop Until en_y >= 240
Print: Print "Steps = " & steps
Print "incs [] = {" & Left (incs, Len (incs) - 2) & "};"
Print "coor [] = {" & Left (coor, Len (coor) - 2) & "};"

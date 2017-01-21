Dim As Integer enf_x, enf_vx, en_x, en_x_old, steps
Dim As String incs, coor, spee

Const FANTY_A As Integer = 4
Const FANTY_MAXV As Integer = 64

Print "precalculation fanty acceleration cycle"
Print "original uses (-)8.6 fixed point math."

enf_x = 0
enf_vx = 0
en_x_old = 0

While enf_vx < FANTY_MAXV
	enf_vx = enf_vx + FANTY_A
	enf_x = enf_x + enf_vx
	en_x = enf_x Shr 6

	incs = incs & (en_x - en_x_old) & ", "
	coor = coor & en_x & ", "
	spee = spee & enf_vx & ", "
	en_x_old = en_x
	steps = steps + 1
Wend
Print: Print "Steps = " & steps
Print "incs [] = {" & Left (incs, Len (incs) - 2) & "};"
Print "coor [] = {" & Left (coor, Len (coor) - 2) & "};"
Print "spee [] = {" & Left (spee, Len (spee) - 2) & "};"

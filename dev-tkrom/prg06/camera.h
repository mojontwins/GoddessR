// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Camera control

void camera_do (void) {
	cam_pos = px_world - 120;
	if (cam_pos < section_x0) cam_pos = section_x0;
	if (cam_pos > section_x1) cam_pos = section_x1;

	cam_pos_pant = (MSB (cam_pos)) & 1;
	cam_pos_mod = LSB (cam_pos);
}

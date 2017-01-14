20170111
========

Voy a divagar un momento.

Esto es una locura. Faltan 20 días para que termine el concurso de nesdev y se me ha ocurrido hacer un remake del abandonado Cheril the Goddes pero usando scroll. Necesito rehacer todos los sprites y montar un proyecto nuevo con un montón de cosas que aún no he probado. Además tengo que integrar la cantidad de cosas chulas que tenía el original: portales, objetos, chac-chacs...

El tema está en que el juego siga 100% orientado a pantallas, pero que se muestre con scroll. Esto implica tener un scroller para ir mostrando nuevo contenido, además de manejar dos pantallas de enemigos a la vez. La idea es que sea lo más sencillo posible.

Si la pantalla de scroll siempre está alineada a pantalla HW, modificar el contenido debería ser trivial. Sólo tendría que tener en cuenta dónde estoy. Lo digo porque los chac-chacs se hacen pintando tiles. Esto es muy importante. 

El motor debería poder empezar en cualquier sitio del mapa, pero siempre alineado a pantalla. Esto es MUY importante. Si se dice que tengo que empezar en X = n, tengo que empezar realmente al principio de la pantalla que contenga a X.

Si siempre llevo sincronía entre scroll y pantallas, puedo usar el motor de movimiento tal cual con prx y pry como bytes, y px un signed char normal que sólo pueda tomar valores hasta 4096. Así no importa que el mapa tenga 20 pantallas de ancho. Para las colisiones con los malos tengo que idear una estrategia para:

1.- Sólo tener en cuenta los 3 de la pantalla donde está Cheril. Por tanto tengo que llevar un registro de en qué pantalla estoy, y actualizarlo siempre que px se reinicie al llegar a uno u otro bordes.
2.- Si se está en la misma pantalla, las coordenadas "x" reales son más que suficientes.

El problema, si quiero usar bytes para las coordenadas de los malos, es cómo pintarlos en la pantalla con desplazamiento ajustados al offset de la cámara. Creo que ahora voy a coger el cuaderno y a hacer un par de dibujitos a ver si me aclaro.

~~

Creo que lo tengo (y me valdrá también para los enemigos de Yun en SMS):

El quid está en dividir los enemigos por pantalla. Estaré procesando 6 enemigos. Los 3 primeros siempre están en la pantalla de la izquierda, y los 3 últimos en la de la derecha.

Se entiendeo que cam_x_module es la parte LSB de cam_x (o sea, cam_x & 0xff).

Para los 3 primeros, en la pantalla de la izquierda:
	- Si en_x < cam_x_module -> NO
	- Si en_x >= cam_x_module -> SI

	spr_x = en_x - cam_x_module;

Para los 3 últimos, en la pantalla de la derecha:
	- Si en_x <= cam_x_module - 16 -> SI
	- Si en_x > cam_x_module - 16 -> NO

	spr_x = 256 - cam_x_module + en_x

Lo dejo aquí apuntadico.

~~

El scroller puede basarse en el de pongpong. Veré cómo generalizarlo bien. El tema es pintar una columna siempre en el borde al que se esté avanzando. En la función scroll_to se mira si el desplazamiento de cam_pos respecto del valor anterior es hacia la izquierda o hacia la derecha y se pinta la columna no visible (-1 o +9, si hablamos de chunks de 32).

El problema en NES son los atributos, que hay que calcular y enviar. Teniendo una columna "en el horizonte", hay 32 pixels de scroll de tiempo para tener la siguiente lista. 

He mirado y en el original, Cheril corre como máximo a 2 pixels por frame, pero cuando es diosa va a 4. 32 / 4 = 8 frames para dibujar la columna completa; estamos hablando de 4 columnas de 24 patrones cada una más una ristra de 6 atributos.

Podrá ser así:

1 frame para calcular atributos.
1 frame para escribir 6 bytes de atributos.
6 frames para 24x4 patrones = 16 patrones en cada frame, o lo que es lo mismo, un chunk de 4x4 patrones.

Ahora se me pasa por la cabeza que si pudiese procesar el mapa en chunks de 4x4 el scroller sería de los cojones de sencillo, pero no sé si saldrían demasiados metatiles y ocuparían un huevo. ¡No tengo más que escribir un conversor para comprobarlo!

Ya tengo algo divertido que hacer para luego.

~~~~

Antes de escribir nada, he pensado en una forma mucho mejor para almacenar metatiles, sus atributos, y luego los supermetatiles (por llamarles de alguna forma): en vez de intercalar los datos, lo cual es muy humano, los desintercalaré (deinterlace queda más chulo) y los separaré en cuatro arrays de patrones y una quinta de atributos. Así imprimir será mucho más rápido porque no tendré que andar buscando un puntero multiplicando por 4 y avanzándolo luego. Como de todos modos lo hago desenrollado, todo son ganancias. Voy a añadir la funcionalidad a mkts (el enjendro).

~~

mkts.exe está modificado para el parámetro deinterlace en todos los targets (aunque el scripting de SMS es algo que aún tengo que probar... Cuando llegue el momento ~ quizá deba escribir scripts para toda la conversión que se hace en yun pero ya). Ahora tengo que hacer el exporter del mapa. Lo malo es que lo chulo del mapa eran las estrellicas y las estrellicas se ponían a vuelo. Voy a pensar en qué hacer. Primero de todo, la forma de modificar el mapa en tiempo real era que, al ir a imprimir el tile "t"...

	if (t == 0) {
		rda = rand8 ();
		if (level) {
			t = (rda & 31) == 1 ? t = 45 + (rand8 () & 1) : 44;
		} else {
			if ((rda & 15) < 7) t = 40 + ((n_pant + rdx + rdy + rdy) & 3);
		}
	} else if (t == 10) {
		if (map_buff [rda - 16] != 10) t = 16;
	}

"level" se calcula así:

	level = (n_pant == 0 || n_pant == 60 || 
		(n_pant >= 57 && n_pant <= 59) ||
		(n_pant >= 76 && n_pant <= 79) );

Voy a necesitar un preprocesador del .map de entrada para introducir todos esos cambios. También tengo que introducir el offset, eso lo puedo hacer de entrada, y deshacerlo en el conversor, que es lo suyo. Nada de cuadrados negros como primer tile, qué atraso.

~~

Por cierto, que se me olvidaba: Esto va a ser UNROM de 64K, necesito 16K solo para level data (mapa y tablas de metatiles, tiles, y dátiles).

~~

Voy a por el conversor del mapa. Tiene que exportar chunks de supermetatiles y luego un índice de dichos supermetatiles. Y por tiras. Va a ser diver diver y no me va a dar tiempo, pero al menos lo planteow.

~~

Nah. La idea parecía buena pero para este mapa no parece que sirva. Voy por la cuarta fila de supermetatiles (¡y son 24!) y ya hay más de 256 bloques diferentes, con lo que la idea se va al pedus. A cascal, por tiles. Ocupa un egg, pero bueno. Tengo 16K solo para este mapaco. Uso el colsmapper que tenía para Yun y a cascal. CASCAL!

Veamos, hay 56 metatiles; 56x5 = 280 bytes. El mapa columnado ocupa 320x48 = 15360. O sea, que ambas cosas me caben en la misma página. Eso está BIEN. Cuando tenga que escrollear, la pongo, hago fullerías, y la quito. Como mola UNROM.

Para ir teniendo cosas, voy a ir haciendo el compile.bat y que vaya guardando cosas en sitios. Por ejemplo, todo esto puede ir en PRG0. En PRG1 puedo meter gráficos y músicas. En PRG2/PRG3, el motor. Por ir empezando.

~~

Bueno, ya tengo todos los tiestos convertidos. Ahora voy a trasladar enemigos y tal. Supongo y espero que todos los datos de la tira actual me quepan en RAM. Cuando tenga todo dentro monto el esqueleto y me pongo a hacer el nuevo scroller.

Hum. No hago más que dudar sobre el scroller y si no me cogerá el toro. Hay que tener en cuenta que puede ir para ambos lados y que un cambio brusco puede ser heavy.

DA+-------------+BC

O no, es el comecocos de siempre. Por lo general se van a ver 9 chunks, con un cachito de B. Nada más andar a la derecha se empieza a pintar el décimo, que es C, y nada más andar a la izquierda se pintará el menos dos, o sea, D. Si al empezar A y B están pintados da igual adonde vayamos que dará tiempo a que esté la nueva columna antes de llegar. Lo que estoy viendo es que a lo mejor me va a venir mejor guardar el mapa de otra forma, por cachos de 4x4, que son los que actualizaré cada frame, para así sólo tener que incrementar el puntero para el siguiente mientras estoy pintando la columna... aunque la copia a VRAM esta optimizada para columnas. No sé qué hacer, probaré tal y como tenía planteado a ver si va bien de tiempo.

el motor de pongpong no se raya un carajo y va pintando una nueva columna de patrones SIEMPRE que se cambia la posición de la cámara. Lo hace en el chunk de la izquierda o de la derecha sin pensárselo, ciclando el contador de estados del pintador de columnas continuamente. No parece cogerle el toro, pero tiene siempre todo pintado en 5 ciclos y Lin Lin creo que nunca se mueve a mas de 2 pixels por frame.

Veamos, vamos a poner supuestos.

1. Empezamos y nos movemos a 4ppf (velocidad máxima de volar) a la izquierda durante 8 frames, o sea, -32 pixels. Al final de ese desplazamiento, A estará dentro del area visible fuera pero D estará dibujad completamente. OK.

2. Empezamos y nos movemos a 4ppf a la derecha. A los 8 frames lo mismo, B estará dentro entero pero C estará completamente dibujado.

3. Empezamos y nos movemos a 4pff, primero 4 frames a la derecha y luego paramos. B se verá a la mitad, y de C tendremos pintados atributos y dos chunks de los 6. Entonces nos movemos 4 frames a la izquierda: se pintarán en D los 4 últimos chunks, y desaparecera B. tendríamos 8 frames para que tuviese que aparecer D y ya estaría completamente dibujado.

No paro de cambiar de idea. Pintar un chunk de 4x4 patrones implicaría una actualización de (3+4)*4 bytes, o sea, 28 bytes por frame. Pintar una columna de 16 patrones solo necesitaría 19 bytes o 22, de forma alterna, lo que sería un poco raro.

Nada, lo de siempre, hasta que no me ponga no lo sabré. Pero igualmente para ver todas estas mierdas necesito un exporter que me saque el mapa en chunks de 2x2 metatiles en vez de columnas. Bueno, en columnas de chunks. O sea, lo que tenía más o menos en pongpong pero que saque bytes y que tenga columnas de 12 de alto. Lo puedo modificar a partir de ahí para máxima velocidad.

00
11
22
33
44
55
66
77
88
99
AA
BB

Tambien podría probar la forma más sencilla que sería hacer más o menos como Pong Pong pero con la ventaja de que no hay que decodificar los bytes del mapa y que los metatiles están desintercalados.

En ese caso tendría 5 ciclos de pintado:

- 4 ciclos que pintan una columna de 24 patrones (27 bytes).
- 1 ciclo de cálculo de atributos y escritura (18 bytes).

Hm. Sólo gano 1 byte de actualización por frame y necesito leer y mandar al buffer más patrones (24 vs 16).

Creo que me quedo con el plan original pero tendré que modificar el exporter del mapa.

Conversor chunky hecho y funcionando. Esquema del programa con UNROM montado. A medida que añado cosas las voy metiendo en compile.bat. Todas las cosas que ya tengo ya están en sus PRGn correspondientes.

20170112
========

Hoy he estado a otras cosas, pero voy a apuntar unos cuantos hechos que me servirán para simplificarlo todo.

- Siempre estamos alineados a pantallas.
- La columna "chunk" de scroll #0 está en X=0 de NAMETABLE_A. Todos los cálculos tienen eso en cuenta.
- A la hora de pintar el chunk N se he hace "& 0xf" al número obtenido de cam_pos. En el esquema de antes, "A" es ((cam_pos >> 5) - 1) & 0xf.
- Si el bit 3 de "chunk N" es 0, está en NAMETABLE_A. Si es 1, en NAMETABLE_B.
- A la hora de actualizar cosas en la pantalla (por ejemplo, chack chacks): n_pant & 1 ? NAMETABLE_B : NAMETABLE_A
- Actualizamos levemente los cálculos de pongpong

	// Calculate memory address of current column [col_idx * 24]
	gpint = col_idx << 2;
	// 24 = 12 * 2 = (4*3)*2
	col_ptr = map_ptr + ((gpint + gpint + gpint) << 1);

	// VRAM address
	rdc = gpint & 31;

	// which nametable?
	if (col_idx & 8) {
		col_adr = NAMETABLE_B + (TOP_ADJUST << 5) + rdc;
		col_attr_adr = NAMETABLE_B + ((TOP_ADJUST >> 2) << 3) + 0x03c0 + (rdc >> 2);
	} else {
		col_adr = NAMETABLE_A + (TOP_ADJUST << 5) + rdc;
		col_attr_adr = NAMETABLE_A + ((TOP_ADJUST >> 2) << 3) + 0x03c0 + (rdc >> 2);
	}

Parece que no pero me he quitado de enmedio unos cuantos desplazamientos de 16 bits. Además, TOP_ADJUST será 0, otra cosa que me ahorro. Y atención qué tontería cómo calculo la dirección de los atributos. ¿Cómo no me he dado cuenta de esto antes?

	// Calculate memory address of current column [col_idx * 24]
	gpint = col_idx << 2;
	// 24 = 12 * 2 = (4*3)*2
	col_ptr = map_ptr + ((gpint + gpint + gpint) << 1);

	// VRAM address
	rdc = gpint & 31;

	// which nametable?
	if (col_idx & 8) {
		col_adr = NAMETABLE_B + rdc;
		col_attr_adr = NAMETABLE_B + 0x03c0 + (col_idx & 0x7);
	} else {
		col_adr = NAMETABLE_A + rdc;
		col_attr_adr = NAMETABLE_A + 0x03c0 + (col_idx & 0x7);
	}

Mecano y me queda. Refollúo, he ahorrado un montón sobre pongpong. Y con la organización de los metatiles, más [en realidad esto no es del todo correcto - pongpong no usa metatiles mapeados, sino compuestos por patrones sucesivos; con la nueva organización podré tener el lujo de los metatiles mapeados sin impacto].

Hemos dicho que en los seis primeros tiempos (por ejemplo) pintaremos 6 cachos de 4x4 patrones. El offset vertical debería ir en una variable aparte y ciclarse así tras pintar cada cacho.

	col_v_offset += 128;
	if (col_v_offset == 768) col_v_offset = 0;

O mejor, col_v_offset se incrementa en 32 tras cada 4 patrones en linea. La linea de comprobación final tampoco sería necesaria: en el tiempo 7, al calcular los atributos, puede ponerse a 0 sin problema.

Para simplificar la inicialización, lo haremos al revés: primero atributos y luego patrones.

~~

20170113
========

Hoy me he casao así que no me da mucho tiempo de nada, pero quiero apuntar esto: es una tontería, en la parte de calcular los atributos, tener todo el lookup junto y tener que acceder sumando y hostias. Como en el resto de las cosas: 4 arrays separados y tal. Tengo, por tanto, que modificar el exportador para que me genere los datos guay.

Yo tengo que exportar arrays para estos cuatro tiles:

A B 
C D

Que además es el orden de los colores en el atributo, así que genial.

~~

Al final del día he escrito la función que pinta un chunk y que utilizaré para scrollear. Ha quedado así tras algun afeite más:

void scroll_paint_chunk (void) {
	// Calculate memory address of current column [col_idx * 24]
	gpint = col_idx << 2;
	// 24 = 12 * 2 = (4*3)*2
	col_ptr = map_ptr + ((gpint + gpint + gpint) << 1);

	// VRAM address
	rdc = gpint & 31;

	if (!state_ctr) {
		// State 0: fetch & paint attrs.
	
		// which nametable?
		gp_addr = ((col_idx & 8) ? NAMETABLE_B : NAMETABLE_A) + 0x03c0 + (col_idx & 0x7);
		gp_gen = (unsigned char *) col_ptr;

		gpit = 6; while (gpit --) {
			rda = *gp_gen ++;
			rdt = attr_lookup_0_0 [rda];
			rda = *gp_gen ++;
			rdt += attr_lookup_0_1 [rda];
			rda = *gp_gen ++;
			rdt += attr_lookup_0_2 [rda];
			rda = *gp_gen ++;
			rdt += attr_lookup_0_3 [rda];
			*gp_ul ++ = MSB (gp_addr);
			*gp_ul ++ = LSB (gp_addr);
			*gp_ul ++= rdt;
			gp_addr += 8;
		}

		col_v_offset = 0;
	} else if (state_ctr < 7) {
		// State 1..6: draw patterns. 4x4 chunk

		// which nametable?
		gp_addr = ((col_idx & 8) ? NAMETABLE_B : NAMETABLE_A) + rdc + col_v_offset;
		gp_gen = (unsigned char *) (col_ptr + (state_ctr << 2) - 4);
		
		// Two metatiles
		rda = *gp_gen ++; rdb = *gp_gen ++;
		
		*gp_ul ++ = MSB (gp_addr) | NT_UPD_HORZ;
		*gp_ul ++ = LSB (gp_addr);
		*gp_ul ++ = 4;
		*gp_ul ++ = main_ts_tmaps_0 [rda];
		*gp_ul ++ = main_ts_tmaps_1 [rda];
		*gp_ul ++ = main_ts_tmaps_0 [rdb];
		*gp_ul ++ = main_ts_tmaps_1 [rdb];
		
		gp_addr += 32;

		*gp_ul ++ = MSB (gp_addr) | NT_UPD_HORZ;
		*gp_ul ++ = LSB (gp_addr);
		*gp_ul ++ = 4;
		*gp_ul ++ = main_ts_tmaps_2 [rda];
		*gp_ul ++ = main_ts_tmaps_3 [rda];
		*gp_ul ++ = main_ts_tmaps_2 [rdb];
		*gp_ul ++ = main_ts_tmaps_3 [rdb];

		gp_addr += 32;

		// Two metatiles more
		rda = *gp_gen ++; rdb = *gp_gen ++;
		
		*gp_ul ++ = MSB (gp_addr) | NT_UPD_HORZ;
		*gp_ul ++ = LSB (gp_addr);
		*gp_ul ++ = 4;
		*gp_ul ++ = main_ts_tmaps_0 [rda];
		*gp_ul ++ = main_ts_tmaps_1 [rda];
		*gp_ul ++ = main_ts_tmaps_0 [rdb];
		*gp_ul ++ = main_ts_tmaps_1 [rdb];
		
		gp_addr += 32;

		*gp_ul ++ = MSB (gp_addr) | NT_UPD_HORZ;
		*gp_ul ++ = LSB (gp_addr);
		*gp_ul ++ = 4;
		*gp_ul ++ = main_ts_tmaps_2 [rda];
		*gp_ul ++ = main_ts_tmaps_3 [rda];
		*gp_ul ++ = main_ts_tmaps_2 [rdb];
		*gp_ul ++ = main_ts_tmaps_3 [rdb];

		// Next chunk at
		col_v_offset += 128;		
	} else {
		// State 7: extra painting?
		// It may be necessary for custom stuff in this game.
		// Open / closed gates for instance.
	}

	state_ctr = (state_ctr + 1) & 7;
}
Bella, bella cual culo de un camella. Ya la probaré. Pero seguro que ocupa menos rasters que la original ¡y hace bastante más!

Además me ha sobrado un estado, el 7º, para cosas especiales que pueda necesitar, como por ejemplo pintar modificaciones al mapa (puerta abierta, cancelas del final).

~~

Para ponerme cojonudo:

	*gp_ul ++ = main_ts_tmaps_0 [rda];

Genera:

	lda     _gp_ul
	ldx     _gp_ul+1
	sta     regsave
	stx     regsave+1
	clc
	adc     #$01
	bcc     L4463
	inx
L4463:	sta     _gp_ul
	stx     _gp_ul+1
	ldy     _rda
	lda     _main_ts_tmaps_0,y
	ldy     #$00
	sta     (regsave),y

Mientras que:

	*gp_ul ++ = *(main_ts_tmaps_0 + rda);

Genera:

	lda     _gp_ul
	ldx     _gp_ul+1
	sta     regsave
	stx     regsave+1
	clc
	adc     #$01
	bcc     L4463
	inx
L4463:	sta     _gp_ul
	stx     _gp_ul+1
	lda     _rda
	sta     ptr1
	tya
	clc
	adc     #>(_main_ts_tmaps_0)
	sta     ptr1+1
	ldy     #<(_main_ts_tmaps_0)
	lda     (ptr1),y
	ldy     #$00
	sta     (regsave),y

Por eso me he quedado con la primera opción. Fíjate qué curioso, en SDCC sale mejor la segunda.

~~~

Mecano y me queda. Haciendo un bucle tonto para que se scrollee el mapa y midiendo cuántos rasters ocupa mi rutina, resulta que nunca pasa de los 12 (a simple vista). Me he superado, bacalado. Y eso que hay una expresión al principio que creo que se podría optimizar un poco.

Y fin por hoy.

20170114
========

Me he despertado con una cuestión en la que no había pensado: yo siempre había movido cam_pos según el valor de 16 bits de prx... Pero ahora voy a mantener un prx de 8 bits normal y corriente. Como voy a tener n_pant actualizado correctamente cada vez que prx "sature", este número de 16 bis es, efectvamente, n_pant:prx.

La cosa es que tengo que ver como convertir n_pant:prx en MSB/LSB del mismo número. Creo que cc65 no se va a coscar y no va a optimizar si hago (n_pant << 8) | prx, probaré qué código saca y veré la viablilidad de hacer ASM en linea si llega el caso.

~~

¡Ay, pues no! ¡cc65 optimiza esto de puta madre!

;
; cam_pos = (n_pant << 8) | prx;
;
	lda     _prx
	sta     _cam_pos
	lda     _n_pant
	sta     _cam_pos+1

Ferpecto :) Una cosa más resuelta.

Hoy tocará meter a Cheril dando saltos (modo básico, sin florituras) y a tirar. He pensado que además tengo un montón de sitio en patrones y metatiles para floriturear gráficamente un montón. Ya me da igual si no da tiempo para el concurso, lo voy a poner muy bonico.

~~

Necesito además la infraestructura para la colisión. Ahora tengo que ver si los fantis colisionaban con el escenario; en ese caso, necesitaré hacer el buffer completo de dos pantallas. Voy a echar un vistazo.

No colisionan. ESTUPENDO.

Aunque creo que no me cuesta nada llevar el buffer completo. Con la idea de que en próximos juegos pueda hacer falta. Como ahora mismo no me puedo poner me llevaré el cuaderno y pensaré.

~~

Veamos, lo suyo sería rellenar un buffer a la vez que se pinta el chunk. Pero ¿es realmente necesario? ¿No puede hacerse la colisión tirando directamente del mapdata?

De entrada tenemos que está organizado por columnas y tiene un byte por tile. Cada 192 bytes del mapa es una pantalla. Si apuntamos el puntero al principio del stripe actual,

	n_pant * 192 = (n_pant * 64) * 3, también n_pant * 64 + n_pant * 128.

Podemos hacer:

	gpint = n_pant << 6;
	gpint = gpint + gpint + gpint;

Aunque también podemos tener un cur_scr_ptr e incrementarlo/decrementarlo en 192 a la vez que n_pant.

En ese caso, un cálculo de attr (x, y) sería

behs [*(cur_scr_ptr + x * 12 + y << 4)];

x * 12 = (x * 4) * 3 = (x * 8) + (x * 4)

Y me ahorro el buffer circular y las mierdas en lata. Lo malo de esto es que sólo puedo usar la colisión para la pantalla actual donde está el jugador. Si en el futuro necesitase colisionar enemigos, debería almacenar el cur_scr_ptr de dicho enemigo en su estructura de datos, y generalizar.

También vamos a dar dos tiles de ajuste como en Lala para que moverse por la parte superior de la pantalla sea menos dolor.

Sería algo así:

void cm_two_points (void) {
	cyaux = cy1 < 2 ? 0 : cy1 - 2; cxaux = cx1 << 2; 
	at1 = behs [*(cur_scr_ptr + cxaux + cxaux + cxaux + cyaux)];
	cyaux = cy2 < 2 ? 0 : cy2 - 2; cxaux = cx2 << 2; 
	at2 = behs [*(cur_scr_ptr + cxaux + cxaux + cxaux + cyaux)];
}

En realidad las colisiones siempre son para un segmento vertical o uno horizontal, por lo que creo que podríamos simplificar:

void cm_two_points_horizontal (void) {
	// cy1 == cy2
	cyaux = cy1 < 2 ? 0 : cy1 - 2; 
	cxaux = cx1 << 2;
	at1 = behs [*(cur_scr_ptr + cxaux + cxaux + cxaux + cyaux)];
	cyaux = cx2 << 2; 
	at2 = behs [*(cur_scr_ptr + cxaux + cxaux + cxaux + cyaux)];
}

void cm_two_points_vertical (void) {
	// cx1 == cx2
	cxaux = cx1 << 2; cxaux = cxaux + cxaux + cxaux;
	cyaux = cy1 < 2 ? 0 : cy1 - 2; 
	at1 = behs [*(cur_scr_ptr + cxaux + cyaux)];
	cyaux = cy2 < 2 ? 0 : cy2 - 2; 
	at2 = behs [*(cur_scr_ptr + cxaux + cyaux)];
}

Que serían levemente más rápidas y además me ahorro una asignación antes de la llamada en todos los casos. Creo que merece la pena.

~~


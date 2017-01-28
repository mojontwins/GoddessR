20170111
========

Voy a divagar un momento.

Esto es una locura. Faltan 20 días para que termine el concurso de nesdev y se me ha ocurrido hacer un remake del abandonado Cheril the Goddes pero usando scroll. Necesito rehacer todos los sprites y montar un proyecto nuevo con un montón de cosas que aún no he probado. Además tengo que integrar la cantidad de cosas chulas que tenía el original: portales, objetos, chac-chacs...

El tema está en que el juego siga 100% orientado a pantallas, pero que se muestre con scroll. Esto implica tener un scroller para ir mostrando nuevo contenido, además de manejar dos pantallas de enemigos a la vez. La idea es que sea lo más sencillo posible.

Si la pantalla de scroll siempre está alineada a pantalla HW, modificar el contenido debería ser trivial. Sólo tendría que tener en cuenta dónde estoy. Lo digo porque los chac-chacs se hacen pintando tiles. Esto es muy importante. 

El motor debería poder empezar en cualquier sitio del mapa, pero siempre alineado a pantalla. Esto es MUY importante. Si se dice que tengo que empezar en X = n, tengo que empezar realmente al principio de la pantalla que contenga a X.

Si siempre llevo sincronía entre scroll y pantallas, puedo usar el motor de movimiento tal cual con prx y pry como bytes, y px un signed char normal que sólo pueda tomar valores hasta 4096. Así no importa que el mapa tenga 20 pantallas de ancho. Para las colisiones con los malos tengo que idear una estrategia para:

1. Sólo tener en cuenta los 3 de la pantalla donde está Cheril. Por tanto tengo que llevar un registro de en qué pantalla estoy, y actualizarlo siempre que px se reinicie al llegar a uno u otro bordes.

2. Si se está en la misma pantalla, las coordenadas "x" reales son más que suficientes.

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

* 1 frame para calcular atributos.
* 1 frame para escribir 6 bytes de atributos.
* 6 frames para 24x4 patrones = 16 patrones en cada frame, o lo que es lo mismo, un chunk de 4x4 patrones.

Ahora se me pasa por la cabeza que si pudiese procesar el mapa en chunks de 4x4 el scroller sería de los cojones de sencillo, pero no sé si saldrían demasiados metatiles y ocuparían un huevo. ¡No tengo más que escribir un conversor para comprobarlo!

Ya tengo algo divertido que hacer para luego.

~~

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
    L4463:  sta     _gp_ul
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
    L4463:  sta     _gp_ul
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

~~

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

Hum - Ahora que lo pienso, farfis de mí, voy a tener que usar el buffer de RAM porque el fondo es modificable :-/

SUPUTAMATER.

Haré la copia a la vez que pinto la columna, no debería ser muy complejo. El cálculo en cm_two_points_horizontal y cm_two_points_vertical será además más sencillo.

~~

Ahora tengo que pensar en cómo montar el buffer. Mierder, esto me ha pillado un poco por sorpresa.

Veamos, supuestamente nosotros siempre estamos en la misma pantalla que se va pintando. El tema más sencillo, por potencias de dos, es llenar un buffer que ocupe ambas pantallas, y luego en las rutinas de colisión usar la parte izquierda o derecha del buffer, según corresponda.

Podríamos incializar con scr_buffer como un array de 384 tiles, y tener scr_buffer_0 y scr_buffer_1 apuntndo a scr_buffer y (scr_buffer + 192), respectivamente.

Podría probar a rellenar el buffer en el 8º paso (state_ctr == 7), que ahora mismo está libre. Y de paso podría parchear luego de alguna forma para rellenar como me conviene.

En col_idx tenemos el índice de la columna o chunk. Hay 16 columnas chunk o 32 tiles para poner en el buffer:

    rdx = (col_idx & 0xf) << 1;

De esta manera:

    // State 7: collision buffer
    rdx = (col_idx & 0xf) << 1;
    gp_gen = (unsigned char *) col_ptr;
    for (gpint = rdx; gpint < 384; gpint += 32)
        scr_buffer [gpint] = *gp_gen ++;
        scr_buffer [gpint + 1] = *gp_gen ++;
    }

De este modo, las rutinas de colisión quedarían así:

    void cm_two_points_horizontal (void) {
        // cy1 == cy2
        cyaux = cy1 < 2 ? 0 : cy1 - 2; 
        gpint = cyaux << 5;
        at1 = behs [*(scr_buffer + gpint + cx1)];
        at1 = behs [*(scr_buffer + gpint + cx2)];
    }

    void cm_two_points_vertical (void) {
        // cx1 == cx2
        cyaux = cy1 < 2 ? 0 : cy1 - 2; 
        at1 = behs [*(scr_buffer + (cyaux << 5) + cx1)];
        cyaux = cy2 < 2 ? 0 : cy2 - 2; 
        at2 = behs [*(scr_buffer + (cyaux << 5) + cx1)];
    }

Hm, pero no. Me lo vuelvo a pensar y va a ser mejor tener el buffer partido en 2 buffers de 1 pantalla.

    // State 7: collision buffer
    gp_aux = scr_buffer + ((col_idx & 8) ? 192 : 0) + (col_idx & 0x7) << 1;
    gp_gen = (unsigned char *) col_ptr;
    rdy = 12; do {
        *gp_aux ++ = *gp_gen;
        *gp_aux = *gp_gen ++;
        gp_aux += 15;
    } while (-- rdy);

De este modo, las rutinas de colisión quedarían así (teniendo scr_buffer_ptr bien apuntado dependiendo del valor de n_pant!):

    void cm_two_points_horizontal (void) {
        // cy1 == cy2
        cyaux = (cy1 < 2 ? 0 : cy1 - 2) << 4; 
        at1 = behs [*(scr_buffer_ptr + cyaux + cx1)];
        at1 = behs [*(scr_buffer_ptr + cyaux + cx2)];
    }

    void cm_two_points_vertical (void) {
        // cx1 == cx2
        cyaux = cy1 < 2 ? 0 : cy1 - 2; 
        at1 = behs [*(scr_buffer_ptr + (cyaux << 4) + cx1)];
        cyaux = cy2 < 2 ? 0 : cy2 - 2; 
        at2 = behs [*(scr_buffer_ptr + (cyaux << 4) + cx1)];
    }

Cuando vaya a actualizar n_pant:

    n_pant ++;
    scr_buffer_ptr = scr_buffer + ((n_pant & 1) ? 192 : 0);

Y también

    n_pant --;
    scr_buffer_ptr = scr_buffer + ((n_pant & 1) ? 192 : 0);

El cálculo de scr_buffer_ptr lo puedo meter en una macro.

    n_pant ++; SCR_BUFFER_PTR_UPD;

Etc...

~~

Probando más cosas veo que el relleno del buffer de colisión es demasiado lento. Se ve un saltaco, dura más del doble que el resto de las cosas que se hacen.

Tengo que replantearlo. Aunque ahora estoy ansioso por montar el puto motor de movimiento, y el tiempo se acaba hoy. Ar.

He desenrollado y no se nota mucho, pero a lo mejor puedo distribuir por ahi partiendo las 12 lineas entre el resto de mierdas que se hacen... de alguna manera.

~~

Mejor así. He balanceado la carga. Creo que puedo optimizar algo los cáclulos aún, pero ahora casi todos los frames ocupan lo mismo excepto el 8º que vuelve a no durar nada. Lo dejamos por ahora.

20170115
========

Ayer al final terminé de integrar el motor de movimiento de Cheril y además creé todo el flujo de juego (al menos de forma esquelética) y la gestión de niveles y subsecciones de nivel. Todo guay, pero hay un glitch en las colisiones: los puntos de la derecha del bounding box dan problemas cuando se salen de la pantalla. Hay wrap-around y miran los valores correctos de x... pero en la pantalla que no es.

La solución es sencilla: darse cuenta y actualizar el puntero en esos casos, pero lo cierto es que no se me ocurre una forma de integrarlo todo que sea relativamente general e indolente.

~~

Bueno, he aprendido algo más sobre cc65 que viene genial:

    rda = (rdb + 7) >> 4;

aunque rdb sea unsigned char (8 bits), es promocionado a 16 bits al sumarle 7, así que si el resultado es >= 256 al hacer >> 4 dará 16. Yo pensaba que rdb iba a saturar al sumarle 7 (suma de 8 bits). Eso me permite coscarme y mirar donde es:

    void player_collision_vertical (void) {
        cyaux = (cy1 < 2 ? 0 : cy1 - 2) << 4;
        at1 = behs [*(scr_buffer_ptr + cyaux + cx1)];
        if (cx2 > 15) {
            cx2 -= 16;
            gp_aux = scr_buffer + ((n_pant & 1) ? 0 : 192);
        } else {
            gp_aux = scr_buffer_ptr;
        }
        at2 = behs [*(gp_aux + cyaux + cx2)];
    }

    void player_collision_horizontal (void) {
        *((unsigned char *)0xf0)=cx1;
        if (cx1 > 15) {
            cx1 -= 16;
            gp_aux = scr_buffer + ((n_pant & 1) ? 0 : 192);
        } else {
            gp_aux = scr_buffer_ptr;
        }

        cyaux = cy1 < 2 ? 0 : cy1 - 2; 
        at1 = behs [*(gp_aux + (cyaux << 4) + cx1)];
        cyaux = cy2 < 2 ? 0 : cy2 - 2; 
        at2 = behs [*(gp_aux + (cyaux << 4) + cx1)];
    }

Se ve un tanto guarreras. No sé si tendré que hacer recálculos. Además, hay mierda no controlada aún - pero como en este juego no se da, me callo.

    X|·

Con X = obstáculo, | = limite de la pantalla, · = nada, colisionando a la izquierda... undefined. No sé qué pasaría XD

Mañana me pongo con el próximo coco: meter enemigos. Así de entrada cam_pos tiene un MSB que indica la "pantalla", hay que ver la que va entrando y crear al vuelo 3 nuevos en la primera (par) o segunda (impar) mitades de nuestros arrays de 6 posiciones.

Y habrá que pillarlos del level que sea.

Uf, ya me duele la cabeza. Pensaré despacio en esto mañana. Buenas noches.

20170116
========

Ayer se me ocurrió usar el frame libre del scroller para que, si el número del chunk & 7 == 0 o 7 (ver más tarde), emplear para cargar los 3 enemigos correspondientes en el array de enemigos activos.

El array de enemigos activos tiene 6 posiciones: 3 para cada pantalla activa. Como recordaremos, si (n_pant & 1) == 0 (par), pintamos en las tres primeras posiciones del array; si (n_pant & 1) == 1 (impar), lo haremos en las tres siguientes.

Cada vez que "entra" una pantalla debe cargarse la mitad correcta. Al avanzar a la derecha, la pantalla nueva "entra" cuando se pinta su primer chunk (0); al avanzar a la izquierda, lo hace cuando se pinta su último chunk (7).

Lo más sencillo de integrarlo todo es marcar, con un flag, cuando estamos en el "frame libre" del chunk correcto, y usar esto desde el módulo de enemigos.

También voy a reordenar los estados para ahorrar algunos ciclos más, y quiero empezar a rediseñar gráficos. Para ello miraré gráficos de otra gente para inspirarme, aunque tengo ideas.

No va a dar tiempo, veo, pero mola. 

20170118
========

He estado estos días haciendo gráficos nuevos de fondo y rellenando el mapa de detalles. Joder, lo mola todísimo, pero creo que me he liado tanto con algo que debería haber dejado hasta el final.

No quiero terminar hoy la jornada sin pensar un poco en el motor de enemigos. El tema está en cargar los activos de la pantalla que entra en el array de los enemigos que se actualiza.

Ahora mismo he dejado preparado el scroller para que envíe una señal durante el tiempo 7 (el último) de su máquina de estados si está dibujando el primer o último chunk de una pantalla.

La idea era que si estábamos avanzando a la izquierda y se pinta el chunk 7 de una pantalla creásemos los enemigos de esa pantalla aprovechando el frame con menos carga.

n_pant = chunk >> 3, si no me salen mal los cálculos, o MSB cam_pos.

La función enems_load debería obtener en rda, por ejemplo, el n_pant sobre el que tiene que actuar, quizá dentro de la tira o piso actual del mapa (con un offset, vaya).

Si este (rda & 1) == 0, crear los enemigos de rda en las posiciones 0..2 de los arrays de enemigos en pantalla. Si (rda & 1) == 1 deberán ser creados en las posiciones 3..5.

La creación puede ser tal que Yun, o MK2. Vaya, la de siempre. Creo que dará tiempo a hacer algunas asignaciones, ¿no?

Tengo que rehacer el exporter para exportar los valores de los enemigos en cuatro arrays separados en lugar de intercalarlos todos en el mismo array. Hoy se me está haciendo un poco tarde, supongo que lo haré mañana. Así habrá que hacer menos cálculos. 

Ahora hay que multiplicar por 3, en vez de por 12, y puedo usar un índice para todos los accesos. A ver si es más rápido hacer a + (a << 1) o a + a + a. Voy a generar código para ambos.

Peo.

    ;
    ; rdb = (rda << 1) + rda;
    ;
        lda     _rda            4
        asl     a               2
        clc                     2
        adc     _rda            4
        sta     _rdb            4

    ;
    ; rdc = rda + rda + rda;
    ;
        lda     _rda            4
        clc                     2
        adc     _rda            4
        bcc     L60D7           2+
        clc                     2
    L60D7:  adc     _rda        4
        sta     _rdc            4

Es más rápida la primera.

Además viendo como suele actuar el compilador, seguro que si leo en masa los cuatro arrays haciendo así:

    rda = arr1 [i];
    rdb = arr2 [i];
    rdc = arr3 [i];
    rdd = arr4 [i];

El compilador puede generar código molón. En ensamblador, cargaría i en X y usaría direccionamiento absoluto con desplazamiento.

    ldy _i
    lda (_arr1), Y
    sta _rda
    lda (_arr2), Y
    sta _rda
    lda (_arr3), Y
    sta _rda
    lda (_arr4), Y
    sta _rda

Si no lo hace así miro de meterlo en linea.

20170119
========

Voy con los enemigos. Por lo pronto he escrito el conversor. Luego tendré que repasar las notas del goddess original para ver cómo se interpretaban los hotspots que, además, creo recordar que eran contenedores (por lo que habrá que crear una estructura en RAM para todos - al menos para el contenido: 80 bytes).

voy primero a hacer una especie de tester de concepto. Imprimiré en pantalla qué índices del array de enemigos se irían cargando al avanzar por el mapa. Necesito 0123456789ABCDEF en los ts, al principio. Remember que vacío = 255.

~~

Por ahora la precarga de enemigos (bueno, no hago precarga real, sólo he estado imprimiendo qué slots se cargarían y con qué valores, y todo va guay) genera este código, muy feo:

    ;
    ; rda = c_enems_t [enidx];
    ;
    L6640:  lda     _c_enems_t
        ldx     _c_enems_t+1
        ldy     _enidx
        sta     ptr1
        stx     ptr1+1
        lda     (ptr1),y
        sta     _rda
    ;
    ; rdb = c_enems_yx1 [enidx];
    ;
        lda     _c_enems_yx1
        ldx     _c_enems_yx1+1
        ldy     _enidx
        sta     ptr1
        stx     ptr1+1
        lda     (ptr1),y
        sta     _rdb
    ;
    ; rdc = c_enems_yx2 [enidx];
    ;
        lda     _c_enems_yx2
        ldx     _c_enems_yx2+1
        ldy     _enidx
        sta     ptr1
        stx     ptr1+1
        lda     (ptr1),y
        sta     _rdc
    ;
    ; rdd = c_enems_mn [enidx];
    ;
        lda     _c_enems_mn
        ldx     _c_enems_mn+1
        ldy     _enidx
        sta     ptr1
        stx     ptr1+1
        lda     (ptr1),y
        sta     _rdd
    ;

No mola. ¿Me cargaré mucho esto si meto en linea mi solución? Voy a comprobarlo ;-)

Nah, funciona guay:

    ldy     _enidx
    lda     (_c_enems_t),y
    sta     _rda
    lda     (_c_enems_yx1),y
    sta     _rdb
    lda     (_c_enems_yx2),y
    sta     _rdc
    lda     (_c_enems_mn),y
    sta     _rdd

~~

Esto son los tipos de enemigos que manejo en el goddess original. Creo que cambiaré los valores en el .ENE para usar algo más parecido a MK2 (que es más fácil de procesar, entiendo):

Lineares
1, 2, 3 -> 0x10, 0x11, 0x12

Plataforma
4 -> 0x23

Homing Fanty
6 -> 0x30

Pezons
9 -> 0xC0

Chac chac
10 -> 0x50

Este cambio es compatible con steady shooters (0x80), monococos (0x90), gyrosaws (0xB0) y catacrocks (0x40)

Voy a pasar un updater custom por el enems antes de seguir.

~~

Me lo apunto: voy a intentar implementar fantis y pezons empleando unicamente enteros. Oh, sí, lo voy a flipar, porque necesito tablas de velocidades precalculadas y jugar con índices en un cacho de código ilegible. Pero molará.

Por ahora he hecho la carga dinámica de los valores de los enemigos y tengo que ver como me sube eso el tiempo empleado.

Lo próximo es meter esto, si cabe, antes del split del escenario.

~~

Bueno, el bucle de proceso fuera de orden de los enemigos está funcionando (aunque no procese nada). La carga está bien balanceada, o casi (hay algunos timbrazos gordos pero espero poder compensar). 

Quiero establecer el split y pintar el marcador (o al menos el esqueleto del mismo) y ver qué cosas de las que hay puedo colocar antes del punto de split. Probablemente tenga que reordenar las tareas del bucle principal.

También me estoy planteando muy pucho pasar de la compensación NTSC/PAL y que simplemente todo vaya más deprisa en NTSC. No sé qué hacer.

~~ 

Voy a mirar el código de los pezones de Goddess y a grabar los incrementos *exactos* en una tabla, pasando de aproximar con mi aplicación mierder.

~

Tras extraer los incrementos y meterlos en un array he programado a ciegas el comportamiento de los pezones, y queda tal que así:

    // Occluding sprite
    oam_index = oam_meta_spr (
        en_x1 [gpit], en_y1 [gpit],
        oam_index,
        spr_enems [PEZONS_BASE_SPRID + 2]
    );

    if (en_state [gpit]) {
        en_y [gpit] += pezon_incs [PEZON_INCS_IDX [gpit]];
        oam_index = oam_meta_spr (
            en_x1 [gpit], en_y [gpit],
            oam_index,
            spr_enems [PEZONS_BASE_SPRID + (PEZON_INCS_IDX [gpit] > PEZON_INCS_FIRST_FALL)];
        );
        if (PEZON_INCS_IDX [gpit] < PEZON_INCS_MAX) {
            PEZON_INCS_IDX [gpit] ++; 
        } else {
            en_state [gpit] = 0;
            PEZON_TIMER [gpit] = PEZON_MAX_TIME [gpit];
        }
    } else {
        if (PEZON_TIMER [gpit]) PEZON_TIMER [gpit] --; else {
            PEZON_INCS_IDX [gpit] = 0;
            en_state [gpit] = 1;
            en_y [gpit] = en_y1 [gpit];
        }
    }
    
Lo probaría, pero necesito redibujar y cierta infraestructura, y se me hace tarde, así que lo dejaré hasta mañana.

20170120
========

Más gripón, y 11 días para hacer esto. Creo que pinta mal, me he liao con los gráficos, y ahora me voy a poner a hacer más XD

Bueno, al lío, que tengo poco tiempo y las siestas del churum son jodidamente cortas últimamente.

~~

Gráficos entregagos, ahora voy a modificar el script de recorte que muchos sprites son más grandes. A ver como vamos de patrones :)

~~

El pezón funciona pero tengo mal el cálculo de los sprites que tengo que mostrar y que entran en el viewport. Algo chungo estoy haciendo, no selecciono bien. Pero va por buen camino :)

~~

Arreglé eso, más o menos, porque glitchea. O sea, va bien, pero me da la impresión de que durante un instante mientras scrolleamos los sprites desaparecen. Seguro que hay un caso marginal en el que no se cumple ninguna de las condiciones, tengo que revisarlo.

También he hecho los enemigos lineales - con colisión. Eso significa que he tenido que añadir infraestructuras para leer los buffers temporales desde el módulo de enemigos y está funcionando guay.

He apañado también las transiciones laterales aunque si me sobra sitio y ciclos puede que las ajuste más, pero por ahora me vale. 

Ahora hay un par de detalles tonters que me mosquean un poco, pero bueno, poco a poco. A ver qué tal se me dan los fantis de lógica entera e incrementos precalculados. Generaré la tabla y empezaré a probar. Supuestamente tenemos un índice que se incrementa cuando aceleramos y decrementa cuando deceleramos. El incremento 0 está en el centro de la tabla, así que eso debe ser nuestra "velocidad 0". Luego saturamos por ambos lados si nos vamos a salir de la tabla y poco más. Debería estar chupado. Y me va a venir de puta madre para el Yun de master.

Tendré que refinar un poco el tema este. Son homing fantis: si te vas muy lejos vuelven a casa. Ese "si te vas muy lejos" es un cálculo medianamente costoso, creo que puedo limitarlo a la coordenada X y hacer el fullero. Además, si te sales de la pantalla donde están directamente ya no te verán y quedará menos cantoso. Creo que puede dar el pego... Aunque recuerdo que los metí en Pong Pong y quedaba raro. Bueno, ya veremos.

Qué coño - acabo de ver el tema del glitch: es el frame en el que no proceso los enemigos. Me cago en mi puta calavera. 

Creo que tengo que pasar de eso, hay que pintarlos por lo menos, y pintar es procesar porque va todo unido.

Mira, cojona, si me veo jodido de tiempo de frame ya me pondré a multiplexar luego. Joder.

20170121
========

Ayer me acosté con la sensación de que los sprites más grandes y la animación penca quedaban fatal. He intercalado frames entre los que hay y voy a ver si me sigue dando la tabla de patrones para sprites. Quería dejarme algo para otro tipo de enemigos pero creo que tendré que ser creativo cuando llegue el momento.

~~

Ok - no he gastado demasiado y ha quedado BASTANTE mejor. Ya estoy contento, tras una hora de mover pixels. Ahora voy a programar los fantis. Primero, como en el otro caso, me generaré toda la tabla de incrementos simulando el comportamiento del motor real (aceleración hasta el máximo, y valores negados para el contrario).

~~

Veamos, he generado una tabla de 16 incrementos. Esto harán que, en 16 frames, se llegue de 0 pixels por frame a 1 pixel por frame. Más o menos. Según lo veo es muy rápido, pero veamos como funciona. Si veo que es muy mal, aumentamos los pasos dividiendo la aceleración.

Tendremos en mx, my las "velocidades", que no son más que índices de la tabla fanty_incs. Podrán valer de -16 a 16, con estas restricciones:

- Si valen -16 o 16, se convierten en -15 o 15.
- El incremento I según el valor de mx/my será:
    inc = ADD_SIGN (mx, fanty_incs [ABS (mx)])

UF! Veamos qué tal se da. Es que esto es lo mas rápido con diferencia.

~~

Más o menos parece que funciona ¡a la primera! pero debe haber algo que no controlo bien porque los fantys nunca se quedan estacionados en modo idle cuando salgo de la "pantalla" virtual. Hm...

Y de tiempo van guay. Obviamente son mas pesados que otros tipos de enemigos pero el motor podrá mover tres sin toser.

Hm... no. En determinadas circunstancias se quedan TOPI. TOPILLAOS.

A examinar valores XD

~~

Solucionado. El tema era que estaba incrementando siempre aunque no hiciera falta los valores en el estado retreating, con lo que los murciélagos empezaban a pivotar en un loop que podía hacerse infinito. Creo que lo he arreglado.

Ahora habrá que pasar a lo siguiente: ¡hotspots!

~~

Espera, que quedan los chac-chacs.

Se me ha ocurrido que es tontería procesarlos como enemigos. No se mueven (no son sprites, me refiero), actualizan de forma diferente (mediante la update list), no usan la colisión usual (simplemente marcan el buffer como tiles de tipo 1 - algo que por cierto tengo que meter todavía)... Lo suyo es manejarlos aparte.

Me crearé las estructuras necesarias en BSS (que está casi libre) y activaré los chac-chacs cuando se entre en la pantalla y los desactivaré cuando salgan del área visible. Por cierto, voy a meter los precálculos del módulo y parte "entera" de cam_pos en el módulo de manejo de la cámara y así estarán disponibles posteriormente a tutiplen, que los necesito.

También guardaré la ejecución. Cada frame sólo voy a actualizar una (si toca), y solo lo haré si no hemos scrolleado o estamos en el paso 7.

~~

Atención con esto:

    // Chac chac creation. Note there's an increible
    // shortcut: chac chacks must have X even, Y odd to be
    // detected!
    if (rda == CHAC_CHAC_BASE_TILE) {
        chac_chac_create ();
        rda = CHAC_CHAC_TOP_SHADOW_TILE;
    }
        
Sorry, asín es.

~~

Ojal guarrada: en printer estoy metiendo una función que actualice un metatile y tal. Necesito los metatiles y sus datos, y estos están en prg0... La función debe colocar prg2 en cuanto acabe o crash. Pero bueno, no pasa nada. La putada es que no puedo leer la pantalla, y no quiero tener otro buffer, por lo que esta mierda tendrá que llevar la paleta que ya hay. Es una putada, pero peor es nada. Si queda muy soso cambiaré los gráficos. ¿A quién quiero engañar? Los cambiaré de todos modos.

~~

Lo he hecho muy rápido... ¿Qué me falta? Voy a compilar y a ver.

(no lo he compilado aún) ¡Ah, ya sé! Eliminar los chac chacs. Esto no es tan sencillo, bro.

A ver, cc_x contendrá un número de 0 a 15. cc_pant, un número 0 o 1. voy a dibujar. Hm - espera, que se crean fuera de la pantalla. Al carajo el dibujo. Tiene que ser más sencillo.

Si almaceno el col_idx donde estaba, sólo tengo que eliminarlo cuando este col_idx esté "muy lejos". Si cc_col_idx < col_idx_act - 1 o cc_col_idx > col_idx_act + 9, esto es.

~~

Mayormente las columnas en sí medio van bien, pero la creación parece penca. Algo estoy pasando por alto...

Bueno, por lo pronto tengo el mapa con columnas en Y par. Pero el tema es que no las está eliminando, crea sin sesar.

No, las elimina guay. El problema es que las crea N veces. Seguro que está pintando el mismo tile varias veces o algo (es como las detecto).

Puf - para ver si ya no está creada tendría que hacer una busqueda para que no se repita el col_idx ... Pero eso me duele solo de pensarlo.

Mierder.

~~

Me cago en mi puta calavera. Se me ocurren soluciones, pero todas implican gastar un porrón de RAM, y paso. Búsqueda que te crió.

Hay un shortcut: si recuerdo el anterior cc_it y miro que el col_idx nuevo sea diferente, elimino un montón de casos - a menos que se de que coincida que, al scrollear, en col_idx - 1 y en col_idx + 9 haya chac chacs. Eso se arregla diseñando bien el nivel. Creo que podría funcionar.

Nah, lo he probado y si hay muchos chac chac glitchea que es un gusto.

Búsqueda lineal y a mamarla.

~~

Todo va muy guay. Lo he subido a Github. Justo después, jugando, me he dado cuenta de un glitch en la creación de enemigos. Ha sido al subir a la pantalla de arriba desde la última pantalla del mapa, y luego avanzar a la izquierda. Hay un murciélago que se convirtió en mono en la pantalla penúltima. Tengo que revisar cómo se inicializa el mapa en los bordes, puede que sea el problema.

Pero hoy me he pegado muuucho rato.

~~

Creo que es esto: 

    rdpant = n_pant; enems_load ();
    rdpant = n_pant + 1; enems_load ();

Obviamente n_pant + 1 no tiene sentido. Voy a intentar controlarlo.

~~

He puesto esto:

    rdpant = n_pant; enems_load ();
    rdpant = n_pant < 19 ? n_pant + 1 : n_pant - 1; enems_load ();

Por ahora no lo veo glitchear más. Será cuestión de seguir jugando y verlo. Voy a subirlo a github y me voy a jugar un rato a la consola. Mañana hotspots.

~~

Pero me apetece divagar un poco sobre los hotspots. A nivel de sprites y mierdas serían igual que los enemigos, mismos cálculos, bla bla, solo que más sencillos. Sólo hay un por pantalla. La precarga necesita menos valores. 

Los hotspots están vacíos, contienen objetos, o sirven de detectores. Todo tiene que ver con el valor que almacenan. En teoría puedo poner y dejar objetos en los hotspots.

- Un objeto correcto que se deje en un templo debe quedarse fijado y no poder cogerse de nuevo.
- Determinados contenidos hacen que mostremos el cuadrado de linea discontinua: hotspot sin objeto, detector.
- El hotspot de vida y el de la calavera se pueden coger y deben desaparecer para siempre.

El quid está en como codificar:

- Hotspots que se cogen, actúan y desaparecen (vida, calavera).
- Hotspots de detección (teletransportador, templos, recarga de superpoderes).
- Hotspots contenedores para piedra, papel, tijeras y llave.

Podemos hacer 0xff sea "sin objeto". Si no llevas nada, llevarás "0xff". Si interactúas con un hotspot que tenga un objeto recogiscible, se intercambia este 0xff con el código del objeto.

Si ponemos corazon = 1, Calavera = 2, Piedra = 4, Papel = 5, Tijeras = 6, Llave = 7 los puedo hacer coincidir con el sprite_id.

Al tocar un hotspot, primero detecto 1 o 2, y actúo y pongo el hotspot a 0, que es desactivado total.

Si no era 1 o 2, miro si es 5, 6, 7 o 8. En ese caso intercambio el objeto que llevamos con el que hay en el hotspot (intercambio los valores).

Todo esto me cabe en 3 bits, por lo que puedo codificar el resto levantando bits.

- bit 3 a 1: es el templo donde se utiliza el objeto correspondiente con el bit 3 a 0, en orden templos de tijeras, piedra, papel, cerrojo. 
- bit 4 a 1: el objeto que tiene no se puede coger.

Por tanto, seguimos detectando así. Si no se cumple nada de lo anterior, ver si (hst & 8) (bit 3 = 1) y que no sea que (hst & 16) (bit 4 = 0). En este caso, si hst & 7 == objeto en el inventario, le levantamos el bit 4 al hotspot, le bajamos el 3 y hacemos la animación e historias necesarias.

Si no se cumple nada, vemos si es recarga o teletransportador, con códigos especiales.

A la hora de pintar:

- Si es 0, nada.
- Si es < 8, el sprite que corresponda.
- Si es el cerrojo, el sprite cerrojo! <-especial
- Si tiene el bit 4 a 1 se muestra el sprite que sea hst & 7.
- En otro caso, caja vacía.

Con esto puedo hacer rápido el soporte básico. Luego ya veremos las animaciones y las historias, que eso trae más cola.

Tendré que modificar los valores del mapa.

    - CORAZON: 01
    - CALAVERA: 02
    - PIEDRA: 04
    - TEMPLO TIJERAS: 4 + 8 = 0C
    - PAPEL: 05
    - TEMPLO PIEDRA: 5 + 8 = 0D
    - TIJERAS: 06
    - TEMPLO PAPEL: 6 + 8 = 0E
    - LLAVE: 07
    - CERROJO: 7 + 8 = 0F
    - TELETRANSPORTE: 20
    - RECARGA PODER: 21
    - FINAL: 22

Ok - puestos. Agur.

20170122
========

Voy a hacer una implementación de la base necesaria: copia a RAM, creación al vuelo del sprite, etc. Y luego me hago un cafel.

~~

Bueno, ya se muestran los hotspots. Ahora es el momento en el que me tengo que poner con las colisiones. Y me temo que para ello tendremos que reorganizar un par de cosas, como el orden en el que se pintan los sprites, para que las plataformas verticales no den "saltitos". Haré lo de siempre: sacaré al sprite del protagonista de oam_index, lo pinto siempre fijo en oam_index = 4, e inicializo oam_index para el resto en 28 en vez de en 4. Sí, si alguien lee esto, no se ha enterado de un carajo.

~~

Vamos con la colisión de los enemigos y plataformas. Empezaré por las plataformas, pero antes algo de infraestructura: reorganizo el código para que se salte el enemigo lo antes posible: 

- Si tras moverlo sprid = 0xff, no se muestra, no interactúa.
- Si tras calcular el clipping (si aparece en pantalla o no) está fuera, no interactúa.
- Si está en una pantalla diferente al jugador, no interactúa.

Si hemos llegado hasta aquí el enemigo se ha pintado y está en la misma pantalla que el jugador, por lo que podrá colisionar.

El orden de comprobación de la colisión (por caja) debe intentar quitarse de encima todo lo antes posible. Es mejor comprobar primer X y luego Y, porque las pantallas son más anchas que altas, y es más probable que coincidan Y pero no X que coincidan X pero no Y. Es una chorrez, pero puede eliminar muchos ciclos en la mayoría de los casos. Personalmente siempre hago estas mierdas.

Ojezno, además: en este punto puedo usar sprx y spry para colisionar porque ya contienen las coordenadas correctas del sprite. 

~~

Bueno, eso que yo llamo "die & respawn" desde tiempos de Ninjajar! ya está implementado. Ahora faltaría detectar los tiles que te matan. Lo más fácil en este juego es mirar el punto central de Cheril. Creo que funcionará y es lo más tonto de hacer. Ojal: no voy a controlar la condición de salirme de la pantalla y tener que bla bla bla como la colisión con el escenario. No hace falta ser tan precisos. Las condiciones en las que te vas a topar con un tile que mata harán que si no te da en el frame A te de en el A+1, vaya, que caerse a la lava y darse con un chac chac no son cosas que requieran una precisión milimétrica.

~~

Bueno, pues ya están las colisiones andando. Ahora podemos hacer otras cosas que son necesarias:

- Colisiones con hotspots y lógica.
- Hud y sprite 0 hit.

Las colisiones con hotspots + lógica llevarán luego la implementación de las animaciones: activar templo y teletransportarse.

Además tendré que ver qué voy a hacer con el cerrojo. Se abre la llave y debería modificarse al vuelo el escenario. Eso es tarea para colocar en algún sitio pero aún no he pensado como hacerlo y no me quiero liar a meter mierda sin pensar que luego todo se caga.

Además he optimizado el cálculo del índice del buffer de colisiones a saco con una tontería, y además me planteo hacer que el buffer no contenga tiles sino comportamientos directamente, ahorrando aún más ciclos, pero eso por ahora no es necesario y prefiero dejarlo así por lo que pueda pasar (puede que lo necesite).

Tengo que pensar también como voy a hacer para renderizar la escena de las puertas abriéndose. Quizá iniciando el motor de forma especial en un bucle alternativo que solo cargue la zona, dibuje las puertas, y poco más.

Otra cosa que hay que hacer es pintar las puertas en el templo si están cerradas. Llevo toda la mañana pensando que quizá lo suyo sería generalizar los chac chacs para que se encargasen de todos estos manejos de nametable. Le daré más vueltas.

Son las 13:30 y llevo un montón de rato aquí, creo que lo dejo porque trabajo mejor despejado y me apetece escribir a máquina.

~~

Voy a hacer lo básico con los hotspots:

- Coger vida.
- Coger (intercambiar) un objeto.
- ¿Usarlo en el templo?

Para ello necesito empezar con la guasa del HUD y de camino hacer el split. Creo que lo he estado demorando mucho. Siempre es bueno colocar algunas tareas antes del split. Tampoco vamos a estar esperando de brazos cruzados ¿no? En otros motores me ha saido muy bien. En Isshokuta, por ejemplo, todo el scroll pasa antes del split. Pero en este juego me temo que va a estar más difícil.

~~

Muchas, muchas cosas metidas, split y música incluidos. Voy a tener que fullear con los sonidos para retrasarlos y cosas así como en pongpong seguro, porque el tiempo de frame se acaba - de hecho hay sitios puntuales donde pierdo 1 frame. Nada grave, solo 1 frame. 

Cuestión de mejorar algunas cosas y dividir carga, pero antes tengo que identificar qué carga debería dividir.

¿Paso de actualizar los enemigos en el frame en el que se crean? ¿Se notará?

Por lo pronto lo primero que voy a hacer es meter directamente behs en el buffer de colisiones.

~~

Joder con la amnesia, lo de los enemigos no era viable porque necesito que se procesen para crear los sprites. Lo que sí puedo hacer es fumarme la deteccion de colisiones. Algo ganaré.

De todos modos he movido código y voy a ver qué sucede.

~~

Parece que mejora, pero si fuera necesario, tiraré de multiplexión ;-)

20170123
========

Voy a revisar cómo hacía las animaciones en el Goddess original & Peste (no tan peste) a ver si me convence. 

~~

Apuntes:

- Todas las animaciones se gestionan en player_move y no detienen el motor.
- Necesito fx_flash (pal_to_return_to);
- El "NO!" se activa del tirón, en cuanto se ve que no se puede interactuar con el hotspot. 
- Al recargar poderes, sonido FT! (lo tengo que meter en el set o buscar equivalente, es el 3)
- Al activar teleportador, ponemos tt_ct a 1. tt_ct parece ser el contador de una animación. La animación parece guardarse en un array que finaliza en 0xff. Cada valor del array SF, con F los frames (0 se cambia por 20) y S el número del sprite (0 == primer sprite de la animación de girar)
- use_ct se activa al comprobar que se puede usar un objeto, lo dejo para luego.

Medio me convence, voy a hacerlo (que no copiarlo). Necesito antes infraestructura y mierdas, pero debería tenerlo rápido.

~~

Toneladas de infraestructura, recargas y teletransportaciones hechas. Podría haber empezado por coger objetos... Bueno, eso lo siguiente. Ahora a Github.

20170127
========

Después de las vacaciones (sin apenas tiempo y con dos cojones ¡vacaciones!) voy a ponerme a generalizar los chac chacs para que también contengan la puerta abierta / cerrada y las tres compuertas de final.

~~

Vale, he estado pensando como implementar esto. Está claro que voy a usar las estructuras de los chac-chacs. X = par, hasta ahí todo guay. El tipo de cosa podría identificarlo usando tiles especiales del tileset, como los chac-chacs. Los tiles, a partir del 96, indicarán qué flag de estado de juego gobiernan cada chac chac. O lo hago custom así, o no hay forma.

0 -> usar piedra
1 -> usar papel
2 -> usar tijeras
3 -> usar llaves.

Además está todo en el level 0, para ahorrar.

~~

Anim Gate:

s = 0, s = 1, s = 2.

20170128
========

Al final, tras muchas tribulaciones y cambios de planes, lo hice. En el camino tuve que cambiar cómo se comportaba el renderer del scroll. El cambio ha necesitado que se pinte más pantalla al empezar para que esté más relleno el buffer, con lo que la transición entre pisos es más lenta, pero nada grave.

Lo que haré (y lo dejo para el final) es una función específica para que este primer dibujado de la pantalla sea mucho más rápido, que actué con la pantalla apagada y modificando directamente VRAM, sin esperas ni pollas.

Otra cosa que tengo que hacer es pulir las plataformas horizontales, que no van finas.

Ahora voy a dejar fino el marcador y controlar un poco el desarrollo del juego (game over y win game).


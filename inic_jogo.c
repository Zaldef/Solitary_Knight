#include "s_k_rpg.h"

void inicializar_jogo(){
    //Iniciar allegro
    al_init();
    //Carregar e usar fontes TrueType
    al_init_font_addon();
    al_init_ttf_addon();
    //Carregar imagens
    al_init_image_addon();
    //Habilitar o uso do teclado
    al_install_keyboard();

    ALLEGRO_DISPLAY * display = al_create_display(1000,588); // Tamanho da tela
    al_set_window_position(display, 0, 0);// posição aonde a tela começa
    al_set_window_title(display, "Solitary Knight"); //titulo da janela

    ALLEGRO_FONT* font = al_load_font("./font.ttf", 25, 0); // tamanho da fonte
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);

    ALLEGRO_BITMAP *icon = al_load_bitmap("knight_ico.png"); // Icone
    al_set_display_icon(display, icon);// Icone
    ALLEGRO_BITMAP * sprite = al_load_bitmap("./dragon.png"); // sprite dragon
    ALLEGRO_BITMAP * bg = al_load_bitmap("./bg.gif");// background (nao funciona gif, ele fica estatico)

    ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source() );
    al_start_timer(timer);
}

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
    al_set_window_position(display, 0, 0);// posi��o aonde a tela come�a
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

    void mover_dragon() {
    float frame = 0.f;
    int pos_x = 0, pos_y = 0;
    int current_frame_y = 161;

    while(true){
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        if( event.type == ALLEGRO_EVENT_DISPLAY_CLOSE ){
            break;
        }else if( event.keyboard.keycode == ALLEGRO_KEY_RIGHT ){
            current_frame_y = 161;
            pos_x += 20;
        }else if( event.keyboard.keycode == ALLEGRO_KEY_LEFT ){
            current_frame_y = 161 * 3;
            pos_x -= 20;
        }else if( event.keyboard.keycode == ALLEGRO_KEY_DOWN ){
            current_frame_y = 161 * 2;
            pos_y += 20;
        }else if( event.keyboard.keycode == ALLEGRO_KEY_UP ){
            current_frame_y = 0;
            pos_y -= 20;
        }

        frame += 0.3f;
        if( frame > 3){
            frame -= 3;
        }

        al_clear_to_color(al_map_rgb(255,255,255));// Cor da tela, nao visivel pois o background cobre ela inteira
        al_draw_bitmap(bg, 0, 0, 0); // jogar bg(background) na tela
        al_draw_bitmap_region(sprite, 191 * (int)frame, current_frame_y, 191, 161, pos_x, pos_y, 0); // jogar o sprite do dragao e mudar as iamgens "animando" ele
        al_flip_display();
    }

    al_destroy_bitmap(bg);
    al_destroy_bitmap(sprite);
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}
}

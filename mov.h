#ifndef MOV_H_INCLUDED
#define MOV_H_INCLUDED

#include "s_k_rpg.h"

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

#endif // MOV_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>  // Usar fontes
#include <allegro5/allegro_image.h> // Usar imagens
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h> // Renderizar fontes
#include <allegro5/keyboard.h> // Teclado
#include <stdio.h>
int TELA_ALTURA = 480;
int TELA_LARGURA = 480;
int mapa = 1;

int main() {

  al_init();
  al_init_font_addon();
  al_init_image_addon();
  al_install_keyboard();

  ALLEGRO_DISPLAY *display = al_create_display(TELA_LARGURA, TELA_ALTURA);
  al_set_window_position(display, 200, 200);
  ALLEGRO_FONT *font = al_create_builtin_font();
  ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);
  ALLEGRO_BITMAP *knight = al_load_bitmap("./images/Chars/actor9.png");
  ALLEGRO_BITMAP *villa = al_load_bitmap("./images/Mapas/villa2.png");
  ALLEGRO_BITMAP *villa2 = al_load_bitmap("./images/Mapas/villa3.1.png");
  

  ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_start_timer(timer);

  int xknight = 0, yknight = 0;
  float frame = 0.f;
  int current_frame_y = 0;

  while (true) {

    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    ////////////////////////Inicialização//////////////////////////////////////////////

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      break;
    }else if( event.keyboard.keycode == ALLEGRO_KEY_S ){
      current_frame_y = 32 * 0;
      yknight += 1;
    }else if( event.keyboard.keycode == ALLEGRO_KEY_A ){
      current_frame_y = 32 * 1;
      xknight -= 1;
    }else if( event.keyboard.keycode == ALLEGRO_KEY_D ){
      current_frame_y = 32 * 2;
       xknight += 1;
    }else if( event.keyboard.keycode == ALLEGRO_KEY_W ){
      current_frame_y = 32 * 3;
      yknight -= 1;
    }

    frame += 0.3f;
    if( frame > 3){
      frame -= 3;
    }
    
    ////////////////////////CONTROLES//////////////////////////////////////////////

    if (yknight < 0) {
      yknight += 1;
    }
    if (xknight < 0) {
      yknight += 1;
    }
    if (yknight > TELA_ALTURA-32) {
      yknight -= 1;
    }
    if (xknight > TELA_LARGURA-32) {
      xknight -= 1;
    }
    ////////////////////////LIMITES DA TELA//////////////////////////////////////

    if (mapa = 1) {
      //al_clear_to_color(al_map_rgb(255, 255, 255));
      al_draw_bitmap(villa2, 0, 0, 0);
      al_draw_bitmap_region(knight, 32 * (int)frame,current_frame_y,32,32,xknight,yknight,0);
      if (yknight < 440 && yknight > 315 && xknight > 10 && xknight < 325){
        yknight += 1;
      }
      if (yknight < 190 && yknight > 10 && xknight < 355){
        xknight += 1;
      }
      if (xknight < 10 && yknight < 0 && yknight > 60){
        xknight -= 1;
      }
      ///COLISAO///
    }
    ////////////////////////Definições de mapa//////////////////////////////////////////////

    char xbposicao[50];
    char ybposicao[50];
    char nmapa[50];
    sprintf(nmapa, "mapa: é %d", mapa);
    sprintf(xbposicao, "xknight: é %d", xknight);
    sprintf(ybposicao, "yknight: é %d", yknight);

    al_draw_text(font, al_map_rgb(0, 0, 0), 0, 10, 0, xbposicao);
    al_draw_text(font, al_map_rgb(0, 0, 0), 0, 20, 0, ybposicao);
    al_draw_text(font, al_map_rgb(0, 0, 0), 0, 30, 0, nmapa);
    al_flip_display();
    ////////////////////////EXIBIR CORDENADAS//////////////////////////////////////////////
  }
  al_destroy_font(font);
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
  al_destroy_bitmap(knight);
  al_destroy_bitmap(villa);
  //Encerrando
  return 0;
}




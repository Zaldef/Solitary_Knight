#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>  // Usar fontes
#include <allegro5/allegro_image.h> // Usar imagens
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h> // Renderizar fontes
#include <allegro5/keyboard.h> // Teclado
#include <stdio.h>
int TELA_ALTURA = 640;
int TELA_LARGURA = 640;
int mapa_X = 2560;
int mapa_Y = 2560;

int main() {

  al_init();
  al_init_font_addon();
  al_init_image_addon();
  al_install_keyboard();

  ALLEGRO_DISPLAY *display = al_create_display(TELA_LARGURA, TELA_ALTURA);
  al_set_window_position(display, 50, 50);
  ALLEGRO_FONT *font = al_create_builtin_font();
  ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
  ALLEGRO_BITMAP *knight = al_load_bitmap("./images/Chars/actor9.png");
  ALLEGRO_BITMAP *mapa = al_load_bitmap("./images/Mapas/mapa1.png");
  

  ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_start_timer(timer);
  
  int xknight = 32, yknight = 32; 
  int xmapa = 0, ymapa = 0;
  float frame = 0.f;
  int current_frame_y = 0;

  while (true) {

    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    ////////////////////////Inicialização//////////////////////////////////////////////

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      break;
    }else if( event.keyboard.keycode == ALLEGRO_KEY_S){
      current_frame_y = 32 * 0;
      yknight += 32;
    }else if( event.keyboard.keycode == ALLEGRO_KEY_A){
      current_frame_y = 32 * 1;
      xknight -= 32;
    }else if( event.keyboard.keycode == ALLEGRO_KEY_D){
      current_frame_y = 32 * 2;
      xknight += 32;
    }else if( event.keyboard.keycode == ALLEGRO_KEY_W){
      current_frame_y = 32 * 3;
      yknight -= 32;
    }

    frame += 0.3f;
    if( frame > 3){
      frame -= 3;
    }
    
    ////////////////////////CONTROLES//////////////////////////////////////////////

    if (yknight < 0) {
      ymapa += 640;
      yknight = 640;
    }
    if (xknight < 0) {
      xmapa += 640;
      xknight = 640;
    }
    if (yknight > TELA_ALTURA-32){
      ymapa -= 640;
      yknight = 0;
    }
    if (xknight > TELA_LARGURA-32){
      xmapa -= 640;
      xknight = 0;
    }
    ////////////////////////LIMITES DA TELA & TROCA DE MAPA//////////////////////////////////////

      al_draw_bitmap(mapa, xmapa, ymapa, 0);
      al_draw_bitmap_region(knight, 32 * (int)frame,current_frame_y,32,32,xknight,yknight,0);
 
    ////////////////////////Definições de mapa//////////////////////////////////////////////

    char xkposicao[50];
    char ykposicao[50];
    char xmposicao[50];
    char ymposicao[50];

    sprintf(xkposicao, "xknight: é %d", xknight);
    sprintf(ykposicao, "yknight: é %d", yknight);
    sprintf(xmposicao, "xmapa: é %d", xmapa);
    sprintf(ymposicao, "ymapa: é %d", ymapa);

    al_draw_text(font, al_map_rgb(255, 255, 255), 0, 10, 0, xkposicao);
    al_draw_text(font, al_map_rgb(255, 255, 255), 0, 20, 0, ykposicao);
    al_draw_text(font, al_map_rgb(255, 255, 255), 0, 30, 0, xmposicao);
    al_draw_text(font, al_map_rgb(255, 255, 255), 0, 40, 0, ymposicao);
    al_flip_display();
    ////////////////////////EXIBIR CORDENADAS//////////////////////////////////////////////
  }
  al_destroy_font(font);
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
  al_destroy_bitmap(knight);
  al_destroy_bitmap(mapa);
  //Encerrando
  return 0;
}




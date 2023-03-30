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
  ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
  ALLEGRO_BITMAP *bolinha = al_load_bitmap("./images/Chars/personagem4.png");
  ALLEGRO_BITMAP *villa = al_load_bitmap("./images/Mapas/villa2.png");
  ALLEGRO_BITMAP *villa2 = al_load_bitmap("./images/Mapas/villa3.1.png");

  ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_start_timer(timer);

  int xbolinha = 0;
  int ybolinha = 0;

  int xcubo = 100;
  int ycubo = 150;

  while (true) {

    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    ////////////////////////Inicialização//////////////////////////////////////////////

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      break;
    }
    if (event.keyboard.keycode == ALLEGRO_KEY_D) {
      xbolinha += 1;
    }
    if (event.keyboard.keycode == ALLEGRO_KEY_A) {
      xbolinha -= 1;
    }
    if (event.keyboard.keycode == ALLEGRO_KEY_W) {
      ybolinha -= 1;
    }
    if (event.keyboard.keycode == ALLEGRO_KEY_S) {
      ybolinha += 1;
    }
    ////////////////////////CONTROLES//////////////////////////////////////////////

    if (ybolinha < 0) {
      ybolinha += 1;
    }
    if (xbolinha < 0) {
      ybolinha += 1;
    }
    if (ybolinha > TELA_ALTURA) {
      ybolinha -= 1;
    }
    if (xbolinha > TELA_LARGURA) {
      xbolinha -= 1;
    }
    ////////////////////////LIMITES DA TELA//////////////////////////////////////

    if (mapa = 2) {
      al_clear_to_color(al_map_rgb(255, 255, 255));
      al_draw_bitmap(villa, 0, 0, 0);
      al_draw_bitmap(bolinha, xbolinha, ybolinha, 0);
    }

    if (mapa = 1) {
      al_clear_to_color(al_map_rgb(255, 255, 255));
      al_draw_bitmap(villa2, 0, 0, 0);
      al_draw_bitmap(bolinha, xbolinha, ybolinha, 0);
      if (ybolinha < 440 && ybolinha > 315 && xbolinha > 10 && xbolinha < 325){
        ybolinha += 1;
      }
      if (ybolinha < 190 && ybolinha > 10 && xbolinha < 355){
        xbolinha += 1;
      }
      if (xbolinha < 10 && ybolinha < 0 && ybolinha > 60){
        xbolinha -= 1;
      }
      ///COLISAO///
    }
    ////////////////////////Definições de mapa//////////////////////////////////////////////

    char xbposicao[50];
    char ybposicao[50];
    char nmapa[50];
    sprintf(nmapa, "mapa: é %d", mapa);
    sprintf(xbposicao, "xbolinha: é %d", xbolinha);
    sprintf(ybposicao, "ybolinha: é %d", ybolinha);
    char xcposicao[50];
    char ycposicao[50];
    sprintf(xcposicao, "xcubo: é %d", xcubo);
    sprintf(ycposicao, "ycubo: é %d", ycubo);

    al_draw_text(font, al_map_rgb(0, 0, 0), 0, 10, 0, xbposicao);
    al_draw_text(font, al_map_rgb(0, 0, 0), 0, 20, 0, ybposicao);
    al_draw_text(font, al_map_rgb(0, 0, 0), 0, 30, 0, xcposicao);
    al_draw_text(font, al_map_rgb(0, 0, 0), 0, 40, 0, ycposicao);
    al_draw_text(font, al_map_rgb(0, 0, 0), 0, 50, 0, nmapa);
    al_flip_display();
    ////////////////////////EXIBIR CORDENADAS//////////////////////////////////////////////
  }
  al_destroy_font(font);
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
  al_destroy_bitmap(bolinha);
  al_destroy_bitmap(villa);
  //Encerrando
  return 0;
}




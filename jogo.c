
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h> // Usar fontes
#include <allegro5/allegro_ttf.h> // Renderizar fontes
#include <allegro5/allegro_image.h> // Usar imagens
#include <allegro5/keyboard.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

int main (){

  al_init();
  al_init_font_addon();
  al_init_image_addon();
  al_install_keyboard();

  ALLEGRO_DISPLAY * display = al_create_display(640,480);
  al_set_window_position(display, 200, 200);

  ALLEGRO_FONT* font = al_create_builtin_font();
  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
  ALLEGRO_BITMAP * bolinha = al_load_bitmap("./images/bolinha3.png");
  ALLEGRO_BITMAP * cubo = al_load_bitmap("./images/cubo2.png");
  


  ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();
  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_start_timer(timer);

  int xbolinha =0;
  int ybolinha=0;

  int xcubo =100;
  int ycubo =150;

  while(true){
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);

    
////////////////////////COLOÇÃO COM O CUBO//////////////////////////////////////
    if(ybolinha + 39 == ycubo && xbolinha >= 60 && xbolinha <= 245) {
      ybolinha -=1;
    }
    if(xbolinha +39  == xcubo && ybolinha >= 110 && ybolinha <= 295) {
      xbolinha -=1;
    }

    if(ybolinha + 39 == ycubo + 180 && xbolinha >= 60 && xbolinha <= 245 ) {
      ybolinha +=1;
    }

    if(xbolinha +39  == xcubo +180 && ybolinha >= 110 && ybolinha <= 295) {
      xbolinha +=1;
    }
////////////////////////COLOÇÃO COM O CUBO//////////////////////////////////////

    
////////////////////////CONTROLES//////////////////////////////////////////////
    if( event.type == ALLEGRO_EVENT_DISPLAY_CLOSE ){
      break;
    }
    if (event.keyboard.keycode == ALLEGRO_KEY_D)
    {
    xbolinha +=1;
    }
     if (event.keyboard.keycode == ALLEGRO_KEY_A)
    {
    xbolinha -=1;
    }
     if (event.keyboard.keycode == ALLEGRO_KEY_W)
    {
    ybolinha -=1;
    }
     if (event.keyboard.keycode == ALLEGRO_KEY_S)
    {
    ybolinha +=1;
    }
////////////////////////CONTROLES//////////////////////////////////////////////


////////////////////////EXIBIR CORDENADAS//////////////////////////////////////////////
    char xbposicao[50];
    char ybposicao[50];
        sprintf(xbposicao, "xbolinha: é %d", xbolinha);
        sprintf(ybposicao, "ybolinha: é %d", ybolinha);
    char xcposicao[50];
    char ycposicao[50];
        sprintf(xcposicao, "xcubo: é %d", xcubo);
        sprintf(ycposicao, "ycubo: é %d", ycubo);
////////////////////////EXIBIR CORDENADAS//////////////////////////////////////////////       

    
    

    al_clear_to_color(al_map_rgb(255,255,255));
     al_draw_bitmap(bolinha, xbolinha, ybolinha, 0);
     al_draw_bitmap(cubo, 100, 150, 0);

////////////////////////EXIBIR CORDENADAS//////////////////////////////////////////////   
     al_draw_text(font, al_map_rgb(0, 0, 0), 0, 10, 0, xbposicao);
     al_draw_text(font, al_map_rgb(0, 0, 0), 0, 20, 0, ybposicao);
     al_draw_text(font, al_map_rgb(0, 0, 0), 0, 30, 0, xcposicao);
     al_draw_text(font, al_map_rgb(0, 0, 0), 0, 40, 0, ycposicao);
 ////////////////////////EXIBIR CORDENADAS//////////////////////////////////////////////    
 
    al_flip_display();
   
  }

  al_destroy_font(font);
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
  al_destroy_bitmap(bolinha);
  al_destroy_bitmap(cubo);

  return 0;
}
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>  // Usar fontes
#include <allegro5/allegro_image.h> // Usar imagens
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h> // Renderizar fontes
#include <allegro5/keyboard.h> // Teclado
#include <stdio.h>

int main() {
  // Definições inicias do allegro
    int TELA_ALTURA = 640;
    int TELA_LARGURA = 640;

    al_init();
    al_init_font_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_init_primitives_addon();//TESTE DE MATRIZ, excluir depois

    ALLEGRO_DISPLAY *display = al_create_display(TELA_LARGURA, TELA_ALTURA);
    al_set_window_position(display, 50, 50);
    ALLEGRO_FONT *font = al_create_builtin_font();
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_BITMAP *knight = al_load_bitmap("./images/Chars/actor9.png");
    ALLEGRO_BITMAP *mapa = al_load_bitmap("./images/Mapas/mapa.png");
    ALLEGRO_BITMAP * dragon_r = al_load_bitmap("./images/Chars/dragon.png"); // sprite dragon red
    ALLEGRO_BITMAP * dragon_b = al_load_bitmap("./images/Chars/blue_dragon.png"); // sprite dragon blue
    ALLEGRO_BITMAP * menu_inicial = al_load_bitmap("./images/menu_inicial.jpg");
    ALLEGRO_COLOR cor = al_map_rgb(255, 0, 0);//TESTE DE MATRIZ, excluir depois

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
  
  // Variaveis cavaleiro
    int xknight = 160, yknight = 608; //posição inicial do cavaleiro
    int tamanho_xk = 32, tamanho_yk = 32; //tamanho do sprite
    int deslocamento = 32; // velocidade 
    float frame = 0.f;
  
  //variaveis mapa
    int xmapa = 0, ymapa = 0, map = 0; // posição do map
    int mapa_X = -1280;
    int mapa_Y = -1280;
  
  // variaveis dragoes
    float frame_d = 0.f; // frames dragão
    int current_frame_y = 0;
    int current_frame_dragon_r = 161;
    float current_frame_dragon_b = 128;
    int dragon_r_x = 235, dragon_r_y = 188, dragon_b_x = 275, dragon_b_y = 78; // posição na tela dos dragoes

  while (true) {
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    al_draw_bitmap(menu_inicial, 0, 0, 0);
    al_draw_text(font, al_map_rgb(0, 0, 0), 170, 630,0, "Pressione qualquer tecla para começar");
    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
      break;
    }
    al_flip_display();
  }
  al_destroy_bitmap(menu_inicial);
  while (true) {
    //////////Inicialização//////////
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    
    /////encerrar o executavel/////
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      break;
    }

    /////Controles do cavaleiro mais limitação de borda de mapa/////
    if (event.type == ALLEGRO_EVENT_KEY_DOWN && !event.keyboard.repeat) {
      switch (event.keyboard.keycode) {
        case ALLEGRO_KEY_S:
          if(yknight < TELA_ALTURA - tamanho_yk){
            current_frame_y = tamanho_yk * 0;
            yknight += deslocamento;
            frame += 0.3f;
            if( frame > 3){
              frame -= 3;
            }
          }
          break;
            case ALLEGRO_KEY_A:
              if(xknight > 0){
                current_frame_y = tamanho_xk * 1;
                xknight -= deslocamento;
                frame += 0.3f;
                if( frame > 3){
                   frame -= 3;
                }
              }
              break;
            case ALLEGRO_KEY_D:
                if(xknight < TELA_LARGURA - tamanho_xk){
                  current_frame_y = tamanho_xk * 2;
                  xknight += deslocamento;
                  frame += 0.3f;
                  if( frame > 3){
                    frame -= 3;
                  }
                }
                break;
            case ALLEGRO_KEY_W:
              if(yknight > 0){
                current_frame_y = tamanho_yk * 3;
                yknight -= deslocamento;
                frame += 0.3f;
                if( frame > 3){
                  frame -= 3;
                }
              }
              break;
        }
    }
    
    ///// TROCA DE MAPA /////
    if( xknight > 385 && xknight < 445 && yknight <= 0 && map == 0 ){
      xmapa -= TELA_LARGURA;
      yknight = 608;
      xknight = 288;
      map ++;
    }
    if( xknight >= 576 && xknight <= 608 && yknight <= 48 && map == 1){
      xmapa = 0;
      ymapa -= TELA_ALTURA;
      yknight = 608;
      xknight = 288;
      map ++;
    }
    
    ///// Coisas na tela /////
      al_draw_bitmap(mapa, xmapa, ymapa, 0); // Mapa
      al_draw_bitmap_region(knight, tamanho_xk * (int)frame,current_frame_y,tamanho_xk,tamanho_yk,xknight,yknight,0); // Knight
      if(map == 1){
      al_draw_bitmap_region(dragon_b, 144 * (int)frame_d, current_frame_dragon_b*2, 144, 128, dragon_b_x, dragon_b_y, 0); 
      }// dragao azul
      if(map == 2){
      al_draw_bitmap_region(dragon_r, 191 * (int)frame_d, current_frame_dragon_r*2, 191, 161, dragon_r_x, dragon_r_y, 0); 
      }// Dragon vermelho
      frame_d += 0.3f;
      if( frame_d > 3){
        frame_d -= 3;
      }
 
      al_draw_line(32, 0, 32,  640, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(64, 0, 64,  640, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(96, 0, 96,  640, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(128, 0,128 , 640,  cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(160, 0,160 , 640,  cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(192, 0,192 , 640,  cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(224, 0,224 , 640,  cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(256, 0,256 , 640,  cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(288, 0,288 , 640,  cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(320, 0,320 , 640,  cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(352, 0,352 , 640,  cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(384, 0,384 , 640,  cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(416, 0,416 , 640,  cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(448, 0,448 , 640,  cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(480, 0,480 , 640,  cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(512, 0,512 , 640,  cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(544, 0,544 , 640,  cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(576, 0,576 , 640,  cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(608, 0,608 , 640,  cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(640, 0,640 , 640,  cor, 1); //TESTE DE MATRIZ, excluir depois

      al_draw_line(0, 32,  640, 32, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(0, 64,  640, 64, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(0, 96,  640, 96, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(0,128, 640, 128, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(0,160, 640, 160, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(0,192, 640, 192, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(0,224, 640, 224, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(0,256, 640, 256, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(0,288, 640, 288, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(0,320, 640, 320, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(0,352, 640, 352, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(0,384, 640, 384, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(0,416, 640, 416, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(0,448, 640, 448, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(0,480, 640, 480, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(0,512, 640, 512, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(0,544, 640, 544, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(0,576, 640, 576, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(0,608, 640, 608, cor, 1); //TESTE DE MATRIZ, excluir depois
      al_draw_line(0,640, 640, 640, cor, 1); //TESTE DE MATRIZ, excluir depois
    ////////////////////////EXIBIR informações na tela//////////////////////////////////////////////
    char xkposicao[50];
    char ykposicao[50];
    char xmposicao[50];
    char ymposicao[50];
    char mapp[50];

    sprintf(xkposicao, "xknight: é %d", xknight);
    sprintf(ykposicao, "yknight: é %d", yknight);
    sprintf(xmposicao, "xmapa: é %d", xmapa);
    sprintf(ymposicao, "ymapa: é %d", ymapa);
    sprintf(mapp, "mapa: é %d", map);

    al_draw_text(font, al_map_rgb(255, 255, 255), 0, 10, 0, xkposicao);
    al_draw_text(font, al_map_rgb(255, 255, 255), 0, 20, 0, ykposicao);
    al_draw_text(font, al_map_rgb(255, 255, 255), 0, 30, 0, xmposicao);
    al_draw_text(font, al_map_rgb(255, 255, 255), 0, 40, 0, ymposicao);
    al_draw_text(font, al_map_rgb(255, 255, 255), 0, 50, 0, mapp);
    al_flip_display();
    
  }
  al_destroy_font(font);
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
  al_destroy_bitmap(knight);
  al_destroy_bitmap(mapa);
  al_destroy_bitmap(dragon_b);
  al_destroy_bitmap(dragon_r);
  //Encerrando
  return 0;
}
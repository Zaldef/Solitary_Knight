#include <allegro5/allegro.h> // Main biblioteca
#include <allegro5/allegro_font.h>  // Usar fontes
#include <allegro5/allegro_ttf.h> // Renderizar fontes
#include <allegro5/allegro_image.h> // Usar imagens
#include <allegro5/keyboard.h> // Teclado
#include <allegro5/allegro_primitives.h> // Desenhar formas
#include <stdio.h>

int main() {
  ///// Definições inicias do allegro /////
    //Tamanho mapa
    int TELA_ALTURA = 640;
    int TELA_LARGURA = 640;

    //Carregando bibliotecas
    al_init();
    al_init_font_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_init_primitives_addon();

    //referenciais e ponteiros
    ALLEGRO_DISPLAY *display = al_create_display(TELA_LARGURA, TELA_ALTURA);
    al_set_window_position(display, 50, 50);
    ALLEGRO_FONT *font = al_create_builtin_font();
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_BITMAP *knight[6];
    knight[0] = al_load_bitmap("./images/char_1.png");
    knight[1] = al_load_bitmap("./images/char_2.png");
    knight[2] = al_load_bitmap("./images/char_3.png");
    knight[3] = al_load_bitmap("./images/char_4.png");
    knight[4] = al_load_bitmap("./images/char_5.png");
    knight[5] = al_load_bitmap("./images/char_6.png");
    ALLEGRO_BITMAP *mapa = al_load_bitmap("./images/Mapas/mapa.png");
    ALLEGRO_BITMAP * dragon_r = al_load_bitmap("./images/Chars/dragon.png"); // sprite dragon red
    ALLEGRO_BITMAP * dragon_b = al_load_bitmap("./images/Chars/blue_dragon.png"); // sprite dragon blue
    ALLEGRO_BITMAP * menu_inicial = al_load_bitmap("./images/menu_inicial.jpg");
    ALLEGRO_BITMAP * menu_char = al_load_bitmap("./images/menu_char.jpg");

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
  
  ///// Variaveis cavaleiro /////
    int persona = 0; // knight jogado
    int xknight = 160, yknight = 608; //posição inicial do cavaleiro
    int tamanho_xk = 32, tamanho_yk = 32; //tamanho do sprite
    int deslocamento = 32; // velocidade/pixel 
    float frame = 0.f; //frames
    int current_frame_y = 0; // utilizado para atualizar o ponteiro do frame dentro da imagem
  
  ///// variaveis mapa /////
    int xmapa = 0, ymapa = 0, map = 0; // posição do map
    int mapa_X = -1280;
    int mapa_Y = -1280; // tamanho mapa 
  
  ///// variaveis dragoes /////
    float frame_d = 0.f; // frames dragão
    int current_frame_dragon_r = 161; // utilizado para atualizar o ponteiro do frame dentro da imagem
    float current_frame_dragon_b = 128; // utilizado para atualizar o ponteiro do frame dentro da imagem
    int dragon_r_x = 235, dragon_r_y = 188, dragon_b_x = 275, dragon_b_y = 78; // posição na tela dos dragoes

  ///// Variveis do retangulo no Menu_Char /////
    int x1 = 59;  //inicio do ponteiro x na tela
    int y1 = 219; // inicio do ponteiro y na tela
    int x2 = 197; //termino do ponteiro x na tela
    int y2 = 357; // termino do ponteiro y na tela
    int thickness = 5; //largura da linha

  ///// Tela inicial /////
  while (true) { 
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    al_draw_bitmap(menu_inicial, 0, 0, 0);
    al_draw_text(font, al_map_rgb(0, 0, 0), 170, 630,0, "Pressione qualquer tecla para começar");
    if (event.type == ALLEGRO_EVENT_KEY_DOWN || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
      break;
    }
    al_flip_display();
  }
  al_destroy_bitmap(menu_inicial);

  ///// Escolha char /////
  while (true) { 
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    al_draw_bitmap(menu_char, 0, 0, 0);
    float sx = 32; // inicio do ponteiro x dentro da imagem
    float sy = 0; // inicio do ponteiro y dentro da imagem
    float sw = 32; //qntd de pixels de largura inicial
    float sh = 32; //qntd de pixels de altura inicial
    float dw = 128; // qntd de pixels de largura final
    float dh = 128; // qntd de pixels de altura final
    int k = 0;
    for (int j = 0; j<2; j++)
      for (int i = 0; i < 3; i++) {
        float dx = 64 + i * 192; //inicio do ponteiro x na tela
        float dy = 224 + j * 192 ; // inicio do ponteiro y na tela
        al_draw_scaled_bitmap(knight[k],sx,sy,sw,sh,dx,dy,dw,dh,0);
        k ++;
      }
    al_draw_rectangle(x1, y1, x2, y2, al_map_rgb(255, 255, 255), thickness);
    if (event.type == ALLEGRO_EVENT_KEY_DOWN ) {
      switch (event.keyboard.keycode){
        case ALLEGRO_KEY_W:
        if(y1 == 411 && y2 == 549){
        y1  -= 192;
        y2  -= 192;
        persona -=3;
        }
        break;
        case ALLEGRO_KEY_A:
        if(x1 > 59 && x2 > 197 ){ 
        x1  -= 192;
        x2  -= 192;
        persona --;
        }
        break;
        case ALLEGRO_KEY_S:
        if(y1 == 219 && y2 == 357){
        y1  += 192;
        y2  += 192;
        persona += 3;
        }
        break;
        case ALLEGRO_KEY_D:
        if( x1 < 443 && x2 < 581){
        x1  += 192;
        x2  += 192;
        persona ++;
        }
        break;       
      }
    }

    if ( event.keyboard.keycode == ALLEGRO_KEY_ESCAPE || event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
      break;
    }
    al_flip_display();
  }
  al_destroy_bitmap(menu_char);
  ///// loop principal game /////
  while (true) {
    /////Inicialização/////
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    
    /////encerrar o executavel/////
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
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
      al_draw_bitmap_region(knight[persona], tamanho_xk * (int)frame,current_frame_y,tamanho_xk,tamanho_yk,xknight,yknight,0); // Knight
      // dragao azul
      if(map == 1){
      al_draw_bitmap_region(dragon_b, 144 * (int)frame_d, current_frame_dragon_b*2, 144, 128, dragon_b_x, dragon_b_y, 0); 
      }
      // Dragon vermelho
      if(map == 2){
      al_draw_bitmap_region(dragon_r, 191 * (int)frame_d, current_frame_dragon_r*2, 191, 161, dragon_r_x, dragon_r_y, 0); 
      }
      // animação dragão
      frame_d += 0.3f;
      if( frame_d > 3){
        frame_d -= 3;
      }
 
    ////////////////////////EXIBIR informações na tela//////////////////////////////////////////////
    char xkposicao[50];
    char ykposicao[50];


    sprintf(xkposicao, "xknight: é %d", xknight);
    sprintf(ykposicao, "yknight: é %d", yknight);


    al_draw_text(font, al_map_rgb(255, 255, 255), 0, 10, 0, xkposicao);
    al_draw_text(font, al_map_rgb(255, 255, 255), 0, 20, 0, ykposicao);

    al_flip_display();
    
  }
  ///// Encerrando /////
  al_destroy_font(font);
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
  al_destroy_bitmap(knight[persona]);
  al_destroy_bitmap(mapa);
  al_destroy_bitmap(dragon_b);
  al_destroy_bitmap(dragon_r);
  return 0;
}
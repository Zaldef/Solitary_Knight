#ifndef S_K_RPG_H_INCLUDED
#define S_K_RPG_H_INCLUDED

//Aqui estão definidas as bibliotecas do jogo
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h> // Usar fontes
#include <allegro5/allegro_ttf.h> // Renderizar fontes
#include <allegro5/allegro_image.h> // Usar imagens
#include <allegro5/keyboard.h> // Usar keyboard

    //INICIAR JOGO COM ALLEGRO
    void inicializar_jogo();

    //MOVIMENTAÇÃO DO DRAGÃO
   void mover_dragon();

#endif // S_K_RPG_H_INCLUDED

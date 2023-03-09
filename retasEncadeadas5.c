#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

const int TELA_LARGURA = 640;
const int TELA_ALTURA = 480;

int main(void)
{
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *listaEventos;
    ALLEGRO_EVENT evento;
    ALLEGRO_COLOR cor;
    int x1, y1, x2, y2;
    int vermelho, verde, azul;

    // inicialização do allegro
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar allegro!\n");
        return -1;
    }

    // inicialização do complemento "primitives"
    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "Falha ao inicializar complemento primitives!\n");
        return -1;
    }

    // criação da tela
    display = al_create_display(TELA_LARGURA, TELA_ALTURA);
    if (!display)
    {
        fprintf(stderr, "Falha ao criar display!\n");
        return -1;
    }

    // indicação do bitmap alvo
    al_set_target_bitmap(al_get_backbuffer(display));

    // criação de lista de eventos
    listaEventos = al_create_event_queue();
    if (!listaEventos)
    {
        fprintf(stderr, "Falha ao criar listaEventos!\n");
        al_destroy_display(display);
        return -1;
    }

    // registro da tela como fonte de eventos junto à lista de eventos
    al_register_event_source(listaEventos, al_get_display_event_source(display));

    // inicialização do gerador de números pseudo-aleatórios
    srand(time(NULL));

    // limpeza da tela com a cor branca
    al_clear_to_color(al_map_rgb(255, 255, 255));

    // definição de coordenadas de uma posição na tela, de forma aleatória
    x2 = 10 + rand() % (TELA_LARGURA - 20);
    y2 = 10 + rand() % (TELA_ALTURA - 20);

    // laço principal
    while (true)
    {
        // saída do laço quando da ocorrência de um evento de tela
        if (al_peek_next_event(listaEventos, &evento)) break;

        /* segunda extremidade da reta anterior
           passa ser a primeira da nova reta */
        x1 = x2;
        y1 = y2;

        // definição de uma nova posição aleatória
        x2 = 10 + rand() % (TELA_LARGURA - 20);
        y2 = 10 + rand() % (TELA_ALTURA - 20);

        // definição de uma cor, de forma aleatória
        vermelho = rand() % 256;
        verde = rand() % 256;
        azul = rand() % 256;
        cor = al_map_rgb(vermelho, verde, azul);

        // traçado da reta
        al_draw_line(x1, y1, x2, y2, cor, 5.0);

        // apresentação do traçado
        al_flip_display();

        // congelamento da execução do programa por meio segundo
        al_rest(0.5);
    }

    // liberação de recursos alocados
    al_destroy_display(display);
    al_destroy_event_queue(listaEventos);

    return 0;
}

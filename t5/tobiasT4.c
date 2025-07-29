#include "tela.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define TEMPO_MAX 50
typedef struct
{
    int r;
    int g;
    int b;
} Cor;
typedef struct
{
    float pontuacao;
    char nome[50];
} Jogador;
/// era para usar as funÃÂ§ÃÂµes de tela.h
// Corrigido, mantive anteriormente as funÃ§Ãµes pois percebi que aquelas que eu iria usar
// nao haviam sido alteradas
void imprime_quadrados(Cor cor0, Cor cor_user)
{
    int i, n = 9;
    for (i = 0; i < n; i++)
    {
        tela_posiciona((posicao){(2 + i), 35});
        cor cor_fundo0 = {cor0.r, cor0.g, cor0.b};
        tela_cor_fundo(cor_fundo0);
        printf("                  ");
        tela_cor_normal();
        printf("  -----  ");
        cor cor_fundo_user = {cor_user.r, cor_user.g, cor_user.b};
        tela_cor_fundo(cor_fundo_user);
        printf("                  ");
        tela_cor_normal();
        printf("\n");
    }
}
void listra_r(Cor cor0, Cor cor_user)
{
    tela_posiciona((posicao){12, 23});
    cor cor_vermelha = {255, 0, 0};
    tela_cor_letra(cor_vermelha);
    printf("R: %d", cor_user.r);
    tela_posiciona((posicao){12, 30});
    int i;
    for (i = 0; i < 255; i += 4)
    {
        cor cor_fundo_i = {i, 0, 0};
        tela_cor_fundo(cor_fundo_i);
        if (cor_user.r == i || cor_user.r == (i + 1) || cor_user.r == (i + 2) || cor_user.r == (i + 3))
        {
            cor cor_branca = {255, 255, 255};
            tela_cor_fundo(cor_branca);
            if (cor0.r > cor_user.r)
            {
                printf(">");
            }
            else if (cor0.r < cor_user.r)
            {
                printf("<");
            }
            else
            {
                printf(" ");
            }
        }
        else
        {
            printf(" ");
        }
    }
    printf("\n");
    tela_cor_normal();
}
void listra_g(Cor cor0, Cor cor_user)
{
    tela_posiciona((posicao){14, 23});
    cor cor_verde = {0, 255, 0};
    tela_cor_letra(cor_verde);
    printf("G: %d", cor_user.g);
    tela_posiciona((posicao){14, 30});
    int i;
    for (i = 0; i < 255; i += 4)
    {
        cor cor_fundo_i = {0, i, 0};
        tela_cor_fundo(cor_fundo_i);
        if (cor_user.g == i || cor_user.g == (i + 1) || cor_user.g == (i + 2) || cor_user.g == (i + 3))
        {
            cor cor_branca = {255, 255, 255};
            tela_cor_fundo(cor_branca);
            if (cor0.g > cor_user.g)
            {
                printf(">");
            }
            else if (cor0.g < cor_user.g)
            {
                printf("<");
            }
            else
            {
                printf(" ");
            }
        }
        else
        {
            printf(" ");
        }
    }
    printf("\n");
    tela_cor_normal();
}
void listra_b(Cor cor0, Cor cor_user)
{
    tela_posiciona((posicao){16, 23});
    cor cor_azul = {0, 0, 255};
    tela_cor_letra(cor_azul);
    printf("B: %d", cor_user.b);
    tela_posiciona((posicao){16, 30});
    int i;
    for (i = 0; i < 255; i += 4)
    {
        cor cor_fundo_i = {0, 0, i};
        tela_cor_fundo(cor_fundo_i);
        if (cor_user.b == i || cor_user.b == (i + 1) || cor_user.b == (i + 2) || cor_user.b == (i + 3))
        {
            cor cor_branca = {255, 255, 255};
            tela_cor_fundo(cor_branca);
            if (cor0.b > cor_user.b)
            {
                printf(">");
            }
            else if (cor0.b < cor_user.b)
            {
                printf("<");
            }
            else
            {
                printf(" ");
            }
        }
        else
        {
            printf(" ");
        }
    }
    printf("\n");
    tela_cor_normal();
}
float pontuacao_rodada(Cor cor0, Cor cor_user)
{
    float dr, dg, db, dt, res;
    dr = fabs((cor0.r - cor_user.r));
    dg = fabs((cor0.g - cor_user.g));
    db = fabs((cor0.b - cor_user.b));
    dt = dr + dg + db;
    res = 100 - ((dt * 100) / 765);

    return res;
}
void ordena_vetor(Jogador vetor[], int tam)
{
    int i, j;
    Jogador aux;

    for (i = 0; i < tam - 1; i++)
    {
        for (j = 0; j < tam - 1 - i; j++)
        {
            if (vetor[j].pontuacao < vetor[j + 1].pontuacao)
            {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}
int le_arquivo(Jogador jogadores[])
{
    int partidas = 0;
    FILE *arquivo = fopen("jogadores.txt", "r");
    if (arquivo == NULL)
    {
        arquivo = fopen("jogadores.txt", "w");
    }
    while (fscanf(arquivo, "Nome: %[^,], Pontuacao: %f\n", jogadores[partidas].nome, &jogadores[partidas].pontuacao) == 2)
    {
        partidas++;
        if (partidas >= 100)
        {
            break;
        }
    }
    return partidas;
}
void salva_arquivo(Jogador jogadores[], int partidas)
{
    int i;
    FILE *arquivo = fopen("jogadores.txt", "w");
    for (i = 0; i < partidas; i++)
    {
        fprintf(arquivo, "Nome: %s, Pontuacao: %f\n", jogadores[i].nome, jogadores[i].pontuacao);
    }
    fclose(arquivo);
}
void podium_e_continuar(Jogador vetor[], int num_jogadores, int *continuar)
{
    tela_posiciona((posicao){13, 0});
    printf("        ______________________________\n");
    printf("             PODIUM DE JOGADORES\n");
    printf("        ______________________________\n\n");
    int i;
    for (i = 0; i < num_jogadores; i++)
    {
        printf("\t%d - %s - %.2f\n", i + 1, vetor[i].nome, vetor[i].pontuacao);
    }

    printf("\nPara sair digite 0, para continuar jogando digite 1:\n");
    scanf("%d", continuar);
    tela_limpa();
    tela_posiciona((posicao){0, 0});
}
void calcula_bonus(float *points, double inicio, double tempo, int max_temp)
{
    if (tempo < max_temp)
    {
        float bonus;
        bonus = (max_temp - (tela_relogio() - inicio)) * 3;
        bonus = fabs(bonus);
        bonus = (1 + (bonus / 100));
        *points = (*points) * bonus;
    }
}
void tela_final(int *partidas, Cor cor0, Cor cor_user, Jogador jogadores[])
{
    tela_destroi();
    *partidas = *partidas + 1;
    tela_limpa();
    tela_posiciona((posicao){0, 0});
    cor cor_laranja = {240, 170, 0};
    tela_cor_letra(cor_laranja);
    printf("  ================Gameee Overr================\n\n");
    printf("  Cores originais:\n\n");
    cor cor_vermelha = {255, 0, 0};
    tela_cor_letra(cor_vermelha);
    printf("  R: %d\n", cor0.r);
    cor cor_verde = {0, 255, 0};
    tela_cor_letra(cor_verde);
    printf("  G: %d\n", cor0.g);
    cor cor_azul = {0, 0, 255};
    tela_cor_letra(cor_azul);
    printf("  B: %d", cor0.b);
    tela_cor_normal();
    tela_posiciona((posicao){3, 30});
    tela_cor_letra(cor_laranja);
    printf("Cores do usuario:");
    tela_posiciona((posicao){5, 30});
    tela_cor_letra(cor_vermelha);
    printf("R: %d", cor_user.r);
    tela_posiciona((posicao){6, 30});
    tela_cor_letra(cor_verde);
    printf("G: %d", cor_user.g);
    tela_posiciona((posicao){7, 30});
    tela_cor_letra(cor_azul);
    printf("B: %d", cor_user.b);
    tela_cor_normal();
}
void tela_jogo(Cor cor0, Cor cor_user, float *points, double *tempo, double inicio, int max_tempo)
{
    imprime_quadrados(cor0, cor_user);

    listra_r(cor0, cor_user);
    listra_g(cor0, cor_user);
    listra_b(cor0, cor_user);

    tela_posiciona((posicao){18, 50});
    *points = pontuacao_rodada(cor0, cor_user);
    printf("Pontuacao: %.2f%%\n", *points);

    *tempo = tela_relogio() - inicio;
    tela_posiciona((posicao){1, 1});
    printf("Tempo:%.1f", max_tempo - *tempo);
}
void inicializacao_cores(Cor *cor0, Cor *cor_user)
{
    cor0->r = rand() % 255;
    cor0->g = rand() % 255;
    cor0->b = rand() % 255;

    cor_user->r = 0;
    cor_user->g = 0;
    cor_user->b = 0;

    tela_cria(); // sempre tem que ser a primeira funÃÂ§ÃÂ£o de tela a ser chamada
    tela_limpa();
}
int controle(Cor *cor_user, int **controle)
{
    int tecla = tela_le_char();
    switch (tecla)
    {
    case c_left:
        if (**controle > 0)
        {
            **controle = **controle - 1;
        }
        break;
    case c_right:
        if (**controle < 255)
        {
            **controle = **controle + 1;
        }
        break;
    case c_up:
        if (*controle == &cor_user->b)
        {
            *controle = &cor_user->g;
        }
        else if (*controle == &cor_user->g)
        {
            *controle = &cor_user->r;
        }
        break;
    case c_down:
        if (*controle == &cor_user->r)
        {
            *controle = &cor_user->g;
        }
        else if (*controle == &cor_user->g)
        {
            *controle = &cor_user->b;
        }
        break;
    }
    return tecla;
}
void desenho(void)
{
    cor cor_ciano = {5, 255, 188};
    tela_cor_letra(cor_ciano);
    tela_posiciona((posicao){3, 61});
    printf("@@@@@@@@@@@@   ::       :.  ::");
    tela_posiciona((posicao){4, 61});
    printf("@@@@@@@@@@@@   @@      .@:  @@@@@@@@@@@ ");
    tela_posiciona((posicao){5, 65});
    printf("@@@        @@      .@:  @@@@@@@@@@@ ");
    tela_posiciona((posicao){6, 65});
    printf("@@@        @@      .@:  @@.      @@ ");
    tela_posiciona((posicao){7, 65});
    printf("@@@        @@      .@:  @@.      @@ ");
    tela_posiciona((posicao){8, 65});
    printf("@@@        @@      .@:  @@.      @@ ");
    tela_posiciona((posicao){9, 65});
    printf("@@@        @@@@@@@@@@:  @@#######@@ ");
    tela_posiciona((posicao){10, 65});
    printf("@@@        @@@@@@@@@@:  @@@@@@@@@@@ ");
    tela_posiciona((posicao){11, 65});
    printf("@@@                .@:  @@#######@@ ");
    tela_posiciona((posicao){12, 65});
    printf("@@@                .@:  @@.      @@ ");
    tela_posiciona((posicao){13, 65});
    printf("@@@                .@:  @@.      @@ ");
    tela_posiciona((posicao){14, 65});
    printf("@@@                .@:  @@!::::::@@ ");
    tela_posiciona((posicao){15, 65});
    printf("@@@                .@:  @@@@@@@@@@@ ");
    tela_posiciona((posicao){16, 65});
    printf("@@@                .@:  @@::::::::: ");
}
void imprime_atribui_pontuacao(float points, int *partidas, Jogador jogadores[])
{
    printf("\n\nSua pontuacao: %.2lf", points);

    char nome[50];

    printf("\n\nDigite seu nome: ");
    fflush(stdin);
    scanf(" %[^\n]", nome);
    strcpy(jogadores[*partidas - 1].nome, nome);
    jogadores[*partidas - 1].pontuacao = points;
}
void final(float points, double inicio, double tempo, int *partidas, Cor cor0, Cor cor_user, Jogador *jogadores, int *continuar)
{
    calcula_bonus(&points, inicio, tempo, TEMPO_MAX);
    tela_final(partidas, cor0, cor_user, jogadores);
    imprime_atribui_pontuacao(points, partidas, jogadores);
    desenho();
    ordena_vetor(jogadores, *partidas);
    podium_e_continuar(jogadores, *partidas, continuar);
}

int main()
{
    srand(time(0));
    Jogador jogadores[100];
    int partidas = 0, continuar = 1;
    partidas = le_arquivo(jogadores);
    do
    {
        Cor cor0, cor_user;
        inicializacao_cores(&cor0, &cor_user);
        int tecla, *cor_control = &cor_user.r;
        double inicio = tela_relogio();
        double tempo;
        float points = 0;
        do
        {
            tela_jogo(cor0, cor_user, &points, &tempo, inicio, TEMPO_MAX);
            tecla = controle(&cor_user, &cor_control);

        } while (points != 100 && tecla != c_enter && tempo < TEMPO_MAX);
        final(points, inicio, tempo, &partidas, cor0, cor_user, jogadores, &continuar);
    } while (continuar == 1);
    salva_arquivo(jogadores, partidas);
    tela_destroi();
}

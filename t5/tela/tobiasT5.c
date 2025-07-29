#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "tela.h"

typedef struct
{
    int pontuacao;
    char nome[50];
} Jogador;

// Declarações de funções
int botao_voltar_menu();
void desenha_rodada(char vet[5][5], int score);
int conta_movimentos_direita(char vet[]);
int conta_movimentos_esquerda(char vet[]);

//Funcoes que envolvem arquivos
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
        fclose(arquivo);
        return 0;
    }
    while (fscanf(arquivo, "Nome: %[^,], Pontuacao: %d\n", jogadores[partidas].nome, &jogadores[partidas].pontuacao) == 2)
    {
        partidas++;
        if (partidas >= 100)
        {
            break;
        }
    }
    fclose(arquivo);
    return partidas;
}
void salva_arquivo(Jogador jogadores[], int partidas)
{
    FILE *arquivo = fopen("jogadores.txt", "w");
    if (arquivo == NULL)
    {
        return;
    }
    int max_salvar = (partidas < 5) ? partidas : 5;
    for (int i = 0; i < max_salvar; i++)
    {
        fprintf(arquivo, "Nome: %s, Pontuacao: %d\n", jogadores[i].nome, jogadores[i].pontuacao);
    }
    fclose(arquivo);
}
void podium(Jogador vetor[], int num_jogadores)
{
    int voltar_btn = 0;
    while (voltar_btn == 0)
    {
        char texto[100];
        strcpy(texto, "______________________________");
        tela_texto(640, 20, 40, 1, texto);
        strcpy(texto, "TOP 5 JOGADORES");
        tela_texto(640, 65, 30, 1, texto);
        strcpy(texto, "______________________________");
        tela_texto(640, 70, 40, 1, texto);

        int max_mostrar = (num_jogadores < 5) ? num_jogadores : 5;
        for (int i = 0; i < max_mostrar; i++)
        {
            sprintf(texto, "%d - %s - %d", i + 1, vetor[i].nome, vetor[i].pontuacao);
            tela_texto(640, 150 + (i * 25), 20, 1, texto);
        }
        voltar_btn = botao_voltar_menu();
        tela_atualiza();
    }
}

//Funcoes que nao envolvem o Allegro
int conta_movimentos_direita(char vet[])
{
    int movimentos = 0;
    char vet_copia[5];
    for (int i = 0; i < 5; i++)
    {
        vet_copia[i] = vet[i];
    }
    
    for (int i = 1; i < 5; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            if (vet_copia[j] == ' ')
            {
                if (vet_copia[j - 1] != ' ')
                {
                    movimentos++;
                }
                vet_copia[j] = vet_copia[j - 1];
                vet_copia[j - 1] = ' ';
            }
        }
    }
    return movimentos;
}

int conta_movimentos_esquerda(char vet[])
{
    int movimentos = 0;
    char vet_copia[5];
    for (int i = 0; i < 5; i++)
    {
        vet_copia[i] = vet[i];
    }
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (vet_copia[j] == ' ')
            {
                if (vet_copia[j + 1] != ' ')
                {
                    movimentos++;
                }
                vet_copia[j] = vet_copia[j + 1];
                vet_copia[j + 1] = ' ';
            }
        }
    }
    return movimentos;
}

void juntar_direita(char vet[])
{
    char aux = ' ';
    int i, j;
    for (i = 1; i < 5; i++)
    {
        for (j = 1; j < 5; j++)
        {
            if (vet[j] == ' ')
            {
                vet[j] = vet[j - 1];
                vet[j - 1] = aux;
            }
        }
    }
}
void juntar_esquerda(char vet[])
{
    char aux = ' ';
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (vet[j] == ' ')
            {
                vet[j] = vet[j + 1];
                vet[j + 1] = aux;
            }
        }
    }
}
char proxima_letra(char letra)
{
    switch (letra)
    {
    case 'A':
        return 'B';
    case 'B':
        return 'C';
    case 'C':
        return 'D';
    case 'D':
        return 'E';
    case 'E':
        return 'F';
    default:
        return letra;
    }
}
int score_letra(char letra)
{
    switch (letra)
    {
    case 'A':
        return 10;
    case 'B':
        return 30;  // 3 * 10
    case 'C':
        return 90;  // 3 * 30
    case 'D':
        return 270; // 3 * 90
    case 'E':
        return 810; // 3 * 270
    default:
        return 0;
    }
}
void soma_letra_direita(char vet[], int *score)
{
    int i;
    char aux = ' ';
    char letra;
    bool combinacao_feita = true;
    
    while (combinacao_feita)
    {
        combinacao_feita = false;
        for (i = 4; i >= 2; i--)
        {
            if (vet[i] != ' ' && vet[i] == vet[i-1] && vet[i] == vet[i-2])
            {
                letra = vet[i];
                vet[i-2] = proxima_letra(letra);
                vet[i-1] = aux;
                vet[i] = aux;
                *score = *score + score_letra(letra);
                combinacao_feita = true;
                break;
            }
        }
        if (combinacao_feita)
        {
            juntar_direita(vet);
        }
    }
}
void soma_letra_esquerda(char vet[], int *score)
{
    int i;
    char aux = ' ';
    char letra;
    bool combinacao_feita = true;
    
    while (combinacao_feita)
    {
        combinacao_feita = false;
        for (i = 0; i <= 2; i++)
        {
            if (vet[i] != ' ' && vet[i] == vet[i+1] && vet[i] == vet[i+2])
            {
                letra = vet[i];
                vet[i] = proxima_letra(letra);
                vet[i+1] = aux;
                vet[i+2] = aux;
                *score = *score + score_letra(letra);
                combinacao_feita = true;
                break;
            }
        }
        if (combinacao_feita)
        {
            juntar_esquerda(vet);
        }
    }
}
void horizontaliza_vet(char vet[5][5], char aux[], int j)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        aux[i] = vet[i][j];
    }
}
void verticaliza_vet(char vet[5][5], char aux[], int j)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        vet[i][j] = aux[i];
    }
}
void extrai_linha(char vet[5][5], char aux[], int j)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        aux[i] = vet[j][i];
    }
}
void devolve_linha(char vet[5][5], char aux[], int j)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        vet[j][i] = aux[i];
    }
}
char sorteia_letra()
{
    char letras[4] = {'A', 'A', 'A', 'B'};
    int i = rand() % 4;
    return letras[i];
}
void sorteia_lugar_letra(char vet[5][5])
{
    int linha, coluna;
    int cont = 0;
    int posicoes_livres[25][2];
    
    for (int lin = 0; lin < 5; lin++)
    {
        for (int col = 0; col < 5; col++)
        {
            if (vet[lin][col] == ' ')
            {
                posicoes_livres[cont][0] = lin;
                posicoes_livres[cont][1] = col;
                cont++;
            }
        }
    }
    
    if (cont > 0)
    {
        int indice = rand() % cont;
        linha = posicoes_livres[indice][0];
        coluna = posicoes_livres[indice][1];
        vet[linha][coluna] = sorteia_letra();
    }
}
void exibe_matriz(char vet[5][5])
{
    int i, j;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            printf("%c", vet[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
int manipulacao_matriz(char vet[5][5])
{
    char aux[5];
    int j, score = 0;
    int tecla;
    do
    {
        tecla = tela_tecla();
    } while (tecla == c_none);
    switch (tecla)
    {
    case c_right:
        for (j = 0; j < 5; j++)
        {
            extrai_linha(vet, aux, j);
            score += conta_movimentos_direita(aux);
            juntar_direita(aux);
            soma_letra_direita(aux, &score);
            devolve_linha(vet, aux, j);
        }
        break;
    case c_left:
        for (j = 0; j < 5; j++)
        {
            extrai_linha(vet, aux, j);
            score += conta_movimentos_esquerda(aux);
            juntar_esquerda(aux);
            soma_letra_esquerda(aux, &score);
            devolve_linha(vet, aux, j);
        }
        break;
    case c_down:
        for (j = 0; j < 5; j++)
        {
            horizontaliza_vet(vet, aux, j);
            score += conta_movimentos_direita(aux);
            juntar_direita(aux);
            soma_letra_direita(aux, &score);
            verticaliza_vet(vet, aux, j);
        }
        break;
    case c_up:
        for (j = 0; j < 5; j++)
        {
            horizontaliza_vet(vet, aux, j);
            score += conta_movimentos_esquerda(aux);
            juntar_esquerda(aux);
            soma_letra_esquerda(aux, &score);
            verticaliza_vet(vet, aux, j);
        }

        break;
    default:
        break;
    }
    return score;
}
void salvar_matriz(char vet[5][5], char vet_anterior[5][5])
{
    memcpy(vet_anterior, vet, 5 * 5);
}
bool compara_matriz(char vet[5][5], char vet_anterior[5][5])
{
    return memcmp(vet_anterior, vet, 5 * 5) != 0;
}
int verifica_fim(char vet[5][5])
{
    int i, j;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (vet[i][j] == 'F')
            {
                return 2;
            }
        }
    }
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (vet[i][j] == ' ')
            {
                return 0;
            }
            if (j < 3)
            {
                if (vet[i][j] == vet[i][j + 1] && vet[i][j] == vet[i][j + 2])
                {
                    return 0;
                }
            }
        }
        for (j = 0; j < 5; j++)
        {
            if (vet[j][i] == ' ')
            {
                return 0;
            }
            if (j < 3)
            {
                if (vet[j][i] == vet[j + 1][i] && vet[j][i] == vet[j + 2][i])
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}
int cor_letra(char letra)
{
    switch (letra)
    {
    case 'A':
        return 7;
    case 'B':
        return 1;
    case 'C':
        return 3;
    case 'D':
        return 4;
    case 'E':
        return 6;
    case 'F':
        return 2;
    default:
        return 0;
    }
}

//Funcoes que envolvem o Allegro
void desenha_quadrado()
{
    int i, j;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            int ex = 110 * j + 360;
            int ey = 110 * i + 90;
            tela_retangulo(ex, ey, ex + 100, ey + 100, 5, 8, 80);
        }
    }
}
void desenha_matriz(char vet[5][5])
{
    int i, j;
    char letra[1];
    char cor;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            cor = vet[i][j];
            int ex = 110 * j + 360 + 50;
            int ey = 110 * i + 90 + 45;
            letra[0] = vet[i][j];
            tela_texto(ex, ey, 80, cor_letra(cor), letra);
        }
    }
}
void desenha_score(int score)
{
    char texto[20];
    sprintf(texto, "Score: %d", score);
    tela_texto(640, 20, 40, 3, texto);
}
void desenha_voce_ganhou()
{
    char texto[50];
    strcpy(texto, "Parabens, voce venceu!!!");
    tela_texto_dir(10, 20, 25, 3, texto);
}
void desenha_voce_perdeu()
{
    char texto[50];
    strcpy(texto, "Parabens, voce perdeu :(");
    tela_texto_dir(10, 20, 25, 2, texto);
}
void desenha_menu(char jogar[], char ranking[], char sair[], char texto[], float ex, float ey)
{
    strcpy(texto, "EFE By Tobias");
    tela_texto(640, 55, 40, 1, texto);
    strcpy(texto, "______________________________");
    tela_texto(640, 75, 40, 1, texto);
    ex = tela_rato_x();
    ey = tela_rato_y();
    if ((ex > 590 && ex < 690) && (ey > 230 && ey < 270))
    {
        tela_texto(640, 250, 30, 8, jogar);
    }
    else
    {
        tela_texto(640, 250, 30, 1, jogar);
    }

    if ((ex > 590 && ex < 690) && (ey > 320 && ey < 360))
    {
        tela_texto(640, 340, 30, 8, ranking);
    }
    else
    {
        tela_texto(640, 340, 30, 1, ranking);
    }

    if ((ex > 590 && ex < 690) && (ey > 410 && ey < 450))
    {
        tela_texto(640, 430, 30, 8, sair);
    }
    else
    {
        tela_texto(640, 430, 30, 1, sair);
    }
    tela_atualiza();
}
int verifica_clique_menu(float ex, float ey)
{
    tela_rato_clicado();
    ex = tela_rato_x_clique();
    ey = tela_rato_y_clique();
    if ((ex > 590 && ex < 690) && (ey > 230 && ey < 270))
    {
        return 1;
    }
    else if ((ex > 590 && ex < 690) && (ey > 320 && ey < 360))
    {
        return 2;
    }
    else if ((ex > 590 && ex < 690) && (ey > 410 && ey < 450))
    {
        return 3;
    }
    return 0;
}
int botao_voltar_menu()
{
    float ex = 0, ex_c = 0;
    float ey = 0, ey_c = 0;
    char voltar[20];

    strcpy(voltar, "Menu");
    tela_texto(1150, 630, 30, 1, voltar);
    ex = tela_rato_x();
    ey = tela_rato_y();
    if ((ex > 1100 && ex < 1200) && (ey > 610 && ey < 650))
    {
        tela_texto(1150, 630, 30, 8, voltar);
    }

    tela_rato_clicado();
    ex_c = tela_rato_x_clique();
    ey_c = tela_rato_y_clique();
    if ((ex_c > 1100 && ex_c < 1200) && (ey_c > 610 && ey_c < 650))
    {
        return 1;
    }
    return 0;
}
int menu()
{
    char jogar[20], ranking[20], sair[20], texto[100];
    strcpy(jogar, "Jogar");
    strcpy(ranking, "Ranking");
    strcpy(sair, "Sair");
    float ex = 0, ey = 0;
    int menu = 0;
    while (menu == 0)
    {
        desenha_menu(jogar, ranking, sair, texto, ex, ey);
        menu = verifica_clique_menu(ex, ey);
    }
    return menu;
}
int escreve_tela(int tecla, char nome[50], int *i)
{
    tecla = tela_tecla();
    if ((tecla > 96 && tecla < 123) || (tecla > 64 && tecla < 91) || (tecla == 32))
    {
        if (*i < 49)
        {
            nome[*i] = tecla;
            *i = *i + 1;
        }
    }
    else if (tecla == c_back && *i > 0)
    {
        nome[*i - 1] = '\0';
        *i = *i - 1;
    }
    return tecla;
}
void tela_final_perdeu(char vet[5][5], int score, int partidas, Jogador *jogadores)
{
    char texto[50];
    char nome[50] = {0};
    int tecla = 0, i = 0;
    strcpy(texto, "Digite seu nome: ");
    tela_texto_dir(18, 55, 15, 9, texto);
    while (tecla != c_enter)
    {
        tecla = escreve_tela(tecla, nome, &i);
        desenha_voce_perdeu();
        desenha_rodada(vet, score);
        strcpy(texto, "Digite seu nome: ");
        tela_texto_dir(18, 55, 20, 9, texto);
        tela_texto_dir(200, 55, 20, 9, nome);
        tela_atualiza();
    }
    jogadores[partidas].pontuacao = score;
    strcpy(jogadores[partidas].nome, nome);
}
void tela_final_ganhou(char vet[5][5], int score, int partidas, Jogador *jogadores)
{
    char texto[50];
    char nome[50] = {0};
    int tecla = 0, i = 0;
    strcpy(texto, "Digite seu nome: ");
    tela_texto_dir(18, 55, 15, 9, texto);
    while (tecla != c_enter)
    {
        tecla = escreve_tela(tecla, nome, &i);
        desenha_voce_ganhou();
        desenha_rodada(vet, score);
        strcpy(texto, "Digite seu nome: ");
        tela_texto_dir(18, 55, 20, 9, texto);
        tela_texto_dir(200, 55, 20, 9, nome);
        tela_atualiza();
    }
    jogadores[partidas].pontuacao = score;
    strcpy(jogadores[partidas].nome, nome);
}
void desenha_rodada(char vet[5][5], int score)
{
    desenha_quadrado();
    desenha_matriz(vet);
    desenha_score(score);
}
void jogo(char vet[5][5], int score, int partidas, Jogador *jogadores)
{
    int fim = 0;
    char vet_anterior[5][5];
    while (true)
    {
        desenha_rodada(vet, score);
        tela_atualiza();
        fim = verifica_fim(vet);
        if (fim == 1)
        {
            tela_final_perdeu(vet, score, partidas, jogadores);
            break;
        }
        if (fim == 2)
        {
            tela_final_ganhou(vet, score, partidas, jogadores);
            break;
        }
        salvar_matriz(vet, vet_anterior);
        score += manipulacao_matriz(vet);
        if (compara_matriz(vet, vet_anterior))
        {
            sorteia_lugar_letra(vet);
        }
    }
}
void inicializa_jogo(int *partidas, Jogador *jogadores)
{
    int score=0;
    char vet[5][5] = {{' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' '}};
    sorteia_lugar_letra(vet);
    sorteia_lugar_letra(vet);
    jogo(vet, score, *partidas, jogadores);
    
    if (*partidas >= 5) {
        ordena_vetor(jogadores, 5);
        if (jogadores[*partidas].pontuacao > jogadores[4].pontuacao) {
            jogadores[4] = jogadores[*partidas];
        }
        ordena_vetor(jogadores, 5);
        *partidas = 5;
    } else {
        *partidas = *partidas + 1;
        ordena_vetor(jogadores, *partidas);
    }
    
    int max_mostrar = (*partidas < 5) ? *partidas : 5;
    podium(jogadores, max_mostrar);
}
int main()
{
    tela_inicio(1280, 720, "x");
    srand(time(NULL));
    Jogador jogadores[100];
    int partidas = 0, sair = 0;
    partidas = le_arquivo(jogadores);
    while (sair != 1)
    {
        switch (menu())
        {
        case 1:
            inicializa_jogo(&partidas, jogadores);
            break;
        case 2:
            podium(jogadores, partidas);
            break;
        case 3:
            sair = 1;
        default:
            break;
        }
    }
    salva_arquivo(jogadores, partidas);
    tela_fim();
}

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define XAXIS 10
#define YAXIS 10
#define FLAG 241
#define EMPTY 'x'
#define BOMB 254
#define ALLBOMBS 10
#define SECONDSINHOUR 3600
#define SECONDSINMINUTE 60

typedef struct{
    int x;
    char y, acao;
} Jogada;

typedef struct{
    int isMarked, hasBomb, isDescovered, position[2], number;
} Cell;

Cell tabuleiro[XAXIS][YAXIS];
int flags=0;

void menu ();
void header ();
void imprime_tabuleiro ();
int jogar (Jogada jogada, int alive);
int vencer (int ganhou);
void inicializar_tabuleiro();
void revelar_cell (int y, int x);
void revelar_number (int y, int x);
void clean_stdin();

int main(){
    Jogada jogada;
    int alive=1, ganhou=0;

    menu();
    inicializar_tabuleiro();
    // as próximas 2 linhas existem pq o jogo praticamente não funciona sem elas
    for (int i=0; i<YAXIS; i++){
    }

    while(alive && flags<ALLBOMBS){
        alive=jogar(jogada, alive);
    }
    ganhou=vencer(ganhou);
    if (ganhou && alive){
        printf("Parabens voce ganhou!");
    } else {
        printf("Infelizmente nao foi dessa vez.");
    }
    return 0;
}

void menu (){
    printf("Seja bem-vindo ao Campo Minado!");
    printf("\nEste jogo funciona com o sistema de coordenadas");
    printf("\nentao voce escolhera um numero (1..10), depois uma letra(A..J)");
    printf("\ndepois a acao que devera ser feita, cavar (c) ou marcar (m).");
    printf("\n\nAntes de comecar, algumas padronizacoes:");
    printf("\nBandeirinha: %c", FLAG);
    printf("\nVazio: %c", EMPTY);
    printf("\nBomba: %c", BOMB);
    printf("\n\nAperte qualquer tecla para continuar..");
    getch();
    system("cls");
    /* Caso você esteja no Linux, favor descomentar as linhas e comentar as 2 de cima
    system("read a; clear");
    */
}

void header (){
    int hours,minutes,seconds;
    int remainingSeconds;
    int time_in_seconds = (double)clock() / (double)CLOCKS_PER_SEC;
    hours = (time_in_seconds/SECONDSINHOUR);
    remainingSeconds = time_in_seconds - (hours * SECONDSINHOUR);
    minutes = remainingSeconds/SECONDSINMINUTE;
    remainingSeconds = remainingSeconds - (minutes*SECONDSINMINUTE);
    seconds = remainingSeconds;
    printf("time %d:%d:%d\t\t\t\t\t\t\t\t\t\t\t\tmines:%d/%d\n",hours,minutes,seconds, flags, ALLBOMBS);
    for (int i=0; i<120; i++){
            printf("%c",196);
    }
    printf("\n");
}

void inicializar_tabuleiro(){
    int countBombs;
    for (int i=0; i<YAXIS; i++){
        for (int j=0; j<XAXIS; j++){
            if(rand() % 2 == 0){
                tabuleiro[i][j].hasBomb=0;
            }else {
                if(ALLBOMBS>countBombs){
                    tabuleiro[i][j].hasBomb=1;
                    countBombs++;
                }
            }
            tabuleiro[i][j].isDescovered=0;
            tabuleiro[i][j].isMarked=0;
            tabuleiro[i][j].position[0]=i;
            tabuleiro[i][j].position[1]=j;
            tabuleiro[i][j].number=0;
        }
    }
}

void imprime_tabuleiro (){
    header();
    printf(" ");
    for (int j=1; j<=XAXIS; j++){
        printf(" ");
        printf("%d", j);
    }
    printf("\n");
    char k='A';
    for (int i=0; i<YAXIS; i++){
        printf("%c",k);
        k++;
        printf(" ");
        for (int j=0; j<XAXIS; j++){
            if (tabuleiro[i][j].isDescovered==0){
                if (tabuleiro[i][j].isMarked==0){
                    printf("*");
                }else {
                    printf("%c", FLAG);
                }
            }else {
                if (tabuleiro[i][j].number>0){
                    if (tabuleiro[i][j].hasBomb==0){
                        printf("%d", tabuleiro[i][j].number);
                    }
                }else {
                    printf("%c", EMPTY);
                }
            }
            printf(" ");
        }
        printf("\n");
    }
}

int jogar(Jogada jogada, int alive) {
    imprime_tabuleiro();
    printf("\n\nSelecione um numero para marcar ou cavar entre 1 e 10: ");
    scanf("%d", &jogada.x);
    jogada.x -= 1;

    clean_stdin();
    printf("\n\nSelecione uma letra para marcar ou cavar entre A e J: ");
    scanf("%c", &jogada.y);
    jogada.y = toupper(jogada.y);

    clean_stdin();
    printf("\n\nSelecione uma acao marcar (m) ou cavar (c): ");
    scanf("%c", &jogada.acao);
    jogada.acao = toupper(jogada.acao);

    if (jogada.acao=='C'){
        if(tabuleiro[jogada.y - 'A'][jogada.x].hasBomb){
            printf("\n\nFim de jogo");
            alive=0;
        }else {
            revelar_cell(jogada.y - 'A', jogada.x);
        }
    } else {
        flags++;
        tabuleiro[jogada.y - 'A'][jogada.x].isMarked = 1;
    }
    system("cls");
    return alive;
}

void revelar_cell (int y, int x) {
    tabuleiro[y][x].isDescovered = 1;

     for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++){

            int posX = x + j,
                posY = y + i;

            if (posX < 0 || posY < 0 || posX >= XAXIS || posY >= YAXIS) {
                continue;
            }

            if (!tabuleiro[posY][posX].isDescovered) {
                if (tabuleiro[posY][posX].hasBomb) {
                    tabuleiro[y][x].number++;
                } else {
                    revelar_cell(posY, posX);
                }
            }
        }
     }
}

int vencer (int ganhou){
    int certo=0;
    for (int i=0; i<YAXIS; i++){
        for (int j=0; j<XAXIS; j++){
            if(tabuleiro[i][j].hasBomb && tabuleiro[i][j].isMarked){
                printf("%d%d\n", tabuleiro[i][j].position[0], tabuleiro[i][j].position[1]);
                certo++;
            }
        }
    }
    if (certo == ALLBOMBS){
        ganhou=1;
    }
    return ganhou;
}


void clean_stdin() {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

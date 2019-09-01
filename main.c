#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

#define XAXIS 10
#define YAXIS 10
#define FLAG 241
#define EMPTY 176
#define BOMB 254
#define ALLBOMBS 10

typedef struct{
    int x;
    char y, acao;
} Jogada;

void menu ();
void imprime_tabuleiro ();
int jogar (Jogada jogada, int alive);
void inicializar_tabuleiro();

typedef struct{
    int isMarked, hasBomb, isDescovered, position[2];
} Cell;

Cell tabuleiro[XAXIS][YAXIS];

int main(){
    Jogada jogada;
    int alive=1;

    menu();
    inicializar_tabuleiro();
    printf("\n\n");
    for (int i=0; i<YAXIS; i++){
        printf(" ");
        for (int j=0; j<XAXIS; j++){
            printf("%d",tabuleiro[i][j].hasBomb);
            printf(" ");
        }
        printf("\n");
    }
    printf("\n\n");
    while(alive==1){
        alive=jogar(jogada, alive);
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
}

void inicializar_tabuleiro(){
    for (int i=0; i<YAXIS; i++){
        for (int j=0; j<XAXIS; j++){
            if(rand() % 2 == 0){
                tabuleiro[i][j].hasBomb=0;
            }else {
                tabuleiro[i][j].hasBomb=1;
            }
            tabuleiro[i][j].isDescovered=0;
            tabuleiro[i][j].isMarked=0;
            tabuleiro[i][j].position[0]=i;
            tabuleiro[i][j].position[1]=j;
        }
    }
}

void imprime_tabuleiro (){
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
                printf("%c", EMPTY);
            }
            printf(" ");
        }
        printf("\n");
    }
}

int jogar(Jogada jogada, int alive){
    imprime_tabuleiro();
    printf("\n\nSelecione um numero para marcar ou cavar entre 1 e 10: ");
    scanf("%d", &jogada.x);

    fflush(stdin);
    printf("\n\nSelecione uma letra para marcar ou cavar entre A e J: ");
    scanf("%c", &jogada.y);

    fflush(stdin);
    printf("\n\nSelecione uma acao marcar (m) ou cavar (c): ");
    scanf("%c", &jogada.acao);

    if (jogada.acao=='c'){
        switch(toupper(jogada.y)){
        case 'A':
            if(tabuleiro[0][jogada.x-1].hasBomb==1){
                printf("\n\nFim de jogo");
                alive=0;
            } else {
                tabuleiro[0][jogada.x-1].isDescovered=1;
            }
            break;
        case 'B':
            if(tabuleiro[1][jogada.x-1].hasBomb==1){
                printf("\n\nFim de jogo");
                alive=0;
            }else {
                tabuleiro[1][jogada.x-1].isDescovered=1;
            }
            break;
        case 'C':
            if(tabuleiro[2][jogada.x-1].hasBomb==1){
                printf("\n\nFim de jogo");
                alive=0;
            }else {
                tabuleiro[2][jogada.x-1].isDescovered=1;
            }
            break;
        case 'D':
            if(tabuleiro[3][jogada.x-1].hasBomb==1){
                printf("\n\nFim de jogo");
                alive=0;
            }else {
                tabuleiro[3][jogada.x-1].isDescovered=1;
            }
            break;
        case 'E':
            if(tabuleiro[4][jogada.x-1].hasBomb==1){
                printf("\n\nFim de jogo");
                alive=0;
            }else {
                tabuleiro[4][jogada.x-1].isDescovered=1;
            }
            break;
        case 'F':
            if(tabuleiro[5][jogada.x-1].hasBomb==1){
                printf("\n\nFim de jogo");
                alive=0;
            }else {
                tabuleiro[5][jogada.x-1].isDescovered=1;
            }
            break;
        case 'G':
            if(tabuleiro[6][jogada.x-1].hasBomb==1){
                printf("\n\nFim de jogo");
                alive=0;
            }else {
                tabuleiro[6][jogada.x-1].isDescovered=1;
            }
            break;
        case 'H':
            if(tabuleiro[7][jogada.x-1].hasBomb==1){
                printf("\n\nFim de jogo");
                alive=0;
            }else {
                tabuleiro[7][jogada.x-1].isDescovered=1;
            }
            break;
        case 'I':
            if(tabuleiro[8][jogada.x-1].hasBomb==1){
                printf("\n\nFim de jogo");
                alive=0;
            }else {
                tabuleiro[8][jogada.x-1].isDescovered=1;
            }
            break;
        case 'J':
            if(tabuleiro[9][jogada.x-1].hasBomb==1){
                printf("\n\nFim de jogo");
                alive=0;
            }else {
                tabuleiro[9][jogada.x-1].isDescovered=1;
            }
            break;
        }
        }else {
            switch(toupper(jogada.y)){
            case 'A':
                tabuleiro[0][jogada.x-1].isMarked=1;
            break;
            case 'B':
                tabuleiro[1][jogada.x-1].isMarked=1;
            break;
            case 'C':
                tabuleiro[2][jogada.x-1].isMarked=1;
            break;
            case 'D':
                tabuleiro[3][jogada.x-1].isMarked=1;
            break;
            case 'E':
                tabuleiro[4][jogada.x-1].isMarked=1;
            break;
            case 'F':
                tabuleiro[5][jogada.x-1].isMarked=1;
            break;
            case 'G':
                tabuleiro[6][jogada.x-1].isMarked=1;
            break;
            case 'H':
                tabuleiro[7][jogada.x-1].isMarked=1;
            break;
            case 'I':
                tabuleiro[8][jogada.x-1].isMarked=1;
            break;
            case 'J':
                tabuleiro[9][jogada.x-1].isMarked=1;
        break;
        }
    }
    return alive;
}

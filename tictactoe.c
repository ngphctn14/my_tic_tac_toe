#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int owins=0, xwins=0, draw=0;

void seperate(char*, char[3][2]);
int isValidInput(int, int, char*);
int isValidTurn(int, char*);
int isValidMove(int, int, char[5][6]);
void printBoard(char[5][6]);
void result(char[5][6]);
void posChanger(int*, int*);
void setBoard(char[5][6]);
void winCond(int, char);

int main() {
    char board[5][6], piece[2], input1[69], input2[3][2];
    int col, row, stop=0, count=0, i;
    setBoard(board);
    printf("\n================ Tic Tac Toe ================\n\n");
    do {
        printBoard(board);
        if(count>4)
            result(board);
        if(owins || xwins)
            break;
        if(count==9) {
            draw=1;
            break;
        }
        do {
            printf("\nEnter row, col, piece: ");
            for(i=0; i<3; i++)
                memset(input2[i], 0, strlen(input2[i]));
            scanf(" %[^\n]", input1);
            if(strlen(input1)!=5) {
                printf("\n");
                continue;
            }
            seperate(input1, input2);
            row=atoi(input2[0]);
            col=atoi(input2[1]);
            strcpy(piece, input2[2]);
            if(row==0 && col==0 && !strcmp(piece, "0")) {
                stop=1;
                break;
            }
            printf("\n");
        } while(!isValidInput(row, col, piece) || !isValidTurn(count, piece) || !isValidMove(row, col, board));
        count++;
        if(stop) {
            printf("\nThe game has been stopped.\n");
            break;
        }
        posChanger(&col, &row);
        board[row][col]=piece[0];
    } while(69/*funny number*/);
    if(owins)
        printf("\nO won! :)\nX lost. :(\n");
    else if(xwins)
        printf("\nX won! :)\nO lost. :(\n");
    else if(draw)
        printf("\nDraw!\n");
    return 0;
}

void seperate(char *a, char b[3][2]) {
    int i, j=0, k=0;
    for(i=0; a[i]!='\0'; i++) {
        if(a[i]==' ') {
            j++;
            k=0;
            continue;
        }
        b[j][k]=a[i];
        k++;
    }
}

void setBoard(char a[5][6]) {
    int i, j;
    for(i=0; i<5; i++) {
        for(j=0; j<5; j++) {
            if(i%2==0 && j%2==0)
                a[i][j]=' ';
            else if(i%2==0 && j%2==1)
                a[i][j]='|';
            else if(i%2==1 && j%2==0)
                a[i][j]='-';
            else if(i%2==1 && j%2==1)
                a[i][j]='.';
        }
    }

}

int isValidInput(int row, int col, char* piece) {
    return (((col>0 && col<=3)) && ((row>0 && row<=3)) && (!strcmp(piece, "O") || !strcmp(piece, "X")));
}

int isValidTurn(int count, char* piece) {
    return ((count%2==0 && !strcmp(piece, "X")) || (count%2==1 && !strcmp(piece, "O")));
}

int isValidMove(int row, int col, char a[5][6]) {
    posChanger(&col, &row);
    return !(a[row][col]=='O' || a[row][col]=='X');
}

void printBoard(char a[5][6]) {
    int i, j;
    for(i=0; i<5; i++) {
        for(j=0; j<5; j++)
            printf("%c", a[i][j]);
        printf("\n");
    }
}

void posChanger(int *row, int *col) {
    if(*row==1)
        (*row)--;
    else if(*row==3)
        (*row)++;
    if(*col==1)
        (*col)--;
    else if(*col==3)
        (*col)++;
}

void winCond(int count, char piece) {
    if(count!=2)
        return;
    if(piece=='O') {
        owins=1;
        return;
    } else {
        xwins=1;
        return;
    }
}

void result(char a[5][6]) {
    int i, j, count;
    for(i=0; i<3; i+=2) {
        count=0;
        for(j=0; j<3; j+=2) {
            if(a[i][j]==a[i][j+2] && (a[i][j]=='O' || a[i][j]=='X'))
                count++;
            winCond(count, a[i][j]);
            if(owins || xwins)
                return;
        }
    }
    for(j=0; j<3; j+=2) {
        count=0;
        for(i=0; i<3; i+=2) {
            if(a[i][j]==a[i+2][j] && (a[i][j]=='O' || a[i][j]=='X'))
                count++;
            winCond(count, a[i][j]);
            if(owins || xwins)
                return;
        }
    }
    count=0;
    for(i=0, j=0; i<3; i+=2, j+=2) {
        if(a[i][j]==a[i+2][j+2] && (a[i][j]=='O' || a[i][j]=='X'))
            count++;
        winCond(count, a[i][j]);
        if(owins || xwins)
            return;
    }
    count=0;
    for(i=0, j=4; i<3; i+=2, j-=2) {
        if(a[i][j]==a[i+2][j-2] && (a[i][j]=='O' || a[i][j]=='X'))
            count++;
        winCond(count, a[i][j]);
        if(owins || xwins)
            return;
    }
}

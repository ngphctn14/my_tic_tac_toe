#include <stdio.h>

int draw;
int owins=0;
int xwins=0;

int isValidInput(int, int, char);
int isValidTurn(int, char);
int isValidTurn1(int, int, char[6][6]);
void printBoard(char[6][6]);
void result(char[6][6]);
void posChanger(int*, int*);
void setBoard(char[6][6]);

int main() {
    char board[6][6];
    int col, row, stop=0;
    char piece;
    int count=0;
    setBoard(board);
    printf("\n================ Tic Tac Toe ================\n\n");
    do {
        printBoard(board);
        if(count>4)
            result(board);
        if(owins || xwins) {
            break;
        }
        if(count==9) {
            draw=1;
            break;
        }
        do {
            printf("\n");
            printf("Enter row, col, piece: ");
            scanf("%d %d %c", &row, &col, &piece);
            if(row==5 || col==5 || piece=='5') {
                stop=1;
                break;
            }
            printf("\n");
        } while(!isValidInput(row, col, piece) || !isValidTurn(count, piece) || !isValidTurn1(row, col, board));
        count++;
        if(stop) {
            printf("\nThe game has been stopped.\n");
            break;
        }
        posChanger(&col, &row);
        board[row][col]=piece;
    } while(1);
    if(owins)
        printf("\nO won\nX lost\n");
    else if(xwins)
        printf("\nX won\nO lost\n");
    else if(draw)
        printf("\nDraw\n");
    return 0;
}

void setBoard(char a[6][6]) {
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

int isValidInput(int row, int col, char piece) {
    return ((col>0 && col<=3)) && ((row>0 && row<=3)) && (piece=='O' || piece=='X');
}

int isValidTurn(int count, char piece) {
    if(count%2==0 && piece=='X')
        return 1;
    else if(count%2==1 && piece=='O')
        return 1;
    return 0;
}

int isValidTurn1(int row, int col, char a[6][6]) {
    posChanger(&col, &row);
    if(a[row][col]=='O' || a[row][col]=='X')
        return 0;
    return 1;
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

void printBoard(char a[6][6]) {
    int i, j;
    for(i=0; i<5; i++) {
        for(j=0; j<5; j++) {
            printf("%c", a[i][j]);
        }
        printf("\n");
    }
}

void result(char a[6][6]) {
    int i, j, count;
    for(i=0; i<3; i+=2) {
        count=0;
        for(j=0; j<3; j+=2) {
            if(a[i][j]==a[i][j+2] && (a[i][j]=='O' || a[i][j]=='X')) {
                count++;
            }
            if(count==2) {
                if(a[i][j]=='O') {
                    owins=1;
                    return;
                } else {
                    xwins=1;
                    return;
                }
            }
        }
    }
    for(j=0; j<3; j+=2) {
        count=0;
        for(i=0; i<3; i+=2) {
            if(a[i][j]==a[i+2][j] && (a[i][j]=='O' || a[i][j]=='X')) {
                count++;
            }
            if(count==2) {
                if(a[i][j]=='O') {
                    owins=1;
                    return;
                } else {
                    xwins=1;
                    return;
                }
            }
        }
    }
    count=0;
    for(i=0, j=0; i<3; i+=2, j+=2) {
        if(a[i][j]==a[i+2][j+2] && (a[i][j]=='O' || a[i][j]=='X')) {
            count++;
        }
        if(count==2) {
            if(a[i][j]=='O') {
                owins=1;
                return;
            } else {
                xwins=1;
                return;
            }
        }
    }
    count=0;
    for(i=0, j=4; i<3; i+=2, j-=2) {
        if(a[i][j]==a[i+2][j-2] && (a[i][j]=='O' || a[i][j]=='X')) {
            count++;
        }
        if(count==2) {
            if(a[i][j]=='O') {
                owins=1;
                return;
            } else {
                xwins=1;
                return;
            }
        }
    }
}

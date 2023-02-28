#include <stdio.h>

int draw;
int owins=0;
int xwins=0;

int isValid(int, int, char);
int isValidTurn(int, char);
int isValidTurn1(int, int, char[6][6]);
void printBoard(char[6][6]);
void result(char[6][6]);

int main() {
    char board[6][6];
    int col, row;
    char piece;
    int i, j, count=0;
    for(i=0; i<5; i++) {
        for(j=0; j<5; j++) {
            if(i%2==0 && j%2==0)
                board[i][j]=' ';
            else if(i%2==0 && j%2==1)
                board[i][j]='|';
            else if(i%2==1 && j%2==0)
                board[i][j]='-';
            else if(i%2==1 && j%2==1)
                board[i][j]='.';
        }
    }
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
            printf("Enter row, col, piece: ");
            scanf("%d %d %c", &row, &col, &piece);
        } while(!isValid(row, col, piece) || !isValidTurn(count, piece) || !isValidTurn1(row, col, board));
        count++;
        if(row==1)
            row=0;
        if(col==1)
            col=0;
        if(row==3)
            row=4;
        if(col==3)
            col=4;
        board[row][col]=piece;
        printf("%d\n%d\n", owins, xwins);
    } while(1);
    if(owins) {
        printf("O won\nX lost\n");
    } else if(xwins) {
        printf("X won\nO lost\n");
    } else if(draw) {
        printf("\nDraw\n");
    }
    return 0;
}

int isValid(int row, int col, char piece) {
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
    if(row==1)
        row=0;
    if(col==1)
        col=0;
    if(row==3)
        row=4;
    if(col==3)
        col=4;
    if(a[row][col]=='O' || a[row][col]=='X')
        return 0;
    return 1;
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
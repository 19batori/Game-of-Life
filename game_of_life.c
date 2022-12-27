#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#define H 25
#define W 80

char map[H][W];
// 178-блок по ASCII
void input(FILE *file);
void show();
int neighbor(int i, int j, char a[H][W]);
int new_Y(int y);
int new_X(int x);
void life(int i, int j, char a[H][W]);
void game();
int main() {
    int option, speed;
    printf("Choose speed of game from 1 to 3:\n");
    scanf("%d", &speed);
    printf("Choose start position from 1 to 5:\n");
    scanf("%d", &option);
    FILE *file1 = fopen("1.txt", "rt");
    FILE *file2 = fopen("2.txt", "rt");
    FILE *file3 = fopen("3.txt", "rt");
    FILE *file4 = fopen("4.txt", "rt");
    FILE *file5 = fopen("5.txt", "rt");
    if (option == 1) {
        input(file1);
        fclose(file1);
    } else if (option == 2) {
        input(file2);
        fclose(file2);
    } else if (option == 3) {
        input(file3);
        fclose(file3);
    } else if (option == 4) {
        input(file4);
        fclose(file4);
    } else if (option == 5) {
        input(file5);
        fclose(file5);
    }
    show();
    usleep(10000);
    game();
    show();
    usleep(10000);
    int k = 0;
    do {
        printf("\033c");
        game();
        show();
        k++;
        usleep(100000 * pow(2, -speed));
    } while (k < 1000);
    return 0;
}

void input(FILE *file) {
    if (file == NULL) {
        printf("Open file error");
    }
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            fscanf(file, "%c", &map[i][j]);
}

void show() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

void life(int i, int j, char a[H][W]) {
    if (neighbor(i, j, a) == 3 && a[i][j] == ' ')
        map[i][j] = 'X';
    else if ((neighbor(i, j, a) == 2 || neighbor(i, j, a) == 3) && (a[i][j] == 'X'))
            map[i][j] = 'X';
    else
        map[i][j] = ' ';
}

void game() {
    char buf[H][W];
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            buf[i][j] = map[i][j];
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++) {
            life(i, j, buf);
        }
}

int neighbor(int x, int y, char a[H][W]) {
    int n = 0;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i == x && j == y) {
                continue;
            } else if (a[new_X(i)][new_Y(j)] == 'X') {
                   n++;
            }
        }
    }
    return n;
}

int new_X(int x) {
    if (x < 0) {
        x = H - 1;
    } else {
        if (x > H - 1)
        x = 0;
    }
    return x;
}

int new_Y(int y) {
    if (y < 0)
        y = W - 1;
    if (y > W - 1)
        y = 0;
    return y;
}

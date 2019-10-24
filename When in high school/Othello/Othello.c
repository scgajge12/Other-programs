#include <stdio.h>
#include <stdlib.h>
#ifdef _MSC_VER
#include <Windows.h>
#endif
// define定義
#define LEN 8
#define WHITE 'O' //白
#define BLACK 'X' //黒
#define BLANK ' '
#define CPU BLACK //コンピュータ
#define HUMAN WHITE //人間
// セルの情報（取れる個数）
typedef struct cell {
    int x;
    int y;
    char *p_cell;
    int count;
} CELL;
// フィールド情報構造体
typedef struct finfo {
    int white;
    int black;
    int blank;
} F_INFO;
// プロトタイプ宣言
void startup(char field[][LEN]);
void wait(int sec);
void cls();
void viewStatus(char f[LEN][LEN]);
void initField(char f[LEN][LEN]);
void printField(char f[LEN][LEN]);
int setPos(int y, int x, char c, char f[LEN][LEN], int set);
int directCount(int y, int x, int dy, int dx, char c, char f[LEN][LEN], int set);
char *beInField(char field[LEN][LEN], int y, int x);
int blankCellCount(char f[LEN][LEN]);
void availableCellList(char f[LEN][LEN], CELL* list, char player);
int cpu(char f[LEN][LEN], char);
int human(char f[LEN][LEN], char);
F_INFO fieldStatus(char f[LEN][LEN]);
int main(int argc, char **argv) {
    char field[LEN][LEN];	// 8x8の文字型2次元配列
    int blcnt = 0;		// 空白セル数のカウント
    int available;		// パス，終了判定フラグ
    char player;		// 人間のコマ
    F_INFO info;		// 盤面情報（コマ，空白の個数）
                        // 盤面の初期化
    initField(field);
    // スタート画面の表示
    startup(field);
    // 人間は白で先手
    player = HUMAN;
    cls();
    // ゲーム開始
    printf("GAME START!!\n");
    wait(2);
    // ゲームループ
    do {
        cls();
        available = 0;
        /* 人間の手番 */
        printf("Your('%c') turn:\n", player);
        printField(field);
        available |= human(field, player);
        cls();
        if (available) {
            printf("Your('%c') turn:\n", player);
            printField(field);
        }
        else printf("\tYou: Pass!\n");
        wait(1);
        /* コンピュータの手番 */
        available |= cpu(field, player == WHITE ? BLACK : WHITE);
        cls();
        if (available) {
            printf("CPU's turn:\n\n");
            printField(field);
        }
        else printf("\tCPU: Pass!\n");
        viewStatus(field);
        printf("\n");
        wait(1);
    } while (available);
    // ゲーム終了処理
    cls();
    printf("GAME FINISHED!!\n");
    printField(field);
    viewStatus(field);
    info = fieldStatus(field);
    printf("\tResult: ");
    if (info.black == info.white) {
        printf("EVEN\n");
    }
    else if (info.black > info.white) {
        printf("Black　Win!!\n");
    }
    else {
        printf("White　Win!!\n");
    }
    return 0;
}
/* 起動時の画面表示 */
void startup(char field[][LEN]) {
    printf("   [オセロゲーム]  \n\n");
    printField(field);
    printf("CPUとオセロ対決!\n");
    printf(" あなたの色はホワイト('O')\n");
    printf(" CPUの色はブラック('X')\n");
    printf("please input: [横番号　縦番号]で入力すること\n\n");
    printf("Enterキーを押してゲームスタート!!\n");
    getchar();
}
/* それぞれのコマの数の表示 */
void viewStatus(char f[LEN][LEN]) {
    F_INFO info;
    // コマの数を取得
    info = fieldStatus(f);
    printf("\tCount: Black('X'): %d\t", info.black);
    printf("White('O'): %d\n\n", info.white);
}
/* 一定時間待機させる関数 */
void wait(int sec) {
    // Visual C++コンパイラへの対応
#ifdef _MSC_VER
    Sleep(sec * 1000);
#else
    //sleep(sec);
#endif
}
/* 画面クリア関数 */
void cls() {
    // Windows環境への対応（Visual C++）
#ifdef _MSC_VER
    system("cls");
#else
    printf("\n\x1b[2J\n");
#endif
}
/* フィールドの初期化 */
void initField(char f[LEN][LEN]) {
    int x, y;
    for (y = 0; y < LEN; y++) {
        for (x = 0; x < LEN; x++) {
            f[y][x] = ' ';
        }
    }
    // 初期位置
    f[3][3] = f[4][4] = WHITE;
    f[4][3] = f[3][4] = BLACK;
}
/* フィールドの描画 */
void printField(char f[LEN][LEN]) {
    int x, y;
    for (x = 0; x < LEN; x++) printf(x ? "  %d " : "     %d ", x);
    printf("\n");
    printf("   +---+---+---+---+---+---+---+---+\n");
    for (y = 0; y < LEN; y++) {
        printf(" %d |", y);
        for (x = 0; x < LEN; x++) {
            printf(x ? " %c |" : " %c |", f[y][x]);
        }
        printf("\n");
        printf("   +---+---+---+---+---+---+---+---+\n");
    }
    printf("\n");
}
/* 指定座標に指定文字が置けるかチェックする */
int setPos(int Y, int X, char c, char f[LEN][LEN], int set) {
    int count = 0;
    //上方向
    count += directCount(Y, X, -1, 0, c, f, set);
    //下方向
    count += directCount(Y, X, 1, 0, c, f, set);
    //左方向
    count += directCount(Y, X, 0, -1, c, f, set);
    //右方向
    count += directCount(Y, X, 0, 1, c, f, set);
    //左上方向
    count += directCount(Y, X, -1, -1, c, f, set);
    //右上方向
    count += directCount(Y, X, 1, -1, c, f, set);
    //左下方向
    count += directCount(Y, X, -1, 1, c, f, set);
    //右下方向
    count += directCount(Y, X, 1, 1, c, f, set);
    if (set && count) f[Y][X] = c;
    return count; //置けない
}
/* 指定方向へのカウント */
int directCount(int y, int x, int dy, int dx, char c, char f[LEN][LEN], int set) {
    int i;
    int count = 0;
    char *p;
    x += dx;
    y += dy;
    //cと同じ文字を探す
    while ((p = beInField(f, y, x)) && (*p != c)) {
        if (*p == ' ') {
            count = 0;
            break;
        }
        else {
            count++;
        }
        x += dx;
        y += dy;
    }
    //フィールドの端まで達したとき
    // p は NULL
    //同じ文字が見つかったとき
    // p は cに等しい
    if (p == NULL) count = 0;
    // 裏返し処理
    if (set && count > 0) {
        x -= dx;
        y -= dy;
        for (i = 0; i < count; i++) {
            f[y][x] = c;
            x -= dx;
            y -= dy;
        }
    } 
    return count;
}
/* 座標がフィールド内かどうか判定する関数 */
char *beInField(char field[LEN][LEN], int y, int x) {
    // フィールド内ならポインタを返す
    if (x >= 0 && x < LEN && y >= 0 && y < LEN) return &field[y][x];
    // フィールド外ならNULL
    return NULL;
}
/* 空白セルのカウント */
int blankCellCount(char f[LEN][LEN]) {
    int x, y;
    int blcnt = 0;
    for (y = 0; y < LEN; y++) {
        for (x = 0; x < LEN; x++) {
            if (f[y][x] == ' ') {
                blcnt++;
            }
        }
    }
    return blcnt;
}
/* 空白セルのリスト */
void availableCellList(char f[LEN][LEN], CELL* list, char player) {
    int x, y;
    int blcnt = 0;
    for (y = 0; y < LEN; y++) {
        for (x = 0; x < LEN; x++) {
            if (f[y][x] == ' ') {
                blcnt++;
                // セルの情報を格納
                list[blcnt - 1].x = x;
                list[blcnt - 1].y = y;
                list[blcnt - 1].p_cell = &f[y][x];
                list[blcnt - 1].count = setPos(y, x, player, f, 0);
            }
        }
    }
}
/* コンピュータの手番 */
int cpu(char f[LEN][LEN], char player) {
    CELL* bl;
    int bc;
    int better = 0;
    CELL better_cell;
    int i;
    bc = blankCellCount(f); // 空白セル数
    bl = (CELL*)malloc(sizeof(CELL) * bc); //1つ分あらかじめ確保
    if (bl == NULL) {
        printf("malloc Error!\n");
        return -1;
    }
    availableCellList(f, bl, player); // 取得
                                      /* ここから */
    for (i = 0; i < bc; i++) {
        if (bl[i].count > better) {
            better = bl[i].count; // とりあえず最後の最善手で
            better_cell = bl[i];
        }
    }
    if (better > 0) {
        // 実際に置く
        setPos(better_cell.y, better_cell.x, player, f, 1);
    }
    /* ここまで */
    free(bl);
    return better;
}
/* 人間の手番 */
int human(char f[LEN][LEN], char player) {
    CELL* bl;
    int bc;
    int better = 0;
    CELL better_cell;
    int i;
    int x, y;
    int check;
    bc = blankCellCount(f); // 空白セル数
    bl = (CELL*)malloc(sizeof(CELL) * bc); //1つ分あらかじめ確保
    if (bl == NULL) {
        printf("malloc Error!\n");
        return -1;
    }
    availableCellList(f, bl, player); // 取得
                                      /* ここから */
    for (i = 0; i < bc; i++) {
        if (bl[i].count > better) {
            better = bl[i].count; // とりあえず最後の最善手で
            better_cell = bl[i];
        }
    }
    if (better > 0) {
        do {
            // ユーザ入力を受け取る
            printf("please input: ");
            scanf("%d %d", &x, &y);
            // 実際に置く
            check = setPos(y, x, player, f, 1);
        } while (check == 0);
    }
    /* ここまで */
    free(bl);
    return better;
}
/* フィールドに置かれているオブジェクトの数を調べる */
F_INFO fieldStatus(char f[LEN][LEN]) {
    F_INFO info = { 0, 0, 0 };
    int x, y;
    for (y = 0; y < LEN; y++) {
        for (x = 0; x < LEN; x++) {
            switch (f[y][x]) {
            case WHITE:
                info.white++;
                break;
            case BLACK:
                info.black++;
                break;
            case BLANK:
                info.blank++;
                break;
            }
        }
    }
    return info;
}

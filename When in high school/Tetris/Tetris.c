#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
//グローバル変数
int stage[21][12] = { 0 };//壁と固定済みブロック用
int block[4][4] = { 0 };//現在落下中のブロックを入れる
int nextblock[4][4] = { 0 };//次のブロック入れ
int field[21][12] = { 0 };//描画するデータ。stage[][]にblock[][]を重ねたもの
                          //７種類のブロックのデータ
int block_list[7][4][4] =
{ { { 0,1,0,0 },{ 0,1,0,0 },{ 0,1,0,0 },{ 0,1,0,0 } },
{ { 0,0,0,0 },{ 0,1,1,0 },{ 0,1,0,0 },{ 0,1,0,0 } },
{ { 0,0,1,0 },{ 0,1,1,0 },{ 0,1,0,0 },{ 0,0,0,0 } },
{ { 0,1,0,0 },{ 0,1,1,0 },{ 0,0,1,0 },{ 0,0,0,0 } },
{ { 0,0,0,0 },{ 0,1,0,0 },{ 1,1,1,0 },{ 0,0,0,0 } },
{ { 0,0,0,0 },{ 0,1,1,0 },{ 0,1,1,0 },{ 0,0,0,0 } },
{ { 0,0,0,0 },{ 0,1,1,0 },{ 0,0,1,0 },{ 0,0,1,0 } } };
int y = 0;//ブロックの画面上でのy座標
int x = 4;//ブロックの画面上でのx座標
int oneline, twoline, threeline, fourline;//消したラインの数
int gameover = 0;//ゲームオーバー判定。新しいブロックが初期位置に置けなければ1になる。
                 //関数プロトタイプ宣言
void Initialize();//ゲーム起動直後の初期設定を行う関数。画面と壁のデータを初期化
int CreateBlock();//新しいブロックを生成して次のブロックに発生させる
void ShowGameField();//field[][]の中身に応じて、画面を描画する
void ControlBlock();//キー入力に応じてブロックに移動や回転等の処理を行わせる
int  CheckOverlap(int, int);//落下中のブロックが壁や固定済みブロックに接触していないか判別
void MoveBlock(int, int);//落下中ブロックを一旦消して、任意の座標に移動させる
int TurnBlock();//ブロックの回転を処理する
void DropBlock();//ブロックを落下させる。下に移動できない場合ブロックをその位置に固定
void LockBlock();//着地したブロックを固定済みブロックに加える関数
void CheckLines();//ブロックが横一列にそろえばそこを消去後、上のブロックをそこに下ろす
void InitializeNextBlock();
int main()
{
    int a, p;
    printf("   <<<テトリス>>>      \n");
    printf("[ルール]\n");
    printf("　①kを押すとブロックが右に動く。\n");
    printf("　②hを押すとブロックが左に動く。\n");
    printf("　③jを押すとブロックが下に早く動く。\n");
    printf("　④スペースキーを押すとブロックの向きが変わる。\n\n");
    printf("[スコア]\n");
    printf("　①1行消しすると＋100点。\n");
    printf("  ②2行消しすると＋300点。\n");
    printf("  ③3行消しすると＋700点。\n");
    printf("　④4行消しすると＋1000点入る。\n\n");
    printf("その合計点が君のスコアになる。\n");
    printf(" ルールがわかったら0を押してスタート!\n");
    int time = 0;//時間をカウント
    char insertcoin = 'y';
    while (insertcoin == 'y') {
        printf("\n");
        printf(" 0を入力してください。　\n");
        for (p = 0; p < 100; p++) {
            printf("=>");
            scanf("%d", &a);
            if (a == 0) {
                break;
            }
            else {
                printf("%dが入力されました。\n\n", a);
                printf("0を入力したください。\n");
            }
        }
        system("cls");
        Initialize();//初期化
                     //ゲームオーバーになるまでゲーム続行
        while (!gameover) {
            //キー入力があればそれに応じて操作
            if (kbhit()) {
                ControlBlock();
            }
            //時間がきたらブロックを１マス落下させる。時間が来てなければ時間を１だけインクリメント。
            if (oneline * 100 + twoline * 300 + threeline * 700 + fourline * 1000 < 1000) {
                if (time < 15000) {
                    time++;
                }
                else {
                    DropBlock();
                    time = 0;
                }
            }
            else if(oneline * 100 + twoline * 300 + threeline * 700 + fourline * 1000 < 2500){
                if (time < 11000) {
                    time++;
                }
                else {
                    DropBlock();
                    time = 0;
                }

            }
            else if (oneline * 100 + twoline * 300 + threeline * 700 + fourline * 1000 < 4000) {
                if (time < 7000) {
                    time++;
                }
                else {
                    DropBlock();
                    time = 0;
                }

            }
        }
        //ゲームオーバーの場合はGAME OVERを表示
        system("cls");
        printf("\n\n");
        printf("               <<ゲーム終了>>      　　 \n\n" );
        printf(" 君のスコアは%d点です。\n\n", oneline * 100 + twoline * 300 + threeline * 700 + fourline * 1000);
        printf("今までの高スコア\n");
        printf(" 1位:5900点\n");
        printf(" 2位:4100点\n");
        printf(" 3位:3700点\n\n");
        printf("コンティニューしますか？（コンティニューする場合はy,しない場合はn）\n");
        insertcoin = getch();
        while (insertcoin != 'y' && insertcoin != 'n') {
            printf("yかnを押してください(押されたキー: %c)\n", insertcoin);
            insertcoin = getch();
        }
        if (insertcoin == 'y') {
            gameover = 0;
        }
    }
    return 0;
}
//ゲームの初期化
void Initialize()
{
    int i, j;//forループ制御用変数
    oneline = 0;
    twoline = 0;
    threeline = 0;
    fourline = 0;
    //画面と壁を初期設定
    for (i = 0; i <= 20; i++) {
        for (j = 0; j <= 11; j++) {
            if ((j == 0) || (j == 11) || (i == 20)) {
                field[i][j] = stage[i][j] = 9;
            }
            else {
                field[i][j] = stage[i][j] = 0;
            }
        }
    }
    InitializeNextBlock();//次のブロック初期化
    CreateBlock();//最初のブロック発生させる
    ShowGameField();//ゲーム直後の画面を描画
}
void InitializeNextBlock()
{
    int i, j;
    int block_type;
    srand((unsigned)time(NULL));
    block_type = rand() % 7;
    for (i = 0; i<4; i++) {
        for (j = 0; j<4; j++) {
            nextblock[i][j] = block_list[block_type][i][j];
        }
    }
}
//ブロック作成
int CreateBlock()
{
    int i, j;//forループ制御用の変数
    int block_type;//ブロックの種類用。０～６の乱数を入れる
                   //まずブロックの座標を初期位置にリセット
    y = 0;
    x = 4;
    //乱数を発生させ、その乱数を7で割った余り（０～６まで）でブロックの種類を決定
    srand((unsigned)time(NULL));
    block_type = rand() % 7;
    //ネクストブロック出現
    for (i = 0; i<4; i++) {
        for (j = 0; j<4; j++) {
            block[i][j] = 0;
            block[i][j] = nextblock[i][j];
        }
    }
    //ネクストブロック生成
    for (i = 0; i<4; i++) {
        for (j = 0; j<4; j++) {
            nextblock[i][j] = block_list[block_type][i][j];
        }
    }
    //壁＋ブロックをフィールドへ
    for (i = 0; i<4; i++) {
        for (j = 0; j<4; j++) {
            field[i][j + 4] = stage[i][j + 4] + block[i][j];
            //初期位置に置いたブロックが既に固定ブロックに重なっていればゲームオーバー
            if (field[i][j + 4] > 1) {
                gameover = 1;
                return 1;
            }
        }
    }
    return 0;
}
//画面表示
void ShowGameField()
{
    int i, j, k;//forループ制御用変数
                //画面を一旦クリア
    system("cls");
    //データに応じてブロックや空白を画面表示
    for (i = 0; i<21; i++) {
        for (j = 0; j < 12; j++) {
            switch (field[i][j]) {
            case 0:
                printf("　");
                break;
            case 9:
                printf("□");
                break;
            default:
                printf("■");
                break;
            }
        }
        if (i == 3) {
            printf("　　　□□□□□□");
        }
        if (i == 4) {
            printf("　　　□");
            for (k = 0; k<4; k++) {
                switch (nextblock[0][k]) {
                case 0:
                    printf("　");
                    break;
                default:
                    printf("■");
                    break;
                }
            }
            printf("□");
        }
        if (i == 5) {
            printf("　　　□");
            for (k = 0; k<4; k++) {
                switch (nextblock[1][k]) {
                case 0:
                    printf("　");
                    break;
                default:
                    printf("■");
                    break;
                }
            }
            printf("□");
        }
        if (i == 6) {
            printf("　　　□");
            for (k = 0; k<4; k++) {
                switch (nextblock[2][k]) {
                case 0:
                    printf("　");
                    break;
                default:
                    printf("■");
                    break;
                }
            }
            printf("□");
        }
        if (i == 7) {
            printf("　　　□");
            for (k = 0; k<4; k++) {
                switch (nextblock[3][k]) {
                case 0:
                    printf("　");
                    break;
                default:
                    printf("■");
                    break;
                }
            }
            printf("□");
        }
        if (i == 8) {
            printf("　　　□□□□□□");
        }
        if (i == 13) {
            printf("　　　□□□□□□");
        }
        if (i == 14) {
            printf("　　　　 SCORE");
        }
        if (i == 15) {
            printf("　　　　　%d点", oneline * 100 + twoline * 300 + threeline * 700 + fourline * 1000);
        }
        if (i == 16) {
            printf("　　　□□□□□□");
        }
        printf("\n");
    }
    //得点表示
    printf("\n１行消し：%d回　２行消し：%d回　３行消し：%d回　４行消し：%d回\n", oneline, twoline, threeline, fourline);
}
//キー入力に応じてブロックを処理
void ControlBlock()
{
    char key;//受け付けたキーを保存する変数
    key = getch();//キーから一文字入力
                  //キーに応じて各方向へブロックを移動したり、回転させたりする
    switch (key) {
    case 'k':
        if (!CheckOverlap(x + 1, y)) {
            MoveBlock(x + 1, y);
        }
        break;
    case 'h':
        if (!CheckOverlap(x - 1, y)) {
            MoveBlock(x - 1, y);
        }
        break;
    case 'j':
        if (!CheckOverlap(x, y + 1)) {
            MoveBlock(x, y + 1);
        }
        break;
    case ' ':
        TurnBlock();
    }
}
//重なり検査
int CheckOverlap(int x2, int y2)
{
    int i, j;//forループ制御用変数
             //ブロックが向かう位置に、固定ブロックもしくは壁があるかどうかを検査
    for (i = 0; i<4; i++) {
        for (j = 0; j<4; j++) {
            if (block[i][j]) {
                if (stage[y2 + i][x2 + j] != 0) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
//移動
void MoveBlock(int x2, int y2)
{
    int i, j;//forループ制御用変数
             //消して
    for (i = 0; i<4; i++) {
        for (j = 0; j<4; j++) {
            field[y + i][x + j] -= block[i][j];
        }
    }
    //ブロックの座標を更新
    x = x2;
    y = y2;
    //下に表示
    for (i = 0; i<4; i++) {
        for (j = 0; j<4; j++) {
            field[y + i][x + j] += block[i][j];
        }
    }
    ShowGameField();
}
//ブロックを回転する処理
int TurnBlock()
{
    int i, j;//forループ制御用
    int temp[4][4] = { 0 };//ブロックを一時保存するための配列
                           //ブロックを回転する前にtempにセーブ
    for (i = 0; i<4; i++) {
        for (j = 0; j<4; j++) {
            temp[i][j] = block[i][j];
        }
    }
    //ブロックを回転
    for (i = 0; i<4; i++) {
        for (j = 0; j<4; j++) {
            block[i][j] = temp[3 - j][i];
        }
    }
    //重なってるブロックが出てしまったらブロックを回転前に戻して中止
    if (CheckOverlap(x, y)) {
        for (i = 0; i<4; i++) {
            for (j = 0; j<4; j++) {
                block[i][j] = temp[i][j];
            }
        }
        return 1;
    }
    //一旦フィールドからブロック消して回転後のブロックを再表示
    for (i = 0; i<4; i++) {
        for (j = 0; j<4; j++) {
            field[y + i][x + j] -= temp[i][j];
            field[y + i][x + j] += block[i][j];
        }
    }
    ShowGameField();
    return 0;
}
//ブロックを落とす
void DropBlock()
{
    //重なりがなければ移動
    if (!CheckOverlap(x, y + 1)) {
        MoveBlock(x, y + 1);
    }
    //重なりがあれば壁にする
    else {
        LockBlock();
        CreateBlock();
        ShowGameField();
    }
}
//着地後のブロックを固定し、横一列がそろってるかの判定を呼び出す
void LockBlock()
{
    int i, j;//forループ制御用変数
             //ブロックを壁に加える
    for (i = 0; i<21; i++) {
        for (j = 0; j<12; j++) {
            stage[i][j] = field[i][j];
        }
    }
    CheckLines();//横一列がそろってるか判定して処理する関数を呼ぶ
                 //列完成判定後の壁をフィールドへ
    for (i = 0; i<21; i++) {
        for (j = 0; j<12; j++) {
            field[i][j] = stage[i][j];
        }
    }
}
//横一列が完成しているか検査。そろっていればそこを消して上のブロック群を下ろす
void CheckLines()
{
    int i, j, k;//forループ制御用
    int comp;//横一列がそろっていれば１、一つでも隙間があると０になる
    int lines = 0;//同時に消したラインの数
    while (1) {
        for (i = 0; i<20; i++) {
            comp = 1;
            for (j = 1; j<11; j++) {
                if (stage[i][j] == 0) {
                    comp = 0;
                }
            }
            if (comp == 1) break;
        }
        if (comp == 0)
            break;
        lines++;
        // 列を消去
        for (j = 1; j<11; j++) {
            stage[i][j] = 0;
        }
        //消えた列より上にあった固定ブロックを列の消えたところへ下ろす
        for (k = i; k>0; k--) {
            for (j = 1; j<11; j++) {
                stage[k][j] = stage[k - 1][j];
            }
        }
    }
    //同時に消したラインの数をカウント
    switch (lines) {
    case 1:
        oneline++;
        break;
    case 2:
        twoline++;
        break;
    case 3:
        threeline++;
        break;
    case 4:
        fourline++;
        break;
    default:
        break;
    }
}

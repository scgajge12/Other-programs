#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void) {
    int x[] = { 1,2,3,4,5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    const int n = sizeof(x) / sizeof(x[0]); 
    int i, j, k, t;
    int a;
    printf(" [毎日おみくじ] \n");
    printf("1～9の中から好きな数字を１つ入力しよう\n=>");
    scanf("%d", &a);
    srand((unsigned)time(NULL));
    for (i = 0; i<n ; i++) {
        j = rand() % n;
        k = rand() % n;
        while (j == k) k = rand() % n;
        t = x[j];
        x[j] = x[k]; 
        x[k] = t;
    }
    printf("\n今日の君の運勢は%d番だ！\n", x[a]);
    printf("  ーーーーー+ーーーーーーーーーーーーーー\n");
    printf("  | 1.大大吉:最高の運気                 |\n");
    printf("  | 2. 大吉 :とても良い運気             |\n");
    printf("  | 3.  吉　:良い運気                   |\n");
    printf("  | 4. 中吉 :まぁまぁ良い運気           |\n");
    printf("  | 5. 小吉 :少し良い運気               |\n");
    printf("  | 6. 半吉 :吉の半分くらいの運気       |\n");
    printf("  | 7. 末吉 :後になって良くなる運気     |\n");
    printf("  | 8.末小吉:後になって少し良くなる運気 |\n");
    printf("  | 9. 平吉 :可もなく不可もなくの運気   |\n");
    printf("  |10.  区  :悪い運気                   |\n");
    printf("  |11. 小区 :区より少し悪い運気         |\n");
    printf("  |12. 半区 :小区より少し悪い運気       |\n");
    printf("  |13. 末区 :半区より少し悪い運気       |\n");
    printf("  |14. 大区 :最悪の運気                 |\n");
    printf("  ーーーーー+ーーーーーーーーーーーーーー\n\n");
    return 0;
}

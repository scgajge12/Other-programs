#include <stdio.h>
#include <math.h>
int main(void)
{
    double takara[12][2];
    int kosu;
    int shirei[12], maisu, shireiNo;
    double total_kyori, X_kyori, Y_kyori;
    int k;
    double best_kyori;
    int best_shireiNo, best_shirei[12];

    scanf("%d", &kosu);
    printf("宝箱は%d個\n", kosu);
    if (kosu > 10) {
        printf("宝箱の数が多すぎます。\n");
        return 0;
    }
    for (k = 1; k <= kosu; k++) {
        scanf("%lf, %lf", &takara[k][0], &takara[k][1]);
        printf("宝箱%d:(%lf,%lf)\n", k, takara[k][0], takara[k][1]);
    }
    takara[0][0] = 0.0; takara[0][1] = 0.0;
    takara[kosu + 1][0] = 1000.0; takara[kosu + 1][1] = 0.0;

    scanf("%d", &maisu);
    printf("指令書は%d枚\n", maisu);
    for (shireiNo = 1; shireiNo <= maisu; shireiNo++) {
        printf("指令書%d：\n", shireiNo);
        printf("スタート=>");
        for (k = 1; k <= kosu; k++) {
            scanf("%d", &shirei[k]);
            printf("%d=>", shirei[k]);
        }
        printf("ゴール\n");
        shirei[0] = 0;
        shirei[kosu + 1] = kosu + 1;

        total_kyori = 0.0;
        for (k = 1; k <= kosu + 1; k++) {
            X_kyori = takara[shirei[k]][0] - takara[shirei[k - 1]][0];
            Y_kyori = takara[shirei[k]][1] - takara[shirei[k - 1]][1];
            total_kyori += sqrt(X_kyori*X_kyori + Y_kyori*Y_kyori);
        }
        printf("合計距離は%lf\n", total_kyori);
        switch (shireiNo) {
        case 1:
            best_kyori = total_kyori;
            best_shireiNo = shireiNo;
            for (k = 1; k <= kosu; k++) {
                best_shirei[k] = shirei[k];
            }
            break;
        default:
            if (best_kyori > total_kyori) {
                best_kyori = total_kyori;
                best_shireiNo = shireiNo;
                for (k = 1; k <= kosu; k++) {
                    best_shirei[k] = shirei[k];
                }
            }
        }
        }
        printf("\n");
        printf("最短距離は%lf\n", best_kyori);
        printf("指令書%d：\n", best_shireiNo);
        printf("スタート=>");
        for (k = 1; k <= kosu; k++) {
            printf("%d=>", best_shirei[k]);
        }
        printf("ゴール\n");
    return 0;
}

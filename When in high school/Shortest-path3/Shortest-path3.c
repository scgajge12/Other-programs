#include <stdio.h>
#include <math.h>
int main(void)
{
    double takara[20][2];
    int kosu;
    int shirei[20];
    double total_kyori, X_kyori, Y_kyori;
    double best_kyori;
    int best_shirei[20];
    int k, a;
    int i, j;
    int flag;

    scanf("%d", &kosu);
    printf("宝箱は%d個\n", kosu);
    if (kosu > 13) {
        printf("宝箱の数が多すぎます。\n");
        return 0;
    }
    for (k = 1; k <= kosu; k++) {
        scanf("%lf,%lf", &takara[k][0], &takara[k][1]);
        printf("宝箱%d:(%lf,%lf)\n", k, takara[k][0], takara[k][1]);
    }
    takara[0][0] = 0.0; takara[0][1] = 0.0;
    takara[kosu + 1][0] = 1000.0; takara[kosu + 1][1] = 0.0;
    best_kyori = 0.0;

    for (a= 0; a <= kosu + 1; a++) {
        shirei[a] = 0;
    }
    i = 1;

    while (i != 0) {
            shirei[i] += 1;
            if (shirei[i] > kosu) {
                shirei[i] = 0;
                i--;
                continue;
            }
        flag = 0;
        for (j = 1; j < i; j++) {
            if (shirei[j] == shirei[i]) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            continue;
        }
        else {
            i++;
        }

        if (i != kosu+1) {
            continue;
        }
        shirei[0] = 0;
        shirei[kosu + 1] = kosu + 1;
        total_kyori = 0.0;
        for (k = 1; k <= kosu + 1; k++) {
            X_kyori = takara[shirei[k]][0] - takara[shirei[k - 1]][0];
            Y_kyori = takara[shirei[k]][1] - takara[shirei[k - 1]][1];
            total_kyori += sqrt(X_kyori*X_kyori + Y_kyori*Y_kyori);
        }

        if (best_kyori == 0.0) {
            best_kyori = total_kyori;
            for (k = 1; k <= kosu; k++) {
                best_shirei[k] = shirei[k];
            }
        }
        else {
            if (best_kyori > total_kyori) {
                best_kyori = total_kyori;
                for (k = 1; k <= kosu; k++) {
                    best_shirei[k] = shirei[k];
                }
            }
        }
        i--;
    }
    printf("\n");
    printf("最短距離は%lf\n", best_kyori);
    printf("スタート=>");
    for (k = 1; k <= kosu; k++) {
        printf("%d=>", best_shirei[k]);
    }
    printf("ゴール\n");
    return 0;
}

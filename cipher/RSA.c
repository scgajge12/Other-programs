/*  Key pair generation / encryption / decryption (鍵ペア生成・暗号化・復号化) */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
int power(int A, int B, int C);
int sosu();
int kakezan(int D, int E);
int Gcd(int F, int G);
int lcm(int H, int I, int J);
int kazuE(int K);
int kazuD(int L, int M);
int keta(int N);
int main(void) {
    int N, L, E, D;
    int p, q, f, gcd, K;
    int plain, cipher, Plain;

    printf("   [RSA(公開鍵暗号)]   \n");

    srand((unsigned)time(NULL));
    f = 0;
    while (f == 0) {
        p = sosu();
        q = sosu();

        N = kakezan(p, q);

        gcd = Gcd(p, q);
        L = lcm(p, q, gcd);

        E = kazuE(L);

        D = kazuD(L, E);
        if (D<0)
            continue;

        printf("p:%d q=%d L:%d\n\n", p, q, L);
        printf("公開鍵:(E, N)=(%d, %d)\n", E, N);
        printf("秘密鍵:(D, N)=(%d, %d)\n\n", D, N);

        f = 1;
        }

    K = keta(N);

    printf("暗号化したい数値を入力してください.\n");
    printf(" 制限:%d未満の数値[%d桁] (制限の最大値は1,073,676,288未満である.)\n=>", N-1, K);
    scanf("%d", &plain);
    if (plain >= N-1) {
        printf("入力した数値が大きくて暗号化できません.\n");
        return 1;
    }
    cipher = power(plain, E, N);
    printf("暗号化:%d\n\n", cipher);

    Plain = power(cipher, D, N);
    printf("復号化:%d\n\n", Plain);

        return 0;
}

int power(int A, int B, int C) {
    int j;
    unsigned long long answer;
    answer = A;
  
    for (j = 0; j < B-1; j++) {
        answer = answer*A;
        answer = answer%C;
    }
    return (int)answer;
}

int sosu() {
    int x, z, i, flag;

    flag = 0;
    while (flag == 0) {
        x = rand() % 22768 + 10000;
        for (i = 2; i < sqrt(x); i++) {
            z = x%i;
            if (z == 0) {
                flag = 0;
                break;
            }
            flag = 1;
        }
    }
    return x;
}

int kakezan(int D, int E) {
    int y;
    y = D*E;

    return y;
}

int Gcd(int F, int G) {
    int r, x, y;

    x = F - 1;
    y = G - 1;
    while ((r = x%y) != 0) {
        x = y;
        y = r;
    }
    return y;
}

int lcm(int H, int I, int J) {
    int w;
    
    w = (H - 1)*(I - 1) / J;

    return w;
}

int kazuE(int K) {
    int g, e, r, x, y;
    g = 0;

    while (g != 1) {
        e = 0;
        while (e <= 1) {
            e = rand() % (K-2)+2;
        }
        x = e;
        y = K;
        while ((r = x%y) != 0) {
            x = y;
            y = r;
        }
        g = y;
    }
    return e;
}

int kazuD(int L, int M) {
    int a1, a2, a3, b1, b2, b3, c1, c2, c3, w;

    a1 = 1;
    b1 = 0;
    c1 = L;
    a2 = 0;
    b2 = 1;
    c2 = M;
    while (c2 != 0) {
        w = c1 / c2;
        a3 = a1 - w*a2;
        b3 = b1 - w*b2;
        c3 = c1 - w*c2;
        a1 = a2;
        b1 = b2;
        c1 = c2;
        a2 = a3;
        b2 = b3;
        c2 = c3;
    }

    return b1;
}

int keta(int N) {
    int n, k;
    k = 0;

    n = N - 1;
    while (n != 0) {
        n = n / 10;
        ++k;
    }
    
    return k;
}

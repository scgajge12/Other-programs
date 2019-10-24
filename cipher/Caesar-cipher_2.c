/* Decoding　(解読用)  */

#include<stdio.h>
#define LEN 1000
int main(void) {
    char plain[LEN];
    char cipher[LEN];
    int key, i, n;

    printf("解読したい暗号文を入力してください(英文字で125字以内)\n=>");
    scanf("%s", &cipher);

    for (key = 1; key < 26; key++) {
        printf("鍵%dの場合:", key);
        for (i = 0; cipher[i] != '\0'; i++) {
            if (cipher[i] > 96) {
                n = ('z' - cipher[i] + key) % 26;
                plain[i] = 'z' - n;
            }
            else {
                n = ('Z' - cipher[i] + key) % 26;
                plain[i] = 'Z' - n;
            }
        }
        plain[i] = '\0';
        printf("%s\n", plain);
    }

    return 0;
}

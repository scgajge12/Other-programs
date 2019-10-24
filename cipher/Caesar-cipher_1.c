/* Encryption / decryption　(暗号化/復号化) */

#include<stdio.h>
#define LEN 125
int main(void) {
    char plain[LEN], Plain[LEN];
    char cipher[LEN], Cipher[LEN];
    int key, Key;
    int i, n;
   
    printf("平文を入力してください(英文字で125字以内)\n=>");
    scanf("%s", &plain);
    printf("鍵を入力してください\n=>");
    scanf("%d", &key);

    i = 0;
    while (plain[i] != '\0') {
        if (plain[i] > 96) {
            n = (plain[i] - 'a' + key) % 26;
            cipher[i] = n + 'a';
        }
        else {
            n = (plain[i] - 'A' + key) % 26;
            cipher[i] = n + 'A';
        }
        i++;
    }
    cipher[i] = '\0';
    printf("暗号文:%s\n", cipher);

    printf("\n");

    printf("暗号文を入力してください\n=>");
    scanf("%s", &Cipher);
    printf("鍵を入力してください\n=>");
    scanf("%d", &Key);

    i = 0;
    while (Cipher[i] != '\0') {
        if (Cipher[i] > 96) {
            n = ('z' - Cipher[i] + Key) % 26;
            Plain[i] = 'z' - n;
        }
        else {
            n = ('Z' - Cipher[i] + Key) % 26;
            Plain[i] = 'Z' - n;
        }
        i++;
    }
    Plain[i] = '\0';

    printf("平文:%s\n", Plain);

    return 0;
}

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void Espaco(char *str) {
    int i, j = 0;
    for (i = 0; str[i]; i++) {
        if (!isspace(str[i])) {
            str[j++] = tolower(str[i]);  
        }
    }
    str[j] = '\0';  
}

int Palindromo(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return 0;  
        }
    }
    return 1;  
}

int main() {
    char frase[100];
    printf("Digite uma frase: ");
    fgets(frase, sizeof(frase), stdin);
    Espaco(frase);
    
    if (Palindromo(frase)) {
        printf("A frase é palíndroma.\n");
    } else {
        printf("A frase não é palíndroma.\n");
    }

    return 0;
}

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

//#include <stdio.h>
//#include <string.h>
//#include <ctype.h>

//int Palindromo(char *str) {
//    int len = strlen(str);
//    int i = 0, j = len - 1;
//   while (i < j) {
//        while (!isalpha(str[i])) i++;  
//        while (!isalpha(str[j])) j--;
//
//      if (tolower(str[i]) != tolower(str[j])) {
//          return 0;  
//      }
//        i++;
//        j--;
//    }
//    return 1;  
//}

//int main() {
//    char frase[100];
//    printf("Digite uma frase: ");
//    fgets(frase, sizeof(frase), stdin);
//    
//    if (Palindromo(frase)) {
//        printf("A frase é palíndroma.\n");
//    } else {
//        printf("A frase não é palíndroma.\n");
//    }
//
//    return 0;
//}

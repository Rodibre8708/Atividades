#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_TITULO 50
#define TAM_ARTISTA 50
#define TAM_LOGIN 20
#define TAM_SENHA 20
#define MAX_USUARIOS 10

typedef struct Musica {
    char titulo[TAM_TITULO];
    char artista[TAM_ARTISTA];
    int minutos;
    int segundos;
    struct Musica *prox;
    struct Musica *ant;
} Musica;

typedef struct Usuario {
    char nome[50];
    char login[TAM_LOGIN];
    char senha[TAM_SENHA];
    Musica *listaReproducao;
    int totalMusicas;
} Usuario;

Usuario usuarios[MAX_USUARIOS];
int qtdUsuarios = 0;
Usuario *usuarioLogado = NULL;

// Funções de gerenciamento de músicas
void adicionarMusica();
void removerMusica();
void listarMusicas();
void limparLista();
void pesquisarMusica();
void ordenarMusicas();
void contarMusicas();
void menuUsuario();

// Funções de gerenciamento de usuário
void telaEscolhaUsuario();
void loginUsuario();
void cadastrarUsuario();
void exibirMenuPrincipal();

// Função principal
int main() {
    telaEscolhaUsuario();
    return 0;
}

// Funções para exibir e navegar nos menus
void telaEscolhaUsuario() {
    int opcao;
    do {
        printf("\n--- MENU INICIAL ---\n");
        printf("1. Login de usuário\n");
        printf("2. Cadastrar usuário\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: loginUsuario(); break;
            case 2: cadastrarUsuario(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while(opcao != 0);
}

void loginUsuario() {
    char login[TAM_LOGIN];
    char senha[TAM_SENHA];
    printf("Digite o login: ");
    scanf("%s", login);
    printf("Digite a senha: ");
    scanf("%s", senha);

    for (int i = 0; i < qtdUsuarios; i++) {
        if (strcmp(usuarios[i].login, login) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
            usuarioLogado = &usuarios[i];
            printf("Login realizado com sucesso! Bem-vindo, %s!\n", usuarioLogado->nome);
            menuUsuario();
            return;
        }
    }
    printf("Login ou senha incorretos.\n");
}

void cadastrarUsuario() {
    if (qtdUsuarios >= MAX_USUARIOS) {
        printf("Limite de usuários atingido.\n");
        return;
    }

    Usuario novoUsuario;
    printf("Digite seu nome: ");
    scanf(" %[^\n]s", novoUsuario.nome);
    printf("Digite um login: ");
    scanf("%s", novoUsuario.login);

    char senha[TAM_SENHA];
    char confirmacaoSenha[TAM_SENHA];

    do {
        printf("Digite a senha: ");
        scanf("%s", senha);
        printf("Confirme a senha: ");
        scanf("%s", confirmacaoSenha);

        if (strcmp(senha, confirmacaoSenha) != 0) {
            printf("As senhas não coincidem. Tente novamente.\n");
        }
    } while (strcmp(senha, confirmacaoSenha) != 0);

    strcpy(novoUsuario.senha, senha);
    novoUsuario.listaReproducao = NULL;
    novoUsuario.totalMusicas = 0;

    usuarios[qtdUsuarios++] = novoUsuario;
    printf("Usuário cadastrado com sucesso!\n");
}

void menuUsuario() {
    int opcao;
    do {
        printf("\n--- MENU DE REPRODUÇÃO ---\n");
        printf("1. Adicionar música\n");
        printf("2. Remover música\n");
        printf("3. Visualizar todas as músicas\n");
        printf("4. Limpar lista de músicas\n");
        printf("5. Pesquisar música\n");
        printf("6. Ordenar músicas por título\n");
        printf("7. Contar total de músicas\n");
        printf("0. Deslogar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: adicionarMusica(); break;
            case 2: removerMusica(); break;
            case 3: listarMusicas(); break;
            case 4: limparLista(); break;
            case 5: pesquisarMusica(); break;
            case 6: ordenarMusicas(); break;
            case 7: contarMusicas(); break;
            case 0: usuarioLogado = NULL; return;
            default: printf("Opção inválida!\n");
        }
    } while(opcao != 0);
}

// Funções de música (usar lista circular duplamente encadeada)
void adicionarMusica() {
    Musica *novaMusica = (Musica *)malloc(sizeof(Musica));
    if (!novaMusica) {
        printf("Erro de memória!\n");
        return;
    }

    printf("Digite o título da música: ");
    scanf(" %[^\n]", novaMusica->titulo);
    printf("Digite o artista: ");
    scanf(" %[^\n]", novaMusica->artista);
    printf("Digite a duração (minutos e segundos): ");
    scanf("%d %d", &novaMusica->minutos, &novaMusica->segundos);

    if (usuarioLogado->listaReproducao == NULL) {
        novaMusica->prox = novaMusica;
        novaMusica->ant = novaMusica;
        usuarioLogado->listaReproducao = novaMusica;
    } else {
        Musica *fim = usuarioLogado->listaReproducao->ant;
        fim->prox = novaMusica;
        novaMusica->ant = fim;
        novaMusica->prox = usuarioLogado->listaReproducao;
        usuarioLogado->listaReproducao->ant = novaMusica;
    }
    usuarioLogado->totalMusicas++;
    printf("Música adicionada com sucesso!\n");
}

void removerMusica() {
    if (usuarioLogado->listaReproducao == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    char titulo[TAM_TITULO];
    printf("Digite o título da música a ser removida: ");
    scanf(" %[^\n]", titulo);

    Musica *atual = usuarioLogado->listaReproducao;
    int encontrado = 0;
    do {
        if (strcmp(atual->titulo, titulo) == 0) {
            if (atual->prox == atual) {
                usuarioLogado->listaReproducao = NULL;
            } else {
                atual->ant->prox = atual->prox;
                atual->prox->ant = atual->ant;
                if (atual == usuarioLogado->listaReproducao) {
                    usuarioLogado->listaReproducao = atual->prox;
                }
            }
            free(atual);
            usuarioLogado->totalMusicas--;
            printf("Música removida com sucesso!\n");
            encontrado = 1;
            break;
        }
        atual = atual->prox;
    } while (atual != usuarioLogado->listaReproducao);

    if (!encontrado) {
        printf("Música não encontrada.\n");
    }
}

void listarMusicas() {
    if (usuarioLogado->listaReproducao == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    Musica *atual = usuarioLogado->listaReproducao;
    printf("\n--- Lista de Músicas ---\n");
    do {
        printf("Título: %s, Artista: %s, Duração: %d:%02d\n", atual->titulo, atual->artista, atual->minutos, atual->segundos);
        atual = atual->prox;
    } while (atual != usuarioLogado->listaReproducao);
}

void limparLista() {
    if (usuarioLogado->listaReproducao == NULL) {
        printf("A lista já está vazia.\n");
        return;
    }

    Musica *atual = usuarioLogado->listaReproducao;
    do {
        Musica *prox = atual->prox;
        free(atual);
        atual = prox;
    } while (atual != usuarioLogado->listaReproducao);

    usuarioLogado->listaReproducao = NULL;
    usuarioLogado->totalMusicas = 0;
    printf("Lista de reprodução limpa.\n");
}

void pesquisarMusica() {
    if (usuarioLogado->listaReproducao == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    char titulo[TAM_TITULO];
    printf("Digite o título da música a ser pesquisada: ");
    scanf(" %[^\n]", titulo);

    Musica *atual = usuarioLogado->listaReproducao;
    int encontrado = 0;
    do {
        if (strcmp(atual->titulo, titulo) == 0) {
            printf("Música encontrada: %s - %s, Duração: %d:%02d\n", atual->titulo, atual->artista, atual->minutos, atual->segundos);
            encontrado = 1;
            break;
        }
        atual = atual->prox;
    } while (atual != usuarioLogado->listaReproducao);

    if (!encontrado) {
        printf("Música não encontrada.\n");
    }
}

void ordenarMusicas() {
    if (usuarioLogado->listaReproducao == NULL || usuarioLogado->listaReproducao->prox == usuarioLogado->listaReproducao) {
        printf("Não há músicas suficientes para ordenar.\n");
        return;
    }

    Musica *atual = usuarioLogado->listaReproducao;
    Musica *prox;
    do {
        prox = atual->prox;
        while (prox != usuarioLogado->listaReproducao) {
            if (strcmp(atual->titulo, prox->titulo) > 0) {
                char tituloTemp[TAM_TITULO], artistaTemp[TAM_ARTISTA];
                int minutosTemp, segundosTemp;

                strcpy(tituloTemp, atual->titulo);
                strcpy(artistaTemp, atual->artista);
                minutosTemp = atual->minutos;
                segundosTemp = atual->segundos;

                strcpy(atual->titulo, prox->titulo);
                strcpy(atual->artista, prox->artista);
                atual->minutos = prox->minutos;
                atual->segundos = prox->segundos;

                strcpy(prox->titulo, tituloTemp);
                strcpy(prox->artista, artistaTemp);
                prox->minutos = minutosTemp;
                prox->segundos = segundosTemp;
            }
            prox = prox->prox;
        }
        atual = atual->prox;
    } while (atual->prox != usuarioLogado->listaReproducao);

    printf("Lista de músicas ordenada.\n");
}

void contarMusicas() {
    printf("Total de músicas na lista: %d\n", usuarioLogado->totalMusicas);
}

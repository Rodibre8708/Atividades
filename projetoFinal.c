#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX_PLYLST 200
#define TAM_NOME 50
#define TAM_LOGIN 15
#define TAM_SENHA 15
#define TAM_PLAYLIST 100
#define TAM_TITULO 50
#define TAM_MUSICAS 100 

struct Musica{
    int codigo; // autoincremento
    char titulo[TAM_TITULO]; // título da música
    char artista[TAM_NOME]; // nome do artista que canta esta música
};

struct Playlist{
    int codigo; // autoincremento
    int codUsuario; // o código do usuário que criou a playlist
    char titulo[TAM_TITULO]; // título desta playlist
    int qtdMusicas; // qtd atual de músicas incluídas nesta playlist
    int musicas[TAM_MUSICAS]; // vetor contendo os códigos das músicas
};

struct Usuario{
    int codigo; // autoincremento
    char nome[TAM_NOME];
    char login[TAM_LOGIN];
    char senha[TAM_SENHA];
    int qtdPlaylists;  // quantid. de playlists criadas pelo usuário
    struct Playlist playlists[TAM_PLAYLIST]; // todas playlists criadas
    int qtdPlaylistsFav; // quantid. de playlists favoritadas pelo usuário
    int playlistsFav[TAM_PLAYLIST]; // códigos das playlists favoritadas pelo usuário
} ;

struct Musica musicas[TAM_MAX_PLYLST];
int qtdMusicas = 0;

struct Usuario usuarios[TAM_MAX_PLYLST];
int qtdUsuarios = 0;

struct Usuario *usuarioLogado = NULL;

void telaMenuPrincipal();   

void gerarDadosAutomaticos();

void menuAdministrador();

void listarUsuarios(); // todos
void consultarUsuario(); // por codigo login nome
void alterarSenhaDeUmUsuario();
void cadastrarMusica();
void listarMusicas(); // todas
void consultarMusica(); // por codigo titulo nome artista
void alterarDadosMusica();
void excluirMusica();
void listarPlaylists(); // todas
void consultarPlaylist(); // por codigo titulo (especifica)

void telaEscolhaUsuario(); // login ou cadastro

void loginUsuario();
void cadastrarUsuario();

void menuUsuario();

void verSeusDados();
void alterarNomeUsuario();
void alterarLoginUsuario();
void alterarSuaSenha(); 
void verTodosUsuarios(); // todos  (so o nome)
void verUsuarios(); // parte nome (especifico) 
void verSuasPlaylists();   // so as suas
void verTodasPlaylists(); // todas sem as suas
void verPlaylist(); // codigo titulo (especifica) primeiro a sua
void cadastrarPlaylist();
void inserirMusicaPlaylist();
void excluirMusicaPlaylist();
void excluirPlaylist();
void favoritarPlaylist();

////////////////////////
int main() {
    telaMenuPrincipal();
    return 0;
}
////////////////////////

// menu principal solto

void telaMenuPrincipal() {
    int opcao;
    printf("Menu principal:\n");
    printf("1. Administrador\n");
    printf("2. Usuário\n");
    printf("3. Gerar dados automáticos\n");
    printf("0. Fechar\n");
    scanf("%d", &opcao);

    switch(opcao) {
        case 1:
            menuAdministrador();
            break;
        case 2:
            telaEscolhaUsuario();
            break;
        case 3:
            gerarDadosAutomaticos();
            break;
        case 0:
            exit(0);
        default:
            printf("Opção inválida!\n");
            telaMenuPrincipal();
    }
}

// parte de adm

void menuAdministrador() {
    char senha[TAM_SENHA];
    printf("Digite a senha do administrador: ");
    scanf("%s", senha);

    if(strcmp(senha, "m@st3r2024") != 0) {
        printf("Senha incorreta!\n");
        telaMenuPrincipal();    
        
    }

    int opcao;
    do {
        printf("Menu de administrador:\n");
        printf("1. Listar usuários\n");
        printf("2. Consultar usuário por código, login ou parte do nome\n");
        printf("3. Alterar a senha de um usuário\n");
        printf("4. Cadastrar novas músicas\n");
        printf("5. Listar todas as músicas\n");
        printf("6. Consultar músicas por código, parte do título da música ou parte do nome do artista \n");
        printf("7. Alterar dados de músicas cadastradas\n");
        printf("8. Excluir músicas cadastradas\n");
        printf("9. Listar todas as playlists\n");
        printf("10. Consultar playlist por código da playlist, parte do título da playlist, por código de música\n");
        printf("0. Sair\n");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                listarUsuarios();
                break;
            case 2:
                consultarUsuario();
                break;
            case 3:
                alterarSenhaDeUmUsuario();
                break;
            case 4:
                cadastrarMusica();
                break;
            case 5:
                listarMusicas();
                break;
            case 6:
                consultarMusica();
                break;
            case 7:
                alterarDadosMusica();
                break;
            case 8:
                excluirMusica();
                break;
            case 9:
                listarPlaylists();
                break;
            case 10:
                consultarPlaylist();
                break;
            case 0:
                telaMenuPrincipal();
                return;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);
}

void listarUsuarios() {
    if (qtdUsuarios == 0) {
        printf("Nenhum usuário cadastrado.\n");
        return;
    }

    for (int i = 0; i < qtdUsuarios; i++) {
        printf("Código: %d\nNome: %s\nLogin: %s\n\n", usuarios[i].codigo, usuarios[i].nome, usuarios[i].login);
    }
}

void consultarUsuario() {
    char consulta[TAM_NOME];
    printf("Digite o código, login ou parte do nome do usuário: ");
    scanf(" %[^\n]s", consulta);

    int encontrado = 0;
    for (int i = 0; i < qtdUsuarios; i++) {
        if (strstr(usuarios[i].nome, consulta) || strstr(usuarios[i].login, consulta) || atoi(consulta) == usuarios[i].codigo) {
            printf("Código: %d\nNome: %s\nLogin: %s\n", usuarios[i].codigo, usuarios[i].nome, usuarios[i].login);
            printf("Playlists Favoritas: %d\n", usuarios[i].qtdPlaylistsFav);
            for (int j = 0; j < usuarios[i].qtdPlaylistsFav; j++) {
                printf("%d ", usuarios[i].playlistsFav[j]);
            }
            printf("\n");
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("Usuário não encontrado.\n");
    }
}


void alterarSenhaDeUmUsuario() {
    int codigo;
    char senhaAtual[TAM_SENHA];
    char novaSenha[TAM_SENHA];
    printf("Digite o código do usuário: ");
    scanf("%d", &codigo);

    for (int i = 0; i < qtdUsuarios; i++) {
        if (usuarios[i].codigo == codigo) {
            printf("Digite a senha atual: ");
            scanf("%s", senhaAtual);
            if (strcmp(usuarios[i].senha, senhaAtual) == 0) {
                printf("Digite a nova senha: ");
                scanf("%s", novaSenha);
                strcpy(usuarios[i].senha, novaSenha);
                printf("Senha alterada com sucesso.\n");
                return;
            } else {
                printf("Senha atual incorreta. Não foi possível alterar a senha.\n");
                return;
            }
        }
    }
    printf("Usuário não encontrado.\n");
}

void cadastrarMusica() {
    if (qtdMusicas >= TAM_MUSICAS) {
        printf("Limite de músicas atingido.\n");
        return;
    }

    struct Musica novaMusica;
    novaMusica.codigo = qtdMusicas + 1;
    printf("Digite o título da música: ");
    scanf(" %[^\n]s", novaMusica.titulo);
    printf("Digite o artista da música: ");
    scanf(" %[^\n]s", novaMusica.artista);

    musicas[qtdMusicas++] = novaMusica;
    printf("Música cadastrada com sucesso.\n");
}

void listarMusicas() {
    if (qtdMusicas == 0) {
        printf("Nenhuma música cadastrada.\n");
        return;
    }

    printf("Músicas:\n");
    for(int i = 0; i < qtdMusicas; i++) {
        printf("Código: %d, Título: %s, Artista: %s\n", musicas[i].codigo, musicas[i].titulo, musicas[i].artista);
    }
}


void consultarMusica() {
    char consulta[TAM_TITULO];
    printf("Digite código, parte do título da música ou nome do artista: ");
    scanf("%s", consulta);

    printf("Músicas encontradas:\n");
    for(int i = 0; i < qtdMusicas; i++) {
        if(strstr(musicas[i].titulo, consulta) != NULL || strstr(musicas[i].artista, consulta) != NULL || atoi(consulta) == musicas[i].codigo) {
            printf("Código: %d, Título: %s, Artista: %s\n", musicas[i].codigo, musicas[i].titulo, musicas[i].artista);
        }
    }
}

void alterarDadosMusica() {
    int codigo;
    printf("Digite o código da música: ");
    scanf("%d", &codigo);

    for (int i = 0; i < qtdMusicas; i++) {
        if (musicas[i].codigo == codigo) {
            printf("Digite o novo título da música: ");
            scanf(" %[^\n]s", musicas[i].titulo);
            printf("Digite o novo artista da música: ");
            scanf(" %[^\n]s", musicas[i].artista);
            printf("Música alterada com sucesso.\n");
            return;
        }
    }
    printf("Música não encontrada.\n");
}

void excluirMusica() {
    int codigo;
    printf("Digite o código da música: ");
    scanf("%d", &codigo);

    for (int i = 0; i < qtdMusicas; i++) {
        if (musicas[i].codigo == codigo) {
            for (int j = i; j < qtdMusicas - 1; j++) {
                musicas[j] = musicas[j + 1];
            }
            qtdMusicas--;
            printf("Música excluída com sucesso.\n");
            return;
        }
    }
    printf("Música não encontrada.\n");
}

void listarPlaylists() {
    if (qtdUsuarios == 0) {
        printf("Nenhuma playlist cadastrada.\n");
        return;
    }

    for (int i = 0; i < qtdUsuarios; i++) {
        struct Usuario usuario = usuarios[i];
        printf("Usuário: %s\n", usuario.nome);
        for (int j = 0; j < usuario.qtdPlaylists; j++) {
            struct Playlist playlist = usuario.playlists[j];
            printf("  Código: %d\n  Título: %s\n  Músicas: %d\n", playlist.codigo, playlist.titulo, playlist.qtdMusicas);
            for (int k = 0; k < playlist.qtdMusicas; k++) {
                for (int l = 0; l < qtdMusicas; l++) {
                    if (musicas[l].codigo == playlist.musicas[k]) {
                        printf("    Música: %s - %s\n", musicas[l].titulo, musicas[l].artista);
                    }
                }
            }
        }
        printf("\n");
    }
}

void consultarPlaylist() {
    int codigo;
    printf("Digite o código, parte do título, código música:");
    scanf("%d", &codigo);

    for (int i = 0; i < qtdUsuarios; i++) {
        for (int j = 0; j < usuarios[i].qtdPlaylists; j++) {
            if (usuarios[i].playlists[j].codigo == codigo) {
                struct Playlist playlist = usuarios[i].playlists[j];
                printf("Usuário: %s\n", usuarios[i].nome);
                printf("Código: %d\nTítulo: %s\nMúsicas: %d\n", playlist.codigo, playlist.titulo, playlist.qtdMusicas);
                for (int k = 0; k < playlist.qtdMusicas; k++) {
                    for (int l = 0; l < qtdMusicas; l++) {
                        if (musicas[l].codigo == playlist.musicas[k]) {
                            printf("  Música: %s - %s\n", musicas[l].titulo, musicas[l].artista);
                        }
                    }
                }
                return;
            }
        }
    }
    printf("Playlist não encontrada.\n");
}

// dados solto

void gerarDadosAutomaticos() {                                                  
    qtdUsuarios = 0;
    qtdMusicas = 0;

    struct Musica musica1 = {1, "Água de chuva no mar", "Beth Carvalho"};
    struct Musica musica2 = {2, "Menina Mulher Da Pele Preta", "Jorge Ben Jor"};
    struct Musica musica3 = {3, "War", "Bob Marley & The Wailers"};
    struct Musica musica4 = {4, "A Praiera", "Chico Science, Nação Zumbi"};
    struct Musica musica5 = {5, "Rock with You", "Michael Jackson"};
    
    musicas[qtdMusicas++] = musica1;
    musicas[qtdMusicas++] = musica2;
    musicas[qtdMusicas++] = musica3;
    musicas[qtdMusicas++] = musica4;
    musicas[qtdMusicas++] = musica5;

    struct Usuario usuario1 = {1, "Durval", "xerife", "sport", 0, {}, 0, {}};
    struct Usuario usuario2 = {2, "Magrão", "idolo", "8708", 0, {}, 0, {}};

    struct Playlist playlist1 = {1, 1, "Playlist de Durval", 3, {1, 2, 3}};
    struct Playlist playlist2 = {2, 2, "Playlist de Magrão", 2, {4, 5}};

    usuario1.playlists[usuario1.qtdPlaylists++] = playlist1;
    usuario2.playlists[usuario2.qtdPlaylists++] = playlist2;

    usuarios[qtdUsuarios++] = usuario1;
    usuarios[qtdUsuarios++] = usuario2;

    printf("Dados automáticos gerados com sucesso.\n");

    telaMenuPrincipal();
}

// parte de usuario

void telaEscolhaUsuario(){
    int opcao;
    printf("1. Login usuário\n");
    printf("2. Cadastrar usuário\n");
    printf("0. Voltar\n");
    scanf("%d", &opcao);

    switch(opcao) {
        case 1:
            loginUsuario();
            break;
        case 2:
            cadastrarUsuario();
            break;
        case 0:
            telaMenuPrincipal();
        default:
            printf("Opção inválida!\n");
            telaEscolhaUsuario();
    }
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
            menuUsuario();
            return;
        }
    }
    printf("Login ou senha incorretos ou usuário não existe.\n");
    telaEscolhaUsuario();
}

void cadastrarUsuario() {
    if (qtdUsuarios >= TAM_MAX_PLYLST) {
        printf("Limite de usuários atingido.\n");
        return;
    }

    struct Usuario novoUsuario;
    novoUsuario.codigo = qtdUsuarios + 1;
    printf("Digite o nome: ");
    scanf(" %[^\n]s", novoUsuario.nome);
    printf("Digite o login: ");
    scanf("%s", novoUsuario.login);

    char senha[TAM_SENHA];
    char confirmacaoSenha[TAM_SENHA];

    do {
        printf("Digite a senha: ");
        scanf("%s", senha);
        printf("Confirme a senha: ");
        scanf("%s", confirmacaoSenha);

        if (strcmp(senha, confirmacaoSenha) != 0) {
            printf("As senhas estão diferentes. Tente novamente.\n");
        }
    } while (strcmp(senha, confirmacaoSenha) != 0);

    strcpy(novoUsuario.senha, senha);
    novoUsuario.qtdPlaylists = 0;
    novoUsuario.qtdPlaylistsFav = 0;

    usuarios[qtdUsuarios++] = novoUsuario;
    printf("Usuário cadastrado com sucesso.\n");
    telaEscolhaUsuario();
}


void menuUsuario() {
    int opcao;
    do {
        printf("Menu de usuário:\n");
        printf("1. Listar seus dados\n");
        printf("2. Alterar o nome do usuário\n");
        printf("3. Alterar o login do usuário\n");
        printf("4. Alterar a senha do usuário\n");
        printf("5. Listar usuários\n");
        printf("6. Consultar usuários por parte do nome\n");
        printf("7. Listar todas as músicas\n");
        printf("8. Consultar músicas por código, parte do título da música ou parte do nome do artista\n");
        printf("9. Listar todas as suas playlists\n");
        printf("10. Listar todas as playlists\n");
        printf("11. Consultar playlist por código da playlist, parte do título da playlist, por código de música\n");
        printf("12. Cadastrar uma playlist\n");
        printf("13. Inserir música na playlist sua \n");
        printf("14. Excluir música de uma playlist sua\n");
        printf("15. Excluir uma playlist\n");
        printf("16. Favoritar uma playlist\n");
        printf("0. Deslogar\n");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                verSeusDados();
                break;
            case 2:
                alterarNomeUsuario();
                break;
            case 3:
                alterarLoginUsuario();
                break;
            case 4:
                alterarSuaSenha();
                break;
            case 5:
                verTodosUsuarios();
                break;
            case 6:
                verUsuarios();
                break;
            case 7:
                listarMusicas();
                break;
            case 8:
                consultarMusica();
                break;
            case 9:
                verSuasPlaylists();
                break;
            case 10:
                verTodasPlaylists();
                break;
            case 11:
                verPlaylist();
                break;
            case 12:
                cadastrarPlaylist();
                break;
            case 13:
                inserirMusicaPlaylist();
                break;
            case 14:
                excluirMusicaPlaylist();
                break;
            case 15:
                excluirPlaylist();
                break;
            case 16:
                favoritarPlaylist();
                break;
            case 0:
                usuarioLogado = NULL;
                telaEscolhaUsuario();
                return;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);
}

void verSeusDados() {
    printf("Código: %d\nNome: %s\nLogin: %s\n", usuarioLogado->codigo, usuarioLogado->nome, usuarioLogado->login);
    printf("Playlists Favoritas: %d\n", usuarioLogado->qtdPlaylistsFav);
    for (int i = 0; i < usuarioLogado->qtdPlaylistsFav; i++) {
        printf("%d ", usuarioLogado->playlistsFav[i]);
    }
    printf("\n");
}

void alterarNomeUsuario() {
    char senha[TAM_SENHA];
    char novoNome[TAM_NOME];
    printf("Digite a senha para confirmar: ");
    scanf("%s", senha);

    if (strcmp(usuarioLogado->senha, senha) == 0) {
        printf("Digite o novo nome: ");
        scanf(" %[^\n]s", novoNome);
        strcpy(usuarioLogado->nome, novoNome);
        printf("Nome alterado com sucesso.\n");
    } else {
        printf("Senha incorreta. Não foi possível alterar o nome.\n");
    }
}

void alterarLoginUsuario() {
    char senha[TAM_SENHA];
    char novoLogin[TAM_LOGIN];
    printf("Digite a senha para confirmar: ");
    scanf("%s", senha);

    if (strcmp(usuarioLogado->senha, senha) == 0) {
        printf("Digite o novo login: ");
        scanf("%s", novoLogin);
        strcpy(usuarioLogado->login, novoLogin);
        printf("Login alterado com sucesso.\n");
    } else {
        printf("Senha incorreta. Não foi possível alterar o login.\n");
    }
}

void alterarSuaSenha() {
    char senhaAtual[TAM_SENHA];
    char novaSenha[TAM_SENHA];
    printf("Digite a senha atual: ");
    scanf("%s", senhaAtual);

    if (strcmp(usuarioLogado->senha, senhaAtual) == 0) {
        printf("Digite a nova senha: ");
        scanf("%s", novaSenha);
        strcpy(usuarioLogado->senha, novaSenha);
        printf("Senha alterada com sucesso.\n");
    } else {
        printf("Senha atual incorreta. Não foi possível alterar a senha.\n");
    }
}

void verTodosUsuarios() {                     
    printf("Usuários:\n");
    for(int i = 0; i < qtdUsuarios; i++) {
        printf("%s\n", usuarios[i].nome);
    }
}

void verUsuarios() {                        
    char nome[TAM_NOME];
    printf("Digite parte do nome: ");
    scanf("%s", nome);

    printf("Usuários encontrados:\n");
    for(int i = 0; i < qtdUsuarios; i++) {
        if(strstr(usuarios[i].nome, nome) != NULL) {
            printf("%s\n", usuarios[i].nome);
        }
    }
}

void verPlaylist() {  
    int codigo;
    printf("Digite o código, parte do título, código música: ");
    scanf("%d", &codigo);

    for(int i = 0; i < usuarioLogado->qtdPlaylists; i++) {
        if(usuarioLogado->playlists[i].codigo == codigo) {
            printf("Título: %s\n", usuarioLogado->playlists[i].titulo);
            printf("Músicas:\n");
            for(int j = 0; j < usuarioLogado->playlists[i].qtdMusicas; j++) {
                int codMusica = usuarioLogado->playlists[i].musicas[j];
                for(int k = 0; k < qtdMusicas; k++) {
                    if(musicas[k].codigo == codMusica) {
                        printf("%s - %s\n", musicas[k].titulo, musicas[k].artista);
                    }
                }
            }
            return;
        }
    }

    printf("Playlist não encontrada!\n");
}

void verSuasPlaylists() {   
    if (usuarioLogado->qtdPlaylists == 0) {
        printf("Nenhuma playlist cadastrada.\n");
        return;
    }

    for (int i = 0; i < usuarioLogado->qtdPlaylists; i++) {
        struct Playlist playlist = usuarioLogado->playlists[i];
        printf("Código: %d\nTítulo: %s\nMúsicas: %d\n", playlist.codigo, playlist.titulo, playlist.qtdMusicas);
        for (int j = 0; j < playlist.qtdMusicas; j++) {
            for (int k = 0; k < qtdMusicas; k++) {
                if (musicas[k].codigo == playlist.musicas[j]) {
                    printf("  Música: %s - %s\n", musicas[k].titulo, musicas[k].artista);
                }
            }
        }
        printf("\n");
    }
}

void verTodasPlaylists() {
    if (qtdUsuarios == 0) {
        printf("Nenhuma playlist cadastrada.\n");
        return;
    }

    for (int i = 0; i < qtdUsuarios; i++) {
        if (usuarios[i].codigo == usuarioLogado->codigo) continue;

        struct Usuario usuario = usuarios[i];
        printf("Usuário: %s\n", usuario.nome);
        for (int j = 0; j < usuario.qtdPlaylists; j++) {
            struct Playlist playlist = usuario.playlists[j];
            printf("  Código: %d\n  Título: %s\n  Músicas: %d\n", playlist.codigo, playlist.titulo, playlist.qtdMusicas);
            for (int k = 0; k < playlist.qtdMusicas; k++) {
                for (int l = 0; l < qtdMusicas; l++) {
                    if (musicas[l].codigo == playlist.musicas[k]) {
                        printf("    Música: %s - %s\n", musicas[l].titulo, musicas[l].artista);
                    }
                }
            }
        }
        printf("\n");
    }
}

void cadastrarPlaylist() {
    if (usuarioLogado->qtdPlaylists >= TAM_PLAYLIST) {
        printf("Limite de playlists atingido.\n");
        return;
    }

    struct Playlist novaPlaylist;
    novaPlaylist.codigo = usuarioLogado->qtdPlaylists + 1;
    novaPlaylist.codUsuario = usuarioLogado->codigo;
    printf("Digite o título da playlist: ");
    scanf(" %[^\n]s", novaPlaylist.titulo);
    novaPlaylist.qtdMusicas = 0;

    usuarioLogado->playlists[usuarioLogado->qtdPlaylists++] = novaPlaylist;
    printf("Playlist cadastrada com sucesso.\n");
}

void inserirMusicaPlaylist() {
    int codigoPlaylist;
    int codigoMusica;
    printf("Digite o código da playlist: ");
    scanf("%d", &codigoPlaylist);
    printf("Digite o código da música: ");
    scanf("%d", &codigoMusica);

    for (int i = 0; i < usuarioLogado->qtdPlaylists; i++) {
        if (usuarioLogado->playlists[i].codigo == codigoPlaylist) {
            if (usuarioLogado->playlists[i].qtdMusicas >= TAM_MUSICAS) {
                printf("Limite de músicas na playlist atingido.\n");
                return;
            }

            for (int j = 0; j < qtdMusicas; j++) {
                if (musicas[j].codigo == codigoMusica) {
                    usuarioLogado->playlists[i].musicas[usuarioLogado->playlists[i].qtdMusicas++] = codigoMusica;
                    printf("Música inserida na playlist com sucesso.\n");
                    return;
                }
            }
            printf("Música não encontrada.\n");
            return;
        }
    }
    printf("Playlist não encontrada.\n");
}

void excluirMusicaPlaylist() {
    int codigoPlaylist;
    int codigoMusica;
    printf("Digite o código da playlist: ");
    scanf("%d", &codigoPlaylist);
    printf("Digite o código da música: ");
    scanf("%d", &codigoMusica);

    for (int i = 0; i < usuarioLogado->qtdPlaylists; i++) {
        if (usuarioLogado->playlists[i].codigo == codigoPlaylist) {
            for (int j = 0; j < usuarioLogado->playlists[i].qtdMusicas; j++) {
                if (usuarioLogado->playlists[i].musicas[j] == codigoMusica) {
                    for (int k = j; k < usuarioLogado->playlists[i].qtdMusicas - 1; k++) {
                        usuarioLogado->playlists[i].musicas[k] = usuarioLogado->playlists[i].musicas[k + 1];
                    }
                    usuarioLogado->playlists[i].qtdMusicas--;
                    printf("Música excluída da playlist com sucesso.\n");
                    return;
                }
            }
            printf("Música não encontrada na playlist.\n");
            return;
        }
    }
    printf("Playlist não encontrada.\n");
}

void excluirPlaylist() {
    int codigo;
    printf("Digite o código da playlist: ");
    scanf("%d", &codigo);

    for (int i = 0; i < usuarioLogado->qtdPlaylists; i++) {
        if (usuarioLogado->playlists[i].codigo == codigo) {
            for (int j = i; j < usuarioLogado->qtdPlaylists - 1; j++) {
                usuarioLogado->playlists[j] = usuarioLogado->playlists[j + 1];
            }
            usuarioLogado->qtdPlaylists--;
            printf("Playlist excluída com sucesso.\n");
            return;
        }
    }
    printf("Playlist não encontrada.\n");
}

void favoritarPlaylist() {
    int codigo;
    printf("Digite o código da playlist: ");
    scanf("%d", &codigo);

    for (int i = 0; i < usuarioLogado->qtdPlaylistsFav; i++) {
        if (usuarioLogado->playlistsFav[i] == codigo) {
            printf("Playlist já favoritada.\n");
            return;
        }
    }

    for (int i = 0; i < qtdUsuarios; i++) {
        for (int j = 0; j < usuarios[i].qtdPlaylists; j++) {
            if (usuarios[i].playlists[j].codigo == codigo) {
                usuarioLogado->playlistsFav[usuarioLogado->qtdPlaylistsFav++] = codigo;
                printf("Playlist favoritada com sucesso.\n");
                return;
            }
        }
    }
    printf("Playlist não encontrada.\n");
}

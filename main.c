#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

// ***** DEFINIÇÕES DE CONSTANTES ***** //
#define MAX_NOME 50
#define MAX_DATA 20
#define MAX_HORA 10
#define MAX_EVENTOS 100
#define MAX_MESAS 10
#define MAX_ARQUIVO 100
#define MAX_USUARIO 20
#define MAX_SENHA 20
#define MAX_CPF 14
#define MAX_EMAIL 50
#define MAX_TELEFONE 20
#define MAX_TAMANHO 50
#define MAX_DESCRICAO 200
// ************************************ //

// ***** DEFINIÇÕES DE CORES ***** //
#define RED "\e[1;91m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[0;33m"
#define BLUE "\e[0;34m"
#define PURPLE "\e[0;35m"
#define WHITE "\e[0;37m"
#define CYAN "\e[0;36m"
#define RESET "\e[m"
#define WHITEB "\e[47m"
// ******************************* //

char* tipoUsuario[MAX_USUARIO];
int isAdmin=0;

// ***** DEFINIÇÕES DAS STRUCTS ***** //
struct CursorPos {
    int linha;
    int coluna;
};
typedef struct { // Struct do Evento

    int idEvento; // Número identificador de evento

    // Informações do contratante do evento
    char nomeContratante[MAX_USUARIO];
    char cpfContratante[MAX_CPF];
    char emailContratante[MAX_EMAIL];
    char telefoneContratante[MAX_TELEFONE];

    // Detalhes do evento
    char nomeEvento[MAX_NOME];
    char descricaoEvento[MAX_DESCRICAO];
    int quantidadePessoas;
    int dia, mes, ano;

    // Car
    char nomeCardapio[MAX_TAMANHO];
    char descricaoCardapio[MAX_DESCRICAO];
    char ingredientesCardapio[MAX_DESCRICAO];
    int quantidadePessoasCardapio;

    // Local
    char nomeLocal[100];
    char enderecoLocal[100];
    char descricaoAmbienteLocal[MAX_DESCRICAO];
    char telefoneLocal[MAX_TELEFONE];
    int lotacaoMaximaLocal;

    // Valores
    float valorEstimado;
    float valorCardapio;
    float valorLocal;

    int status; // '0' cancelado, '1' para em andamento, '2' concluído

} Evento;
typedef struct { // Struct do Cardápio
    char nome[50];
    char descricao[100];
    char ingredientes[200];
    int quantidadePessoas;
    float valor;
    int disponibilidade;
} Cardapio;
typedef struct{ // Struct do Local
    char nome[50];
    char endereco[100];
    float valorLocacao;
    char descricaoAmbiente[200];
    char telefone[MAX_TELEFONE];
    int lotacaoMaxima;
} Local;
typedef struct { // Struct do Funcionário
    char nome[MAX_USUARIO];
    char cpf[MAX_CPF];
    char funcao[MAX_TAMANHO];
    double salarioHora;
    char email[MAX_EMAIL];
    char telefone[MAX_TELEFONE];
    int disponibilidade;
} Funcionario;
typedef struct { // Struct do Usuário
    char login[MAX_USUARIO];
    char senha[MAX_SENHA];
    char nome[MAX_USUARIO];
    char cpf[MAX_CPF];
    char email[MAX_EMAIL];
    char telefone[MAX_TELEFONE];
    int disponibilidade;
} Usuario;
// ********************************* //

// ***** DECLARAÇÕES DAS FUNÇÕES MENU ***** //
void exibirMenuPrincipal();
void exibirMenuAdmin();
void exibirSubMenuGerencimento();
void exibirSubMenuEventos();
void exibirSubMenuCardapio();
void exibirSubMenuUsuario();
void exibirSubMenuFuncionario();
void exibirSubMenuLocais();
// **************************************** //

// ***** DECLARAÇÃO DA FUNÇÃO DE LOGIN ***** //
int fazerLogin(char *arquivo, char *tipoUsuario);
// ***************************************** //

// ***** DECLARAÇÕES DAS FUNÇÕES PARA LIMPAR CONSOLE ***** //
void limparBuffer();
void limparConsole();
void apagarMensagemAposTempo();
// ******************************************************* //

//DECLARAÇÕES DE FUNÇÕES CRUD LUGAR
void criarLocal();
void modificarLocal();
void excluirLocal();
void exibirLocalDoArquivo();
void exibirLocal();

//DECLARAÇÕES DE FUNÇÕES CRUD FUNCIONARIO
void criarFuncionario();
void modificarFuncionario();
void excluirFuncionario();
void exibirFuncionarioDoArquivo();
void exibirFuncionario();

//DECLARAÇÕES DE FUNÇÕES CRUD CARDAPIO
void criarCardapio();
void atualizarCardapio();
void excluirCardapio();
void exibirCardapiosDoArquivo();
void exibirCardapio();

//DECLARAÇÕES DE FUNÇÕES CRUD USUARIO
void criarUsuario();
void modificarUsuario();
void excluirUsuario();
void exibirUsuariosDoArquivo();
void exibirUsuarios();

//DECLARAÇÕES DE FUNÇÕES LER COM VALIDAÇÃO
int validandoAnoBissexto();
int validandoData();
void lerString();
void lerCPFValidado();
void lerFuncaoValidada();
void lerEmailValidado();
void lerTelefoneValidado();
int confirmarExclusao();
int confirmarContinuacao();
int validarEntradaInt();
double validarEntradaDouble();
bool validarEmail();
bool validarTelefone();
int validarCPF();
bool verificarCPF();

//////////
int idGerador();

//DECLARAÇÕES DE FUNÇÕES PAUSA
void pausar();
//DECLARAÇÕES DE FUNÇÕES POSICAO CURSOR
struct CursorPos pegarCursorPos();
void moveCursorParaPosicao();

// ***** FUNÇÃO PRINCIPAL ***** //
int main(){

    setlocale(LC_ALL, "");

    exibirMenuPrincipal();

    return 0;
}
// **************************** //

// ***** FUNÇÕES DE MENU ***** //
void exibirMenuPrincipal(){

    int escolha;

    do{

        system(CLEAR_SCREEN);

        printf("\n\t|-------------------------------------------|\n");
        printf("\t| Sistema de Gerenciamento - %sDebroi Eventos%s |\n", CYAN, RESET);
        printf("\t|-------------------------------------------|\n");
        printf("\t| 1 | Iniciar como %sAdministrador%s            |\n", GREEN, RESET);
        printf("\t|-------------------------------------------|\n");
        printf("\t| 2 | Iniciar como %sUsuário%s                  |\n", YELLOW, RESET);
        printf("\t|-------------------------------------------|\n");
        printf("\t| 3 | %sSair do Programa%s                      |\n", RED, RESET);
        printf("\t|-------------------------------------------|\n");
        printf("\n\t      Escolha uma opção: ");

        escolha=validarEntradaInt();

        switch(escolha){

            case 1:
                limparConsole();
                strcpy(tipoUsuario, "Admin");

                if(fazerLogin("./Admin.txt", tipoUsuario)){
                    if(strcmp(tipoUsuario, "Admin") == 0){  // Comparando strings usando strcmp
                        isAdmin = 1;
                    }
                    exibirMenuAdmin(tipoUsuario);
                }

                limparConsole();
                break;
            case 2:
                limparConsole();
                strcpy(tipoUsuario, "Usuario");

                if(fazerLogin("./Usuario.txt", tipoUsuario)){
                    if(strcmp(tipoUsuario, "Usuario") == 0){  // Comparando strings usando strcmp
                        isAdmin = 0;
                    }
                    exibirMenuAdmin(tipoUsuario);
                }

                limparConsole();
                break;
            case 3:
                limparConsole();
                printf("\n\t    %sSaindo do programa...%s", RED, RESET);
                sleep(2);
                limparConsole();
                break;
            default:
                printf("\n\t      %sOpção inválida!%s Tente novamente.\n", YELLOW, RESET);
                sleep(2);
                break;

        }

    }while(escolha != 3);

}
void exibirMenuAdmin(tipoUsuario){

    int escolha;

    if(isAdmin){

        do{

            limparConsole();

            printf("\n\t|---------------------------------------------------------|\n");
            printf("\t| Sistema de Gerenciamento %sDebroi Eventos%s - %sAdministrador%s |", CYAN, RESET, GREEN, RESET);
            printf("\n\t|---------------------------------------------------------|\n");
            printf("\t| 1 | \tMenus de Gerenciamento                            |");
            printf("\n\t|---------------------------------------------------------|\n");
            printf("\t| 2 | \t%sVoltar Menu Inicial%s                               |", RED, RESET);
            printf("\n\t|---------------------------------------------------------|\n");
            printf("\n\t\tEscolha uma opção: ");

            escolha=validarEntradaInt();

            switch(escolha){

                case 1:
                    limparConsole();
                    exibirSubMenuGerenciamento();
                    break;
                case 2:
                    limparConsole();
                    exibirMenuPrincipal(); // Adicionado comando para voltar ao menu principal
                    break;
                default:
                    printf("\n\t\t%sOpção inválida!%s Tente novamente.\n", YELLOW, RESET);
                    sleep(2);
                    break;

            }

        }while(escolha != 4);

    }
    else{

         do{

            system(CLEAR_SCREEN);

            printf("\n\t|---------------------------------------------------|\n");
            printf("\t| Sistema de Gerenciamento %sDebroi Eventos%s - %sUsuário%s |\n", CYAN, RESET, GREEN, RESET);
            printf("\t|---------------------------------------------------|\n");
            printf("\t| 1 | \tMenus de Gerenciamento                      |\n");
            printf("\t|---------------------------------------------------|\n");
            printf("\t| 2 | \t%sVoltar Menu Inicial%s                         |\n", RED, RESET);
            printf("\t|---------------------------------------------------|\n\n");
            printf("\t\tEscolha uma opção: ");

            escolha=validarEntradaInt();

            switch(escolha){

                case 1:
                    limparConsole();
                    exibirSubMenuGerenciamento();
                    break;
                case 2:
                    limparConsole();
                    exibirMenuPrincipal(); // Adicionado comando para voltar ao menu principal
                    break;
                default:
                    printf("\n\t\t%sOpção inválida!%s Tente novamente.\n", YELLOW, RESET);
                    sleep(2);
                    break;

            }

        }while(escolha != 4);

    }

}
void exibirSubMenuGerenciamento(tipoUsuario){

    int escolha;

    do {

        limparConsole();

        printf("\n\t|-------------------------------------------------|\n");
        printf("\t| Sistema de Gerenciamento %sDebroi Eventos%s - %sAdmin%s |\n", CYAN, RESET, GREEN, RESET);
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 1 | \tMenu Eventos                              |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 2 | \tMenu Cardápios                            |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 3 | \tMenu Locais                               |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 4 | \tMenu Funcionários                         |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 5 | \tMenu Usuários                             |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 6 | \t%sVoltar%s                                    |\n", RED, RESET);
        printf("\t|-------------------------------------------------|\n");
        printf("\n\t\tEscolha uma opção: ");

        escolha=validarEntradaInt();

        switch(escolha){

            case 1:
                limparConsole();
                exibirSubMenuEventos();
                break;
            case 2:
                limparConsole();
                exibirSubMenuCardapio(tipoUsuario);
                break;
            case 3:
                limparConsole();
                exibirSubMenuLocais(tipoUsuario);
                break;
            case 4:
                limparConsole();
                exibirSubMenuFuncionario(tipoUsuario);
                break;
            case 5:
                limparConsole();
                exibirSubMenuUsuario(tipoUsuario);
                break;
            case 6:
                exibirMenuAdmin(tipoUsuario);
                break;
            default:
                printf("\n\t\t%sOpção inválida!%s Tente novamente.\n", YELLOW, RESET);
                sleep(2);
                break;

        }

    }while(escolha != 6);

}
void exibirSubMenuEventos(tipoUsuario){

    int escolha;

    do{

        limparConsole();

        printf("\n\t|-------------------------------------------------|\n");
        printf("\t| Sistema de Gerenciamento %sDebroi Eventos%s - %sAdmin%s |\n", CYAN, RESET, GREEN, RESET);
        printf("\t|-------------------------------------------------|\n");
        printf("\t|    \tMenu Eventos                              |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 1 |\tCriar Evento                              |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 2 |\tAtualizar Evento                          |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 3 |\tVisualizar Eventos                        |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 4 |\tCancelar Evento                           |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 5 |\t%sVoltar%s                                    |\n", RED, RESET);
        printf("\t|-------------------------------------------------|\n");
        printf("\n\t\tEscolha uma opção: ");

        escolha=validarEntradaInt();

        switch(escolha){

            case 1:
                limparConsole();
                criarEvento();
                break;
            case 2:
                limparConsole();
                // modificar
                break;
            case 3:
                limparConsole();
                exibirEventosDoArquivo();
                break;
            case 4:
                limparConsole();
                // Cancelar
            case 5:
                limparConsole();
                exibirSubMenuGerenciamento(tipoUsuario);
                break;
            default:
                printf("\n\t\t%sOpção inválida!%s Tente novamente.\n", YELLOW, RESET);
                sleep(2);
                break;

        }

    }while(escolha != 5);

}
void exibirSubMenuCardapio(tipoUsuario){

    int escolha;

    do{

        limparConsole();

        printf("\n\t|-------------------------------------------------|\n");
        printf("\t| Sistema de Gerenciamento %sDebroi Eventos%s - %sAdmin%s |\n", CYAN, RESET, GREEN, RESET);
        printf("\t|-------------------------------------------------|\n");
        printf("\t|    \tMenu Cardápios                            |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 1 |\tCriar Cardápio                            |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 2 |\tAtualizar Cardápio                        |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 3 |\tVisualizar Cardápios Disponíveis          |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 4 |\tExcluir Cardápio                          |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 5 |\t%sVoltar%s                                    |\n", RED, RESET);
        printf("\t|-------------------------------------------------|\n");
        printf("\n\t\tEscolha uma opção: ");

        escolha=validarEntradaInt();

        switch (escolha){

            case 1:
                limparConsole();
                criarCardapio();
                break;
            case 2:
                limparConsole();
                modificarCardapio();
                break;
            case 3:
                limparConsole();
                exibirCardapiosDoArquivo();
                break;
            case 4:
                limparConsole();
                excluirCardapio();
                break;
            case 5:
                limparConsole();
                exibirSubMenuGerenciamento(tipoUsuario);
                break;
            default:
                printf("\n\t\t%sOpção inválida!%s Tente novamente.\n", YELLOW, RESET);
                sleep(2);
                break;

        }

    }while(escolha != 5);

}
void exibirSubMenuLocais(char* tipoUsuario){

    int escolha;

    do{

        limparConsole();

        printf("\n\t|-------------------------------------------------|\n");
        printf("\t| Sistema de Gerenciamento %sDebroi Eventos%s - %sAdmin%s |\n", CYAN, RESET, GREEN, RESET);
        printf("\t|-------------------------------------------------|\n");
        printf("\t|    \tMenu Locais                               |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 1 |\tCriar Local                              |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 2 |\tAtualizar Local                           |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 3 |\tVisualizar Locais Disponíveis             |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 4 |\tExcluir Local                             |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 5 |\t%sVoltar%s                                    |\n", RED, RESET);
        printf("\t|-------------------------------------------------|\n");
        printf("\n\t\tEscolha uma opção: ");

        escolha = validarEntradaInt();

        switch(escolha){

            case 1:
                limparConsole();
                criarLocal();
                break;
            case 2:
                limparConsole();
                modificarLocal();
                break;
            case 3:
                limparConsole();
                exibirLocalDoArquivo();
                break;
            case 4:
                limparConsole();
                excluirLocal();
                break;
            case 5:
                limparConsole();
                exibirSubMenuGerenciamento(tipoUsuario);
                break;
            default:
                printf("\n\t\t%sOpção inválida!%s Tente novamente.\n", YELLOW, RESET);
                sleep(2);
                break;
        }

    }while(escolha != 5);

}
void exibirSubMenuFuncionario(char* tipoUsuario){

    int escolha;

    do{

        limparConsole();

        printf("\n\t|-------------------------------------------------|\n");
        printf("\t| Sistema de Gerenciamento %sDebroi Eventos%s - %sAdmin%s |\n", CYAN, RESET, GREEN, RESET);
        printf("\t|-------------------------------------------------|\n");
        printf("\t|    \tMenu Funcionários                         |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 1 |\tAdicionar Funcionário                     |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 2 |\tAtualizar Funcionário                     |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 3 |\tVisualizar Funcionários                   |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 4 |\tExcluir Funcionário                       |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 5 |\t%sVoltar%s                                    |\n", RED, RESET);
        printf("\t|-------------------------------------------------|\n");
        printf("\n\t\tEscolha uma opção: ");

        escolha = validarEntradaInt();

        switch(escolha){

            case 1:
                limparConsole();
                criarFuncionario();
                break;
            case 2:
                limparConsole();
                exibirFuncionarioDoArquivo();
                break;
            case 3:
                limparConsole();
                excluirFuncionario();
                break;
            case 4:
                limparConsole();
                modificarFuncionario();
                break;
            case 5:
                limparConsole();
                exibirSubMenuGerenciamento(tipoUsuario);
                break;
            default:
                printf("\n\t\t%sOpção inválida!%s Tente novamente.\n", YELLOW, RESET);
                sleep(2);
                break;

        }

    } while (escolha != 5);

}
void exibirSubMenuUsuario(tipoUsuario){

    int escolha;

    do{

        limparConsole();

        printf("\n\t|-------------------------------------------------|\n");
        printf("\t| Sistema de Gerenciamento %sDebroi Eventos%s - %sAdmin%s |\n", CYAN, RESET, GREEN, RESET);
        printf("\t|-------------------------------------------------|\n");
        printf("\t|    \tMenu Usuários                             |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 1 |\tAdicionar Usuário                         |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 2 |\tAtualizar Usuário                         |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 3 |\tVisualizar Usuários                       |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 4 |\tExcluir Usuário                           |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 5 |\t%sVoltar%s                                    |\n", RED, RESET);
        printf("\t|-------------------------------------------------|\n");
        printf("\n\t\tEscolha uma opção: ");

        escolha = validarEntradaInt();

        switch(escolha){

            case 1:
                limparConsole();
                criarUsuario();
                break;
            case 2:
                limparConsole();
                modificarUsuario();
                break;
            case 3:
                limparConsole();
                exibirUsuariosDoArquivo();
                break;
            case 4:
                limparConsole();
                excluirUsuario();
                break;
            case 5:
                limparConsole();
                exibirSubMenuGerenciamento(tipoUsuario);
                break;
            default:
                printf("\n\t\t%sOpção inválida!%s Tente novamente.\n", YELLOW, RESET);
                sleep(2);
                break;
        }

    }while(escolha != 5);

}
// *************************** //

// ***** FUNÇÃO DE LOGIN ***** //
int fazerLogin(char *arquivo, char *tipoUsuario) {

    FILE *f = fopen(arquivo, "r");

    if(!f){
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    char login[MAX_USUARIO];
    char senha[MAX_SENHA];
    char loginArquivo[MAX_USUARIO];
    char senhaArquivo[MAX_SENHA];


    int tentativas = 0;
    int loginValido = 0;

    do{

        limparConsole();

        printf("\n\t| Conectando ao Sistema - %s%s%s |\n\n", CYAN, tipoUsuario, WHITE);

        printf("\t  Login: ");
        lerString(login, MAX_USUARIO);
        printf("\t  Senha: ");
        lerString(senha, MAX_SENHA);

        fseek(f, 0, SEEK_SET);

        while(fscanf(f, "%19[^;];%19[^\n]\n", loginArquivo, senhaArquivo) == 2){

            if(strcmp(loginArquivo, login) == 0 && strcmp(senhaArquivo, senha) == 0){

                loginValido = 1;

                break;

            }
        }

        if(!loginValido){

            printf("\n\t%s  Login ou senha incorretos!%s Tente novamente.\n", RED, WHITE);

            tentativas++;

            sleep(1);

        }

    }while(!loginValido && tentativas < 3);

    fclose(f);

    if(loginValido){

        limparConsole();

        printf(GREEN"\n\tLogin bem-sucedido!\n"RESET);

        sleep(2);

    }
    else{

        limparConsole();

        printf("\n\t%sNúmero máximo de tentativas alcançado.%s Saindo do login.", RED, WHITE);

        sleep(2);

    }

    return loginValido;
}
// *************************** //

// ***** FUNÇÕES PARA LIMPAR CONSOLE ***** //
void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void limparConsole(){
    system(CLEAR_SCREEN);
}
void apagarMensagemAposTempo(int tempo, char mensagem[100]){
    printf("%s", mensagem);
    // Verifica se estamos no Windows para usar Sleep
    #ifdef _WIN32
    Sleep(tempo * 1000);  // Converte para milissegundos
    #else
    sleep(tempo);  // No Unix, sleep usa segundos diretamente
    #endif

    printf("\033[2K");
}
// *************************************** //

// ***** FUNÇÕES CRUD EVENTO ***** //
void criarEvento(){ // Criando o Evento

    Evento novoEvento;
    Cardapio cardapio;
    Local local;

    limparConsole();

    printf("\n\tCadastro de Evento -  %sDebroi Eventos%s \n\n", CYAN, WHITE);

    do {

        novoEvento.idEvento=idGerador();

        // ***** Primeira etapa do cadastro de evento, dados do contrantante ***** //

        printf("\t%sPrimeira etapa%s\n\n", CYAN, RESET);

        printf("\tDigite seu nome: ");
        lerString(novoEvento.nomeContratante, MAX_TAMANHO);

        printf("\tDigite seu CPF: ");
        lerCPFValidado(novoEvento.cpfContratante, MAX_TAMANHO);

        printf("\tDigite seu e-mail: ");
        lerEmailValidado(novoEvento.emailContratante, MAX_TAMANHO);

        //printf("\tTelefone: ");
        lerTelefoneValidado(novoEvento.telefoneContratante, MAX_TAMANHO);

        // *********************************************************************** //

        limparConsole();

        // ***** Segunda etapa do cadastro de evento, dados do evento ***** //

        printf("\n\tCadastro de Evento -  %sDebroi Eventos%s \n\n", CYAN, WHITE);

        printf("\n\t%sSegunda etapa%s\n\n", CYAN, RESET);

        printf("\tNome do Evento: ");
        lerString(novoEvento.nomeEvento, MAX_NOME);

        printf("\tDescrição do Evento: ");
        lerString(novoEvento.descricaoEvento, MAX_DESCRICAO);

        printf("\tDescrição a quantidade de pessoas: ");
        novoEvento.quantidadePessoas = validarEntradaInt();

        int aux=0; // Variável para auxiliar o 'DO WHILE'

        // Obtém o tempo atual em segundos desde 1 de janeiro de 1970 (Unix timestamp)
        time_t tempoAtual;
        time(&tempoAtual);

        // Converte o tempo atual em uma estrutura de data
        struct tm *infoTempo = localtime(&tempoAtual);

        // Obtém a data atual
        int diaAtual = infoTempo->tm_mday;
        int mesAtual = infoTempo->tm_mon + 1;
        int anoAtual = infoTempo->tm_year + 1900;

        do{

            printf("\tDigite o dia do evento: ");
            novoEvento.dia = validarEntradaInt();

            printf("\tDigite o mês do evento: ");
            novoEvento.mes = validarEntradaInt();

            printf("\tDigite o ano do evento: ");
            novoEvento.ano = validarEntradaInt();

            if(validandoData(novoEvento.dia, novoEvento.mes, novoEvento.ano)){
                if((novoEvento.dia<diaAtual && novoEvento.mes<mesAtual) && novoEvento.ano<anoAtual){
                    printf("\t%sA data é inválida!%s Digite Novamente.\n", RED, RESET);
                }
                else{
                    aux++;
                }
            }
            else{
                printf("\t%sA data é inválida!%s Digite Novamente.\n", RED, RESET);
            }

        }while(aux==0);


        // **************************************************************** //

        // ***** Manipulando o arquivo 'cardapios.txt' ***** //

        printf("Digite o nome do cardápio que deseja: ");
        lerString(novoEvento.nomeCardapio, MAX_TAMANHO);

        FILE *arquivoCardapio = fopen("cardapios.txt", "r");

        if(arquivoCardapio == NULL){
            printf("Erro ao abrir o arquivo.\n");
            return;
        }

        while(fscanf(arquivoCardapio, "%[^;];%[^;];%[^;];%d;%f;%d\n",
                     cardapio.nome, cardapio.descricao, cardapio.ingredientes,
                     &cardapio.quantidadePessoas, &cardapio.valor,
                     &cardapio.disponibilidade) != EOF){

            if(strcmp(cardapio.nome, novoEvento.nomeCardapio) == 0){
                strcpy(novoEvento.descricaoCardapio,cardapio.descricao);
                strcpy(novoEvento.ingredientesCardapio, cardapio.ingredientes);
                novoEvento.quantidadePessoasCardapio = cardapio.quantidadePessoas;
                novoEvento.valorCardapio = cardapio.valor;
            }
        }

        fclose(arquivoCardapio);

        // ************************************************* //

        // ***** Manipulando o arquivo 'Locais.txt' ***** //

        printf("Digite o nome do local que deseja: ");
        lerString(novoEvento.nomeLocal, 100);

        FILE *arquivoLocal = fopen("Locais.txt", "r");

        if(arquivoLocal == NULL){
            printf("Erro ao abrir o arquivo.\n");
            return;
        }

        while(fscanf(arquivoLocal, "%[^;];%[^;];%f;%[^;];%[^;];%d\n",
                     local.nome, local.endereco, &local.valorLocacao, local.descricaoAmbiente,
                     local.telefone, &local.lotacaoMaxima) != EOF){

            if(strcmp(local.nome, novoEvento.nomeLocal) == 0){
                strcpy(novoEvento.enderecoLocal, local.endereco);
                novoEvento.valorLocal = local.valorLocacao;
                strcpy(novoEvento.descricaoAmbienteLocal, local.descricaoAmbiente);
                strcpy(novoEvento.telefoneLocal, local.telefone);
                novoEvento.lotacaoMaximaLocal = local.lotacaoMaxima;
            }
        }

        fclose(arquivoLocal);
        // *********************************************** //

        // Cálculo do valor estimado para o evento
        novoEvento.valorCardapio = novoEvento.valorCardapio * novoEvento.quantidadePessoas;
        novoEvento.valorEstimado = (novoEvento.valorCardapio + novoEvento.valorLocal)*1.1;

        novoEvento.status=1; // Status do evento(ANDAMENTO/CONCLUÍDO/CANCELADO)


        // ***** Manipulando o arquivo 'eventos.txt' ***** //

        FILE *arquivo = fopen("eventos.txt", "a"); // Abrindo o arquivo para escrita

        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n"); // Verificando se houve erro ao abrir
            return;
        }

        fprintf(arquivo, "%d;%s;%s;%s;%s;%s;%s;%d;%d;%d;%d;%s;%s;%s;%d;%s;%s;%s;%s;%d;%f;%f;%f;%d\n", // Escrever os dados no arquivo
                novoEvento.idEvento, novoEvento.nomeContratante, novoEvento.cpfContratante, novoEvento.emailContratante, novoEvento.telefoneContratante,
                novoEvento.nomeEvento, novoEvento.descricaoEvento, novoEvento.quantidadePessoas, novoEvento.dia, novoEvento.mes, novoEvento.ano,
                novoEvento.nomeCardapio, novoEvento.descricaoCardapio, novoEvento.ingredientesCardapio, novoEvento.quantidadePessoasCardapio,
                novoEvento.nomeLocal, novoEvento.enderecoLocal, novoEvento.descricaoAmbienteLocal, novoEvento.telefoneLocal, novoEvento.lotacaoMaximaLocal,
                novoEvento.valorEstimado, novoEvento.valorCardapio, novoEvento.valorLocal,
                novoEvento.status);

        fclose(arquivo); // Fechando o arquivo

        // *********************************************** //

        printf("\tEvento criado e salvo com sucesso!\n");
        sleep(2);
        limparConsole();

    } while (confirmarContinuacao() != 0);
    printf("\n\n\t\tVoltando ao menu anterior... ");
    sleep(1);
}
void modificarEvento(){

    int eventoModificar;
    printf("Digite o nome do cardapio que deseja modificar: ");
    eventoModificar=validarEntradaInt;

    FILE *arquivoEntrada = fopen("eventos.txt", "r");
    FILE *arquivoTemp = fopen("temp.txt", "w");

    if (arquivoEntrada == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Evento evento;
    Cardapio cardapio;
    Local local;

    int encontrado = 0;
    int escolha;
    int aux=0; // Variável para auxiliar o 'DO WHILE'

    while (fscanf(arquivoEntrada, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d;%[^;];%[^;];%[^;];%d;%[^;];%[^;];%[^;];%[^;];%d;%f;%f;%f;%d\n",
                    &evento.idEvento, evento.nomeContratante, evento.cpfContratante, evento.emailContratante, evento.telefoneContratante,
                    evento.nomeEvento, evento.descricaoEvento, &evento.quantidadePessoas, &evento.dia, &evento.mes, &evento.ano,
                    evento.nomeCardapio, evento.descricaoCardapio, evento.ingredientesCardapio, &evento.quantidadePessoasCardapio,
                    evento.nomeLocal, evento.enderecoLocal, evento.descricaoAmbienteLocal, evento.telefoneLocal, &evento.lotacaoMaximaLocal,
                    &evento.valorEstimado, &evento.valorCardapio, &evento.valorLocal,
                    &evento.status) != EOF){

        if (strcmp(evento.idEvento, eventoModificar) == 0) {

            // Se o nome corresponder, permita ao usuário modificar as características

            do{

                printf("\t============= Cardápio Atual =============\n");
                exibirEvento(&evento);
                printf("\n\t============= O que deseja atualizar =======\n");
                printf("\t\t1. E-mail contratante\n");
                printf("\t\t2. Telefone contratante\n");
                printf("\t\t3. Quantidade de pessoas\n");
                printf("\t\t4. Data\n");
                printf("\t\t5. Cardápio\n");
                printf("\t\t6. Local\n");
                printf("\t\t7. Voltar\n");
                printf("\n\t===========================================\n");
                printf("\tDigite a opção escolhida: ");

                escolha=validarEntradaInt();

                switch(escolha){

                    case 1:

                        printf("\t\t Novo e-mail: ");
                        lerString(evento.emailContratante, MAX_EMAIL);

                        limparConsole();

                        break;
                    case 2:

                        printf("\t\tNovo telefone: ");
                        lerString(evento.telefoneContratante, MAX_TELEFONE);

                        limparConsole();

                        break;
                    case 3:

                        printf("\t\tNova quantidade de pessoas: ");
                        evento.quantidadePessoas = validarEntradaDouble();

                        limparConsole();

                        break;
                    case 4:

                        printf("\n\tNova Data\n");

                        // Obtém o tempo atual em segundos desde 1 de janeiro de 1970 (Unix timestamp)
                        time_t tempoAtual;
                        time(&tempoAtual);

                        // Converte o tempo atual em uma estrutura de data
                        struct tm *infoTempo = localtime(&tempoAtual);

                        // Obtém a data atual
                        int diaAtual = infoTempo->tm_mday;
                        int mesAtual = infoTempo->tm_mon + 1;
                        int anoAtual = infoTempo->tm_year + 1900;

                        do{

                            printf("\tDigite o dia do evento: ");
                            evento.dia = validarEntradaInt();

                            printf("\tDigite o mês do evento: ");
                            evento.mes = validarEntradaInt();

                            printf("\tDigite o ano do evento: ");
                            evento.ano = validarEntradaInt();

                            if(validandoData(evento.dia, evento.mes, evento.ano)){

                                if((evento.dia<diaAtual || evento.mes<mesAtual) || evento.ano<anoAtual){

                                    printf("\t%sA data é inválida!%s Digite Novamente.\n", RED, RESET);

                                }
                                else{

                                    aux++;

                                }
                            }
                            else{

                                printf("\t%sA data é inválida!%s Digite Novamente.\n", RED, RESET);

                            }

                        }while(aux==0);

                        limparConsole();

                        break;
                    case 5:

                        printf("\t\tNova cardápio: ");
                        lerString(evento.nomeCardapio, MAX_TAMANHO);

                        // ***** Manipulando o arquivo 'cardapios.txt' ***** //

                        FILE *arquivoCardapio = fopen("cardapios.txt", "r");

                        if(arquivoCardapio == NULL){
                            printf("Erro ao abrir o arquivo.\n");
                            return;
                        }

                        while(fscanf(arquivoCardapio, "%[^;];%[^;];%[^;];%d;%f;%d\n",
                                     cardapio.nome, cardapio.descricao, cardapio.ingredientes,
                                     &cardapio.quantidadePessoas, &cardapio.valor,
                                     &cardapio.disponibilidade) != EOF){

                            if(strcmp(cardapio.nome, evento.nomeCardapio) == 0){
                                strcpy(evento.descricaoCardapio,cardapio.descricao);
                                strcpy(evento.ingredientesCardapio, cardapio.ingredientes);
                                evento.quantidadePessoasCardapio = cardapio.quantidadePessoas;
                                evento.valorCardapio = cardapio.valor;
                            }
                        }

                        fclose(arquivoCardapio);

                        // ************************************************* //

                        limparConsole();

                        break;
                    case 6:

                        // ***** Manipulando o arquivo 'Locais.txt' ***** //

                        printf("Novo local: ");
                        lerString(evento.nomeLocal, 100);

                        FILE *arquivoLocal = fopen("Locais.txt", "r");

                        if(arquivoLocal == NULL){
                            printf("Erro ao abrir o arquivo.\n");
                            return;
                        }

                        while(fscanf(arquivoLocal, "%[^;];%[^;];%f;%[^;];%[^;];%d\n",
                                     local.nome, local.endereco, &local.valorLocacao, local.descricaoAmbiente,
                                     local.telefone, &local.lotacaoMaxima) != EOF){

                            if(strcmp(local.nome, evento.nomeLocal) == 0){
                                strcpy(evento.enderecoLocal, local.endereco);
                                evento.valorLocal = local.valorLocacao;
                                strcpy(evento.descricaoAmbienteLocal, local.descricaoAmbiente);
                                strcpy(evento.telefoneLocal, local.telefone);
                                strcpy(evento.lotacaoMaximaLocal, local.lotacaoMaxima);
                            }
                        }

                        fclose(arquivoLocal);

                        // *********************************************** //

                        break;

                    case 7:
                        limparConsole();
                        exibirSubMenuEventos(tipoUsuario);
                        break;
                    default:
                        printf("\n\t\tOpção inválida! Tente novamente.\n");
                        sleep(2);
                        break;
                }
            }while (escolha != 6);
            encontrado = 1;
        }

        // Cálculo do valor estimado para o evento
        evento.valorCardapio = evento.valorCardapio*evento.quantidadePessoas;
        evento.valorEstimado = evento.valorCardapio + evento.valorLocal;

        fprintf(arquivoTemp, "%d;%s;%s;%s;%s;%s;%s;%d;%d;%d;%d;%s;%s;%s;%d;%s;%s;%s;%s;%d;%f;%f;%f;%d\n", // Escrever os dados no arquivo temporário
                evento.idEvento, evento.nomeContratante, evento.cpfContratante, evento.emailContratante, evento.telefoneContratante,
                evento.nomeEvento, evento.descricaoEvento, evento.quantidadePessoas, evento.dia, evento.mes, evento.ano,
                evento.nomeCardapio, evento.descricaoCardapio, evento.ingredientesCardapio, evento.quantidadePessoasCardapio,
                evento.nomeLocal, evento.enderecoLocal, evento.descricaoAmbienteLocal, evento.telefoneLocal, evento.lotacaoMaximaLocal,
                evento.valorEstimado, evento.valorCardapio, evento.valorLocal, evento.status);

    }

    fclose(arquivoEntrada);
    fclose(arquivoTemp);

    // Remover o arquivo original
    remove("eventos.txt");

    // Renomear o arquivo temporário para o original
    rename("temp.txt", "cardapios.txt");

    if (encontrado) {
        printf("Cardapio modificado com sucesso!\n");
        sleep(2);
    } else {
        printf("Cardapio nao encontrado.\n");
        sleep(2);
    }

}
void exibirEventosDoArquivo(){ // Reutilizado

    FILE *arquivo = fopen("eventos.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Evento eventoLido;
    int pageSize = 2; // Número de eventos por página
    int pagina = 1;
    int contador = 0;
    int reiniciarArquivo = 1;

    do {
        if (reiniciarArquivo) {
            rewind(arquivo);
            reiniciarArquivo = 0;
        }

        printf("\t=========== Eventos (\e[0;32mPAGINA %d\e[m) =============\n", pagina);

        char linha[512];
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            sscanf(linha, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d;%[^;];%[^;];%[^;];%d;%[^;];%[^;];%[^;];%[^;];%d;%f;%f;%f;%d\n",
                        &eventoLido.idEvento, eventoLido.nomeContratante, eventoLido.cpfContratante, eventoLido.emailContratante, eventoLido.telefoneContratante,
                        eventoLido.nomeEvento, eventoLido.descricaoEvento, &eventoLido.quantidadePessoas, &eventoLido.dia, &eventoLido.mes, &eventoLido.ano,
                        eventoLido.nomeCardapio, eventoLido.descricaoCardapio, eventoLido.ingredientesCardapio, &eventoLido.quantidadePessoasCardapio,
                        eventoLido.nomeLocal, eventoLido.enderecoLocal, eventoLido.descricaoAmbienteLocal, eventoLido.telefoneLocal, &eventoLido.lotacaoMaximaLocal,
                        &eventoLido.valorEstimado, &eventoLido.valorCardapio, &eventoLido.valorLocal,
                        &eventoLido.status);

            exibirEvento(&eventoLido);
            printf("\n");

            contador++;

            if (contador >= pageSize) {
                break;
            }
        }

        if (feof(arquivo)) {
            break; // Se chegamos ao final do arquivo, saímos do loop externo
        }

        limparBuffer();

        printf("\n\tPressione '\e[0;32mn\e[m' para avançar, '\e[0;33mp\e[m' para retroceder, ou '\e[1;91mq\e[m' para sair...\n\t\t");
        char input = getchar();

        while (getchar() != '\n');

        if (input == 'q' || input == 'Q') {
            break; // Sair do loop se o usuário digitar 'q' ou 'Q'
        } else if (input == 'n' || input == 'N') {
            // Avançar para a próxima página
            limparConsole();
            pagina++;
            contador = 0;
        } else if (input == 'p' || input == 'P' && pagina > 1) {
            // Retroceder para a página anterior
            limparConsole();
            pagina--;
            contador = 0;
            reiniciarArquivo = 1;
            if(pagina < 1){
                pagina = 1;
            } // Reiniciar o arquivo ao retroceder
        }

    } while (1);

    fclose(arquivo);
}
void exibirEvento(Evento *evento){ // Visualizando o Evento
    printf("\t\tID evento: %d\n", evento->idEvento);
    printf("\t\tNome: %s\n", evento->nomeEvento);
    printf("\t\tDescricão: %s\n", evento->descricaoEvento);
    printf("\t\tDATA: %d/%d/%d\n", evento->dia, evento->mes, evento->ano);
    printf("\t\tQTD PESSOAS: %d\n", evento->quantidadePessoas);
    printf("\t\tCardápio: %s\n", evento->nomeCardapio);
    printf("\t\tLocal: %s\n", evento->nomeLocal);
    printf("\t\tEndereço: %s\n", evento->enderecoLocal);
    printf("\t\tValor cardápio:: %.2f\n", evento->valorCardapio);
    printf("\t\tValor local: %.2f\n", evento->valorLocal);
    printf("\t\tValor estimado: %.2f\n", evento->valorEstimado);
    printf("\t\tStatus:\e[0;36m  %s\e[m\n", evento->status ? "\e[0;32mAtivo\e[m" : "\e[1;91mInativo\e[m");

}
void excluirEvento(){ // Bloqueando o Evento
}
// ******************************* //

//FUNÇÃO CRUD CARDAPIO
void criarCardapio(){
    Cardapio novoCardapio;
    limparConsole();
    printf(GREEN"\n\t========= Cadastro de Cardápio -  Debroi Eventos ==========\n"RESET);

    do {

        printf("\t\tNome do Cardápio: ");
        lerString(novoCardapio.nome, 50);

        printf("\t\tDescrição do Cardápio: ");
        lerString(novoCardapio.descricao, 100);

        printf("\t\tIngredientes: ");
        lerString(novoCardapio.ingredientes, 200);

        printf("\t\tQuantidade de Pessoas: ");
        novoCardapio.quantidadePessoas = validarEntradaInt();

        printf("\t\tValor do cardápio por pessoa: ");
        novoCardapio.valor = validarEntradaDouble();

        printf("\t\tDisponibilidade (1 para ativo, 0 para inativo): ");
        novoCardapio.disponibilidade = validarEntradaInt();

        FILE *arquivo = fopen("cardapios.txt", "a");

        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
        }

        // Escrever os dados no arquivo
        fprintf(arquivo, "%s;%s;%s;%d;%.2lf;%d\n", novoCardapio.nome, novoCardapio.descricao,
                novoCardapio.ingredientes, novoCardapio.quantidadePessoas,
                novoCardapio.valor, novoCardapio.disponibilidade);
        // Fechar o arquivo
        fclose(arquivo);
        printf("Cardápio criado e salvo com sucesso!\n");
        sleep(1);
        limparConsole();

    } while (confirmarContinuacao() != 0);
    printf("\n\n\t\tVoltando ao menu anterior... ");
    sleep(1);
}
void modificarCardapio(){

    char nomeModificar[50];
    printf("Digite o nome do cardapio que deseja modificar: ");
    lerString(nomeModificar,50);

    FILE *arquivoEntrada = fopen("cardapios.txt", "r");
    FILE *arquivoTemp = fopen("temp.txt", "w");

    if (arquivoEntrada == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Cardapio cardapio;

    int encontrado = 0;
    int escolha;

    while (fscanf(arquivoEntrada, "%[^;];%[^;];%[^;];%d;%f;%d\n",
                  cardapio.nome, cardapio.descricao, cardapio.ingredientes,
                  &cardapio.quantidadePessoas, &cardapio.valor,
                  &cardapio.disponibilidade) != EOF) {

        if (strcmp(cardapio.nome, nomeModificar) == 0) {
            // Se o nome corresponder, permita ao usuário modificar as características
             do{
                    printf("\t============= Cardapio Atual =============\n");
                    exibirCardapio(&cardapio);
                    printf("\n\t============= O que deseja atualizar =======\n");
                    printf("\t\t1. Nome\n");
                    printf("\t\t2. Descrição\n");
                    printf("\t\t3. Ingredientes\n");
                    printf("\t\t4. Valor do cardapio por pessoas\n");
                    printf("\t\t5. Disponibilidade\n");
                    printf("\t\t6. Voltar\n");
                    printf("\n\t===========================================\n");
                    printf("\tDigite a opção escolhida: ");
                    scanf("%d", &escolha);

            switch (escolha) {
            case 1:
                printf("\t\t Novo Nome: ");
                lerString(cardapio.nome,50);
                limparConsole();
                break;
            case 2:
                printf("\t\tNova Descricao: ");
                lerString(cardapio.descricao,100);
                limparConsole();
                break;
            case 3:
                printf("\t\tNovos Ingredientes: ");
                lerString(cardapio.ingredientes,200);
                limparConsole();

                break;
            case 4:
                printf("\t\tNovo Valor: ");
                cardapio.valor = validarEntradaDouble();
                limparConsole();

                break;
            case 5:
                printf("\t\tNova Disponibilidade (1 para ativo, 0 para inativo): ");
                cardapio.disponibilidade = validarEntradaInt();
                limparConsole();

                break;
            case 6:
                limparConsole();
               // exibirSubMenuCardapio(tipoUsuario);
                break;
            default:
                printf("\n\t\tOpção inválida! Tente novamente.\n");
                sleep(2);
                break;
 } } while (escolha != 6);
            encontrado = 1;
        }

        // Escreva no arquivo temporário
        fprintf(arquivoTemp, "%s;%s;%s;%d;%f;%d\n", cardapio.nome, cardapio.descricao,
                cardapio.ingredientes, cardapio.quantidadePessoas,
                cardapio.valor, cardapio.disponibilidade);
    }

    fclose(arquivoEntrada);
    fclose(arquivoTemp);

    // Remover o arquivo original
    remove("cardapios.txt");

    // Renomear o arquivo temporário para o original
    rename("temp.txt", "cardapios.txt");

    if (encontrado) {
        printf("Cardapio modificado com sucesso!\n");
        sleep(2);
    } else {
        printf("Cardapio nao encontrado.\n");
        sleep(2);
    }
}
void excluirCardapio(){
     char nomeExcluir[50];
    printf("Digite o nome do cardapio que deseja excluir: ");
    lerString(nomeExcluir, 50);

    FILE *arquivoEntrada = fopen("cardapios.txt", "r");
    FILE *arquivoTemp = fopen("temp.txt", "w");

    if (arquivoEntrada == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Cardapio cardapio;
    int encontrado = 0;

    while (fscanf(arquivoEntrada, "%[^;];%[^;];%[^;];%d;%f;%d\n",
                  cardapio.nome, cardapio.descricao, cardapio.ingredientes,
                  &cardapio.quantidadePessoas, &cardapio.valor,
                  &cardapio.disponibilidade) != EOF) {

        if (strcmp(cardapio.nome, nomeExcluir) == 0) {
            encontrado = 1;
            exibirCardapio(&cardapio); // Exibir detalhes do cardápio antes de excluir

            if (!confirmarExclusao()) {
                fclose(arquivoEntrada);
                fclose(arquivoTemp);
                remove("temp.txt");
                printf("Exclusao cancelada.\n");
                return;
            }
        } else {
            // Escrever no arquivo temporário apenas se não for o cardápio a ser excluído
            fprintf(arquivoTemp, "%s;%s;%s;%d;%f;%d\n", cardapio.nome, cardapio.descricao,
                    cardapio.ingredientes, cardapio.quantidadePessoas,
                    cardapio.valor, cardapio.disponibilidade);
        }
    }

    fclose(arquivoEntrada);
    fclose(arquivoTemp);

    if (!encontrado) {
        remove("temp.txt"); // Se não foi encontrado, remover o arquivo temporário
        printf("Cardapio nao encontrado.\n");
        return;
    }

    // Remover o arquivo original
    remove("cardapios.txt");

    // Renomear o arquivo temporário para o original
    rename("temp.txt", "cardapios.txt");

    printf("Cardapio excluido com sucesso!\n");
}
void exibirCardapiosDoArquivo(){
    FILE *arquivo = fopen("cardapios.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Cardapio cardapioLido;
    int pageSize = 3; // Número de cardápios por página
    int pagina = 1;
    int contador = 0;
    int reiniciarArquivo = 1;

    do {
        if (reiniciarArquivo) {
            rewind(arquivo);
            reiniciarArquivo = 0;
        }

        printf("\t=========== CARDAPIOS (\e[0;32mPAGINA %d\e[m) =============\n", pagina);

        char linha[512];
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            sscanf(linha, "%[^;];%[^;];%[^;];%d;%f;%d\n", cardapioLido.nome, cardapioLido.descricao,
                   cardapioLido.ingredientes, &cardapioLido.quantidadePessoas, &cardapioLido.valor,
                   &cardapioLido.disponibilidade);

            exibirCardapio(&cardapioLido);
            printf("\n");

            contador++;

            if (contador >= pageSize) {
                break;
            }
        }

        if (feof(arquivo)) {
            break; // Se chegamos ao final do arquivo, saímos do loop externo
        }

        pausar();

        printf("\n\tPressione '\e[0;32mn\e[m' para avançar, '\e[0;33mp\e[m' para retroceder, ou '\e[1;91mq\e[m' para sair...\n\t\t");
        char input = getchar();
        while (getchar() != '\n');

        if (input == 'q' || input == 'Q') {
            break; // Sair do loop se o usuário digitar 'q' ou 'Q'
        } else if (input == 'n' || input == 'N') {
            // Avançar para a próxima página
            limparConsole();
            pagina++;
            contador = 0;
        } else if (input == 'p' || input == 'P' && pagina > 1) {
            // Retroceder para a página anterior
            limparConsole();
            pagina--;
            contador = 0;
            reiniciarArquivo = 1;
            if(pagina < 1){
                pagina = 1;
            } // Reiniciar o arquivo ao retroceder
        }

    } while (1);

    fclose(arquivo);
}
void exibirCardapio(const Cardapio *cardapio){
    printf("\t============= Detalhes do Cardapio =============\n");
    printf("\t\tNome:\e[0;36m %s\e[m\n", cardapio->nome);
    printf("\t\tDescricao:\e[0;36m %s\e[m\n", cardapio->descricao);
    printf("\t\tIngredientes:\e[0;36m %s\e[m\n", cardapio->ingredientes);
    printf("\t\tQuantidade de Pessoas:\e[0;36m %d\e[m\n", cardapio->quantidadePessoas);
    printf("\t\tValor:\e[0;36m %.2f\e[m\n", cardapio->valor);
    printf("\t\tDisponibilidade:\e[0;36m  %s\e[m\n", cardapio->disponibilidade ? "\e[0;32mAtivo\e[m" : "\e[1;91mInativo\e[m" );
    printf("\t=============================================\n");
}

// FUNÇÃO CRUD LOCAL
void criarLocal(){

    Local novoLocal;

    limparConsole();

    printf("\n\t========= Cadastro de Local - Debroi Eventos ==========\n");

    do {

        printf("\t\tNome do Local: ");
        lerString(novoLocal.nome, MAX_TAMANHO);

        printf("\t\tEndereço do Local: ");
        lerString(novoLocal.endereco, MAX_TAMANHO);

        printf("\t\tValor de Locação do Local: ");
        novoLocal.valorLocacao = validarEntradaDouble();

        printf("\t\tDescrição do Ambiente: ");
        lerString(novoLocal.descricaoAmbiente, MAX_DESCRICAO);

        printf("\t\tTelefone: ");
        lerTelefoneValidado(novoLocal.telefone, MAX_TELEFONE);

        printf("\t\tLotação Máxima do Local: ");
        novoLocal.lotacaoMaxima = validarEntradaInt();

        FILE *arquivo = fopen("Locais.txt", "a");

        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
        }

        // Escrever os dados no arquivo
        fprintf(arquivo, "%s;%s;%.2f;%s;%d\n", novoLocal.nome, novoLocal.endereco,
                &novoLocal.valorLocacao, novoLocal.descricaoAmbiente, &novoLocal.lotacaoMaxima);

        // Fechar o arquivo
        fclose(arquivo);

        printf("Local criado e salvo com sucesso!\n");
        sleep(1);
        limparConsole();

    } while (confirmarContinuacao() != 0);

    printf("\n\n\t\tVoltando ao menu anterior... ");
    sleep(1);
}
void modificarLocal(){
    char nomeModificar[MAX_TAMANHO];
    printf("Digite o nome do Local que deseja atualizar: ");
    lerString(nomeModificar, MAX_TAMANHO);

    FILE *arquivoEntrada = fopen("Locais.txt", "r");
    FILE *arquivoTemp = fopen("temp.txt", "w");

    if (arquivoEntrada == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Local localLido;

    int encontrado = 0;
    int escolha;
    char linha[512];
    while (fgets(linha, sizeof(linha), arquivoEntrada) != NULL) {
        // printf("Lido do arquivo: %s\n", linha);  // Debug: exibe a linha lida

        int leituras = sscanf(linha, "%[^;];%[^;];%f;%[^;];%[^;];%d\n", localLido.nome, localLido.endereco,
                              &localLido.valorLocacao, localLido.descricaoAmbiente,localLido.telefone, &localLido.lotacaoMaxima);

        if (leituras != 6) {
            printf("Erro ao ler os dados do local. Linha ignorada.\n");
            continue;
        }

        if (strcmp(localLido.nome, nomeModificar) == 0) {
            // Se o nome corresponder, permita ao usuário modificar as características
            do {
                printf("\t============= Status Atual do Local =============\n");
                exibirLocal(&localLido);
                printf("\n\t============= O que deseja atualizar =======\n");
                printf("\t\t1. Nome\n");
                printf("\t\t2. Endereço\n");
                printf("\t\t3. Valor de Locação\n");
                printf("\t\t4. Descrição do Ambiente\n");
                printf("\t\t5. Lotação Máxima\n");
                printf("\t\t6. Telefone\n");
                printf("\t\t7. Voltar\n");
                printf("\n\t===========================================\n");
                printf("\tDigite a opção escolhida: ");
                escolha = validarEntradaInt();

                switch (escolha) {
                    case 1:
                        printf("\t\t Novo Nome: ");
                        lerString(localLido.nome, MAX_TAMANHO);
                        limparConsole();
                        break;
                    case 2:
                        printf("\t\tNovo Endereço: ");
                        lerString(localLido.endereco, MAX_TAMANHO);
                        limparConsole();
                        break;
                    case 3:
                        printf("\t\tNovo Valor de Locação: ");
                        localLido.valorLocacao = validarEntradaDouble();
                        limparConsole();
                        break;
                    case 4:
                        printf("\t\tNova Descrição do Ambiente: ");
                        lerString(localLido.descricaoAmbiente, MAX_DESCRICAO);
                        limparConsole();
                        break;
                    case 5:
                        printf("\t\tNova Lotação Máxima: ");
                        localLido.lotacaoMaxima = validarEntradaInt();
                        limparConsole();
                        break;
                    case 6:
                        printf("\t\tNova Telefone: ");
                        lerTelefoneValidado(localLido.telefone,MAX_TELEFONE);
                        limparConsole();
                        break;
                    case 7:
                        limparConsole();
                        break;
                    default:
                        printf("\n\t\tOpção inválida! Tente novamente.\n");
                        sleep(2);
                        break;
                }
            } while (escolha != 7);
            encontrado = 1;
        }

        // Escreva no arquivo temporário
        fprintf(arquivoTemp, "%s;%s;%.2f;%s;%s;%d\n", localLido.nome, localLido.endereco,
                localLido.valorLocacao, localLido.descricaoAmbiente,localLido.telefone, localLido.lotacaoMaxima);
    }

    fclose(arquivoEntrada);
    fclose(arquivoTemp);

    // Remover o arquivo original
    remove("Locais.txt");

    // Renomear o arquivo temporário para o original
    rename("temp.txt", "Locais.txt");

    if (encontrado) {
        printf("Local modificado com sucesso!\n");
        sleep(2);
    } else {
        printf("Local não encontrado.\n");
        sleep(2);
    }
}
void excluirLocal(){
    char nomeExcluir[MAX_TAMANHO];
    printf("Digite o nome do local que deseja excluir: ");
    fgets(nomeExcluir, sizeof(nomeExcluir), stdin);
    nomeExcluir[strcspn(nomeExcluir, "\n")] = '\0'; // Remover a quebra de linha

    FILE *arquivoEntrada = fopen("Locais.txt", "r");
    FILE *arquivoTemp = fopen("temp.txt", "w");

    if (arquivoEntrada == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Local local;
    int encontrado = 0;

    while (fscanf(arquivoEntrada, "%[^;];%[^;];%f;%[^;];%d\n",
                  local.nome, local.endereco, &local.valorLocacao,
                  local.descricaoAmbiente, &local.lotacaoMaxima) != EOF) {

        if (strcmp(local.nome, nomeExcluir) == 0) {
            encontrado = 1;
            exibirLocal(&local); // Exibir detalhes do local antes de excluir

            printf("Deseja realmente excluir este local? (s/n): ");
            char confirmacao;
            scanf(" %c", &confirmacao);

            if (confirmacao != 's' && confirmacao != 'S') {
                fclose(arquivoEntrada);
                fclose(arquivoTemp);
                printf("Exclusao cancelada.\n");
                return;
            }
        } else {
            // Escrever no arquivo temporário apenas se não for o local a ser excluído
            fprintf(arquivoTemp, "%s;%s;%.2f;%s;%d\n", local.nome, local.endereco,
                    local.valorLocacao, local.descricaoAmbiente, local.lotacaoMaxima);
        }
    }

    fclose(arquivoEntrada);
    fclose(arquivoTemp);

    if (!encontrado) {
        printf("Local nao encontrado.\n");
        return;
    }

    // Remover o arquivo original
    remove("Locais.txt");

    // Renomear o arquivo temporário para o original
    rename("temp.txt", "Locais.txt");

    printf("Local excluído com sucesso!\n");
}
void exibirLocalDoArquivo(){
    FILE *arquivo = fopen("Locais.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Local localLido;
    int pageSize = 3; // Número de locais por página
    int pagina = 1;
    int contador = 0;
    int reiniciarArquivo = 1;

    do {
        if (reiniciarArquivo) {
            rewind(arquivo);
            reiniciarArquivo = 0;
        }

        printf("\t=========== Locais (\e[0;32mPAGINA %d\e[m) =============\n", pagina);

        char linha[512];
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            int leituras = sscanf(linha, "%[^;];%[^;];%f;%[^;];%[^;];%d\n", localLido.nome, localLido.endereco,
                                  &localLido.valorLocacao, localLido.descricaoAmbiente,localLido.telefone, &localLido.lotacaoMaxima);

            if (leituras != 6) {
                printf("Erro ao ler os dados do local. Linha ignorada.\n");
                continue;
            }

            exibirLocal(&localLido);
            printf("\n");

            contador++;

            if (contador >= pageSize) {
                break;
            }
        }

        if (feof(arquivo)) {
            break; // Se chegamos ao final do arquivo, saímos do loop externo
        }

        pausar();

        printf("\n\tPressione '\e[0;32mn\e[m' para avançar, '\e[0;33mp\e[m' para retroceder, ou '\e[1;91mq\e[m' para sair...\n\t\t");
        char input = getchar();
        while (getchar() != '\n');

        if (input == 'q' || input == 'Q') {
            break; // Sair do loop se o usuário digitar 'q' ou 'Q'
        } else if (input == 'n' || input == 'N') {
            // Avançar para a próxima página
            limparConsole();
            pagina++;
            contador = 0;
        } else if (input == 'p' || input == 'P' && pagina > 1) {
            // Retroceder para a página anterior
            limparConsole();
            pagina--;
            contador = 0;
            reiniciarArquivo = 1;
            if (pagina < 1) {
                pagina = 1;
            } // Reiniciar o arquivo ao retroceder
        }

    } while (1);

    fclose(arquivo);
}
void exibirLocal(Local *local){
    printf("\t============= Detalhes \e[0;36m%s\e[m =============\n", local->nome);
    printf("\t\tNome: \e[0;36m%s\e[m\n", local->nome);
    printf("\t\tEndereço:\e[0;36m %s\e[m\n", local->endereco);
    printf("\t\tValor de Locação:\e[0;36mR$ %.2f\e[m\n", local->valorLocacao);
    printf("\t\tDescrição do Ambiente: \e[0;36m%s\e[m\n", local->descricaoAmbiente);
     printf("\t\tTelefone: \e[0;36m%s\e[m\n", local->telefone);
    printf("\t\tLotação Máxima:\e[0;36m%d pessoas\e[m\n", local->lotacaoMaxima);
    printf("\t=============================================\n");
}

//FUNÇÃO CRUD FUNCIONARIO
void criarFuncionario(){
    Funcionario novoFuncionario;
    limparConsole();
    printf(GREEN"\n\t========= Cadastro de Funcioário -  Debroi Eventos ==========\n"RESET);
    do {
        printf("\t\tNome do Funcionário: ");
        lerString(novoFuncionario.nome, MAX_TAMANHO);

        printf("\t\tCPF do Funcionário: ");
        lerCPFValidado(novoFuncionario.cpf, MAX_TAMANHO);

        printf("\t\tFunção do Funcionário: ");
        lerFuncaoValidada(novoFuncionario.funcao, MAX_TAMANHO);

        printf("\t\tSalário por Hora do Funcionário: ");
        novoFuncionario.salarioHora = validarEntradaDouble();

        printf("\t\tEmail do Funcionário ");
        lerEmailValidado(novoFuncionario.email,MAX_EMAIL);

        printf("\t\tTelefone do Funcionário ");
        lerTelefoneValidado(novoFuncionario.telefone,MAX_TELEFONE);

        printf("\t\tDisponibilidade (1 para ativo, 0 para inativo): ");
        novoFuncionario.disponibilidade = validarEntradaInt();

        FILE *arquivo = fopen("Funcionarios.txt", "a");

        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
        }

        // Escrever os dados no arquivo
        fprintf(arquivo, "%s;%s;%s;%lf;%s;%s;%d\n", novoFuncionario.nome, novoFuncionario.cpf,
                novoFuncionario.funcao,novoFuncionario.salarioHora,
                novoFuncionario.email,novoFuncionario.telefone,novoFuncionario.disponibilidade);
        // Fechar o arquivo
        fclose(arquivo);
        printf("Funcionario criado e salvo com sucesso!\n");
        sleep(1);
        limparConsole();

    } while (confirmarContinuacao() != 0);
    printf("\n\n\t\tVoltando ao menu anterior... ");
    sleep(1);
}
void modificarFuncionario(){
    char nomeModificar[50];
    printf("Digite o nome do Funcionario que deseja atualizar: ");
    lerString(nomeModificar,50);

    FILE *arquivoEntrada = fopen("Funcionarios.txt", "r");
    FILE *arquivoTemp = fopen("temp.txt", "w");

    if (arquivoEntrada == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Funcionario funcionarioLido;

    int encontrado = 0;
    int escolha;
    char linha[512];
    while (fgets(linha, sizeof(linha), arquivoEntrada) != NULL) {
          //  printf("Lido do arquivo: %s\n", linha);  // Debug: exibe a linha lida

            char salarioString[20];  // Ajuste: Use uma string temporária para o salário
            int leituras = sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d\n", funcionarioLido.nome, funcionarioLido.cpf,
                                  funcionarioLido.funcao, salarioString, funcionarioLido.email, funcionarioLido.telefone,
                                  &funcionarioLido.disponibilidade);

            if (leituras != 7) {
                printf("Erro ao ler os dados do funcionário. Linha ignorada.\n");
                continue;
            }

            // Converta a string do salário para um double
            if (sscanf(salarioString, "%lf", &funcionarioLido.salarioHora) != 1) {
                printf("Erro ao converter o salário para número. Linha ignorada.\n");
                continue;
            }

//    while (fscanf(arquivoEntrada, "%[^;];%[^;];%[^;];%lf;%[^;];%[^;];%d\n",
//                  funcionario.nome, funcionario.cpf, funcionario.funcao,
//                  funcionario.salarioHora, funcionario.email,funcionario.telefone,
//                  &funcionario.disponibilidade) != EOF) {

        if (strcmp(funcionarioLido.nome, nomeModificar) == 0) {
            // Se o nome corresponder, permita ao usuário modificar as características
             do{
                    printf("\t============= Status Atual Funcinário =============\n");
                    exibirFuncionario(&funcionarioLido);
                    printf("\n\t============= O que deseja atualizar =======\n");
                    printf("\t\t1. Nome\n");
                    printf("\t\t2. CPF\n");
                    printf("\t\t3. Função\n");
                    printf("\t\t4. Salário por Hora\n");
                    printf("\t\t5. Email\n");
                    printf("\t\t6. Telefone\n");
                    printf("\t\t7. Disponibilidade\n");
                    printf("\t\t8. Voltar\n");
                    printf("\n\t===========================================\n");
                    printf("\tDigite a opção escolhida: ");
                    escolha = validarEntradaInt();

            switch (escolha) {
            case 1:
                printf("\t\t Novo Nome: ");
                lerString(funcionarioLido.nome,50);
                limparConsole();
                break;
            case 2:
                printf("\t\tNovo CPF: ");
                lerCPFValidado(funcionarioLido,100);
                limparConsole();
                break;
            case 3:
                printf("\t\tNova Função: ");
                lerFuncaoValidada(funcionarioLido.funcao,200);
                limparConsole();

                break;
            case 4:
                printf("\t\tNovo Salário por Hora: ");
                funcionarioLido.salarioHora = validarEntradaDouble();
                limparConsole();

                break;
            case 5:
                printf("\t\tNovo Email: ");
                lerEmailValidado(funcionarioLido.email,MAX_EMAIL);
                limparConsole();

                break;
            case 6:
                printf("\t\tNovo Telefone: ");
                lerTelefoneValidado(funcionarioLido.telefone,MAX_TELEFONE);
                limparConsole();

                break;
            case 7:
                printf("\t\tNova Disponibilidade (1 para ativo, 0 para inativo): ");
                funcionarioLido.disponibilidade = validarEntradaInt();
                limparConsole();

                break;
            case 8:
                limparConsole();
               // exibirSubMenuCardapio(tipoUsuario);
                break;
            default:
                printf("\n\t\tOpção inválida! Tente novamente.\n");
                sleep(2);
                break;
 } } while (escolha != 8);
            encontrado = 1;
        }

        // Escreva no arquivo temporário
        fprintf(arquivoTemp, "%s;%s;%s;%.2lf;%s;%s;%d\n", funcionarioLido.nome, funcionarioLido.cpf,
                funcionarioLido.funcao,funcionarioLido.salarioHora,
                funcionarioLido.email,funcionarioLido.telefone,funcionarioLido.disponibilidade);
    }

    fclose(arquivoEntrada);
    fclose(arquivoTemp);

    // Remover o arquivo original
    remove("Funcionarios.txt");

    // Renomear o arquivo temporário para o original
    rename("temp.txt", "Funcionarios.txt");

    if (encontrado) {
        printf("Funcionario modificado com sucesso!\n");
        sleep(2);
    } else {
        printf("Funcionario não encontrado.\n");
        sleep(2);
    }
}
void excluirFuncionario(){
    char nomeExcluir[50];
    printf("Digite o nome do funcionario que deseja excluir: ");
    lerString(nomeExcluir, 50);

    FILE *arquivoEntrada = fopen("Funcionarios.txt", "r");
    FILE *arquivoTemp = fopen("temp.txt", "w");

    if (arquivoEntrada == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Funcionario funcionario;
    int encontrado = 0;

    while (fscanf(arquivoEntrada, "%[^;];%[^;];%[^;];%lf;%[^;];%[^;];%d\n",
                  funcionario.nome, funcionario.cpf, funcionario.funcao, &funcionario.salarioHora,
                  funcionario.email, funcionario.telefone, &funcionario.disponibilidade) != EOF) {

        if (strcmp(funcionario.nome, nomeExcluir) == 0) {
            encontrado = 1;
            exibirFuncionario(&funcionario); // Exibir detalhes do funcionário antes de excluir

            if (!confirmarExclusao()) {
                fclose(arquivoEntrada);
                fclose(arquivoTemp);
                printf("Exclusao cancelada.\n");
                return;
            }
        } else {
            // Escrever no arquivo temporário apenas se não for o funcionário a ser excluído
            fprintf(arquivoTemp, "%s;%s;%s;%lf;%s;%s;%d\n", funcionario.nome, funcionario.cpf,
                    funcionario.funcao, funcionario.salarioHora,
                    funcionario.email, funcionario.telefone, funcionario.disponibilidade);
        }
    }

    fclose(arquivoEntrada);
    fclose(arquivoTemp);

    if (!encontrado) {
        printf("Funcionario nao encontrado.\n");
        return;
    }

    // Remover o arquivo original
    remove("Funcionarios.txt");

    // Renomear o arquivo temporário para o original
    rename("temp.txt", "Funcionarios.txt");

    printf("Funcionario excluído com sucesso!\n");
}
void exibirFuncionarioDoArquivo(){
    FILE *arquivo = fopen("Funcionarios.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Funcionario funcionarioLido;
    int pageSize = 3; // Número de cardápios por página
    int pagina = 1;
    int contador = 0;
    int reiniciarArquivo = 1;

    do {
        if (reiniciarArquivo) {
            rewind(arquivo);
            reiniciarArquivo = 0;
        }

        printf("\t=========== Funcionarios (\e[0;32mPAGINA %d\e[m) =============\n", pagina);

        char linha[512];
       while (fgets(linha, sizeof(linha), arquivo) != NULL) {
          //  printf("Lido do arquivo: %s\n", linha);  // Debug: exibe a linha lida

            char salarioString[20];  // Ajuste: Use uma string temporária para o salário
            int leituras = sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d\n", funcionarioLido.nome, funcionarioLido.cpf,
                                  funcionarioLido.funcao, salarioString, funcionarioLido.email, funcionarioLido.telefone,
                                  &funcionarioLido.disponibilidade);

            if (leituras != 7) {
                printf("Erro ao ler os dados do funcionário. Linha ignorada.\n");
                continue;
            }

            // Converta a string do salário para um double
            if (sscanf(salarioString, "%lf", &funcionarioLido.salarioHora) != 1) {
                printf("Erro ao converter o salário para número. Linha ignorada.\n");
                continue;
            }

        //    printf("Valores lidos: Nome: %s, CPF: %s, Função: %s, Salário: %.2lf, Email: %s, Telefone: %s, Disponibilidade: %d\n",
        //           funcionarioLido.nome, funcionarioLido.cpf, funcionarioLido.funcao, funcionarioLido.salarioHora,
        //           funcionarioLido.email, funcionarioLido.telefone, funcionarioLido.disponibilidade);

            exibirFuncionario(&funcionarioLido);
            printf("\n");

            contador++;

            if (contador >= pageSize) {
                break;
            }
        }

        if (feof(arquivo)) {
            break; // Se chegamos ao final do arquivo, saímos do loop externo
        }

        pausar();

        printf("\n\tPressione '\e[0;32mn\e[m' para avançar, '\e[0;33mp\e[m' para retroceder, ou '\e[1;91mq\e[m' para sair...\n\t\t");
        char input = getchar();
        while (getchar() != '\n');

        if (input == 'q' || input == 'Q') {
            break; // Sair do loop se o usuário digitar 'q' ou 'Q'
        } else if (input == 'n' || input == 'N') {
            // Avançar para a próxima página
            limparConsole();
            pagina++;
            contador = 0;
        } else if (input == 'p' || input == 'P' && pagina > 1) {
            // Retroceder para a página anterior
            limparConsole();
            pagina--;
            contador = 0;
            reiniciarArquivo = 1;
            if(pagina < 1){
                pagina = 1;
            } // Reiniciar o arquivo ao retroceder
        }

    } while (1);

    fclose(arquivo);
}
void exibirFuncionario(const Funcionario *funcionario){
    printf("\t============= Detalhes do Funcionario =============\n");
    printf("\t\tNome:\e[0;36m %s\e[m\n", funcionario->nome);
    printf("\t\tCPF:\e[0;36m %s\e[m\n", funcionario->cpf);
    printf("\t\tFunção:\e[0;36m %s\e[m\n", funcionario->funcao);
    printf("\t\tSalário por hora:\e[0;36m %.2lf\e[m\n", funcionario->salarioHora);
    printf("\t\tEmail:\e[0;36m %s\e[m\n", funcionario->email);
    printf("\t\tTelefone:\e[0;36m %s\e[m\n", funcionario->telefone);
    printf("\t\tDisponibilidade:\e[0;36m  %s\e[m\n", funcionario->disponibilidade ? "\e[0;32mAtivo\e[m" : "\e[1;91mInativo\e[m");
    printf("\t=============================================\n");
}

//FUNÇÃO CRUD USUARIO
void criarUsuario(){
    Usuario novoUsuario;
    limparConsole();
    printf(GREEN"\n\t========= Cadastro de Usuario -  Debroi Eventos ==========\n"RESET);
    do {
        printf("\t\tLogin do Usuario: ");
        lerString(novoUsuario.login, MAX_USUARIO);

        printf("\t\tSenha do Usuario: ");
        lerString(novoUsuario.senha,MAX_SENHA);

        printf("\t\tNome do Usuario: ");
        lerString(novoUsuario.nome,MAX_USUARIO );

        printf("\t\tCPF do Usuario: ");
        lerCPFValidado(novoUsuario.cpf,MAX_CPF);

        printf("\t\tEmail do Usuario: ");
        lerEmailValidado(novoUsuario.email,MAX_EMAIL);

        printf("\t\tTelefone do Usuario: ");
        lerTelefoneValidado(novoUsuario.telefone,MAX_TELEFONE);

        printf("\t\tDisponibilidade do Usuario: ");
        novoUsuario.disponibilidade = validarEntradaInt();

        FILE *arquivo = fopen("Usuario.txt", "a");
        FILE *arquivoControle = fopen("controleUsuario.txt", "a");

        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
        }

        // Escrever os dados no arquivo
        fprintf(arquivo, "%s;%s\n",novoUsuario.login,novoUsuario.senha);
        fprintf(arquivoControle, "%s;%s;%s;%s;%s;%s;d\n",novoUsuario.login,novoUsuario.senha,novoUsuario.nome,novoUsuario.cpf,novoUsuario.email,novoUsuario.telefone,novoUsuario.disponibilidade);
        // Fechar o arquivo
        fclose(arquivo);
        fclose(arquivoControle);
        printf("Novo usuario criado e salvo com sucesso!\n");
        sleep(1);
        limparConsole();

    } while (confirmarContinuacao() != 0);
    printf("\n\n\t\tVoltando ao menu anterior... ");
    sleep(1);
}
void modificarUsuario(){
    char nomeModificar[50];
    printf("Digite o login do usuario que deseja modificar: ");
    lerString(nomeModificar,50);

    FILE *arquivoEntrada = fopen("controleUsuario.txt", "r");
    FILE *arquivoTemp = fopen("temp.txt", "w");
    FILE *arquivoTemp2 = fopen("temp2.txt", "w");


    if (arquivoEntrada == NULL || arquivoTemp == NULL || arquivoTemp2 == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Usuario usuario;

    int encontrado = 0;
    int escolha;

     while (fscanf(arquivoEntrada, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d\n",
                  usuario.login, usuario.senha, usuario.nome,
                  usuario.cpf, usuario.email, usuario.telefone, usuario.disponibilidade) != EOF) {

        if (strcmp(usuario.login, nomeModificar) == 0) {
            // Se o nome corresponder, permita ao usuário modificar as características
             do{
                    printf("\t============= Usuario Status Atual =============\n");
                    exibirUsuarios(&usuario);
                    printf("\n\t============= O que deseja atualizar =======\n");
                    printf("\t\t1. Login\n");
                    printf("\t\t2. Senha\n");
                    printf("\t\t3. Nome\n");
                    printf("\t\t4. Email\n");
                    printf("\t\t5. Telefone\n");
                    printf("\t\t6. Disponibilidade\n");
                    printf("\t\t7. Voltar\n");
                    printf("\n\t===========================================\n");
                    printf("\tDigite a opção escolhida: ");
                    scanf("%d", &escolha);

            switch (escolha) {
            case 1:
                printf("\t\t Novo Login: ");
                lerString(usuario.login,MAX_USUARIO);
                limparConsole();
                break;
            case 2:
                printf("\t\tNova Senha: ");
                lerString(usuario.senha,MAX_SENHA);
                limparConsole();
                break;
            case 3:
                printf("\t\tNovo Nome: ");
                lerString(usuario.nome,MAX_USUARIO);
                limparConsole();

                break;
            case 4:
                printf("\t\tNovo EMAIL: ");
                lerEmailValidado(usuario.email,MAX_EMAIL);
                limparConsole();

                break;
            case 5:
                printf("\t\tNovo Telefone: ");
                lerTelefoneValidado(usuario.telefone,MAX_TELEFONE);
                limparConsole();

                break;
            case 6:
                printf("\t\tNova Disponibilidade (1 para ativo, 0 para inativo): ");
                usuario.disponibilidade = validarEntradaInt();
                limparConsole();
                break;
            default:
                printf("\n\t\tOpção inválida! Tente novamente.\n");
                sleep(2);
                break;
 } } while (escolha != 7);
            encontrado = 1;
        }

        // Escreva no arquivo temporário
        fprintf(arquivoTemp, "%s;%s;%s;%s;%s;%s;%d\n", usuario.login, usuario.senha,
                        usuario.nome, usuario.cpf, usuario.email, usuario.telefone,usuario.disponibilidade);
                fprintf(arquivoTemp2, "%s;%s\n", usuario.login, usuario.senha);
    }

    fclose(arquivoEntrada);
    fclose(arquivoTemp);
    fclose(arquivoTemp2);

    // Remover o arquivo original
    remove("Usuario.txt");
    remove("controleUsuario.txt");

    // Renomear o arquivo temporário para o original
    rename("temp.txt", "controleUsuario.txt");
    rename("temp2.txt", "Usuario.txt");

    if (encontrado) {
        printf("Dados do usuario modificado com sucesso!\n");
        sleep(2);
    } else {
        printf("Usuario nao encontrado.\n");
        sleep(2);
    }
}
void excluirUsuario(){
    char loginExcluir[50];
    printf("Digite o login do usuario que deseja excluir: ");
    lerString(loginExcluir, 50);

    FILE *arquivoEntrada = fopen("controleUsuario.txt", "r");
    FILE *arquivoTemp = fopen("temp.txt", "w");
    FILE *arquivoTemp2 = fopen("temp2.txt", "w");

    if (arquivoEntrada == NULL || arquivoTemp == NULL || arquivoTemp2 == NULL ) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Usuario usuario;
    int encontrado = 0;

    // Ler e processar cada linha do arquivo
    while (fscanf(arquivoEntrada, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d\n",
                  usuario.login, usuario.senha, usuario.nome,
                  usuario.cpf, usuario.email, usuario.telefone, usuario.disponibilidade) != EOF) {

        // Verificar se a linha não está em branco
        if (usuario.login[0] != '\0') {
            if (strcmp(usuario.login, loginExcluir) == 0) {
                encontrado = 1;
                exibirUsuarios(&usuario); // Exibir detalhes do usuário antes de excluir

                if (!confirmarExclusao()) {
                    fclose(arquivoEntrada);
                    fclose(arquivoTemp);
                    fclose(arquivoTemp2);
                    remove("temp.txt");
                    remove("temp2.txt");
                    printf("Exclusao cancelada.\n");
                    return;
                }
            } else {

                // Escrever no arquivo temporário apenas se não for o usuário a ser excluído
                fprintf(arquivoTemp, "%s;%s;%s;%s;%s;%s;%d\n", usuario.login, usuario.senha,
                        usuario.nome, usuario.cpf, usuario.email, usuario.telefone,usuario.disponibilidade);
                fprintf(arquivoTemp2, "%s;%s\n", usuario.login, usuario.senha);
            }
        }
    }

    fclose(arquivoEntrada);
    fclose(arquivoTemp);
    fclose(arquivoTemp2);

    if (!encontrado) {
        remove("temp.txt");
        remove("temp2.txt");// Se não foi encontrado, remover o arquivo temporário
        printf("Usuario nao encontrado.\n");
        return;
    }

    // Remover o arquivo original
    remove("controleUsuario.txt");
    remove("Usuario.txt");
    rename("temp.txt", "controleUsuario.txt");
    rename("temp2.txt", "Usuario.txt");

    printf("Usuario excluido com sucesso!\n");
}
void exibirUsuariosDoArquivo(){
   FILE *arquivo = fopen("controleUsuario.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Usuario usuarioLido;
    int pageSize = 3;
    int pagina = 1;
    int contador = 0;
    int reiniciarArquivo = 1;

    do {
        if (reiniciarArquivo) {
            rewind(arquivo);
            reiniciarArquivo = 0;
        }

        printf("\t=========== Usuarios (PAGINA %d) =============\n", pagina);

        char linha[512];
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d\n",
                   usuarioLido.login, usuarioLido.senha,
                   usuarioLido.nome, usuarioLido.cpf,
                   usuarioLido.email, usuarioLido.telefone, &usuarioLido.disponibilidade);

            exibirUsuarios(&usuarioLido);
            printf("\n");

            contador++;

            if (contador >= pageSize) {
                break;
            }
        }

        if (feof(arquivo)) {
            break;
        }

        pausar();

        printf("\n\tPressione '\e[0;32mn\e[m' para avançar, '\e[0;33mp\e[m' para retroceder, ou '\e[1;91mq\e[m' para sair...\n\t\t");
        char input = getchar();
        while (getchar() != '\n');

        if (input == 'q' || input == 'Q') {
            break;
        } else if (input == 'n' || input == 'N') {
            limparConsole();
            pagina++;
            contador = 0;
        } else if ((input == 'p' || input == 'P') && pagina > 1) {
            limparConsole();
            pagina--;
            contador = 0;
            reiniciarArquivo = 1;
            if(pagina < 1){
                pagina = 1;
            }
        }

    } while (1);

    fclose(arquivo);
}
void exibirUsuarios(const Usuario *usuario){
    printf("\t============= Detalhes do Usuario =============\n");
    printf("\t\tLogin:\e[0;36m %s\e[m\n", usuario->login);
    printf("\t\tSenha:\e[0;36m %s\e[m\n", usuario->senha);
    printf("\t\tNome do Usuario:\e[0;36m %s\e[m\n", usuario->nome);
    printf("\t\tCPF:\e[0;36m %s\e[m\n", usuario->cpf);
    printf("\t\tEmail:\e[0;36m %s\e[m\n", usuario->email);
    printf("\t\tTelefone:\e[0;36m %s\e[m\n", usuario->telefone);
    printf("\t\tDisponibilidade:\e[0;36m  %s\e[m\n", usuario->disponibilidade ? "\e[0;32mAtivo\e[m" : "\e[1;91mInativo\e[m");
    printf("\t=============================================\n");
}

//FUNÇÕES PARA LER ENTRADAS COM VALIDAÇÃO

int validandoAnoBissexto(int ano){

    return (ano % 400 == 0) || ((ano % 100 != 0) && (ano % 4 == 0));

}
int validandoData(int dia, int mes, int ano){
    // Verifique o mês
    if(mes < 1 || mes > 12){
        return 0; // Mês inválido
    }

    // Verifique o dia
    if(dia < 1){
        return 0; // Dia inválido
    }

    if(mes == 2){
        // Fevereiro: Verifique se é bissexto
        if(validandoAnoBissexto(ano)){
            if(dia > 29){
                return 0; // Dia inválido para um ano bissexto
            }
        }
        else{
            if(dia > 28){
                return 0; // Dia inválido para um ano não bissexto
            }
        }
    }
    else if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
        // Meses com 30 dias
        if(dia > 30){
            return 0; // Dia inválido
        }
    }
    else{
        // Meses com 31 dias
        if(dia > 31){
            return 0; // Dia inválido
        }
    }

    return 1; // Data válida
}
void lerString(char *destino, int tamanho){
    // Obtém a posição inicial do cursor
    struct CursorPos posInicial = pegarCursorPos();

    do {
        fflush(stdin);
        fgets(destino, tamanho, stdin);

        // Limpa o buffer de entrada
        if (destino[0] != '\0' && destino[0] != '\n') {
            destino[strcspn(destino, "\n")] = '\0';
        }

        // Verifica se a entrada está vazia
        if (destino[0] == '\0' || (destino[0] == '\n' && destino[1] == '\0')) {

            // Aguarda 2 segundos antes de apagar a mensagem
            apagarMensagemAposTempo(2,"Entrada inválida. Por favor, tente novamente.");

            // Move o cursor para a posição inicial e limpa a mensagem de erro
            moveCursorParaPosicao(posInicial);
            printf("\033[2K");
        } else {
            break;
        }
    } while (1);
}
void lerCPFValidado(char *cpf, int tamanhoMaximo){
    struct CursorPos posInicial;

    do {
        fflush(stdin);
        posInicial = pegarCursorPos();
        fgets(cpf, tamanhoMaximo, stdin);

        // Remove caracteres não numéricos
        int j = 0;
        for (int i = 0; cpf[i] != '\0'; i++) {
            if (isdigit(cpf[i])) {
                cpf[j++] = cpf[i];
            }
        }
        cpf[j] = '\0';

        if (!validarCPF(cpf)) {
            apagarMensagemAposTempo(2, "CPF inválido. Por favor, tente novamente.");
            Sleep(2);
            moveCursorParaPosicao(posInicial);
        } else {
            break;
        }
    } while (1);
}
void lerFuncaoValidada(char *funcao, int tamanhoMaximo){
    struct CursorPos posInicial;

    do {
        fflush(stdin);
        posInicial = pegarCursorPos();
        fgets(funcao, tamanhoMaximo, stdin);

        if (funcao[0] != '\0' && funcao[0] != '\n') {
            funcao[strcspn(funcao, "\n")] = '\0';
        }

        // Adicione qualquer lógica adicional de validação necessária para a função

        if (strlen(funcao) == 0) {
            apagarMensagemAposTempo(2, "Função inválida. Por favor, tente novamente.");
            Sleep(2);
            moveCursorParaPosicao(posInicial);
        } else {
            break;
        }
    } while (1);
}
void lerEmailValidado(char *destino, int tamanhoMaximo){
    struct CursorPos posInicial;

    do {
        fflush(stdin);
        posInicial = pegarCursorPos();
        fgets(destino, tamanhoMaximo, stdin);

        if (destino[0] != '\0' && destino[0] != '\n') {
            destino[strcspn(destino, "\n")] = '\0';
        }

        if (!validarEmail(destino)) {
            apagarMensagemAposTempo(2, "E-mail inválido. Por favor, tente novamente.");
            Sleep(2);
            moveCursorParaPosicao(posInicial);
        } else {
            break;
        }
    } while (1);
}
void lerTelefoneValidado(char *telefone, int tamanhoMaximo){
    struct CursorPos posInicial;

    do {
        fflush(stdin);
        posInicial = pegarCursorPos();
        printf("Digite um número de telefone (no formato XX XXXXX-XXXX): ");
        fgets(telefone, tamanhoMaximo, stdin);

        if (telefone[0] != '\0' && telefone[0] != '\n') {
            telefone[strcspn(telefone, "\n")] = '\0';
        }

        if (validarTelefone(telefone)) {
            apagarMensagemAposTempo(2, "Número de telefone inválido. Por favor, tente novamente.");
            Sleep(2);
            moveCursorParaPosicao(posInicial);
        } else {
            break;
        }
    } while (1);
}
int confirmarExclusao(){
    char resposta;
    printf("Tem certeza que deseja excluir ? (S/N): ");
    scanf(" %c", &resposta);  // Adicionamos um espaço antes do %c para consumir a nova linha pendente
    limparBuffer(); // Limpar o buffer para evitar problemas de leitura posterior

    return (resposta == 'S' || resposta == 's');
}
int confirmarContinuacao(){
    char resposta;
    printf("Deseja continuar o realizando este tipo de operação? (S/N): ");
    scanf(" %c", &resposta);  // Adicionamos um espaço antes do %c para consumir a nova linha pendente
    limparBuffer(); // Limpar o buffer para evitar problemas de leitura posterior

    return (resposta == 'S' || resposta == 's');
}
int validarEntradaInt(){
    int valor;
    struct CursorPos posInicial = pegarCursorPos();

    do {
        fflush(stdin);
        if (scanf("%d", &valor) == 1) {
            limparBuffer();
            return valor;
        } else {
            // Verifica se a entrada não é um número
            if (scanf("%*s") == 0) {
                apagarMensagemAposTempo(2, "\n\t      Por favor, insira um valor válido (número inteiro).");
                Sleep(1);

                // Move o cursor para a posição inicial e limpa a mensagem de erro
                moveCursorParaPosicao(posInicial);
            } else {
                break;
            }
        }
    } while (1);

    return valor;  // Retorno adicional, caso deseje continuar com a entrada inválida
}
double validarEntradaDouble(){
    double valor;
    struct CursorPos posInicial = pegarCursorPos();

    do {
        fflush(stdin);
        if (scanf("%lf", &valor) == 1) {
            limparBuffer();
            return valor;
        } else {
            // Verifica se a entrada não é um número
            if (scanf("%*s") == 0) {
                apagarMensagemAposTempo(2, "Por favor, insira um valor válido (número real).");
                Sleep(2);

                // Move o cursor para a posição inicial e limpa a mensagem de erro
                moveCursorParaPosicao(posInicial);
            } else {
                break;
            }
        }
    } while (1);

    return valor;  // Retorno adicional, caso deseje continuar com a entrada inválida
}
bool validarEmail(const char *email){
    int tamanho = strlen(email);
    bool temArroba = false;
    bool temPonto = false;
    int posicaoArroba = -1;

    for (int i = 0; i < tamanho; i++) {
        if (email[i] == '@') {
            if (temArroba) {
                return false;
            }
            temArroba = true;
            posicaoArroba = i;
        } else if (email[i] == '.') {
            temPonto = true;
        }
    }

    if (!temArroba || !temPonto || posicaoArroba == 0 || posicaoArroba == tamanho - 1) {
        return false;
    }

    int posicaoUltimoPonto = strrchr(email, '.') - email;
    if (tamanho - posicaoUltimoPonto - 1 < 2) {
        return false;
    }

    for (int i = 0; i < posicaoArroba; i++) {
        if (!isalnum(email[i]) && email[i] != '.' && email[i] != '-') {
            return false;
        }
    }

    return true;
}
bool validarTelefone(const char *telefone){
    int tamanho = strlen(telefone);

    if (tamanho != 14) {
        return false;
    }

    for (int i = 0; i < tamanho; i++) {
        if (i == 2 || i == 6) {
            if (telefone[i] != ' ') {
                return false;
            }
        } else if (i == 9) {
            if (telefone[i] != '-') {
                return false;
            }
        } else {
            if (!isdigit(telefone[i])) {
                return false;
            }
        }
    }

    return true;
}
int validarCPF(const char *cpf){
    int i, j;
    char digitos[11];
    int soma1 = 0, soma2 = 0, resto;

    // Remove caracteres não numéricos
    for (i = j = 0; cpf[i] != '\0'; i++) {
        if (isdigit(cpf[i])) {
            digitos[j++] = cpf[i];
        }
    }

    if (j != 11) {
        return 0; // CPF deve ter 11 dígitos
    }

    // Verifica se todos os dígitos são iguais
    for (i = 1; i < 11; i++) {
        if (digitos[i] != digitos[0]) {
            break;
        }
    }

    if (i == 11) {
        return 0; // Todos os dígitos são iguais
    }

    // Calcula o primeiro dígito verificador
    for (i = 0; i < 9; i++) {
        soma1 += (digitos[i] - '0') * (10 - i);
    }

    resto = soma1 % 11;

    if (resto < 2) {
        resto = 0;
    } else {
        resto = 11 - resto;
    }

    if (resto != digitos[9] - '0') {
        return 0; // Primeiro dígito verificador incorreto
    }

    // Calcula o segundo dígito verificador
    for (i = 0; i < 10; i++) {
        soma2 += (digitos[i] - '0') * (11 - i);
    }

    resto = soma2 % 11;

    if (resto < 2) {
        resto = 0;
    } else {
        resto = 11 - resto;
    }

    if (resto != digitos[10] - '0') {
        return 0; // Segundo dígito verificador incorreto
    }

    return 1; // CPF válido
}
//fUNÇÃO PAUSAR
void pausar(){
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n'); // Limpa o buffer do teclado
    getchar(); // Aguarda a tecla Enter
}

//FUNCAO ID
int idGerador(int numero){
    srand(time(NULL));
    numero=100000+(rand()%(999999-100000+1));
}

// Função para mover o cursor para uma posição específica
void moveCursorParaPosicao(struct CursorPos pos){
    COORD coord;
    coord.X = pos.coluna;
    coord.Y = pos.linha;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct CursorPos pegarCursorPos(){
   CONSOLE_SCREEN_BUFFER_INFO csbi;
    struct CursorPos pos;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    pos.linha = csbi.dwCursorPosition.Y;
    pos.coluna = csbi.dwCursorPosition.X;

    return pos;
}

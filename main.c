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

// ***** DEFINI��ES DE CONSTANTES ***** //
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

// ***** DEFINI��ES DE CORES ***** //
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

// ***** DEFINI��ES DAS STRUCTS ***** //
struct CursorPos {
    int linha;
    int coluna;
};
typedef struct { // Struct do Evento

    int idEvento; // N�mero identificador de evento

    // Informa��es do contratante do evento
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

    int status; // '0' cancelado, '1' para em andamento, '2' conclu�do

} Evento;
typedef struct { // Struct do Card�pio
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
typedef struct { // Struct do Funcion�rio
    char nome[MAX_USUARIO];
    char cpf[MAX_CPF];
    char funcao[MAX_TAMANHO];
    double salarioHora;
    char email[MAX_EMAIL];
    char telefone[MAX_TELEFONE];
    int disponibilidade;
} Funcionario;
typedef struct { // Struct do Usu�rio
    char login[MAX_USUARIO];
    char senha[MAX_SENHA];
    char nome[MAX_USUARIO];
    char cpf[MAX_CPF];
    char email[MAX_EMAIL];
    char telefone[MAX_TELEFONE];
    int disponibilidade;
} Usuario;
// ********************************* //

// ***** DECLARA��ES DAS FUN��ES MENU ***** //
void exibirMenuPrincipal();
void exibirMenuAdmin();
void exibirSubMenuGerencimento();
void exibirSubMenuEventos();
void exibirSubMenuCardapio();
void exibirSubMenuUsuario();
void exibirSubMenuFuncionario();
void exibirSubMenuLocais();
// **************************************** //

// ***** DECLARA��O DA FUN��O DE LOGIN ***** //
int fazerLogin(char *arquivo, char *tipoUsuario);
// ***************************************** //

// ***** DECLARA��ES DAS FUN��ES PARA LIMPAR CONSOLE ***** //
void limparBuffer();
void limparConsole();
void apagarMensagemAposTempo();
// ******************************************************* //

//DECLARA��ES DE FUN��ES CRUD LUGAR
void criarLocal();
void modificarLocal();
void excluirLocal();
void exibirLocalDoArquivo();
void exibirLocal();

//DECLARA��ES DE FUN��ES CRUD FUNCIONARIO
void criarFuncionario();
void modificarFuncionario();
void excluirFuncionario();
void exibirFuncionarioDoArquivo();
void exibirFuncionario();

//DECLARA��ES DE FUN��ES CRUD CARDAPIO
void criarCardapio();
void atualizarCardapio();
void excluirCardapio();
void exibirCardapiosDoArquivo();
void exibirCardapio();

//DECLARA��ES DE FUN��ES CRUD USUARIO
void criarUsuario();
void modificarUsuario();
void excluirUsuario();
void exibirUsuariosDoArquivo();
void exibirUsuarios();

//DECLARA��ES DE FUN��ES LER COM VALIDA��O
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

//DECLARA��ES DE FUN��ES PAUSA
void pausar();
//DECLARA��ES DE FUN��ES POSICAO CURSOR
struct CursorPos pegarCursorPos();
void moveCursorParaPosicao();

// ***** FUN��O PRINCIPAL ***** //
int main(){

    setlocale(LC_ALL, "");

    exibirMenuPrincipal();

    return 0;
}
// **************************** //

// ***** FUN��ES DE MENU ***** //
void exibirMenuPrincipal(){

    int escolha;

    do{

        system(CLEAR_SCREEN);

        printf("\n\t|-------------------------------------------|\n");
        printf("\t| Sistema de Gerenciamento - %sDebroi Eventos%s |\n", CYAN, RESET);
        printf("\t|-------------------------------------------|\n");
        printf("\t| 1 | Iniciar como %sAdministrador%s            |\n", GREEN, RESET);
        printf("\t|-------------------------------------------|\n");
        printf("\t| 2 | Iniciar como %sUsu�rio%s                  |\n", YELLOW, RESET);
        printf("\t|-------------------------------------------|\n");
        printf("\t| 3 | %sSair do Programa%s                      |\n", RED, RESET);
        printf("\t|-------------------------------------------|\n");
        printf("\n\t      Escolha uma op��o: ");

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
                printf("\n\t      %sOp��o inv�lida!%s Tente novamente.\n", YELLOW, RESET);
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
            printf("\n\t\tEscolha uma op��o: ");

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
                    printf("\n\t\t%sOp��o inv�lida!%s Tente novamente.\n", YELLOW, RESET);
                    sleep(2);
                    break;

            }

        }while(escolha != 4);

    }
    else{

         do{

            system(CLEAR_SCREEN);

            printf("\n\t|---------------------------------------------------|\n");
            printf("\t| Sistema de Gerenciamento %sDebroi Eventos%s - %sUsu�rio%s |\n", CYAN, RESET, GREEN, RESET);
            printf("\t|---------------------------------------------------|\n");
            printf("\t| 1 | \tMenus de Gerenciamento                      |\n");
            printf("\t|---------------------------------------------------|\n");
            printf("\t| 2 | \t%sVoltar Menu Inicial%s                         |\n", RED, RESET);
            printf("\t|---------------------------------------------------|\n\n");
            printf("\t\tEscolha uma op��o: ");

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
                    printf("\n\t\t%sOp��o inv�lida!%s Tente novamente.\n", YELLOW, RESET);
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
        printf("\t| 2 | \tMenu Card�pios                            |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 3 | \tMenu Locais                               |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 4 | \tMenu Funcion�rios                         |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 5 | \tMenu Usu�rios                             |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 6 | \t%sVoltar%s                                    |\n", RED, RESET);
        printf("\t|-------------------------------------------------|\n");
        printf("\n\t\tEscolha uma op��o: ");

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
                printf("\n\t\t%sOp��o inv�lida!%s Tente novamente.\n", YELLOW, RESET);
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
        printf("\n\t\tEscolha uma op��o: ");

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
                printf("\n\t\t%sOp��o inv�lida!%s Tente novamente.\n", YELLOW, RESET);
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
        printf("\t|    \tMenu Card�pios                            |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 1 |\tCriar Card�pio                            |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 2 |\tAtualizar Card�pio                        |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 3 |\tVisualizar Card�pios Dispon�veis          |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 4 |\tExcluir Card�pio                          |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 5 |\t%sVoltar%s                                    |\n", RED, RESET);
        printf("\t|-------------------------------------------------|\n");
        printf("\n\t\tEscolha uma op��o: ");

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
                printf("\n\t\t%sOp��o inv�lida!%s Tente novamente.\n", YELLOW, RESET);
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
        printf("\t| 3 |\tVisualizar Locais Dispon�veis             |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 4 |\tExcluir Local                             |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 5 |\t%sVoltar%s                                    |\n", RED, RESET);
        printf("\t|-------------------------------------------------|\n");
        printf("\n\t\tEscolha uma op��o: ");

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
                printf("\n\t\t%sOp��o inv�lida!%s Tente novamente.\n", YELLOW, RESET);
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
        printf("\t|    \tMenu Funcion�rios                         |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 1 |\tAdicionar Funcion�rio                     |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 2 |\tAtualizar Funcion�rio                     |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 3 |\tVisualizar Funcion�rios                   |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 4 |\tExcluir Funcion�rio                       |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 5 |\t%sVoltar%s                                    |\n", RED, RESET);
        printf("\t|-------------------------------------------------|\n");
        printf("\n\t\tEscolha uma op��o: ");

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
                printf("\n\t\t%sOp��o inv�lida!%s Tente novamente.\n", YELLOW, RESET);
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
        printf("\t|    \tMenu Usu�rios                             |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 1 |\tAdicionar Usu�rio                         |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 2 |\tAtualizar Usu�rio                         |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 3 |\tVisualizar Usu�rios                       |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 4 |\tExcluir Usu�rio                           |\n");
        printf("\t|-------------------------------------------------|\n");
        printf("\t| 5 |\t%sVoltar%s                                    |\n", RED, RESET);
        printf("\t|-------------------------------------------------|\n");
        printf("\n\t\tEscolha uma op��o: ");

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
                printf("\n\t\t%sOp��o inv�lida!%s Tente novamente.\n", YELLOW, RESET);
                sleep(2);
                break;
        }

    }while(escolha != 5);

}
// *************************** //

// ***** FUN��O DE LOGIN ***** //
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

        printf("\n\t%sN�mero m�ximo de tentativas alcan�ado.%s Saindo do login.", RED, WHITE);

        sleep(2);

    }

    return loginValido;
}
// *************************** //

// ***** FUN��ES PARA LIMPAR CONSOLE ***** //
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

// ***** FUN��ES CRUD EVENTO ***** //
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

        printf("\tDescri��o do Evento: ");
        lerString(novoEvento.descricaoEvento, MAX_DESCRICAO);

        printf("\tDescri��o a quantidade de pessoas: ");
        novoEvento.quantidadePessoas = validarEntradaInt();

        int aux=0; // Vari�vel para auxiliar o 'DO WHILE'

        // Obt�m o tempo atual em segundos desde 1 de janeiro de 1970 (Unix timestamp)
        time_t tempoAtual;
        time(&tempoAtual);

        // Converte o tempo atual em uma estrutura de data
        struct tm *infoTempo = localtime(&tempoAtual);

        // Obt�m a data atual
        int diaAtual = infoTempo->tm_mday;
        int mesAtual = infoTempo->tm_mon + 1;
        int anoAtual = infoTempo->tm_year + 1900;

        do{

            printf("\tDigite o dia do evento: ");
            novoEvento.dia = validarEntradaInt();

            printf("\tDigite o m�s do evento: ");
            novoEvento.mes = validarEntradaInt();

            printf("\tDigite o ano do evento: ");
            novoEvento.ano = validarEntradaInt();

            if(validandoData(novoEvento.dia, novoEvento.mes, novoEvento.ano)){
                if((novoEvento.dia<diaAtual && novoEvento.mes<mesAtual) && novoEvento.ano<anoAtual){
                    printf("\t%sA data � inv�lida!%s Digite Novamente.\n", RED, RESET);
                }
                else{
                    aux++;
                }
            }
            else{
                printf("\t%sA data � inv�lida!%s Digite Novamente.\n", RED, RESET);
            }

        }while(aux==0);


        // **************************************************************** //

        // ***** Manipulando o arquivo 'cardapios.txt' ***** //

        printf("Digite o nome do card�pio que deseja: ");
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

        // C�lculo do valor estimado para o evento
        novoEvento.valorCardapio = novoEvento.valorCardapio * novoEvento.quantidadePessoas;
        novoEvento.valorEstimado = (novoEvento.valorCardapio + novoEvento.valorLocal)*1.1;

        novoEvento.status=1; // Status do evento(ANDAMENTO/CONCLU�DO/CANCELADO)


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
    int aux=0; // Vari�vel para auxiliar o 'DO WHILE'

    while (fscanf(arquivoEntrada, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d;%[^;];%[^;];%[^;];%d;%[^;];%[^;];%[^;];%[^;];%d;%f;%f;%f;%d\n",
                    &evento.idEvento, evento.nomeContratante, evento.cpfContratante, evento.emailContratante, evento.telefoneContratante,
                    evento.nomeEvento, evento.descricaoEvento, &evento.quantidadePessoas, &evento.dia, &evento.mes, &evento.ano,
                    evento.nomeCardapio, evento.descricaoCardapio, evento.ingredientesCardapio, &evento.quantidadePessoasCardapio,
                    evento.nomeLocal, evento.enderecoLocal, evento.descricaoAmbienteLocal, evento.telefoneLocal, &evento.lotacaoMaximaLocal,
                    &evento.valorEstimado, &evento.valorCardapio, &evento.valorLocal,
                    &evento.status) != EOF){

        if (strcmp(evento.idEvento, eventoModificar) == 0) {

            // Se o nome corresponder, permita ao usu�rio modificar as caracter�sticas

            do{

                printf("\t============= Card�pio Atual =============\n");
                exibirEvento(&evento);
                printf("\n\t============= O que deseja atualizar =======\n");
                printf("\t\t1. E-mail contratante\n");
                printf("\t\t2. Telefone contratante\n");
                printf("\t\t3. Quantidade de pessoas\n");
                printf("\t\t4. Data\n");
                printf("\t\t5. Card�pio\n");
                printf("\t\t6. Local\n");
                printf("\t\t7. Voltar\n");
                printf("\n\t===========================================\n");
                printf("\tDigite a op��o escolhida: ");

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

                        // Obt�m o tempo atual em segundos desde 1 de janeiro de 1970 (Unix timestamp)
                        time_t tempoAtual;
                        time(&tempoAtual);

                        // Converte o tempo atual em uma estrutura de data
                        struct tm *infoTempo = localtime(&tempoAtual);

                        // Obt�m a data atual
                        int diaAtual = infoTempo->tm_mday;
                        int mesAtual = infoTempo->tm_mon + 1;
                        int anoAtual = infoTempo->tm_year + 1900;

                        do{

                            printf("\tDigite o dia do evento: ");
                            evento.dia = validarEntradaInt();

                            printf("\tDigite o m�s do evento: ");
                            evento.mes = validarEntradaInt();

                            printf("\tDigite o ano do evento: ");
                            evento.ano = validarEntradaInt();

                            if(validandoData(evento.dia, evento.mes, evento.ano)){

                                if((evento.dia<diaAtual || evento.mes<mesAtual) || evento.ano<anoAtual){

                                    printf("\t%sA data � inv�lida!%s Digite Novamente.\n", RED, RESET);

                                }
                                else{

                                    aux++;

                                }
                            }
                            else{

                                printf("\t%sA data � inv�lida!%s Digite Novamente.\n", RED, RESET);

                            }

                        }while(aux==0);

                        limparConsole();

                        break;
                    case 5:

                        printf("\t\tNova card�pio: ");
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
                        printf("\n\t\tOp��o inv�lida! Tente novamente.\n");
                        sleep(2);
                        break;
                }
            }while (escolha != 6);
            encontrado = 1;
        }

        // C�lculo do valor estimado para o evento
        evento.valorCardapio = evento.valorCardapio*evento.quantidadePessoas;
        evento.valorEstimado = evento.valorCardapio + evento.valorLocal;

        fprintf(arquivoTemp, "%d;%s;%s;%s;%s;%s;%s;%d;%d;%d;%d;%s;%s;%s;%d;%s;%s;%s;%s;%d;%f;%f;%f;%d\n", // Escrever os dados no arquivo tempor�rio
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

    // Renomear o arquivo tempor�rio para o original
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
    int pageSize = 2; // N�mero de eventos por p�gina
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
            break; // Se chegamos ao final do arquivo, sa�mos do loop externo
        }

        limparBuffer();

        printf("\n\tPressione '\e[0;32mn\e[m' para avan�ar, '\e[0;33mp\e[m' para retroceder, ou '\e[1;91mq\e[m' para sair...\n\t\t");
        char input = getchar();

        while (getchar() != '\n');

        if (input == 'q' || input == 'Q') {
            break; // Sair do loop se o usu�rio digitar 'q' ou 'Q'
        } else if (input == 'n' || input == 'N') {
            // Avan�ar para a pr�xima p�gina
            limparConsole();
            pagina++;
            contador = 0;
        } else if (input == 'p' || input == 'P' && pagina > 1) {
            // Retroceder para a p�gina anterior
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
    printf("\t\tDescric�o: %s\n", evento->descricaoEvento);
    printf("\t\tDATA: %d/%d/%d\n", evento->dia, evento->mes, evento->ano);
    printf("\t\tQTD PESSOAS: %d\n", evento->quantidadePessoas);
    printf("\t\tCard�pio: %s\n", evento->nomeCardapio);
    printf("\t\tLocal: %s\n", evento->nomeLocal);
    printf("\t\tEndere�o: %s\n", evento->enderecoLocal);
    printf("\t\tValor card�pio:: %.2f\n", evento->valorCardapio);
    printf("\t\tValor local: %.2f\n", evento->valorLocal);
    printf("\t\tValor estimado: %.2f\n", evento->valorEstimado);
    printf("\t\tStatus:\e[0;36m  %s\e[m\n", evento->status ? "\e[0;32mAtivo\e[m" : "\e[1;91mInativo\e[m");

}
void excluirEvento(){ // Bloqueando o Evento
}
// ******************************* //

//FUN��O CRUD CARDAPIO
void criarCardapio(){
    Cardapio novoCardapio;
    limparConsole();
    printf(GREEN"\n\t========= Cadastro de Card�pio -  Debroi Eventos ==========\n"RESET);

    do {

        printf("\t\tNome do Card�pio: ");
        lerString(novoCardapio.nome, 50);

        printf("\t\tDescri��o do Card�pio: ");
        lerString(novoCardapio.descricao, 100);

        printf("\t\tIngredientes: ");
        lerString(novoCardapio.ingredientes, 200);

        printf("\t\tQuantidade de Pessoas: ");
        novoCardapio.quantidadePessoas = validarEntradaInt();

        printf("\t\tValor do card�pio por pessoa: ");
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
        printf("Card�pio criado e salvo com sucesso!\n");
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
            // Se o nome corresponder, permita ao usu�rio modificar as caracter�sticas
             do{
                    printf("\t============= Cardapio Atual =============\n");
                    exibirCardapio(&cardapio);
                    printf("\n\t============= O que deseja atualizar =======\n");
                    printf("\t\t1. Nome\n");
                    printf("\t\t2. Descri��o\n");
                    printf("\t\t3. Ingredientes\n");
                    printf("\t\t4. Valor do cardapio por pessoas\n");
                    printf("\t\t5. Disponibilidade\n");
                    printf("\t\t6. Voltar\n");
                    printf("\n\t===========================================\n");
                    printf("\tDigite a op��o escolhida: ");
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
                printf("\n\t\tOp��o inv�lida! Tente novamente.\n");
                sleep(2);
                break;
 } } while (escolha != 6);
            encontrado = 1;
        }

        // Escreva no arquivo tempor�rio
        fprintf(arquivoTemp, "%s;%s;%s;%d;%f;%d\n", cardapio.nome, cardapio.descricao,
                cardapio.ingredientes, cardapio.quantidadePessoas,
                cardapio.valor, cardapio.disponibilidade);
    }

    fclose(arquivoEntrada);
    fclose(arquivoTemp);

    // Remover o arquivo original
    remove("cardapios.txt");

    // Renomear o arquivo tempor�rio para o original
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
            exibirCardapio(&cardapio); // Exibir detalhes do card�pio antes de excluir

            if (!confirmarExclusao()) {
                fclose(arquivoEntrada);
                fclose(arquivoTemp);
                remove("temp.txt");
                printf("Exclusao cancelada.\n");
                return;
            }
        } else {
            // Escrever no arquivo tempor�rio apenas se n�o for o card�pio a ser exclu�do
            fprintf(arquivoTemp, "%s;%s;%s;%d;%f;%d\n", cardapio.nome, cardapio.descricao,
                    cardapio.ingredientes, cardapio.quantidadePessoas,
                    cardapio.valor, cardapio.disponibilidade);
        }
    }

    fclose(arquivoEntrada);
    fclose(arquivoTemp);

    if (!encontrado) {
        remove("temp.txt"); // Se n�o foi encontrado, remover o arquivo tempor�rio
        printf("Cardapio nao encontrado.\n");
        return;
    }

    // Remover o arquivo original
    remove("cardapios.txt");

    // Renomear o arquivo tempor�rio para o original
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
    int pageSize = 3; // N�mero de card�pios por p�gina
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
            break; // Se chegamos ao final do arquivo, sa�mos do loop externo
        }

        pausar();

        printf("\n\tPressione '\e[0;32mn\e[m' para avan�ar, '\e[0;33mp\e[m' para retroceder, ou '\e[1;91mq\e[m' para sair...\n\t\t");
        char input = getchar();
        while (getchar() != '\n');

        if (input == 'q' || input == 'Q') {
            break; // Sair do loop se o usu�rio digitar 'q' ou 'Q'
        } else if (input == 'n' || input == 'N') {
            // Avan�ar para a pr�xima p�gina
            limparConsole();
            pagina++;
            contador = 0;
        } else if (input == 'p' || input == 'P' && pagina > 1) {
            // Retroceder para a p�gina anterior
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

// FUN��O CRUD LOCAL
void criarLocal(){

    Local novoLocal;

    limparConsole();

    printf("\n\t========= Cadastro de Local - Debroi Eventos ==========\n");

    do {

        printf("\t\tNome do Local: ");
        lerString(novoLocal.nome, MAX_TAMANHO);

        printf("\t\tEndere�o do Local: ");
        lerString(novoLocal.endereco, MAX_TAMANHO);

        printf("\t\tValor de Loca��o do Local: ");
        novoLocal.valorLocacao = validarEntradaDouble();

        printf("\t\tDescri��o do Ambiente: ");
        lerString(novoLocal.descricaoAmbiente, MAX_DESCRICAO);

        printf("\t\tTelefone: ");
        lerTelefoneValidado(novoLocal.telefone, MAX_TELEFONE);

        printf("\t\tLota��o M�xima do Local: ");
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
            // Se o nome corresponder, permita ao usu�rio modificar as caracter�sticas
            do {
                printf("\t============= Status Atual do Local =============\n");
                exibirLocal(&localLido);
                printf("\n\t============= O que deseja atualizar =======\n");
                printf("\t\t1. Nome\n");
                printf("\t\t2. Endere�o\n");
                printf("\t\t3. Valor de Loca��o\n");
                printf("\t\t4. Descri��o do Ambiente\n");
                printf("\t\t5. Lota��o M�xima\n");
                printf("\t\t6. Telefone\n");
                printf("\t\t7. Voltar\n");
                printf("\n\t===========================================\n");
                printf("\tDigite a op��o escolhida: ");
                escolha = validarEntradaInt();

                switch (escolha) {
                    case 1:
                        printf("\t\t Novo Nome: ");
                        lerString(localLido.nome, MAX_TAMANHO);
                        limparConsole();
                        break;
                    case 2:
                        printf("\t\tNovo Endere�o: ");
                        lerString(localLido.endereco, MAX_TAMANHO);
                        limparConsole();
                        break;
                    case 3:
                        printf("\t\tNovo Valor de Loca��o: ");
                        localLido.valorLocacao = validarEntradaDouble();
                        limparConsole();
                        break;
                    case 4:
                        printf("\t\tNova Descri��o do Ambiente: ");
                        lerString(localLido.descricaoAmbiente, MAX_DESCRICAO);
                        limparConsole();
                        break;
                    case 5:
                        printf("\t\tNova Lota��o M�xima: ");
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
                        printf("\n\t\tOp��o inv�lida! Tente novamente.\n");
                        sleep(2);
                        break;
                }
            } while (escolha != 7);
            encontrado = 1;
        }

        // Escreva no arquivo tempor�rio
        fprintf(arquivoTemp, "%s;%s;%.2f;%s;%s;%d\n", localLido.nome, localLido.endereco,
                localLido.valorLocacao, localLido.descricaoAmbiente,localLido.telefone, localLido.lotacaoMaxima);
    }

    fclose(arquivoEntrada);
    fclose(arquivoTemp);

    // Remover o arquivo original
    remove("Locais.txt");

    // Renomear o arquivo tempor�rio para o original
    rename("temp.txt", "Locais.txt");

    if (encontrado) {
        printf("Local modificado com sucesso!\n");
        sleep(2);
    } else {
        printf("Local n�o encontrado.\n");
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
            // Escrever no arquivo tempor�rio apenas se n�o for o local a ser exclu�do
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

    // Renomear o arquivo tempor�rio para o original
    rename("temp.txt", "Locais.txt");

    printf("Local exclu�do com sucesso!\n");
}
void exibirLocalDoArquivo(){
    FILE *arquivo = fopen("Locais.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Local localLido;
    int pageSize = 3; // N�mero de locais por p�gina
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
            break; // Se chegamos ao final do arquivo, sa�mos do loop externo
        }

        pausar();

        printf("\n\tPressione '\e[0;32mn\e[m' para avan�ar, '\e[0;33mp\e[m' para retroceder, ou '\e[1;91mq\e[m' para sair...\n\t\t");
        char input = getchar();
        while (getchar() != '\n');

        if (input == 'q' || input == 'Q') {
            break; // Sair do loop se o usu�rio digitar 'q' ou 'Q'
        } else if (input == 'n' || input == 'N') {
            // Avan�ar para a pr�xima p�gina
            limparConsole();
            pagina++;
            contador = 0;
        } else if (input == 'p' || input == 'P' && pagina > 1) {
            // Retroceder para a p�gina anterior
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
    printf("\t\tEndere�o:\e[0;36m %s\e[m\n", local->endereco);
    printf("\t\tValor de Loca��o:\e[0;36mR$ %.2f\e[m\n", local->valorLocacao);
    printf("\t\tDescri��o do Ambiente: \e[0;36m%s\e[m\n", local->descricaoAmbiente);
     printf("\t\tTelefone: \e[0;36m%s\e[m\n", local->telefone);
    printf("\t\tLota��o M�xima:\e[0;36m%d pessoas\e[m\n", local->lotacaoMaxima);
    printf("\t=============================================\n");
}

//FUN��O CRUD FUNCIONARIO
void criarFuncionario(){
    Funcionario novoFuncionario;
    limparConsole();
    printf(GREEN"\n\t========= Cadastro de Funcio�rio -  Debroi Eventos ==========\n"RESET);
    do {
        printf("\t\tNome do Funcion�rio: ");
        lerString(novoFuncionario.nome, MAX_TAMANHO);

        printf("\t\tCPF do Funcion�rio: ");
        lerCPFValidado(novoFuncionario.cpf, MAX_TAMANHO);

        printf("\t\tFun��o do Funcion�rio: ");
        lerFuncaoValidada(novoFuncionario.funcao, MAX_TAMANHO);

        printf("\t\tSal�rio por Hora do Funcion�rio: ");
        novoFuncionario.salarioHora = validarEntradaDouble();

        printf("\t\tEmail do Funcion�rio ");
        lerEmailValidado(novoFuncionario.email,MAX_EMAIL);

        printf("\t\tTelefone do Funcion�rio ");
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

            char salarioString[20];  // Ajuste: Use uma string tempor�ria para o sal�rio
            int leituras = sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d\n", funcionarioLido.nome, funcionarioLido.cpf,
                                  funcionarioLido.funcao, salarioString, funcionarioLido.email, funcionarioLido.telefone,
                                  &funcionarioLido.disponibilidade);

            if (leituras != 7) {
                printf("Erro ao ler os dados do funcion�rio. Linha ignorada.\n");
                continue;
            }

            // Converta a string do sal�rio para um double
            if (sscanf(salarioString, "%lf", &funcionarioLido.salarioHora) != 1) {
                printf("Erro ao converter o sal�rio para n�mero. Linha ignorada.\n");
                continue;
            }

//    while (fscanf(arquivoEntrada, "%[^;];%[^;];%[^;];%lf;%[^;];%[^;];%d\n",
//                  funcionario.nome, funcionario.cpf, funcionario.funcao,
//                  funcionario.salarioHora, funcionario.email,funcionario.telefone,
//                  &funcionario.disponibilidade) != EOF) {

        if (strcmp(funcionarioLido.nome, nomeModificar) == 0) {
            // Se o nome corresponder, permita ao usu�rio modificar as caracter�sticas
             do{
                    printf("\t============= Status Atual Funcin�rio =============\n");
                    exibirFuncionario(&funcionarioLido);
                    printf("\n\t============= O que deseja atualizar =======\n");
                    printf("\t\t1. Nome\n");
                    printf("\t\t2. CPF\n");
                    printf("\t\t3. Fun��o\n");
                    printf("\t\t4. Sal�rio por Hora\n");
                    printf("\t\t5. Email\n");
                    printf("\t\t6. Telefone\n");
                    printf("\t\t7. Disponibilidade\n");
                    printf("\t\t8. Voltar\n");
                    printf("\n\t===========================================\n");
                    printf("\tDigite a op��o escolhida: ");
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
                printf("\t\tNova Fun��o: ");
                lerFuncaoValidada(funcionarioLido.funcao,200);
                limparConsole();

                break;
            case 4:
                printf("\t\tNovo Sal�rio por Hora: ");
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
                printf("\n\t\tOp��o inv�lida! Tente novamente.\n");
                sleep(2);
                break;
 } } while (escolha != 8);
            encontrado = 1;
        }

        // Escreva no arquivo tempor�rio
        fprintf(arquivoTemp, "%s;%s;%s;%.2lf;%s;%s;%d\n", funcionarioLido.nome, funcionarioLido.cpf,
                funcionarioLido.funcao,funcionarioLido.salarioHora,
                funcionarioLido.email,funcionarioLido.telefone,funcionarioLido.disponibilidade);
    }

    fclose(arquivoEntrada);
    fclose(arquivoTemp);

    // Remover o arquivo original
    remove("Funcionarios.txt");

    // Renomear o arquivo tempor�rio para o original
    rename("temp.txt", "Funcionarios.txt");

    if (encontrado) {
        printf("Funcionario modificado com sucesso!\n");
        sleep(2);
    } else {
        printf("Funcionario n�o encontrado.\n");
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
            exibirFuncionario(&funcionario); // Exibir detalhes do funcion�rio antes de excluir

            if (!confirmarExclusao()) {
                fclose(arquivoEntrada);
                fclose(arquivoTemp);
                printf("Exclusao cancelada.\n");
                return;
            }
        } else {
            // Escrever no arquivo tempor�rio apenas se n�o for o funcion�rio a ser exclu�do
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

    // Renomear o arquivo tempor�rio para o original
    rename("temp.txt", "Funcionarios.txt");

    printf("Funcionario exclu�do com sucesso!\n");
}
void exibirFuncionarioDoArquivo(){
    FILE *arquivo = fopen("Funcionarios.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Funcionario funcionarioLido;
    int pageSize = 3; // N�mero de card�pios por p�gina
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

            char salarioString[20];  // Ajuste: Use uma string tempor�ria para o sal�rio
            int leituras = sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d\n", funcionarioLido.nome, funcionarioLido.cpf,
                                  funcionarioLido.funcao, salarioString, funcionarioLido.email, funcionarioLido.telefone,
                                  &funcionarioLido.disponibilidade);

            if (leituras != 7) {
                printf("Erro ao ler os dados do funcion�rio. Linha ignorada.\n");
                continue;
            }

            // Converta a string do sal�rio para um double
            if (sscanf(salarioString, "%lf", &funcionarioLido.salarioHora) != 1) {
                printf("Erro ao converter o sal�rio para n�mero. Linha ignorada.\n");
                continue;
            }

        //    printf("Valores lidos: Nome: %s, CPF: %s, Fun��o: %s, Sal�rio: %.2lf, Email: %s, Telefone: %s, Disponibilidade: %d\n",
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
            break; // Se chegamos ao final do arquivo, sa�mos do loop externo
        }

        pausar();

        printf("\n\tPressione '\e[0;32mn\e[m' para avan�ar, '\e[0;33mp\e[m' para retroceder, ou '\e[1;91mq\e[m' para sair...\n\t\t");
        char input = getchar();
        while (getchar() != '\n');

        if (input == 'q' || input == 'Q') {
            break; // Sair do loop se o usu�rio digitar 'q' ou 'Q'
        } else if (input == 'n' || input == 'N') {
            // Avan�ar para a pr�xima p�gina
            limparConsole();
            pagina++;
            contador = 0;
        } else if (input == 'p' || input == 'P' && pagina > 1) {
            // Retroceder para a p�gina anterior
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
    printf("\t\tFun��o:\e[0;36m %s\e[m\n", funcionario->funcao);
    printf("\t\tSal�rio por hora:\e[0;36m %.2lf\e[m\n", funcionario->salarioHora);
    printf("\t\tEmail:\e[0;36m %s\e[m\n", funcionario->email);
    printf("\t\tTelefone:\e[0;36m %s\e[m\n", funcionario->telefone);
    printf("\t\tDisponibilidade:\e[0;36m  %s\e[m\n", funcionario->disponibilidade ? "\e[0;32mAtivo\e[m" : "\e[1;91mInativo\e[m");
    printf("\t=============================================\n");
}

//FUN��O CRUD USUARIO
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
            // Se o nome corresponder, permita ao usu�rio modificar as caracter�sticas
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
                    printf("\tDigite a op��o escolhida: ");
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
                printf("\n\t\tOp��o inv�lida! Tente novamente.\n");
                sleep(2);
                break;
 } } while (escolha != 7);
            encontrado = 1;
        }

        // Escreva no arquivo tempor�rio
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

    // Renomear o arquivo tempor�rio para o original
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

        // Verificar se a linha n�o est� em branco
        if (usuario.login[0] != '\0') {
            if (strcmp(usuario.login, loginExcluir) == 0) {
                encontrado = 1;
                exibirUsuarios(&usuario); // Exibir detalhes do usu�rio antes de excluir

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

                // Escrever no arquivo tempor�rio apenas se n�o for o usu�rio a ser exclu�do
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
        remove("temp2.txt");// Se n�o foi encontrado, remover o arquivo tempor�rio
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

        printf("\n\tPressione '\e[0;32mn\e[m' para avan�ar, '\e[0;33mp\e[m' para retroceder, ou '\e[1;91mq\e[m' para sair...\n\t\t");
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

//FUN��ES PARA LER ENTRADAS COM VALIDA��O

int validandoAnoBissexto(int ano){

    return (ano % 400 == 0) || ((ano % 100 != 0) && (ano % 4 == 0));

}
int validandoData(int dia, int mes, int ano){
    // Verifique o m�s
    if(mes < 1 || mes > 12){
        return 0; // M�s inv�lido
    }

    // Verifique o dia
    if(dia < 1){
        return 0; // Dia inv�lido
    }

    if(mes == 2){
        // Fevereiro: Verifique se � bissexto
        if(validandoAnoBissexto(ano)){
            if(dia > 29){
                return 0; // Dia inv�lido para um ano bissexto
            }
        }
        else{
            if(dia > 28){
                return 0; // Dia inv�lido para um ano n�o bissexto
            }
        }
    }
    else if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
        // Meses com 30 dias
        if(dia > 30){
            return 0; // Dia inv�lido
        }
    }
    else{
        // Meses com 31 dias
        if(dia > 31){
            return 0; // Dia inv�lido
        }
    }

    return 1; // Data v�lida
}
void lerString(char *destino, int tamanho){
    // Obt�m a posi��o inicial do cursor
    struct CursorPos posInicial = pegarCursorPos();

    do {
        fflush(stdin);
        fgets(destino, tamanho, stdin);

        // Limpa o buffer de entrada
        if (destino[0] != '\0' && destino[0] != '\n') {
            destino[strcspn(destino, "\n")] = '\0';
        }

        // Verifica se a entrada est� vazia
        if (destino[0] == '\0' || (destino[0] == '\n' && destino[1] == '\0')) {

            // Aguarda 2 segundos antes de apagar a mensagem
            apagarMensagemAposTempo(2,"Entrada inv�lida. Por favor, tente novamente.");

            // Move o cursor para a posi��o inicial e limpa a mensagem de erro
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

        // Remove caracteres n�o num�ricos
        int j = 0;
        for (int i = 0; cpf[i] != '\0'; i++) {
            if (isdigit(cpf[i])) {
                cpf[j++] = cpf[i];
            }
        }
        cpf[j] = '\0';

        if (!validarCPF(cpf)) {
            apagarMensagemAposTempo(2, "CPF inv�lido. Por favor, tente novamente.");
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

        // Adicione qualquer l�gica adicional de valida��o necess�ria para a fun��o

        if (strlen(funcao) == 0) {
            apagarMensagemAposTempo(2, "Fun��o inv�lida. Por favor, tente novamente.");
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
            apagarMensagemAposTempo(2, "E-mail inv�lido. Por favor, tente novamente.");
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
        printf("Digite um n�mero de telefone (no formato XX XXXXX-XXXX): ");
        fgets(telefone, tamanhoMaximo, stdin);

        if (telefone[0] != '\0' && telefone[0] != '\n') {
            telefone[strcspn(telefone, "\n")] = '\0';
        }

        if (validarTelefone(telefone)) {
            apagarMensagemAposTempo(2, "N�mero de telefone inv�lido. Por favor, tente novamente.");
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
    scanf(" %c", &resposta);  // Adicionamos um espa�o antes do %c para consumir a nova linha pendente
    limparBuffer(); // Limpar o buffer para evitar problemas de leitura posterior

    return (resposta == 'S' || resposta == 's');
}
int confirmarContinuacao(){
    char resposta;
    printf("Deseja continuar o realizando este tipo de opera��o? (S/N): ");
    scanf(" %c", &resposta);  // Adicionamos um espa�o antes do %c para consumir a nova linha pendente
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
            // Verifica se a entrada n�o � um n�mero
            if (scanf("%*s") == 0) {
                apagarMensagemAposTempo(2, "\n\t      Por favor, insira um valor v�lido (n�mero inteiro).");
                Sleep(1);

                // Move o cursor para a posi��o inicial e limpa a mensagem de erro
                moveCursorParaPosicao(posInicial);
            } else {
                break;
            }
        }
    } while (1);

    return valor;  // Retorno adicional, caso deseje continuar com a entrada inv�lida
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
            // Verifica se a entrada n�o � um n�mero
            if (scanf("%*s") == 0) {
                apagarMensagemAposTempo(2, "Por favor, insira um valor v�lido (n�mero real).");
                Sleep(2);

                // Move o cursor para a posi��o inicial e limpa a mensagem de erro
                moveCursorParaPosicao(posInicial);
            } else {
                break;
            }
        }
    } while (1);

    return valor;  // Retorno adicional, caso deseje continuar com a entrada inv�lida
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

    // Remove caracteres n�o num�ricos
    for (i = j = 0; cpf[i] != '\0'; i++) {
        if (isdigit(cpf[i])) {
            digitos[j++] = cpf[i];
        }
    }

    if (j != 11) {
        return 0; // CPF deve ter 11 d�gitos
    }

    // Verifica se todos os d�gitos s�o iguais
    for (i = 1; i < 11; i++) {
        if (digitos[i] != digitos[0]) {
            break;
        }
    }

    if (i == 11) {
        return 0; // Todos os d�gitos s�o iguais
    }

    // Calcula o primeiro d�gito verificador
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
        return 0; // Primeiro d�gito verificador incorreto
    }

    // Calcula o segundo d�gito verificador
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
        return 0; // Segundo d�gito verificador incorreto
    }

    return 1; // CPF v�lido
}
//fUN��O PAUSAR
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

// Fun��o para mover o cursor para uma posi��o espec�fica
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SENHA_PADRAO "money"
void limparTela();
int main() {
char BancoNome[] = "O_BANCO";
    char senhaDigitada[20];
    int opcao;
    

    do {
        limparTela();
        printf("Digite a senha: ");
        scanf("%s", senhaDigitada);

        if (strcmp(senhaDigitada, SENHA_PADRAO) != 0) {
            printf("Senha incorreta! Tente novamente.\n");
            printf("Pressione Enter para continuar...");
            getchar();
            getchar();
        }
    } while (strcmp(senhaDigitada, SENHA_PADRAO) != 0);

    while (1) {
        limparTela();

        printf("%s\n", BancoNome);
        printf("\n------------ MENU ------------\n");8
        printf("1 - Criar nova Conta\n");
        printf("2 - Depositar e sacar dinheiro em uma nova conta\n");
        printf("3 - Mostrar saldo total de cada conta\n");
        printf("4 - Editar informacoes do titular de uma conta\n");
        printf("5 - Remover conta\n");
        printf("6 - Transferir valor de uma conta para outra\n");
        printf("7 - Salvar dados de uma conta em um arquivo\n");
        printf("8 - SAIR\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("1 - COLOQUE SUA FUNCAO\n");
                break;
            case 2:
                printf("2 - COLOQUE SUA FUNCAO\n");
                break;
            case 3:
                printf("3 - COLOQUE SUA FUNCAO\n");
                break;
             case 4:
                printf("4 - COLOQUE SUA FUNCAO\n");
                break;
             case 5:
                printf("5 - COLOQUE SUA FUNCAO\n");
                break;
            case 6:
                printf("6 - COLOQUE SUA FUNCAO\n");
                break;
            case 7:
                printf("7 - COLOQUE SUA FUNCAO\n");
                break;
            case 8:
                printf("Fim da operacao %s\n", BancoNome);
                exit(0);
            default:
                printf("Opcao incorreta. Pressione Enter para continuar...");
                getchar();  
                getchar();  
                break;
        }
    }



    return 0;

}
void limparTela() {
    system("cls");
}

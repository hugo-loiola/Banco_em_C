#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define SENHA_PADRAO "money"
#define MAX_CONTAS 10 // MÃ¡ximo de contas

// Estrutura para representar uma conta bancÃ¡ria
typedef struct
{
    int numero_conta;
    char nome_titular[50];
    double saldo;
} ContaBancaria;

ContaBancaria **contas;

// FunÃ§Ã£o para criar uma nova conta bancÃ¡ria
ContaBancaria *criarConta()
{
    // Alocar memÃ³ria para a estrutura da conta
    ContaBancaria *nova_conta = (ContaBancaria *)malloc(sizeof(ContaBancaria));

    // Verificar se a alocaÃ§Ã£o foi bem-sucedida
    if (nova_conta == NULL)
    {
        fprintf(stderr, "Erro ao alocar memoria para a conta bancaria\n");
        exit(EXIT_FAILURE);
    }

    // Solicitar informaÃÂ§ÃÂµes ao usuÃÂ¡rio
    printf("Digite o nÃºmero da conta: ");
    scanf("%d", &nova_conta->numero_conta);

    printf("Digite o nome do titular: ");
    scanf("%s", nova_conta->nome_titular);

    printf("Digite o saldo inicial: ");
    scanf("%lf", &nova_conta->saldo);

    // Retornar o ponteiro para a nova conta
    return nova_conta;
}

// FunÃ§Ã£o para mostrar o saldo total de todas as contas

// No seu switch-case, vocÃª pode chamar essa funÃÂ§ÃÂ£o quando o usuÃÂ¡rio escolher a opÃ§Ã£o 3

void mostrarSaldoTotal()
{
    double saldoTotal = 0.0;

    // Iterar sobre todas as contas e somar os saldos
    for (int i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
    {
        printf("Conta: %d saldo: %.2lf\n", contas[i]->numero_conta, contas[i]->saldo);
    }

    // Exibir o saldo total
    printf("Saldo total de todas as contas: %.2lf\n", saldoTotal);
}

void listarContas()
{
    printf("\n------------ LISTA DE CONTAS ------------\n");
    for (int i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
    {
        printf("Conta: %d\n", contas[i]->numero_conta);
        printf("Titular: %s\n", contas[i]->nome_titular);
        printf("Saldo: %.2lf\n", contas[i]->saldo);
        printf("-----------------------------\n");
    }
}

// FunÃ§Ã£o para depositar em uma conta
void depositar()
{
    int numeroConta;
    double valor;

    printf("Digite o nÃºmero da conta para DepÃ³sito: ");
    scanf("%d", &numeroConta);

    // Procurar a conta pelo nÃºmero
    int i;
    for (i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
    {
        if (contas[i]->numero_conta == numeroConta)
        {
            printf("Digite o valor a ser depositado: ");
            scanf("%lf", &valor);

            // Validar o valor do DepÃ³sito
            if (valor > 0)
            {
                contas[i]->saldo += valor;
                printf("DepÃ³sito realizado com sucesso!\n");
            }
            else
            {
                printf("Valor de depÃ³sito invÃ¡lido. O valor deve ser maior que zero.\n");
            }

            return; // Sair da funÃÂ§ÃÂ£o depois de realizar o DepÃ³sito
        }
    }

    // Se a conta nÃÂ£o for encontrada
    printf("Conta nÃÂ£o encontrada. Verifique o nÃºmero da conta e tente novamente.\n");
}

// FunÃ§Ã£o para sacar de uma conta
void sacar()
{
    int numeroConta;
    double valor;

    printf("Digite o nÃºmero da conta para saque: ");
    scanf("%d", &numeroConta);

    // Procurar a conta pelo nÃºmero
    int i;
    for (i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
    {
        if (contas[i]->numero_conta == numeroConta)
        {
            printf("Digite o valor a ser sacado: ");
            scanf("%lf", &valor);

            // Validar o valor do saque
            if (valor > 0 && valor <= contas[i]->saldo)
            {
                contas[i]->saldo -= valor;
                printf("Saque realizado com sucesso!\n");
            }
            else if (valor <= 0)
            {
                printf("Valor de saque invÃ¡lido. O valor deve ser maior que zero.\n");
            }
            else
            {
                printf("Saldo insuficiente para realizar o saque.\n");
            }

            return; // Sair da funÃ§Ã£o depois de realizar o saque
        }
    }

    // Se a conta nÃ£o for encontrada
    printf("Conta nÃÂ£o encontrada. Verifique o nÃºmero da conta e tente novamente.\n");
}

// FunÃ§Ã£o para exibir um menu de operaÃÂ§ÃÂµes em uma conta (DepÃ³sito ou saque)
void depositarSacar()
{
    int escolha;
    printf("\n------------ MENU DE OPERAÃÃES EM CONTA ------------\n");
    printf("1 - DepÃ³sito\n");
    printf("2 - Saque\n");
    printf("Escolha uma opÃÂ§ÃÂ£o: ");
    scanf("%d", &escolha);

    switch (escolha)
    {
    case 1:
        depositar();
        break;
    case 2:
        sacar();
        break;
    default:
        printf("OpÃ§Ã£o invÃ¡lida.\n");
    }
}

void trasnferirValor()
{
    double valor;
    int numeroConta, numeroConta2;

    printf("Digite o nÃºmero da conta remetente: ");
    scanf("%d", &numeroConta);
    for (int i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
    {
        if (contas[i]->numero_conta == numeroConta)
        {
            printf("Digite o valor da TransferÃªncia: \n");
            scanf("%lf", &valor);

            // Validar o valor da transferência
            if (valor > 0 && valor <= contas[i]->saldo)
            {
                contas[i]->saldo -= valor;
                printf("TransaÃ§Ã£o em andamento, aguarde!\n");
            }
            else if (valor <= 0)
            {
                printf("Valor de saque invÃ¡lido. O valor deve ser maior que zero.\n");
            }
            else
            {
                printf("Saldo insuficiente para realizar a TransferÃªncia.\n");
            }
        }
    }

    printf("Digite o nÃºmero da conta do destinatÃ¡rio: ");
    scanf("%d", &numeroConta2);
    for (int i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
    {
        if (contas[i]->numero_conta == numeroConta2)
        {
            printf("Valor a ser recebido: %.2lf\n", valor);

            // Validar o valor da transferência recebida pelo destinatário
            if (valor > 0)
            {
                contas[i]->saldo += valor;
                printf("Saldo creditado!\n");
            }
            else
            {
                printf("Erro no valor de TransferÃªncia. O valor deve ser maior que zero.\n");
            }

            return printf("----------Transferencia Realizada com Sucesso----------\n");
            // Sair da função depois da transferência ser concluída
        }
    }

    // Se a conta nÃÂ£o for encontrada
    printf("Conta nÃÂ£o encontrada. Verifique o nÃºmero da conta e tente novamente.\n");
}

int main()
{
    char BancoNome[] = "BANCO MASSA DE MAIS VEI";
    char senhaDigitada[20];
    int opcao;
    setlocale(LC_ALL, "Portuguese");

    contas = (ContaBancaria **)malloc(MAX_CONTAS * sizeof(ContaBancaria *));
    if (contas == NULL)
    {
        fprintf(stderr, "Erro ao alocar memoria para o vetor de contas\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_CONTAS; i++)
    {
        contas[i] = NULL;
    }

    do
    {

        printf("Digite a senha para acessar o sistema do banco: ");
        scanf("%s", senhaDigitada);

        if (strcmp(senhaDigitada, SENHA_PADRAO) != 0)
        {
            printf("Senha incorreta! Tente novamente.\n");
            printf("Pressione Enter para continuar...");
            getchar();
            getchar();
        }
    } while (strcmp(senhaDigitada, SENHA_PADRAO) != 0);

    while (1)
    {

        printf("%s\n", BancoNome);
        printf("\n------------ MENU ------------\n");
        printf("1 - Criar nova Conta\n");
        printf("2 - Depositar e sacar dinheiro em uma nova conta\n");
        printf("3 - Mostrar saldo total de cada conta\n");
        printf("4 - Editar informacoes do titular de uma conta\n");
        printf("5 - Remover conta\n");
        printf("6 - Transferir valor de uma conta para outra\n");
        printf("7 - Salvar dados de uma conta em um arquivo\n");
        printf("8 - SAIR\n");
        printf("\nEscolha uma opÃ§Ã£o: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:;
            // Exibir informaÃ§Ãµes da conta
            ContaBancaria *minha_conta = criarConta();

            // Encontrar um espaÃ§o vazio no array
            int i;
            for (i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
            {
            }

            // Checar se o nÃºmero de contas
            if (i < MAX_CONTAS)
            {
                contas[i] = minha_conta;
                printf("Conta criada com sucesso!\n");
            }
            else
            {
                printf("Limite de contas atingido. Nao eh possivel criar mais contas.\n");

                free(minha_conta); // Liberar memÃ³ria, se possÃÂ­vel
            }
            break;
        case 2:
            depositarSacar();
            break;
        case 3:
            mostrarSaldoTotal();
            break;

        case 4:
            printf("4 - COLOQUE SUA FUNCAO\n");
            break;
        case 5:
            printf("5 - COLOQUE SUA FUNCAO\n");
            break;
        case 6:
            trasnferirValor();
            break;
        case 7:
            printf("7 - COLOQUE SUA FUNCAO\n");
            break;
        case 8:
            printf("Fim da operaÃ§Ã£o %s\n", BancoNome);

            for (int i = 0; i < MAX_CONTAS; i++)
            {
                free(contas[i]);
            }

            return 0;
        case 9:;
            listarContas();
            break;
            // Liberar memoria quando o cÃ³digo terminar
            free(contas);

            exit(0);
        default:
            printf("OpÃ§Ã£o incorreta. Pressione Enter para continuar...");
            getchar();
            getchar();
            break;
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define SENHA_PADRAO "money"#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define SENHA_PADRAO "money"
#define MAX_CONTAS 10 // Máximo de contas

// Estrutura para representar uma conta bancária
typedef struct
{
    int numero_conta;
    char nome_titular[50];
    double saldo;
} ContaBancaria;

ContaBancaria **contas;

// Função para criar uma nova conta bancária
ContaBancaria *criarConta()
{
    // Alocar memória para a estrutura da conta
    ContaBancaria *nova_conta = (ContaBancaria *)malloc(sizeof(ContaBancaria));

    // Verificar se a alocação foi bem-sucedida
    if (nova_conta == NULL)
    {
        fprintf(stderr, "Erro ao alocar memoria para a conta bancaria\n");
        exit(EXIT_FAILURE);
    }

    // Solicitar informações ao usuário
    printf("Digite o número da conta: ");
    scanf("%d", &nova_conta->numero_conta);

    printf("Digite o nome do titular: ");
    scanf("%s", nova_conta->nome_titular);

    printf("Digite o saldo inicial: ");
    scanf("%lf", &nova_conta->saldo);

    // Retornar o ponteiro para a nova conta
    return nova_conta;
}

// Função para mostrar o saldo total de todas as contas

// No seu switch-case, você pode chamar essa função quando o usuário escolher a opção 3

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

// Função para depositar em uma conta
void depositar()
{
    int numeroConta;
    double valor;

    printf("Digite o número da conta para depósito: ");
    scanf("%d", &numeroConta);

    // Procurar a conta pelo número
    int i;
    for (i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
    {
        if (contas[i]->numero_conta == numeroConta)
        {
            printf("Digite o valor a ser depositado: ");
            scanf("%lf", &valor);

            // Validar o valor do depósito
            if (valor > 0)
            {
                contas[i]->saldo += valor;
                printf("Depósito realizado com sucesso!\n");
            }
            else
            {
                printf("Valor de depósito inválido. O valor deve ser maior que zero.\n");
            }

            return; // Sair da função depois de realizar o depósito
        }
    }

    // Se a conta não for encontrada
    printf("Conta não encontrada. Verifique o número da conta e tente novamente.\n");
}

// Função para sacar de uma conta
void sacar()
{
    int numeroConta;
    double valor;

    printf("Digite o número da conta para saque: ");
    scanf("%d", &numeroConta);

    // Procurar a conta pelo número
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
                printf("Valor de saque inválido. O valor deve ser maior que zero.\n");
            }
            else
            {
                printf("Saldo insuficiente para realizar o saque.\n");
            }

            return; // Sair da função depois de realizar o saque
        }
    }

    // Se a conta não for encontrada
    printf("Conta não encontrada. Verifique o número da conta e tente novamente.\n");
}

// Função para exibir um menu de operações em uma conta (depósito ou saque)
void depositarSacar()
{
    int escolha;
    printf("\n------------ MENU DE OPERAÇÕES EM CONTA ------------\n");
    printf("1 - Depósito\n");
    printf("2 - Saque\n");
    printf("Escolha uma opção: ");
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
        printf("Opção inválida.\n");
    }
}

void trasnferirValor()
{
    sacar();
    depositar();
    printf("----------Transferencia Realizada com Sucesso----------\n");
}

int main()
{
    char BancoNome[] = "BANCO MASSA DE MAIS VEI";
    char senhaDigitada[20];
    int opcao;
    setlocale(LC_ALL, "");

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
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:;
            // Exibir informações da conta
            ContaBancaria *minha_conta = criarConta();

            // Encontrar um espaço vazio no array
            int i;
            for (i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
            {
            }

            // Checar se o número de contas
            if (i < MAX_CONTAS)
            {
                contas[i] = minha_conta;
                printf("Conta criada com sucesso!\n");
            }
            else
            {
                printf("Limite de contas atingido. Nao eh possivel criar mais contas.\n");

                free(minha_conta); // Liberar memória, se possível
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
            printf("Fim da operação %s\n", BancoNome);

            for (int i = 0; i < MAX_CONTAS; i++)
            {
                free(contas[i]);
            }
        case 9:;
            listarContas();
            break;
            // Liberar memoria quando o código terminar
            free(contas);

            exit(0);
        default:
            printf("Opçao incorreta. Pressione Enter para continuar...");
            getchar();
            getchar();
            break;
        }
    }

    return 0;
}
#define MAX_CONTAS 10 // Máximo de contas

// Estrutura para representar uma conta bancária
typedef struct
{
  int numero_conta;
  char nome_titular[50];
  double saldo;
} ContaBancaria;

ContaBancaria **contas;

// Função para criar uma nova conta bancária
ContaBancaria *criarConta()
{
  // Alocar memória para a estrutura da conta
  ContaBancaria *nova_conta = (ContaBancaria *)malloc(sizeof(ContaBancaria));

  // Verificar se a alocação foi bem-sucedida
  if (nova_conta == NULL)
  {
    fprintf(stderr, "Erro ao alocar memoria para a conta bancaria\n");
    exit(EXIT_FAILURE);
  }

  // Solicitar informações ao usuário
  printf("Digite o número da conta: ");
  scanf("%d", &nova_conta->numero_conta);

  printf("Digite o nome do titular: ");
  scanf("%s", nova_conta->nome_titular);

  printf("Digite o saldo inicial: ");
  scanf("%lf", &nova_conta->saldo);

  // Retornar o ponteiro para a nova conta
  return nova_conta;
}

// Função para mostrar o saldo total de todas as contas

// No seu switch-case, você pode chamar essa função quando o usuário escolher a opção 3

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



// Função para depositar em uma conta
void depositar()
{
  int numeroConta;
  double valor;

  printf("Digite o número da conta para depósito: ");
  scanf("%d", &numeroConta);

  // Procurar a conta pelo número
  int i;
  for (i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
  {
      if (contas[i]->numero_conta == numeroConta)
      {
          printf("Digite o valor a ser depositado: ");
          scanf("%lf", &valor);

          // Validar o valor do depósito
          if (valor > 0)
          {
              contas[i]->saldo += valor;
              printf("Depósito realizado com sucesso!\n");
          }
          else
          {
              printf("Valor de depósito inválido. O valor deve ser maior que zero.\n");
          }

          return; // Sair da função depois de realizar o depósito
      }
  }

    // Se a conta não for encontrada
    printf("Conta não encontrada. Verifique o número da conta e tente novamente.\n");
}

// Função para sacar de uma conta
void sacar()
{
    int numeroConta;
    double valor;

    printf("Digite o número da conta para saque: ");
    scanf("%d", &numeroConta);

    // Procurar a conta pelo número
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
                printf("Valor de saque inválido. O valor deve ser maior que zero.\n");
            }
            else
            {
                printf("Saldo insuficiente para realizar o saque.\n");
            }

            return; // Sair da função depois de realizar o saque
        }
    }

    // Se a conta não for encontrada
    printf("Conta não encontrada. Verifique o número da conta e tente novamente.\n");
}

// Função para exibir um menu de operações em uma conta (depósito ou saque)
void depositarSacar()
{
    int escolha;
    printf("\n------------ MENU DE OPERAÇÕES EM CONTA ------------\n");
    printf("1 - Depósito\n");
    printf("2 - Saque\n");
    printf("Escolha uma opção: ");
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
        printf("Opção inválida.\n");
    }
}

void transferirvalor(){
    int numeroConta;
    double valor;

    printf("Digite o número da conta para transferir:\n");
    scanf("%d", &numeroConta);

    int i;
    for (i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
    {
        if (contas[i]->numero_conta == numeroConta)
        {
            printf("Digite o valor da transferência: ");
            scanf("%lf", &valor);

            // Validar o valor da transferência
            if (valor > 0 && valor <= contas[i]->saldo)
            {
                contas[i]->saldo -= valor;
                contas[i] 
                printf("Transferência realizada com sucesso!\n");
            }
            else if (valor <= 0)
            {
                printf("Erro no valor de transferência. O valor deve ser maior que zero.\n");
            }
            else
            {
                printf("Saldo insuficiente para realizar a transferência.\n");
            }

            return; // Sair da função depois de realizar a transferência
        }
    }

    // Se a conta não for encontrada
    printf("Conta não encontrada. Verifique o número da conta e tente novamente.\n");
}


int main()
{
  char BancoNome[] = "BANCO MASSA DE MAIS VEI";
  char senhaDigitada[20];
  int opcao;
  setlocale(LC_ALL, "");

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
    printf("\nEscolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:;
      // Exibir informações da conta
      ContaBancaria *minha_conta = criarConta();

      // Encontrar um espaço vazio no array
      int i;
      for (i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
      {
      }

      // Checar se o número de contas
      if (i < MAX_CONTAS)
      {
        contas[i] = minha_conta;
        printf("Conta criada com sucesso!\n");
      }
      else
      {
        printf("Limite de contas atingido. Nao eh possivel criar mais contas.\n");

        free(minha_conta); // Liberar memória, se possível
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
      transferirvalor();
      break;
    case 7:
      printf("7 - COLOQUE SUA FUNCAO\n");
      break;
    case 8:
      printf("Fim da operação %s\n", BancoNome);

      for (int i = 0; i < MAX_CONTAS; i++)
      {
        free(contas[i]);
      }
    case 9: ;
      listarContas();
      break;
      // Liberar memoria quando o código terminar
      free(contas);

      exit(0);
    default:
      printf("Opçao incorreta. Pressione Enter para continuar...");
      getchar();
      getchar();
      break;
    }
  }

  return 0;
}

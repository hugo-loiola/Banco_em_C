#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define SENHA_PADRAO "money"
#define MAX_CONTAS 10 // Máximo de contas

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

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
  printf("Digite o numero da conta: ");
  scanf("%d", &nova_conta->numero_conta);

  printf("Digite o nome do titular: ");
  clean_stdin();
  fgets(nova_conta->nome_titular, 30,stdin);
  nova_conta->nome_titular[strcspn(nova_conta->nome_titular, "\n")] = 0;

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
  for (int i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
  {
    saldoTotal += contas[i]->saldo;
  }

// Exibir o saldo total
  printf("Saldo total de todas as contas: %.2lf\n", saldoTotal);
}

// Função para editar informações do titular de uma conta
void editarInformacoes(ContaBancaria *conta)
{
    // Solicitar novas informações ao usuário
    printf("Digite o novo nome do titular: ");
    scanf("%s", conta->nome_titular);

    printf("Digite o novo saldo: ");
    scanf("%lf", &conta->saldo);

    printf("Informacoes da conta atualizadas com sucesso!\n");
}

// Função para encontrar uma conta pelo número
ContaBancaria *encontrarConta(int numeroConta)
{
    for (int i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
    {
        if (contas[i]->numero_conta == numeroConta)
        {
            return contas[i];
        }
    }
    return NULL; // Retorna NULL se a conta não for encontrada
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

  printf("Digite o numero da conta para depósito: ");
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
              printf("Deposito realizado com sucesso!\n");
          }
          else
          {
              printf("Valor de deposito invalido. O valor deve ser maior que zero.\n");
          }

          return; // Sair da função depois de realizar o depósito
      }
  }

    // Se a conta não for encontrada
    printf("Conta nao encontrada. Verifique o numero da conta e tente novamente.\n");
}

// Função para sacar de uma conta
void sacar()
{
    int numeroConta;
    double valor;

    printf("Digite o numero da conta para saque: ");
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
                printf("Valor de saque invalido. O valor deve ser maior que zero.\n");
            }
            else
            {
                printf("Saldo insuficiente para realizar o saque.\n");
            }

            return; // Sair da função depois de realizar o saque
        }
    }

    // Se a conta não for encontrada
    printf("Conta nao encontrada. Verifique o numero da conta e tente novamente.\n");
}

// Função para exibir um menu de operações em uma conta (depósito ou saque)
void depositarSacar()

{
    int escolha;
    printf("\n------------ MENU DE OPERAÇÕES EM CONTA ------------\n");
    printf("1 - Deposito\n");
    printf("2 - Saque\n");
    printf("Escolha uma opcao: ");
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
        printf("Opção invalida.\n");
    }
}

// Função para remover uma conta bancária
void removerConta(int numeroConta)
{
  // Procurar a conta com o número especificado
  for (int i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
  {
    if (contas[i]->numero_conta == numeroConta)
    {
      // Encontrou a conta, liberar memória e remover
      free(contas[i]);
      contas[i] = NULL;
      printf("Conta removida com sucesso!\n");
      return;
    }
  }

  // Se chegou aqui, a conta não foi encontrada
  printf("Conta nao encontrada. Verifique o número da conta.\n");
}

// Função para salvar dados das contas em um arquivo
void salvarDados()
{
    FILE *arquivo;
    arquivo = fopen("dados_contas.txt", "w");

    if (arquivo == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
    {
        fprintf(arquivo, "%d %s %.2lf\n", contas[i]->numero_conta, contas[i]->nome_titular, contas[i]->saldo);
    }

    fclose(arquivo);
    printf("Dados das contas salvos no arquivo com sucesso!\n");
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
    printf("\nEscolha uma opcao: ");
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
{
    int numeroContaEditar;
    printf("Digite o numero da conta que deseja editar: ");
    scanf("%d", &numeroContaEditar);

    // Encontrar a conta pelo número
    ContaBancaria *contaParaEditar = encontrarConta(numeroContaEditar);

    if (contaParaEditar != NULL)
    {
        // Chamar a função para editar as informações
        editarInformacoes(contaParaEditar);
    }
    else
    {
        printf("Conta nao encontrada. Verifique o numero da conta e tente novamente.\n");
    }

    break;
}
    case 5: ;
      int numero_conta_remover;
      printf("Digite o numero da conta a ser removida: ");
      scanf("%d", &numero_conta_remover);
      removerConta(numero_conta_remover);

      break;
    case 6:
      printf("6 - COLOQUE SUA FUNCAO\n");
      break;
    case 7:
      salvarDados();
      break;
    case 8:
      printf("FIM da operacao %s\n", BancoNome);

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
      printf("Opcao incorreta. Pressione Enter para continuar...");
      getchar();
      getchar();
      break;
    }
  }

  return 0;
}

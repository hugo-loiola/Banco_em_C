#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTAS 10
#define MAX_TITULAR 50

typedef struct {
    int numeroConta;
    char titular[MAX_TITULAR];
    double saldo;
} ContaBancaria;

ContaBancaria contas[MAX_CONTAS];
int numContas = 0;

void criarConta() {
    if (numContas < MAX_CONTAS) {
        ContaBancaria novaConta;
        printf("Digite o nome do titular da conta: ");
        scanf("%49s", novaConta.titular);
        novaConta.numeroConta = numContas + 1;
        novaConta.saldo = 0.0;
        contas[numContas] = novaConta;
        numContas++;
        printf("Conta criada com sucesso!\n");
    } else {
        printf("Limite máximo de contas atingido.\n");
    }
}

void depositarSacar(int numeroConta, double valor, int tipoOperacao) {
    for (int i = 0; i < numContas; i++) {
        if (contas[i].numeroConta == numeroConta) {
            if (tipoOperacao == 1) {
                contas[i].saldo += valor;
                printf("Depósito realizado com sucesso!\n");
            } else if (tipoOperacao == 2) {
                if (contas[i].saldo >= valor) {
                    contas[i].saldo -= valor;
                    printf("Saque realizado com sucesso!\n");
                } else {
                    printf("Saldo insuficiente para saque.\n");
                }
            }
            return;
        }
    }
    printf("Conta não encontrada.\n");
}

void mostrarSaldo(int numeroConta) {
    for (int i = 0; i < numContas; i++) {
        if (contas[i].numeroConta == numeroConta) {
            printf("Saldo da conta %d (%s): R$ %.2f\n", contas[i].numeroConta, contas[i].titular, contas[i].saldo);
            return;
        }
    }
    printf("Conta não encontrada.\n");
}

void editarTitular(int numeroConta) {
    for (int i = 0; i < numContas; i++) {
        if (contas[i].numeroConta == numeroConta) {
            printf("Digite o novo nome do titular: ");
            scanf("%s", contas[i].titular);
            printf("Nome do titular atualizado com sucesso!\n");
            return;
        }
    }
    printf("Conta não encontrada.\n");
}

void removerConta(int numeroConta) {
    for (int i = 0; i < numContas; i++) {
        if (contas[i].numeroConta == numeroConta) {
            for (int j = i; j < numContas - 1; j++) {
                contas[j] = contas[j + 1];
            }
            numContas--;
            printf("Conta removida com sucesso!\n");
            return;
        }
    }
    printf("Conta não encontrada.\n");
}

void transferirValor(int contaOrigem, int contaDestino, double valor) {
    depositarSacar(contaOrigem, valor, 2);  // Sacar da conta de origem
    depositarSacar(contaDestino, valor, 1); // Depositar na conta de destino
    printf("Transferência realizada com sucesso!\n");
}

void salvarContas() {
    FILE *arquivo = fopen("contas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < numContas; i++) {
        fprintf(arquivo, "%d %s %.2f\n", contas[i].numeroConta, contas[i].titular, contas[i].saldo);
    }

    fclose(arquivo);
    printf("Informações salvas no arquivo 'contas.txt'.\n");
}

int main() {
    int escolha, numeroConta, numeroContaDestino;
    double valor;

    do {
        printf("\n--- Menu ---\n");
        printf("1. Criar nova conta\n");
        printf("2. Depositar dinheiro\n");
        printf("3. Sacar dinheiro\n");
        printf("4. Mostrar saldo\n");
        printf("5. Editar titular\n");
        printf("6. Remover conta\n");
        printf("7. Transferir valor\n");
        printf("8. Salvar contas em arquivo\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                criarConta();
                break;
            case 2:
                printf("Digite o número da conta: ");
                scanf("%d", &numeroConta);
                printf("Digite o valor a depositar: ");
                scanf("%lf", &valor);
                depositarSacar(numeroConta, valor, 1);
                break;
            case 3:
                printf("Digite o número da conta: ");
                scanf("%d", &numeroConta);
                printf("Digite o valor a sacar: ");
                scanf("%lf", &valor);
                depositarSacar(numeroConta, valor, 2);
                break;
            case 4:
                printf("Digite o número da conta: ");
                scanf("%d", &numeroConta);
                mostrarSaldo(numeroConta);
                break;
            case 5:
                printf("Digite o número da conta: ");
                scanf("%d", &numeroConta);
                editarTitular(numeroConta);
                break;
            case 6:
                printf("Digite o número da conta a ser removida: ");
                scanf("%d", &numeroConta);
                removerConta(numeroConta);
                break;
            case 7:
                printf("Digite o número da conta de origem: ");
                scanf("%d", &numeroConta);
                printf("Digite o número da conta de destino: ");
                scanf("%d", &numeroContaDestino);
                printf("Digite o valor a transferir: ");
                scanf("%lf", &valor);
                transferirValor(numeroConta, numeroContaDestino, valor);
                break;
            case 8:
                salvarContas();
                break;
            case 0:
                printf("Saindo do programa. Até logo!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 0);

    return 0;
}

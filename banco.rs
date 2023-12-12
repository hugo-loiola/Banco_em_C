// Pequeno teste em Rust
use std::io::{self, Write};

const SENHA_PADRAO: &str = "money";
const MAX_CONTAS: usize = 10;

struct ContaBancaria {
    numero_conta: i32,
    nome_titular: String,
    saldo: f64,
}

fn criar_conta() -> ContaBancaria {
    print!("Digite o numero da conta: ");
    io::stdout().flush().unwrap();
    let mut numero_conta = String::new();
    io::stdin().read_line(&mut numero_conta).unwrap();
    let numero_conta: i32 = numero_conta.trim().parse().unwrap();

    print!("Digite o nome do titular: ");
    io::stdout().flush().unwrap();
    let mut nome_titular = String::new();
    io::stdin().read_line(&mut nome_titular).unwrap();
    let nome_titular = nome_titular.trim().to_string();

    print!("Digite o saldo inicial: R$ ");
    io::stdout().flush().unwrap();
    let mut saldo = String::new();
    io::stdin().read_line(&mut saldo).unwrap();
    let saldo: f64 = saldo.trim().parse().unwrap();

    ContaBancaria {
        numero_conta,
        nome_titular,
        saldo,
    }
}

fn depositar(contas: &mut Vec<ContaBancaria>) {
    print!("Digite o numero da conta para deposito: ");
    io::stdout().flush().unwrap();
    let mut numero_conta = String::new();
    io::stdin().read_line(&mut numero_conta).unwrap();
    let numero_conta: i32 = numero_conta.trim().parse().unwrap();

    if let Some(conta) = contas.iter_mut().find(|c| c.numero_conta == numero_conta) {
        print!("Digite o valor a ser depositado: R$ ");
        io::stdout().flush().unwrap();
        let mut valor = String::new();
        io::stdin().read_line(&mut valor).unwrap();
        let valor: f64 = valor.trim().parse().unwrap();

        if valor > 0.0 {
            conta.saldo += valor;
            println!("\n----------------------------\nDeposito realizado com sucesso!\n----------------------------\n");
        } else {
            println!("\n----------------------------\nValor de deposito invalido. O valor deve ser maior que zero.\n----------------------------\n");
        }
    } else {
        println!("\n----------------------------\nConta nao encontrada. Verifique o numero da conta e tente novamente.\n----------------------------\n");
    }
}

fn editar_informacoes_titular(contas: &mut Vec<ContaBancaria>) {
    print!("Digite o numero da conta para editar as informacoes do titular: ");
    io::stdout().flush().unwrap();
    let mut numero_conta = String::new();
    io::stdin().read_line(&mut numero_conta).unwrap();
    let numero_conta: i32 = numero_conta.trim().parse().unwrap();

    if let Some(conta) = contas.iter_mut().find(|c| c.numero_conta == numero_conta) {
        print!("Digite o novo nome do titular: ");
        io::stdout().flush().unwrap();
        let mut nome_titular = String::new();
        io::stdin().read_line(&mut nome_titular).unwrap();
        let nome_titular = nome_titular.trim().to_string();

        conta.nome_titular = nome_titular;
        println!("\n----------------------------\nInformacoes do titular editadas com sucesso!\n----------------------------\n");
    } else {
        println!("\n----------------------------\nConta nao encontrada. Verifique o numero da conta e tente novamente.\n----------------------------\n");
    }
}

fn remover_conta(contas: &mut Vec<ContaBancaria>) {
    print!("Digite o numero da conta para remover: ");
    io::stdout().flush().unwrap();
    let mut numero_conta = String::new();
    io::stdin().read_line(&mut numero_conta).unwrap();
    let numero_conta: i32 = numero_conta.trim().parse().unwrap();

    if let Some(_conta) = contas.iter_mut().find(|c| c.numero_conta == numero_conta) {
        contas.remove(
            contas
                .iter()
                .position(|c| c.numero_conta == numero_conta)
                .unwrap(),
        );
        println!("\n----------------------------\nConta removida com sucesso!\n----------------------------\n");
    } else {
        println!("\n----------------------------\nConta nao encontrada. Verifique o numero da conta e tente novamente.\n----------------------------\n");
    }
}

fn transferir_valor(contas: &mut Vec<ContaBancaria>) {
    print!("Digite o numero da conta de origem: ");
    io::stdout().flush().unwrap();
    let mut origem_conta = String::new();
    io::stdin().read_line(&mut origem_conta).unwrap();
    let origem_conta: i32 = origem_conta.trim().parse().unwrap();

    if let Some(origem_index) = contas.iter().position(|c| c.numero_conta == origem_conta) {
        print!("Digite o numero da conta de destino: ");
        io::stdout().flush().unwrap();
        let mut destino_conta = String::new();
        io::stdin().read_line(&mut destino_conta).unwrap();
        let destino_conta: i32 = destino_conta.trim().parse().unwrap();

        if let Some(destino_index) = contas.iter().position(|c| c.numero_conta == destino_conta) {
            print!("Digite o valor a ser transferido: R$ ");
            io::stdout().flush().unwrap();
            let mut valor = String::new();
            io::stdin().read_line(&mut valor).unwrap();
            let valor: f64 = valor.trim().parse().unwrap();

            if valor > 0.0 && valor <= contas[origem_index].saldo {
                contas[origem_index].saldo -= valor;
                contas[destino_index].saldo += valor;

                println!("\n----------------------------\nTransferencia realizada com sucesso!\n----------------------------\n");
            } else if valor <= 0.0 {
                println!("\n----------------------------\nValor de transferencia invalido. O valor deve ser maior que zero.\n----------------------------\n");
            } else {
                println!("\n----------------------------\nSaldo insuficiente para realizar a transferencia.\n----------------------------\n");
            }
        } else {
            println!("\n----------------------------\nConta de destino nao encontrada. Verifique o numero da conta e tente novamente.\n----------------------------\n");
        }
    } else {
        println!("\n----------------------------\nConta de origem nao encontrada. Verifique o numero da conta e tente novamente.\n----------------------------\n");
    }
}

use std::fs::File;

fn salvar_dados(contas: &Vec<ContaBancaria>) {
    print!("Digite o nome do arquivo para salvar os dados: ");
    io::stdout().flush().unwrap();
    let mut nome_arquivo = String::new();
    io::stdin().read_line(&mut nome_arquivo).unwrap();
    let nome_arquivo = nome_arquivo.trim();

    let mut arquivo = match File::create(nome_arquivo) {
        Ok(file) => file,
        Err(_) => {
            println!("\n----------------------------\nErro ao criar o arquivo.\n----------------------------\n");
            return;
        }
    };

    for conta in contas {
        if let Err(_) = writeln!(
            arquivo,
            "N° da conta: {} | Titular: {} | Saldo: R$ {:.2}",
            conta.numero_conta, conta.nome_titular, conta.saldo
        ) {
            println!("\n----------------------------\nErro ao escrever no arquivo.\n----------------------------\n");
            return;
        }
    }

    println!("\n----------------------------\nDados das contas salvos no arquivo com sucesso!\n----------------------------\n");
}

fn main() {
    let mut contas: Vec<ContaBancaria> = Vec::with_capacity(MAX_CONTAS);

    println!("Digite a senha para acessar o sistema do banco: ");
    let mut senha_digitada = String::new();
    io::stdin().read_line(&mut senha_digitada).unwrap();

    if senha_digitada.trim() != SENHA_PADRAO {
        println!("Senha incorreta! Tente novamente.");
        return;
    }

    loop {
        println!("\n------------ MENU ------------");
        println!("1 - Criar nova Conta");
        println!("2 - Depositar dinheiro em uma conta");
        println!("3 - Mostrar saldo total de cada conta");
        println!("4 - Editar informacoes do titular de uma conta");
        println!("5 - Remover conta");
        println!("6 - Transferir valor de uma conta para outra");
        println!("7 - Salvar dados de uma conta em um arquivo");
        println!("8 - SAIR");
        print!("\nEscolha uma opcao: ");
        io::stdout().flush().unwrap();
        let mut opcao = String::new();
        io::stdin().read_line(&mut opcao).unwrap();
        let opcao: u32 = opcao.trim().parse().unwrap();

        match opcao {
            1 => {
                let nova_conta = criar_conta();
                if contas.len() < MAX_CONTAS {
                    contas.push(nova_conta);
                    println!("\n----------------------------\nConta criada com sucesso!\n----------------------------\n");
                } else {
                    println!("\n----------------------------\nLimite de contas atingido. Nao eh possivel criar mais contas.\n----------------------------\n");
                }
            }
            2 => depositar(&mut contas),
            3 => {
                for conta in &contas {
                    println!(
                        "Conta: {}\nTitular: {}\nSaldo: R$ {:.2}\n-----------------------------",
                        conta.numero_conta, conta.nome_titular, conta.saldo
                    );
                }
            }
            4 => {
                editar_informacoes_titular(&mut contas);
            }
            5 => {
                remover_conta(&mut contas);
            }
            6 => {
                transferir_valor(&mut contas);
            }
            7 => {
                salvar_dados(&contas);
            }
            8 => {
                println!("FIM da operacao BANCO MASSA DE MAIS VEI.");
                break;
            }
            _ => {
                println!("Opcao incorreta. Tente novamente.");
            }
        }
    }
}

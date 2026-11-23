#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

// =========================
// ARRAYS DAS CONTAS
// =========================
const int MAX_CONTAS = 100;

int numeroConta[MAX_CONTAS];
string nomeCliente[MAX_CONTAS];
string cpf[MAX_CONTAS];
int tipoConta[MAX_CONTAS];
double saldo[MAX_CONTAS];
bool contaAtiva[MAX_CONTAS];

int quantidadeContas = 0;

// =========================
// ARRAYS DAS MOVIMENTACOES
// =========================
const int MAX_MOVIMENTACOES = 500;

int contaMovimentacao[MAX_MOVIMENTACOES];
char tipoMovimentacao[MAX_MOVIMENTACOES];
double valorMovimentacao[MAX_MOVIMENTACOES];

int quantidadeMovimentacoes = 0;

// =========================
// FUNCOES AUXILIARES DE ENTRADA
// =========================
int lerInteiro(const string& mensagem) {
    int valor;

    while (true) {
        cout << mensagem;

        if (cin >> valor) {
            return valor;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. Digite um numero inteiro.\n";
    }
}

double lerDouble(const string& mensagem) {
    double valor;

    while (true) {
        cout << mensagem;

        if (cin >> valor) {
            return valor;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. Digite um valor numerico.\n";
    }
}

// =========================
// BUSCAR CONTA PELO NUMERO
// =========================
int buscarConta(int numero) {
    for (int i = 0; i < quantidadeContas; i++) {
        if (numeroConta[i] == numero) {
            return i;
        }
    }

    return -1;
}

// =========================
// CARREGAR CONTAS DO ARQUIVO
// =========================
void carregarContas() {
    ifstream arquivo("contas.txt");
    string linha;

    if (!arquivo.is_open()) {
        return;
    }

    while (getline(arquivo, linha) && quantidadeContas < MAX_CONTAS) {
        if (linha.empty()) {
            continue;
        }

        string numeroTexto;
        string nome;
        string cpfTexto;
        string tipoTexto;
        string saldoTexto;
        string ativaTexto;

        stringstream dados(linha);

        // Os campos do arquivo sao separados por ponto e virgula.
        if (!getline(dados, numeroTexto, ';') ||
            !getline(dados, nome, ';') ||
            !getline(dados, cpfTexto, ';') ||
            !getline(dados, tipoTexto, ';') ||
            !getline(dados, saldoTexto, ';') ||
            !getline(dados, ativaTexto)) {
            continue;
        }

        int numero;
        int tipo;
        int ativa;
        double valorSaldo;

        stringstream conversaoNumero(numeroTexto);
        stringstream conversaoTipo(tipoTexto);
        stringstream conversaoSaldo(saldoTexto);
        stringstream conversaoAtiva(ativaTexto);

        if (!(conversaoNumero >> numero) ||
            !(conversaoTipo >> tipo) ||
            !(conversaoSaldo >> valorSaldo) ||
            !(conversaoAtiva >> ativa)) {
            continue;
        }

        // Impede a leitura de registros invalidos ou contas repetidas.
        if (numero <= 0 ||
            (tipo != 1 && tipo != 2) ||
            valorSaldo < 0 ||
            (ativa != 0 && ativa != 1) ||
            buscarConta(numero) != -1) {
            continue;
        }

        int i = quantidadeContas;
        numeroConta[i] = numero;
        nomeCliente[i] = nome;
        cpf[i] = cpfTexto;
        tipoConta[i] = tipo;
        saldo[i] = valorSaldo;
        contaAtiva[i] = (ativa == 1);

        quantidadeContas++;
    }

    arquivo.close();
}

// =========================
// SALVAR CONTAS NO ARQUIVO
// =========================
bool salvarContas() {
    // Sem ios::app: grava novamente todas as contas atualizadas.
    ofstream arquivo("contas.txt");

    if (!arquivo.is_open()) {
        return false;
    }

    arquivo << fixed << setprecision(2);

    for (int i = 0; i < quantidadeContas; i++) {
        arquivo << numeroConta[i] << ";"
                << nomeCliente[i] << ";"
                << cpf[i] << ";"
                << tipoConta[i] << ";"
                << saldo[i] << ";"
                << (contaAtiva[i] ? 1 : 0) << endl;
    }

    arquivo.close();
    return !arquivo.fail();
}

// =========================
// CARREGAR MOVIMENTACOES
// =========================
void carregarMovimentacoes() {
    ifstream arquivo("movimentacoes.txt");
    string linha;

    if (!arquivo.is_open()) {
        return;
    }

    while (getline(arquivo, linha) &&
           quantidadeMovimentacoes < MAX_MOVIMENTACOES) {
        if (linha.empty()) {
            continue;
        }

        string contaTexto;
        string tipoTexto;
        string valorTexto;

        stringstream dados(linha);

        if (!getline(dados, contaTexto, ';') ||
            !getline(dados, tipoTexto, ';') ||
            !getline(dados, valorTexto)) {
            continue;
        }

        int conta;
        double valor;

        stringstream conversaoConta(contaTexto);
        stringstream conversaoValor(valorTexto);

        if (!(conversaoConta >> conta) ||
            !(conversaoValor >> valor)) {
            continue;
        }

        if (conta <= 0 ||
            (tipoTexto != "D" && tipoTexto != "S") ||
            valor <= 0) {
            continue;
        }

        int i = quantidadeMovimentacoes;
        contaMovimentacao[i] = conta;
        tipoMovimentacao[i] = tipoTexto[0];
        valorMovimentacao[i] = valor;

        quantidadeMovimentacoes++;
    }

    arquivo.close();
}

// =========================
// SALVAR MOVIMENTACOES
// =========================
bool salvarMovimentacoes() {
    // Regrava o historico completo, preservando os registros anteriores.
    ofstream arquivo("movimentacoes.txt");

    if (!arquivo.is_open()) {
        return false;
    }

    arquivo << fixed << setprecision(2);

    for (int i = 0; i < quantidadeMovimentacoes; i++) {
        arquivo << contaMovimentacao[i] << ";"
                << tipoMovimentacao[i] << ";"
                << valorMovimentacao[i] << endl;
    }

    arquivo.close();
    return !arquivo.fail();
}

// =========================
// SALVAR TODOS OS DADOS
// =========================
bool salvarDados() {
    bool contasSalvas = salvarContas();
    bool movimentacoesSalvas = salvarMovimentacoes();

    return contasSalvas && movimentacoesSalvas;
}

// =========================
// REGISTRAR MOVIMENTACAO
// =========================
void registrarMovimentacao(int conta, char tipo, double valor) {
    if (quantidadeMovimentacoes < MAX_MOVIMENTACOES) {
        contaMovimentacao[quantidadeMovimentacoes] = conta;
        tipoMovimentacao[quantidadeMovimentacoes] = tipo;
        valorMovimentacao[quantidadeMovimentacoes] = valor;
        quantidadeMovimentacoes++;
    }
}

int main() {
    // Cria os arquivos vazios na primeira execucao, sem apagar dados existentes.
    ofstream criarContas("contas.txt", ios::app);
    ofstream criarMovimentacoes("movimentacoes.txt", ios::app);

    if (!criarContas.is_open() || !criarMovimentacoes.is_open()) {
        cout << "Erro ao criar ou acessar os arquivos do sistema.\n";
        criarContas.close();
        criarMovimentacoes.close();
        return 1;
    }

    criarContas.close();
    criarMovimentacoes.close();

    // Recupera os dados armazenados em execucoes anteriores.
    carregarContas();
    carregarMovimentacoes();

    int opcao = 0;

    do {
        cout << "\n=====================================\n";
        cout << "        BANCO INF101\n";
        cout << "=====================================\n";
        cout << "1 - Cadastrar conta\n";
        cout << "2 - Listar contas\n";
        cout << "3 - Consultar conta\n";
        cout << "4 - Verificar saldo\n";
        cout << "5 - Alterar tipo da conta\n";
        cout << "6 - Ativar/Desativar conta\n";
        cout << "7 - Depositar\n";
        cout << "8 - Sacar\n";
        cout << "9 - Transferir\n";
        cout << "10 - Exibir extrato\n";
        cout << "11 - Sair\n";

        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {

        // ====================================
        // CADASTRAR CONTA
        // ====================================
        case 1: {
            if (quantidadeContas >= MAX_CONTAS) {
                cout << "\nLimite de contas atingido!\n";
                break;
            }

            int novoNumero = lerInteiro("\nNumero da conta: ");

            while (novoNumero <= 0 || buscarConta(novoNumero) != -1) {
                if (novoNumero <= 0) {
                    cout << "Numero invalido. ";
                } else {
                    cout << "Essa conta ja existe. ";
                }

                novoNumero = lerInteiro("Digite outro numero: ");
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string novoNome;
            string novoCPF;

            cout << "Nome do cliente: ";
            getline(cin, novoNome);

            cout << "CPF: ";
            getline(cin, novoCPF);

            int novoTipo = lerInteiro("Tipo da conta (1-Corrente | 2-Poupanca): ");

            while (novoTipo != 1 && novoTipo != 2) {
                novoTipo = lerInteiro("Tipo invalido. Digite 1 ou 2: ");
            }

            double saldoInicial = lerDouble("Saldo inicial: ");

            while (saldoInicial < 0) {
                saldoInicial = lerDouble("Saldo nao pode ser negativo. Digite novamente: ");
            }

            numeroConta[quantidadeContas] = novoNumero;
            nomeCliente[quantidadeContas] = novoNome;
            cpf[quantidadeContas] = novoCPF;
            tipoConta[quantidadeContas] = novoTipo;
            saldo[quantidadeContas] = saldoInicial;
            contaAtiva[quantidadeContas] = true;

            quantidadeContas++;

            if (salvarDados()) {
                cout << "\nConta cadastrada com sucesso!\n";
            } else {
                cout << "\nConta cadastrada, mas ocorreu um erro ao salvar os arquivos.\n";
            }

            break;
        }

        // ====================================
        // LISTAR CONTAS
        // ====================================
        case 2: {
            if (quantidadeContas == 0) {
                cout << "\nNenhuma conta cadastrada.\n";
                break;
            }

            cout << "\n===== LISTA DE CONTAS =====\n";

            for (int i = 0; i < quantidadeContas; i++) {
                cout << "\nConta: " << numeroConta[i];
                cout << "\nTitular: " << nomeCliente[i];
                cout << "\nSaldo: R$ " << fixed << setprecision(2) << saldo[i];
                cout << "\nStatus: ";

                if (contaAtiva[i]) {
                    cout << "Ativa";
                } else {
                    cout << "Inativa";
                }

                cout << "\n-----------------------\n";
            }

            break;
        }

        // ====================================
        // CONSULTAR CONTA
        // ====================================
        case 3: {
            int busca = lerInteiro("\nNumero da conta: ");
            int indice = buscarConta(busca);

            if (indice == -1) {
                cout << "\nConta nao encontrada.\n";
            } else {
                cout << "\nNumero: " << numeroConta[indice];
                cout << "\nTitular: " << nomeCliente[indice];
                cout << "\nCPF: " << cpf[indice];
                cout << "\nTipo: ";

                if (tipoConta[indice] == 1) {
                    cout << "Corrente";
                } else {
                    cout << "Poupanca";
                }

                cout << "\nSaldo: R$ " << fixed << setprecision(2)
                     << saldo[indice];
                cout << "\nStatus: ";

                if (contaAtiva[indice]) {
                    cout << "Ativa";
                } else {
                    cout << "Inativa";
                }

                cout << endl;
            }

            break;
        }

        // ====================================
        // VERIFICAR SALDO
        // ====================================
        case 4: {
            int conta = lerInteiro("\nNumero da conta: ");
            int indice = buscarConta(conta);

            if (indice == -1) {
                cout << "\nConta nao encontrada.\n";
            } else {
                cout << "\nSaldo atual: R$ " << fixed << setprecision(2)
                     << saldo[indice] << endl;
            }

            break;
        }

        // ====================================
        // ALTERAR TIPO DA CONTA
        // ====================================
        case 5: {
            int conta = lerInteiro("\nNumero da conta: ");
            int indice = buscarConta(conta);

            if (indice == -1) {
                cout << "\nConta nao encontrada.\n";
            } else {
                int novoTipo = lerInteiro("Novo tipo (1-Corrente | 2-Poupanca): ");

                while (novoTipo != 1 && novoTipo != 2) {
                    novoTipo = lerInteiro("Digite apenas 1 ou 2: ");
                }

                tipoConta[indice] = novoTipo;

                if (salvarDados()) {
                    cout << "\nTipo atualizado com sucesso!\n";
                } else {
                    cout << "\nTipo alterado, mas ocorreu um erro ao salvar os arquivos.\n";
                }
            }

            break;
        }

        // ====================================
        // ATIVAR / DESATIVAR CONTA
        // ====================================
        case 6: {
            int conta = lerInteiro("\nNumero da conta: ");
            int indice = buscarConta(conta);

            if (indice == -1) {
                cout << "\nConta nao encontrada.\n";
            } else {
                contaAtiva[indice] = !contaAtiva[indice];

                if (salvarDados()) {
                    if (contaAtiva[indice]) {
                        cout << "\nConta ativada.\n";
                    } else {
                        cout << "\nConta desativada.\n";
                    }
                } else {
                    cout << "\nStatus alterado, mas ocorreu um erro ao salvar os arquivos.\n";
                }
            }

            break;
        }

        // ====================================
        // DEPOSITO
        // ====================================
        case 7: {
            int conta = lerInteiro("\nNumero da conta: ");
            int indice = buscarConta(conta);

            if (indice == -1) {
                cout << "\nConta nao encontrada.\n";
                break;
            }

            if (!contaAtiva[indice]) {
                cout << "\nConta inativa.\n";
                break;
            }

            if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
                cout << "\nLimite de movimentacoes atingido. Operacao cancelada.\n";
                break;
            }

            double valor = lerDouble("Valor para deposito: ");

            if (valor <= 0) {
                cout << "\nValor invalido.\n";
                break;
            }

            saldo[indice] += valor;
            registrarMovimentacao(numeroConta[indice], 'D', valor);

            if (salvarDados()) {
                cout << "\nDeposito realizado.\n";
            } else {
                cout << "\nDeposito realizado, mas ocorreu um erro ao salvar os arquivos.\n";
            }

            break;
        }

        // ====================================
        // SAQUE
        // ====================================
        case 8: {
            int conta = lerInteiro("\nNumero da conta: ");
            int indice = buscarConta(conta);

            if (indice == -1) {
                cout << "\nConta nao encontrada.\n";
                break;
            }

            if (!contaAtiva[indice]) {
                cout << "\nConta inativa.\n";
                break;
            }

            if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
                cout << "\nLimite de movimentacoes atingido. Operacao cancelada.\n";
                break;
            }

            double valor = lerDouble("Valor do saque: ");

            if (valor <= 0) {
                cout << "\nValor invalido.\n";
                break;
            }

            if (valor > saldo[indice]) {
                cout << "\nSaldo insuficiente.\n";
                break;
            }

            saldo[indice] -= valor;
            registrarMovimentacao(numeroConta[indice], 'S', valor);

            if (salvarDados()) {
                cout << "\nSaque realizado.\n";
            } else {
                cout << "\nSaque realizado, mas ocorreu um erro ao salvar os arquivos.\n";
            }

            break;
        }

        // ====================================
        // TRANSFERENCIA
        // ====================================
        case 9: {
            int origem = lerInteiro("\nConta origem: ");
            int destino = lerInteiro("Conta destino: ");

            int indiceOrigem = buscarConta(origem);
            int indiceDestino = buscarConta(destino);

            if (indiceOrigem == -1 || indiceDestino == -1) {
                cout << "\nConta nao encontrada.\n";
                break;
            }

            if (indiceOrigem == indiceDestino) {
                cout << "\nA conta de origem e destino devem ser diferentes.\n";
                break;
            }

            if (!contaAtiva[indiceOrigem] || !contaAtiva[indiceDestino]) {
                cout << "\nUma das contas esta inativa.\n";
                break;
            }

            if (quantidadeMovimentacoes + 2 > MAX_MOVIMENTACOES) {
                cout << "\nNao ha espaco para registrar as duas movimentacoes. Operacao cancelada.\n";
                break;
            }

            double valor = lerDouble("Valor da transferencia: ");

            if (valor <= 0) {
                cout << "\nValor invalido.\n";
                break;
            }

            if (saldo[indiceOrigem] < valor) {
                cout << "\nSaldo insuficiente.\n";
                break;
            }

            saldo[indiceOrigem] -= valor;
            saldo[indiceDestino] += valor;

            // A transferencia gera dois registros no historico:
            // saida (S) na origem e entrada (D) no destino.
            registrarMovimentacao(numeroConta[indiceOrigem], 'S', valor);
            registrarMovimentacao(numeroConta[indiceDestino], 'D', valor);

            if (salvarDados()) {
                cout << "\nTransferencia realizada.\n";
            } else {
                cout << "\nTransferencia realizada, mas ocorreu um erro ao salvar os arquivos.\n";
            }

            break;
        }

        // ====================================
        // EXTRATO
        // ====================================
        case 10: {
            int conta = lerInteiro("\nNumero da conta: ");

            if (buscarConta(conta) == -1) {
                cout << "\nConta nao encontrada.\n";
                break;
            }

            cout << "\n===== EXTRATO =====\n";
            bool encontrou = false;

            for (int i = 0; i < quantidadeMovimentacoes; i++) {
                if (contaMovimentacao[i] == conta) {
                    encontrou = true;

                    if (tipoMovimentacao[i] == 'D') {
                        cout << "Deposito/entrada: R$ "
                             << fixed << setprecision(2)
                             << valorMovimentacao[i] << endl;
                    } else if (tipoMovimentacao[i] == 'S') {
                        cout << "Saque/saida: R$ "
                             << fixed << setprecision(2)
                             << valorMovimentacao[i] << endl;
                    }
                }
            }

            if (!encontrou) {
                cout << "Nenhuma movimentacao encontrada.\n";
            }

            break;
        }

        case 11:
            if (salvarDados()) {
                cout << "\nDados salvos. Encerrando sistema...\n";
            } else {
                cout << "\nErro ao salvar os dados. Encerrando sistema...\n";
            }
            break;

        default:
            cout << "\nOpcao invalida!\n";
        }

    } while (opcao != 11);

    return 0;
}


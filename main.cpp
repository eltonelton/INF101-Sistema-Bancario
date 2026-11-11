#include <iostream>
#include <string>

using namespace std;

int main() {
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

    int opcao;

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
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {

        // ====================================
        // CADASTRAR CONTA
        // ====================================
        case 1: {
            if (quantidadeContas >= MAX_CONTAS) {
                cout << "\nLimite de contas atingido!\n";
                break;
            }

            cout << "\nNumero da conta: ";
            cin >> numeroConta[quantidadeContas];

            while (numeroConta[quantidadeContas] <= 0) {
                cout << "Numero invalido. Digite novamente: ";
                cin >> numeroConta[quantidadeContas];
            }

            cin.ignore();

            cout << "Nome do cliente: ";
            getline(cin, nomeCliente[quantidadeContas]);

            cout << "CPF: ";
            getline(cin, cpf[quantidadeContas]);

            cout << "Tipo da conta (1-Corrente | 2-Poupanca): ";
            cin >> tipoConta[quantidadeContas];

            while (tipoConta[quantidadeContas] != 1 &&
                   tipoConta[quantidadeContas] != 2) {

                cout << "Tipo invalido. Digite 1 ou 2: ";
                cin >> tipoConta[quantidadeContas];
            }

            cout << "Saldo inicial: ";
            cin >> saldo[quantidadeContas];

            while (saldo[quantidadeContas] < 0) {
                cout << "Saldo nao pode ser negativo: ";
                cin >> saldo[quantidadeContas];
            }

            contaAtiva[quantidadeContas] = true;

            quantidadeContas++;

            cout << "\nConta cadastrada com sucesso!\n";

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
                cout << "\nSaldo: R$ " << saldo[i];
                cout << "\nStatus: ";

                if (contaAtiva[i])
                    cout << "Ativa";
                else
                    cout << "Inativa";

                cout << "\n-----------------------\n";
            }

            break;
        }

        // ====================================
        // CONSULTAR CONTA
        // ====================================
        case 3: {
            int busca;
            int indice = -1;

            cout << "\nNumero da conta: ";
            cin >> busca;

            for (int i = 0; i < quantidadeContas; i++) {
                if (numeroConta[i] == busca) {
                    indice = i;
                    break;
                }
            }

            if (indice == -1) {
                cout << "\nConta nao encontrada.\n";
            } else {

                cout << "\nNumero: " << numeroConta[indice];
                cout << "\nTitular: " << nomeCliente[indice];
                cout << "\nCPF: " << cpf[indice];

                cout << "\nTipo: ";

                if (tipoConta[indice] == 1)
                    cout << "Corrente";
                else
                    cout << "Poupanca";

                cout << "\nSaldo: R$ " << saldo[indice];

                cout << "\nStatus: ";
                if (contaAtiva[indice])
                    cout << "Ativa";
                else
                    cout << "Inativa";

                cout << endl;
            }

            break;
        }

        // ====================================
        // SALDO
        // ====================================
        case 4: {

            int conta;
            int indice = -1;

            cout << "\nNumero da conta: ";
            cin >> conta;

            for (int i = 0; i < quantidadeContas; i++) {
                if (numeroConta[i] == conta) {
                    indice = i;
                    break;
                }
            }

            if (indice == -1)
                cout << "\nConta nao encontrada.\n";
            else
                cout << "\nSaldo atual: R$ "
                     << saldo[indice] << endl;

            break;
        }

        // ====================================
        // ALTERAR TIPO
        // ====================================
        case 5: {

            int conta;
            int indice = -1;

            cout << "\nNumero da conta: ";
            cin >> conta;

            for (int i = 0; i < quantidadeContas; i++) {
                if (numeroConta[i] == conta) {
                    indice = i;
                    break;
                }
            }

            if (indice == -1) {
                cout << "\nConta nao encontrada.\n";
            }
            else {

                cout << "Novo tipo (1-Corrente | 2-Poupanca): ";
                cin >> tipoConta[indice];

                while (tipoConta[indice] != 1 &&
                       tipoConta[indice] != 2) {

                    cout << "Digite apenas 1 ou 2: ";
                    cin >> tipoConta[indice];
                }

                cout << "\nTipo atualizado com sucesso!\n";
            }

            break;
        }

        // ====================================
        // ATIVAR / DESATIVAR
        // ====================================
        case 6: {

            int conta;
            int indice = -1;

            cout << "\nNumero da conta: ";
            cin >> conta;

            for (int i = 0; i < quantidadeContas; i++) {

                if (numeroConta[i] == conta) {
                    indice = i;
                    break;
                }
            }

            if (indice == -1) {
                cout << "\nConta nao encontrada.\n";
            }
            else {

                contaAtiva[indice] = !contaAtiva[indice];

                if (contaAtiva[indice])
                    cout << "\nConta ativada.\n";
                else
                    cout << "\nConta desativada.\n";
            }

            break;
        }

        // ====================================
        // DEPOSITO
        // ====================================
        case 7: {

            int conta;
            int indice = -1;
            double valor;

            cout << "\nNumero da conta: ";
            cin >> conta;

            for (int i = 0; i < quantidadeContas; i++) {

                if (numeroConta[i] == conta) {
                    indice = i;
                    break;
                }
            }

            if (indice == -1) {
                cout << "\nConta nao encontrada.\n";
                break;
            }

            if (!contaAtiva[indice]) {
                cout << "\nConta inativa.\n";
                break;
            }

            cout << "Valor para deposito: ";
            cin >> valor;

            if (valor <= 0) {
                cout << "\nValor invalido.\n";
                break;
            }

            saldo[indice] += valor;

            if (quantidadeMovimentacoes < MAX_MOVIMENTACOES) {

                contaMovimentacao[quantidadeMovimentacoes] =
                    numeroConta[indice];

                tipoMovimentacao[quantidadeMovimentacoes] = 'D';

                valorMovimentacao[quantidadeMovimentacoes] =
                    valor;

                quantidadeMovimentacoes++;
            }

            cout << "\nDeposito realizado.\n";

            break;
        }

        // ====================================
        // SAQUE
        // ====================================
        case 8: {

            int conta;
            int indice = -1;
            double valor;

            cout << "\nNumero da conta: ";
            cin >> conta;

            for (int i = 0; i < quantidadeContas; i++) {
                if (numeroConta[i] == conta) {
                    indice = i;
                    break;
                }
            }

            if (indice == -1) {
                cout << "\nConta nao encontrada.\n";
                break;
            }

            if (!contaAtiva[indice]) {
                cout << "\nConta inativa.\n";
                break;
            }

            cout << "Valor do saque: ";
            cin >> valor;

            if (valor <= 0) {
                cout << "\nValor invalido.\n";
                break;
            }

            if (valor > saldo[indice]) {
                cout << "\nSaldo insuficiente.\n";
                break;
            }

            saldo[indice] -= valor;

            if (quantidadeMovimentacoes < MAX_MOVIMENTACOES) {

                contaMovimentacao[quantidadeMovimentacoes] =
                    numeroConta[indice];

                tipoMovimentacao[quantidadeMovimentacoes] = 'S';

                valorMovimentacao[quantidadeMovimentacoes] =
                    valor;

                quantidadeMovimentacoes++;
            }

            cout << "\nSaque realizado.\n";

            break;
        }

        // ====================================
        // TRANSFERENCIA
        // ====================================
        case 9: {

            int origem, destino;
            int indiceOrigem = -1;
            int indiceDestino = -1;

            double valor;

            cout << "\nConta origem: ";
            cin >> origem;

            cout << "Conta destino: ";
            cin >> destino;

            for (int i = 0; i < quantidadeContas; i++) {

                if (numeroConta[i] == origem)
                    indiceOrigem = i;

                if (numeroConta[i] == destino)
                    indiceDestino = i;
            }

            if (indiceOrigem == -1 ||
                indiceDestino == -1) {

                cout << "\nConta nao encontrada.\n";
                break;
            }

            if (!contaAtiva[indiceOrigem] ||
                !contaAtiva[indiceDestino]) {

                cout << "\nUma das contas esta inativa.\n";
                break;
            }

            cout << "Valor da transferencia: ";
            cin >> valor;

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

            if (quantidadeMovimentacoes + 1 <
                MAX_MOVIMENTACOES) {

                contaMovimentacao[quantidadeMovimentacoes] =
                    numeroConta[indiceOrigem];

                tipoMovimentacao[quantidadeMovimentacoes] = 'S';

                valorMovimentacao[quantidadeMovimentacoes] =
                    valor;

                quantidadeMovimentacoes++;

                contaMovimentacao[quantidadeMovimentacoes] =
                    numeroConta[indiceDestino];

                tipoMovimentacao[quantidadeMovimentacoes] = 'D';

                valorMovimentacao[quantidadeMovimentacoes] =
                    valor;

                quantidadeMovimentacoes++;
            }

            cout << "\nTransferencia realizada.\n";

            break;
        }

        // ====================================
        // EXTRATO
        // ====================================
        case 10: {

            int conta;

            cout << "\nNumero da conta: ";
            cin >> conta;

            cout << "\n===== EXTRATO =====\n";

            bool encontrou = false;

            for (int i = 0;
                 i < quantidadeMovimentacoes;
                 i++) {

                if (contaMovimentacao[i] == conta) {

                    encontrou = true;

                    if (tipoMovimentacao[i] == 'D')
                        cout << "Deposito: R$ "
                             << valorMovimentacao[i]
                             << endl;

                    else if
                    (tipoMovimentacao[i] == 'S')

                        cout << "Saque: R$ "
                             << valorMovimentacao[i]
                             << endl;
                }
            }

            if (!encontrou) {
                cout << "Nenhuma movimentacao encontrada.\n";
            }

            break;
        }

        case 11:
            cout << "\nEncerrando sistema...\n";
            break;

        default:
            cout << "\nOpcao invalida!\n";
        }

    } while (opcao != 11);

    return 0;
}
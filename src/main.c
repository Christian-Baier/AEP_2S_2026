#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cctype>
#include <iomanip>
using namespace std;

const int LIMITE_MAXIMO = 50;

struct Acao {
    string codigo;
    string escola;
    string tema;
    string data;
    string publicoAlvo;
    string responsavel;
    int quantidadePrevista;
    int participantesEfetivos;
    string situacao;
};

string lerTexto(string mensagem) {
    string texto;
    bool temConteudo;

    while (true) {
        cout << mensagem;
        if (!getline(cin, texto)) {
            cout << "\nEntrada encerrada.\n";
            exit(0);
        }

        if (texto.size() > 0 && texto[texto.size() - 1] == '\r') {
            texto.erase(texto.size() - 1);
        }

        temConteudo = false;
        for (int i = 0; i < (int) texto.size(); i++) {
            if (texto[i] != ' ') {
                temConteudo = true;
            }
        }

        if (temConteudo) {
            return texto;
        }
        cout << "Erro: campo vazio.\n";
    }
}

int lerNumero(string mensagem) {
    string texto;
    bool valido;
    int numero;

    while (true) {
        texto = lerTexto(mensagem);
        valido = true;
        numero = 0;

        for (int i = 0; i < (int) texto.size(); i++) {
            if (texto[i] < '0' || texto[i] > '9') {
                valido = false;
            } else {
                numero = numero * 10 + (texto[i] - '0');
            }
        }

        if (valido && texto.size() <= 6) {
            return numero;
        }
        cout << "Erro: digite apenas numeros, sem sinal de menos.\n";
    }
}

int lerOpcao(string mensagem, int minimo, int maximo) {
    int opcao;

    while (true) {
        opcao = lerNumero(mensagem);
        if (opcao >= minimo && opcao <= maximo) {
            return opcao;
        }
        cout << "Opcao invalida. Escolha de " << minimo << " a " << maximo << ".\n";
    }
}

bool dataValida(string data) {
    if (data.size() != 10) {
        return false;
    }
    if (data[2] != '/' || data[5] != '/') {
        return false;
    }

    for (int i = 0; i < 10; i++) {
        if (i != 2 && i != 5) {
            if (data[i] < '0' || data[i] > '9') {
                return false;
            }
        }
    }

    int dia = (data[0] - '0') * 10 + (data[1] - '0');
    int mes = (data[3] - '0') * 10 + (data[4] - '0');
    int ano = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');

    if (dia < 1 || dia > 31) {
        return false;
    }
    if (mes < 1 || mes > 12) {
        return false;
    }
    if (ano < 2000 || ano > 2100) {
        return false;
    }
    return true;
}

string lerData(string mensagem) {
    string data;

    while (true) {
        data = lerTexto(mensagem);
        if (dataValida(data)) {
            return data;
        }
        cout << "Erro: data invalida. Use dd/mm/aaaa (exemplo: 15/10/2026).\n";
    }
}

string minusculo(string texto) {
    for (int i = 0; i < (int) texto.size(); i++) {
        texto[i] = tolower(texto[i]);
    }
    return texto;
}

// retorna a posicao da acao no vetor, ou -1 se nao achar
int buscarPorCodigo(const vector<Acao>& acoes, string codigo) {
    for (int i = 0; i < (int) acoes.size(); i++) {
        if (acoes[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void mostrarAcao(const Acao& a) {
    cout << "Codigo: " << a.codigo << "\n";
    cout << "Escola: " << a.escola << "\n";
    cout << "Tema: " << a.tema << "\n";
    cout << "Data prevista: " << a.data << "\n";
    cout << "Publico-alvo: " << a.publicoAlvo << "\n";
    cout << "Responsavel: " << a.responsavel << "\n";
    cout << "Quantidade prevista: " << a.quantidadePrevista << "\n";
    cout << "Participantes efetivos: " << a.participantesEfetivos << "\n";
    cout << "Situacao: " << a.situacao << "\n";
    cout << "----------------------------------\n";
}

// RF01
void cadastrarAcao(vector<Acao>& acoes) {
    if ((int) acoes.size() >= LIMITE_MAXIMO) {
        cout << "Capacidade maxima de acoes atingida.\n";
        return;
    }

    Acao nova;

    while (true) {
        nova.codigo = lerTexto("Codigo da acao: ");
        if (buscarPorCodigo(acoes, nova.codigo) != -1) {
            cout << "Erro: codigo ja cadastrado.\n";
        } else {
            break;
        }
    }

    nova.escola = lerTexto("Escola: ");
    nova.tema = lerTexto("Tema: ");
    nova.data = lerData("Data prevista (dd/mm/aaaa): ");
    nova.publicoAlvo = lerTexto("Publico-alvo: ");
    nova.responsavel = lerTexto("Responsavel (cargo ou setor): ");
    nova.quantidadePrevista = lerNumero("Quantidade prevista de participantes: ");

    nova.situacao = "planejada";
    nova.participantesEfetivos = 0;

    acoes.push_back(nova);
    cout << "Acao cadastrada com sucesso.\n";
}

// RF02
void listarAcoes(const vector<Acao>& acoes) {
    if (acoes.empty()) {
        cout << "Nenhuma acao cadastrada.\n";
        return;
    }

    cout << "\n=== LISTA DE ACOES ===\n";
    for (int i = 0; i < (int) acoes.size(); i++) {
        mostrarAcao(acoes[i]);
    }
}

// RF03
void pesquisarAcoes(const vector<Acao>& acoes) {
    if (acoes.empty()) {
        cout << "Nenhuma acao cadastrada.\n";
        return;
    }

    cout << "Pesquisar por:\n";
    cout << "1 - Codigo\n";
    cout << "2 - Escola\n";
    cout << "3 - Tema\n";
    int tipo = lerOpcao("Escolha: ", 1, 3);
    string busca = minusculo(lerTexto("Digite o que procura: "));

    int encontradas = 0;
    string campo;

    for (int i = 0; i < (int) acoes.size(); i++) {
        if (tipo == 1) {
            campo = acoes[i].codigo;
        } else if (tipo == 2) {
            campo = acoes[i].escola;
        } else {
            campo = acoes[i].tema;
        }

        if (minusculo(campo).find(busca) != string::npos) {
            mostrarAcao(acoes[i]);
            encontradas++;
        }
    }

    if (encontradas == 0) {
        cout << "Nenhuma acao encontrada.\n";
    } else {
        cout << "Total encontrado: " << encontradas << "\n";
    }
}

// RF04
void atualizarSituacao(vector<Acao>& acoes) {
    if (acoes.empty()) {
        cout << "Nenhuma acao cadastrada.\n";
        return;
    }

    string codigo = lerTexto("Codigo da acao: ");
    int pos = buscarPorCodigo(acoes, codigo);

    if (pos == -1) {
        cout << "Erro: acao nao encontrada.\n";
        return;
    }

    cout << "Situacao atual: " << acoes[pos].situacao << "\n";
    cout << "1 - Planejada\n";
    cout << "2 - Realizada\n";
    cout << "3 - Cancelada\n";
    int opcao = lerOpcao("Nova situacao: ", 1, 3);

    if (opcao == 1) {
        acoes[pos].situacao = "planejada";
        acoes[pos].participantesEfetivos = 0;
    } else if (opcao == 2) {
        acoes[pos].situacao = "realizada";
        acoes[pos].participantesEfetivos = lerNumero("Quantidade efetiva de participantes: ");
    } else {
        acoes[pos].situacao = "cancelada";
        acoes[pos].participantesEfetivos = 0;
    }

    cout << "Situacao atualizada com sucesso.\n";
}

// RF05
void registrarParticipantes(vector<Acao>& acoes) {
    if (acoes.empty()) {
        cout << "Nenhuma acao cadastrada.\n";
        return;
    }

    string codigo = lerTexto("Codigo da acao: ");
    int pos = buscarPorCodigo(acoes, codigo);

    if (pos == -1) {
        cout << "Erro: acao nao encontrada.\n";
        return;
    }

    if (acoes[pos].situacao != "realizada") {
        cout << "Erro: so e possivel registrar participantes de acao realizada.\n";
        cout << "Use a opcao 4 para atualizar a situacao primeiro.\n";
        return;
    }

    acoes[pos].participantesEfetivos = lerNumero("Quantidade efetiva de participantes: ");
    cout << "Participantes registrados com sucesso.\n";
}

// RF06
void gerarResumo(const vector<Acao>& acoes) {
    if (acoes.empty()) {
        cout << "Nenhuma acao cadastrada.\n";
        return;
    }

    int planejadas = 0;
    int realizadas = 0;
    int canceladas = 0;
    int totalPrevisto = 0;
    int totalEfetivo = 0;

    for (int i = 0; i < (int) acoes.size(); i++) {
        if (acoes[i].situacao == "planejada") {
            planejadas++;
        } else if (acoes[i].situacao == "realizada") {
            realizadas++;
        } else {
            canceladas++;
        }
        totalPrevisto = totalPrevisto + acoes[i].quantidadePrevista;
        totalEfetivo = totalEfetivo + acoes[i].participantesEfetivos;
    }

    cout << "\n=== RESUMO ESTATISTICO ===\n";
    cout << "Total de acoes: " << acoes.size() << "\n";
    cout << "Planejadas: " << planejadas << "\n";
    cout << "Realizadas: " << realizadas << "\n";
    cout << "Canceladas: " << canceladas << "\n";
    cout << "Total previsto de participantes: " << totalPrevisto << "\n";
    cout << "Total efetivo de participantes: " << totalEfetivo << "\n";

    if (totalPrevisto > 0) {
        double percentual = (double) totalEfetivo / totalPrevisto * 100;
        cout << fixed << setprecision(1);
        cout << "Percentual geral de participacao: " << percentual << "%\n";
    } else {
        cout << "Percentual geral de participacao: sem previsao para calcular.\n";
    }
}

void exibirMenu() {
    cout << "\n===== NUTRIESCOLA =====\n";
    cout << "1 - Cadastrar acao\n";
    cout << "2 - Listar acoes\n";
    cout << "3 - Pesquisar acao\n";
    cout << "4 - Atualizar situacao\n";
    cout << "5 - Registrar participantes\n";
    cout << "6 - Gerar resumo estatistico\n";
    cout << "7 - Sair\n";
}

int main() {
    vector<Acao> acoes;
    int opcao = 0;

    while (opcao != 7) {
        exibirMenu();
        opcao = lerOpcao("Escolha uma opcao: ", 1, 7);

        if (opcao == 1) {
            cadastrarAcao(acoes);
        } else if (opcao == 2) {
            listarAcoes(acoes);
        } else if (opcao == 3) {
            pesquisarAcoes(acoes);
        } else if (opcao == 4) {
            atualizarSituacao(acoes);
        } else if (opcao == 5) {
            registrarParticipantes(acoes);
        } else if (opcao == 6) {
            gerarResumo(acoes);
        } else {
            cout << "NutriEscola encerrado.\n";
        }
    }

    return 0;
}

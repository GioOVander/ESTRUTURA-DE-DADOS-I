#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Enum (struct de número) do Status
typedef enum {
    AGUARDANDOAVALIACAO,
    EM_REPARO,
    FINALIZADO,
    ENTREGUE
} Status;

//Struct do Cliente
typedef struct {
    char cpf[12];
    char nome[100];
    char telefone[13];
} Cliente;

//Struct do Veículo
typedef struct {
    char placa[8];
    char modelo[100];
    int ano;
    char cpfDono[12];
} Veiculo;

//Struct de Ordem de Serviço
typedef struct {
    int id;
    char placaVeiculo[8];
    char dataEntrada[20];
    char descricaoProblema[200];
    Status status;
} OrdemServico;

//Função pra limpar o buffer do teclado (evita problemas no scanf)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Função para calcular o tamanho da string
int tamanhoString(const char *str) {
    int tam = 0;
    while (str[tam] != '\0') {
        tam++;
    }
    return tam;
}

//Função para copiar strings (sem usar strcpy)
void copiarString(char *destino, const char *origem) {
    int i = 0;
    while (origem[i] != '\0') {
        destino[i] = origem[i];
        i++;
    }
    destino[i] = '\0';
}

//Função que verifica se a string é numérica
int ehNumero(const char *str) {
    int i = 0;
    if (str[0] == '\0') return 0;
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
        i++;
    }
    return 1;
}

//Função que verifica se a string é alfanumérica (letras e números)
int ehAlfanumerico(const char *str) {
    int i = 0;
    if (str[0] == '\0') return 0;
    while (str[i] != '\0') {
        if (!isalnum((unsigned char)str[i])) {
            return 0;
        }
        i++;
    }
    return 1;
}

//Transforma string em maiúsculas
void maiusculas(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] = toupper((unsigned char)str[i]);
        i++;
    }
}

//Lê um número inteiro de forma segura
int lerInt(int *destino) {
    if (scanf("%d", destino) == 1) {
        limparBuffer();
        return 1;
    }
    limparBuffer();
    return 0;
}

//Função para ler strings com validação (CPF, telefone, placa, nome, etc.)
void lerStringValidada(const char *prompt, char *destino, int tamanhoMax, int tipoValidacao) {
    char buffer[512];
    int valido = 0;
    while (!valido) {
        printf("%s", prompt);
        if (scanf("%511[^\n]", buffer) == 1) {
            limparBuffer();
            int len = tamanhoString(buffer);
            if (len <= 0) {
                printf("Erro: entrada vazia.\n");
                continue;
            }
            if (len >= tamanhoMax) {
                printf("Erro: máximo %d caracteres.\n", tamanhoMax - 1);
                continue;
            }

            if (tipoValidacao == 1) { // CPF
                if (len != 11 || !ehNumero(buffer)) {
                    printf("Erro: CPF deve conter exatamente 11 números.\n");
                    continue;
                }
                valido = 1;
            } 
            else if (tipoValidacao == 2) { // Telefone
                if ((len < 10 || len > 11) || !ehNumero(buffer)) {
                    printf("Erro: telefone deve ter 10 ou 11 dígitos numéricos.\n");
                    continue;
                }
                valido = 1;
            } 
            else if (tipoValidacao == 3) { // Placa
                if (len != 7 || !ehAlfanumerico(buffer)) {
                    printf("Erro: placa deve conter exatamente 7 letras e números.\n");
                    continue;
                }
                maiusculas(buffer);
                valido = 1;
            } 
            else {
                valido = 1;
            }

            if (valido) {
                copiarString(destino, buffer);
            }
        } else {
            limparBuffer();
            printf("Erro na leitura. Tente novamente.\n");
        }
    }
}

//Função para ler e validar o ano
void lerAno(int *destino) {
    int ok = 0;
    do {
        printf("Ano: ");
        if (!lerInt(destino)) {
            printf("Entrada inválida.\n");
            continue;
        }
        if (*destino < 1900 || *destino > 2100) {
            printf("Ano inválido. Use um ano entre 1900 e 2100.\n");
            continue;
        }
        ok = 1;
    } while (!ok);
}

//Função para comparar strings (retorna 1 se forem iguais)
int compararStrings(const char *str1, const char *str2) {
    return strcmp(str1, str2) == 0;
}

//Busca cliente pelo CPF
int buscarClienteporCPF(const char *cpf, Cliente *clienteEncontrado) {
    FILE *arquivo = fopen("clientes.dat", "rb");
    if (arquivo == NULL) return 0;

    Cliente temp;
    while (fread(&temp, sizeof(Cliente), 1, arquivo) == 1) {
        if (compararStrings(temp.cpf, cpf)) {
            *clienteEncontrado = temp;
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
    return 0;
}

//Busca veículo pela placa
int buscarVeiculoporPlaca(const char *placa, Veiculo *veiculoEncontrado) {
    FILE *arquivo = fopen("veiculos.dat", "rb");
    if (arquivo == NULL) return 0;

    Veiculo temp;
    while (fread(&temp, sizeof(Veiculo), 1, arquivo) == 1) {
        if (compararStrings(temp.placa, placa)) {
            *veiculoEncontrado = temp;
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
    return 0;
}

//Função para o Cadastro de Clientes
void CadastrarCliente() {
    Cliente novoCliente;
    Cliente clienteExistente;

    printf("\n--- Cadastro de Cliente ---\n");
    lerStringValidada("CPF (apenas números): ", novoCliente.cpf, sizeof(novoCliente.cpf), 1);

    if (buscarClienteporCPF(novoCliente.cpf, &clienteExistente)) {
        printf("Erro: CPF já cadastrado!\n");
        return;
    }

    lerStringValidada("Nome completo: ", novoCliente.nome, sizeof(novoCliente.nome), 0);
    lerStringValidada("Telefone (apenas números): ", novoCliente.telefone, sizeof(novoCliente.telefone), 2);

    FILE *arquivo = fopen("clientes.dat", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    fwrite(&novoCliente, sizeof(Cliente), 1, arquivo);
    fclose(arquivo);
    printf("Cliente cadastrado com sucesso!\n");
}

//Função para o Cadastro de Veículos
void cadastrarVeiculo() {
    Veiculo novoVeiculo;
    Cliente dono;
    Veiculo veiculoExistente;

    printf("\n--- Cadastro de Veículo ---\n");
    lerStringValidada("CPF do dono: ", novoVeiculo.cpfDono, sizeof(novoVeiculo.cpfDono), 1);

    if (!buscarClienteporCPF(novoVeiculo.cpfDono, &dono)) {
        printf("Erro! Cliente com este CPF não existe.\n");
        return;
    }

    lerStringValidada("Placa (ex: ABC1234): ", novoVeiculo.placa, sizeof(novoVeiculo.placa), 3);

    if (buscarVeiculoporPlaca(novoVeiculo.placa, &veiculoExistente)) {
        printf("Erro! Veículo com esta placa já está cadastrado!\n");
        return;
    }

    lerStringValidada("Modelo: ", novoVeiculo.modelo, sizeof(novoVeiculo.modelo), 0);
    lerAno(&novoVeiculo.ano);

    FILE *arquivo = fopen("veiculos.dat", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de veículos!\n");
        return;
    }
    fwrite(&novoVeiculo, sizeof(Veiculo), 1, arquivo);
    fclose(arquivo);

    printf("Veículo cadastrado com sucesso para o cliente %s!\n", dono.nome);
}

//Função para abrir Ordem de Serviço
void AbrirOrdemServico() {
    OrdemServico novaOrdem;
    Veiculo veiculo;
    int ultimoID = 0;

    printf("\n--- Abertura de Ordem de Serviço ---\n");
    lerStringValidada("Placa do veículo: ", novaOrdem.placaVeiculo, sizeof(novaOrdem.placaVeiculo), 3);

    if (!buscarVeiculoporPlaca(novaOrdem.placaVeiculo, &veiculo)) {
        printf("Erro! Veículo não encontrado!\n");
        return;
    }

    FILE *arquivo = fopen("ordem.dat", "rb");
    if (arquivo != NULL) {
        OrdemServico temp;
        while (fread(&temp, sizeof(OrdemServico), 1, arquivo) == 1) {
            ultimoID = temp.id;
        }
        fclose(arquivo);
    }
    novaOrdem.id = ultimoID + 1;

    lerStringValidada("Data de entrada (DD/MM/AAAA): ", novaOrdem.dataEntrada, sizeof(novaOrdem.dataEntrada), 0);
    lerStringValidada("Descrição do problema: ", novaOrdem.descricaoProblema, sizeof(novaOrdem.descricaoProblema), 0);
    novaOrdem.status = AGUARDANDOAVALIACAO;

    arquivo = fopen("ordem.dat", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de ordens de serviço!\n");
        return;
    }
    fwrite(&novaOrdem, sizeof(OrdemServico), 1, arquivo);
    fclose(arquivo);

    printf("Ordem de serviço %d aberta com sucesso para o veículo %s!\n", novaOrdem.id, veiculo.modelo);
}

//Função para Atualização de Status
void atualizarStatusOS() {
    int idOS, novoStatusInt;
    printf("\n--- Atualizar Status da Ordem de Serviço ---\n");
    printf("Digite o ID da Ordem de Serviço: ");
    scanf("%d", &idOS);
    limparBuffer();

    FILE *arquivo = fopen("ordem.dat", "rb+");
    if (arquivo == NULL) {
        printf("Nenhuma ordem de serviço encontrada.\n");
        return;
    }

    OrdemServico os;
    int encontrada = 0;
    while (fread(&os, sizeof(OrdemServico), 1, arquivo) == 1) {
        if (os.id == idOS) {
            printf("Status atual: %d\n", os.status);
            printf("Novo status (0: Aguardando, 1: Em reparo, 2: Finalizado, 3: Entregue): ");
            scanf("%d", &novoStatusInt);
            limparBuffer();

            if (novoStatusInt >= 0 && novoStatusInt <= 3) {
                os.status = (Status)novoStatusInt;
                fseek(arquivo, -sizeof(OrdemServico), SEEK_CUR);
                fwrite(&os, sizeof(OrdemServico), 1, arquivo);
                printf("Status da OS #%d atualizado com sucesso!\n", idOS);
            } else {
                printf("Status inválido.\n");
            }

            encontrada = 1;
            break;
        }
    }

    if (!encontrada) {
        printf("Ordem de serviço com ID #%d não encontrada.\n", idOS);
    }
    fclose(arquivo);
}

//Função para Relatório de Veículos por Cliente
void relatorioVeiculoCliente() {
    char cpf[12];
    Cliente cliente;

    printf("\n--- Relatório de Veículos por Cliente ---\n");
    lerStringValidada("Digite o CPF do cliente: ", cpf, sizeof(cpf), 1);

    if (!buscarClienteporCPF(cpf, &cliente)) {
        printf("Cliente não encontrado.\n");
        return;
    }

    printf("\nVeículos de %s:\n", cliente.nome);
    Veiculo v;
    int encontrou = 0;
    FILE *arquivo = fopen("veiculos.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de veículos.\n");
        return;
    }
    while (fread(&v, sizeof(Veiculo), 1, arquivo) == 1) {
        if (compararStrings(v.cpfDono, cpf)) {
            printf("- Placa: %s, Modelo: %s, Ano: %d\n", v.placa, v.modelo, v.ano);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("Nenhum veículo encontrado para este cliente.\n");
    fclose(arquivo);
}

//Relatório de OS por Data
void relatorioOSporData() {
    char data[20];
    printf("\n--- Relatório de OS por Data ---\n");
    lerStringValidada("Digite a data (DD/MM/AAAA): ", data, sizeof(data), 0);

    FILE *arquivo = fopen("ordem.dat", "rb");
    if (arquivo == NULL) {
        printf("Nenhuma ordem de serviço cadastrada.\n");
        return;
    }

    printf("\nOrdens de serviço abertas em %s:\n", data);
    OrdemServico os;
    int encontrou = 0;
    while (fread(&os, sizeof(OrdemServico), 1, arquivo) == 1) {
        if (compararStrings(os.dataEntrada, data)) {
            printf("- ID: %d, Placa: %s, Problema: %s\n", os.id, os.placaVeiculo, os.descricaoProblema);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("Nenhuma OS encontrada para esta data.\n");
    fclose(arquivo);
}

//Relatório de Histórico de Veículo
void relatorioHistoricoVeiculo() {
    char placa[8];
    Veiculo veiculo;

    printf("\n--- Relatório de Histórico do Veículo ---\n");
    lerStringValidada("Digite a placa do veículo: ", placa, sizeof(placa), 3);

    if (!buscarVeiculoporPlaca(placa, &veiculo)) {
        printf("Veículo não encontrado.\n");
        return;
    }

    FILE *arquivo = fopen("ordem.dat", "rb");
    if (arquivo == NULL) {
        printf("Nenhuma ordem de serviço cadastrada.\n");
        return;
    }

    printf("\nHistórico do veículo %s - %s:\n", veiculo.placa, veiculo.modelo);
    OrdemServico os;
    int encontrou = 0;
    while (fread(&os, sizeof(OrdemServico), 1, arquivo) == 1) {
        if (compararStrings(os.placaVeiculo, placa)) {
            printf("- Data: %s, Problema: %s, Status: %d\n", os.dataEntrada, os.descricaoProblema, os.status);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("Nenhum histórico encontrado para este veículo.\n");
    fclose(arquivo);
}

//Função para exibir o Menu principal
void menu() {
    printf("\n==== MENU ====\n");
    printf("1 - Cadastrar Cliente\n");
    printf("2 - Cadastrar Veiculo\n");
    printf("3 - Abrir Ordem de Servico\n");
    printf("4 - Atualizar Status\n");
    printf("5 - Relatorio Veiculos por Cliente\n");
    printf("6 - Relatorio OS por Data\n");
    printf("7 - Relatorio Historico Veiculo\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

//Função principal
int main() {
    int opcao;
    do {
        menu();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: CadastrarCliente(); break;
            case 2: cadastrarVeiculo(); break;
            case 3: AbrirOrdemServico(); break;
            case 4: atualizarStatusOS(); break;
            case 5: relatorioVeiculoCliente(); break;
            case 6: relatorioOSporData(); break;
            case 7: relatorioHistoricoVeiculo(); break;
            case 0: printf("Saindo do sistema...\n"); break;
            default: printf("Opção invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

#include <stdio.h>

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

//Struct da Ordem de Serviço
typedef struct {
    int id;
    char placaVeiculo[8];
    char dataEntrada[20];
    char descricaoProblema[200];
    Status status;
} OrdemServico;

//Função para limpar o buffer do teclado (remove caracteres sobrando no input)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Função para calcular o tamanho de uma string
int tamanhodastring(char *str) {
    int tam = 0;
    while (str[tam] != '\0') {
        tam++;
    }
    return tam;
}

//Função para copiar o conteúdo de uma string pra outra
void copiarString(char *destino, char *origem) {
    int i = 0;
    while (origem[i] != '\0') {
        destino[i] = origem[i];
        i++;
    }
    destino[i] = '\0';
}

//Função para verificar se a string contém apenas números
int ehnumero(char *str) {
    int i = 0;
    if (str[0] == '\0') return 0; //verifica se a string está vazia
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') { //verifica se tem algo que não é número
            return 0;
        }
        i++;
    }
    return 1; //tudo ok, só números
}

//Função para verificar se a string é alfanumérica (letras ou números)
int ehAlfaNumerico(char *str) {
    int i = 0;
    if (str[0] == '\0') return 0; //string vazia
    while (str[i] != '\0') {
        //Se o caractere não for letra e nem número, retorna falso
        if (!((str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= 'a' && str[i] <= 'z') ||
              (str[i] >= '0' && str[i] <= '9'))) {
            return 0;
        }
        i++;
    }
    return 1;
}

//Função para ler um número inteiro e validar entrada
int lerInt(int *destino) {
    if (scanf("%d", destino) == 1) {
        limparBuffer(); //limpa buffer após leitura
        return 1;
    }
    limparBuffer();
    return 0; //entrada inválida
}

//Função para comparar duas strings (similar ao strcmp)
int compararStrings(char *str1, char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 0; //são diferentes
        }
        i++;
    }
    //retorna 1 se as duas acabaram ao mesmo tempo (iguais)
    return str1[i] == '\0' && str2[i] == '\0';
}

//Função para buscar Cliente por CPF dentro do arquivo
int buscarClienteporCPF(char *cpf, Cliente *clienteEncontrado) {
    FILE *arquivo = fopen("clientes.dat", "rb"); //abre arquivo dos clientes
    if (arquivo == NULL) { //caso o arquivo não exista
        return 0;
    }

    Cliente temp;
    //Percorre o arquivo inteiro
    while (fread(&temp, sizeof(Cliente), 1, arquivo) == 1) {
        if (compararStrings(temp.cpf, cpf)) { //achou o CPF
            *clienteEncontrado = temp;
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
    return 0; //não achou
}

//Função para buscar Veículo por Placa dentro do arquivo
int buscarVeiculoporPlaca(char *placa, Veiculo *veiculoEncontrado) {
    FILE *arquivo = fopen("veiculos.dat", "rb");
    if (arquivo == NULL) {
        return 0;
    }

    Veiculo temp;
    //Percorre todos os veículos até achar a placa
    while (fread(&temp, sizeof(Veiculo), 1, arquivo) == 1) {
        if (compararStrings(temp.placa, placa)) {
            *veiculoEncontrado = temp;
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
    return 0; //não achou
}

//Função para cadastrar Clientes
void CadastrarCliente() {
    Cliente novoCliente, clienteExistente;

    printf("\n--- Cadastro de Cliente ---\n");
    printf("CPF (apenas numeros): ");
    scanf("%s", novoCliente.cpf);

    //Verifica se CPF já está cadastrado
    if (buscarClienteporCPF(novoCliente.cpf, &clienteExistente)) {
        printf("Erro: CPF ja cadastrado!\n");
        return;
    }

    printf("Nome completo: ");
    scanf(" %[^\n]", novoCliente.nome);
    printf("Telefone: ");
    scanf("%s", novoCliente.telefone);

    FILE *arquivo = fopen("clientes.dat", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    fwrite(&novoCliente, sizeof(Cliente), 1, arquivo);
    fclose(arquivo);
    printf("Cliente cadastrado com sucesso!\n");
}

//Função para cadastrar Veículos
void cadastrarVeiculo() {
    Veiculo novoVeiculo, veiculoExistente;
    Cliente dono;

    printf("\n--- Cadastro de Veiculo ---\n");
    printf("CPF do dono: ");
    scanf(" %[^\n]", novoVeiculo.cpfDono);

    //Verifica se cliente existe antes de cadastrar veículo
    if (!buscarClienteporCPF(novoVeiculo.cpfDono, &dono)) {
        printf("Erro! Cliente com este CPF nao existe.\n");
        return;
    }

    printf("Placa (ex: ABC01D2): ");
    scanf("%s", novoVeiculo.placa);

    //Verifica se placa já está cadastrada
    if (buscarVeiculoporPlaca(novoVeiculo.placa, &veiculoExistente)) {
        printf("Erro! Veiculo com esta placa ja esta cadastrado!\n");
        return;
    }

    printf("Modelo: ");
    scanf(" %[^\n]", novoVeiculo.modelo);
    printf("Ano: ");
    scanf("%d", &novoVeiculo.ano);

    FILE *arquivo = fopen("veiculos.dat", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de veiculos!\n");
        return;
    }

    fwrite(&novoVeiculo, sizeof(Veiculo), 1, arquivo);
    fclose(arquivo);

    printf("Veiculo cadastrado com sucesso para o cliente %s!\n", dono.nome);
}

//Função para abrir uma nova Ordem de Serviço
void AbrirOrdemServico() {
    OrdemServico novaOrdem, temp;
    Veiculo veiculo;
    int ultimoID = 0;

    printf("\n--- Abertura de Ordem de Servico ---\n");
    printf("Placa do veiculo: ");
    scanf("%s", novaOrdem.placaVeiculo);

    //Valida se veículo existe
    if (!buscarVeiculoporPlaca(novaOrdem.placaVeiculo, &veiculo)) {
        printf("Erro! Veiculo nao encontrado!\n");
        return;
    }

    //Busca o último ID registrado
    FILE *arquivo = fopen("ordem.dat", "rb");
    if (arquivo != NULL) {
        while (fread(&temp, sizeof(OrdemServico), 1, arquivo) == 1) {
            ultimoID = temp.id; //mantém o último ID lido
        }
        fclose(arquivo);
    }

    novaOrdem.id = ultimoID + 1;

    printf("Data de entrada (DD/MM/AAAA): ");
    scanf("%s", novaOrdem.dataEntrada);
    printf("Descricao do Problema: ");
    scanf(" %[^\n]", novaOrdem.descricaoProblema);
    novaOrdem.status = AGUARDANDOAVALIACAO;

    arquivo = fopen("ordem.dat", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de ordens de servico!\n");
        return;
    }

    fwrite(&novaOrdem, sizeof(OrdemServico), 1, arquivo);
    fclose(arquivo);

    printf("Ordem de servico %d aberta com sucesso para o veiculo %s!\n", novaOrdem.id, veiculo.modelo);
}

//Função para atualizar o status de uma OS existente
void atualizarStatusOS() {
    int idOS, novoStatusInt;
    FILE *arquivo = fopen("ordem.dat", "rb+");
    if (arquivo == NULL) {
        printf("Nenhuma ordem de servico encontrada.\n");
        return;
    }

    printf("\n--- Atualizar Status da Ordem de Servico ---\n");
    printf("Digite o ID da Ordem de Servico: ");
    scanf("%d", &idOS);

    OrdemServico os;
    int encontrada = 0;

    //Percorre todas as ordens até achar o ID informado
    while (fread(&os, sizeof(OrdemServico), 1, arquivo) == 1) {
        if (os.id == idOS) {
            printf("Status atual: %d\n", os.status);
            printf("Digite o novo status (0: Aguardando, 1: Em reparo, 2: Finalizado, 3: Entregue): ");
            scanf("%d", &novoStatusInt);

            //Valida se o status informado é válido
            if (novoStatusInt >= 0 && novoStatusInt <= 3) {
                os.status = (Status)novoStatusInt;
                fseek(arquivo, -sizeof(OrdemServico), SEEK_CUR);
                fwrite(&os, sizeof(OrdemServico), 1, arquivo);
                printf("Status da OS #%d atualizado com sucesso!\n", idOS);
            } else {
                printf("Status invalido.\n");
            }
            encontrada = 1;
            break;
        }
    }

    if (!encontrada) {
        printf("Ordem de servico com ID #%d nao encontrada.\n", idOS);
    }

    fclose(arquivo);
}

//Função para relatório de veículos por cliente
void relatorioVeiculoCliente() {
    char cpf[12];
    Cliente cliente;

    printf("\n--- Relatorio de Veiculos por Cliente ---\n");
    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);

    //Busca o cliente pelo CPF
    if (!buscarClienteporCPF(cpf, &cliente)) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    printf("\nVeiculos de %s:\n", cliente.nome);

    FILE *arquivo = fopen("veiculos.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de veiculos.\n");
        return;
    }

    Veiculo v;
    int encontrou = 0;

    //Percorre todos os veículos e mostra os do cliente
    while (fread(&v, sizeof(Veiculo), 1, arquivo) == 1) {
        if (compararStrings(v.cpfDono, cpf)) {
            printf("- Placa: %s, Modelo: %s, Ano: %d\n", v.placa, v.modelo, v.ano);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum veiculo encontrado para este cliente.\n");
    }

    fclose(arquivo);
}

//Função para relatório de OS por data
void relatorioOSporData() {
    char data[11];

    printf("\n--- Relatorio de OS por Data ---\n");
    printf("Digite a data (DD/MM/AAAA): ");
    scanf("%s", data);

    FILE *arquivo = fopen("ordem.dat", "rb");
    if (arquivo == NULL) {
        printf("Nenhuma ordem de servico cadastrada.\n");
        return;
    }

    printf("\nOrdens de servico abertas em %s:\n", data);

    OrdemServico os;
    int encontrou = 0;

    while (fread(&os, sizeof(OrdemServico), 1, arquivo) == 1) {
        if (compararStrings(os.dataEntrada, data)) {
            printf("- ID: %d, Placa: %s, Problema: %s\n", os.id, os.placaVeiculo, os.descricaoProblema);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhuma Ordem de Servico encontrada para esta data.\n");
    }

    fclose(arquivo);
}

//Função para relatório de histórico do veículo
void relatorioHistoricoVeiculo() {
    char placa[8];
    Veiculo veiculo;

    printf("\n--- Relatorio de Historico do Veiculo ---\n");
    printf("Digite a placa do veiculo: ");
    scanf("%s", placa);

    //Valida se veículo existe
    if (!buscarVeiculoporPlaca(placa, &veiculo)) {
        printf("Veiculo nao encontrado.\n");
        return;
    }

    FILE *arquivo = fopen("ordem.dat", "rb");
    if (arquivo == NULL) {
        printf("Nenhuma ordem de servico cadastrada.\n");
        return;
    }

    printf("\nHistorico do veiculo %s - %s:\n", veiculo.placa, veiculo.modelo);

    OrdemServico os;
    int encontrou = 0;

    //Percorre todas as OS e mostra as do veículo informado
    while (fread(&os, sizeof(OrdemServico), 1, arquivo) == 1) {
        if (compararStrings(os.placaVeiculo, placa)) {
            printf("- Data: %s, Problema: %s, Status: %d\n", os.dataEntrada, os.descricaoProblema, os.status);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum historico encontrado para este veiculo.\n");
    }

    fclose(arquivo);
}

//Função para mostrar o menu principal
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

//Função principal do programa
int main() {
    int opcao;

    //Laço principal do menu
    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: CadastrarCliente(); break;
            case 2: cadastrarVeiculo(); break;
            case 3: AbrirOrdemServico(); break;
            case 4: atualizarStatusOS(); break;
            case 5: relatorioVeiculoCliente(); break;
            case 6: relatorioOSporData(); break;
            case 7: relatorioHistoricoVeiculo(); break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0); //repete até o usuário escolher sair

    return 0;
}

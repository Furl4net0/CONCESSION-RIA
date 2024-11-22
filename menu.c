#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CLIENTES 100
#define MAX_NOME 100
#define MAX_CARROS 5
#define CPF_TAMANHO 12
#define ARQUIVO_CLIENTES "clientes.txt"

void corTexto(char *cor) {
    printf("%s", cor);
}

// Cores ANSI
#define RESET "\033[0m"
#define VERDE "\033[0;32m"
#define ROSA "\033[0;35m"
#define AZUL "\033[0;36m"
#define VERMELHO "\033[1;31m"
#define VERMELHOCLARO "\033[0;31m"


// Estrutura para Carro
typedef struct {
    int id;
    char modelo[MAX_NOME];
    float preco;
} Carro;

// Estrutura para Cliente
typedef struct {
    char cpf[CPF_TAMANHO];
    char nome[MAX_NOME];
    int ativo;  // 1 para ativo, 0 para inativo
    float rendaMensal;
    char temDivida;         // 'S' ou 'N'
    char temFinanciamento;  // 'S' ou 'N'
    Carro carroComprado;    // Carro associado ao cliente
} Cliente;

// Lista de clientes
Cliente listaClientes[MAX_CLIENTES];
int quantidadeClientes = 0;

// Funcao para validar CPF
int validarCPF(const char* cpf) {
    if (strlen(cpf) != 11) return 0;
    for (int i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) return 0;
    }
    return 1;
}


// Função para carregar clientes do arquivo
void carregarClientes() {
    FILE* arquivo = fopen(ARQUIVO_CLIENTES, "r");
    if (!arquivo) return;

    quantidadeClientes = 0;
    while (fscanf(arquivo, "%s %[^\n] %d %f %c %c %d %[^\n] %f\n",
                  listaClientes[quantidadeClientes].cpf,
                  listaClientes[quantidadeClientes].nome,
                  &listaClientes[quantidadeClientes].ativo,
                  &listaClientes[quantidadeClientes].rendaMensal,
                  &listaClientes[quantidadeClientes].temDivida,
                  &listaClientes[quantidadeClientes].temFinanciamento,
                  &listaClientes[quantidadeClientes].carroComprado.id,
                  listaClientes[quantidadeClientes].carroComprado.modelo,
                  &listaClientes[quantidadeClientes].carroComprado.preco) != EOF) {
        quantidadeClientes++;
    }

    fclose(arquivo);
}

// Função para salvar clientes no arquivo com a formatação solicitada
void salvarClientes() {
    FILE* arquivo = fopen(ARQUIVO_CLIENTES, "w");
    if (!arquivo) {
        printf("Erro ao salvar clientes!\n");
        return;
    }

    for (int i = 0; i < quantidadeClientes; i++) {
        Cliente c = listaClientes[i];
        fprintf(arquivo, 
                "Nome: %s | CPF: %s | Renda Bruta: %.2f | Tem_Financiamento: %s | Tem_Divida: %s | Carros comprados: %s (%.2f)\n", 
                c.nome, 
                c.cpf, 
                c.rendaMensal,
                (c.temFinanciamento == 'S') ? "Sim" : "Nao", 
                (c.temDivida == 'S') ? "Sim" : "Nao",
                c.carroComprado.id > 0 ? c.carroComprado.modelo : "Nenhum",
                c.carroComprado.preco);
    }

    fclose(arquivo);
    printf("Dados salvos com sucesso no arquivo.\n");
}

// Cadastro de cliente
void cadastrarCliente() {
    if (quantidadeClientes >= MAX_CLIENTES) {
        printf("Erro: Capacidade maxima de clientes atingida.\n");
        return;
    }

    Cliente novoCliente;


    corTexto(AZUL);
    printf("╔════════════════════════════════╗\n");
    printf("║ ╔==  Cadastro de Cliente   ==╗ ║\n");
    printf(" >>> Digite o CPF (11 digitos):\n");
    scanf("%s", novoCliente.cpf);
    if (!validarCPF(novoCliente.cpf)) {
        printf("CPF invalido!\n");
        return;
    }

    for (int i = 0; i < quantidadeClientes; i++) {
        if (strcmp(listaClientes[i].cpf, novoCliente.cpf) == 0) {
            printf("CPF ja cadastrado!\n");
            return;
        }
    }

    printf(" >>> Digite o nome do cliente:\n");
    scanf(" %[^\n]", novoCliente.nome);
    printf(" >>> Digite a renda mensal:\n");
    scanf("%f", &novoCliente.rendaMensal);
    printf(" >>> Cliente possui divida? (S/N):\n");
    scanf(" %c", &novoCliente.temDivida);
    printf(" >>> Cliente possui financiamento? (S/N):\n");
    scanf(" %c", &novoCliente.temFinanciamento);

    if (novoCliente.rendaMensal < 3000.0 || novoCliente.temDivida == 'S' ||  novoCliente.temDivida == 's'|| novoCliente.temFinanciamento == 'S'|| novoCliente.temFinanciamento == 's') {
        printf("Cliente nao e elegivel para\n a compra de um carro.\n");
        printf("╚════════════════════════════════╝\n");
        return;

    }

    novoCliente.ativo = 1;
    novoCliente.carroComprado.id = 0;
    strcpy(novoCliente.carroComprado.modelo, "Nenhum");
    novoCliente.carroComprado.preco = 0.0;

    listaClientes[quantidadeClientes++] = novoCliente;
    salvarClientes();
    printf("  Cliente cadastrado com sucesso!\n");
    printf("╚════════════════════════════════╝\n");
    corTexto(RESET);
}

// Listar clientes e desativar cliente
void listarClientes() {
     corTexto(AZUL);
    if (quantidadeClientes == 0) {
        printf(VERDE"\nNenhum cliente cadastrado.\n"RESET);
        return;
    }

    printf("\n╔════════════════════════════════╗\n");
    printf("║  ╔==== Lista de Clientes ===╗  ║\n");

    for (int i = 0; i < quantidadeClientes; i++) {
        Cliente c = listaClientes[i];
        printf("   Cliente %d\n", i + 1);
        printf("   CPF: %s\n", c.cpf);
        printf("   Nome: %s\n", c.nome);
        printf("   Ativo: %s\n", c.ativo ? "Sim" : "Nao");
        printf("   Carro Comprado: %s\t\t", c.carroComprado.modelo);
        printf("\n╚════════════════════════════════╝\n");
        corTexto(RESET);
    }

    // Opcao para desativar cliente
    printf("Deseja desativar algum cliente? (S/N): ");
    char escolha;
    scanf(" %c", &escolha);
    if (escolha == 'S' || escolha == 's') {
        int indice;
        printf("Digite o numero do cliente a ser desativado: ");
        scanf("%d", &indice);
        if (indice < 1 || indice > quantidadeClientes) {
            printf("Numero invalido.\n");
            return;
        }
        listaClientes[indice - 1].ativo = 0;
        salvarClientes();
        printf("Cliente desativado com sucesso!\n");
    }
}

// Simular compra de carro
void comprarCarro() {
    corTexto(VERDE);
    if (quantidadeClientes == 0) {
        printf("\nNenhum cliente cadastrado.\n");
        return;
    }
    printf("\n╔════════════════════════════════╗\n");
    printf("║  ===== Compra de Carro ======= ║\n");
    printf("\n >>> Digite o CPF do cliente: ");
    char cpfBusca[CPF_TAMANHO];
    scanf("%s", cpfBusca);

    int encontrado = -1;
    for (int i = 0; i < quantidadeClientes; i++) {
        if (strcmp(listaClientes[i].cpf, cpfBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    Cliente* cliente = &listaClientes[encontrado];
    if (!cliente->ativo) {
        printf("Cliente inativo. Nao e possivel realizar a compra.\n");
        return;
    }

    printf("\nCarros disponiveis:\n");
    Carro carros[MAX_CARROS] = {
        {1, "Sedan", 40000.0},
        {2, "SUV", 60000.0},
        {3, "Hatch", 30000.0},
        {4, "Pickup", 80000.0},
        {5, "Conversivel", 120000.0},
    };

    for (int i = 0; i < MAX_CARROS; i++) {
        printf("%d. %s - R$ %.2f\n", carros[i].id, carros[i].modelo, carros[i].preco);
    }

    printf(" Escolha o numero do carro que o cliente deseja comprar: ");
    int escolhaCarro;
    scanf("%d", &escolhaCarro);

    if (escolhaCarro < 1 || escolhaCarro > MAX_CARROS) {
        printf("\nOpcao invalida.\n");
        return;
    }

    Carro carroEscolhido = carros[escolhaCarro - 1];
    if (carroEscolhido.preco > cliente->rendaMensal * 12) {
        printf("Cliente nao possui renda suficiente para comprar este carro.\n");
        return;
    }

    cliente->carroComprado = carroEscolhido;
    salvarClientes();
    corTexto(RESET);
    corTexto(ROSA);
printf("\n╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ Compra realizada com sucesso! O cliente adquiriu o carro %s por R$%.2f    ║\n",
        carroEscolhido.modelo, carroEscolhido.preco);
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n");
    corTexto(RESET);
}

// Menu principal

void menuPrincipal() {
    carregarClientes();
    int opcao;
    do {
        corTexto(VERMELHO);
        printf("\n\n");
        printf("╔══════════════════════════════╗\n");
        printf("║ ╔===== Menu Principal =====╗ ║\n");
        printf("║ |                          | ║\n");
        printf("║ |    1. Cadastro           | ║\n");
        printf("║ |    2. Listar Clientes    | ║\n");
        printf("║ |    3. Comprar um Carro   | ║\n");
        printf("║ |    4. Sair               | ║\n");
        printf("║ ╚                          ╝ ║\n");
        printf("╚═════╗                   ╔════╝\n");
        printf("\t\tDigite sua opcao:");
        scanf("%d", &opcao);
        corTexto(RESET);

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                listarClientes();
                break;
            case 3:
                comprarCarro();
                break;
            case 4:
                printf(ROSA"Saindo...\n"RESET);
                salvarClientes();
                break;
            default:
                printf(ROSA"Opcao invalida!\n"RESET);
        }
    } while (opcao != 4);
}

int main() {
    menuPrincipal();
    return 0;
}

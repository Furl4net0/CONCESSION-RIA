#include <stdio.h>

// Funções para cada opção do menu
void opcoesDeCarros() {
    printf("Exibindo opções de carros...\n");
}

void ofertas() {
    printf("Exibindo ofertas...\n");
}

void simularFinanciamento() {
    float rendaBruta;
    char temDivida, temFinanciamento;

    // Pergunta 1: Renda Bruta
    printf("Qual sua renda bruta? ");
    scanf("%f", &rendaBruta);

    // Pergunta 2: Dívidas
    printf("Tem alguma dívida no seu nome? (S/N): ");
    scanf(" %c", &temDivida);  // Espaço antes de %c para ignorar o Enter do scanf anterior

    // Pergunta 3: Financiamentos
    printf("Tem algum financiamento no nome? (S/N): ");
    scanf(" %c", &temFinanciamento);  // Espaço antes de %c para ignorar o Enter do scanf anterior

    // Resultado da Simulação
    printf("\n===== Resultado da Simulação =====\n");
    printf("Renda Bruta: R$ %.2f\n", rendaBruta);
    printf("Dívida no nome: %s\n", (temDivida == 'S' || temDivida == 's') ? "Sim" : "Não");
    printf("Financiamento no nome: %s\n", (temFinanciamento == 'S' || temFinanciamento == 's') ? "Sim" : "Não");

    // Análise de Aprovação Básica
    if (rendaBruta >= 2000 && (temDivida == 'N' || temDivida == 'n') && (temFinanciamento == 'N' || temFinanciamento == 'n')) {
        printf("Parabéns! Você possui perfil para um financiamento.\n");
    } else {
        printf("Infelizmente, seu perfil não atende aos requisitos básicos para aprovação do financiamento.\n");
    }
}

int main() {
    int opcao;

    do {
        // Exibe o menu
        printf("\n===== MENU =====\n");
        printf("1. Opções de Carros\n");
        printf("2. Ofertas\n");
        printf("3. Simular Financiamento\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        // Executa a função correspondente à opção escolhida
        switch (opcao) {
            case 1:
                opcoesDeCarros();
                break;
            case 2:
                ofertas();
                break;
            case 3:
                simularFinanciamento();
                break;
            case 4:
                printf("Obrigado pela preferência, esperamos que nossos serviços tenham sido úteis para você!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 4); // Repete até que o usuário escolha a opção "Sair"

    return 0;
}

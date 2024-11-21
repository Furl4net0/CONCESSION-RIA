#include <stdio.h>
#include <string.h>
#include <ctype.h>


int validar_cpf(const char *cpf) {
    int i, soma, resto;
    int digitos[11];
    
    
    if (strlen(cpf) != 11) return -1; 
    for (i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) return -1; 
        digitos[i] = cpf[i] - '0'; 
    }
    
    int todos_iguais = 1;
    for (i = 1; i < 11; i++) {
        if (digitos[i] != digitos[0]) {
            todos_iguais = 0;
            break;
        }
    }
    
    if (todos_iguais) return -2;
   
    soma = 0;
    for (i = 0; i < 9; i++) {
        soma += digitos[i] * (10 - i);
    }
    resto = (soma * 10) % 11;
    if (resto == 10) resto = 0;
    if (resto != digitos[9]) return -3; 

  
    soma = 0;
    for (i = 0; i < 10; i++) {
        soma += digitos[i] * (11 - i);
    }
    resto = (soma * 10) % 11;
    if (resto == 10) resto = 0;
    if (resto != digitos[10]) return -4;

    return 1; 
}


int cpf_ja_cadastrado(const char *cpf, const char cadastrados[][12], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(cpf, cadastrados[i]) == 0) {
            return 1; 
        }
    }
    return 0; 
}



    const char *cpf = "12345678909"; 

    
    const char cadastrados[][12] = { "12345678909", "98765432100" };
    int tamanho_cadastrados = sizeof(cadastrados) / sizeof(cadastrados[0]);

    int resultado = validar_cpf(cpf);
    if (resultado == 1) {
        if (cpf_ja_cadastrado(cpf, cadastrados, tamanho_cadastrados)) {
            printf("Erro: CPF já cadastrado!\n");
        } else {
            printf("CPF válido e não cadastrado!\n");
        }
    } else {
        switch (resultado) {
            case -1:
                printf("Erro: Formato inválido. O CPF deve conter 11 dígitos numéricos.\n");
                break;
            case -2:
                printf("Erro: CPF inválido. Todos os dígitos são iguais.\n");
                break;
            case -3:
                printf("Erro: Primeiro dígito verificador inválido.\n");
                break;
            case -4:
                printf("Erro: Segundo dígito verificador inválido.\n");
                break;
            default:
                printf("Erro: CPF inválido.\n");
        }
    }

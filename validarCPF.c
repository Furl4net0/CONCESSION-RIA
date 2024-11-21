#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validar_cpf(const char *cpf) {
    int i, j, soma, resto;
    int digitos[11];
    
    
    if (strlen(cpf) != 11) return 0;
    for (i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) return 0;
        digitos[i] = cpf[i] - '0'; 
    }
    
    
    int todos_iguais = 1;
    for (i = 1; i < 11; i++) {
        if (digitos[i] != digitos[0]) {
            todos_iguais = 0;
            break;
        }
    }
    if (todos_iguais) return 0;

    
    soma = 0;
    for (i = 0; i < 9; i++) {
        soma += digitos[i] * (10 - i);
    }
    resto = (soma * 10) % 11;
    if (resto == 10) resto = 0;
    if (resto != digitos[9]) return 0;

    
    soma = 0;
    for (i = 0; i < 10; i++) {
        soma += digitos[i] * (11 - i);
    }
    resto = (soma * 10) % 11;
    if (resto == 10) resto = 0;
    if (resto != digitos[10]) return 0;

    return 1;
}

int main() {
    const char *cpf = "12345678909"; 

    if (validar_cpf(cpf)) {
        printf("CPF válido!\n");
    } else {
        printf("CPF inválido!\n");
    }

    return 0;
}

#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
typedef struct {
    char nome[50];
    char cor[20];
    int tropas;
} Territorio;

// Função para cadastrar territórios
void cadastrarTerritorio(Territorio *t) {
    printf("\n=== Cadastro de Território ===\n");
    
    printf("Nome do território: ");
    fgets(t->nome, sizeof(t->nome), stdin);
    t->nome[strcspn(t->nome, "\n")] = '\0'; // Remove o \n
    
    printf("Cor do exército: ");
    fgets(t->cor, sizeof(t->cor), stdin);
    t->cor[strcspn(t->cor, "\n")] = '\0'; // Remove o \n
    
    printf("Número de tropas: ");
    scanf("%d", &t->tropas);
    getchar(); // Limpa o buffer
}

// Função para exibir todos os territórios
void exibirMapa(Territorio territorios[], int tamanho) {
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║                     MAPA DE TERRITÓRIOS                      ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    
    for (int i = 0; i < tamanho; i++) {
        printf("║ Território %d: %-20s                       ║\n", i + 1, territorios[i].nome);
        printf("║   └─ Exército: %-15s  Tropas: %-5d       ║\n", 
               territorios[i].cor, territorios[i].tropas);
        if (i < tamanho - 1) {
            printf("╟────────────────────────────────────────────────────────────╢\n");
        }
    }
    
    printf("╚════════════════════════════════════════════════════════════╝\n");
}

int main() {
    // Vetor estático de 5 territórios
    Territorio territorios[5];
    
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║                  WAR - NÍVEL NOVATO                        ║\n");
    printf("║          Cadastro Inicial dos Territórios                  ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    // Cadastrar os 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("\n--- Território %d de 5 ---\n", i + 1);
        cadastrarTerritorio(&territorios[i]);
    }
    
    // Exibir o mapa final
    exibirMapa(territorios, 5);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    t->nome[strcspn(t->nome, "\n")] = '\0';
    
    printf("Cor do exército: ");
    fgets(t->cor, sizeof(t->cor), stdin);
    t->cor[strcspn(t->cor, "\n")] = '\0';
    
    printf("Número de tropas: ");
    scanf("%d", &t->tropas);
    getchar();
}

// Função para exibir todos os territórios
void exibirMapa(Territorio *territorios, int tamanho) {
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║                      MAPA DE TERRITÓRIOS                ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    
    for (int i = 0; i < tamanho; i++) {
        printf("║ [%d] %-25s                        ║\n", i + 1, territorios[i].nome);
        printf("║     └─ Exército: %-15s  Tropas: %-5d    ║\n", 
               territorios[i].cor, territorios[i].tropas);
        if (i < tamanho - 1) {
            printf("╟────────────────────────────────────────────────────────────╢\n");
        }
    }
    
    printf("╚════════════════════════════════════════════════════════════╝\n");
}

// Função para simular o lançamento de dados
int lancarDado() {
    return (rand() % 6) + 1; // Retorna número entre 1 e 6
}

// Função para realizar um ataque
void atacar(Territorio *territorios, int numTerr, int atacante, int defensor) {
    // Validações
    if (atacante < 1 || atacante > numTerr || defensor < 1 || defensor > numTerr) {
        printf("\n❌ Territórios inválidos!\n");
        return;
    }
    
    if (atacante == defensor) {
        printf("\n❌ Não pode atacar o próprio território!\n");
        return;
    }
    
    // Ajusta para índices do array (0-based)
    atacante--;
    defensor--;
    
    if (territorios[atacante].tropas < 2) {
        printf("\n❌ %s não tem tropas suficientes para atacar! (mínimo: 2)\n", 
               territorios[atacante].nome);
        return;
    }
    
    if (territorios[defensor].tropas <= 0) {
        printf("\n❌ %s já foi conquistado!\n", territorios[defensor].nome);
        return;
    }
    
    // Simulação da batalha
    printf("\n⚔️  BATALHA: %s (%s) VS %s (%s)\n",
           territorios[atacante].nome, territorios[atacante].cor,
           territorios[defensor].nome, territorios[defensor].cor);
    
    int dadoAtaque = lancarDado();
    int dadoDefesa = lancarDado();
    
    printf("\n🎲 Dado do Atacante: %d\n", dadoAtaque);
    printf("🎲 Dado do Defensor: %d\n", dadoDefesa);
    
    // Lógica da batalha (empate favorece atacante)
    if (dadoAtaque >= dadoDefesa) {
        territorios[defensor].tropas--;
        printf("\n✅ Atacante venceu! %s perde 1 tropa.\n", territorios[defensor].nome);
        
        // Verifica se o território foi conquistado
        if (territorios[defensor].tropas == 0) {
            printf("\n🎉 TERRITÓRIO CONQUISTADO!\n");
            printf("   %s agora pertence ao exército %s!\n", 
                   territorios[defensor].nome, territorios[atacante].cor);
            strcpy(territorios[defensor].cor, territorios[atacante].cor);
            territorios[defensor].tropas = 1; // Deixa 1 tropa no território conquistado
            territorios[atacante].tropas--; // Move uma tropa do atacante
        }
    } else {
        territorios[atacante].tropas--;
        printf("\n❌ Defensor resistiu! %s perde 1 tropa.\n", territorios[atacante].nome);
    }
}

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    
    int numTerr = 5;
    
    // Alocação dinâmica de memória
    Territorio *territorios = (Territorio *)calloc(numTerr, sizeof(Territorio));
    
    if (territorios == NULL) {
        printf("❌ Erro ao alocar memória!\n");
        return 1;
    }
    
    printf("╔══════════════════════════════════════════════════════╗\n");
    printf("║            WAR - NÍVEL AVENTUREIRO                   ║\n");
    printf("║              Batalhas Estratégicas                   ║\n");
    printf("╚══════════════════════════════════════════════════════╝\n");
    
    // Cadastrar os territórios
    for (int i = 0; i < numTerr; i++) {
        printf("\n--- Território %d de %d ---\n", i + 1, numTerr);
        cadastrarTerritorio(&territorios[i]);
    }
    
    // Loop de batalhas
    int continuar = 1;
    while (continuar) {
        exibirMapa(territorios, numTerr);
        
        printf("\n╔════════════════════════════════════════════════════════════╗\n");
        printf("║                        FASE DE ATAQUE                        ║\n");
        printf("╚════════════════════════════════════════════════════════════╝\n");
        
        int atacante, defensor;
        
        printf("\nEscolha o território ATACANTE (1-%d) ou 0 para sair: ", numTerr);
        scanf("%d", &atacante);
        
        if (atacante == 0) {
            continuar = 0;
            break;
        }
        
        printf("Escolha o território DEFENSOR (1-%d): ", numTerr);
        scanf("%d", &defensor);
        
        atacar(territorios, numTerr, atacante, defensor);
        
        printf("\nPressione ENTER para continuar...");
        getchar();
        getchar();
    }
    
    // Exibir mapa final
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║                       MAPA FINAL                             ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    exibirMapa(territorios, numTerr);
    
    // Liberar memória
    free(territorios);
    
    printf("\n✅ Jogo encerrado. Obrigado por jogar!\n");
    
    return 0;
}
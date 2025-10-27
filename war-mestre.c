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

// Definição da struct Missao
typedef struct {
    int tipo; // 1 = Destruir exército, 2 = Conquistar territórios
    char corAlvo[20];
    int territoriosNecessarios;
    char corJogador[20];
} Missao;

// ============== FUNÇÕES DE INICIALIZAÇÃO ==============

void inicializarTerritorio(Territorio *t, const char *nome, const char *cor, int tropas) {
    strcpy(t->nome, nome);
    strcpy(t->cor, cor);
    t->tropas = tropas;
}

void inicializarTerritórios(Territorio *territorios) {
    inicializarTerritorio(&territorios[0], "Brasil", "Verde", 5);
    inicializarTerritorio(&territorios[1], "Argentina", "Azul", 4);
    inicializarTerritorio(&territorios[2], "Peru", "Vermelho", 3);
    inicializarTerritorio(&territorios[3], "Chile", "Amarelo", 4);
    inicializarTerritorio(&territorios[4], "Colômbia", "Verde", 3);
}

void inicializarMissao(Missao *missao, const char *corJogador) {
    strcpy(missao->corJogador, corJogador);
    missao->tipo = (rand() % 2) + 1;
    
    if (missao->tipo == 1) {
        // Missão: Destruir exército Verde
        strcpy(missao->corAlvo, "Verde");
        missao->territoriosNecessarios = 0;
    } else {
        // Missão: Conquistar 3 territórios
        missao->territoriosNecessarios = 3;
        strcpy(missao->corAlvo, "");
    }
}

// ============== FUNÇÕES DE EXIBIÇÃO ==============

void exibirMapa(const Territorio *territorios, int tamanho) {
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

void exibirMissao(const Missao *missao) {
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║                      SUA MISSÃO                          ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    
    if (missao->tipo == 1) {
        printf("║  Destruir completamente o exército %s%-17s║\n", 
               missao->corAlvo, "");
    } else {
        printf("║  Conquistar %d territórios com o exército %s%-11s║\n",
               missao->territoriosNecessarios, missao->corJogador, "");
    }
    
    printf("╚════════════════════════════════════════════════════════════╝\n");
}

void exibirMenu() {
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║                       MENU PRINCIPAL                     ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    printf("║  [1]   Atacar território                                ║\n");
    printf("║  [2]  Verificar Missão                                  ║\n");
    printf("║  [0]  Sair do jogo                                      ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\nEscolha uma opção: ");
}

// ============== FUNÇÕES DE JOGO ==============

int lancarDado() {
    return (rand() % 6) + 1;
}

void realizarAtaque(Territorio *territorios, int numTerr) {
    int atacante, defensor;
    
    printf("\nEscolha o território ATACANTE (1-%d): ", numTerr);
    scanf("%d", &atacante);
    
    if (atacante < 1 || atacante > numTerr) {
        printf("\n❌ Território inválido!\n");
        return;
    }
    
    printf("Escolha o território DEFENSOR (1-%d): ", numTerr);
    scanf("%d", &defensor);
    
    if (defensor < 1 || defensor > numTerr) {
        printf("\n❌ Território inválido!\n");
        return;
    }
    
    if (atacante == defensor) {
        printf("\n❌ Não pode atacar o próprio território!\n");
        return;
    }
    
    // Ajusta para índices do array
    atacante--;
    defensor--;
    
    if (territorios[atacante].tropas < 2) {
        printf("\n❌ %s não tem tropas suficientes para atacar! (mínimo: 2)\n", 
               territorios[atacante].nome);
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
    
    if (dadoAtaque >= dadoDefesa) {
        territorios[defensor].tropas--;
        printf("\n✅ Atacante venceu! %s perde 1 tropa.\n", territorios[defensor].nome);
        
        if (territorios[defensor].tropas == 0) {
            printf("\n🎉 TERRITÓRIO CONQUISTADO!\n");
            printf("   %s agora pertence ao exército %s!\n", 
                   territorios[defensor].nome, territorios[atacante].cor);
            strcpy(territorios[defensor].cor, territorios[atacante].cor);
            territorios[defensor].tropas = 1;
            territorios[atacante].tropas--;
        }
    } else {
        territorios[atacante].tropas--;
        printf("\n❌ Defensor resistiu! %s perde 1 tropa.\n", territorios[atacante].nome);
    }
}

// ============== FUNÇÕES DE VERIFICAÇÃO ==============

int contarTerritoriosCor(const Territorio *territorios, int numTerr, const char *cor) {
    int count = 0;
    for (int i = 0; i < numTerr; i++) {
        if (strcmp(territorios[i].cor, cor) == 0) {
            count++;
        }
    }
    return count;
}

int exercitoExiste(const Territorio *territorios, int numTerr, const char *cor) {
    return contarTerritoriosCor(territorios, numTerr, cor) > 0;
}

int verificarMissao(const Territorio *territorios, int numTerr, const Missao *missao) {
    if (missao->tipo == 1) {
        // Missão: Destruir exército
        if (!exercitoExiste(territorios, numTerr, missao->corAlvo)) {
            printf("\n🏆 MISSÃO CUMPRIDA! Você destruiu o exército %s!\n", missao->corAlvo);
            return 1;
        } else {
            int territoriosRestantes = contarTerritoriosCor(territorios, numTerr, missao->corAlvo);
            printf("\n⏳ Missão em andamento: O exército %s ainda possui %d território(s).\n",
                   missao->corAlvo, territoriosRestantes);
            return 0;
        }
    } else {
        // Missão: Conquistar territórios
        int territorios_conquistados = contarTerritoriosCor(territorios, numTerr, missao->corJogador);
        
        if (territorios_conquistados >= missao->territoriosNecessarios) {
            printf("\n🏆 MISSÃO CUMPRIDA! Você conquistou %d territórios!\n", territorios_conquistados);
            return 1;
        } else {
            printf("\n⏳ Missão em andamento: Você possui %d/%d territórios.\n",
                   territorios_conquistados, missao->territoriosNecessarios);
            return 0;
        }
    }
}

// ============== FUNÇÃO PRINCIPAL ==============

int main() {
    srand(time(NULL));
    
    const int numTerr = 5;
    
    // Alocação dinâmica
    Territorio *territorios = (Territorio *)calloc(numTerr, sizeof(Territorio));
    
    if (territorios == NULL) {
        printf("❌ Erro ao alocar memória!\n");
        return 1;
    }
    
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║                WAR - NÍVEL MESTRE                       ║\n");
    printf("║          Missões e Modularização Total                     ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    // Inicializar territórios
    inicializarTerritórios(territorios);
    
    // Solicitar cor do jogador
    char corJogador[20];
    printf("\nEscolha a cor do seu exército: ");
    fgets(corJogador, sizeof(corJogador), stdin);
    corJogador[strcspn(corJogador, "\n")] = '\0';
    
    // Inicializar missão
    Missao missao;
    inicializarMissao(&missao, corJogador);
    
    printf("\n✅ Territórios inicializados!");
    exibirMissao(&missao);
    
    // Loop principal do jogo
    int continuar = 1;
    while (continuar) {
        exibirMapa(territorios, numTerr);
        exibirMenu();
        
        int opcao;
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                realizarAtaque(territorios, numTerr);
                break;
                
            case 2:
                exibirMissao(&missao);
                if (verificarMissao(territorios, numTerr, &missao)) {
                    printf("\n🎊 PARABÉNS! VOCÊ VENCEU O JOGO! 🎊\n");
                    continuar = 0;
                }
                break;
                
            case 0:
                printf("\n👋 Encerrando o jogo...\n");
                continuar = 0;
                break;
                
            default:
                printf("\n❌ Opção inválida!\n");
        }
        
        if (continuar && opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();
            getchar();
        }
    }
    
    // Exibir mapa final
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║                       MAPA FINAL                         ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    exibirMapa(territorios, numTerr);
    
    // Liberar memória
    free(territorios);
    
    printf("\n✅ Obrigado por jogar WAR Estruturado!\n");
    
    return 0;
}
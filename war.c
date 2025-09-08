// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
   
#include <stdio.h>
#include <string.h>

// valores definidos nos requisitos do projeto
#define MAX_TERRITORIOS 5
#define MAX_NOME 30
#define MAX_COR 10

// criação da estrutura "Territorio" usando typedef para facilitar a criação de um novo territorio.
// criação da estrutura Territorio seguindo os requisitos solicitados. Ou seja, uma estrutura com 3 atributos onde nome e corExercito têm limite de caracteres definido
typedef struct {
    char nome[MAX_NOME];
    char corExercito[MAX_COR];
    int numTropas;
} Territorio;

// funções auxiliares para deixar o código mais limpo
void cadastraTerritorios(Territorio territorios[MAX_TERRITORIOS]);
void listaTerritorios(Territorio territorios[MAX_TERRITORIOS]);

int main() {

    // Criação de um vetor de Territorios. Para armazenar os 5 diferentes territórios.
    Territorio territorios[MAX_TERRITORIOS];

    printf("Bem-vindo ao jogo WAR!\n");

    // chamada da função que cadastra os territorios
    cadastraTerritorios(territorios);

    // chamada da função que exibe territorios cadastrados
    listaTerritorios(territorios);

    return 0;
}

void cadastraTerritorios(Territorio territorios[MAX_TERRITORIOS]) {
    printf("Por favor, cadastre 5 territorios diferentes: ");

    for(int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("\nTerritorio %d\n", i + 1);

        printf("Digite o nome do territorio: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        // Remove o \n caso exista
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].corExercito);
        getchar(); // consome o '\n' deixado no buffer

        printf("Digite o numero de tropas: ");
        scanf("%d", &territorios[i].numTropas);
        getchar(); // consome o '\n' deixado no buffer
    }

    printf("\nTerritorios cadastrados com sucesso!\n");

}

void listaTerritorios(Territorio territorios[MAX_TERRITORIOS]) {
    printf("\n========================================\n");
    printf("      LISTA DE TERRITÓRIOS CADASTRADOS   \n");
    printf("========================================\n\n");

    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Território %d\n", i + 1);
        printf("  Nome           : %s\n", territorios[i].nome);
        printf("  Cor do exército: %s\n", territorios[i].corExercito);
        printf("  Nº de tropas   : %d\n", territorios[i].numTropas);
        printf("----------------------------------------\n");
    }
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.

// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
   
#include <stdio.h>
#include <stdlib.h> // necessário para alocação de memória
#include <string.h>
#include <time.h> // necessário para função rand

// valores definidos nos requisitos do projeto
#define MAX_TERRITORIOS 10 // Adicionei mais 5
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
void cadastraTerritorios(Territorio *territorios, int totalTerritorios);
void listaTerritorios(Territorio *territorios, int totalTerritorios);
void atacar(Territorio *atacante, Territorio *defensor);

int main() {
    
    // Inicializo todas as variaveis no inicio da função main para organização
    Territorio *territorios;
    territorios = (Territorio *)calloc(MAX_TERRITORIOS, sizeof(Territorio));

    int totalTerritorios = 0;
    int atacante, defensor;

    // tratamento de erro
    if (territorios == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    printf("Bem-vindo ao jogo WAR!\n");
    printf("Por favor, digite o número de territorios que deseja cadastrar, tendo no máximo %d territorios!\n", MAX_TERRITORIOS);

    scanf("%d", &totalTerritorios);
    getchar(); // limpar o \n

    // Tratamento de erro caso o usuário digite um número maior que MAX_TERRITORIOS
    if (totalTerritorios > MAX_TERRITORIOS) {
        printf("Erro: número máximo de territorios excedido. O número máximo de territorios eh de %d\n", MAX_TERRITORIOS);
        return 1;
    }

    // chamada da função que cadastra os territorios
    cadastraTerritorios(territorios, totalTerritorios);

    // chamada da função que exibe territorios cadastrados
    listaTerritorios(territorios, totalTerritorios);

    printf("Agora, escolha dois territorios. O primeiro sendo o territorio atacante e o segundo sendo o territorio defensor.\n");
    printf("Digite o número do território atacante: \n");
    scanf("%d", &atacante);

    printf("Digite o número do território defensor: \n");
    scanf("%d", &defensor);

    // tratamento de erro caso o usuário digite um número maior que totalTerritorios
    if (atacante > totalTerritorios || defensor > totalTerritorios) {
        printf("Erro: número de territorio inválido. Digite um número de territorio existente.\n");
        return 1;
    }

    atacar(&territorios[atacante - 1], &territorios[defensor - 1]); // adiciono o -1 pois o que o usuário ve no terminal é a posição do territorio. E o que tá armazenado vai ser manipulado via índice

    // Exibindo os territorios após o ataque
    listaTerritorios(territorios, totalTerritorios);

    // Liberando a memória
    free(territorios);

    return 0;
}

void cadastraTerritorios(Territorio *territorios, int totalTerritorios) {
    printf("Cadastrando novo territorio ");

    if (totalTerritorios > MAX_TERRITORIOS) {
        printf("Erro: número máximo de territorios excedido.\n");
        printf("Limite de territorios cadastrados excedido! Não é possível cadastrar um novo território.");
        return;
    }

    for(int i = 0; i < totalTerritorios; i++) {
        printf("\nTerritorio %d\n", i + 1);

        printf("Digite o nome do territorio: ");
        fgets(territorios[i].nome, MAX_NOME, stdin);
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

void listaTerritorios(Territorio *territorios, int totalTerritorios) {
    printf("\n========================================\n");
    printf("      LISTA DE TERRITÓRIOS CADASTRADOS   \n");
    printf("========================================\n\n");

    for (int i = 0; i < totalTerritorios; i++) {
        printf("Território %d\n", i + 1);
        printf("  Nome           : %s\n", territorios[i].nome);
        printf("  Cor do exército: %s\n", territorios[i].corExercito);
        printf("  Nº de tropas   : %d\n", territorios[i].numTropas);
        printf("----------------------------------------\n");
    }
}

void atacar(Territorio *atacante, Territorio *defensor) {

    // Validações para o ataque prosseguir.
    // O correto seria eu criar uma função só pra validar antes de chamar o ataque, mas como não tem necessidade por agora, vou deixar aqui dentro da função atacar.
    if (atacante->numTropas < 2) {
        printf("O território %s não possui tropas suficientes para atacar!\n", atacante->nome);
        return;
    }

    if (strcmp(atacante->corExercito, defensor->corExercito) == 0) {
        printf("O território %s já pertence ao exército %s!\n", defensor->nome, defensor->corExercito);
        return;
    }

    int atacanteTropas = atacante->numTropas;
    int defensorTropas = defensor->numTropas;

    srand(time(NULL));

    // Enquanto o atacante ter pelo menos 2 tropas e o defensor ainda não ter zerado, acontece o combate.
    // Caso o atacante tenha menos que 2 tropas, o ataque é encerrado pois, mesmo que vença, não teria pelo menos 1 tropa para enviar pro próximo território
    // E por fim, caso o numero de tropas dos defensores chegue a 0 e os atacantes tenha pelo menos 2 tropas, o ataque é um sucesso.
    while (atacanteTropas > 1 && defensorTropas > 0) {
        int ataque = rand() % 6 + 1;
        int defesa = rand() % 6 + 1;

        printf("\nAtaque: %d vs Defesa: %d\n", ataque, defesa);

        if (ataque > defesa) {
            printf("O atacante venceu o ataque! Defensores perdem 1 tropa!\n");
            defensorTropas--;
        } else {
            printf("O atacante perdeu o ataque! Atacante perde 1 tropa!\n");
            atacanteTropas--;
        }
    }

    if (defensorTropas == 0) {
        printf("\nO território %s foi conquistado pelo exército %s!\n", defensor->nome, atacante->corExercito);
        strcpy(defensor->corExercito, atacante->corExercito);
        defensor->numTropas = (int)(atacanteTropas / 2); // passando a metade das tropas do atacante para o territorio conquistado
        atacante->numTropas = 1;
    } else {
        printf("\nO território %s não foi conquistado pelo exército %s!\n", atacante->nome, defensor->corExercito);
        atacante->numTropas = 1;
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

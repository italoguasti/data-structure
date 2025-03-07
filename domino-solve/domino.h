#ifndef DOMINO_H
#define DOMINO_H

#include <stdbool.h>

// Definição da estrutura de uma peça de dominó
typedef struct
{
    int x; // Valor do lado esquerdo da peça
    int y; // Valor do lado direito da peça
} Peca;

// Definição do nó da lista duplamente encadeada
typedef struct No
{
    Peca peca;       // Peça armazenada no nó
    struct No *prox; // Ponteiro para o próximo nó
    struct No *ant;  // Ponteiro para o nó anterior
} No;

// Definição do TAD Domino (lista de peças)
typedef struct
{
    No *inicio;  // Ponteiro para o início da lista
    No *fim;     // Ponteiro para o fim da lista
    int tamanho; // Quantidade de peças na lista
} Domino;

// Operações do TAD Domino

// Cria um TAD Domino vazio
Domino *DominoCria();
// Destrói um TAD Domino, liberando a memória alocada
void DominoDestroi(Domino *domino);
// Adiciona uma peça ao TAD Domino
void DominoAdicionaPeca(Domino *domino, int x, int y);
// Imprime as peças do TAD Domino
void DominoImprime(Domino *domino);
// Verifica se é possível organizar as peças em uma ordem válida
bool DominoEhPossivelOrganizar(Domino *domino, int *sequencia);
// Imprime a sequência de peças
void ImprimeSequencia(Domino *domino, int *sequencia);

#endif // DOMINO_H
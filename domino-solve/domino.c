#include "domino.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cria um TAD Domino vazio
Domino *DominoCria()
{
    // Aloca memória para a estrutura Domino
    Domino *novoDomino = (Domino *)malloc(sizeof(Domino));
    if (novoDomino == NULL)
    {
        return NULL; // Retorna NULL se a alocação falhar
    }
    // Inicializa os campos da estrutura Domino
    novoDomino->inicio = NULL; // Lista vazia, início aponta para NULL
    novoDomino->fim = NULL;    // Lista vazia, fim aponta para NULL
    novoDomino->tamanho = 0;   // Tamanho inicial é 0
    return novoDomino;         // Retorna o novo Domino criado
}

// Destrói um TAD Domino, liberando a memória alocada
void DominoDestroi(Domino *domino)
{
    if (domino == NULL)
    {
        return; // Se o Domino for NULL, não há nada para liberar
    }
    // Percorre a lista encadeada, liberando cada nó
    No *atual = domino->inicio;
    while (atual != NULL)
    {
        No *proximo = atual->prox; // Guarda o próximo nó
        free(atual);               // Libera o nó atual
        atual = proximo;           // Avança para o próximo nó
    }
    // Libera a estrutura Domino
    free(domino);
}

// Adiciona uma peça ao TAD Domino
void DominoAdicionaPeca(Domino *domino, int x, int y)
{
    if (domino == NULL)
    {
        return; // Se o Domino for NULL, não faz nada
    }
    // Cria uma nova peça com os valores x e y
    Peca novaPeca = {x, y};
    // Aloca memória para um novo nó
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL)
    {
        return; // Se a alocação falhar, retorna sem fazer nada
    }
    // Inicializa o novo nó
    novoNo->peca = novaPeca;   // Armazena a peça no nó
    novoNo->prox = NULL;       // O próximo do novo nó será NULL (ele será o último)
    novoNo->ant = domino->fim; // O anterior do novo nó será o atual fim da lista

    // Se a lista estiver vazia, o novo nó será o início
    if (domino->inicio == NULL)
    {
        domino->inicio = novoNo;
    }
    else
    {
        // Caso contrário, o próximo do atual fim será o novo nó
        domino->fim->prox = novoNo;
    }
    // Atualiza o fim da lista para o novo nó
    domino->fim = novoNo;
    // Incrementa o tamanho da lista
    domino->tamanho++;
}

// Imprime as peças do TAD Domino
void DominoImprime(Domino *domino)
{
    // Verifica se o Domino é válido e não está vazio
    if (domino == NULL || domino->inicio == NULL)
    {
        printf("Domino vazio ou inválido!\n");
        return;
    }
    // Percorre a lista a partir do início
    No *atual = domino->inicio;
    while (atual != NULL)
    {
        // Imprime a peça no formato [x|y]
        printf("[%d|%d] ", atual->peca.x, atual->peca.y);
        atual = atual->prox; // Avança para o próximo nó
    }
    printf("\n"); // Quebra de linha ao final da impressão
}

// Função auxiliar recursiva para tentar organizar as peças
bool DominoOrganizaRecursivo(No **pecas, int n, No *atual, bool *usadas, int *sequencia, int pos)
{
    // Se todas as peças foram usadas, a sequência é válida
    if (pos == n)
    {
        return true;
    }
    // Tenta adicionar cada peça à sequência
    for (int i = 0; i < n; i++)
    {
        if (!usadas[i]) // Verifica se a peça ainda não foi usada
        {
            // Verifica se a peça pode ser adicionada à sequência atual
            if (pos == 0 || pecas[i]->peca.x == atual->peca.y)
            {
                usadas[i] = true;   // Marca a peça como usada
                sequencia[pos] = i; // Adiciona a peça à sequência
                // Tenta organizar o restante das peças recursivamente
                if (DominoOrganizaRecursivo(pecas, n, pecas[i], usadas, sequencia, pos + 1))
                {
                    return true; // Se encontrar uma combinação válida, retorna true
                }
                usadas[i] = false; // Retrocede (backtrack): desmarca a peça como usada
            }
            // Tenta inverter a peça (y, x) e verifica se ela pode ser adicionada
            if (pos == 0 || pecas[i]->peca.y == atual->peca.y)
            {
                // Inverte os valores da peça
                int temp = pecas[i]->peca.x;
                pecas[i]->peca.x = pecas[i]->peca.y;
                pecas[i]->peca.y = temp;

                usadas[i] = true;   // Marca a peça como usada
                sequencia[pos] = i; // Adiciona a peça à sequência
                // Tenta organizar o restante das peças recursivamente
                if (DominoOrganizaRecursivo(pecas, n, pecas[i], usadas, sequencia, pos + 1))
                {
                    return true; // Se encontrar uma combinação válida, retorna true
                }
                // Retrocede (backtrack): desmarca a peça como usada e restaura os valores
                usadas[i] = false;
                temp = pecas[i]->peca.x;
                pecas[i]->peca.x = pecas[i]->peca.y;
                pecas[i]->peca.y = temp;
            }
        }
    }
    // Se nenhuma combinação válida foi encontrada, retorna false
    return false;
}

// Verifica se é possível organizar as peças em uma ordem válida
bool DominoEhPossivelOrganizar(Domino *domino, int *sequencia)
{
    // Verifica se o Domino é válido e não está vazio
    if (domino == NULL || domino->tamanho == 0)
    {
        return false;
    }
    // Converte a lista encadeada em um array de ponteiros para nós
    No **pecas = (No **)malloc(domino->tamanho * sizeof(No *));
    No *atual = domino->inicio;
    for (int i = 0; i < domino->tamanho; i++)
    {
        pecas[i] = atual;    // Armazena cada nó no array
        atual = atual->prox; // Avança para o próximo nó
    }
    // Array para marcar as peças usadas
    bool *usadas = (bool *)malloc(domino->tamanho * sizeof(bool));
    memset(usadas, 0, domino->tamanho * sizeof(bool)); // Inicializa todas como não usadas

    // Tenta organizar as peças recursivamente
    bool resultado = DominoOrganizaRecursivo(pecas, domino->tamanho, NULL, usadas, sequencia, 0);

    // Libera a memória alocada
    free(pecas);
    free(usadas);

    return resultado; // Retorna o resultado da organização
}

// Imprime a sequência de peças
void ImprimeSequencia(Domino *domino, int *sequencia)
{
    // Verifica se o Domino e a sequência são válidos
    if (domino == NULL || sequencia == NULL)
    {
        return;
    }
    // Percorre a lista de peças na ordem da sequência
    No *atual = domino->inicio;
    for (int i = 0; i < domino->tamanho; i++)
    {
        No *peca = atual;   
        // Avança na lista até a posição da peça na sequência
        for (int j = 0; j < sequencia[i]; j++)
        {
            peca = peca->prox;
        }
        // Imprime a peça no formato xy
        printf("%d%d", peca->peca.x, peca->peca.y);
        if (i < domino->tamanho - 1)
        {
            printf("|"); // Separa as peças com "|"
        }
    }
    printf("\n"); // Quebra de linha ao final da impressão
}
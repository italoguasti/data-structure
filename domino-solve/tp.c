#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "domino.h"

int main()
{
    int N;
    int teste = 1;

    while (1)
    {
        // Lê o número de peças
        scanf("%d", &N);
        if (N == 0)
        {
            break; // Fim da entrada
        }

        // Cria um novo Domino
        Domino *domino = DominoCria();

        // Lê as peças e adiciona ao Domino
        for (int i = 0; i < N; i++)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            DominoAdicionaPeca(domino, x, y);
        }

        // Aloca memória para a sequência de peças
        int *sequencia = (int *)malloc(N * sizeof(int));

        // Verifica se é possível organizar as peças
        bool resultado = DominoEhPossivelOrganizar(domino, sequencia);

        // Imprime o resultado
        printf("Test %d:\n", teste);
        if (resultado)
        {
            printf("YES\n");
            // Imprime a sequência de peças
            ImprimeSequencia(domino, sequencia);
        }
        else
        {
            printf("NO\n");
        }
        printf("\n");

        // Incrementa o número do teste
        teste++;

        // Libera a memória alocada para a sequência
        free(sequencia);

        // Destrói o Domino
        DominoDestroi(domino);
    }

    return 0;
}
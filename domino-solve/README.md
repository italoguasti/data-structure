# Domino Solve

O jogo de dominós é um passatempo clássico, conhecido por sua simplicidade e pelo desafio estratégico que oferece. Nele, peças com dois valores devem ser organizadas em uma sequência, de forma que os valores 
de peças adjacentes sejam iguais. No entanto, dado um conjunto de peças, surge uma questão interessante: será que é sempre possível formar uma sequência válida com todas elas? <br>
Um exemplo de resposta para esta pergunta é visto na figura abaixo.

<br>
<div align="center">
  <img src="https://github.com/user-attachments/assets/b93513e8-14cb-4064-bf41-0ec1fd682285" style="width: 50%;"/>
</div>
<br>

Este programa resolve o jogo de dominós com base na entrada do usuário e retorna se há soluções válidas ou não e a sequência das peças organizadas.

<br>
<div align="center">
  <img src="https://github.com/user-attachments/assets/1a8d2284-6db0-4118-aa7e-f86bfc3dab85" style="width: 50%;"/>
</div>
<br>

---

## Detalhes da implementação

 - Tipo Abstrato de Dados Domino como representação da lista de peças do jogo dominó.
 - O TAD implementa as seguintes operações:
     1. DominoCria: aloca um TAD Domino que é uma lista.
     2. DominoDestroi: desaloca um TAD Domino.
     3. DominoAdicionaPeca: adiciona uma peça lida ao TAD Domino.
     4. DominoImprime: função que imprime as peças do TAD Domino de acordo com a sua posição.
     5. DominoEhPossivelOrganizar: função que tenta organizar as peças do TAD Domino em uma ordem válida. Ela retorna true se for possível e false, caso contrário de forma recursiva, utilizando backtracking.

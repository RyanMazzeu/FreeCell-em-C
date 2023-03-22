# FreeCell-em-C
FreeCell é um jogo de cartas no estilo paciência jogado com um baralho padrão de 52 cartas.
![image](https://user-images.githubusercontent.com/104333277/226992783-d60d408d-8415-47df-bd1c-51030915fae8.png)

Resumo de como jogar:
* As cartas são colocadas em 8 colunas com a face voltada para cima, você terá que tirar as cartas dessa coluna para criar as quatro pilhas;
* Na parte superior terá 4 espaços vazios (chamados de "temp"), onde você poderá armazenar cartas temporariamente durante o jogo.
* No canto superior esquerdo também há 4 espaços vazios, mas neles é onde você fará as pilhas.

Objetivo do jogo:
Fazer 4 pilhas de 13 cartas cada. Cada pilha deve ser feita na ordem crescente, do ás até o rei.

Movimentos possíveis no jogo:
* [1-Mesa para Temporario] - Movimenta 1 carta da mesa para um temp livre;
* [2-Temporario para Mesa] - Movimenta 1 carta do temp para alguma mesa;
* [3-Mesa para Naipe] - Movimenta 1 carta da mesa para algum Naipe;
* [4-Mesa para Mesa] - Movimenta 1 carta de alguma mesa para outra;
* [5-Temp para Naipe] - Movimenta 1 carta de um Temp para um Naipe
* [6-Mesa para Mesa (varias)] - Movimenta N cartas de uma mesa para outra;
* [7-Naipe para Temp] - Movimenta 1 carta de um Naipe para um Temp;
* [8-Naipe para Mesa] - Movimenta 1 carta de um Naipe para uma mesa;

OBS1: Os movimentos seguem às regras oficiais do freecell, em que uma carta só pode ser colocada sobre outra que seja de cor diferente e 1 valor acima dela e a quantidade de cartas que podem ser movimentadas se limitam a quantidade de cartas livres no temp + 1.

OBS2: Como a interface gráfica foi feita de maneira simplória para rodar no terminal do Windows, é possível que ocorra alguns glitches, tais como a interface bugar ao alterar o tamanho da janela (bastando apenas atualizar pressionando qualquer tecla).

OBS3: Os movimentos 7 e 8 são inúteis entendendo a lógica do jogo, portanto não existem na maioria dos simuladores oficiais de freecell.

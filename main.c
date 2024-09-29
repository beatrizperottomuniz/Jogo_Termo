
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int tem(char, char[], char[], int);
void sorteio(char[]);
int certo(char[], char[], char[], char[]);
int valida(char[]); // extra
int main(void) {
  char segredo[] = "     ";
  char digitado[6];
  char digitadas[][6] = {{'_', '_', '_', '_', '_'}, {'_', '_', '_', '_', '_'},
                         {'_', '_', '_', '_', '_'}, {'_', '_', '_', '_', '_'},
                         {'_', '_', '_', '_', '_'}, {'_', '_', '_', '_', '_'}};
  char certas[30] = "";
  char erradas[30] = "";
  int vidas = 0;
  int i, j;
  int acertou = 0;
  sorteio(segredo);
  printf(" O segredo sorteado %s\n\n", segredo);
  printf("\033[31mJOGO DO TERMO "
         "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_\033["
         "0m\n\n\t-> Tente adivinhar o termo\n\t-> Clique "
         "<ENTER> para submeter sua tentativa\n\t-> Você tem 6 "
         "tentativas\n\t-> A palavra deve conter 5 letras e nao pode ser "
         "digitado com acento ou numeros\n\t-> Letras amarelas = "
         "posição errada mas esta na palavra; letras verdes = "
         "\n\testa na posição correta; letra vermelhas = não tem na palavra");

  while (vidas < 6 && acertou != 1) {
    if (vidas >= 1) {
      printf("\n\n\tTENTATIVAS");
      for (i = 0; i < 6; i++) {
        printf("\n");
        for (j = 0; j < 5; j++)
          if (digitadas[i][j] == segredo[j]) {
            printf(" \033[32m%c\033[0m ", digitadas[i][j]); // codigo ANSI
          } else {
            if (tem(digitadas[i][j], segredo, digitadas[i], j)) {
              printf(" \033[33m%c\033[0m ", digitadas[i][j]);
            } else {
              printf(" \033[31m%c\033[0m ", digitadas[i][j]);
            }
          }
      }
      printf("\n");
      i = 0;
      printf("\nA palavra nao tem essas letras : ");
      while (erradas[i] != '\0') {
        printf(" %c ", erradas[i]);
        i++;
      }
      i = 0;
      printf("\nA palavra tem essas letras : ");
      while (certas[i] != '\0') {
        printf(" %c ", certas[i]);
        i++;
      }
    }
    digitado[0] = '\0';
    printf("\nDigite seu chute: ");
    scanf("%s", &digitado[0]);
    valida(digitado);
    while (valida(digitado) != 1) {
      printf("\nDigite seu chute: ");
      scanf("%s", &digitado[0]);
    }
    for (i = 0; i < 6; i++) {
      digitadas[vidas][i] = toupper(digitado[i]);
    } // senha maiusc.
    acertou = certo(digitadas[vidas], segredo, certas, erradas);

    vidas++;
  }
  printf("\n\n\tTENTATIVAS");
  for (i = 0; i < 6; i++) {
    printf("\n");
    for (j = 0; j < 5; j++)
      if (digitadas[i][j] == segredo[j]) {
        printf(" \033[32m%c\033[0m ", digitadas[i][j]); // codigo ANSI
      } else {
        if (tem(digitadas[i][j], segredo, digitadas[i], j)) {
          printf(" \033[33m%c\033[0m ", digitadas[i][j]);
        } else {
          printf(" \033[31m%c\033[0m ", digitadas[i][j]);
        }
      }
  }
  printf("\n");
  if (acertou == 1) {
    printf("\n\tVoce acertou a palavra , ela era \033[92m%s\033[0m", segredo);
  } else {
    printf("\n\tVoce errou a palavra , ela era \033[31m%s\033[0m", segredo);
  }
  printf("\n\tFIM DE JOGO");
  return 0;
}

// função para montar a lista de certas e erradas
int certo(char palavra[6], char segredo[6], char certas[5], char erradas[30]) {
  int j, i = 0;
  int erro = 1;
  int soma_certo = 0;
  char letrastr[2] = "";
  for (i = 0; i < 5; i++) {
    erro = 1;
    letrastr[0] = '\0';
    if (palavra[i] == segredo[i]) {
      sprintf(letrastr, "%c", palavra[i]); // faz o caractere virar uma string
      strcat(certas, letrastr);
      soma_certo++;
    } else {
      for (j = 0; j < 5; j++) {
        if (palavra[i] == segredo[j]) {
          erro = 0;
        }
      }
      if (erro == 0) {
        sprintf(letrastr, "%c", palavra[i]); // faz o caractere virar uma string
        strcat(certas, letrastr);
      }
      if (erro == 1) {
        sprintf(letrastr, "%c", palavra[i]); // faz o caractere virar uma string
        strcat(erradas, letrastr);
      }
    }
  }
  if (soma_certo == 5) {
    return 1;
  }
  return 0;
}

int valida(char palavra[6]) {
  int veri = 0;
  int i;
  if (strlen(palavra) == 5) {
    veri = 1;
  }
  for (i = 0; i < strlen(palavra); i++) {
    if (isalpha(palavra[i]) == 0) {
      veri = 0;
    }
  }
  return veri;
}

void sorteio(char segredo[6]) {
  int sorteio = 0;
  int c = 0;
  char nomeArq[] = "palavras.csv"; // ARQUIVO PALAVRAS
  FILE *pf;                        // ponteiro para file
  pf = fopen(nomeArq, "r");
  srand(time(NULL));
  sorteio = rand() % 799; // ela esta indo ate a metade
  if (pf == NULL) {
    printf("Algo inesperado aconteceu!");
    exit(1);
  }
  while (c < sorteio) {
    fgets(segredo, 10, pf); // leitura de uma string
    c++;
  }
  segredo[strcspn(segredo, "\n")] =
      '\0'; // strcspn da o numero do carc barra nova e faz isso ser o final da
            // string
  fclose(pf);
}

int tem(char letra, char palavra[6], char tentativa[6], int posicao) {
  // vamos rodas pela palvra ,ver se tem ela e ver se essa que tem esta na
  // digitada se retornar um pode printar com** fazer um for para ver se antes
  // teve uma igual que estava errada,dou a posição para função
  int p_letra_errada = posicao;
  int i;
  int tem = 0;
  int digitadas_certas = 0;
  int ja_colocadas = 0;
  for (i = 0; i < 5; i++) {
    if (letra == palavra[i]) {
      tem++;
    }
    if (tentativa[i] == palavra[i] && tentativa[i] == letra) {
      digitadas_certas++; // Ex quantos As estão digitados certos na palavra
    }
  }
  for (i = 0; i < posicao; i++) {
    if (tentativa[i] != palavra[i] && (tentativa[i] == letra) &&
        (digitadas_certas + ja_colocadas < tem)) {
      p_letra_errada = i;
      ja_colocadas++;
    } // vamos contar se ha um A(exemplo) na posição errada, vendo sua
      // quantidade e posição. Essa contagem vai até a posição do A que esta na
      // posição que quero. Só vai ser contado se o numero de digitadas certas e
      // as ja colocadas ão menor que o numero de As na palavra
  }
  if (digitadas_certas == tem ||
      ((posicao != p_letra_errada) &&
       (ja_colocadas + digitadas_certas ==
        tem))) { // na primeira, se vc digitou dois as e esses dois as estao
                 // certos, nao coloque * ou  se antes dessa posição tinha uma
                 // ** ou mais, e essas + as que estão certas somam a qtd de
                 // letras A por exemplo, não ha necessidade de colocar mais um
                 // A com ** mesmo que ele esteja errado
    return 0;
  } else {
    return 1;
  }
}
// ou segredo = FEBRE e digitei FEEEH checando E na posicao[3]  tem=2,digitadas
// certas=1, p_letra_errada=2 e ja_colocadas=1,
//  então 1!=2 mas 2!=3 && 1+1==2 então retorno =0
// mas no E posicao[2] tem=2,digitadas_certas=1 e p_letra_errada=2 e
// ja_colocadas=0; então 1!=2(1 condição é falsa) e 2==2 && 0+1!=2 (segunda condição é falsa), então retorno 1
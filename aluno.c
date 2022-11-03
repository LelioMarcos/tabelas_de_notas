/* 
    Implementação dos Alunos e do Sort

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"
#include "readline.h"

// Nó da árvore para o sort
struct no {
    aluno_t *item;
    no_t *left;
    no_t *right;
};

struct aluno {
    char *nome;
    int *notas;
};

// Função para criar o aluno
aluno_t *criar_aluno(int quant_notas) {
    aluno_t *result = (aluno_t*)malloc(sizeof(aluno_t));
    if (result == NULL) return NULL;

    result->nome = readline(stdin);  
    result->notas = (int*)malloc(quant_notas*sizeof(int));

    for (int i = 0; i < quant_notas; i++) {
        int nota;
        scanf("%d ", &nota);
        result->notas[i] = nota; 
    }

    return result;
}

void print_aluno(aluno_t* aluno, int notas) {
    printf("NOME: %s\n", aluno->nome);
    printf("NOTAS: ");
    
    for (int i = 0; i < notas; i++) {
        printf("%d ", aluno->notas[i]);
    }
    printf("\nMEDIA: %f", calcular_media(aluno, notas));

    printf("\n\n");
}

// Calcula a media das notas do aluno
float calcular_media(aluno_t *aluno, int quant) {
    int sum = 0;

    for (int i = 0; i < quant; i++) {
        sum += aluno->notas[i];
    }

    return (float)sum/quant;
}

// Função para comparar alunos e retorna qual dos alunos é maior que o outro.
// Retorno:
//      -1 se aluno1 > aluno2
//      1 se aluno1 < aluno2
//      0 se aluno1 == aluno2
//      Criterio:   0 - media
//                  1, 2 ... - nota n utilizada para desempate
int compara_alunos_tipo(aluno_t* aluno1, aluno_t* aluno2, int quant_provas, int *criterio) {
    float nota1, nota2;

    // Primeiramente, comparar as médias
    nota1 = calcular_media(aluno1, quant_provas);
    nota2 = calcular_media(aluno2, quant_provas);

    *criterio = 0;

    // Se forem iguais, comparar as notas uma por uma para encontrar alguma diferente 
    if (nota1 == nota2) {
        do {
            (*criterio)++;
            nota1 = aluno1->notas[(*criterio) - 1];
            nota2 = aluno2->notas[(*criterio) - 1];
        } while (nota1 == nota2);
    }

    // Fazer a comparação de fato.
    if (nota1 > nota2) return -1;
    if (nota1 < nota2) return 1;
    
    return 0;
}

// Utiliza a função compara para retornar qual aluno é maior.
aluno_t *compara_aluno(aluno_t* aluno1, aluno_t* aluno2, int quant_provas) {
    int crit;
    int compara = compara_alunos_tipo(aluno1, aluno2, quant_provas, &crit);

    if (compara == -1)  {
        return aluno1;
    } 

    return aluno2;
}

// Atualiza a árvore de comparação para remover certo aluno.
no_t *atualizar(no_t** raiz, aluno_t *aluno, int quant_provas) {
    // Se chegou no final (raiz == NULL), retornar nulo.
    if (*raiz == NULL) return NULL;

    // Se o aluno no nó atual é diferente do aluno que queremos remover, retornar esse nó.
    if ((*raiz)->item != aluno) return *raiz;

    // Chamada recursiva para os filhos do nó atual.
    no_t *esq = atualizar(&(*raiz)->left, aluno, quant_provas);
    no_t *dir = atualizar(&(*raiz)->right, aluno, quant_provas);

    // Se achou a folha do aluno que queremos remover, colocá-lo como nulo.
    if (esq == NULL && dir == NULL) {
        free(*raiz);
        *raiz = NULL;
    }
    else if (dir == NULL) (*raiz)->item = esq->item; // Se for o aluno e não tem filho na direita, raiz vai ser igual ao filho da esquerda.
    else if (esq == NULL) (*raiz)->item = dir->item; // Análogo para a o filho da direita.
    else (*raiz)->item = compara_aluno(esq->item, dir->item, quant_provas); // Se tem os dois filhos, comparar qual vai ser o que será o pai.

    return *raiz;
}

// Função que constrói a árvore de torneio.
no_t *torneioGeralSort(aluno_t **vet, int min, int max, int quant_provas) {
    int m;
    no_t *p = (no_t*)malloc(sizeof(no_t));

    // Calcula o meio do vetor, para executar para cada metade do vetor recursivamente.
    m = (min + max) / 2;
    if (min == max) { // Se for um nó folha
        p->left = NULL;
        p->right = NULL;
        p->item = vet[m];
        return p;
    } 

    // Executar para cada metade do vetor.
    p->left = torneioGeralSort(vet, min, m, quant_provas);
    p->right = torneioGeralSort(vet, m + 1, max, quant_provas);

    // Compara para escolher qual dos nós será pai;
    p->item = compara_aluno(p->left->item, p->right->item, quant_provas);

    return p;
}

void sort(aluno_t **alunos, int n, int quant_provas) {
    no_t *raiz;
    aluno_t *aluno_ant;

    raiz = torneioGeralSort(alunos, 0, n - 1, quant_provas);
    printf("Maior media: %.3f\n", calcular_media(raiz->item, quant_provas));

    for (int i = 1; i <= n; i++) {
        printf("%d. %s", i, raiz->item->nome);
        
        aluno_ant = raiz->item;
        raiz = atualizar(&raiz, raiz->item, quant_provas);  

        if (raiz != NULL) {
            printf(" - ");

            int desempate;
            compara_alunos_tipo(aluno_ant, raiz->item, quant_provas, &desempate);
            if (desempate == 0) printf("media");
            else printf("desempate: nota %d", desempate);
        }
        
        printf("\n");
    }

    free(raiz);
}

void destruir_aluno(aluno_t **aluno) {
    if (*aluno != NULL) {
        free((*aluno)->nome);
        free((*aluno)->notas);
        free(*aluno);

        *aluno = NULL;
    }
}
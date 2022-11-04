/*
    Trabalho Prático 2 - Tabela de notas
    Disciplina: SCC0201 - Introdução à Ciência de Computação II 
    Nome: Lelio Marcos
*/

#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"

int main() {
    // Começo.
    int num_alunos;
    scanf("%d", &num_alunos);

    aluno_t **alunos = (aluno_t**)malloc(num_alunos*sizeof(aluno_t*));

    if (alunos == NULL) {
        fprintf(stderr, "Erro ao alocar o vetor de alunos");
        return 1;
    } 

    int quant_provas;
    scanf("%d ", &quant_provas);

    for (int i = 0; i < num_alunos; i++) {
        alunos[i] = criar_aluno(quant_provas);

        if (alunos[i] == NULL) {
            fprintf(stderr, "Erro ao alocar aluno");
            
            for (int k = 0; k < i; k++) {
                destruir_aluno(&alunos[k]);
            }
            free(alunos);
            
            return 1;
        }
    }

    // Exibe a ordem dos alunos.
    sort(alunos, num_alunos, quant_provas);

    // Termina
    for (int i = 0; i < num_alunos; i++) {
        destruir_aluno(&alunos[i]);
    }
    free(alunos);

    return 0;
}
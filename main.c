/*
    Trabalho Prático 2 - Tabela de notas
    Disciplina: SCC0201 - Introdução à Ciência de Computação II 
    Nome: Lelio Marcos Rangel Cunha
*/

#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"

int main() {
    int num_alunos;
    scanf("%d", &num_alunos);

    aluno_t **alunos = (aluno_t**)malloc(num_alunos*sizeof(aluno_t*));

    int num_provas;
    scanf("%d ", &num_provas);

    for (int i = 0; i < num_alunos; i++) {
        alunos[i] = criar_aluno(num_provas); 
    }

    sort(alunos, num_alunos, num_provas);

    for (int i = 0; i < num_alunos; i++) {
        destruir_aluno(&alunos[i]);
    }

    free(alunos);

    return 0;
}
#pragma once

typedef struct aluno aluno_t;
typedef struct no no_t;

aluno_t *criar_aluno(int quant_notas);
void print_aluno(aluno_t* aluno, int num_provas);
float calcular_media(aluno_t *nota, int quant);
void sort(aluno_t **alunos, int n, int quant_provas);
void destruir_aluno(aluno_t **aluno);
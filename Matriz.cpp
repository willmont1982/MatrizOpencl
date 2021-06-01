int i, j;                                     /* contadores */
double sistema[3][4],                         /* matriz do sistema */
       solucao[3],                            /* vetor solução */
       coef_10, coef_20, coef_21;             /* coeficientes de triangularização */
//Leitura dos coeficientes do sistema (matriz do sistema):
for (i = 0; i < 3; i++) {
  for (j = 0; j < 4; j++) {
    printf("[%d:%d] = ", i, j);
    scanf("%lf", &sistema[i][j]);
  }
}
//Primeira etapa de triangularização:
coef_10 = -1.0 * sistema[1][0] / sistema[0][0];
coef_20 = -1.0 * sistema[2][0] / sistema[0][0];
for (j = 0; j < 4; j++) {
  sistema[1][j] += coef_10 * sistema[0][j];
  sistema[2][j] += coef_20 * sistema[0][j];
}
//Segunda etapa de triangularização:
coef_21 = -1.0 * sistema[2][1] / sistema [1][1];
for (j = 1; j < 4; j++) {    
  sistema[2][j] += coef_21 * sistema[1][j];
}
//Impressão do sistema resultante:
printf("\n");
printf("Sistema resultante:\n");
for (i = 0; i < 3; i++) {
  for (j = 0; j < 4; j++) {
    printf("%5.2lf ", sistema[i][j]);
  }
  printf("\n");
}
//Cálculo das soluções:
solucao[2] = (sistema[2][3]) / sistema[2][2];
solucao[1] = (sistema[1][3] - (solucao[2] * sistema[1][2])) / sistema[1][1];
solucao[0] = (sistema[0][3] - (solucao[2] * sistema[0][2]) - (solucao[1] * sistema[0][1])) / sistema[0][0];

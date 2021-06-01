
__kernel void mmul(
    const int N,
    __global float* A,
    __global float* B,
    __global float* C)
{
    int k;
    int i = get_global_id(0);
    int j = get_global_id(1);
    float tmp;
    const unsigned int indice_t = id(0);
    const unsigned int tam_bloco = tamanho_bloco;
    const unsigned int c = (indice_t / sat_bs) % sat_bs + 1;
    const unsigned int r = indice_t % a + 1;
    unsigned int block = id(0) / (a*a);
    if ((i < N) && (j < N))
    {
        tmp = 0.0;
        for (k = 0; k < N; k++)
            tmp += A[i*N+k] * B[k*N+j];
        C[i*N+j] = tmp;
    }
    id_linha = idx_t % linhas_validas;
    id_coluna = idx_t / colunas_validas;
    p_coluna = p[colunas_validas[id_coluna]];
    u_coluna = p[colunas_validas[id_coluna] + 1];
    cr = p_coluna + id_coluna;
    if(cr < lr){
        for(unsigned int i = 0; i < nr; i++){
            submat[nr * id + i] = 0.0;
            if(I[cr] == vi[i]){
                submat[nr * ri + i] = valor[cr];
                 if(indice_t < nr){
        residuo[idx_t] = 0.0;
        conjugado[idx_t] = 0.0;
        for(unsigned int i = 0; i < nr; i++){
            normalizar_linha += submat[nr * oidx + i] * submat[nr * oidx + i];
        }
        if(normalizear_linha != 0){
            x0[indice_t] = submat[nr * oidx + idx_t] / normalizr_linha;
        }
}

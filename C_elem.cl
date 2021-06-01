
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
    const unsigned int idx_t = get_local_id(0);
    const unsigned int bs = block_size;
    const unsigned int sat_bs = 2;
    const unsigned int c = (idx_t / sat_bs) % sat_bs + 1;
    const unsigned int r = idx_t % sat_bs + 1;
    unsigned int block = get_global_id(0) / (sat_bs*sat_bs);
    if ((i < N) && (j < N))
    {
        tmp = 0.0;
        for (k = 0; k < N; k++)
            tmp += A[i*N+k] * B[k*N+j];
        C[i*N+j] = tmp;
    }
    row_idx = idx_t % n_valid_rows;
    col_idx = idx_t / n_valid_rows;
    first_col_in_row = colPtr[valid_rows_idx[row_idx]];
    last_col_in_row = colPtr[valid_rows_idx[row_idx] + 1];
    current_col_in_row = first_col_in_row + col_idx;
    if(current_col_in_row < last_col_in_row){
        for(unsigned int i = 0; i < n_valid_rows; i++){
            submat[n_valid_rows * row_idx + i] = 0.0;
            if(I[current_col_in_row] == valid_rows_idx[i]){
                submat[n_valid_rows * row_idx + i] = nnzValues[current_col_in_row];
                 if(idx_t < n_valid_rows){
        residual[idx_t] = 0.0;
        conjugate[idx_t] = 0.0;
        for(unsigned int i = 0; i < n_valid_rows; i++){
            normalize_x0 += submat[n_valid_rows * one_row_idx + i] * submat[n_valid_rows * one_row_idx + i];
        }
        if(normalize_x0 != 0){
            x0[idx_t] = submat[n_valid_rows * one_row_idx + idx_t] / normalize_x0;
        }
}

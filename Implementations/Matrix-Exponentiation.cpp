struct matrix{
    ll mat[100][100];
    int dim;
    matrix(){};
    matrix(int d){
        dim = d;
        for(int i=0;i<dim;i++)
            for(int j=0;j<dim;j++)
                mat[i][j] = 0;
    }
    /// mat = mat * mul
    matrix operator *(const matrix &mul){
        matrix ret = matrix(dim);
        for(int i=0;i<dim;i++){
            for(int j=0;j<dim;j++){
                for(int k=0;k<dim;k++){
                    ret.mat[i][j] += (mat[i][k])*(mul.mat[k][j]) ;
                    ret.mat[i][j] %= MOD ;
                }
            }
        }
        return ret ;
    }
    matrix operator + (const matrix &add){
        matrix ret = matrix(dim);
        for(int i=0;i<dim;i++){
            for(int j=0;j<dim;j++){
                ret.mat[i][j] = mat[i][j] + add.mat[i][j] ;
                ret.mat[i][j] %= MOD ;
            }
        }
        return ret ;
    }
    matrix operator ^(int p){
        matrix ret = matrix(dim);
        matrix m = *this ;
        for(int i=0;i<dim;i++) ret.mat[i][i] = 1 ; /// identity matrix
        while(p){
            if( p&1 ) ret = ret * m ;
            m = m * m ;
            p >>= 1 ;
        }
        return ret ;
    }
};

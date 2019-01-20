/*
 * セグメント木のノードに行列を持って与えた範囲の行列積を返す
 *
 * もし一括でノードを更新するならall_updateを使うとO(N)で全てのノードが更新される
 */

/* T: 行列の要素の型 , MatrixSize:行列の大きさ */
template<typename T,int MatrixSize>
class MatrixSegmentTree{
    public:
        using Matrix = vector<vector<T>>;

        Matrix mul(const Matrix& mat1, const Matrix& mat2)const {
            Matrix ret(MatrixSize,vector<T>(MatrixSize,0));

            for(int i=0;i<MatrixSize;i++){
                for(int j=0;j<MatrixSize;j++){
                    for(int k=0;k<MatrixSize;k++){
                        ret[i][j] += mat1[i][k] * mat2[k][j];
                    }
                }
            }
            return ret;
        }

        /* 行列の単位元 */
        Matrix getUnit(){
            Matrix ret(MatrixSize,vector<T>(MatrixSize,0));
            for(int i=0;i<MatrixSize;i++){
                ret[i][i]=1;
            }
            return ret;
        }


        int n;
        vector<Matrix> data;
        const Matrix unit = getUnit();

        MatrixSegmentTree(){}
        MatrixSegmentTree(int n_){
            init(n_);
        }

        void init(int n_){
            n = 1;
            while(n < n_) n <<= 1;
            data.resize(2*n-1);
            for(int i=0;i<2*n-1;i++) data[i] = unit; 
        }

        void update(int idx,const Matrix& mat){
            idx += n-1;
            data[idx] = mat;
            while(idx>0){
                idx = (idx-1)/2;
                data[idx] = mul(data[idx*2+1],data[idx*2+2]);
            }
        }

        void all_update(){
            for(int i=n-2;i>=0;i--){
                data[i] = mul(data[i*2+1],data[i*2+2]);
            }
        }

        Matrix query(int a,int b,int k,int l,int r) const {
            if(r<=a or b<=l) return unit;
            if(a<=l and r<=b) return data[k];
            else return mul(query(a,b,k*2+1,l,(l+r)/2),query(a,b,k*2+2,(l+r)/2,r));
        }

        Matrix get(int idx) const {
            return data[idx+n-1];
        }

        Matrix query(int a,int b) const {
            return query(a,b,0,0,n);
        }
};

// verify DDCC2019 本戦D

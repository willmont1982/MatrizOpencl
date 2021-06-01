class SparseMatrix
{
 int numRows, numColumns;
 Data **data;
public:
 //construtor e destrutor
 SparseMatrix(int nl, int nc);//inicializa matriz
 ~SparseMatrix();//desaloca memoria
 //funções membro
 double& operator () (int i, int j);
 double& InsertElement(Element*,int,int,int);

};
class ComplexSparseMatrix
{
public :
// construtor e destrutor

// funções membro
  vector operator*(vector&);
  void GetColumn(int,vector&,int[],int&); 
  void GetRow(int,vector&,int[],int&); 
  vector SolveLower(vector&);
  vector SolveTransLower(vector&);
  ComplexSparseMatrix& Factorize(ComplexSparseMatrix&);

};
void ComplexSparseMatrix ::
 SolveCOCG (ComplexSparseMatrix& A, Vector& b)
{
 ComplexSparseMatrix T(A.numrows,A.numcolumns);
 // cria e inicializa com zero vetores com mesma 
//dimensão do vetor b
      Vector r(b.size,0), rb(b.size,0), x(b.size,0), p(b.size,0),
      z(b.size,0), w(b.size,0), u(b.size,0), ub(b.size,0);
      complex e, e_ant, mi, alpha, y, beta;
      r = b - A*x;
      z = (T.Factorize(A)).SolveLower(r);
      w =T.SolveTransLower(z);
         e = (conjugado(r)).prod(w);
      do {
         p = w + p*beta;
         u = A*p;
         ub = conjugado(u);
         mi = ub.prod(p);
         alpha = e / mi;
         x += p*alpha;
         r -= u*alpha;
         rb = conjugado(r);
         y = r*r;
 if(abs(y) > 1.E-7)
 {
     z = T.SolveLower(r);
     w = T.SolveTransLower(z);
     e = rb.prod(w);
     beta = e / e_ant;
 }
} while(abs(y) > 1.E-7);
    b = x;
 }

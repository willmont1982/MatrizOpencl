 complex Vector :: operator * (Vector &c)
{
 complex aux = 0;
 for(int i=1;i<=c.size;++i)
 if((vet[i] !=0) || (c.vet[i] !=0))
 aux += *(vet+i)* (c.vet[i]);
 return aux;
}
Vector ComplexSparseMatrix :: operator * (Vector &c)
{ 
 Element *elem;// ponteiro para estrutura Element
 Vector result(numrows,0);// inicializa com zeros o vetor de 
 // dimensão numrows ( no. de linhas da matriz A )
 for(i = 1;i<=numrows;++i)
 for(elem = elementRow[i];elem!=NULL;elem = elem->next)
{
 result.vet[i] += elem->value *c.vet[elem->column];
 if(elem->column != i)
 result.vet[elem->column] += elem->value * c.vet[i];
 }
 return result; 
 }

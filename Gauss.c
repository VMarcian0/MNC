#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

void leitura(float *m,int *ord);
void exibir(float *m, int *ord);
void mat_gauss(float *m, int *ord);
void res_sis(float *m,float *x, int *ord);

int main(){
	setlocale(LC_ALL,"Portuguese");
	float mat[3][4];//Matriz com as informações
	float x[4]={0};//vetor com os valores de Xn, com tamanho de n+1 e inicializado com 0 para não alterar as subtrações
	int tam;//tamanho do sistema quadrado inserido pelo usuário
	leitura(*mat , &tam);
	system("cls");
	printf("\n----A Matriz Original:----\n\n");
	exibir(*mat , &tam);
	mat_gauss(*mat, &tam);
	printf("\n----A Matriz Transformada em Gauss:----\n\n");
	exibir(*mat, &tam);
	res_sis(*mat,x,&tam);
	return 0;
}//main

void leitura(float *m, int *ord){
	int i,j;
		do{
	printf("\nInsira a ordem da matriz, onde 3ª é a maior possível:\t");
	scanf(" %d",ord);
		}while(*ord<=1 || *ord>3);//laço de verificação
	for(i=0;i<*ord;i++){
		for(j=0;j<*ord+1;j++){
			if(j==*ord){
				printf("\nInsira o termo independente da %d linha:\t",i+1);
			}
			else{
				printf("\nInsira o coeficiente de X%d%d:\t",i+1,j+1);
			}
			scanf("%f",m+i*(*ord+1)+j);//conferido já
		}
	}
}//leitura

void exibir(float *m, int *ord){
	int i,j;
	printf("\n");
	for(i=0;i<*ord;i++){
		for(j=0;j<*ord+1;j++){
			if(j==*ord){
				printf("|\t");
			}
			printf("%.3f\t",*(m+i*(*ord+1)+j));
		}
		printf("\n");
	}
	printf("\n");
}//exibir

void mat_gauss(float *m, int *ord){
	int i,j,k;
	float mul;//multiplicador
	for (k=0;k<*ord-1;k++){
		for (i=k+1; i<*ord;i++){
		mul=-1*(*(m+i*(*ord+1)+k)/(*(m+k*(*ord+1)+k)));
			for (j=0;j<*ord+1;j++){
		*(m+i*(*ord+1)+j)=(*(m+k*(*ord+1)+j)*mul)+*(m+i*(*ord+1)+j);
						}
					}
				}
}//Transforma a matriz em uma matriz Triangular ascendente

void res_sis(float *m,float *x, int *ord){
	int i,j;
	float termo;//termo independente
	for(i=*ord-1;i>=0;i--){
		termo=0;
		termo=*(m+i*(*ord+1)+*ord);
		for(j=*ord-i;j>=0;j--){
			termo-=*(x+j)*(*(m+i*(*ord+1)+j));
			/*
			Subtração dos valores de Xn do termo independente
			*/
		}
			*(x+i)=(termo/(*(m+i*(*ord+1)+i)));
			/*
			divisão do termo independente, subtraído dos outros valores de Xn
			*/
	}
	printf("\n----------Conjunto Solução:------------\n\n");
	for(i=0;i<*ord;i++){
		printf("X%d = %.3f\n",i,*(x+i));
	}
}//ressolução do sistema

#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<ctype.h>
void receberTabela(double *x,double *y,double *Inter,int *count); //função que recebe os valroes de X e f(X)
void exibirTabela(double *x,double *y,double *Inter,int *count); //função que exibe todos os valores inseridos como também mostra o intervalo I
void receberG(double *g,double *Inter);//função que recebe o valor de x à ser interpolado verificando com relação ao intervalo I
void laGran(double *x,double *y,double *Inter,int *count,double *g);//função que executa a somatória e exibe o resultado Lk(x)
double BLn(double *x,double *y,int *n,int *count,double *g);//função que faz o produtório
int main(){
	setlocale(LC_ALL,"Portuguese");
	int cont=0,*ptr_cont;//contador para determinar o fim dos vetores
	double x[128],Fx[128];//vetores para armazenar os dados
	double I[2];// valores para armazenar o intervalo I, para modos de verificação ao digitar X desejado para a interpolação
	double g,*ptr_g;//valor à ser interpolado
	ptr_cont=&cont;//incialização de ponteiro
	ptr_g=&g;//incialização de ponteiro
	receberTabela(x,Fx,I,ptr_cont);
	system("cls");
	exibirTabela(x,Fx,I,ptr_cont);
	laGran(x,Fx,I,ptr_cont,ptr_g);
	system("pause");
	return 0;
}

void receberTabela(double *x,double *y,double *Inter,int *count){
	char op='S',*ptr_op;
	ptr_op=&op;
	printf("\t------Interpolação Polinomial – Forma de Lagrange------\n\n\nInsira os números em rol crescente, na forma de: x [espaço] f(x).\nNúmeros com decimais devem ser inseridos com vírgula ao invés de ponto, 3,33 ao invés de 3.33\n\n");
	do{
	printf("Insira os valores da posição %d da tabela de pontos:\n",*count);
	fflush(stdin);
	scanf("%lf %lf",x+*count,y+*count);
		if(*count>=1){
			if(*(x+*count)<=*(x+*count-1)){//verificação de digitação em rol crescente
				*count-=1;
				printf("\n\nERRO\tDigite os pontos X em rol crescente!\n\n");
			}
		}
		*count+=1;
		if(*count>1){//verificação de continuidade. Ocorre em count>1 pois são nessesários pelo menos 2 pontos
			do{
			printf("\n\nDeseja continuar inserindo pontos para a interpolação? S-sim|N-não:\t");
			fflush(stdin);
			scanf("%c",ptr_op);
			}while(toupper(*ptr_op)!='S' && toupper(*ptr_op)!='N');//verificação
			printf("\n");
		}
		if(toupper(*ptr_op)=='N'){ break; //condição para quebrar o laço
		}
	}while(*count<128);
	*Inter=*x;//primeiro valor do intervalo
	Inter+=1;
	*Inter=*(x+*count-1);//ultimo valor do intervalo
}//receberTabela

void exibirTabela(double *x,double *y,double *Inter,int *count){
	
	int i;
	printf("Entrada\t");
	for(i=0;i<*count;i++){ printf("\t#%d\t",i);//entrada
	}
	printf("\nX=\t");
	for(i=0;i<*count;i++){ printf("\t%.3lf\t",*(x+i));//valor de x
	}
	printf("\nf(x)=\t");
	for(i=0;i<*count;i++){printf("\t%.3lf\t",*(y+i));//valor de f(x)
	}	
	printf("\n\nI=[%.3lf ; %.3lf]\n",*Inter,*(Inter+1));
}//exibirTabela

void receberG(double *g,double *Inter){
	printf("Insira o valor de X que deseja interpolar:\n");
	do{
		fflush(stdin);
		scanf("%lf",g);
		if(*g<*Inter || *g>*(Inter+1)){
			printf("\nO valor %.3lf Digitado não pertence ao Intervalo I[%.3lf ; %.3lf]\n",*g,*Inter,*(Inter+1));
		}
	}while(*g<*Inter || *g>*(Inter+1));
}//receberG

void laGran(double *x,double *y,double *Inter,int *count, double *g){
do{
	receberG(g,Inter);
	char vef,*ptr_vef;
	int i,*ptr_i;
	double laG=0,*ptr_laG;
	double Ln,*ptr_Ln;
	ptr_i=&i;
	ptr_vef=&vef;
	ptr_Ln=&Ln;
	ptr_laG=&laG;
	for(i=0;i<*count;i++){
		Ln=BLn(x,y,ptr_i,count,g);//Li -> elemento que é usado na somatória
		*ptr_laG+=(*(y+i))*(*ptr_Ln);
	}
	printf("\nLk(x) = %.3lf onde x = %.3lf\n",*ptr_laG,*g);
		do{
		printf("\n\nDeseja continuar inserindo valores de x para a interpolação? S-sim|N-não:\t");
		fflush(stdin);
		scanf("%c",ptr_vef);
		}while(toupper(*ptr_vef)!='S' && toupper(*ptr_vef)!='N');//verificação
			printf("\n");
		if(toupper(*ptr_vef)=='N'){ break; //condição para quebrar o laço
		}
}while(*(Inter+1)>*Inter);
}//laGran

double BLn(double *x,double *y,int *n,int *count,double *g){
	int i;
	double LnR=1,*ptr_LnR;//valor do dividendo
	double Lnr=1,*ptr_Lnr;//valor do divisor
	ptr_LnR=&LnR;
	ptr_Lnr=&Lnr;
	for(i=0;i<*count;i++){//laço do Dividendo
		if(i==*n){ //o dividendo não recebe Xn de Ln
		}
		else{(*ptr_LnR)*=(*g-*(x+i));//operação do dividendo
		}
	}
	for(i=0;i<*count;i++){//Laço do Divisor
		if(i==*n){//o divisor não recebe Xn de Ln para o produto não ser 0
		}
		else{(*ptr_Lnr)*=(*(x+*n)-*(x+i));//operação do divisor
		}
	}
	return ((*ptr_LnR)/(*ptr_Lnr));//retorno de Ln(x)
}//BLn

//projeto atualizado em 08/06


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

bool verificaSim (char op)
{
    if (op == 'S' || op == 's')
        return true;
    else
        return false;
}

void exibe (float coeficientes[], int expoentes[], int grau, float *valores, int conta_val, bool deriva, float div_coeficientes[])
{
    if (deriva != true)
    {
     for(int i = grau; i > 1; i--) 
        {
            if(i != grau && coeficientes[i] > 0) 
                printf(" + ");
            else if (i != grau && coeficientes[i] < 0)
                printf(" - ");
            if (coeficientes[i] == 1 && div_coeficientes[i] == 1)
                printf("x^%d",expoentes[i]);
            else if (coeficientes[i] == 1 && div_coeficientes[i] == 1)
                printf("%0.fx^%d",fabsf(coeficientes[i]),expoentes[i]);
            else if (coeficientes[i] != 1 && div_coeficientes[i] == 1)
                printf("%.0fx^%d",fabsf(coeficientes[i]),expoentes[i]);
            else if (coeficientes[i] == 1 && div_coeficientes[i] != 1)
                printf("(x^%d)/%.0f",expoentes[i],div_coeficientes[i]);
            else if (coeficientes[i] != 1 && div_coeficientes[i] != 1)
                printf("(%0.fx^%d)/%.0f",fabsf(coeficientes[i]),expoentes[i],div_coeficientes[i]);
        }
        for(int i = 0; i < conta_val; i++) 
        {
            if ((*(valores + i)) > 0)
                printf(" + ");
            else if ((*(valores + i)) < 0)
                printf(" - ");
            printf("%.0f",fabsf((*(valores + i))));
        }
    }
    else
    {
         for(int i = grau; i > 1; i--) 
            {
                if(i != grau && coeficientes[i] > 0) 
                    printf(" + ");
                else if (i != grau && coeficientes[i] < 0)
                    printf(" - ");
                if (coeficientes[i] == 1)
                    printf("x^%d",expoentes[i]);
                else if (coeficientes[i] != 1)
                    printf("%.2fx^%d",fabsf(coeficientes[i]),expoentes[i]);
            }
    }
        
}

void divisao (float coeficientes[], float div_coeficientes[], int grau)
{
    for (int i = grau; i > 1; i--)
        coeficientes[i] /= div_coeficientes[i];
}


void derivar (float coeficientes[], int expoentes[], int grau)
{
    //derivando elementos em função de X usando a "regra da potência"
    for(int i = grau; i > 1; i--)
        {
            coeficientes[i] *= expoentes[i];
            expoentes[i]--;
        }
}

float calculaF_derivada (float coeficientes[], int expoentes[], int grau, float funcional)
{
    float expressao=0;
    for (int i = grau; i > 1; i--)
        expressao += coeficientes[i] * (pow(funcional, expoentes[i]));
    return expressao;
}

float calculaF_inicial (float coeficientes[], int expoentes[], int grau, float funcional, float *valores, int conta_val)
{
    float expressao=0;
    for (int i = grau; i > 1; i--)
        expressao += coeficientes[i] * (pow(funcional, expoentes[i]));
    for (int i = 0; i < conta_val; i++)
        expressao += valores[i];
    return expressao;
}

void retaTangente (float m, int x0, int y0) // y = m(x-x0) + y0
{
    float mx = m*(-x0);// y = mx -m*x0
    printf("%.2fx + %.2f",m,(mx + y0)); // y = mx - m*x0 + y0
}


void clonar (float coeficientes[], int expoentes[], float coeficientes2[], int expoentes2[], int grau)
{
    for (int i = grau; i > 1; i--)
        {
            coeficientes2[i] =  coeficientes[i];
            expoentes2[i] =  expoentes[i];
        }
}

int main() {
    int grau,total,conta_val=0,tamanho=8;//tamanho inicial do vetor valores: 8 floats
    bool cancela = false; //cancela o cálculo caso alguma informação esteja incorreta
    float expressao,funcional,valor=-1,*valores,*div_valores;
    valores = (float*)malloc(tamanho*sizeof(float));//alocação do tamanho inicial do vetor valores
    char op;   //usada para interpretar as opções "Sim" e "Não" 
    printf("Digite o grau do polinômio: ");
    scanf(" %d", &grau);
    float coeficientes[grau + 1],coeficientes2[grau + 1]; //criação dos vetores dos coeficientes de X
    float div_coeficientes [grau +1]; //criação dos vetores dos divisores desses coeficientes
    int expoentes[grau + 1],expoentes2[grau + 1]; // criação dos vetores dos expoente de X
    if (grau > 1)
    {
        for(int i = grau; i > 1; i--) 
        {
            expoentes[i] = i;
            printf("Digite o coeficiente de x^%d: ", expoentes[i]);
            scanf("%f", &coeficientes[i]);
        }

        // clonando os vetores para realizar as contas separadamente
        clonar(coeficientes,expoentes,coeficientes2,expoentes2,grau);
        
        printf("Esse polinômio possui algum elemento em função de X que está sendo dividido?    Digite (S) para Sim e (N) para Não: "); //pergunta ao usuário
        scanf(" %c",&op);

        if (verificaSim(op) == true)
        {
            while ((op = getchar()) != '\n' && op != EOF) {} //limpa o buffer de "op"
            for (int i = grau; i > 1; i--)
                {
                    printf("O elemento %.0fx^%d está sendo dividido? Digite o valor do divisor ou \"0\" para ir para o próximo coeficiente em função de X.",coeficientes[i],expoentes[i]);
                    scanf("%f",&valor);
                    if (valor != 0)
                        div_coeficientes[i] = valor;
                    else
                        div_coeficientes[i] = 1;
                }
            divisao(coeficientes2,div_coeficientes,grau); //coeficientes 2 agora possui o resultado de cada divisão.
            valor = -1; //reseta a variável valor para o estado inicial. O valor -1 será utilizado para saber se foi ou não inserido um novo valor.
        }
        else
        {
            for (int i = grau; i > 1; i--)
                div_coeficientes[i] = 1; //define por padrão que todos os coeficientes são 1.
        }
    }
    else
        cancela = true;
    if (cancela != true)
    {
        printf("Esse polinômio possui algum elemento que não esteja em função de X?    Digite (S) para Sim e (N) para Não: "); //pergunta ao usuário
        scanf(" %c",&op);
        if (verificaSim(op) == true)
        {
            while ((op = getchar()) != '\n' && op != EOF) {} //limpa o buffer de "op"
            while (valor != 0)
                {
                    printf("Digite os elementos (separados por 1 espaço). Digite 0 para encerrar a adição de elementos: ");
                    scanf("%f", &valor);
                    if (valor == 0) 
                    {
                        break;
                    }
                    if (conta_val == tamanho)
                        {
                            tamanho *= 2;
                            float *temp = realloc(valores, tamanho * sizeof(float));            // Redimensiona o vetor se necessário
                            if (temp == NULL) 
                                {
                                    printf("Erro ao realocar memória. Reinicie o programa.\n");
                                    free(valores);
                                    return 1;
                                }
                             valores = temp;
                        }

                    valores[conta_val++] = valor;

                }
        }
        //exibe
        printf("\n\n\nFunção digitada:  f(x) = ");
        exibe(coeficientes,expoentes,grau,valores,conta_val,false,div_coeficientes);
        //deriva
        derivar(coeficientes2,expoentes2,grau);
        //exibe derivada
        printf("\n\n                  f'(x) = ");
        exibe(coeficientes2,expoentes2,grau,valores,conta_val,true,div_coeficientes);
        printf("\n\n\nDeseja calcular o valor funcional f'(a)?    Digite (S) para Sim e (N) para Não: "); //pergunta ao usuário.
        scanf(" %c",&op);
        if (verificaSim(op) == true)
        {
            while ((op = getchar()) != '\n' && op != EOF) {} //limpa o buffer de "op"
            printf("Qual o valor?: ");
            scanf("%f",&funcional);
            printf("\n\n\na = %.2f    ",funcional);
            //calculando sem derivar e exibindo
            printf("f(%.2f) = %.2f",funcional,calculaF_inicial(coeficientes,expoentes,grau,funcional,valores,conta_val));
            //calculando a derivada com o funcional e exibindo;
            printf("        f'(%.2f) = %.2f",funcional,calculaF_derivada(coeficientes2,expoentes2,grau,funcional));
            //exibindo P
            printf("        P = (%.2f,%.2f)",funcional,calculaF_inicial(coeficientes,expoentes,grau,funcional,valores,conta_val));
        }
        printf("\n\n\nDeseja calcular a equação da reta tangente ao gráfico de f(x) no ponto P = (a,f(a))?    Digite (S) para Sim e (N) para Não: "); //pergunta ao usuário.
        scanf(" %c",&op);
        if (verificaSim(op) == true)
        {
            while ((op = getchar()) != '\n' && op != EOF) {} //limpa o buffer de "op"
            printf("Para qual valor de a gostaria de calcular?: ");
            scanf("%f",&funcional);
            printf("\n\n\nA equação da reta tangente ao gráfico de f(x) = ");
            exibe(coeficientes,expoentes,grau,valores,conta_val,false,div_coeficientes);
            float m = calculaF_derivada(coeficientes2,expoentes2,grau,funcional);
            float y0 = calculaF_inicial(coeficientes,expoentes,grau,funcional,valores,conta_val);
            printf(" no ponto P = (%.2f,%.2f) será y = ",funcional,y0);
            retaTangente(m,funcional,y0);
        }
    }
    else
        printf("Erro. Foi digitado um grau menor ou igual a 1.");
    free(valores);
    return 0;
}

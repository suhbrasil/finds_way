/*Marcella Scholze , Suzana Pachelle , Raissa Machado*/

#include<stdio.h>
#include<stdlib.h>
#include"imagem.h"
#include"trabalho3.h"

#define CAMINHO -1
#define PAREDE -2

void binariza(Imagem1C* in, Imagem1C* out);
void normaliza(Imagem1C* in, Imagem1C* out);
void preencheMatrizCusto (int** matrizCusto , int altura, int largura);

int encontraCaminho(Imagem1C* img , Coordenada** caminho)
{
    int i, j, menor , tamanho , pos_y_inicio, pos_x_final , pos_y_final , aux , altura, largura;
    Imagem1C* imgBinarizada;
    Imagem1C* imgNormalizada;
    int** matrizCusto;
    char imname[50];
    static int imnum=0;

    altura = img->altura;
    largura = img->largura;

    matrizCusto = (int**) malloc (altura * sizeof(int*));

	for(i = 0 ; i < altura ; i++)
		matrizCusto[i] = (int*) malloc (largura * sizeof(int));

    imgBinarizada = criaImagem1C(largura, altura);
    imgNormalizada = criaImagem1C(largura, altura);

    normaliza(img, imgNormalizada);
    binariza(imgNormalizada, imgBinarizada);

    for(i = 0 ; i <altura ; i++)
    {
        for(j = 0 ; j <largura ; j++)
        {
            if(imgBinarizada->dados[i][j] == 255)
                matrizCusto[i][j] = PAREDE;
            else
                matrizCusto[i][j] = CAMINHO;
        }
    }

    sprintf(imname, "bin%d.bmp", imnum);
    salvaImagem1C(imgBinarizada,imname);
    imnum++;

    preencheMatrizCusto(matrizCusto, altura, largura);

    FILE *fp;
    fp = fopen("ajuda2.txt", "w");
    for (i = 0; i < altura; i++)
    {
      for (j = 0; j < largura; j++)
          if(matrizCusto[i][j] == PAREDE)
              fprintf(fp,"%2d ", 0);
           else
             fprintf(fp,"%2d-", matrizCusto[i][j]);
           fprintf(fp, "\n");
    }
     fclose(fp);

    for(i = 0 ; i <altura ; i++)
    {
        if(matrizCusto[i][0] >= 0)
        {
            menor = matrizCusto[i][0];
        }
    }

    for(i = 0 ; i <altura ; i++)
    {
        if(matrizCusto[i][0] <= menor && matrizCusto[i][0]>=0)
        {
            menor = matrizCusto[i][0];
            pos_y_inicio = i;
        }
    }
    tamanho = menor;
    //printf("Criando caminho de tamanho %d\n\n", tamanho);


    *caminho = (Coordenada*) malloc ((tamanho+1) * sizeof(Coordenada));

    (*caminho)[0].y = pos_y_inicio;
    (*caminho)[0].x =0;
    //printf("inserindo coordenada [%d %d]\n",(*caminho)[0].x, (*caminho)[0].y);


    for(i = 0 ; i < altura ; i++)
        free(matrizCusto[i]);

    free(matrizCusto);


    return tamanho+1;
}


void preencheCaminho (int** matrizCusto, Coordenada** caminho, int largura, int altura, int menor)
{
    int tamanho = menor, i, j, aux;

    for(i=0;i<tamanho;i++)
    {
        aux=0;
        if((*caminho)[i].x+1<largura&&aux==0 &&matrizCusto[(*caminho)[i].y][(*caminho)[i].x+1]==menor-1)
        {
                (*caminho)[i+1].x=(*caminho)[i].x+1;
                (*caminho)[i+1].y=(*caminho)[i].y;
                aux=1;
        }

        if((*caminho)[i].y+1<altura&&aux==0)
        {
            if(matrizCusto[(*caminho)[i].y+1][(*caminho)[i].x]==menor-1)
            {
                (*caminho)[i+1].x=(*caminho)[i].x;
                (*caminho)[i+1].y=(*caminho)[i].y +1;
                aux=1;
            }
        }

        if((*caminho)[i].y-1>=0&&aux==0)
        {
            if(matrizCusto[(*caminho)[i].y-1][(*caminho)[i].x]==menor-1)
            {
                (*caminho)[i+1].x=(*caminho)[i].x;
                (*caminho)[i+1].y=(*caminho)[i].y-1;
                aux=1;
            }
        }

        if((*caminho)[i].x-1>=0&&aux==0)
        {
            if(matrizCusto[(*caminho)[i].y][(*caminho)[i].x-1]==menor-1)
            {
                (*caminho)[i+1].x=(*caminho)[i].x-1;
                (*caminho)[i+1].y=(*caminho)[i].y;
                aux=1;
            }
        }
        menor--;

        //printf("inserindo coordenada [%d %d]\n",(*caminho)[i+1].x, (*caminho)[i+1].y);
    }
}

void normaliza(Imagem1C* in, Imagem1C* out)
{
    int i,j;
    unsigned char maiorNum = in->dados[0][0], menorNum = in->dados[0][0];
    float soma =0;
    float fator;


    for(j = 0; j <in->largura; j++)
    {
         for(i= 0; i < in->altura; i++) {
            if (in->dados[i][j] > maiorNum)
                maiorNum = in->dados[i][j];
            if (in->dados[i][j] < menorNum)
                menorNum = in->dados[i][j];
         }
    }

    fator = 255.0f / (maiorNum-menorNum);
    for(j = 0; j < in->largura; j++) {
        for(i= 0; i < in->altura; i++)
        {
            out->dados[i][j] = (unsigned char) ((((in->dados[i][j])-menorNum)*fator)+0.5f);
        }
    }
}


void binariza(Imagem1C* in, Imagem1C* out)
{
    int i,j;
    unsigned char maiorNum = in->dados[0][0], menorNum = in->dados[0][0];
    float soma =0;
    float fator;


    for(j = 0; j <in->largura; j++)
    {
         for(i= 0; i < in->altura; i++) {
            if (in->dados[i][j] > maiorNum)
                maiorNum = in->dados[i][j];
            if (in->dados[i][j] < menorNum)
                menorNum = in->dados[i][j];
         }
    }

    fator = 255.0f / (maiorNum-menorNum);
    for(j = 0; j < in->largura; j++) {
        for(i= 0; i < in->altura; i++)
        {
            out->dados[i][j] = (unsigned char) ((((in->dados[i][j])-menorNum)*fator)+0.5f);
        }
    }


    for(j = 0; j <in->largura; j++)
    {
        soma =0;
        for(i= 0; i < in->altura; i++)
            soma+=out->dados[i][j];

        soma/=in->altura;

        for(i= 0; i < in->altura; i++)
        {
            if(out->dados[i][j] >= soma*0.85)
                out->dados[i][j] =255;
            else
                out->dados[i][j] = 0;
        }
    }
}

void preencheMatrizCusto (int **matrizCusto , int altura , int largura)
{
    int mudou = 1, i, j, distancia;


    for(j = 0 ; j < altura ;j++)
    {
        if(matrizCusto[j][largura-1] == CAMINHO)
        {
            matrizCusto[j][largura-1] = 0;
        }
    }

    distancia = 1;

    while(mudou)
    {
        mudou = 0;
        for(i = 0 ; i < altura ;i++)
        {
            for(j = 0 ; j < largura ; j++)
            {
                if(matrizCusto[i][j] == CAMINHO )
                {
                    if(i>0)
                    {
                        if(matrizCusto[i-1][j] == distancia-1)
                        {
                            matrizCusto[i][j] = distancia;
                            mudou = 1;
                        }
                    }

                    if(i < altura-1)
                    {
                        if(matrizCusto[i+1][j] == distancia-1)
                        {
                            matrizCusto[i][j] = distancia;
                            mudou = 1;
                        }
                    }
                    if(j>0)
                    {
                       if(matrizCusto[i][j-1] == distancia-1 )
                        {
                            matrizCusto[i][j] = distancia;
                            mudou = 1;
                        }
                    }
                    if(j < largura-1)
                    {
                        if(matrizCusto[i][j+1] == distancia-1 )
                        {
                            matrizCusto[i][j] = distancia;
                            mudou = 1;
                        }
                    }
                }
            }
        }
        distancia++;
    }
}

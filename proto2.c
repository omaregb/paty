//Este programa calcula las temperaturas en diferentes puntos de una placa. Proyecto2.
//Creado por Patricia Godinez el 24 de Octubre de 2018.
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
void LlenaMatriz(int num, float T[200][200]);
int main ()
{
    FILE *fp;
    FILE *f0;
    int num,iarr,iab,jder,jiz,i,j,n=300;
    float T[200][200],eps;
    fp=fopen("datos.txt","r");
    //num= dimensiones de la placa. eps=epsilon. iarr=magnitud de la temperatura del lado superior. iab=magnitud de la temperatura del lado inferior. jder=magnitud de la temperatura del lado derecho. jiz=magnitud de la temperatura del lado izquierdo.
    fscanf(fp,"%i\t%f\t%i\t%i\t%i\t%i\t",&num,&eps,&iarr,&iab,&jder,&jiz);
    fclose(fp);
    printf("%i\t%f\t%i\t%i\t%i\t%i\n",num,eps,iarr,iab,jder,jiz);//printf provisional para ver si se esta lleyendo el archivo.

    for(i=0;i<=num;i++)//ciclos for para llenar los valores de los lados.   //superior
    {
        T[i][num]=iarr;
    }
    for(i=0;i<=num;i++)//inferior
    {
        T[i][0]=iab;
    }
    for(j=0;j<=num;j++)//izquierda
    {
        T[0][j]=jiz;
    }
    for(j=0;j<=num;j++)//derecha
    {
        T[num][j]=jder;
    }
    //llamando a la funcion para llenar los valores del centro con ceros.
    LlenaMatriz(num,T);

    //Creando archivo inicial para guardar los datos.
    f0=fopen("T_inicial.txt","w");
        for(i=0;i<=num;i++)
        {
            for(j=0;j<=num;j++)
            {
                fprintf(f0,"%f\t",T[i][j]);
            }
            fprintf(f0,"\n");
        }
    fclose(f0);

    int k, t;
    float Told[200][200]/*matriz para guardar los valores de las temperaturas de la matriz anterior*/,tol=100/*tolerancia*/;
    t=1;//contador de iteraciones.
    k=200; //numero maximo de iteraciones.
    char filename[256]; //DECLARANDO EL CONTENEDOR DEL NOMBRE PARA CADA ARCHIVO
    while(t<k)
    {
        //printf("//////////////////////////////////\n");// separador de matrices. //ESTO LO QUITE AL CARAJO
        sprintf(filename,"Iteracion%d.txt",t); //CREA UN STRING QUE CONTIENE UN NOMBRE QUE VARIA CON EL NUMERO DE ITERACION Y LO GUARDA EN FILENAME
	FILE *f_point; //POINTER PARA NUEVO ARCHIVO
	f_point=fopen(filename,"w"); //ABRIENDO EL NUEVO ARCHIVO USANDO EL NOMBRE GENERADO CON SPRINTF
	    for(i=1;i<=num-1;i++)
        {
            for(j=1;j<=num-1;j++)
            {
                Told[i][j]=(T[i+1][j]+T[i-1][j]+T[i][j+1]+T[i][j-1])/4;//calculo del promedio de temperatura de cada punto de la placa.
                //printf("T[%i][%i]=%f\n",i,j,T[i][j]);//Printf provisional
                tol=fabs((T[i][j]-Told[i][j])/Told[i][j]);//calculo de la tolerancia confonme van pasando la iteraciones.
                //printf("iteracion=%i",t);
                //printf("tol=%f\n",tol);
                if(tol<eps)//comparando tolerancia con epsilon para decidir si se sigue realizando el programa o si debe terminar cuando se cumple la condicion.
                {
                    printf("Se alcanzo la tolerancia maxima en la iteracion %i y la matriz en esta es: \n",t);
                    for(i=0;i<=num;i++)
                    {
                        for(j=0;j<=num;j++)
                        {
                            printf("%f\t",T[i][j]);
                        }
                    }
                    return 1;
                }
                else
                {
                    T[i][j]=Told[i][j];
                }
            }
        }
        //imprimiendo la matriz actual.
        for(i=0;i<=num;i++)
        {
            for(j=0;j<=num;j++)
            {
                fprintf(f_point,"%f\t",T[i][j]);
            }
            fprintf(f_point,"\n");
        }
	fclose(f_point); //CERRANDO ARCHIVO 
        t++;
    }
}

void LlenaMatriz(int num, float T[200][200])//Esta funcion llena todos los puntos centrales de la matriz con ceros.
{
    int i,j;
    for(i=1;i<num-1;i++)
    {
        for(j=1;j<num-1;j++)
        {
            T[i][j]=0;
        }
    }
    printf("\n");
}

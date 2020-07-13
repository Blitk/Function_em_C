#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

//Teste de ponteiros 
void maisum(int* variavel){
    ++(*variavel);
}

//teste de criação de arquivos
void warquivo(){
    FILE *arquivo;
    char nome[20];
    char conteudo[200];
    printf("\n\n\033[34m     >>>>>>>>>> Bem vindo ao escritor de arquivos <<<<<<<<\033[0m\n");
    printf("\nDigite um nome para o arquivo: ");
    scanf("%s", nome);
    arquivo = fopen(nome, "w");
    if(arquivo){
        printf("\nDigite algo para escrever no arquivo: ");
        fgets(conteudo, 200, stdin);
        while(conteudo[0] != '0'){
            fputs(conteudo, arquivo);
            printf("\n... ");
            fgets(conteudo, 200, stdin);
        }
        printf("\n\033[32m>>>>>>>>>>mArquivo escrito com sucesso<<<<<<<<<\033[0m");
        fclose(arquivo);
    }
    else{
        printf("\033[31m\nInfelizmente não conseguimos criar o arquivo...\033[0m");
    }
}

//Teste de Leitura de arquivos
void rarquivo(){
    printf("\n\n\033[34m     >>>>>>>>>> Bem vindo ao leitor de arquivos <<<<<<<<\033[0m\n");
    FILE *arquivo;
    char nome[20];
    char conteudo[200], *resultado;
    printf("\nDigite um nome para o arquivo: ");
    scanf("%s", nome);
    arquivo = fopen(nome, "r");
    if(arquivo){
        while(!feof(arquivo)){
            resultado = fgets(conteudo, 200, arquivo);
            if(resultado){
                printf("%s", conteudo);
            }
        }
        fclose(arquivo);
    }
    else{
        printf("\033[31m\nInfelizmente não conseguimos ler o arquivo...\033[0m");
    }
}

//Cronometro para programas
void cronometro(){
    //#include <time.h>
    long int beginning_t, end_t, total_t;
    //inicio do cronometro
    beginning_t = clock();
    time(&beginning_t);
    //fim do cronometro
    end_t = clock();
    time(&end_t);
    //converter o long para float e tirar a diferença de tempo entre inicio e fim
    total_t = (end_t - beginning_t) / 100;
    //100 é para ficar no padrao de minutos: 22:30
    //caso queira deixar em segundos, exclui o "/100"
    //caso queira deixar em horas é só dividir por 6000
    printf("O tempo em minutos foi de %.2f ", (float)total_t);
    //o %.2f serve para deixar com duas casas após a virgula
}

//números fatoriais com limite 30
void fatorial(){
    setlocale(LC_ALL, "portuguese-brazilian");
    int num;
    int d;
    int resultado = 1;
    int r[31];
    printf("\n                 >>>>>>>> ATENÇÃO, NÚMERO LIMITE É 30 <<<<<<<\n\n");
    printf("Digite um número para o fatorial: ");
    scanf("%d", &num);
    for(int i = 0; i < num;i++){
        i+=1;
        d = i+1;
        r[num+1];
        printf(" %d X %d\n", i, d);
        r[i]= i*d;
        resultado = resultado * r[i];
    }
    printf("\n\nO resultado é %li\n\n", (long int)resultado);
}


//allocação dinamica de memória com Lista encadeada

struct st_LinkedList{
    int valor;
    struct st_LinkedList * proximo;
};

typedef struct st_LinkedList link; 

int vazia(link * lista){
    if(lista == NULL){
        return 1;
    }else{
        return 0;
    }
}

void iniciar(link * lista){
    lista->proximo = NULL;
}

void exibe(link* lista){
    if(vazia(lista)){
        printf("Não há o que exibir!");
        return;
    }
    link *atual, *prox;
    atual = lista->proximo;
    while(atual != NULL){
        printf("%d", lista->valor);
        atual = atual->proximo;
    }
}

void insereInicio(link* lista){
    link *novo = (link*)malloc(sizeof(link));
    printf("Digite um valor: ");
    scanf("%d", &novo->valor);
    link *oldhead;
    oldhead = lista->proximo;
    lista->proximo = novo;
    novo->proximo = oldhead;
}

void insereFim(link* lista){
    link *novo = (link*)malloc(sizeof(link));
    if(!novo){
        printf("Sem memoria suficiente!");
        exit(1);
    }
    printf("\nDigite o valor: ");
    scanf("%d", &novo->valor);
    novo->proximo = NULL;
    if(vazia(lista)){
        lista->proximo = novo;
    }else{
        link *tmp = lista->proximo;
        while(tmp != NULL){
            tmp = tmp->proximo;
        }
        tmp->proximo = novo;
    }
}

void libera(link* lista){
    link *atual, *proximo;
    atual = lista->proximo;
    while(atual != NULL){
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}


//Arvore binária

struct st_arvore{
    int valor;
    struct st_arvore * sad;  //sub-arvore direita
    struct st_arvore * sae;  //sub-arvore esquerda
};

typedef struct st_arvore arvore;

arvore * criarArvore(){
    return NULL;
}

int vazioArvore(arvore * arvore){
    if(arvore == NULL){
        return 1;
    }else{
        return 0;
    }
}

void mostrarArvore(arvore * arvore){
    printf("<");
    if(!vazioArvore(arvore)){
        printf("%d", arvore->valor);
        mostrarArvore(arvore->sae);
        mostrarArvore(arvore->sad);
    }
    printf(">");
}

void inserirdados(arvore ** t, int num){
    if(*t == NULL){
        *t = (arvore*)malloc(sizeof(arvore));
        (*t)->sad = NULL;
        (*t)->sae = NULL;
        (*t)->valor = num;
    }
    else{
        if(num < (*t)->valor){
            inserirdados(&(*t)->sae, num);
        }
        if(num > (*t)->valor){
            inserirdados(&(*t)->sad, num);
        }
    }
}

int estaNaArvore(arvore * t, int num){
    if(vazioArvore(t)){
        return 0;
    }
    return t->valor == num || estaNaArvore(t->sad, num) || estaNaArvore(t->sae, num);   //A famosa recursividade
}


//Ordenação de vetores:  Select Sort

void select_sort(int vetor [], int tam){
    int menor, troca;
    for(int i = 0; i < (tam-1); i++){
        menor = i;
        for(int j = (i+1) ; j < tam; j++){
            if(vetor[j] < vetor[menor]){
                menor = j;
            }
        }
        if( i != menor){
            troca = vetor[i];
            vetor[i] = vetor [menor];
            vetor[menor] = troca;
        }    
    }
}


//Ordenação de vetores:  Insert Sort

void insert_sort(int vetor[], int tam){
    int troca, proximo;
    for(int i = 1; i < tam; i++){
        proximo = i;
        while( (proximo != 0) && (vetor[proximo] < vetor[proximo -1])){
            troca = vetor[proximo];
            vetor[proximo] = vetor[proximo - 1];
            vetor[proximo - 1] = troca;
            proximo--;
        }
    }
}


//Ordenação de vetores:  Bubble Sort

void bubble_sort(int vetor[], int tam){
    int proximo;
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < (tam -1); j++){
            if(vetor[j] > vetor[j+1]){
                proximo = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = proximo;
            }
        }
    }
}


//Ordenação de vetores:  Shell Sort

void shell_sort(int vetor[], int tam){
    int grupo = 1;
    while (grupo < tam){   //gerar o tamanho do grupo de acordo com o tamanho do vetor
        grupo = 3 * grupo + 1;
    }
    //varrer o vetor enquanto houver grupos para ordenar
    while(grupo > 1){
        //dividir o grupo em 3
        grupo /= 3;
        //varreremos cada grupo
        for(int i = grupo; i < tam; i ++){
            int troca = vetor[i];
            int j = i - grupo;
            //realiza as trocas
            while( j >= 0 && troca < vetor[j]){
                vetor[ j + grupo ] = vetor[j];
                j -= grupo;
            }
            //realiza a troca
            vetor[ j + grupo] = troca;
        }
    }
}


//ordenação de vetores:  Quick Sort

void quick_sort(int vetor[], int tam){
    int i, j, grupo, troca;
    //criterio de parada da recursividade
    if(tam < 2){
        return; //sai da função
    }else{
        grupo = vetor[tam/2];
    }
    //Fazendo um loop unico se comporta como dois
    for(i=0, j = tam - 1;; i++, j--){
        //fazemos a movimentação dos elementos no vetor
        while( vetor[i] < grupo ){
            i++;
        }
        //Fazemos a movimentação dos elementos no vetor
        while( grupo < vetor[j] ){
            j--;
        }
        //Criterio de parada do loop
        if( i >= j ){
            break;
        }else{
            //onde ocorre as trocas
            troca = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = troca;
        }
    }
    //Usar recursividade para ordenar grupos
    quick_sort(vetor, i);
    quick_sort(vetor + i, tam - 1);
}


//Ordenação de vetores: Merge Sort

void merge(int vetor[], int inicio1, int fim1, int inicio2, int fim2){
    //vetor temporario para o merge
    int temp[50];
    //Variaveis auxiliares
    int i, j , k;
    //inicio do primeiro grupo
    i = inicio1;
    //inicio do segundo grupo
    j = inicio2;
    k=0;
    //enquanto tiver elementos em ambos os grupos
    while(i <= fim1 && j<=fim2){
        //faz a ordenação de acordo com cada grupo
        if(vetor[i] < vetor[j]){
            temp[k++] = vetor[i++];
        }else{
            temp[k++] = vetor[j++];
        }
    }
    //copiar os elementos restantes do primeiro grupo
    while( i<= fim1){
        temp[k++] = vetor[i++];
    }
    //copiar os elementos restantes do segundo grupo
    while( j <= fim2){
        temp[k++] = vetor[j++];
    }
    //transfere os elementos do vetor temporario para o original
    for(i=inicio1, j = 0; i <= fim2;i++, j++){
        vetor[i] = temp[j];
    }
}

void merge_sort(int vetor[], int inicio, int fim){
    //condição de parada
    if(inicio < fim){
        //calcula o meio do vetor
        int meio = (inicio + fim)/2;
        //recursão esquerda
        merge_sort(vetor, inicio, meio);
        //recursão direita
        merge_sort(vetor, meio+1, fim);
        //faz o merge (junta) com os dois grupos os valores ordenados
        merge(vetor, inicio, meio, meio+1, fim);
    }
}


//Ordenação de vetores: Heap Sort

void criaHeap(int vetor[], int inicio, int fim){
    int pai = vetor[inicio];
    int filho = inicio*2+1;
    while( filho <= fim){
        if( filho < fim ){
            if( vetor[filho] < vetor[filho +1 ]){
                filho = filho + 1;
            }
        }
        if( pai < vetor[filho]){
            vetor[inicio] = vetor[filho];
            inicio =  filho;
            filho = 2*inicio+1;
        }else{
            filho = fim+1;
        }
    }
    vetor[inicio] = pai;
}

void heap_sort(int vetor[], int tam){
    int troca;
    int meio = (tam-1)/2;
    for(int i = meio; i >=0; i--){
        criaHeap(vetor, i, tam-1);
    }
    for(int i = tam -1; i >= 1; i--){
        troca = vetor[0];
        vetor[0] = vetor[i];
        vetor[i] = troca;
        criaHeap(vetor, 0, i-1);
    }
}



//Busca Binária

int busca_binaria(int vetor[], int chave, int tam){
    int inicio = 0;
    int fim = tam -1;
    while(inicio <= fim){
        //Encontra o meio do vetor
        int meio = (inicio+fim)/2;
        //Se a chave estiver no meio, retorna
        if(chave == vetor[meio]){
            return meio;
        }
        //Se a chave for menor que o valor do meio, passa para o proximo
        if(chave < vetor[meio]){
            fim = meio -1;
        }else{
            inicio = meio+1;
        }
    }
    return -1;
}


//Busca Linear

int busca_linear(int vetor[], int chave, int tam){
    for(int i = 0; i < tam; i++){
        if( chave == vetor[i] ){
            return i;
        }
    }
}

#endif
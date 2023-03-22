#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include <windows.h>

typedef struct stCarta
{
    int numero;
    char naipe;
    struct stCarta* proximo;
} tCarta;

tCarta * primcarta = NULL;
tCarta ** primesa;
tCarta ** primNaipe;
tCarta ** temp;

void imprimecarta(tCarta *carta)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    if(carta!=NULL)
    {
        if(carta->naipe==3||carta->naipe==4)
        {
            SetConsoleTextAttribute(hConsole, 0x74);
        }
        else
        {
            SetConsoleTextAttribute(hConsole, 0x70);
        }

        switch(carta->numero)
        {
        case 1:
        {
            printf("A %c",carta->naipe);
            break;
        }
        case 10:
        {
            printf("%d%c",carta->numero,carta->naipe);
            break;
        }
        case 11:
        {
            printf("Q %c",carta->naipe);
            break;
        }
        case 12:
        {
            printf("J %c",carta->naipe);
            break;
        }
        case 13:
        {
            printf("K %c",carta->naipe);
            break;
        }
        default:
        {
            printf("%d %c",carta->numero,carta->naipe);
            break;
        }
        }
        SetConsoleTextAttribute(hConsole, saved_attributes);
    }
    else
    {
        printf("[vazia]");
    }
}

void imprimecartainvertida(tCarta *carta)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    if(carta->naipe==3||carta->naipe==4)
    {
        SetConsoleTextAttribute(hConsole, 0x74);
    }
    else
    {
        SetConsoleTextAttribute(hConsole, 0x70);
    }

    switch(carta->numero)
    {
    case 1:
    {
        printf("%c A",carta->naipe);
        break;
    }
    case 10:
    {
        printf("%c%d",carta->naipe,carta->numero);
        break;
    }
    case 11:
    {
        printf("%c Q",carta->naipe);
        break;
    }
    case 12:
    {
        printf("%c J",carta->naipe);
        break;
    }
    case 13:
    {
        printf("%c K",carta->naipe);
        break;
    }
    default:
    {
        printf("%c %d",carta->naipe,carta->numero);
        break;
    }
    }
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

bool criacarta(int posicao, int valor, char simbolo)
{
    tCarta * novo=(tCarta*)malloc(sizeof(tCarta));
    novo->numero=valor;
    novo->naipe=simbolo;
    if(posicao==0)
    {
        novo->proximo=primcarta;
        primcarta=novo; // variavel baralho armazenando a posição da 1 carta
    }
    else
    {
        tCarta * atual=primcarta;
        for(int i=0; i<posicao-1; i++)
        {
            atual=atual->proximo;
        }
        novo->proximo=atual->proximo;
        atual->proximo=novo;
    }
    return true;
}

void geraBaralho(void)
{
    int K=0;
    for(int i=3; i<=6; i++)
    {
        for(int j=1; j<=13; j++)
        {
            criacarta(K,j,i);
            K++;
        }
    }
}

void inicializa(void)
{
    primesa = malloc(sizeof(tCarta)*8);
    primNaipe = malloc(sizeof(tCarta)*4);
    temp = malloc(sizeof(tCarta)*4);
    for(int i=0; i<8; i++)
    {
        primesa[i]=NULL;
    }
    for(int i=0; i<4; i++)
    {
        primNaipe[i]=NULL;
        temp[i] = NULL;
    }
}

void embaralhaBaralho(void)
{
    for(int j=0; j<1000; j++)
    {
        tCarta * embaralha1 = primcarta;
        tCarta * embaralha2 = primcarta;
        tCarta aux;
        int n,m,i;
        n = rand()%52;
        m = rand()%52;

        while(n==m)
        {
            m = rand()%52;
        }

        for(i=0; i<n; i++)
        {
            embaralha1 = embaralha1->proximo;
        }
        for(i=0; i<m; i++)
        {
            embaralha2 = embaralha2->proximo;
        }
        aux.numero = embaralha1->numero;
        aux.naipe = embaralha1->naipe;

        embaralha1->numero = embaralha2->numero;
        embaralha1->naipe = embaralha2->naipe;

        embaralha2->numero = aux.numero;
        embaralha2->naipe = aux.naipe;
    }
}

void imprime(void)
{
    printf("                ");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    SetConsoleTextAttribute(hConsole, 0x6F);
    printf("[TEMP]= ");
    int a;
    tCarta * naipeaux;
    tCarta * naipeaux1;

    for(a=0; a<4; a++)
    {
        printf("|");
        if(temp[a]!=NULL)
            imprimecarta(temp[a]);
        else
            printf("  ");
        printf("|");
    }

    SetConsoleTextAttribute(hConsole, saved_attributes);
    printf("\n                ");
    SetConsoleTextAttribute(hConsole, 0x6F);

    printf("        ");
    for(a=0; a<4; a++)
    {
        printf("|");
        if(temp[a]!=NULL)
            imprimecartainvertida(temp[a]);
        else
            printf(" %d",a);
        printf("|");
    }
    printf("\n\n");
    SetConsoleTextAttribute(hConsole, saved_attributes);

    for(a=0; a<4; a++)
    {
        naipeaux = primNaipe[a];
        naipeaux1 = primNaipe[a];
        printf("[NAPE %d]=",a);
        while(naipeaux!=NULL)
        {
            imprimecarta(naipeaux);
            naipeaux = naipeaux->proximo;
            printf(" ");
        }
        printf("\n         ");

        while(naipeaux1!=NULL)
        {
            imprimecartainvertida(naipeaux1);
            naipeaux1 = naipeaux1->proximo;
            printf(" ");
        }
        printf("\n\n");
    }

    tCarta * aux, * aux1;
    for(a=0; a<8; a++)
    {
        printf("[MESA %d]= ",a);
        aux = primesa[a];
        aux1 = primesa[a];
        while(aux!=NULL)
        {
            imprimecarta(aux);
            printf(" ");
            aux=aux->proximo;
        }
        printf("\n");
        printf("          ");
        while(aux1!=NULL)
        {
            imprimecartainvertida(aux1);
            printf(" ");
            aux1=aux1->proximo;
        }
        printf("\n\n");

    }


}

void distribuirMesa(void)
{
    tCarta *aux,*aux1,*auxmesa;
    for(int j=0; j<7; j++)
    {
        for(int i=0; i<8; i++)
        {
            aux = primcarta;
            aux1 = primcarta;

            while(aux->proximo!=NULL)  //caçando a carta disponivel
            {
                aux=aux->proximo;   //ultima carta
            }
            while(aux1->proximo!=aux)    //penultima carta
            {
                aux1=aux1->proximo;
            }

            if(primesa[i]==NULL)
            {
                aux1->proximo=NULL;
                primesa[i] = aux;   //nao mexer mais no primesa
            }
            else
            {
                auxmesa = primesa[i];
                while(auxmesa->proximo!=NULL)   //penultima carta
                    auxmesa=auxmesa->proximo;

                auxmesa->proximo = aux;
                aux1->proximo=NULL;
            }

            if(primcarta->proximo==NULL)
            {
                aux = primesa[i+1];
                while(aux->proximo!=NULL) //caçando a carta disponivel
                    aux=aux->proximo;
                aux->proximo = primcarta;
                primcarta=NULL;
                break;
            }
        }
    }
}

void moveMesaTemp(void)
{
    int m,t;
    tCarta *aux,*aux1;
    printf("Digite de qual mesa voce deseja enviar uma carta para o temporario: ");
    scanf("%d",&m);
    getchar();
    printf("\nDigite para qual temporario voce deseja enviar a carta: ");
    scanf("%d",&t);

    while(!(m>=0&&m<8))
    {
        printf("Digite de qual mesa voce deseja enviar uma carta para o temporario: ");
        scanf("%d",&m);
    }

    while(!(t>=0&&t<4))
    {
        printf("\nDigite para qual temporario voce deseja enviar a carta: ");
        scanf("%d",&t);
    }


    aux = primesa[m];
    aux1 = primesa[m];
    if(primesa[m]!=NULL)
    {
        while(aux->proximo!=NULL)
        {
            aux = aux->proximo; //ULTIMA CARTA
        }
        if(aux!=primesa[m])
        {
            while(aux1->proximo!=aux)
            {
                aux1 = aux1->proximo; //PENULTIMA CARTA
            }
        }
        imprimecarta(aux);
        imprimecarta(primesa[m]);
        getchar();
        getchar();
        if(aux==primesa[m])
        {
            printf("A MESA VAI FICAR VAZIA!");
            getchar();
            getchar();
            if(temp[t]==NULL&&(m>=0&&m<8)&&(t>=0&&t<4))
            {
                temp[t] = aux;
                temp[t]->proximo = NULL;
                aux1->proximo = NULL;
                primesa[m]=NULL;
            }
            else
            {
                printf("MESA OU TEMPORARIO INEXISTENTES!");
                getchar();
                getchar();
            }
        }
        else
        {
            if(temp[t]==NULL&&(m>=0&&m<8)&&(t>=0&&t<4))
            {
                temp[t] = aux;
                temp[t]->proximo = NULL;
                aux1->proximo = NULL;
            }
            else
            {
                printf("MESA OU TEMPORARIO INEXISTENTES!");
                getchar();
                getchar();
            }
        }
    }
    else
    {
        printf("MESA VAZIA!");
        getchar();
        getchar();
    }
}

void moveTempMesa(void)
{
    int m,t;
    tCarta *aux;

    printf("Digite de qual temporario voce deseja retirar uma carta: ");
    scanf("%d",&t);

    printf("\nDigite para qual mesa voce deseja enviar essa carta: ");
    scanf("%d",&m);

    if(m>=0&&m<8&&t>=0&&t<4)
    {
        if(temp[t]==NULL)
        {
            printf("Temporario Vazio!");
            getchar();
            getchar();
        }
        else
        {
            if(primesa[m]==NULL)
            {
                primesa[m] = temp[t];
                primesa[m]->proximo=NULL;
                temp[t] = NULL;
            }
            else
            {
                aux = primesa[m];
                while(aux->proximo!=NULL)
                {
                    aux = aux->proximo;
                }
                if(aux->numero==temp[t]->numero+1)
                {
                    if(aux->naipe==3||aux->naipe==4)
                    {
                        if(temp[t]->naipe==5||temp[t]->naipe==6)
                        {
                            aux->proximo = temp[t];
                            temp[t]=NULL;
                        }
                        else
                        {
                            printf("MOVIMENTO INVALIDO! (Naipe igual)");
                            getchar();
                            getchar();
                        }
                    }
                    if(aux->naipe==5||aux->naipe==6)
                    {
                        if(temp[t]->naipe==3||temp[t]->naipe==4)
                        {
                            aux->proximo = temp[t];
                            temp[t]=NULL;
                        }
                        else
                        {
                            printf("MOVIMENTO INVALIDO! (Naipe igual)");
                            getchar();
                            getchar();
                        }
                    }
                }
                else
                {
                    printf("MOVIMENTO INVALIDO! (Numero menor)");
                    getchar();
                    getchar();
                }
            }

        }
    }

    else
    {
        printf("MOVIMENTO INVALIDO! (MESA OU TEMPORARIO INEXISTENTE!)");
        getchar();
        getchar();
    }
}

void moveMesaNaipe(void)
{
    int m,n;
    tCarta *auxmesa,*auxmesa1,*auxnaipe;

    printf("Digite de qual mesa voce deseja retirar uma carta: ");
    scanf("%d",&m);


    while(!(m>=0&&m<8))
    {
        printf("Digite de qual mesa voce deseja retirar uma carta: ");
        scanf("%d",&m);
    }

    while(!(n>=0&&n<4))
    {
        printf("\nDigite para qual naipe voce deseja enviar essa carta: ");
        scanf("%d",&n);
    }

    if(primesa[m]!=NULL)
    {
        auxmesa = primesa[m];
        while(auxmesa->proximo!=NULL)
        {
            auxmesa = auxmesa->proximo;
        }
        auxmesa1 = primesa[m];

        if(auxmesa!=primesa[m])
        {

            while(auxmesa1->proximo!=auxmesa)
            {
                auxmesa1 = auxmesa1->proximo;
            }

            if(m>=0&&m<8&&n>=0&&n<4)
            {
                if(primNaipe[n]==NULL)
                {
                    if(auxmesa->numero==1)
                    {
                        primNaipe[n] = auxmesa;
                        auxmesa1->proximo=NULL;
                    }
                    else
                    {
                        printf("A mesa Naipe deve ser inicializada com um As!");
                    }
                }
                else
                {
                    auxnaipe = primNaipe[n];
                    while(auxnaipe->proximo!=NULL)
                    {
                        auxnaipe=auxnaipe->proximo;
                    }
                    if((auxnaipe->naipe==auxmesa->naipe)&&(auxnaipe->numero==((auxmesa->numero)-1)))
                    {
                        auxnaipe->proximo = auxmesa;
                        auxmesa1->proximo=NULL;
                    }
                    else
                    {
                        printf("MOVIMENTO INVALIDO! (numero ou naipe incompativeis");
                    }
                }
            }
            else
            {
                printf("MESA OU TEMPORARIO INEXISTENTES!");
            }
        }
        else
        {
            if(primNaipe[n]==NULL)
            {
                if(auxmesa->numero==1)
                {
                    primNaipe[n] = auxmesa;
                    primesa[m]=NULL;
                }
                else
                {
                    printf("A mesa Naipe deve ser inicializada com um As!");
                }
            }
            else
            {
                auxnaipe = primNaipe[n];
                while(auxnaipe->proximo!=NULL)
                {
                    auxnaipe=auxnaipe->proximo;
                }
                if((auxnaipe->naipe==auxmesa->naipe)&&(auxnaipe->numero==((auxmesa->numero)-1)))
                {
                    auxnaipe->proximo = auxmesa;
                    primesa[m] = NULL;
                    auxmesa=NULL;
                }
                else
                {
                    printf("MOVIMENTO INVALIDO! (numero ou naipe incompativeis");
                }
            }
        }
    }
    else
    {
        printf("MESA VAZIA!");
    }
    getchar();
    getchar();
}

void moveMesaMesa(void)
{
    int m1,m2;
    tCarta *aux1,*aux2,*aux3,*aux4;
    printf("Digite de qual mesa voce deseja retirar uma carta: ");
    scanf("%d",&m1);
    printf("Digite para qual mesa voce deseja enviar uma carta: ");
    scanf("%d",&m2);

    while(!(m1>=0&&m1<8))
    {
        printf("Digite de qual mesa voce deseja retirar uma carta: ");
        scanf("%d",&m1);
    }

    while(!(m2>=0&&m2<8))
    {
        printf("Digite para qual mesa voce deseja enviar uma carta: ");
        scanf("%d",&m2);
    }


    if(primesa[m1]!=NULL)
    {
        aux1 = primesa[m1];
        aux2 = primesa[m1];
        aux3 = primesa[m2];
        aux4 = primesa[m2];

        while(aux1->proximo!=NULL&&primesa[m1]!=NULL)
            aux1 = aux1->proximo;

        while(aux2->proximo!=aux1&&aux2!=aux1)
            aux2 = aux2->proximo;


        if(primesa[m2]!=NULL)
        {

            while(aux3->proximo!=NULL&&primesa[m2]!=NULL)
                aux3 = aux3->proximo;
            while(aux4->proximo!=aux3&&aux4!=aux3)
                aux4 = aux4->proximo;

            if(aux1==aux2)
            {
                aux3->proximo = aux1;
                primesa[m1] = NULL;

            }
            else
            {
                if(aux3->numero==aux1->numero+1) //a carta q recebe tem q ser 1 maior
                {
                    switch(aux3->naipe)
                    {
                    case 3:
                    {
                        if(aux1->naipe==5||aux1->naipe==6)
                        {
                            aux3->proximo = aux1;
                            aux2->proximo = NULL;
                        }
                        break;
                    }
                    case 4:
                    {
                        if(aux1->naipe==5||aux1->naipe==6)
                        {
                            aux3->proximo = aux1;
                            aux2->proximo = NULL;
                        }
                        break;
                    }
                    case 5:
                    {
                        if(aux1->naipe==3||aux1->naipe==4)
                        {
                            aux3->proximo = aux1;
                            aux2->proximo = NULL;
                        }
                        break;
                    }
                    case 6:
                    {
                        if(aux1->naipe==3||aux1->naipe==4)
                        {
                            aux3->proximo = aux1;
                            aux2->proximo = NULL;
                        }
                        break;
                    }
                    default:
                        printf("MOVIMENTO INVALIDO! (A carta so pode ser movida para uma cor diferente)");
                    }
                }
                else
                {
                    printf("MOVIMENTO INVALIDO! (A carta so pode ser movida para uma 1 maior)");
                }
            }
        }
        else
        {
            primesa[m2] = aux1;
            aux2->proximo=NULL;
        }
    }
    else
    {
        printf("MESA VAZIA!");
    }
    getchar();
    getchar();
}

void tempnaipe(void)
{
    int t,n;
    tCarta *auxtemp,*auxnaipe;

    printf("Digite de qual temp voce deseja retirar uma carta: ");
    scanf("%d",&t);

    printf("\nDigite para qual naipe voce deseja enviar essa carta: ");
    scanf("%d",&n);

    while(!(t>=0&&t<4))
    {
        printf("Digite de qual temp voce deseja retirar uma carta: ");
        scanf("%d",&t);
    }

    while(!(n>=0&&n<4))
    {
        printf("\nDigite para qual naipe voce deseja enviar essa carta: ");
        scanf("%d",&n);
    }


    auxtemp = temp[t];
    if(temp[t]!=NULL)
    {
        if(t>=0&&t<4&&n>=0&&n<4)
        {
            if(primNaipe[n]==NULL)
            {
                if(temp[t]->numero==1)
                {
                    primNaipe[n] = auxtemp;
                    temp[t]=NULL;
                }
                else
                {
                    printf("A mesa Naipe deve ser inicializada com um As!");
                }
            }
            else
            {
                auxnaipe = primNaipe[n];
                while(auxnaipe->proximo!=NULL)
                {
                    auxnaipe=auxnaipe->proximo;
                }
                if((auxnaipe->naipe==temp[t]->naipe)&&(auxnaipe->numero==((temp[t]->numero)-1)))
                {
                    auxnaipe->proximo = temp[t];
                    temp[t]=NULL;
                }
                else
                {
                    printf("MOVIMENTO INVALIDO! (numero ou naipe incompativeis");
                }
            }
        }
        else
        {
            printf("MESA OU TEMPORARIO INEXISTENTES!");
        }
    }
    else
    {
        printf("TEMPORARIO VAZIO!");
    }

    getchar();
    getchar();
}

int contatemp(void)
{
    int n,aux=0;
    while(aux<4)
    {
        if(temp[aux]==NULL)
        {
            n++;
        }
        aux++;
    }
    return n;
}

int contamesa(int i)
{
    int n=0;
    tCarta *aux=primesa[i];
    while(aux!=NULL)
    {
        aux=aux->proximo;
        n++;
    }
    return n;
}

bool verifica(tCarta *cartafixa,tCarta *cartamovida)
{
    if(cartafixa->numero==cartamovida->numero+1)  //a carta q recebe tem q ser 1 maior
    {
        switch(cartafixa->naipe)
        {
        case 3:
        {
            if(cartamovida->naipe==5||cartamovida->naipe==6)
            {
                return 1;
            }
            break;
        }
        case 4:
        {
            if(cartamovida->naipe==5||cartamovida->naipe==6)
            {
                return 1;
            }
            break;
        }
        case 5:
        {
            if(cartamovida->naipe==3||cartamovida->naipe==4)
            {
                return 1;
            }
            break;
        }
        case 6:
        {
            if(cartamovida->naipe==3||cartamovida->naipe==4)
            {
                return 1;
            }
            break;
        }

        }
    }
    else
    {
    }
    return 0;
}

bool verificafila(tCarta *carta)
{
    while(carta->proximo!=NULL)
    {
        if(verifica(carta, carta->proximo)==0)
            return 0;

        carta = carta->proximo;
    }
    return 1;
}

void movevarias()
{
    int n,m1,m2,c=1,t,t1;
    tCarta *memory,*memory1,*ant;
    printf("Deseja mover as cartas de qual mesa? ");
    scanf("%d",&m1);
    printf("Deseja mover as cartas para qual mesa? ");
    scanf("%d",&m2);
    printf("Digite quantas cartas deseja mover: ");
    scanf("%d",&n);

    while(!(m1>=0&&m1<8))
    {
        printf("Digite de qual mesa voce deseja retirar uma carta: ");
        scanf("%d",&m1);
    }

    while(!(m2>=0&&m2<8))
    {
        printf("Digite para qual mesa voce deseja enviar uma carta: ");
        scanf("%d",&m2);
    }

    while(n<=0){
        printf("Digite quantas cartas deseja mover? ");
        scanf("%d",&n);
    }


    t = contatemp();
    t1 = contamesa(m1);

    printf("Quantidade livre no tempo: %d\n",t);
    printf("Quantidade na mesa: %d\n",t1);

    memory = primesa[m1];
    memory1 = primesa[m2];
    ant = primesa[m1];

    while(primesa[m2]!=NULL&&primesa[m2]->proximo!=NULL)  // if primesa m2 = NULL então ela recebe se nao -> proximo recebe
        primesa[m2] = primesa[m2]->proximo;     //carta q vai receber

    printf("t: %d\nt1: %d\n",t,t1);
    //imprimecarta(primesa[m2]);

    if(t+1>=n&&primesa[m1]!=NULL&&m1!=m2) // A quantidade de cartas a serem movidas tem que ser menor ou igual a quantidade do temp +1
    {
        // A mesa que envia a carta não pode estar vazia
        for(int i=0; i < t1-n; i++)
        {
            primesa[m1] = primesa[m1]->proximo;
        }
        //imprimecarta(primesa[m1]); //carta q vai ser enviada

        while(ant!=primesa[m1]&&ant->proximo!=primesa[m1])
            ant = ant->proximo;

        if(primesa[m2]!=NULL)
        {


            if(verificafila(primesa[m1])&&verifica(primesa[m2], primesa[m1]))
            {
                primesa[m2]->proximo = primesa[m1];

                if(ant==primesa[m1])
                {
                    memory = NULL;
                }
                else
                {
                    ant->proximo = NULL;
                }

            }
            else
            {
                printf("Movimento Invalido!");

            }
            primesa[m1] = memory;
            primesa[m2] = memory1;
        }
        else
        {
            if(verificafila(primesa[m1]))
            {
                primesa[m2] = primesa[m1];

                if(ant==primesa[m1])
                {
                    memory = NULL;
                }
                else
                {
                    ant->proximo = NULL;
                }

            }
            else
            {
                printf("Movimento Invalido!");
                primesa[m2] = memory1;

            }
            primesa[m1] = memory;
           //
        }
    }
    else
    {
        printf("A quantidade de cartas a serem movidas é maior que a quantidade de espaços livres no temp + 1!\n");
        primesa[m2] = memory1;

    }

    getchar();
    getchar();
}

void naipetemp(void)
{
    int n, t;
    tCarta *aux, *aux1;
    printf("Digite de qual naipe voc%c deseja retirar a ultima carta: ",136);
    scanf("%d",&n);
    printf("Digite para qual temporario voc%c deseja enviar: ",136);
    scanf("%d",&t);




    if(temp[t]==NULL){
        if(primNaipe[n]!=NULL){
            aux = primNaipe[n];
            aux1 = primNaipe[n];

            while(aux->proximo!=NULL)
                aux = aux->proximo; //ultima

            while(aux1!=aux&&aux1->proximo!=aux)
                aux1 = aux1->proximo; //penultima

            temp[t] = aux;

            if(aux1==aux){
                primNaipe[n] = NULL;
            }else{
                aux1->proximo = NULL;
            }

        }else{
            printf("Naipe vazio!");
            getchar();
        }

    }else{
        printf("Temporario cheio!");
        getchar();
    }
}

void naipemesa(void)
{
    int n, m;
    tCarta *aux, *aux1, *auxmesa;
    printf("Digite de qual naipe voc%c deseja retirar a ultima carta: ",136);
    scanf("%d",&n);
    printf("Digite para qual mesa voc%c deseja enviar: ",136);
    scanf("%d",&m);

    if(primNaipe[n]!=NULL&&(n>=0)&&(n<4)){
        aux = primNaipe[n];
        aux1 = primNaipe[n];

        while(aux->proximo!=NULL){
            aux = aux->proximo; //ultima
        }

        while(aux1->proximo!=aux&&aux!=aux1){
            aux1=aux1->proximo; //penultima
        }

        if(m>=0&&m<8){
                if(primesa[m]==NULL){
                    if(aux==aux1){
                        primesa[m]=aux;
                        primNaipe[n] = NULL;
                    }else{
                        primesa[m] = aux;
                        aux1->proximo=NULL;
                    }
                }else{
                    auxmesa = primesa[m];
                    while(auxmesa->proximo!=NULL)
                        auxmesa=auxmesa->proximo;

                    if(verifica(auxmesa, aux)){
                        if(aux==aux1){
                            auxmesa->proximo=aux;
                            primNaipe[n] = NULL;
                        }else{
                            auxmesa->proximo = aux;
                            aux1->proximo=NULL;
                        }
                    }else{
                        printf("Movimento invalido!");
                    }

                }



        }else{
            printf("Mesa inexistente!");
        }



    }else{
        printf("Naipe vazio ou inexistente!");
    }

    getchar();
    getchar();
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    system("color 27");
    geraBaralho();
    embaralhaBaralho();

    system("cls");

    inicializa(); //faz todos os montes apontarem para NULL
    distribuirMesa();
    imprime();


    char op;
    while((primesa[0]!=NULL)||(primesa[1]!=NULL)||(primesa[2]!=NULL)||(primesa[3]!=NULL)||(primesa[4]!=NULL)||(primesa[5]!=NULL)||(primesa[6]!=NULL)||(primesa[7]!=NULL)||(temp[0]!=NULL)||(temp[1]!=NULL)||(temp[2]!=NULL)||(temp[3]!=NULL))
    {
        printf("O que deseja fazer? [1-Mesa para Temporario][2-Temporario para Mesa][3-Mesa para Naipe][4-Mesa para Mesa]\n                    [5-Temp para Naipe][6-Mesa para Mesa (varias)][7-Naipe para Temp][8-Naipe para Mesa]\n");
        scanf("%c",&op);

        switch(op)
        {
        case '1':
        {
            moveMesaTemp();
            break;
        }
        case '2':
        {
            moveTempMesa();
                break;
            }
        case '3':
        {
            moveMesaNaipe();
            break;
        }
        case '4':
        {
            moveMesaMesa();
            break;
        }
        case '5':
        {
            tempnaipe();
            break;
        }
        case '6':
        {
            movevarias();
            break;
        }
        case '7':{
            naipetemp();
            break;
        }
        case '8':{
            naipemesa();
            break;
        }
        case 'f':{
            goto fim;
        }
        default :{

        }

        }
        op = '0';
        system("cls");
        imprime();
    }

    fim:;
    system("cls");
    system("color 4F");
    printf("                          .::::::::::::::::::::::::::::::::::::::::::::::::.                    \n");
    printf("                          .:::::..:::::::::::::::::::::::::::::::::::::::::.                    \n");
    printf("            ............. .::..    ..::::::::::::::::::::::::::::::::::::::. .............      \n");
    printf("           .::::::::::::::::::.   .:::::::::::::::::::::::::::::::::::::::::::::::::::::::.     \n");
    printf("           :::::::::::::::::::::..:::::::::::::::::::::::::::::::::::::::::::::::::::::::::     \n");
    printf("           :::::          .::::::::::  ::::::::::::::::::::::::::::::::::::.          :::::     \n");
    printf("           .::::          .::::::::::::::::::::::::::::::::::::::::::::::::.          ::::.     \n");
    printf("            ::::          .::::::::::::::::::::::::::::::::::::::::::::::::.          ::::      \n");
    printf("            ::::          .::::::::::::::::::::::::::::::::::::::::::::::::.          ::::      \n");
    printf("            :::::         .::::::::::::::::::::::::::::::::::::::::::::::::.         :::::      \n");
    printf("             ::::          .::::::::::::::::::::::::::::::::::::::::::::::.          ::::       \n");
    printf("             :::::         .::::::::::::::::::::::::::::::::::::::::::::::.         :::::       \n");
    printf("              ::::          .::::::::::::::::::::::::::::::::::::::::::::.          ::::        \n");
    printf("              .::::         .::::::::::::::::::::::::::::::::::::::::::::.         ::::.        \n");
    printf("               .::::.        .::::::::::::::::::::::::::::::::::::::::::.        .::::.         \n");
    printf("                .:::::.       .:::::::::::::::::::::::::::::::::::::::::       .:::::.          \n");
    printf("                  .:::::..     .:::::::::::::::::::::::::::::::::::::::     ..:::::.            \n");
    printf("                    .:::::::... :::::::::::::::::::::::::::::::::::::: ...:::::::.              \n");
    printf("                      ..::::::::::::::::::::::::::::::::::::::::::::::::::::::..                \n");
    printf("                           ..::::::::::::::::::::::::::::::::::::::::::::..                    \n");
    printf("                                    ::::::::::::::::::::::::::::::                             \n");
    printf("                                      ::::::::::::::::::::::::::                               \n");
    printf("                                         ::::::::::::::::::::                                  \n");
    printf("                                            ::::::::::::::                                     \n");
    printf("                                               .:::::!.                                        \n");
    printf("                                               .::::::.               PARABENS!!!!             \n");
    printf("                                               .::::::.               PARABENS!!!!             \n");
    printf("                                              .::::::::.              PARABENS!!!!             \n");
    printf("                                              .::::::::.              PARABENS!!!!             \n");
    printf("                                              ::::::::::              PARABENS!!!!             \n");
    printf("                                             .::::::::::.             PARABENS!!!!             \n");
    printf("                                            .::::::::::::.                                     \n");
    printf("                                      ::::::::::::::::::::::::::                               \n");
    printf("                                    .::::::::::::::::::::::::::::.                             \n");
    printf("                                    ::::::::::::::::::::::::!!!!!:                              \n");
    printf("                           .!############################################!.                     \n");
    printf("                           .!###::.Universidade Federal de Itajub%c :!:###!.                     \n",160);
    printf("                           .!###:............Free Taty ...:::::::::::::###!.                     \n");
    printf("                           .!###:.......................::::::::::::::###!.                     \n");
    printf("                           .!###:.....Criado e Desenvolvido por:::::::###!.                     \n");
    printf("                           .!###:::...... Ryan Alves Mazzeu ::::::::!:###!.                     \n");
    printf("                           .!###!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!###!.                     \n");
    printf("                        .!!!!####################################HELP ME##!!!.                 \n");
    printf("                        :####################################################:                 \n");
    printf("                           .           .. .. ........... ...  ..............                   \n");

    system("pause");


    tCarta *faxina,*faxina1;




    for(int i=0; i<4; i++)
    {
        faxina = primNaipe[i];
        faxina1= primNaipe[i];

        free(temp[i]);


        while(faxina1!=NULL)
        {
            faxina1 = faxina1->proximo;
            free(faxina);
            faxina = faxina1;
        }
    }


    return 0;
}

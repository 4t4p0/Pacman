#include "raylib.h"
#include <stdio.h>
//Para rand() e srand()
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
//Necessário para usar a função sleep
#include <unistd.h>

#define larguraTela 800
#define alturaTela 640
#define tamanho 20
#define linhas 32
#define colunas 40
//************VARIÁVEIS DO CÓDIGO************
//Variável que guarda em qual mapa o jogo esta
int NumMapaTitulo = 1;
//Variável que mostra o score na tela
int scoreMostrado = 0;
//Variável que guarda a selecao do menu
int selecao = 1;
//selecao = 1 Menu
//selecao = 2 Jogo
//selecao = 3 Carrega um save
//selecao = 4 Exibi os scores
//selecao = 5 Sai do jogo
//selecao = 6 Pausa o jogo
//Variável que armazena a posição da opção escolhida no menu
int posicaomenu = 4;
//Variável que armazena a posição da opção escolhida no menu dos saves
int posicaocarregarjogo = 2;
//Variável que armazena a posição da opção escolhida no menu do pause dos saves
int posicaopausesave = 2;
//Variável que armazena a posição da opção escolhida no menu do pause
int posicaopause = 2;
//Variável que armazena qual o jogo deve ser carregado
int qualjogocarregar = 1;
//Variável que armazena a linha que o jogador está
int linhaJogador = 0;
//Variável que armazena a coluna que o jogador está
int colunaJogador = 0;
//Variável interadora
int numFantasmas = 0;
//Direção inicial do Pac-Man
int direcaoPacman = 1;
//Número alétório para o a movimentação dos fantasmas
int numeroF1=8;
int numeroF2=8;
int numeroF3=8;
int numeroF4=8;
int numeroF5=8;
//Variável que armazena o número de vidas do jogador
int vidas = 3;
//Posição inial do fantasma em x
int posiInicialXP = 0;
//Posição incial dos fantasmas em y
int posiInicialYP = 0;
//Variável que guarada o último número randomico gerado
int ultimo_numero1=-1;
int ultimo_numero2=-1;
int ultimo_numero3=-1;
int ultimo_numero4=-1;
int ultimo_numero5=-1;
//variável que guarda o número de pastilhas
int numPastilhas=0;
//variável que sinaliza qual mapa sera carregado
int numMapa=0;
//Variável que delimita até qual número será icrementado o número do mapa
int aux=0;
//Mapa do jogo
char mapa[linhas][colunas];
//tempo decorrido desde que começou o jogo
float TempoDecorrido;
//variável que determina o intervalo de tempo inicial para os faantasmas mudarem a velocidade de movimento
float intervaloDeTempo=120.0;
//variável acumuladora para controlar a velocidade do pacman
float tempoDesdeUltimoMovimento = 0.0;
//Variável acumuladora para controlar a velcidade do fantasma
float TempoFantasmaVe;
float TempoFantasmaA;
float TempoFantasmaAma;
float TempoFantasmaR;
float TempoFantasmaL;
float aux2;
//aciona o modo perseguição do fantasma
bool perseguirF1=false;
bool perseguirF2=false;
bool perseguirF3=false;
bool perseguirF4=false;
bool perseguirF5=false;
//aciona o modo andar do fantasma
bool andarF1=false;
bool andarF2=false;
bool andarF3=false;
bool andarF4=false;
bool andarF5=false;
//Variável que trava algumas funções quando o jogo é zerado para possibilitar o reinicio
bool arquivoNull=false;
//************VARIÁVEIS DO CÓDIGO*************


//************ESTRUTURAS DO CÓDIGO************
//Estrutura que aramzena as informações do fantasma
typedef struct Fantasma
{
    int linha;
    int coluna;
    int posiInicialXF;
    int posiInicialYF;
} Fantasma;
Fantasma fantasmas[5]; // Assumindo que no máximo teremos 5 fantasmas

//Estrutura que salva o score e o nome de um jogador
typedef struct tipo_score
{
    char nome[30];
    int score;
} TIPO_SCORE;
TIPO_SCORE novoJogador;

//Estrutura que salva as informações de um certo save
typedef struct info_save
{
    int vidas; // Guarda as vidas
    int pontos; //Guarda os pontos
    int numMapaS; //Guarda o número do mapa
    int NumMapaTituloS; //Guarda o título do mapa
    int posiInicialXp; //Guarda a coluna em que o PACMAN esta
    int posiInicialYp; //Guarda a linha em que o PACMAN esta
    float TempoDecorridoS; //Guarda o tempo decorrido
    float intervaloDeTempoS; //Guarda o tempo em que o jogo esta
    float aux2S;
    int fantasmaVermelhoX; //Guarda a coluna em que do fantasma vermelho
    int fantasmaVermelhoY; //Guarda a linha em que do fantasma vermelho
    int fantasmaAzulX; //Guarda a coluna em que do fantasma azul
    int fantasmaAzulY; //Guarda a linha em que do fantasma azul
    int fantasmaAmareloX; //Guarda a coluna em que do fantasma amarelo
    int fantasmaAmareloY;//Guarda a linha em que do fantasma amarelo
    int fantasmaRosaX; //Guarda a coluna em que do fantasma rosa
    int fantasmaRosaY; //Guarda a linha em que do fantasma rosa
    int fantasmaLaranjaX; //Guarda a coluna em que do fantasma laranja
    int fantasmaLaranjaY; //Guarda a linha em que do fantasma laranja
} INFO_SAVE;
//************ESTRUTURAS DO CÓDIGO************


//************FUNÇÕES DO CÓDIGO************
//Função que carrega o menu do jogo
void menu(int posicaomenu);
//Carrega os elementos do mapa
void carregarElementosInterativos();
//Função que desenha os elementos do jogo
void desenharJogo();
//Função que desenha os fanstasmas
void desenharfantasma(int i);
//Função que carrega um mapa
void carregarMapa(char *nomearquivo);
//Função que muda o numero do mapa para o proximo EX:(Mapa01.txt para Mapa02.txt)
void incrementarNumeroMapa(char *nomearquivo);
//Função que atualiza o jogo de acordo com o tempo
void atualizarJogo(float tempo);
//Função que organiza o score
void organizarscore(TIPO_SCORE *dados, int nelem);
//Função que lê o score
void lerscore(const char *nomearquivo);
//Função para inserir um novo score
void inserirscore(const char *nomearquivo);
//Função que cria um arquivo contendo uma estrutura INFO_SAVE, ceontendo as informações de um jogo
void criarinfosave(const char *nomearquivo, INFO_SAVE info);
//Função que carrega uma estrutura INFO_SAVE de um save
void carregarinformacoesmapa(const char *nomearquivo);
//Função que salva um save.txt em um arquivo
void salvarjogo(const char *nomearquivo);
//Função que acessa o menu dos saves
void carregarjogo(int posicaocarregarjogo);
//Função que vê se um save pode ser jogado ou não
int saveehvalido(int posicaocarregarjogo);
//Função que certifica que todos os n fantasmas estão dentro do jogo
void ajustedeposicao();
//Função que faz os fantasmas sairem da posição inicial
void sairDaPoscaoInicial(int fantasmaAsair);
//Fução usada caso o PACMAN morra
void morte();
/*
A função fantasmaperseguir faz o fantasma X perseguir o PACMAN
A função fantasmabuscar faz o fantasma X se movimentar aleatoriamente
*/
void fantasmaVermelhoPerseguir(float intervaloFantasmaVe);
void fantasmaVermelhoBuscar(float intervaloFantasmaVe);
void fantasmaAzulBuscar(float intervaloFantasmaA);
void fantasmaAzulPerseguir(float intervaloFantasmaA);
void fantasmaAmareloBuscar(float intervaloFantasmaAma);
void fantasmaAmareloPerseguir(float intervaloFantasmaAma);
void fantasmaRosaBuscar(float intervaloFantasmaR);
void fantasmaRosaPerseguir(float intervaloFantasmaR);
void fantasmaLaranjaBuscar(float intervaloFantasmaL);
void fantasmaLaranjaPerseguir(float intervaloFantasmaL);
//As 5 funções abaixo retornam numeros aleatorios para a movimentação dos fantasmas
int movimentoaleatorioF1();
int movimentoaleatorioF2();
int movimentoaleatorioF3();
int movimentoaleatorioF4();
int movimentoaleatorioF5();
//************FUNÇÕES DO CÓDIGO************


//************INICIO DO CÓDIGO************
int main()
{
//Inicia a janela
    InitWindow(larguraTela, alturaTela, "pacman");
    //Configura o FPS para 60
    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        /*
        Para cada caso no switch(qualjogocarregar)
        Carrega um jogo a partir da variável qualjogocarregar
        Reseta a variável qualjogocarregar para não carregar o jogo mais de uma vez
        */
        switch (qualjogocarregar)
        {
        case 1:
            carregarMapa("Mapa01.txt");
            qualjogocarregar = 0;
            break;
        case 2:
            carregarMapa("saves/save01.txt");
            carregarinformacoesmapa("saves/save01.bin");
            qualjogocarregar = 0;
            break;
        case 3:
            carregarMapa("saves/save02.txt");
            carregarinformacoesmapa("saves/save02.bin");
            qualjogocarregar = 0;
            break;
        case 4:
            carregarMapa("saves/save03.txt");
            carregarinformacoesmapa("saves/save03.bin");
            qualjogocarregar = 0;
            break;
        }
        //No caso do jogador estar no menu
        if (selecao == 1)
        {
            //Se apertar ⬇️ ou S, decresce a variável posiçãomenu
            if ((IsKeyPressed(KEY_DOWN) && posicaomenu > 1) || (IsKeyPressed(KEY_S) && posicaomenu > 1))
            {
                posicaomenu--;
            }
            //Se apertar ⬆️ ou W, acresce a variável posiçãomenu
            if ((IsKeyPressed(KEY_UP) && posicaomenu < 4) ||(IsKeyPressed(KEY_W) && posicaomenu < 4))
            {
                posicaomenu++;
            }
            //Se apertar ENTER escolhe oque deseja fazer
            if (IsKeyPressed(KEY_ENTER))
            {
                selecao = selecao + fabs(posicaomenu - 5);
            }
            //Chama a função menu, que desenha as opções na tela
            menu(posicaomenu);
        }
        //Jogador entra no jogo
        else if (selecao == 2)
        {
            if(IsKeyPressed(KEY_TAB))
            {
                selecao = 6;
            }
            float tempo = GetFrameTime();
            atualizarJogo(tempo);
            desenharJogo();
        }

        //Jogador entra na tela de saves
        else if (selecao == 3)
        {
            //Se apertar SPACE
            if (IsKeyPressed(KEY_SPACE))
            {
                //Volta para o menu normal
                selecao = 1;
            }
            //Se apertar ⬆️ ou W, acresce a variável posiçãocarregarjogo
            if ((IsKeyPressed(KEY_UP) && posicaocarregarjogo <= 1 )||(IsKeyPressed(KEY_W) && posicaocarregarjogo <= 1))
            {
                posicaocarregarjogo++;
            }
            //Se apertar ⬇️ ou S, decresce a variável posiçãocarregarjogo
            if ((IsKeyPressed(KEY_DOWN) && posicaocarregarjogo >= 1 )|| (IsKeyPressed(KEY_S) && posicaocarregarjogo >= 1))
            {
                posicaocarregarjogo--;
            }
            //Se apertar ENTER escolhe um save para jogar
            if(IsKeyPressed(KEY_ENTER))
            {
                //Se for o primeiro save
                if (posicaocarregarjogo == 2)
                {
                    //Verifica se um save eh valido para jogar
                    if(saveehvalido(posicaocarregarjogo) != 0)
                    {
                        //Muda a váriável  qualjogocarregar para dizer qual nome do arquivo deve ser carregado
                        qualjogocarregar = 2;
                        //Muda a seleção para 2, pois o usuario entra no jogo
                        selecao = 2;
                    }
                }
                //Se for o segundo save
                else if (posicaocarregarjogo == 1)
                {
                    //Verifica se um save eh valido para jogar
                    if(saveehvalido(posicaocarregarjogo) != 0)
                    {
                        //Muda a váriável  qualjogocarregar para dizer qual nome do arquivo deve ser carregado
                        qualjogocarregar = 3;
                        //Muda a seleção para 2, pois o usuario entra no jogo
                        selecao = 2;
                    }
                }
                //Se for o terceiro save
                else if (posicaocarregarjogo == 0)
                {
                    //Verifica se um save eh valido para jogar
                    if(saveehvalido(posicaocarregarjogo) != 0)
                    {
                        //Muda a váriável  qualjogocarregar para dizer qual nome do arquivo deve ser carregado
                        qualjogocarregar = 4;
                        //Muda a seleção para 2, pois o usuario entra no jogo
                        selecao = 2;
                    }
                }
            }
            //Função que carrega os saves
            carregarjogo(posicaocarregarjogo);
            DrawText("SAVES", 230, 100, 80, WHITE);
        }
        //Dentro da tela de ranking
        else if (selecao == 4)
        {
            //Se apertar SPACE
            if (IsKeyPressed(KEY_SPACE))
            {
                //Volta para o menu normal
                selecao = 1;
            }
            //Função que lê o ranking e imprime na tela
            lerscore("ranking.bin");
        }
        //Sai do jogo
        else if (selecao == 5)
        {
            CloseWindow();
        }
        //Jogo pausado
        else if (selecao == 6)
        {
            if(IsKeyPressed(KEY_TAB))
            {
                selecao = 2;
            }
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("JOGO PAUSADO", 90, 100, 80, WHITE);
            DrawText("Continuar", 270, 220, 50, WHITE);
            DrawText("Salvar", 300, 340, 50, WHITE);
            DrawText("Sair", 330, 460, 50, WHITE);
            DrawText("Aperte ENTER para escolher", 10, 600, 35, WHITE);
            //Se apertar ⬆️ ou W, acresce a variável posiçaopause
            if ((IsKeyPressed(KEY_UP) && posicaopause <= 1 )||(IsKeyPressed(KEY_W) && posicaopause <= 1))
            {
                posicaopause++;
            }
            //Se apertar ⬇️ ou S, decresce a variável posiçaopause
            if ((IsKeyPressed(KEY_DOWN) && posicaopause >= 1 )|| (IsKeyPressed(KEY_S) && posicaopause >= 1))
            {
                posicaopause--;
            }
            //Desenha um retangulo para auxiliar na escolha
            DrawRectangle(220, 473 - (posicaopause * 120), 40, 20, WHITE);
//Se apertar ENTER(Escolher)
            if(IsKeyReleased(KEY_ENTER))
            {
                switch(posicaopause)
                {
                //Nao faz nada
                case 3:
                    break;
                //Volta para o jogo
                case 2:
                    selecao = 2;
                    break;
                //Entra no menu dos saves
                case 1:
                    bool menupausesave = 1;
                    while (menupausesave)
                    {
//Se apertar ⬆️ ou W, acresce a variável posiçaopausesave
                        if ((IsKeyPressed(KEY_UP) && posicaopausesave <= 1 )||(IsKeyPressed(KEY_W) && posicaopausesave <= 1))
                        {
                            posicaopausesave++;
                        }
                        //Se apertar ⬇️ ou S, decresce a variável posiçaopausesave
                        if ((IsKeyPressed(KEY_DOWN) && posicaopausesave >= 1 )|| (IsKeyPressed(KEY_S) && posicaopausesave >= 1))
                        {
                            posicaopausesave--;
                        }
                        if (IsKeyPressed(KEY_SPACE))
                        {
                            menupausesave = 0;
                        }
                        if (IsKeyPressed(KEY_ENTER))
                        {
                            INFO_SAVE estejogo;
                            estejogo.vidas = vidas;
                            estejogo.pontos = novoJogador.score;
                            estejogo.numMapaS=numMapa;
                            estejogo.posiInicialXp=posiInicialXP;
                            estejogo.posiInicialYp=posiInicialYP;
                            estejogo.NumMapaTituloS=NumMapaTitulo;
                            estejogo.intervaloDeTempoS=intervaloDeTempo;
                            estejogo.TempoDecorridoS=TempoDecorrido;
                            estejogo.aux2S=aux2;
                            estejogo.fantasmaVermelhoX=fantasmas[0].coluna;
                            estejogo.fantasmaVermelhoY=fantasmas[0].linha;
                            estejogo.fantasmaAzulX=fantasmas[1].coluna;
                            estejogo.fantasmaAzulY=fantasmas[1].linha;
                            estejogo.fantasmaAmareloX=fantasmas[2].coluna;
                            estejogo.fantasmaAmareloY=fantasmas[2].linha;
                            estejogo.fantasmaRosaX=fantasmas[3].coluna;
                            estejogo.fantasmaRosaY=fantasmas[3].linha;
                            estejogo.fantasmaLaranjaX=fantasmas[4].coluna;
                            estejogo.fantasmaLaranjaY=fantasmas[4].linha;
                            switch (posicaopausesave)
                            {
                            case 2:
                                criarinfosave("saves/save01.bin", estejogo);
                                salvarjogo("saves/save01.txt");
                                break;
                            case 1:
                                criarinfosave("saves/save02.bin", estejogo);
                                salvarjogo("saves/save02.txt");
                                break;
                            case 0:
                                criarinfosave("saves/save03.bin", estejogo);
                                salvarjogo("saves/save03.txt");
                                break;
                                //Reseta todo o jogo
                                selecao = 1;
                                NumMapaTitulo=1;
                                vidas=3;//resta as vidas
                                intervaloDeTempo=120;
                                numPastilhas=0;//reseta o número de pastilhas
                                carregarMapa("Mapa01.txt");//carrega o primeiro mapa
                                numMapa=0;//reseta o mapa a ser carregado
                                novoJogador.score=0;
                            }
                        }
                        DrawText("Escolha um slot", 230, 80, 40, WHITE);
                        DrawText("para salvar", 260, 120, 40, WHITE);
                        carregarjogo(posicaopausesave);
                    }
                    break;
                case 0:
                    //Reseta todo o jogo
                    selecao = 1;
                    NumMapaTitulo=1;
                    vidas=3;//resta as vidas
                    intervaloDeTempo=120;
                    numPastilhas=0;//reseta o número de pastilhas
                    carregarMapa("Mapa01.txt");//carrega o primeiro mapa
                    numMapa=0;//reseta o mapa a ser carregado
                    novoJogador.score=0;
                    break;
                }
            }
            EndDrawing();
        }
    }
    CloseWindow();
    return 0;
}
//Função que carrega as opções do menu
void menu(int posicaomenu)
{
    BeginDrawing();
    DrawText("PACMAN", 190, 80, 100, WHITE);
    //Desenha as opções
    DrawText("NOVO JOGO", 240, 200, 50, WHITE);
    DrawText("CARREGAR JOGO", 180, 300, 50, WHITE);
    DrawText("MOSTAR HIGHSCORES", 125, 400, 50, WHITE);
    DrawText("SAIR DO JOGO", 200, 500, 50, WHITE);
    DrawText("Aperte ENTER para escolher", 10, 600, 35, WHITE);
    //Desenha um retângulo para auxiliar na escolha
    DrawRectangle(60, 610 - (posicaomenu * 100), 40, 20, WHITE);
    ClearBackground(BLACK);
    EndDrawing();
}
//Função que carrega uma estrutura do tipo INFO_SAVE dentro de um arquivo e passa para o jogo
void carregarinformacoesmapa(const char *nomearquivo)
{
    //Variável que receberá as informações do arquivo
    INFO_SAVE info;

    // Abre o arquivo em modo de leitura binária
    FILE *arquivo = fopen(nomearquivo, "rb");

    //Checa se concegue abrir o arquivo
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo");
        return;
    }
    // Lê os dados do arquivo e os armazena na estrutura
    size_t quantidade = fread(&info, sizeof(INFO_SAVE), 1, arquivo);

    //Checa se a leitura deu certo
    if (quantidade != 1)
    {
        printf("Erro ao ler do arquivo");
    }
    fclose(arquivo);  // Fecha o arquivo

    //Passa todos os dados que estavam no arquivo para os dados do jogo
    novoJogador.score = info.pontos;
    vidas = info.vidas;
    numMapa=info.numMapaS;
    fantasmas[0].coluna=info.fantasmaVermelhoX;
    fantasmas[0].linha=info.fantasmaVermelhoY;
    fantasmas[1].coluna=info.fantasmaAzulX;
    fantasmas[1].linha=info.fantasmaAzulY;
    fantasmas[2].coluna=info.fantasmaAmareloX;
    fantasmas[2].linha=info.fantasmaAmareloY;
    fantasmas[3].coluna=info.fantasmaRosaX;
    fantasmas[3].linha=info.fantasmaRosaY;
    fantasmas[4].coluna=info.fantasmaLaranjaX;
    fantasmas[4].linha=info.fantasmaLaranjaY;
    NumMapaTitulo=info.NumMapaTituloS;
    posiInicialXP=info.posiInicialXp;
    posiInicialYP=info.posiInicialYp;
    intervaloDeTempo=info.intervaloDeTempoS;
    TempoDecorrido=info.TempoDecorridoS;
    aux2=info.aux2S;
}
//Função que cria o arquivo .txt de um mapa para ser salvo
void salvarjogo(const char *nomearquivo)
{
    //Abre o arquivo na forma de escrita
    FILE *arquivo = fopen(nomearquivo, "w");

    //Adiciona 2 linhas sem nada no arquivo
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            fputc(' ', arquivo);
        }
        fputc('\n', arquivo);
    }

    //Escreve o mapa no arquivo
    for (int i = 2; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if(mapa[i][j]=='\n')
            {
                mapa[i][j]='\0';
            }
            // Escreve o caractere mapa[i][j] no arquivo
            fputc(mapa[i][j], arquivo);
            fflush(arquivo);
        }
        if(i!=31)
        {
            fputc('\n', arquivo);
        }  // Adiciona uma nova linha após cada linha do mapa
    }
    fclose(arquivo);
}
/*
Função que pega as seguintes informações:
-Posição dos fantasmas
-Posição do PACMAN
-Número de pastilhas dentro do jogo
*/
void carregarElementosInterativos()
{
    numFantasmas=0;
    numPastilhas=0;
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            //Se achar o caractere M
            if(mapa[i][j]=='M')
            {
                //Pega as informações da posição do fanstasma
                fantasmas[numFantasmas].posiInicialXF=j;
                fantasmas[numFantasmas].posiInicialYF=i;
                fantasmas[numFantasmas].coluna=fantasmas[numFantasmas].posiInicialXF;
                fantasmas[numFantasmas].linha=fantasmas[numFantasmas].posiInicialYF;
                numFantasmas++;
            }
            //Se achar o caractere J
            if(mapa[i][j]=='J')
            {
                //Pega as informações da posição do PACMAN
                posiInicialYP=i;
                posiInicialXP=j;
            }
            //Se o caractere for . ou S
            if(mapa[i][j]=='.'||mapa[i][j]=='P')
            {
                //Adiciona o numero de pastilhas
                numPastilhas++;
            }
        }
    }
}
//Função que organiza o score
//PS: A função só organiza o último colocado em relação aos outros
void organizarscore(TIPO_SCORE *dados, int nelem)
{
    int i;
    for ( i = 1; i < nelem; i++) //Varre todos os nelem elementos
    {
        TIPO_SCORE chave = dados[i];
        int j = i - 1;
        while (j >= 0 && dados[j].score < chave.score)
        {
            dados[j + 1] = dados[j];
            j = j - 1;
        }
        dados[j + 1] = chave;
    }
}
//Função que lê o score e imprime na tela do usuario
void lerscore(const char *nomearquivo)
{
    //Abre o arquivo no modo leitura
    FILE *arquivo = fopen(nomearquivo, "r");
    //Se o arquivo não existir, imprime erro e retorna
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    //Cria um estrutura de dados do TIPO_SCORE que vai receber as informações do arquivo
    TIPO_SCORE dados[5];
    //Lê o arquivo e guarda o número de estruturas do TIPO_SCORE na variável quantidade
    size_t quantidade = fread(dados, sizeof(TIPO_SCORE), 5, arquivo);
    //Se não houver exatamente 5 elementos, imprime erro e retorna
    if (quantidade != 5)
    {
        printf("Erro ao ler do arquivo\n");
        fclose(arquivo);
        return;
    }
    fclose(arquivo);
    BeginDrawing();
    ClearBackground(BLACK);
    //Desenha o score
    DrawText("SCORE", 230, 100, 80, WHITE);




    //Uso do laço apenas para dar uma distância entre a exibição de cada nome
    for (int i = 0; i < 5; i++)
    {
        //Exibe os nomes e pontuações na tela
        DrawText(dados[i].nome, 70, 200 + (70 * i), 30, WHITE); //NOMES
        //Armazena a string o numero inteiro convertido em string
        char a[7];
        //Transforma um inteiro em uma string para poder ser desenhado
        sprintf(a, "%d", dados[i].score);
        DrawText(a, 640, 200 + (70 * i), 30, WHITE); //SCORE
    }
    DrawText("Aperte SPACE para sair", 10, 600, 35, WHITE);
    EndDrawing();
}
//Função que será insere um novo score dentro do arquivo do score
//PS:Não é necessario ver se o novo score é maior ou menor que o último jogador, esta função faz isso
void inserirscore(const char *nomearquivo)
{
    bool mensagem=false;//variável que trava a tela para mostrar a mensagem necessária
    TIPO_SCORE dados[5];//variável que amazena o conteúdo armazenado no arquivo binário
    FILE *arquivo = fopen(nomearquivo, "rb");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura\n");
        return;
    }
    size_t read = fread(dados, sizeof(TIPO_SCORE), 5, arquivo);
    if (read != 5)
    {
        printf("Erro ao ler o arquivo\n");
        fclose(arquivo);
        return;
    }
    fclose(arquivo);
    if (novoJogador.score < dados[4].score)
    {
        //caso a pontuação não seja maior que a última do ranking
        BeginDrawing();
        if(vidas==0)
        {
            //caso a função seja chamada se quando o jogador morre
            DrawText("Você morreu e sua pontuação não é alta o suficiente para entrar no ranking :(",0, 100, 20, WHITE);
        }
        else
        {
            //caso a função seja chamada quando o jogo acaba
            DrawText("Sua pontuação não é alta o suficiente para entrar no ranking :(",0, 100, 20, WHITE);
        }
        ClearBackground(BLACK);
        EndDrawing();
        sleep(5);
    }
    else
    {
        // se a pontuação seja alta o sufuciente para entrar no ranking
        int k=0;//variável contadora
        for(int i=0; i<30; i++)
        {
            novoJogador.nome[i]=' ';
        }//limpa p vetor
        mensagem=true;
        while(mensagem==true)
        {
            if(k<30)
            {
                char tecla = GetCharPressed();//função que retorna a tecla precionada
                if (tecla >= 32 && tecla <= 125)   // Verifica se a tecla pressionada é um caractere válido
                {
                    novoJogador.nome[k] = tecla;//adiciona o caractere ao vetor nome
                    k++;
                }
                if(IsKeyPressed(KEY_BACKSPACE))
                {
                    novoJogador.nome[k-1]=' ';//exclui o caractere caso o backspace seja apretado
                    k--;
                }
            }
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Digite seu nome para registrar no ranking, depois aperte enter:", 10, 10, 20, WHITE);
            DrawText(novoJogador.nome, 10, 40, 20, WHITE);
            EndDrawing();
            if(IsKeyPressed(KEY_ENTER)==true)
            {
                //quando o jogador precinar o enter
                dados[4] = novoJogador;//todo o conteúdp na última posição do vetor é atualizado
                organizarscore(dados, 5);//o ranking é organizar
                arquivo = fopen(nomearquivo, "wb");//
                if (arquivo == NULL)
                {
                    printf("Erro ao abrir o arquivo para escrita\n");
                    return;
                }
                fwrite(&dados, sizeof(TIPO_SCORE), 5, arquivo);
                fclose(arquivo);
                mensagem=false;
            }
        }
    }
}
//Função que cria um arquivo binario contendo uma estrutura INFO_SAVE
//Este arquivo deve ter as informações de um save(posições, vidas, pontos...)
void criarinfosave(const char *nomearquivo, INFO_SAVE info)
{
    //Abre o arquivo na forma de escrita
    FILE *arquivo = fopen(nomearquivo, "wb");
    //Se o arquivo não existir, imprime erro e retorna
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }
    //Escreve a estrutura do tipo INFO_SAVE dentro do arquivo
    fwrite(&info, sizeof(INFO_SAVE), 1, arquivo);


    //Fecha o arquivo
    fclose(arquivo);
}
//Função que carrega o mapa de um arquivo de texto
void carregarMapa(char *nomearquivo)
{
    aux2=intervaloDeTempo;
    //"Limpa o vetor mapa"
    for(int i=0; i<linhas; i++)
    {
        for(int j=0; j<colunas; j++)
        {
            mapa[i][j]=' ';//inicia o vetor com espaços vazios para conseguir mudar o mapa
        }
    }
    //importa o arquivo no modo leitura
    FILE *arquivo = fopen(nomearquivo, "r");
    if (arquivo!=NULL)
    {
        for (int i = 0; i < linhas; i++)
        {
            fgets(mapa[i], 42, arquivo);
            //se houver um arquivo, os 42(incluindo o \0 e \n) caracteres vão ser atribuidos a cada linha do mapa;
        }
        fclose(arquivo);//encerra o carregamento do mapa
        carregarElementosInterativos();
        //função que carrega os fantasmas, o pacman e conta as pastilhas
    }
    else
    {
        NumMapaTitulo=1;
        vidas=3;//resta as vidas
        arquivoNull=true;//variável para travar as outras funções do código
        intervaloDeTempo=120;
        inserirscore("ranking.bin");//chama a função para verificar se a pontuação é alta o sufuciente para entrar no raking e inclui ela caso seja alta o sufiente
        arquivoNull=false;//libera as outras funções do código
        selecao=1;//volta para o menu principal
        numPastilhas=0;//reseta o número de pastilhas
        carregarMapa("Mapa01.txt");//carrega o primeiro mapa
        numMapa=0;//reseta o mapa a ser carregado
        novoJogador.score=0;
    }
}
//Muda o último digito do char *nomedoarquivo para poder ler o proximo mapa
void incrementarNumeroMapa(char *nomearquivo)
{
    int tamanhoS = strlen(nomearquivo);
    int soma = 1;
    for (int i = tamanhoS - 1; i >= 0; i--)
    {
        if (nomearquivo[i] >= '0' && nomearquivo[i] <= '9')
        {
            nomearquivo[i] += soma;//muda o valor do último digito
            if (nomearquivo[i] > '9')
            {
                nomearquivo[i] = '0';//se for maior que o valor de 9 na tabela ESCII vira 0
                soma = 1; // Continua o incremento para o próximo dígito
            }
            else
            {
                soma = 0; // Incremento completo
            }
        }
    }
    aux--;//variável que sinaliza quando o programa deve passar o valor no nomearquivo como parâmetro
    if(aux==0)
    {
        if(arquivoNull==true)
        {
            strcpy(nomearquivo,"NULL");//trava o incremento do mapa caso o jogo acaba para possibilitar o funcionamento da tela de zeramento
            carregarMapa(nomearquivo);
        }
        else
        {
            intervaloDeTempo-=20;
            carregarMapa(nomearquivo);//carrega o próximo mapa
        }
    }
}
//Função que ajusta todos os parametros de acordo com o tempo
void atualizarJogo(float tempo)
{
    ajustedeposicao();
    //Se a quantidade de pastilhas for zero(Jogo teoricamente acabou)
    if(numPastilhas==0)
    {
        //O programa incrementa o numero do mapa, começando do 01 até o desejado
        NumMapaTitulo++;
        numMapa++;//indica quantas vezes o incremento deve acontecer
        //A variável auxiliar serve para controlar o momento em que a função é chamada
        aux=numMapa;
        char nome[20]="Mapa01.txt";
        for(int i=numMapa; i>0; i--)
        {
            incrementarNumeroMapa(nome);
        }
        //reseta todas as configurações
        numFantasmas=0;
        TempoDecorrido=0;
        for(int i=0; i<linhas; i++)
        {
            for(int j=0; j<colunas; j++)
            {
                if(mapa[i][j]=='M') //desenha os fantasmas nas posições originais
                {
                    fantasmas[numFantasmas].coluna=fantasmas[numFantasmas].posiInicialXF;
                    fantasmas[numFantasmas].linha=fantasmas[numFantasmas].posiInicialYF;
                    numFantasmas++;
                }
            }
        }
        vidas=3;
        ajustedeposicao();
    }
    //Checa se o PACMAN e algum dos fantasmas tem a mesma posição, se tiverem, PACMAN morre
    morte();
    //Incrementa o tempo para todos os parametros que precisam dele
    float intervaloMovimento=0.09;
    TempoDecorrido+=tempo;
    tempoDesdeUltimoMovimento += tempo;//incrementa o tempo desde o último frame
    TempoFantasmaVe += tempo;
    TempoFantasmaA +=tempo;
    TempoFantasmaAma +=tempo;
    TempoFantasmaR +=tempo;
    TempoFantasmaL+=tempo;
    if (tempoDesdeUltimoMovimento >= intervaloMovimento)//testa se um intervalo de tempo decorrido esperado passou
    {
        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                if (mapa[i][j] == 'J')
                {
                    linhaJogador = i;
                    colunaJogador = j;
                    //mapeia a posição do pacman
                }
            }
        }
        //Checa se é possivel andar para a direita
        if (arquivoNull==false&&(IsKeyDown(KEY_RIGHT)||IsKeyDown(KEY_D)) && (mapa[linhaJogador][colunaJogador + 1] == ' ' || mapa[linhaJogador][colunaJogador + 1] == '.'||mapa[linhaJogador][colunaJogador + 1] == 'P'||mapa[linhaJogador][colunaJogador + 1] == 'F'||mapa[linhaJogador][colunaJogador + 1] == 'M'))
        {
            if(mapa[linhaJogador][colunaJogador + 1] == 'F')
            {
                novoJogador.score+=30;
            }
            else if(mapa[linhaJogador][colunaJogador + 1] == 'P')
            {
                novoJogador.score+=20;
            }
            else if(mapa[linhaJogador][colunaJogador + 1] == '.')
            {
                novoJogador.score+=10;
            }
            //testa se a techa da direita foi apertada e verifica se é possivél ir para a direita
            mapa[linhaJogador][colunaJogador] = ' ';
            if(mapa[linhaJogador][colunaJogador+1]=='.'||mapa[linhaJogador][colunaJogador+1]=='P')
            {
                //verifica se o pacman passou por uma pastilha, caso sim aturaliza o numero de pastilhas
                numPastilhas--;
            }
            mapa[linhaJogador][colunaJogador + 1] = 'J';
            direcaoPacman = 1;//variável para guardar a direção em que o pacman está indo
            // se for possíver ir para frente adiciona um espaço vazio na posição antiga e desenha um j na posição seguinte
        }
        //Checa se é possivel andar para a esquerda
        else if (arquivoNull==false&&(IsKeyDown(KEY_LEFT)||IsKeyDown(KEY_A)) && (mapa[linhaJogador][colunaJogador - 1] == ' ' || mapa[linhaJogador][colunaJogador - 1] == '.'||mapa[linhaJogador][colunaJogador - 1] == 'P'||mapa[linhaJogador][colunaJogador - 1] == 'F'||mapa[linhaJogador][colunaJogador - 1] == 'M'))
        {
            if(mapa[linhaJogador][colunaJogador - 1] == 'F')
            {
                novoJogador.score+=30;
            }
            else if(mapa[linhaJogador][colunaJogador - 1] == 'P')
            {
                novoJogador.score+=20;
            }
            else if(mapa[linhaJogador][colunaJogador - 1] == '.')
            {
                novoJogador.score+=10;
            }
            direcaoPacman = 2;
            mapa[linhaJogador][colunaJogador] = ' ';
            if(mapa[linhaJogador][colunaJogador-1]=='.'||mapa[linhaJogador][colunaJogador-1]=='P')
            {
                numPastilhas--;
            }
            mapa[linhaJogador][colunaJogador - 1] = 'J';
            //mesma lógica que antes só que pra esquerda
        }
        //Checa se é possivel andar para baixo
        else if (arquivoNull==false&&(IsKeyDown(KEY_DOWN)||IsKeyDown(KEY_S)) && (mapa[linhaJogador + 1][colunaJogador] == ' ' || mapa[linhaJogador + 1][colunaJogador] == '.'||mapa[linhaJogador + 1][colunaJogador] == 'P'||mapa[linhaJogador+1][colunaJogador] == 'F'||mapa[linhaJogador+1][colunaJogador] == 'M'))
        {
            if(mapa[linhaJogador + 1][colunaJogador] == 'F')
            {
                novoJogador.score+=30;
            }
            else if(mapa[linhaJogador + 1][colunaJogador] == 'P')
            {
                novoJogador.score+=20;
            }
            else if(mapa[linhaJogador + 1][colunaJogador] == '.')
            {
                novoJogador.score+=10;
            }
            //mesma lógica que antes só que para baixo
            direcaoPacman = 3;
            mapa[linhaJogador][colunaJogador] = ' ';
            if(mapa[linhaJogador+1][colunaJogador]=='.'||mapa[linhaJogador+1][colunaJogador]=='P')
            {
                numPastilhas--;
            }
            mapa[linhaJogador + 1][colunaJogador] = 'J';
        }
        //Checa se é possivel andar para cima
        else if (arquivoNull==false&&(IsKeyDown(KEY_UP)||IsKeyDown(KEY_W)) && (mapa[linhaJogador - 1][colunaJogador] == ' ' || mapa[linhaJogador - 1][colunaJogador] == '.'||mapa[linhaJogador - 1][colunaJogador] == 'P'||mapa[linhaJogador-1][colunaJogador] == 'F'||mapa[linhaJogador-1][colunaJogador] == 'M'))
        {
            if(mapa[linhaJogador - 1][colunaJogador] == 'F')
            {
                novoJogador.score+=30;
            }
            else if(mapa[linhaJogador - 1][colunaJogador] == 'P')
            {
                novoJogador.score+=20;
            }
            else if(mapa[linhaJogador - 1][colunaJogador] == '.')
            {
                novoJogador.score+=10;
            }
            //mesma lógica que antes só que para cima
            direcaoPacman = 4;
            mapa[linhaJogador][colunaJogador] = ' ';
            if(mapa[linhaJogador-1][colunaJogador]=='.'||mapa[linhaJogador-1][colunaJogador]=='P')
            {
                numPastilhas--;
            }
            mapa[linhaJogador - 1][colunaJogador] = 'J';
        }
        // reseta a variável de contagem de tempo do delay na movimentação do fantasma
        tempoDesdeUltimoMovimento = 0;
        //reseta a contagem de tempo do delay na movimentação do pacman
    }
    //faz o fantasma sair da posição inicial
    if(fantasmas[0].posiInicialXF==fantasmas[0].coluna&&fantasmas[0].posiInicialYF==fantasmas[0].linha)
    {
        sairDaPoscaoInicial(0);
    }
    if(fantasmas[1].posiInicialXF==fantasmas[1].coluna&&fantasmas[1].posiInicialYF==fantasmas[1].linha)
    {
        sairDaPoscaoInicial(1);
    }
    if(fantasmas[2].posiInicialXF==fantasmas[2].coluna&&fantasmas[2].posiInicialYF==fantasmas[2].linha)
    {
        sairDaPoscaoInicial(2);
    }
    if(fantasmas[3].posiInicialXF==fantasmas[3].coluna&&fantasmas[3].posiInicialYF==fantasmas[3].linha)
    {
        sairDaPoscaoInicial(3);
    }
    if(fantasmas[4].posiInicialXF==fantasmas[4].coluna&&fantasmas[4].posiInicialYF==fantasmas[4].linha)
    {
        sairDaPoscaoInicial(4);
    }
    //test se o pacman está próximo do fantasma vermelho
    if (linhaJogador>=fantasmas[0].linha&&linhaJogador<=fantasmas[0].linha+5&&colunaJogador<=fantasmas[0].coluna+5&&colunaJogador>=fantasmas[0].coluna)
    {
        //Começa a perseguir
        perseguirF1=true;
    }
    else if(linhaJogador<=fantasmas[0].linha&&linhaJogador>=fantasmas[0].linha-5&&colunaJogador>=fantasmas[0].coluna-5&&colunaJogador<=fantasmas[0].coluna)
    {
        //Começa a perseguir
        perseguirF1=true;
    }
    else
    {
        perseguirF1=false;
    }
    //testa se o pacman está perto do fantasma azul
    if (linhaJogador>=fantasmas[1].linha&&linhaJogador<=fantasmas[1].linha+5&&colunaJogador<=fantasmas[1].coluna+5&&colunaJogador>=fantasmas[1].coluna)
    {
        //Começa a perseguir
        perseguirF2=true;
    }
    else if(linhaJogador<=fantasmas[1].linha&&linhaJogador>=fantasmas[1].linha-5&&colunaJogador>=fantasmas[1].coluna-5&&colunaJogador<=fantasmas[1].coluna)
    {
        //Começa a perseguir
        perseguirF2=true;
    }
    else
    {
        perseguirF2=false;
    }
    //testa se o pacman está perto do fantasma amarelo
    if (linhaJogador>=fantasmas[2].linha&&linhaJogador<=fantasmas[2].linha+5&&colunaJogador<=fantasmas[2].coluna+5&&colunaJogador>=fantasmas[2].coluna)
    {
        //Começa a perseguir
        perseguirF3=true;
    }
    else if(linhaJogador<=fantasmas[2].linha&&linhaJogador>=fantasmas[2].linha-5&&colunaJogador>=fantasmas[2].coluna-5&&colunaJogador<=fantasmas[2].coluna)
    {
        //Começa a perseguir
        perseguirF3=true;
    }
    else
    {
        perseguirF3=false;
    }
    //testa se o pacman está perto do fantasma rosa
    if (linhaJogador>=fantasmas[3].linha&&linhaJogador<=fantasmas[3].linha+5&&colunaJogador<=fantasmas[3].coluna+5&&colunaJogador>=fantasmas[3].coluna)
    {
        //Começa a perseguir
        perseguirF4=true;
    }
    else if(linhaJogador<=fantasmas[3].linha&&linhaJogador>=fantasmas[3].linha-5&&colunaJogador>=fantasmas[3].coluna-5&&colunaJogador<=fantasmas[3].coluna)
    {
        //Começa a perseguir
        perseguirF4=true;
    }
    else
    {
        perseguirF4=false;
    }
    //testa se o pacman está perto do fantasma 4
    if (linhaJogador>=fantasmas[4].linha&&linhaJogador<=fantasmas[4].linha+5&&colunaJogador<=fantasmas[4].coluna+5&&colunaJogador>=fantasmas[4].coluna)
    {
        //Começa a perseguir
        perseguirF5=true;
    }
    else if(linhaJogador<=fantasmas[4].linha&&linhaJogador>=fantasmas[4].linha-5&&colunaJogador>=fantasmas[4].coluna-5&&colunaJogador<=fantasmas[4].coluna)
    {
        //Começa a perseguir
        perseguirF5=true;
    }
    else
    {
        perseguirF5=false;
    }
    //Se o fantasma 1 não estiver perseguindo
    if(perseguirF1==false)
    {
        if(TempoDecorrido>=intervaloDeTempo)
        {
            fantasmaVermelhoBuscar(0.03);//caso o pacman não esteja perto do fantasma ele começa a andar aletóriamente a cada 0.05 segundos se 2 minutos se passarem desde que o mapa foi iniciado
            TempoDecorrido=intervaloDeTempo;
        }
        else
        {
            fantasmaVermelhoBuscar(0.06);//ele anda aleatoriamente a cada 0.06 segundos
        }
    }
    else
    {
        fantasmaVermelhoPerseguir(0.10);//caso esteja ele persegue o pacman
    }
    //Se o fantasma 2 não estiver perseguindo
    if(perseguirF2==false)
    {
        if(TempoDecorrido>=intervaloDeTempo)
        {
            fantasmaAzulBuscar(0.03);//caso o pacman não esteja perto do fantasma ele começa a andar aletóriamente a cada 0.05 segundos se 2 minutos se passarem desde que o mapa foi iniciado
            TempoDecorrido=intervaloDeTempo;
        }
        else
        {
            fantasmaAzulBuscar(0.06);//ele anda aleatoriamente a cada 0.11 segundos
        }
    }
    else
    {
        fantasmaAzulPerseguir(0.10);//caso esteja ele persegue o pacman
    }
    //Se o fantasma 3 não estiver perseguindo
    if(perseguirF3==false)
    {
        if(TempoDecorrido>=intervaloDeTempo)
        {
            fantasmaAmareloBuscar(0.03);//caso o pacman não esteja perto do fantasma ele começa a andar aletóriamente a cada 0.05 segundos se 2 minutos se passarem desde que o mapa foi iniciado
            TempoDecorrido=intervaloDeTempo;
        }
        else
        {
            fantasmaAmareloBuscar(0.06);//ele anda aleatoriamente a cada 0.11 segundos
        }
    }
    else
    {
        fantasmaAmareloPerseguir(0.10);//caso esteja ele persegue o pacman
    }
    //Se o fantasma 4 não estiver perseguindo
    if(perseguirF4==false)
    {
        if(TempoDecorrido>=intervaloDeTempo)
        {
            fantasmaRosaBuscar(0.03);//caso o pacman não esteja perto do fantasma ele começa a andar aletóriamente a cada 0.05 segundos se 2 minutos se passarem desde que o mapa foi iniciado
            TempoDecorrido=intervaloDeTempo;
        }
        else
        {
            fantasmaRosaBuscar(0.06);//ele anda aleatoriamente a cada 0.11 segundos
        }
    }
    else
    {
        fantasmaRosaPerseguir(0.10);//caso esteja ele persegue o pacman
    }
    //Se o fantasma 5 não estiver perseguindo
    if(perseguirF5==false)
    {
        if(TempoDecorrido>=intervaloDeTempo)
        {
            fantasmaLaranjaBuscar(0.03);//caso o pacman não esteja perto do fantasma ele começa a andar aletóriamente a cada 0.05 segundos se 2 minutos se passarem desde que o mapa foi iniciado
            TempoDecorrido=intervaloDeTempo;
        }
        else
        {
            fantasmaLaranjaBuscar(0.06);//ele anda aleatoriamente a cada 0.11 segundos
        }
    }
    else
    {
        fantasmaLaranjaPerseguir(0.10);//caso esteja ele persegue o pacman
    }
}
//Função que desenha todas as informações do jogo menos os fantasmas
void desenharJogo()
{
    char Titulo[20];
    char texto[20];
    char tempo[20];
    aux2-=GetFrameTime();
    if(aux2<0.02)
    {
        aux2=0;
    }
    scoreMostrado=novoJogador.score;
    sprintf(texto,"Score: %d",scoreMostrado);
    sprintf(Titulo,"Mapa: %d",NumMapaTitulo);
    sprintf(tempo,":%f",aux2);
    BeginDrawing();
    ClearBackground(BLACK);
    if(vidas==3&&arquivoNull==false)
    {
        DrawText("Aperte Tab para pausar", 530, 22, 21, WHITE);
        DrawText(Titulo, 330, 5, 21, WHITE);//título do mapa
        DrawText(tempo, 675, 5, 21, WHITE);//título do mapa
        DrawText(texto, 170, 22, 21, WHITE);
        DrawText("Tempo até", 530, 1,12, WHITE);
        DrawText("a dificauldade aumentar", 530, 10,12, WHITE);
        DrawText("Vidas:", 0, 22, 21, WHITE);
        DrawCircleSector((Vector2)
        {
            3.7 * tamanho, 1.5 * tamanho
        }, tamanho / 2, 20, 340, 50, YELLOW);//desenha um pacman no topo da tala para representa ar vidas
        DrawCircleSector((Vector2)
        {
            4.9 * tamanho, 1.5 * tamanho
        }, tamanho / 2, 20, 340, 50, YELLOW);
        DrawCircleSector((Vector2)
        {
            6.1 * tamanho, 1.5 * tamanho
        }, tamanho / 2, 20, 340, 50, YELLOW);
    }
    if(vidas==2&&arquivoNull==false)
    {
        DrawText("Aperte Tab para pausar", 530, 22, 21, WHITE);
        DrawText(Titulo, 330, 5, 21, WHITE);//título do mapa
        DrawText(tempo, 675, 5, 21, WHITE);//título do mapa
        DrawText(texto, 170, 22, 21, WHITE);
        DrawText("Tempo até", 530, 1,12, WHITE);
        DrawText("a dificauldade aumentar", 530, 10,12, WHITE);
        DrawText("Vidas:", 0, 22, 21, WHITE);
        DrawCircleSector((Vector2)
        {
            3.7 * tamanho, 1.5 * tamanho
        }, tamanho / 2, 20, 340, 50, YELLOW);//desenha um pacman no topo da tala para representa ar vidas
        DrawCircleSector((Vector2)
        {
            4.9 * tamanho, 1.5 * tamanho
        }, tamanho / 2, 20, 340, 50, YELLOW);
    }
    if(vidas==1&&arquivoNull==false)
    {
        DrawText("Aperte Tab para pausar", 530, 22, 21, WHITE);
        DrawText(Titulo, 330, 5, 21, WHITE);//título do mapa
        DrawText(tempo, 675, 5, 21, WHITE);//título do mapa
        DrawText(texto, 170, 22, 21, WHITE);
        DrawText("Tempo até", 530, 1,12, WHITE);
        DrawText("a dificauldade aumentar", 530, 10,12, WHITE);
        DrawText("Vidas:", 0, 22, 21, WHITE);
        DrawCircleSector((Vector2)
        {
            3.7 * tamanho, 1.5 * tamanho
        }, tamanho / 2, 20, 340, 50, YELLOW);//desenha um pacman no topo da tala para representa ar vidas
    }
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (mapa[i][j] == 'W')
            {
                DrawRectangle(j * tamanho, i * tamanho, tamanho, tamanho, DARKBLUE);
            }
            //desenha um retangulo azul escuro onde for w acada 20 pixels
            else if (mapa[i][j] == '.')
            {
                DrawCircle((j + 0.5) * tamanho, (i + 0.5) * tamanho, tamanho / 8, BEIGE);
            }
            //desenha as pastilhas
            else if(mapa[i][j]=='P')
            {
                DrawCircle((j + 0.5) * tamanho, (i + 0.5) * tamanho, tamanho / 4, BEIGE);
            }
            else if(mapa[i][j]=='F')
            {
                DrawLine((j + 0.5) * tamanho,(i + 0.73) * tamanho, ((j + 0.5) * tamanho)+8, ((i + 0.73) * tamanho)-13, GREEN);
                DrawLine((j + 0.5) * 19.8,(i + 0.73) * 19.8, ((j + 0.5) * tamanho)+8, ((i + 0.73) * tamanho)-13, GREEN);
                DrawCircle((j + 0.5) * tamanho, (i + 0.73) * tamanho, tamanho/4, RED);
                DrawCircle((j + 0.5) * 19.8, (i + 0.73) * 19.9, tamanho/4, RED);
            }
            else if (mapa[i][j] == 'J')
            {
                //desenha o pacman
                switch (direcaoPacman)
                {
                case 1:
                    DrawCircleSector((Vector2)
                    {
                        (j + 0.5) * tamanho, (i + 0.5) * tamanho
                    }, tamanho / 2, 20, 340, 50, YELLOW);//desenha o pacman virado pra direta
                    break;
                case 2:
                    DrawCircleSector((Vector2)
                    {
                        (j + 0.5) * tamanho, (i + 0.5) * tamanho
                    }, tamanho / 2, 160, -160, 50, YELLOW);
//desenha o pacman virado pra esquerda
                    break;
                case 3:
                    DrawCircleSector((Vector2)
                    {
                        (j + 0.5) * tamanho, (i + 0.5) * tamanho
                    }, tamanho / 2, 70, -250, 50, YELLOW);
//desenha o pacman virado pra cima
                    break;
                case 4:
                    DrawCircleSector((Vector2)
                    {
                        (j + 0.5) * tamanho, (i + 0.5) * tamanho
                    }, tamanho / 2, 250, -70, 50, YELLOW);
//desenha o pacman pra baixo
                    break;
                }
            }
        }
    }
    // Desenhar os fantasmas
    for (int i = 0; i < numFantasmas; i++)
    {
        desenharfantasma(i);
        //chama a função que desenha os fantasmas e desenha na tela
    }
    EndDrawing();
}
//Função que desenha os fantasmas
void desenharfantasma(int i)
{
    int x = fantasmas[i].coluna * tamanho;
    int y = fantasmas[i].linha * tamanho;

    float posX1 = x + tamanho / 4.0;
    float posX2 = x + 3 * tamanho / 4.0;
    float posY = y + tamanho;
    if(i==0)
    {
        // Desenhar a cabeça arredondada do fantasma
        DrawCircle(x + tamanho / 2,4+ y + tamanho / 3, tamanho / 2, RED);
        // Desenhar o corpo quadrado do fantasma
        DrawRectangle(x, 1+y + tamanho / 3, tamanho, 2 * tamanho / 3, RED);
        // Desenhar olhos do fantasma
        DrawCircle(x + tamanho / 3, 4+y + tamanho / 3, tamanho / 6, WHITE);
        DrawCircle(x + 2 * tamanho / 3,4+ y + tamanho / 3, tamanho / 6, WHITE);
        // Desenhar pupilas do fantasma
        DrawCircle(2+x + tamanho / 3, 4+y + tamanho / 3, tamanho / 12, DARKBLUE);
        DrawCircle(2+x + 2 * tamanho / 3, 4+y + tamanho / 3, tamanho / 12, DARKBLUE);
        // Desenhar ondulações na base do fantasma usando dois setores circulares
        DrawCircleSector((Vector2)
        {
            posX1, posY-0.3
        }, 3.7, 0, -180, 20, BLACK);
        DrawCircleSector((Vector2)
        {
            posX2, posY-0.3
        }, 3.7, 0, -180, 20, BLACK);
    }
    if(i==1)
    {
        // Desenhar a cabeça arredondada do fantasma
        DrawCircle(x + tamanho / 2,4+ y + tamanho / 3, tamanho / 2, SKYBLUE);
        // Desenhar o corpo quadrado do fantasma
        DrawRectangle(x, 1+y + tamanho / 3, tamanho, 2 * tamanho / 3, SKYBLUE);
        // Desenhar olhos do fantasma
        DrawCircle(x + tamanho / 3, 4+y + tamanho / 3, tamanho / 6, WHITE);
        DrawCircle(x + 2 * tamanho / 3,4+ y + tamanho / 3, tamanho / 6, WHITE);
        // Desenhar pupilas do fantasma
        DrawCircle(2+x + tamanho / 3, 4+y + tamanho / 3, tamanho / 12, DARKBLUE);
        DrawCircle(2+x + 2 * tamanho / 3, 4+y + tamanho / 3, tamanho / 12, DARKBLUE);
        // Desenhar ondulações na base do fantasma usando dois setores circulares
        DrawCircleSector((Vector2)
        {
            posX1, posY-0.3
        }, 3.7, 0, -180, 20, BLACK);
        DrawCircleSector((Vector2)
        {
            posX2, posY-0.3
        }, 3.7, 0, -180, 20, BLACK);
    }
    if(i==2)
    {
        // Desenhar a cabeça arredondada do fantasma
        DrawCircle(x + tamanho / 2,4+ y + tamanho / 3, tamanho / 2, YELLOW);
        // Desenhar o corpo quadrado do fantasma
        DrawRectangle(x, 1+y + tamanho / 3, tamanho, 2 * tamanho / 3, YELLOW);
        // Desenhar olhos do fantasma
        DrawCircle(x + tamanho / 3, 4+y + tamanho / 3, tamanho / 6, WHITE);
        DrawCircle(x + 2 * tamanho / 3,4+ y + tamanho / 3, tamanho / 6, WHITE);
        // Desenhar pupilas do fantasma
        DrawCircle(2+x + tamanho / 3, 4+y + tamanho / 3, tamanho / 12, DARKBLUE);
        DrawCircle(2+x + 2 * tamanho / 3, 4+y + tamanho / 3, tamanho / 12, DARKBLUE);
        // Desenhar ondulações na base do fantasma usando dois setores circulares
        DrawCircleSector((Vector2)
        {
            posX1, posY-0.3
        }, 3.7, 0, -180, 20, BLACK);
        DrawCircleSector((Vector2)
        {
            posX2, posY-0.3
        }, 3.7, 0, -180, 20, BLACK);
    }
    if(i==3)
    {
        // Desenhar a cabeça arredondada do fantasma
        DrawCircle(x + tamanho / 2,4+ y + tamanho / 3, tamanho / 2, PINK);
        // Desenhar o corpo quadrado do fantasma
        DrawRectangle(x, 1+y + tamanho / 3, tamanho, 2 * tamanho / 3, PINK);
        // Desenhar olhos do fantasma
        DrawCircle(x + tamanho / 3, 4+y + tamanho / 3, tamanho / 6, WHITE);
        DrawCircle(x + 2 * tamanho / 3,4+ y + tamanho / 3, tamanho / 6, WHITE);
        // Desenhar pupilas do fantasma
        DrawCircle(2+x + tamanho / 3, 4+y + tamanho / 3, tamanho / 12, DARKBLUE);
        DrawCircle(2+x + 2 * tamanho / 3, 4+y + tamanho / 3, tamanho / 12, DARKBLUE);
        // Desenhar ondulações na base do fantasma usando dois setores circulares
        DrawCircleSector((Vector2)
        {
            posX1, posY-0.3
        }, 3.7, 0, -180, 20, BLACK);
        DrawCircleSector((Vector2)
        {
            posX2, posY-0.3
        }, 3.7, 0, -180, 20, BLACK);
    }
    if(i==4)
    {
        // Desenhar a cabeça arredondada do fantasma
        DrawCircle(x + tamanho / 2,4+ y + tamanho / 3, tamanho / 2, ORANGE);
        // Desenhar o corpo quadrado do fantasma
        DrawRectangle(x, 1+y + tamanho / 3, tamanho, 2 * tamanho / 3, ORANGE);
        // Desenhar olhos do fantasma
        DrawCircle(x + tamanho / 3, 4+y + tamanho / 3, tamanho / 6, WHITE);
        DrawCircle(x + 2 * tamanho / 3,4+ y + tamanho / 3, tamanho / 6, WHITE);
        // Desenhar pupilas do fantasma
        DrawCircle(2+x + tamanho / 3, 4+y + tamanho / 3, tamanho / 12, DARKBLUE);
        DrawCircle(2+x + 2 * tamanho / 3, 4+y + tamanho / 3, tamanho / 12, DARKBLUE);
        // Desenhar ondulações na base do fantasma usando dois setores circulares
        DrawCircleSector((Vector2)
        {
            posX1, posY-0.3
        }, 3.7, 0, -180, 20, BLACK);
        DrawCircleSector((Vector2)
        {
            posX2, posY-0.3
        }, 3.7, 0, -180, 20, BLACK);
    }
}
//Função que avalia se um save pode ser jogado ou não
//Se não puder retorna -1
int saveehvalido (int posicaocarregarjogo)
{
    //Resebe a opção que o jogador escolheu
    switch (posicaocarregarjogo)
    {
    case 2:
        //Abre o arquivo na forma de leitura
        FILE *infosave1 = fopen("saves/save01.bin", "rb");
        //Se o arquivo não existir, imprime erro e retona 0
        if (infosave1 == NULL)
        {
            perror("Erro ao abrir o arquivo");
            return 0;
        }
        INFO_SAVE save1;
        //Lê e grava a quantidade de estruturas do tipo INFO_SAVE na variável leitura1
        size_t leitura1 = fread(&save1, sizeof(INFO_SAVE), 1, infosave1);
        //Se não houver exatamente 1 estrutura do tipo INFO_SAVE
        if (leitura1 != 1)
        {
            perror("Erro ao ler do arquivo");
            fclose(infosave1);
            return 0;
        }
        //Fecha o arquivo
        fclose(infosave1);
        //Retorna o número de vidas do save(se for 0 o save não é jogavel)
        return save1.vidas;
    case 1:
        //Abre o arquivo na forma de leitura
        FILE *infosave2 = fopen("saves/save02.bin", "rb");
        //Se o arquivo não existir, imprime erro e retona 0
        if (infosave2 == NULL)
        {
            perror("Erro ao abrir o arquivo");
            return 0;
        }
        INFO_SAVE save2;
        //Lê e grava a quantidade de estruturas do tipo INFO_SAVE na variável leitura2
        size_t leitura2 = fread(&save2, sizeof(INFO_SAVE), 1, infosave2);
        //Se não houver exatamente 1 estrutura do tipo INFO_SAVE
        if (leitura2 != 1)
        {
            perror("Erro ao ler do arquivo");
            fclose(infosave2);
            return 0;
        }
        //Fecha o arquivo
        fclose(infosave2);
        //Retorna o número de vidas do save(se for 0 o save não é jogavel)
        return save2.vidas;
    case 0:
        //Abre o arquivo na forma de leitura
        FILE *infosave3 = fopen("saves/save03.bin", "rb");
        //Se o arquivo não existir, imprime erro e retona 0
        if (infosave3 == NULL)
        {
            perror("Erro ao abrir o arquivo");
            return 0;
        }
        INFO_SAVE save3;
        //Lê e grava a quantidade de estruturas do tipo INFO_SAVE na variável leitura3
        size_t leitura3 = fread(&save3, sizeof(INFO_SAVE), 1, infosave3);
        //Se não houver exatamente 1 estrutura do tipo INFO_SAVE
        if (leitura3 != 1)
        {
            perror("Erro ao ler do arquivo");
            fclose(infosave3);
            return 0;
        }
        //Fecha o arquivo
        fclose(infosave3);
        //Retorna o número de vidas do save(se for 0 o save não é jogavel)
        return save3.vidas;
    }
}
//Função que mostra o menu dos jogos salvos
void carregarjogo(int posicaocarregarjogo)
{
    //Abre o arquivo na forma de leitura
    FILE *infosave1 = fopen("saves/save01.bin", "rb");
    //Se o arquivo não existir, imprime erro e retona 0
    if (infosave1 == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }
    INFO_SAVE save1;
    //Lê e grava a quantidade de estruturas do tipo INFO_SAVE na variável leitura1
    size_t leitura1 = fread(&save1, sizeof(INFO_SAVE), 1, infosave1);
    //Se não houver exatamente 1 estrutura do tipo INFO_SAVE
    if (leitura1 != 1)
    {
        perror("Erro ao ler do arquivo");
        fclose(infosave1);
        return;
    }
    //Fecha o arquivo
    fclose(infosave1);

    //Abre o arquivo na forma de leitura
    FILE *infosave2 = fopen("saves/save02.bin", "rb");
    //Se o arquivo não existir, imprime erro e retona 0
    if (infosave1 == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }
    INFO_SAVE save2;
    //Lê e grava a quantidade de estruturas do tipo INFO_SAVE na variável leitura1
    size_t leitura2 = fread(&save2, sizeof(INFO_SAVE), 1, infosave2);
    //Se não houver exatamente 1 estrutura do tipo INFO_SAVE
    if (leitura2 != 1)
    {
        perror("Erro ao ler do arquio");
        fclose(infosave2);
        return;
    }
    //Fecha o arquivo
    fclose(infosave2);

    //Abre o arquivo na forma de leitura
    FILE *infosave3 = fopen("saves/save03.bin", "rb");
    //Se o arquivo não existir, imprime erro e retona 0
    if (infosave3 == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }
    INFO_SAVE save3;
    //Lê e grava a quantidade de estruturas do tipo INFO_SAVE na variável leitura3
    size_t leitura3 = fread(&save3, sizeof(INFO_SAVE), 1, infosave3);
    //Se não houver exatamente 1 estrutura do tipo INFO_SAVE
    if (leitura3 != 1)
    {
        perror("Erro ao ler do arquivo");
        fclose(infosave3);
        return;
    }
    //Fecha o arquivo
    fclose(infosave3);

    //Desenha as opções
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Aperte SPACE para sair", 10, 600, 35, WHITE);
    DrawText("Aperte ENTER para escolher", 10, 560, 35, WHITE);

    //String que pega os pontos referentes ao save1
    char pontossave1[6];
    //String que pega as vidas referentes ao saave1
    char vidassave1[2];
    //Transforma os pontos(inteiros) em string
    sprintf(pontossave1, "%d", save1.pontos);
    //Transforma as vidas(inteiros) em string
    sprintf(vidassave1, "%d", save1.vidas);
    //Desenha o slot do save1
    DrawRectangle(120, 180, 550, 100, BLUE);
    DrawRectangle(130, 190, 530, 80, BLACK);
    DrawText("Save 1", 135, 190, 40, WHITE);

    //Se houver um jogo salvo naquele slot
    if(save1.vidas != 0)
    {
        //Desenha os pontos
        DrawText("Pontos:", 135, 235, 40, WHITE);
        DrawText(pontossave1, 300, 235, 40, WHITE);
        //Desenha as vidas
        DrawText("Vidas:", 450, 235, 40, WHITE);
        DrawText(vidassave1, 575, 235, 40, WHITE);
    }
    else
    {
        //Diz que não há save
        DrawText("Nada salvo", 135, 235, 40, WHITE);
    }

    //String que pega os pontos referentes ao save2
    char pontossave2[6];
    //String que pega as vidas referentes ao save2
    char vidassave2[2];
    //Transforma os pontos(inteiros) em string
    sprintf(pontossave2, "%d", save2.pontos);
    //Transforma as vidas(inteiros) em string
    sprintf(vidassave2, "%d", save2.vidas);
    //Desenha o slot do save2
    DrawRectangle(120, 300, 550, 100, BLUE);
    DrawRectangle(130, 310, 530, 80, BLACK);
    DrawText("Save 2", 135, 310, 40, WHITE);

    //Se houver um jogo salvo naquele slot
    if (save2.vidas != 0)
    {
        //Desenha os pontos
        DrawText("Pontos:", 135, 355, 40, WHITE);
        DrawText(pontossave2, 300, 355, 40, WHITE);
        //Desenha as vidas
        DrawText("Vidas:", 450, 355, 40, WHITE);
        DrawText(vidassave2, 575, 355, 40, WHITE);
    }
    else
    {
        //Diz que não há save
        DrawText("Nada salvo", 135, 355, 40, WHITE);
    }

    //String que pega os pontos referentes ao save3
    char pontossave3[6];
    //String que pega as vidas referentes ao save3
    char vidassave3[2];
    //Transforma os pontos(inteiros) em string
    sprintf(pontossave3, "%d", save3.pontos);
    //Transforma as vidas(inteiros) em string
    sprintf(vidassave3, "%d", save3.vidas);
    //Desenha o slot do save3
    DrawRectangle(120, 420, 550, 100, BLUE);
    DrawRectangle(130, 430, 530, 80, BLACK);
    DrawText("Save 3", 135, 430, 40, WHITE);

    //Se houver um jogo salvo naquele slot
    if (save3.vidas != 0)
    {
        //Desenha os pontos
        DrawText("Pontos:", 135, 475, 40, WHITE);
        DrawText(pontossave3, 300, 475, 40, WHITE);
        //Desenha as vidas
        DrawText("Vidas:", 450, 475, 40, WHITE);
        DrawText(vidassave3, 575, 475, 40, WHITE);
    }
    else
    {
        //Diz que não há save
        DrawText("Nada salvo", 135, 475, 40, WHITE);
    }

    //Desenha um retângulo para auxiliar na escolha
    DrawRectangle(70, 460 - (posicaocarregarjogo * 120), 40,20, WHITE);

    EndDrawing();
}
//Função que move o fantasma vermelho para perseguir o PACMAN
void fantasmaVermelhoPerseguir(float intervaloFantasmaVe)
{
    //movimentação do fantasma vermelho
    if(fantasmas[0].coluna<colunaJogador&&mapa[fantasmas[0].linha][fantasmas[0].coluna+1]!='W')
    {
        //persegue o pacman para frente
        if(TempoFantasmaVe>=intervaloFantasmaVe)
        {
            // testa para o fantasma se locomover em um intevalo te tempo específico
            fantasmas[0].coluna++;//alinha a coluna do fantasma e do pacman
            TempoFantasmaVe=0;//reseta o contador de tempo
        }
    }
    if(fantasmas[0].coluna==colunaJogador&&fantasmas[0].linha<linhaJogador&&mapa[fantasmas[0].linha+1][fantasmas[0].coluna]!='W')
    {
        //persegue o pacman para baixo
        if(TempoFantasmaVe>=intervaloFantasmaVe)
        {
            fantasmas[0].linha++; //caso a coluna do fantasma e do pacman estejam alinhadas a linhas serão alinhadas
            TempoFantasmaVe=0;
        }
    }
    if(fantasmas[0].coluna>colunaJogador&&mapa[fantasmas[0].linha][fantasmas[0].coluna-1]!='W')
    {
        //persegue o pacman pra esquerda
        if(TempoFantasmaVe>=intervaloFantasmaVe)
        {
            fantasmas[0].coluna--;//alinha a coluna só que no sentido oposto
            TempoFantasmaVe=0;
        }
    }
    if(fantasmas[0].coluna==colunaJogador&&fantasmas[0].linha>linhaJogador&&mapa[fantasmas[0].linha-1][fantasmas[0].coluna]!='W')
    {
        //persegue o pacman para cima
        if(TempoFantasmaVe>=intervaloFantasmaVe)
        {
            fantasmas[0].linha--; //alinha a linha só que no sentido oposto
            TempoFantasmaVe=0;
        }
    }
}
//Função que move o fantasma vermelho para fazer uma movimentação aleatoria
void fantasmaVermelhoBuscar(float intervaloFantasmaVe)
{
    //movimentação do fantasma vermelho
    if((numeroF1==0||numeroF1==1)&&(mapa[fantasmas[0].linha][fantasmas[0].coluna+1]!='W'))
    {
        //le numero gerado aleatoriamente e se locomove caso não haja parede
        andarF1=true;//registra que não tem parede que impeça o movimento do fantasma
        if(TempoFantasmaVe>=intervaloFantasmaVe)
        {
            //aguarda um determinado tempo decorrido
            fantasmas[0].coluna++;//desloca o fantasma
            TempoFantasmaVe=0;
        }
    }
    else if(mapa[fantasmas[0].linha][fantasmas[0].coluna+1]=='W')
    {
        andarF1=false;//verifica se o fantasma parou de andar por conta de uma parede
    }
    if((numeroF1==2||numeroF1==3)&&(mapa[fantasmas[0].linha+1][fantasmas[0].coluna]!='W'))
    {
        //mesma lógica que o primerio if
        if(TempoFantasmaVe>=intervaloFantasmaVe)
        {
            fantasmas[0].linha++; //desloca o fantasma para baixo
            TempoFantasmaVe=0;
        }
        andarF1=true;
    }
    else if(mapa[fantasmas[0].linha+1][fantasmas[0].coluna]=='W')
    {
        andarF1=false;
    }
    if((numeroF1==4||numeroF1==5)&&(mapa[fantasmas[0].linha][fantasmas[0].coluna-1]!='W'))
    {
        //mesma lógica de antes
        if(TempoFantasmaVe>=intervaloFantasmaVe)
        {
            fantasmas[0].coluna--;//desloca o fantasma para a esqueda
            TempoFantasmaVe=0;
        }
        andarF1=true;
    }
    else if(mapa[fantasmas[0].linha][fantasmas[0].coluna-1]=='W')
    {
        andarF1=false;
    }
    if((numeroF1==6||numeroF1==7)&&(mapa[fantasmas[0].linha-1][fantasmas[0].coluna]!='W'))
    {
        //mesma lógica de antes
        if(TempoFantasmaVe>=intervaloFantasmaVe)
        {
            fantasmas[0].linha--; //desloca o fantasma para cima
            TempoFantasmaVe=0;
        }
        andarF1=true;
    }
    else if(mapa[fantasmas[0].linha-1][fantasmas[0].coluna]=='W')
    {
        andarF1=false;
    }
    //fim do trecho
    if(andarF1==false)
    {
        // se o fantasma esbarra em uma parede gera é gerado um novo número aleatório para mudar a direção do fantasma
        srand(time(NULL));
        movimentoaleatorioF1();
        numeroF1=movimentoaleatorioF1();
    }
}
//Função que move o fantasma azul para fazer uma movimentação aleatoria
void fantasmaAzulBuscar(float intervaloFantasmaA)
{
    //movimentação do fantasma vermelho
    if((numeroF2==6||numeroF2==7)&&(mapa[fantasmas[1].linha][fantasmas[1].coluna+1]!='W'))
    {
        //le numero gerado aleatoriamente e se locomove caso não haja parede
        andarF2=true;//registra que não tem parede que impeça o movimento do fantasma
        if(TempoFantasmaA>=intervaloFantasmaA)
        {
            //aguarda um determinado tempo decorrido
            fantasmas[1].coluna++;//desloca o fantasma
            TempoFantasmaA=0;
        }
    }
    else if(mapa[fantasmas[1].linha][fantasmas[1].coluna+1]=='W')
    {
        andarF2=false;//verifica se o fantasma parou de andar por conta de uma parede
    }
    if((numeroF2==4||numeroF2==5)&&(mapa[fantasmas[1].linha+1][fantasmas[1].coluna]!='W'))
    {
        //mesma lógica que o primerio if
        if(TempoFantasmaA>=intervaloFantasmaA)
        {
            fantasmas[1].linha++; //desloca o fantasma para baixo
            TempoFantasmaA=0;
        }
        andarF2=true;
    }
    else if(mapa[fantasmas[1].linha+1][fantasmas[1].coluna]=='W')
    {
        andarF2=false;
    }
    if((numeroF2==2||numeroF2==3)&&(mapa[fantasmas[1].linha][fantasmas[1].coluna-1]!='W'))
    {
        //mesma lógica de antes
        if(TempoFantasmaA>=intervaloFantasmaA)
        {
            fantasmas[1].coluna--;//desloca o fantasma para a esqueda
            TempoFantasmaA=0;
        }
        andarF2=true;
    }
    else if(mapa[fantasmas[1].linha][fantasmas[1].coluna-1]=='W')
    {
        andarF2=false;
    }
    if((numeroF2==0||numeroF2==1)&&(mapa[fantasmas[1].linha-1][fantasmas[1].coluna]!='W'))
    {
        //mesma lógica de antes
        if(TempoFantasmaA>=intervaloFantasmaA)
        {
            fantasmas[1].linha--; //desloca o fantasma para cima
            TempoFantasmaA=0;
        }
        andarF2=true;
    }
    else if(mapa[fantasmas[1].linha-1][fantasmas[1].coluna]=='W')
    {
        andarF2=false;
    }
    //fim do trecho
    if(andarF2==false)
    {
        // se o fantasma esbarra em uma parede gera é gerado um novo número aleatório para mudar a direção do fantasma
        srand(time(NULL));
        movimentoaleatorioF2();
        numeroF2=movimentoaleatorioF2();
    }
}
//Função que move o fantasma azul para perseguir o PACMAN
void fantasmaAzulPerseguir(float intervaloFantasmaA)
{
    //movimentação do fantasma azul
    if(fantasmas[1].coluna<colunaJogador&&mapa[fantasmas[1].linha][fantasmas[1].coluna+1]!='W')
    {
        //persegue o pacman para frente
        if(TempoFantasmaA>=intervaloFantasmaA)
        {
            // testa para o fantasma se locomover em um intevalo te tempo específico
            fantasmas[1].coluna++;//alinha a coluna do fantasma e do pacman
            TempoFantasmaA=0;//reseta o contador de tempo
        }
    }
    if(fantasmas[1].coluna==colunaJogador&&fantasmas[1].linha<linhaJogador&&mapa[fantasmas[1].linha+1][fantasmas[1].coluna]!='W')
    {
        //persegue o pacman para baixo
        if(TempoFantasmaA>=intervaloFantasmaA)
        {
            fantasmas[1].linha++; //caso a coluna do fantasma e do pacman estejam alinhadas a linhas serão alinhadas
            TempoFantasmaA=0;
        }
    }
    if(fantasmas[1].coluna>colunaJogador&&mapa[fantasmas[1].linha][fantasmas[1].coluna-1]!='W')
    {
        //persegue o pacman pra esquerda
        if(TempoFantasmaA>=intervaloFantasmaA)
        {
            fantasmas[1].coluna--;//alinha a coluna só que no sentido oposto
            TempoFantasmaA=0;
        }
    }
    if(fantasmas[1].coluna==colunaJogador&&fantasmas[1].linha>linhaJogador&&mapa[fantasmas[1].linha-1][fantasmas[1].coluna]!='W')
    {
        //persegue o pacman para cima
        if(TempoFantasmaA>=intervaloFantasmaA)
        {
            fantasmas[1].linha--; //alinha a linha só que no sentido oposto
            TempoFantasmaA=0;
        }
    }
}
//Função que move o fantasma amarelo para fazer uma movimentação aleatoria
void fantasmaAmareloBuscar(float intervaloFantasmaAma)
{
    //movimentação do fantasma vermelho
    if((numeroF3==4||numeroF3==5)&&(mapa[fantasmas[2].linha][fantasmas[2].coluna+1]!='W'))
    {
        //le numero gerado aleatoriamente e se locomove caso não haja parede
        andarF3=true;//registra que não tem parede que impeça o movimento do fantasma
        if(TempoFantasmaAma>=intervaloFantasmaAma)
        {
            //aguarda um determinado tempo decorrido
            fantasmas[2].coluna++;//desloca o fantasma
            TempoFantasmaAma=0;
        }
    }
    else if((mapa[fantasmas[2].linha][fantasmas[2].coluna+1]=='W'))
    {
        andarF3=false;//verifica se o fantasma parou de andar por conta de uma parede
    }
    if((numeroF3==6||numeroF3==7)&&(mapa[fantasmas[2].linha+1][fantasmas[2].coluna]!='W'))
    {
        //mesma lógica que o primerio if
        if(TempoFantasmaAma>=intervaloFantasmaAma)
        {
            fantasmas[2].linha++; //desloca o fantasma para baixo
            TempoFantasmaAma=0;
        }
        andarF3=true;
    }
    else if(mapa[fantasmas[2].linha+1][fantasmas[2].coluna]=='W')
    {
        andarF3=false;
    }
    if((numeroF3==0||numeroF3==1)&&(mapa[fantasmas[2].linha][fantasmas[2].coluna-1]!='W'))
    {
        //mesma lógica de antes
        if(TempoFantasmaAma>=intervaloFantasmaAma)
        {
            fantasmas[2].coluna--;//desloca o fantasma para a esqueda
            TempoFantasmaAma=0;
        }
        andarF3=true;
    }
    else if(mapa[fantasmas[2].linha][fantasmas[2].coluna-1]=='W')
    {
        andarF3=false;
    }
    if((numeroF3==3||numeroF3==2)&&(mapa[fantasmas[2].linha-1][fantasmas[2].coluna]!='W'))
    {
        //mesma lógica de antes
        if(TempoFantasmaAma>=intervaloFantasmaAma)
        {
            fantasmas[2].linha--; //desloca o fantasma para cima
            TempoFantasmaAma=0;
        }
        andarF3=true;
    }
    else if(mapa[fantasmas[2].linha-1][fantasmas[2].coluna]=='W')
    {
        andarF3=false;
    }
    //fim do trecho
    if(andarF3==false)
    {
        // se o fantasma esbarra em uma parede gera é gerado um novo número aleatório para mudar a direção do fantasma
        srand(time(NULL));
        movimentoaleatorioF3();
        numeroF3=movimentoaleatorioF3();
    }
}
//Função que move o fantasma amarelo para perseguir o PACMAN
void fantasmaAmareloPerseguir(float intervaloFantasmaAma)
{
//movimentação do fantasma amarelo
    if(fantasmas[2].coluna<colunaJogador&&mapa[fantasmas[2].linha][fantasmas[2].coluna+1]!='W')
    {
        //persegue o pacman para frente
        if(TempoFantasmaAma>=intervaloFantasmaAma)
        {
            // testa para o fantasma se locomover em um intevalo te tempo específico
            fantasmas[2].coluna++;//alinha a coluna do fantasma e do pacman
            TempoFantasmaAma=0;//reseta o contador de tempo
        }
    }
    if(fantasmas[2].coluna==colunaJogador&&fantasmas[2].linha<linhaJogador&&mapa[fantasmas[2].linha+1][fantasmas[2].coluna]!='W')
    {
        //persegue o pacman para baixo
        if(TempoFantasmaAma>=intervaloFantasmaAma)
        {
            fantasmas[2].linha++; //caso a coluna do fantasma e do pacman estejam alinhadas a linhas serão alinhadas
            TempoFantasmaAma=0;
        }
    }
    if(fantasmas[2].coluna>colunaJogador&&mapa[fantasmas[2].linha][fantasmas[2].coluna-1]!='W')
    {
        //persegue o pacman pra esquerda
        if(TempoFantasmaAma>=intervaloFantasmaAma)
        {
            fantasmas[2].coluna--;//alinha a coluna só que no sentido oposto
            TempoFantasmaAma=0;
        }
    }
    if(fantasmas[2].coluna==colunaJogador&&fantasmas[2].linha>linhaJogador&&mapa[fantasmas[2].linha-1][fantasmas[2].coluna]!='W')
    {
        //persegue o pacman para cima
        if(TempoFantasmaAma>=intervaloFantasmaAma)
        {
            fantasmas[2].linha--; //alinha a linha só que no sentido oposto
            TempoFantasmaAma=0;
        }
    }
}
//Função que move o fantasma rosa para fazer uma movimentação aleatoria
void fantasmaRosaBuscar(float intervaloFantasmaR)
{
    //movimentação do fantasma vermelho
    if((numeroF4==0||numeroF4==2)&&(mapa[fantasmas[3].linha][fantasmas[3].coluna+1]!='W'))
    {
        //le numero gerado aleatoriamente e se locomove caso não haja parede
        andarF4=true;//registra que não tem parede que impeça o movimento do fantasma
        if(TempoFantasmaR>=intervaloFantasmaR)
        {
            //aguarda um determinado tempo decorrido
            fantasmas[3].coluna++;//desloca o fantasma
            TempoFantasmaR=0;
        }
    }
    else if((mapa[fantasmas[3].linha][fantasmas[3].coluna+1]=='W'))
    {
        andarF4=false;//verifica se o fantasma parou de andar por conta de uma parede
    }
    if((numeroF4==4||numeroF4==6)&&(mapa[fantasmas[3].linha+1][fantasmas[3].coluna]!='W'))
    {
        //mesma lógica que o primerio if
        if(TempoFantasmaR>=intervaloFantasmaR)
        {
            fantasmas[3].linha++; //desloca o fantasma para baixo
            TempoFantasmaR=0;
        }
        andarF4=true;
    }
    else if(mapa[fantasmas[3].linha+1][fantasmas[3].coluna]=='W')
    {
        andarF4=false;
    }
    if((numeroF4==1||numeroF4==3)&&(mapa[fantasmas[3].linha][fantasmas[3].coluna-1]!='W'))
    {
        //mesma lógica de antes
        if(TempoFantasmaR>=intervaloFantasmaR)
        {
            fantasmas[3].coluna--;//desloca o fantasma para a esqueda
            TempoFantasmaR=0;
        }
        andarF4=true;
    }
    else if(mapa[fantasmas[3].linha][fantasmas[3].coluna-1]=='W')
    {
        andarF4=false;
    }
    if((numeroF4==5||numeroF4==7)&&(mapa[fantasmas[3].linha-1][fantasmas[3].coluna]!='W'))
    {
        //mesma lógica de antes
        if(TempoFantasmaR>=intervaloFantasmaR)
        {
            fantasmas[3].linha--; //desloca o fantasma para cima
            TempoFantasmaR=0;
        }
        andarF4=true;
    }
    else if(mapa[fantasmas[3].linha-1][fantasmas[3].coluna]=='W')
    {
        andarF4=false;
    }
    //fim do trecho
    if(andarF4==false)
    {
        // se o fantasma esbarra em uma parede gera é gerado um novo número aleatório para mudar a direção do fantasma
        srand(time(NULL));
        movimentoaleatorioF4();
        numeroF4=movimentoaleatorioF4();
    }
}
//Função que move o fantasma rosa para perseguir o PACMAN
void fantasmaRosaPerseguir(float intervaloFantasmaR)
{
//movimentação do fantasma amarelo
    if(fantasmas[3].coluna<colunaJogador&&mapa[fantasmas[3].linha][fantasmas[3].coluna+1]!='W')
    {
        //persegue o pacman para frente
        if(TempoFantasmaR>=intervaloFantasmaR)
        {
            // testa para o fantasma se locomover em um intevalo te tempo específico
            fantasmas[3].coluna++;//alinha a coluna do fantasma e do pacman
            TempoFantasmaR=0;//reseta o contador de tempo
        }
    }
    if(fantasmas[3].coluna==colunaJogador&&fantasmas[3].linha<linhaJogador&&mapa[fantasmas[3].linha+1][fantasmas[3].coluna]!='W')
    {
        //persegue o pacman para baixo
        if(TempoFantasmaR>=intervaloFantasmaR)
        {
            fantasmas[3].linha++; //caso a coluna do fantasma e do pacman estejam alinhadas a linhas serão alinhadas
            TempoFantasmaR=0;
        }
    }
    if(fantasmas[3].coluna>colunaJogador&&mapa[fantasmas[3].linha][fantasmas[3].coluna-1]!='W')
    {
        //persegue o pacman pra esquerda
        if(TempoFantasmaR>=intervaloFantasmaR)
        {
            fantasmas[3].coluna--;//alinha a coluna só que no sentido oposto
            TempoFantasmaR=0;
        }
    }
    if(fantasmas[3].coluna==colunaJogador&&fantasmas[3].linha>linhaJogador&&mapa[fantasmas[3].linha-1][fantasmas[3].coluna]!='W')
    {
        //persegue o pacman para cima
        if(TempoFantasmaR>=intervaloFantasmaR)
        {
            fantasmas[3].linha--; //alinha a linha só que no sentido oposto
            TempoFantasmaR=0;
        }
    }
}
//Função que move o fantasma laranja para perseguir o PACMAN
void fantasmaLaranjaPerseguir(float intervaloFantasmaL)
{
    //movimentação do fantasma vermelho
    if(fantasmas[4].coluna<colunaJogador&&mapa[fantasmas[4].linha][fantasmas[4].coluna+1]!='W')
    {
        //persegue o pacman para frente
        if(TempoFantasmaL>=intervaloFantasmaL)
        {
            // testa para o fantasma se locomover em um intevalo te tempo específico
            fantasmas[4].coluna++;//alinha a coluna do fantasma e do pacman
            if(mapa[fantasmas[4].linha][fantasmas[4].coluna+1]=='W')
            {
                perseguirF5=false;
            }
            TempoFantasmaL=0;//reseta o contador de tempo
        }
    }
    if(fantasmas[4].coluna==colunaJogador&&fantasmas[4].linha<linhaJogador&&mapa[fantasmas[4].linha+1][fantasmas[4].coluna]!='W')
    {
        //persegue o pacman para baixo
        if(TempoFantasmaL>=intervaloFantasmaL)
        {
            fantasmas[4].linha++; //caso a coluna do fantasma e do pacman estejam alinhadas a linhas serão alinhadas
            if(mapa[fantasmas[4].linha+1][fantasmas[4].coluna]=='W')
            {
                perseguirF5=false;
            }
            TempoFantasmaL=0;
        }
    }
    if(fantasmas[4].coluna>colunaJogador&&mapa[fantasmas[4].linha][fantasmas[4].coluna-1]!='W')
    {
        //persegue o pacman pra esquerda
        if(TempoFantasmaL>=intervaloFantasmaL)
        {
            fantasmas[4].coluna--;//alinha a coluna só que no sentido oposto
            if(mapa[fantasmas[4].linha][fantasmas[4].coluna-1]=='W')
            {
                perseguirF5=false;
            }
            TempoFantasmaL=0;
        }
    }
    if(fantasmas[4].coluna==colunaJogador&&fantasmas[4].linha>linhaJogador&&mapa[fantasmas[4].linha-1][fantasmas[4].coluna]!='W')
    {
        //persegue o pacman para cima
        if(TempoFantasmaL>=intervaloFantasmaL)
        {
            fantasmas[4].linha--; //alinha a linha só que no sentido oposto
            if(mapa[fantasmas[4].linha-1][fantasmas[4].coluna]=='W')
            {
                perseguirF5=false;
            }
            TempoFantasmaL=0;
        }
    }
}
//Função que move o fantasma laranja para fazer uma movimentação aleatoria
void fantasmaLaranjaBuscar(float intervaloFantasmaL)
{
    //movimentação do fantasma vermelho
    if((numeroF5==0||numeroF5==7)&&(mapa[fantasmas[4].linha][fantasmas[4].coluna+1]!='W'))
    {
        //le numero gerado aleatoriamente e se locomove caso não haja parede
        andarF1=true;//registra que não tem parede que impeça o movimento do fantasma
        if(TempoFantasmaL>=intervaloFantasmaL)
        {
            //aguarda um determinado tempo decorrido
            fantasmas[4].coluna++;//desloca o fantasma
            TempoFantasmaL=0;
        }
    }
    else if(mapa[fantasmas[5].linha][fantasmas[5].coluna+1]=='W')
    {
        andarF5=false;//verifica se o fantasma parou de andar por conta de uma parede
    }
    if((numeroF5==1||numeroF5==6)&&(mapa[fantasmas[4].linha+1][fantasmas[4].coluna]!='W'))
    {
        //mesma lógica que o primerio if
        if(TempoFantasmaL>=intervaloFantasmaL)
        {
            fantasmas[4].linha++; //desloca o fantasma para baixo
            TempoFantasmaL=0;
        }
        andarF5=true;
    }
    else if(mapa[fantasmas[4].linha+1][fantasmas[4].coluna]=='W')
    {
        andarF5=false;
    }
    if((numeroF5==2||numeroF5==5)&&(mapa[fantasmas[4].linha][fantasmas[4].coluna-1]!='W'))
    {
        //mesma lógica de antes
        if(TempoFantasmaL>=intervaloFantasmaL)
        {
            fantasmas[4].coluna--;//desloca o fantasma para a esqueda
            TempoFantasmaL=0;
        }
        andarF5=true;
    }
    else if(mapa[fantasmas[4].linha][fantasmas[4].coluna-1]=='W')
    {
        andarF5=false;
    }
    if((numeroF5==3||numeroF5==4)&&(mapa[fantasmas[4].linha-1][fantasmas[4].coluna]!='W'))
    {
        //mesma lógica de antes
        if(TempoFantasmaL>=intervaloFantasmaL)
        {
            fantasmas[4].linha--; //desloca o fantasma para cima
            TempoFantasmaL=0;
        }
        andarF5=true;
    }
    else if(mapa[fantasmas[4].linha-1][fantasmas[4].coluna]=='W')
    {
        andarF5=false;
    }
    //fim do trecho
    if(andarF5==false)
    {
        // se o fantasma esbarra em uma parede gera é gerado um novo número aleatório para mudar a direção do fantasma
        srand(time(NULL));
        movimentoaleatorioF5();
        numeroF5=movimentoaleatorioF5();
    }
}
//Função que garante que somente um número exato de fantasmas estão no mapa
void ajustedeposicao()
{
    if(numFantasmas==0)
    {
        fantasmas[0].coluna=0;
        fantasmas[0].linha=0;
        fantasmas[1].coluna=0;
        fantasmas[1].linha=0;
        fantasmas[2].coluna=0;
        fantasmas[2].linha=0;
        fantasmas[3].coluna=0;
        fantasmas[3].linha=0;
        fantasmas[4].coluna=0;
        fantasmas[4].linha=0;
    }
    else if(numFantasmas==1)
    {
        fantasmas[1].coluna=0;
        fantasmas[1].linha=0;
        fantasmas[2].coluna=0;
        fantasmas[2].linha=0;
        fantasmas[3].coluna=0;
        fantasmas[3].linha=0;
        fantasmas[4].coluna=0;
        fantasmas[4].linha=0;
    }
    else if(numFantasmas==2)
    {
        fantasmas[2].coluna=0;
        fantasmas[2].linha=0;
        fantasmas[3].coluna=0;
        fantasmas[3].linha=0;
        fantasmas[4].coluna=0;
        fantasmas[4].linha=0;
    }
    else if(numFantasmas==3)
    {
        fantasmas[3].coluna=0;
        fantasmas[3].linha=0;
        fantasmas[4].coluna=0;
        fantasmas[4].linha=0;
    }
    else if(numFantasmas==4)
    {
        fantasmas[4].coluna=0;
        fantasmas[4].linha=0;
    }//garante que o programa  somente utlize os fantasmas que esteja no mapa e não pegue informação sobre fantasmas do mapa anterior
}
//Função que faz os fantasmas sairem da posição inicial
void sairDaPoscaoInicial(int fantasmaAsair)
{
    if(fantasmaAsair==0)
    {
        while(mapa[fantasmas[0].linha+1][fantasmas[0].coluna]!='W')
        {
            fantasmas[0].linha++;
        }
        while(mapa[fantasmas[0].linha][fantasmas[0].coluna-1]!='W')
        {
            fantasmas[0].coluna--;
        }
        while(mapa[fantasmas[0].linha-1][fantasmas[0].coluna]!='W')
        {
            fantasmas[0].linha--;
        }
        while(mapa[fantasmas[0].linha-1][fantasmas[0].coluna]=='W')
        {
            fantasmas[0].coluna++;
        }
        fantasmas[0].linha--;
        fantasmas[0].linha--;
        fantasmas[0].linha--;
        fantasmas[0].coluna++;
        fantasmas[0].coluna++;
        fantasmas[0].coluna++;
    }
    if(fantasmaAsair==1)
    {
        while(mapa[fantasmas[1].linha+1][fantasmas[1].coluna]!='W')
        {
            fantasmas[1].linha++;
        }
        while(mapa[fantasmas[1].linha][fantasmas[1].coluna-1]!='W')
        {
            fantasmas[1].coluna--;
        }
        while(mapa[fantasmas[1].linha-1][fantasmas[1].coluna]!='W')
        {
            fantasmas[1].linha--;
        }
        while(mapa[fantasmas[1].linha-1][fantasmas[1].coluna]=='W')
        {
            fantasmas[1].coluna++;
        }
        fantasmas[1].linha--;
        fantasmas[1].linha--;
        fantasmas[1].linha--;
        fantasmas[1].coluna++;
        fantasmas[1].coluna++;
        fantasmas[1].coluna++;
    }
    if(fantasmaAsair==2)
    {
        while(mapa[fantasmas[2].linha+1][fantasmas[2].coluna]!='W')
        {
            fantasmas[2].linha++;
        }
        while(mapa[fantasmas[2].linha][fantasmas[2].coluna-1]!='W')
        {
            fantasmas[2].coluna--;
        }
        while(mapa[fantasmas[2].linha-1][fantasmas[2].coluna]!='W')
        {
            fantasmas[2].linha--;
        }
        while(mapa[fantasmas[2].linha-1][fantasmas[2].coluna]=='W')
        {
            fantasmas[2].coluna++;
        }
        fantasmas[2].linha--;
        fantasmas[2].linha--;
        fantasmas[2].linha--;
        fantasmas[2].coluna++;
        fantasmas[2].coluna++;
        fantasmas[2].coluna++;
    }
    if(fantasmaAsair==3)
    {
        while(mapa[fantasmas[3].linha+1][fantasmas[3].coluna]!='W')
        {
            fantasmas[3].linha++;
        }
        while(mapa[fantasmas[3].linha][fantasmas[3].coluna-1]!='W')
        {
            fantasmas[3].coluna--;
        }
        while(mapa[fantasmas[3].linha-1][fantasmas[3].coluna]!='W')
        {
            fantasmas[3].linha--;
        }
        while(mapa[fantasmas[3].linha-1][fantasmas[3].coluna]=='W')
        {
            fantasmas[3].coluna++;
        }
        fantasmas[3].linha--;
        fantasmas[3].linha--;
        fantasmas[3].linha--;
        fantasmas[3].coluna++;
        fantasmas[3].coluna++;
        fantasmas[3].coluna++;
    }
    if(fantasmaAsair==4)
    {
        while(mapa[fantasmas[4].linha+1][fantasmas[4].coluna]!='W')
        {
            fantasmas[4].linha++;
        }
        while(mapa[fantasmas[4].linha][fantasmas[4].coluna-1]!='W')
        {
            fantasmas[4].coluna--;
        }
        while(mapa[fantasmas[4].linha-1][fantasmas[4].coluna]!='W')
        {
            fantasmas[4].linha--;
        }
        while(mapa[fantasmas[4].linha-1][fantasmas[4].coluna]=='W')
        {
            fantasmas[4].coluna++;
        }
        fantasmas[4].linha--;
        fantasmas[4].linha--;
        fantasmas[4].linha--;
        fantasmas[4].coluna++;
        fantasmas[4].coluna++;
        fantasmas[4].coluna++;
    }
}
//Checa se algum dos fantamas ocupa a mesma posição do que o PACMAN
//Se ocupar, decresce 1 da vida e reinicia a posição dos fantasmas e do PACMAN
//Se a vida chegar a zero reinicia tudo
void morte()
{
    //caso o pacman e o fantasma se choquem
    if(fantasmas[0].coluna==colunaJogador&&fantasmas[0].linha==linhaJogador)
    {
        //Reinicia a posicao inicial de todos os fantasmas
        for(int i=0; i<numFantasmas; i++)
        {
            fantasmas[i].coluna=fantasmas[i].posiInicialXF;
            fantasmas[i].linha=fantasmas[i].posiInicialYF;
        }
        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                if (mapa[i][j]=='J')
                {
                    mapa[i][j]=' ';
                    //exclui o caractere J do mapa
                }
            }
        }
        linhaJogador=posiInicialYP;//redefine a posição do jogador para a posição inicial
        colunaJogador=posiInicialXP;
        mapa[linhaJogador][colunaJogador]='J';//reescreve o jogador na posição iicial
        vidas=vidas-1;//decrementa as vidas(mesma logica nos trechos de códigos seguintes)
    }
    //caso o pacman e o fantasma se choquem
    else if(fantasmas[1].coluna==colunaJogador&&fantasmas[1].linha==linhaJogador)
    {
        //Reinicia a posicao inicial de todos os fantasmas
        for(int i=0; i<numFantasmas; i++)
        {
            fantasmas[i].coluna=fantasmas[i].posiInicialXF;
            fantasmas[i].linha=fantasmas[i].posiInicialYF;
        }
        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                if (mapa[i][j]=='J')
                {
                    mapa[i][j]=' ';
                    //exclui o caractere J do mapa
                }
            }
        }
        linhaJogador=posiInicialYP;//redefine a posição do jogador para a posição inicial
        colunaJogador=posiInicialXP;
        mapa[linhaJogador][colunaJogador]='J';//reescreve o jogador na posição iicial
        vidas=vidas-1;
    }
    //caso o pacman e o fantasma se choquem
    else if(fantasmas[2].coluna==colunaJogador&&fantasmas[2].linha==linhaJogador)
    {
        //Reinicia a posicao inicial de todos os fantasmas
        for(int i=0; i<numFantasmas; i++)
        {
            fantasmas[i].coluna=fantasmas[i].posiInicialXF;
            fantasmas[i].linha=fantasmas[i].posiInicialYF;
        }
        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                if (mapa[i][j]=='J')
                {
                    mapa[i][j]=' ';
                    //exclui o caractere J do mapa
                }
            }
        }
        linhaJogador=posiInicialYP;//redefine a posição do jogador para a posição inicial
        colunaJogador=posiInicialXP;
        mapa[linhaJogador][colunaJogador]='J';//reescreve o jogador na posição iicial
        vidas=vidas-1;
    }
    //caso o pacman e o fantasma se choquem
    else if(fantasmas[3].coluna==colunaJogador&&fantasmas[3].linha==linhaJogador)
    {
        //Reinicia a posicao inicial de todos os fantasmas
        for(int i=0; i<numFantasmas; i++)
        {
            fantasmas[i].coluna=fantasmas[i].posiInicialXF;
            fantasmas[i].linha=fantasmas[i].posiInicialYF;
        }
        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                if (mapa[i][j]=='J')
                {
                    mapa[i][j]=' ';
                    //exclui o caractere J do mapa
                }
            }
        }
        linhaJogador=posiInicialYP;//redefine a posição do jogador para a posição inicial
        colunaJogador=posiInicialXP;
        mapa[linhaJogador][colunaJogador]='J';//reescreve o jogador na posição iicial
        vidas=vidas-1;
    }
    //caso o pacman e o fantasma se choquem
    else if(fantasmas[4].coluna==colunaJogador&&fantasmas[4].linha==linhaJogador)
    {
        //Reinicia a posicao inicial de todos os fantasmas
        for(int i=0; i<numFantasmas; i++)
        {
            fantasmas[i].coluna=fantasmas[i].posiInicialXF;
            fantasmas[i].linha=fantasmas[i].posiInicialYF;
        }
        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                if (mapa[i][j]=='J')
                {
                    mapa[i][j]=' ';
                    //exclui o caractere J do mapa
                }
            }
        }
        linhaJogador=posiInicialYP;//redefine a posição do jogador para a posição inicial
        colunaJogador=posiInicialXP;
        mapa[linhaJogador][colunaJogador]='J';//reescreve o jogador na posição iicial
        vidas=vidas-1;
    }
    //Se a vida for 0
    //Reinicia todos os parametros
    if(vidas==0)
    {
        numPastilhas=0;
        carregarMapa("Mapa01.txt");//recarrega o mapa 1 quando as vidas acabam
        TempoDecorrido=0;
        intervaloDeTempo=120;
        numMapa=0;
        inserirscore("ranking.bin");
        vidas=3;
        novoJogador.score=0;
        NumMapaTitulo=1;
        selecao=1;//volta ao menu original
    }
}
//Cria um inteiro aleatorio para o fantasma 1
int movimentoaleatorioF1()
{
    int min=0;
    int max=7;
    int numeroRandom;
    numeroRandom = min + (rand() % (max - min + 1));
    if(numeroRandom==ultimo_numero1&&numeroRandom<7)
    {
        numeroRandom=numeroRandom+1;
        ultimo_numero1 = numeroRandom;
        return numeroRandom;
    }
    else if(numeroRandom==ultimo_numero1&&numeroRandom==7)
    {
        numeroRandom=numeroRandom+1;
        ultimo_numero1 = numeroRandom;
        return numeroRandom;
    }
    else
    {
        ultimo_numero1 = numeroRandom;
        return numeroRandom;
    }
}
//Cria um inteiro aleatorio para o fantasma 2
int movimentoaleatorioF2()
{
    int min=0;
    int max=7;
    int numeroRandom;
    numeroRandom = min + (rand() % (max - min + 1));
    if(numeroRandom==ultimo_numero2&&numeroRandom<7)
    {
        numeroRandom=numeroRandom+1;
        ultimo_numero2 = numeroRandom;
        return numeroRandom;
    }
    else if(numeroRandom==ultimo_numero2&&numeroRandom==7)
    {
        numeroRandom=numeroRandom-1;
        ultimo_numero2 = numeroRandom;
        return numeroRandom;
    }
    else
    {
        ultimo_numero2 = numeroRandom;
        return numeroRandom;
    }
}
//Cria um inteiro aleatorio para o fantasma 3
int movimentoaleatorioF3()
{
    int min=0;
    int max=7;
    int numeroRandom;
    numeroRandom = min + (rand() % (max - min + 1));
    if(numeroRandom==ultimo_numero3&&numeroRandom<7)
    {
        numeroRandom=numeroRandom+1;
        ultimo_numero3 = numeroRandom;
        return numeroRandom;
    }
    else if(numeroRandom==ultimo_numero3&&numeroRandom==7)
    {
        numeroRandom=numeroRandom+1;
        ultimo_numero3 = numeroRandom;
        return numeroRandom;
    }
    else
    {
        ultimo_numero3 = numeroRandom;
        return numeroRandom;
    }
}
//Cria um inteiro aleatorio para o fantasma 4
int movimentoaleatorioF4()
{
    int min=0;
    int max=7;
    int numeroRandom;
    numeroRandom = min + (rand() % (max - min + 1));
    if(numeroRandom==ultimo_numero4&&numeroRandom<7)
    {
        numeroRandom=numeroRandom+1;
        ultimo_numero4 = numeroRandom;
        return numeroRandom;
    }
    else if(numeroRandom==ultimo_numero4&&numeroRandom==7)
    {
        numeroRandom=numeroRandom+1;
        ultimo_numero4 = numeroRandom;
        return numeroRandom;
    }
    else
    {
        ultimo_numero4 = numeroRandom;
        return numeroRandom;
    }
}
//Cria um inteiro aleatorio para o fantasma 5
int movimentoaleatorioF5()
{
    int min=0;
    int max=7;
    int numeroRandom;
    numeroRandom = min + (rand() % (max - min + 1));
    if(numeroRandom==ultimo_numero5&&numeroRandom<7)
    {
        numeroRandom=numeroRandom+1;
        ultimo_numero5 = numeroRandom;
        return numeroRandom;
    }
    else if(numeroRandom==ultimo_numero5&&numeroRandom==7)
    {
        numeroRandom=numeroRandom+1;
        ultimo_numero5 = numeroRandom;
        return numeroRandom;
    }
    else
    {
        ultimo_numero5 = numeroRandom;
        return numeroRandom;
    }
}

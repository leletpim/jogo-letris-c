// Nome: Letícia Pimentel Garcia
// Matrícula: 221016202

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Definição de macros para os arquivos
#define ARQUIVO_TEXTO "numeros.txt" // Arquivo dos números
#define ARQUIVO_RANKING "ranking.bin"      // Arquivo do ranking

// Arquivos e variáveis globais
FILE* arquivo;
FILE* arquivo_bin;

char nickname[20];                  // Nickname do jogador
int points = 0;                     // Pontuação do jogador
int get_martelo = 10000;            // Pontuação inicial necessária para receber um martelo
int martelos = 0;                   // Quantidade de martelos do jogador
int M[10][5] = {0};                 // Matriz de jogo
int free_line[5] = {9, 9, 9, 9, 9}; // Linha livre para cada coluna
int P[5][5] = {{0, 1, 2, 3, 4},
               {1, 2, 0, 3, 4},
               {2, 1, 3, 0, 4},
               {3, 2, 4, 1, 0},
               {4, 3, 2, 1, 0}};    // Prioridades de verificação para cada coluna

// Nickname e pontuação do jogador para salvar no ranking
typedef struct {
    char nick[20];
    int pontos;
}DadosJogador;

// Funções auxiliares
void limpa_tela();
void mostra(int nro, int nro_seguinte);

// Funcões do menu principal
void menu_principal();
void configuracoes();
void instrucoes();
void mostra_ranking();

// Funções de jogo
void jogar();
int check(int l, int c);
void gravity();
void ganhou();
void perdeu();
void martelo(int nro, int nro_seguinte);
void zerar();

// Funções do ranking
void zera_ranking();
void salva_ranking();
void bubbleSort(DadosJogador ranking[], int n);

int main(){
    limpa_tela();
    printf("\nBem vindo(a) ao LETRIS!\n\n");
    printf("Informe seu nickname: ");
    scanf("%s", nickname);
    menu_principal();

    return 0;
}

// Menu principal
void menu_principal(){
    int opcao;

    while(1){  // Loop até uma entrada válida ser fornecida
        limpa_tela();

        printf("*** LETRIS ***\n\n");
        printf("Olá, %s!\n\n", nickname);
        printf("1 - Jogar\n");
        printf("2 - Configurações\n");
        printf("3 - Instruções\n");
        printf("4 - Ranking\n");
        printf("5 - Sair\n\n");
        printf("Digite a opção desejada: ");

        if(scanf("%d", &opcao) == 1 && opcao >= 1 && opcao <= 5){
            switch(opcao){
                case 1:
                    jogar();
                    break;
                case 2:
                    configuracoes();
                    break;
                case 3:
                    instrucoes();
                    break;
                case 4:
                    mostra_ranking();
                    break;
                case 5:
                    limpa_tela();
                    exit(0);  // Sai da função (fecha o jogo)
            }
        }
        else{
            getchar();
        }
    }
}

// Menu de configurações
void configuracoes(){
    int opcao;

    while(1){
        limpa_tela();

        printf("*** CONFIGURAÇÕES ***\n\n");
        printf("1 - Zerar ranking\n");
        printf("2 - Modo de dificuldade\n");
        printf("3 - Voltar ao menu principal\n\n");
        printf("Digite a opção desejada: ");

        if(scanf("%d", &opcao) == 1 && opcao >= 1 && opcao <= 3){
            switch(opcao) {
                case 1:
                    zera_ranking(); // Zera ranking
                    break;
                case 2:
                    limpa_tela();
                    printf(" Em desenvolvimento...\n");
                    printf("\nTecle <enter> para continuar...");
                    while(getchar() != '\n');
                    getchar();
                    break;
                case 3:
                    menu_principal(); // Volta ao menu principal
                    return;
            }
        }
    }
}

// Esvazia o ranking
void zera_ranking(){
    limpa_tela();

    char sim_nao;
    while(scanf("%c", &sim_nao) != 1 || (sim_nao != 's' && sim_nao != 'n' && sim_nao != 'S' && sim_nao != 'N')){
        limpa_tela();
        printf("Tem certeza que deseja zerar o ranking? (s/n) ");
    }
    if(sim_nao == 's' || sim_nao == 'S'){
        arquivo_bin = fopen(ARQUIVO_RANKING, "wb"); // Abre o arquivo no modo "wb" para zerar o conteúdo

        if(arquivo_bin != NULL){
            limpa_tela();
            fclose(arquivo_bin);
            printf("\nRanking zerado com sucesso!\n");
        }

        while(getchar() != '\n');
        printf("\nTecle <enter> para continuar...");
        getchar();
    }
}

// Mostra instruções ao jogador
void instrucoes(){
    limpa_tela();
    printf("Como jogar LETRIS:\n\n");
    printf("O objetivo do jogo é atingir a maior pontuação possível sem que os espaços sejam todos preenchidos.\n\n"
        "Regras:\n"
        "Dois números aparecem no topo da tela. O número à esquerda é o que será jogado, o outro é o próximo. O\n"
        "jogador deve escolher uma coluna para inserir o número, que cai até a casa mais abaixo disponível.\n\n"
        "Se algum dos vizinhos (esquerda, direita e abaixo) do número jogado tiverem valor igual a ele, eles i-\n"
        "rão se fundir, e adotarão um novo valor maior - uma potência de dois que, quanto mais vizinhos iguais,\n"
        "maior será.\n\n"
        "A cada 10.000 pontos, o jogador receberá um martelo que funciona como uma 'vida': se a matriz encher e\n"
        "o jogador tiver pelo menos um martelo, ele poderá usá-lo para eliminar qualquer bloco da matriz, tendo\n"
        "uma chance de continuar o jogo.\n\n"
        "Dicas:\n"
        "Planeje com antecedência onde colocar os números, pois uma má escolha pode bloquear as colunas e tornar\n"
        "as próximas jogadas mais difíceis.\n\n"
        "Fim de jogo:\n"
        "O jogo pode terminar de duas maneiras:\n\n"
        "Vitória: Quando o jogador consegue alocar todos os números.\n"
        "Derrota: Quando a matriz está cheia e o próximo número não pode ser inserido em nenhuma coluna. O joga-\n"
        "dor só perde se não possuir martelos.\n\n"
        "Boa sorte!\n");


    printf("\nTecle <enter> para prosseguir...");

    while(getchar() != '\n');
    getchar();

    menu_principal();
}

// Ordena o ranking
void bubbleSort(DadosJogador ranking[], int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - 1 - i; j++){
            if(ranking[j].pontos < ranking[j + 1].pontos){
                DadosJogador temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }
}

// Mostra o ranking ordenado
void mostra_ranking(){
    arquivo_bin = fopen("ranking.bin", "rb");

    if(arquivo_bin == NULL){
        arquivo_bin = fopen("ranking.bin", "wb"); // Cria o arquivo se não existir
        fclose(arquivo_bin);
        arquivo_bin = fopen("ranking.bin", "rb"); // Reabre para leitura
    }

    DadosJogador ranking[100];
    int i = 0;

    // Lê o ranking do arquivo binário
    while(i < 100 && fread(&ranking[i], sizeof(DadosJogador), 1, arquivo_bin)){
        i++;
    }
    fclose(arquivo_bin);

    bubbleSort(ranking, i); // Ordena o ranking

    limpa_tela();
    printf("Ranking:\n\n");
    for(int j = 0; j < i; j++){
        printf("%d. %s - %d pontos\n", j + 1, ranking[j].nick, ranking[j].pontos);
    }

    while(getchar() != '\n');
    printf("\nTecle <enter> para voltar ao menu...");
    getchar();
}

// Função principal do jogo
void jogar(){
    arquivo = fopen(ARQUIVO_TEXTO, "r");

    int nro, nro_seguinte;
    fscanf(arquivo, "%d", &nro);

    while(fscanf(arquivo, "%d", &nro_seguinte) != EOF){ // Lê a partir do 2º número até EOF
        mostra(nro, nro_seguinte);
        printf("Em qual coluna deseja inserir o número? ");

        int c;
        // Pede ao usuário a coluna até que seja um valor válido e que a coluna não esteja cheia
        while(scanf("%d", &c) != 1 || c < 1 || c > 5 || (free_line[c - 1] == -1 && nro != M[0][c - 1])){
            mostra(nro, nro_seguinte);
            printf("Em qual coluna deseja inserir o número? ");
            while(getchar() != '\n');
        }

        int coluna = c - 1; // Define coluna
        int linha = free_line[coluna]; //Define linha

        if(linha == -1){
            linha++;
            M[linha][coluna] += nro; // Para caso de coluna cheia
        }
        else{
            M[linha][coluna] = nro;
        }

        // Primeira checagem dos vizinhos do número recém-jogado
        int fusoes = check(linha, coluna);

        while(fusoes > 0){
            M[linha][coluna] *= pow(2, fusoes); // Atualiza o valor da célula
            points += M[linha][coluna];

            if(points >= get_martelo){
                martelos++;
                get_martelo += 10000;
            }

            gravity();
            linha = free_line[coluna] + 1; // Atualiza linha após gravidade
            fusoes = check(linha, coluna); // Verifica novamente os vizinhos
        }

        // Verifica os vizinhos dos demais blocos de acordo com as prioridades
        int i = 0;
        while(i < 5){
            for(int j = 0; j < 10; j++){
                if(M[j][P[coluna][i]] != 0){
                    M[j][P[coluna][i]] *= (int)pow(2, check(j, P[coluna][i]));
                    gravity();
                }
            }
            i++;
        }

        nro = nro_seguinte;

        if(free_line[0] == -1 && free_line[1] == -1 && free_line[2] == -1 && free_line[3] == -1 && free_line[4] == -1){
            if(nro != M[0][0] && nro != M[0][1] && nro != M[0][2] && nro != M[0][3] && nro != M[0][4]){
                perdeu();
                martelo(nro, nro_seguinte);
            }
        }
    }

    fclose(arquivo);

    ganhou();
}

// Verifica se há vizinhos iguais
int check(int l, int c){
    int potencia = 0;

    if(l < 9 && M[l][c] == M[l + 1][c] && M[l][c] != 0){ // Abaixo
        potencia++;
        M[l + 1][c] = 0;
    }
    if(c > 0 && M[l][c] == M[l][c - 1] && M[l][c] != 0){ // Esquerda
        potencia++;
        M[l][c - 1] = 0;
    }
    if(c < 4 && M[l][c] == M[l][c + 1] && M[l][c] != 0){ // Direita
        potencia++;
        M[l][c + 1] = 0;
    }
    return potencia;
}

// Aplica a gravidade para os números caírem
void gravity(){
    for(int j = 0; j < 5; j++){
        for(int i = 9; i > 0; i--){
            if(M[i - 1][j] != 0 && M[i][j] == 0){
                M[i][j] = M[i - 1][j];
                M[i - 1][j] = 0;
            }
        }

        // Atualiza a linha livre para cada coluna
        for(int i = 9; i >= 0; i--){
            if(M[i][j] == 0){
                free_line[j] = i;
                break;
            }
            else if(i == 0){
                free_line[j] = -1;
            }
        }
    }
}

// Função para caso de vitória
void ganhou(){
    limpa_tela();
    printf("         PARABÉNS! Você zerou LETRIS!\n\n");

    salva_ranking(); // Salva o ranking ao ganhar o jogo

    printf("Tecle <enter> para voltar ao menu principal...");

    while(getchar() != '\n');
    getchar();

    zerar();
    menu_principal();
}

// Função para caso de derrota
void perdeu(){
    if(martelos == 0){ // Verifica se o usuário possui martelos
        limpa_tela();
        printf("            VOCÊ PERDEU!\n");
        printf("  Não há mais espaços disponíveis.\n\n");

        salva_ranking(); // Salva o ranking ao perder o jogo

        printf("Tecle <enter> para voltar ao menu principal...");

        while(getchar() != '\n');
        getchar();

        zerar();
        menu_principal();
    }
}

// Função para o martelo
void martelo(int nro, int nro_seguinte){
    if(martelos > 0){ // Verifica se há martelos disponíveis
        int c, l;
        while(1){ // Pede coluna até que seja um valor válido
            mostra(nro, nro_seguinte);
            printf("MATRIZ CHEIA!\n");
            printf("USE SEU MARTELO: qual a COLUNA do bloco que deseja quebrar? (1 a 5) ");
            if(scanf("%d", &c) == 1 && c >= 1 && c <= 5) break;
            while(getchar() != '\n');
        }

        while(1){ // Pede linha até que seja um valor válido
            mostra(nro, nro_seguinte);
            printf("MATRIZ CHEIA!\n");
            printf("USE SEU MARTELO: Qual a LINHA do bloco que deseja quebrar? (1 a 10) ");
            if(scanf("%d", &l) == 1 && l >= 1 && l <= 10) break;
            while(getchar() != '\n');
        }

        int linha = l - 1;
        int coluna = c - 1;
        M[linha][coluna] = 0; // Zera o bloco escolhido
        gravity();

        martelos--; // Reduz um martelo após o uso

        // Primeira checagem dos vizinhos da casa martelada
        int fusoes = check(linha, coluna);

        while(fusoes > 0){
            M[linha][coluna] *= pow(2, fusoes); // Atualiza o valor da célula
            points += M[linha][coluna];

            if(points >= get_martelo){
                martelos++;
                get_martelo *= 2;
            }

            gravity();
            linha = free_line[coluna] + 1; // Atualiza linha após gravidade
            fusoes = check(linha, coluna); // Verifica novamente os vizinhos
        }

        // Verifica os vizinhos dos demais blocos
        int i = 0;
        while(i < 5){
            for(int j = 0; j < 10; j++){
                if(M[j][P[coluna][i]] != 0){
                    M[j][P[coluna][i]] *= (int)pow(2, check(j, P[coluna][i]));
                    gravity();
                }
            }
            i++;
        }
    }
}

// Salva a posição do jogador no ranking
void salva_ranking(){
    arquivo_bin = fopen(ARQUIVO_RANKING, "ab");

    DadosJogador jogador;
    strcpy(jogador.nick, nickname);
    jogador.pontos = points;

    fwrite(&jogador, sizeof(DadosJogador), 1, arquivo_bin);
    fclose(arquivo_bin);
}

// Zera as variáveis para um novo jogo
void zerar(){
    points = 0;
    get_martelo = 10000;
    martelos = 0;

    for(int i = 0; i < 5; i++){
        free_line[i] = 9;
    }

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 5; j++){
            M[i][j] = 0;
        }
    }
}

// Função para limpar a tela
void limpa_tela(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Função para mostrar a matriz de jogo
void mostra(int nro, int nro_seguinte){
    int i, j;
    limpa_tela();
    printf("           +----+  +----+\n");
    printf("           |%4d|  |%4d|   martelos: %d\n", nro, nro_seguinte, martelos);
    printf("           +----+  +----+\n");

    for(i = 0; i < 10; i++){
        printf("  +----+----+----+----+----+\n");
        printf("  |");
        for(j = 0; j < 5; j++){
            if (M[i][j] != 0)
                printf("%4d|", M[i][j]);
            else
                printf("    |");
        }
        printf("\n");
    }
    printf("  +----+----+----+----+----+\n");
    printf("  +----+----+----+----+----+\n");
    printf("  |  1 |  2 |  3 |  4 |  5 |\n");
    printf("  +----+----+----+----+----+\n\n");
}

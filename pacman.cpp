#include <raylib.h>
#include <math.h>

void introducao(Texture pacman0, Texture pacman1, Texture pacman2, Texture pacman3, Font fonte, float* posx) {
    float rotacaodireita = 180.0f; // Pacman virado para direita
    float escala = 4.0f; // Escala do pacman
    *posx += 0.2f; // Velocidade do pacman

    Vector2 posicao = {*posx, 500}; // Posição do pacman

    if (*posx >= 800) {
        DrawTextEx(fonte, "P", (Vector2){ 350, 230 }, 80, 0, WHITE);
    }
    if (*posx >= 900) {
        DrawTextEx(fonte, "A", (Vector2){ 450, 230 }, 80, 0, WHITE);
    }
    if (*posx >= 1000) {
        DrawTextEx(fonte, "C", (Vector2){ 550, 230 }, 80, 0, WHITE);
    }
    if (*posx >= 1100) {
        DrawTextEx(fonte, "M", (Vector2){ 650, 230 }, 80, 0, WHITE);
    }
    if (*posx >= 1200) {
        DrawTextEx(fonte, "A", (Vector2){ 750, 230 }, 80, 0, WHITE);
    }
    if (*posx >= 1300) {
        DrawTextEx(fonte, "N", (Vector2){ 850, 230 }, 80, 0, WHITE);
    }
    if (*posx >= 1900){
        DrawTextEx(fonte, "JOGAR", (Vector2){ 500, 400 }, 40, 10, WHITE);
    }
    if (*posx >= 2100){
        DrawTextEx(fonte, "SCORE", (Vector2){ 500, 500 }, 40, 10, WHITE);
    }
    if (*posx >= 2400){
        DrawTextEx(fonte, "MENU", (Vector2){ 500, 600 }, 40, 25, WHITE);
    }
    if (fabs((int)(*posx) % 400) >= 300) {
        DrawTextureEx(pacman0, posicao, rotacaodireita, escala, WHITE);
    } else if (fabs((int)(*posx) % 400) >= 200) {
        DrawTextureEx(pacman1, posicao, rotacaodireita, escala, WHITE);
    } else if (fabs((int)(*posx) % 400) >= 100) {
        DrawTextureEx(pacman2, posicao, rotacaodireita, escala, WHITE);
    } else {
        DrawTextureEx(pacman3, posicao, rotacaodireita, escala, WHITE);
    }
}
void menu(Font fonte, Texture pacman0, Texture pacman1, Texture pacman2, Texture pacman3, int posicaopacmenu){
    float rotacaodireita = 180.0f; // Pacman virado para direita
    Vector2 posicao = {500, 663 -(posicaopacmenu*100)}; // Posição do pacman
    
    DrawTextEx(fonte, "P", (Vector2){ 350, 230 }, 80, 0, WHITE);
    DrawTextEx(fonte, "A", (Vector2){ 450, 230 }, 80, 0, WHITE);
    DrawTextEx(fonte, "C", (Vector2){ 550, 230 }, 80, 0, WHITE);
    DrawTextEx(fonte, "M", (Vector2){ 650, 230 }, 80, 0, WHITE);
    DrawTextEx(fonte, "A", (Vector2){ 750, 230 }, 80, 0, WHITE);
    DrawTextEx(fonte, "N", (Vector2){ 850, 230 }, 80, 0, WHITE);
    DrawTextEx(fonte, "JOGAR", (Vector2){ 500, 400 }, 40, 10, WHITE);
    DrawTextEx(fonte, "SCORE", (Vector2){ 500, 500 }, 40, 10, WHITE);
    DrawTextEx(fonte, "MENU", (Vector2){ 500, 600 }, 40, 25, WHITE);
    
    DrawTextureEx(pacman1, posicao, rotacaodireita, 0.8, WHITE);
}

int main() {
    InitWindow(1280, 720, "Pacman"); // Inicializa a janela
    // Carrega os pngs
    Texture vida = LoadTexture("./imagens/vida.png"); // Coração
    Texture pacman0 = LoadTexture("./imagens/pacman0.png"); // Pacman fechado
    Texture pacman1 = LoadTexture("./imagens/pacman1.png"); // Pacman boca meio aberta
    Texture pacman2 = LoadTexture("./imagens/pacman2.png"); // Pacman boca totalmente aberta
    Texture pacman3 = LoadTexture("./imagens/pacman3.png"); // Pacman boca meio aberta
    Font fonte = LoadFont("./fonte.ttf"); // Fonte do jogo
    //SetTargetFPS(60);
    
    float posx = (-pacman0.width); //Posição inicial do pacman
    int a = 0; // Caso esteja entrando no jogo pela primeira vez
    //a = 0 Faz a introdução
    //a = 1 Menu
    //a = 2 Jogo
    //a = 3 Score
    int posicaopacmenu = 2;
    while (!WindowShouldClose()) { // Enquanto não for fechada a janela
        BeginDrawing(); // Inicia o desenho
        ClearBackground(BLACK); // Limpa a tela para os objetos que se movem não deixarem rastros

        if (a == 0) {
            introducao(pacman0, pacman1, pacman2, pacman3, fonte, &posx);
            if (posx > 2500) a = 1;
        }
        else if(a == 1){
            if (IsKeyPressed(KEY_DOWN) && posicaopacmenu >= 1){
                posicaopacmenu--;
            }
            if (IsKeyPressed(KEY_UP) && posicaopacmenu <= 1){
                posicaopacmenu++;
            }
            menu(fonte, pacman0, pacman1, pacman2, pacman3, posicaopacmenu);
        }
        EndDrawing(); // Termina o desenho
    }

    // Libera as texturas
    UnloadTexture(vida);
    UnloadTexture(pacman0);
    UnloadTexture(pacman1);
    UnloadTexture(pacman2);
    UnloadTexture(pacman3);

    CloseWindow();
    return 0;
}
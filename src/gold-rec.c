#include <raylib.h>

#define BG (Color) { 0x21, 0x21, 0x21, 0xff }

#define PHI 1.6180339887f
#define N   15

int main() {
    float w = 800;
    float h = w / PHI;

    InitWindow(w, h, "Golden Rectangles");
    SetTargetFPS(60);

    Rectangle rec[N] = {};
    float thick = 2.0f;

    for (int i=0; i < N; i++) {
        float diff = 0;

        rec[i].width    = w;
        rec[i].height   = h;

        rec[i].x        = GetScreenWidth()  - w;
        rec[i].y        = GetScreenHeight() - h;

        if (i % 2) {
            h -= w;
        }
        else {
            w -= h;
        }
    }

    while (!WindowShouldClose()) {
        BeginDrawing();

            ClearBackground(BG);

            for (int i=0; i < N; i++)
                DrawRectangleLinesEx(
                    rec[i], 
                    thick, 
                    GOLD
                );

        EndDrawing();
    }

    CloseWindow();
}
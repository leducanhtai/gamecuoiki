/*#include <iostream>
#include "src/include/SDL2/SDL.h"
#include <stdio.h>
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 900;
const int SPRITE_SPEED = 2; // Đổi tốc độ di chuyển ở đây
// Khởi động SDL và tạo cửa sổ
bool init();
// Tải phương tiện
bool loadMedia();
// Giải phóng phương tiện và tắt SDL
void close();
// Cửa sổ chúng ta sẽ hiển thị
SDL_Window* gWindow = NULL;
// Bề mặt chứa bởi cửa sổ
SDL_Surface* gScreenSurface = NULL;
// Hình ảnh chúng ta sẽ tải và hiển thị trên màn hình
SDL_Surface* gBackground = NULL;
SDL_Surface* gSprite = NULL;
// Vị trí hiện tại của sprite
int spriteX = SCREEN_WIDTH / 2;
int spriteY = SCREEN_HEIGHT - 100;
bool init() {
    // Cờ khởi tạo
    bool success = true;
    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Tạo cửa sổ
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // Lấy bề mặt cửa sổ
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}
bool loadMedia() {
    // Đang tải cờ thành công
    bool success = true;
    // Tải hình nền
    gBackground = SDL_LoadBMP("img/farm.bmp");
    if (gBackground == NULL) {
        printf("Unable to load background image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    // Tải hình ảnh sprite
    gSprite = SDL_LoadBMP("img/128148pngtree226128148basket-5407070.bmp");
    if (gSprite == NULL) {
        printf("Unable to load sprite image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    return success;
}
void close() {
    // Phân bổ bề mặt
    SDL_FreeSurface(gBackground);
    gBackground = NULL;
    SDL_FreeSurface(gSprite);
    gSprite = NULL;
    // Phá hủy cửa sổ
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    // Thoát khỏi hệ thống con SDL
    SDL_Quit();
}
int main(int argc, char* args[]) {
    // Khởi động SDL và tạo cửa sổ
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        // Tải phương tiện
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            // Cờ vòng lặp chính
            bool quit = false;
            // Xử lý sự kiện
            SDL_Event e;
            // Biến thời gian
            Uint32 lastUpdate = SDL_GetTicks();
            const Uint32 FRAME_DELAY = 400 / 60; // 60 frames per second
            // While ứng dụng đang chạy
            while (!quit) {
                // Xử lý các sự kiện trên hàng đợi
                while (SDL_PollEvent(&e) != 0) {
                    // Yêu cầu của người dùng thoát
                    if (e.type == SDL_QUIT) {
                    quit = true;
                    }
                }
                // Lấy thời gian hiện tại
                Uint32 currentTime = SDL_GetTicks();
                // Tính chênh lệch thời gian kể từ lần cập nhật cuối cùng
                Uint32 deltaTime = currentTime - lastUpdate;
                // Nếu đủ thời gian trôi qua, hãy di chuyển sprite
                if(deltaTime >= FRAME_DELAY) {
                    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
                    if (currentKeyStates[SDL_SCANCODE_LEFT] && spriteX > 0) { // Kiểm tra xem sprite có ra khỏi ranh giới trái không
                        spriteX -= SPRITE_SPEED;
                        }
                    if (currentKeyStates[SDL_SCANCODE_RIGHT] && spriteX < SCREEN_WIDTH - gSprite->w) { // Kiểm tra xem sprite có ra khỏi ranh giới phải không
                        spriteX += SPRITE_SPEED;
                        }
                   // Cập nhật thời gian cập nhật lần cuối
                     lastUpdate = currentTime;
                }
                //Xóa màn hình
                SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0, 0, 0));
                //
                SDL_BlitSurface(gBackground, NULL, gScreenSurface, NULL);
                // Áp dụng hình ảnh sprite
                SDL_Rect spriteRect = { spriteX, spriteY, 0, 0 }; // Position of the sprite
                SDL_BlitSurface(gSprite, NULL, gScreenSurface, &spriteRect);
                // Cập nhật bề mặt
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }
    // Tài nguyên miễn phí và đóng SDL
    close();
    return 0;
}*/
#include <iostream>
#include "src/include/SDL2/SDL.h"
#include <stdio.h>
#include <vector>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 1015;
const int SPRITE_SPEED = 3; // Đổi tốc độ di chuyển ở đây
const int FALLING_SPEED = 1; // Tốc độ rơi của các hình ảnh

// Khởi động SDL và tạo cửa sổ
bool init();

// Tải phương tiện
bool loadMedia();

// Giải phóng phương tiện và tắt SDL
void close();

// Cửa sổ chúng ta sẽ hiển thị
SDL_Window* gWindow = NULL;

// Bề mặt chứa bởi cửa sổ
SDL_Surface* gScreenSurface = NULL;

// Hình ảnh chúng ta sẽ tải và hiển thị trên màn hình
SDL_Surface* gBackground = NULL;
SDL_Surface* gSprite = NULL;
SDL_Surface* gFallingImage = NULL;

// Vị trí hiện tại của sprite
int spriteX = SCREEN_WIDTH / 2;
int spriteY = SCREEN_HEIGHT - 100;

// Struct đại diện cho hình ảnh rơi tự do
struct FallingImage {
    int x, y;
};

// Mảng lưu trữ các hình ảnh rơi tự do
std::vector<FallingImage> fallingImages;

bool init() {
    // Cờ khởi tạo
    bool success = true;

    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Tạo cửa sổ
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // Lấy bề mặt cửa sổ
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

bool loadMedia() {
    // Đang tải cờ thành công
    bool success = true;

    // Tải hình nền
    gBackground = SDL_LoadBMP("img/caytao.bmp");
    if (gBackground == NULL) {
        printf("Unable to load background image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    // Tải hình ảnh sprite
    gSprite = SDL_LoadBMP("img/128148pngtree226128148basket-5407070.bmp");
    if (gSprite == NULL) {
        printf("Unable to load sprite image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    // Tải hình ảnh rơi tự do
    gFallingImage = SDL_LoadBMP("img/tao.bmp");
    if (gFallingImage == NULL) {
        printf("Unable to load falling image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

void close() {
    // Phân bổ bề mặt
    SDL_FreeSurface(gBackground);
    gBackground = NULL;
    SDL_FreeSurface(gSprite);
    gSprite = NULL;
    SDL_FreeSurface(gFallingImage);
    gFallingImage = NULL;

    // Phá hủy cửa sổ
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Thoát khỏi hệ thống con SDL
    SDL_Quit();
}

int main(int argc, char* args[]) {
    const int NUM_FALLING_IMAGES = 2;
    // Khởi động SDL và tạo cửa sổ
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        // Tải phương tiện
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            // Cờ vòng lặp chính
            bool quit = false;

            // Xử lý sự kiện
            SDL_Event e;

            // Biến thời gian
            Uint32 lastUpdate = SDL_GetTicks();
            const Uint32 FRAME_DELAY = 400 / 60; // 60 frames per second

            // Khởi tạo các hình ảnh rơi tự do
            for (int i = 0; i < NUM_FALLING_IMAGES; ++i) {
            FallingImage fallingImage;
            fallingImage.x = rand() % SCREEN_WIDTH;
            fallingImage.y = rand() % SCREEN_HEIGHT; // Chỉ rơi từ trên cùng của màn hình
            fallingImages.push_back(fallingImage);
            }

            // While ứng dụng đang chạy
            while (!quit) {
                // Xử lý các sự kiện trên hàng đợi
                while (SDL_PollEvent(&e) != 0) {
                    // Yêu cầu của người dùng thoát
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                // Lấy thời gian hiện tại
                Uint32 currentTime = SDL_GetTicks();

                // Tính chênh lệch thời gian kể từ lần cập nhật cuối cùng
                Uint32 deltaTime = currentTime - lastUpdate;

                // Nếu đủ thời gian trôi qua, hãy di chuyển sprite
                if (deltaTime >= FRAME_DELAY) {
                    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
                    if (currentKeyStates[SDL_SCANCODE_LEFT] && spriteX > 0) { // Kiểm tra xem sprite có ra khỏi ranh giới trái không
                        spriteX -= SPRITE_SPEED;
                    }
                    if (currentKeyStates[SDL_SCANCODE_RIGHT] && spriteX < SCREEN_WIDTH - gSprite->w) { // Kiểm tra xem sprite có ra khỏi ranh giới phải không
                        spriteX += SPRITE_SPEED;
                    }

                    // Cập nhật thời gian cập nhật lần cuối
                    lastUpdate = currentTime;
                }

                //Xóa màn hình
                SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0, 0, 0));

                // Vẽ hình nền
                SDL_BlitSurface(gBackground, NULL, gScreenSurface, NULL);

                // Vẽ các hình ảnh rơi tự do
                for (int i = 0; i < NUM_FALLING_IMAGES; ++i) {
                    fallingImages[i].y += FALLING_SPEED;
                    // Kiểm tra nếu hình ảnh rơi tự do ra khỏi màn hình
                    if (fallingImages[i].y > SCREEN_HEIGHT) {
                        fallingImages[i].x = rand() % SCREEN_WIDTH;
                        fallingImages[i].y = rand() % (SCREEN_HEIGHT / 2);
                    }
                    SDL_Rect fallingRect = { fallingImages[i].x, fallingImages[i].y, 0, 0 };
                    SDL_BlitSurface(gFallingImage, NULL, gScreenSurface, &fallingRect);
                }

                // Áp dụng hình ảnh sprite
                SDL_Rect spriteRect = { spriteX, spriteY, 0, 0 }; // Position of the sprite
                SDL_BlitSurface(gSprite, NULL, gScreenSurface, &spriteRect);

                // Cập nhật bề mặt
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    // Tài nguyên miễn phí và đóng SDL
    close();
    return 0;
}
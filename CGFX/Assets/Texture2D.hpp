#ifndef CGFX_TEXTURE2D_HPP
#define CGFX_TEXTURE2D_HPP

#include <string>
#include "SDL_image.h"
#include "CGFX/Core/Macros.hpp"
#include "CGFX/Core/Logger.hpp"

namespace cgfx {

    class Texture2D {
    public:
        Texture2D(SDL_Renderer *renderer, const std::string& file) :
                mTexture(IMG_LoadTexture(renderer, file.c_str())) {
            SDL_QueryTexture(mTexture, nullptr, nullptr, &mWidth, &mHeight);
            if (mTexture == nullptr) {
                throw std::runtime_error("texture loading failed");
            }
        }

        ~Texture2D() {
            SDL_DestroyTexture(mTexture);
        }

        DELETE_COPY_AND_ASSIGN(Texture2D);
        DELETE_MOVE_AND_ASSIGN(Texture2D);

        int GetWidth() const {
            return mWidth;
        }

        int GetHeight() const {
            return mHeight;
        }

        SDL_Texture *GetSDLTexture() const {
            return mTexture;
        }

    private:
        SDL_Texture *mTexture = nullptr;
        int mWidth = 0;
        int mHeight = 0;
    };

} // cgfx

#endif //CGFX_TEXTURE2D_HPP

#include "TextureHandler.h"

unique_ptr<TextureHandler> TextureHandler::textureInstance = nullptr;

vector<Texture*> TextureHandler::textures = vector<Texture*>();

TextureHandler::TextureHandler() {
    textures.reserve(20);
}

TextureHandler::~TextureHandler() {
    OnDestroy();
}

TextureHandler* TextureHandler::GetInstance() {
    if (textureInstance.get() == nullptr) textureInstance.reset(new TextureHandler);
    return textureInstance.get();
}

void TextureHandler::OnDestroy() {
    if (textures.size() > 0) {
        for (auto t : textures) {
            glDeleteTextures(sizeof(GLuint), &t->textureID);
            delete t;
            t = nullptr;
        }
        textures.clear();
    }
}

void TextureHandler::CreateTexture(const string& textureName_, const string& texturePath_) {
    Texture* t = new Texture();
    SDL_Surface* surface = nullptr;
    surface = IMG_Load(texturePath_.c_str());
    if (surface == nullptr) {
        Debug::Error("Surface for texture " + textureName_ + " failed to be created", "TextureHandler.cpp", __LINE__);
        delete t;
        t = nullptr;
        return;
    }

    //place textureID here
    glGenTextures(1, &t->textureID);

    //bind it to this specific texture
    glBindTexture(GL_TEXTURE_2D, t->textureID);

    //create our mode integer. 
    int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;

    /*1. specify texture target
    2. specify mipmap level
    3. specify format for texture storage
    4-5. width and height
    6. ALWAYS BE 0 -- this is the border (?) 
    7. specify format about image data
    8. specify data type
    9. image data in pixels*/
    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

    /*texture the x axis and repeat the texture image*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    /*texture the y axis and repeat the texture image*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /*scale down based on our mipmap settings*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    /*scale up based on texture filtering settings*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /*Mapmaps are a collection of images based on the texxture image where each image is half the size of the previous one.
    We are using mipmaps because it is a waste of memory to use a uber high res texture that is shwon very far away / a very small object*/
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    //set up texture struct width / height / name
    t->width = static_cast<float>(surface->w);
    t->height = static_cast<float>(surface->h);
    t->textureName = textureName_;

    //push back texture struct into the vector
    textures.push_back(t);

    SDL_FreeSurface(surface);
    surface = nullptr;
}

/*using vector so loop through entire vector
make our own check with the if statement
check to see if the elementes texture name is the same, if it is we return the texID of the specific element we are on
if we cant find the textureID we are looking for because ID is a GLuint*/
const GLuint TextureHandler::GetTexture(const string& textureName_) {
    for (auto t : textures) {
        if (t->textureName == textureName_) return t->textureID;
    }

    return 0;
}

/*using vector so loop through entire vector
make our own check with the if statement
check to see if the elementes texture name is the same, if it is we return the specific element we are on
return nullptr if we cant find the specific element*/
const Texture* TextureHandler::GetTextureData(const string textureName_) {
    for (auto t : textures) {
        if (t->textureName == textureName_) return t;
    }

    return nullptr;
}

Посмотреть разные туториалы
https://wiki.linsdl.org/SDL2/Tutorials

Досмотреть Lazy Foo'

Уменьшить Шлёпу
как решить 
(
Texture.cpp

Строка 70
Функция рендеринг

renderQuad - это куда будет помещаться текстура
усли вместо mWidth, mHeight задать свои переменные, то получится уменьшить Шлёпу

void LTexture::render( const int& x, const int& y, SDL_Renderer* renderer ) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy( renderer, mTexture, NULL, &renderQuad );
}

)

Не дать Шлёпе выйти за границы экрана

Ограничить FPS 30 или 60

Сделать класс Шлёпа/Герой Shlepa/Hero
Сделать класс Враг

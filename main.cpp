#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "stdio.h"
#include "string"
#include "vector"
#include "stdlib.h"
#include "iostream"
#include "time.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Window* gWindow = NULL;
Uint16 pixels[64*64] = {
	0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0aab, 0x0789, 0x0bcc, 0x0eee, 0x09aa, 0x099a, 0x0ddd,
    0x0fff, 0x0eee, 0x0899, 0x0fff, 0x0fff, 0x1fff, 0x0dde, 0x0dee,
    0x0fff, 0xabbc, 0xf779, 0x8cdd, 0x3fff, 0x9bbc, 0xaaab, 0x6fff,
    0x0fff, 0x3fff, 0xbaab, 0x0fff, 0x0fff, 0x6689, 0x6fff, 0x0dee,
    0xe678, 0xf134, 0x8abb, 0xf235, 0xf678, 0xf013, 0xf568, 0xf001,
    0xd889, 0x7abc, 0xf001, 0x0fff, 0x0fff, 0x0bcc, 0x9124, 0x5fff,
    0xf124, 0xf356, 0x3eee, 0x0fff, 0x7bbc, 0xf124, 0x0789, 0x2fff,
    0xf002, 0xd789, 0xf024, 0x0fff, 0x0fff, 0x0002, 0x0134, 0xd79a,
    0x1fff, 0xf023, 0xf000, 0xf124, 0xc99a, 0xf024, 0x0567, 0x0fff,
    0xf002, 0xe678, 0xf013, 0x0fff, 0x0ddd, 0x0fff, 0x0fff, 0xb689,
    0x8abb, 0x0fff, 0x0fff, 0xf001, 0xf235, 0xf013, 0x0fff, 0xd789,
    0xf002, 0x9899, 0xf001, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xe789,
    0xf023, 0xf000, 0xf001, 0xe456, 0x8bcc, 0xf013, 0xf002, 0xf012,
    0x1767, 0x5aaa, 0xf013, 0xf001, 0xf000, 0x0fff, 0x7fff, 0xf124,
    0x0fff, 0x089a, 0x0578, 0x0fff, 0x089a, 0x0013, 0x0245, 0x0eff,
    0x0223, 0x0dde, 0x0135, 0x0789, 0x0ddd, 0xbbbc, 0xf346, 0x0467,
    0x0fff, 0x4eee, 0x3ddd, 0x0edd, 0x0dee, 0x0fff, 0x0fff, 0x0dee,
    0x0def, 0x08ab, 0x0fff, 0x7fff, 0xfabc, 0xf356, 0x0457, 0x0467,
    0x0fff, 0x0bcd, 0x4bde, 0x9bcc, 0x8dee, 0x8eff, 0x8fff, 0x9fff,
    0xadee, 0xeccd, 0xf689, 0xc357, 0x2356, 0x0356, 0x0467, 0x0467,
    0x0fff, 0x0ccd, 0x0bdd, 0x0cdd, 0x0aaa, 0x2234, 0x4135, 0x4346,
    0x5356, 0x2246, 0x0346, 0x0356, 0x0467, 0x0356, 0x0467, 0x0467,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff
};
SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(pixels,16,16,16,16*2,0x0f00,0x00f0,0x000f,0xf000);
//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font* gFont = NULL;
TTF_Font* titleFont = NULL;

std::vector<std::vector<int>> bingoBoard(){
	std::vector<std::vector<int>> positionSequence(6,std::vector<int>(36,0));
	std::vector<int> pickedIndex(36,0);
	std::vector<int> oneTo36(36,0);
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 36; j++)
			oneTo36[j] = j;
		int size = 36;
		int index;
		for(int j = 0; j < 36; j++){
			do{
				index = rand() % 36;
			} while (pickedIndex[index] != 0);
			pickedIndex[index] = 1;
			positionSequence[i][j] = oneTo36[index];
		}
	}
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 36; j++)
			std::cout << positionSequence[i][j] << " ";
	}
	return positionSequence;
};

class LTexture
{
	public:
		//Initializes variables
		LTexture(){
            //Initialize
            mTexture = NULL;
            mWidth = 0;
            mHeight = 0;
        };

		//Deallocates memory
		~LTexture(){
            free();
        };

		//Loads image at specified path
		bool loadFromFile( std::string path ){
            free();

            SDL_Texture* newTexture = NULL;
            SDL_Surface* loadedSurface = IMG_Load(path.c_str());

            if( loadedSurface == NULL ){
		        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	        }else{
                //Color key image
                SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

                //Create texture from surface pixels
                newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
                if( newTexture == NULL ){
                    printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
                }else{
                    //Get image dimensions
                    mWidth = loadedSurface->w;
                    mHeight = loadedSurface->h;
                }

                //Get rid of old loaded surface
                SDL_FreeSurface( loadedSurface );
	        }

            //Return success
            mTexture = newTexture;
            return mTexture != NULL;
        };

        #if defined(SDL_TTF_MAJOR_VERSION)
        //Creates image from font string
        bool loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font* input_font = gFont){
            //Get rid of preexisting texture
            free();

            //Render text surface
            SDL_Surface* textSurface = TTF_RenderText_Solid( input_font, textureText.c_str(), textColor );
            if( textSurface != NULL )
            {
                //Create texture from surface pixels
                mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
                if( mTexture == NULL )
                {
                    printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
                }
                else
                {
                    //Get image dimensions
                    mWidth = textSurface->w;
                    mHeight = textSurface->h;
                }

                //Get rid of old surface
                SDL_FreeSurface( textSurface );
            }
            else
            {
                printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
            }


            //Return success
            return mTexture != NULL;
        };
        #endif

        //Deallocates texture
        void free(){
            if(mTexture != NULL){
                SDL_DestroyTexture(mTexture);
                mTexture = NULL;
                mWidth = 0;
                mHeight = 0;
            }
        };

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue ){
            SDL_SetTextureColorMod(mTexture, red, green, blue);
        };

        //Set blending
        void setBlendMode( SDL_BlendMode blending ){
            SDL_SetTextureBlendMode(mTexture, blending);
        };

        //Set alpha modulation
        void setAlpha( Uint8 alpha ){
            SDL_SetTextureAlphaMod(mTexture, alpha);
        };

        //Renders texture at given point
        void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE ){
            //Set rendering space and render to screen
            SDL_Rect renderQuad = { x, y, mWidth, mHeight };

            //Set clip rendering dimensions
            if( clip != NULL )
            {
                renderQuad.w = clip->w;
                renderQuad.h = clip->h;
            }

            //Render to screen
            SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
        };
		void scaledrender(int x, int y, double ratio){
			int scaledw = int(ratio * mWidth);
			int scaledh = int(ratio * mHeight);
			SDL_Rect rescaled = {x, y, scaledw, scaledh};
			SDL_RenderCopy(gRenderer,mTexture,NULL,&rescaled);
		}
        //Gets image dimensions
        int getWidth(){
            return mWidth;
        };

        int getHeight(){
            return mHeight;
        };

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//Scene textures
LTexture titleTexture;
LTexture gPromptTextTexture;
LTexture gInputTextTexture;
LTexture startbutton;
LTexture nextbutton;
LTexture cards[37];
//user info
class User{
    public:
        User(){};
        std::string get_username(){
            return user_name;
        };
        void set_username(std::string input_name){
            user_name = input_name;
        }
    private:
        std::string user_name;
};

//Starts up SDL and creates window
bool init(){
    //Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Mahjong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		SDL_SetWindowIcon(gWindow, surface);
		SDL_FreeSurface(surface);
		if( gWindow == NULL ){
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				 //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
};

//Loads login page
bool loginPage(){
    //Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont( "font/Caviar_Dreams_Bold.ttf", 28 );
    titleFont = TTF_OpenFont( "font/Caviar_Dreams_Bold.ttf", 40 );
	if( gFont == NULL ){
		printf( "Failed to load  gfont! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else{
		//Render the prompt
		SDL_Color textColor = { 0, 0, 0, 0xFF };
        if( !titleTexture.loadFromRenderedText( "MAJHONG", textColor , titleFont) )
		{
			printf( "Failed to render prompt text!\n" );
			success = false;
		}
		if( !gPromptTextTexture.loadFromRenderedText( "Enter User Name(English):", textColor ,gFont) )
		{
			printf( "Failed to render prompt text!\n" );
			success = false;
		}
	}

	return success;
};

//Frees media and shuts down SDL
void close(){
    //Free loaded images
	gPromptTextTexture.free();
	gInputTextTexture.free();

	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;
    TTF_CloseFont(titleFont);
    titleFont = NULL;
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
};

void loadcards(){
	cards[0].loadFromFile("majhongcard/tiao/onetiao.png");
	cards[1].loadFromFile("majhongcard/tiao/twotiao.png");
	cards[2].loadFromFile("majhongcard/tiao/threetiao.png");
	cards[3].loadFromFile("majhongcard/tiao/fourtiao.png");
	cards[4].loadFromFile("majhongcard/tiao/fivetiao.png");
	cards[5].loadFromFile("majhongcard/tiao/sixtiao.png");
	cards[6].loadFromFile("majhongcard/tiao/seventiao.png");
	cards[7].loadFromFile("majhongcard/tiao/eighttiao.png");
	cards[8].loadFromFile("majhongcard/tiao/ninetiao.png");
	cards[9].loadFromFile("majhongcard/tong/onetong.png");
	cards[10].loadFromFile("majhongcard/tong/twotong.png");
	cards[11].loadFromFile("majhongcard/tong/threetong.png");
	cards[12].loadFromFile("majhongcard/tong/fourtong.png");
	cards[13].loadFromFile("majhongcard/tong/fivetong.png");
	cards[14].loadFromFile("majhongcard/tong/sixtong.png");
	cards[15].loadFromFile("majhongcard/tong/seventong.png");
	cards[16].loadFromFile("majhongcard/tong/eighttong.png");
	cards[17].loadFromFile("majhongcard/tong/ninetong.png");
	cards[18].loadFromFile("majhongcard/wan/onewan.png");
	cards[19].loadFromFile("majhongcard/wan/twowan.png");
	cards[20].loadFromFile("majhongcard/wan/threewan.png");
	cards[21].loadFromFile("majhongcard/wan/fourwan.png");
	cards[22].loadFromFile("majhongcard/wan/fivewan.png");
	cards[23].loadFromFile("majhongcard/wan/sixwan.png");
	cards[24].loadFromFile("majhongcard/wan/sevenwan.png");
	cards[25].loadFromFile("majhongcard/wan/eightwan.png");
	cards[26].loadFromFile("majhongcard/wan/ninewan.png");
	cards[27].loadFromFile("majhongcard/word/dong.png");
	cards[28].loadFromFile("majhongcard/word/xi.png");
	cards[29].loadFromFile("majhongcard/word/nan.png");
	cards[30].loadFromFile("majhongcard/word/bei.png");
	cards[31].loadFromFile("majhongcard/word/zhong.png");
	cards[32].loadFromFile("majhongcard/word/fa.png");
	cards[33].loadFromFile("majhongcard/word/baiban.png");
	cards[34].loadFromFile("majhongcard/flower/flower_1.png");
	cards[35].loadFromFile("majhongcard/flower/flower_2.png");
	cards[36].loadFromFile("majhongcard/back.png");
	cards[37].loadFromFile("majhongcard/checked.png");
}
class selectcard// class contain selectcard's coord. and card type
{
	public:
	selectcard():card(36),x(-1),y(-1){}
	~selectcard(){}
	int getx(){return x;}
	int gety(){return y;}
	void setcoord(int cx, int cy){
		x = cx; y = cy;
	}
	int card;
	private:
	int x,y;
};
int bingo(std::vector<selectcard> card, std::vector<int> bingoboard){
	int count = 0;
	bool onboard[36] = {false};
	for (int i = 0; i < 15; i++){
		for (int j = 0; j < 36; j++){
			if (card[i].card == bingoboard[j]){
				onboard[j] = true;
			}
		}
	}
	for (int i = 0; i < 6; i++){
		if (onboard[i*6] && onboard[i*6+1] && onboard[i*6+2] && onboard[i*6+3] && onboard[i*6+4] && onboard[i*6+5]){
			std::cout << i << " row bingo" << std::endl;
			count++;
		}
		if (onboard[i] && onboard[6+i] && onboard[6*2+i] && onboard[6*3+i] && onboard[6*4+i] && onboard[6*5+i]){
			std::cout << i << " col bingo" << std::endl;
			count++;
		}
	}
	if (onboard[0] && onboard[7] && onboard[14] && onboard[21] && onboard[28] && onboard[35]){
		std::cout << "\\ bingo" << std::endl;
		count++;
	}
	if (onboard[5] && onboard[10] && onboard[15] && onboard[20] && onboard[25] && onboard[30]){
		std::cout << "/ bingo" << std::endl;
		count++;
	}

	std::cout << "bingo: " << count << std::endl;
	return count;
}
int main( int argc, char* args[] )
{
	int page = 0;
	SDL_Rect bstart,bnext;
	SDL_Rect bingooutline[6];
	srand(time(NULL));
	std::vector<std::vector<int>> positionSequence(6,std::vector<int>(36,0));
	std::vector<int> oneTo36(36,0);
	std::vector<selectcard> cardlist(15);//fake select
	for(int i = 0; i < 36; i++)
		oneTo36[i] = i;
	int index;
    for(int i = 0; i < 6; i++){
        std::vector<int> pickedIndex(36,0);
        for(int j = 0; j < 36; j++){
            do{index = rand() % 36;}
            while (pickedIndex[index] != 0);
            pickedIndex[index] = 1;
            positionSequence[i][j] = oneTo36[index];
			std::cout << positionSequence[i][j] << " ";
	    }std::cout << std::endl;
	}
	for (int i = 35; i > 0; i--){// random selectcard
		index = rand() % 36;
		std::swap(oneTo36[i],oneTo36[index]);
	}
	std::cout << "Selected cards: \n";
	for (int i = 0; i < 15; i++){
		cardlist[i].card = oneTo36[i];
		std::cout << cardlist[i].card << " ";
	}
	std::cout << std::endl;

	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
        //create user object
        User player;
		//Load media
		loadcards();
		if( !loginPage() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;
			int boardselected = -1;
			int cardselected = -1;
			int bingolines = -1;
			// mouse position
			int mx, my;

			//Event handler
			SDL_Event e;

			//Set text color as black
			SDL_Color textColor = { 0, 0, 0, 0xFF };

			//The current input text.
			std::string inputText = "";
			gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor ,gFont);
			//Enable text input
			SDL_StartTextInput();
			//While application is running
			while( !quit )
			{
				//The rerender text flag
				bool renderText = false;

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					if (e.type == SDL_MOUSEMOTION){
						SDL_GetMouseState(&mx, &my);
					}
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						if (e.button.button == SDL_BUTTON_LEFT){// left click
							if (mx >= bstart.x && mx <= bstart.x+bstart.w
							 && my >= bstart.y && my <= bstart.y+bstart.h){
								page = 1;// change this!!!!
							}
							else{
								for (int i = 0; i < 6; i++){// select bingo board
									if (mx >= bingooutline[i].x && mx <= bingooutline[i].x+bingooutline[i].w && page == 1
									&& my >= bingooutline[i].y && my <= bingooutline[i].y+bingooutline[i].h){
										boardselected = i;
										std::cout << "Selected bingo board: " << boardselected << std::endl;
									}
								}
							}
							if (mx >= bnext.x && mx <= bnext.x+bnext.w
							 && my >= bnext.y && my <= bnext.y+bnext.h){// next button work iff
								if (boardselected != -1 && page == 1)// bingo board selected
									page = 2;
								if (cardselected == 14 && page == 2)// selected 15 cards
									page = 3;
								if (bingolines != -1 && page == 3)
									quit = true;
							}
							for (int i = 0; i < 6; i++){
								for (int j = 0; j < 6; j++){
									if (mx >= SCREEN_WIDTH/2+80*(i-3) && mx <= SCREEN_WIDTH/2+80*(i-3)+cards[36].getWidth()/2 && page == 2
									 && my >= 50+titleTexture.getHeight()+100*j && my <= 50+titleTexture.getHeight()+100*j+cards[36].getHeight()/2){
										bool repeat = false;
										for (int k = 0; k <= cardselected+1; k++){// detect repeat coord.
											if (cardlist[k].getx() == i && cardlist[k].gety() == j){
												repeat = true;
												break;
											}
										}
										if (!repeat && cardselected < 14){
											cardselected++;
											cardlist[cardselected].setcoord(i,j);
											std::cout << cardselected+1 << " " << i << " " << j << std::endl;
										}
									}
								}
							}
						}
					}
					//Special key input
					else if( e.type == SDL_KEYDOWN )
					{
						//Handle backspace
						if( e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
						{
							//lop off character
							inputText.pop_back();
							renderText = true;
						}
						//Handle copy
						else if( e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
						{
							SDL_SetClipboardText( inputText.c_str() );
						}
						//Handle paste
						else if( e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
						{
							inputText = SDL_GetClipboardText();
							renderText = true;
						}
					}
					//Special text input event
					else if( e.type == SDL_TEXTINPUT )
					{
						//Not copy or pasting
						if( !( SDL_GetModState() & KMOD_CTRL && ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' || e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) ) )
						{
							//Append character
							inputText += e.text.text;
							renderText = true;
						}
					}
				}

				//Rerender text if needed
				if( renderText )
				{
					//Text is not empty
					if( inputText != "" )
					{
						//Render new text
						gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor ,gFont);
					}
					//Text is empty
					else
					{
						//Render space texture
						gInputTextTexture.loadFromRenderedText( " ", textColor ,gFont);
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				switch (page){
					case 0://page 1
						//Render text textures
						titleTexture.render(( SCREEN_WIDTH - titleTexture.getWidth() ) / 2, 0);
						gPromptTextTexture.render( ( SCREEN_WIDTH - gPromptTextTexture.getWidth() ) / 2, titleTexture.getHeight() );
						gInputTextTexture.render( ( SCREEN_WIDTH - gInputTextTexture.getWidth() ) / 2, titleTexture.getHeight()+gPromptTextTexture.getHeight() );
						{// button
						bstart = {SCREEN_WIDTH*8/10, SCREEN_HEIGHT*8/10,150,50};
						// fill
						SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
						SDL_RenderFillRect( gRenderer, &bstart );
						// outline
						SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
						SDL_RenderDrawRect( gRenderer, &bstart );

						if (!startbutton.loadFromRenderedText( "Start", textColor, gFont)){// if text successfully loaded
							SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0x00 );
							SDL_RenderFillRect( gRenderer, NULL );
						}
						startbutton.render(bstart.x+(bstart.w-startbutton.getWidth())/2, bstart.y+(bstart.h-startbutton.getHeight())/2);
						}
						break;
					case 1://page 2
						titleTexture.loadFromRenderedText( "Choose Your Bingo Board", textColor ,gFont);
						titleTexture.render(( SCREEN_WIDTH - titleTexture.getWidth() ) / 2, 0);
						for (int i = 0; i < 6; i++){
							if (i <= 2) { bingooutline[i]= {(SCREEN_WIDTH-200)/3*(i%3)+20, titleTexture.getHeight()+30, 300, 300};}
							else bingooutline[i] = {(SCREEN_WIDTH-200)/3*(i%3)+20, 350+titleTexture.getHeight(), 300, 300};
							if (boardselected == i){// selected board change outline color
								SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0x00 );
							}
							else
								SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
							SDL_RenderDrawRect( gRenderer, &bingooutline[i]);
							for (int j = 0; j < 36; j++){
								cards[positionSequence[i][j]].scaledrender(bingooutline[i].x+bingooutline[i].w/2+40*(j%6-3),bingooutline[i].y+bingooutline[i].h/2+45*(j/6-3),0.25);
							}
							if (boardselected != -1){// if selected show next button
								bnext = {SCREEN_WIDTH*85/100, SCREEN_HEIGHT*8/10, 150, 50};
								SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
								SDL_RenderDrawRect( gRenderer, &bnext);
								if (!nextbutton.loadFromRenderedText( "Next", textColor, gFont)){// if text successfully loaded
									SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0x00 );
									SDL_RenderFillRect( gRenderer, NULL );
								}
								nextbutton.render(bnext.x+(bnext.w-nextbutton.getWidth())/2, bnext.y+(bnext.h-nextbutton.getHeight())/2);
							}
						}
						break;
					case 2:
						titleTexture.loadFromRenderedText( "Choose 15 Cards!", textColor ,gFont);
						titleTexture.render(( SCREEN_WIDTH - titleTexture.getWidth() ) / 2, 0);
						for (int i = 0; i < 6; i++){// render 6x6 back cards
							for (int j = 0; j < 6; j++){
								cards[36].scaledrender(SCREEN_WIDTH/2+80*(i-3),50+titleTexture.getHeight()+100*j, 0.5);
							}
						}
						for (int i = 0; i <= cardselected; i++){// show selected card
							cards[cardlist[i].card].scaledrender(SCREEN_WIDTH/2+80*(cardlist[i].getx()-3),50+titleTexture.getHeight()+100*cardlist[i].gety(), 0.5);
						}
						if (cardselected == 14){// 15(0~14) cards selected show next button
							bnext = {SCREEN_WIDTH*85/100, SCREEN_HEIGHT*8/10, 150, 50};
							SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );SDL_RenderDrawRect( gRenderer, &bnext);
							if (!nextbutton.loadFromRenderedText( "Next", textColor, gFont)){// if text successfully loaded
								SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0x00 );
								SDL_RenderFillRect( gRenderer, NULL );
							}
							nextbutton.render(bnext.x+(bnext.w-nextbutton.getWidth())/2, bnext.y+(bnext.h-nextbutton.getHeight())/2);
							SDL_RenderDrawRect( gRenderer, &bnext);
							if (!nextbutton.loadFromRenderedText( "Next", textColor, gFont)){// if text successfully loaded
								SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0x00 );
								SDL_RenderFillRect( gRenderer, NULL );
							}
							nextbutton.render(bnext.x+(bnext.w-nextbutton.getWidth())/2, bnext.y+(bnext.h-nextbutton.getHeight())/2);
						}
						break;
					case 3:
						if (bingolines == -1){
							bingolines = bingo(cardlist,positionSequence[boardselected]);
						}
						titleTexture.loadFromRenderedText("Bingo Time!", textColor ,gFont);
						titleTexture.render(( SCREEN_WIDTH - titleTexture.getWidth() ) / 2, 0);
						std::string resulttext = "Result: " + std::to_string(bingolines) +  " line(s)";
						gPromptTextTexture.loadFromRenderedText(resulttext, textColor ,gFont);
						gPromptTextTexture.render( ( SCREEN_WIDTH - gPromptTextTexture.getWidth() ) / 2, SCREEN_HEIGHT - gPromptTextTexture.getHeight()*1.5 );
						for (int i = 0; i < 6; i++){// render 6x6 back cards
							for (int j = 0; j < 6; j++){
								cards[positionSequence[boardselected][i*6+j]].scaledrender(SCREEN_WIDTH/2+80*(i-3)+2.5,50+titleTexture.getHeight()+95*j+2.5, 0.5);
								for (int k = 0; k < 15; k++){
									if (cardlist[k].card == positionSequence[boardselected][i*6+j]){
										SDL_Rect bingorect = {SCREEN_WIDTH/2+80*(i-3),50+titleTexture.getHeight()+95*j,cards[0].getWidth()/2+5,cards[0].getHeight()/2+5};
										SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0x00 );
										SDL_RenderDrawRect( gRenderer, &bingorect);
										cards[37].scaledrender(SCREEN_WIDTH/2+80*(i-3),50+titleTexture.getHeight()+95*j, 0.05);
									}
								}
							}
						}
						bnext = {SCREEN_WIDTH*85/100, SCREEN_HEIGHT*8/10, 150, 50};// actually exit button
						SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
						SDL_RenderDrawRect( gRenderer, &bnext);
							if (!nextbutton.loadFromRenderedText( "Exit", textColor, gFont)){// if text successfully loaded
								SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0x00 );
								SDL_RenderFillRect( gRenderer, NULL );
							}
						nextbutton.render(bnext.x+(bnext.w-nextbutton.getWidth())/2, bnext.y+(bnext.h-nextbutton.getHeight())/2);
						break;
				}
				//Update screen
				SDL_RenderPresent( gRenderer );
			}

			//Disable text input
			SDL_StopTextInput();
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

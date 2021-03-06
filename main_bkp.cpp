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
LTexture testcard;
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

int main( int argc, char* args[] )
{
	int page = 0;
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
		testcard.loadFromFile("majhongcard/tiao/onetiao.png");
		if( !loginPage() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			// mouse position
			int mx, my;

			//Event handler
			SDL_Event e;

			//Set text color as black
			SDL_Color textColor = { 0, 0, 0, 0xFF };

			//The current input text.
			std::string inputText = "Some text";
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
							if (mx >= SCREEN_WIDTH*65/100 && mx <= SCREEN_WIDTH*65/100+150 
							 && my >= SCREEN_HEIGHT*7/10 && my <= SCREEN_HEIGHT*7/10+50){
								page = 1;// change this!!!!
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
					case 0:
						//Render text textures
						titleTexture.render(( SCREEN_WIDTH - titleTexture.getWidth() ) / 2, 0);
						gPromptTextTexture.render( ( SCREEN_WIDTH - gPromptTextTexture.getWidth() ) / 2, titleTexture.getHeight() );
						gInputTextTexture.render( ( SCREEN_WIDTH - gInputTextTexture.getWidth() ) / 2, titleTexture.getHeight()+gPromptTextTexture.getHeight() );
						{// button
						SDL_Rect bstart = {SCREEN_WIDTH*65/100, SCREEN_HEIGHT*7/10,150,50};
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
						startbutton.render(SCREEN_WIDTH*65/100+(150-startbutton.getWidth())/2, SCREEN_HEIGHT*7/10+(50-startbutton.getHeight())/2);
						}
						break;
					case 1:
						for (int i = 0; i < 6; i++){
							for (int j = 0; j < 6; j++){
								testcard.scaledrender(SCREEN_WIDTH/2+(i-3)*30,j*40,0.25);
							}
						}
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

#include <SDL/SDL.h>
#include "sal.h"
 
int main(){

	//Init SDL.
	if (SDL_Init(SDL_INIT_AUDIO) < 0)return 1;
	
	//Init audiolayer
	initAudio();
	
	//Loading audio file
	sound mus = loadWav("yourmus.wav");
	
	/* Start playing */	
	playSound(mus, SDL_MIX_MAXVOLUME);
	
	//Keep Playing !
	while(mus->currlength > 0);

	//Close audio file, Quit audiolayer and SDL
	closeWav(mus);
	quitAudio();
	SDL_Quit();
}

#define MAX_PLAYING_SOUND 10 //decided arbitrarily

struct sound_data
{
	Uint32 length; // length of our sample
	Uint8* buffer; // audio buffer
	SDL_AudioSpec spec;//try to guess :)
	Uint8 *currpos; // pointer to audio buffer to played
	Uint32 currlength; // remaining length of the sample we have to play
	Uint8 state; // 0:stop /  1: play / 2: pause
	int volume;
};

struct audiop
{
	struct sound_data* s[MAX_PLAYING_SOUND];
	SDL_AudioSpec spec;
};

typedef struct sound_data* sound;
typedef struct audiop audiop;

void audioMix(void *userdata, Uint8 *stream, int len);
void initAudio();
sound loadWav(char *filename);
void playSound(sound s, int volume);
void pauseSound(sound s);
void pauseAllSound();
void stopSound(sound s);
void stopAllSound();
void closeWav(sound s);
void quitAudio();

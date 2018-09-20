#include <SDL/SDL_audio.h>
#include "sal.h"

audiop mplayer;

void audioMix(void *userdata, Uint8 *stream, int len)
{
	
	int i;
	for(i = 0;i<MAX_PLAYING_SOUND; i++)
	{
		if(mplayer.s[i] != NULL && mplayer.s[i]->state == 1)
		{
			len = ( len > mplayer.s[i]->currlength ? mplayer.s[i]->currlength : len );
	
			SDL_MixAudio(stream, mplayer.s[i]->currpos, len, mplayer.s[i]->volume);
	
			mplayer.s[i]->currpos += len;
			mplayer.s[i]->currlength -= len;
		}
	}	
}

void initAudio()
{
	mplayer.spec.freq = 44000;
    mplayer.spec.format = AUDIO_S16SYS;
    mplayer.spec.channels = 2;    /* 1 = mono, 2 = stereo */
    mplayer.spec.samples = 1024;  /* Good low-latency value for callback */
    mplayer.spec.callback = audioMix;
    mplayer.spec.userdata = NULL;
	
	int i;
	for(i=0;i<MAX_PLAYING_SOUND;i++)
	{
		mplayer.s[i] = NULL;
	}

	if ( SDL_OpenAudio(&mplayer.spec, NULL) < 0 ){
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		exit(-1);
	}
	SDL_PauseAudio(0);
}

sound loadWav(char *filename)
{
	sound s = (sound)malloc(sizeof(struct sound_data));
	if( SDL_LoadWAV(filename, &s->spec, &s->buffer, &s->length) != NULL ){
		s->currlength = s->length;
		s->currpos = s->buffer;
		s->state = 0;
		s->volume = 0;
	}
	return s;
}

void playSound(sound s, int volume)
{
	int i = 0;
	int find = 0;
	
	if(s->state != 1)
	{
		while(!find && i<MAX_PLAYING_SOUND)//find a available place in the playing sound array "s"
		{	
			if(mplayer.s[i] == NULL || mplayer.s[i] != 1)
			{
				mplayer.s[i] = s;
				s->state = 1;
				find = 1;
			}
			i++;
		}
	}
	s->volume = volume;
}

void pauseSound(sound s)
{
	s->state = 2;
}

void pauseAllSound()
{
	int i;
	for(i = 0;i < MAX_PLAYING_SOUND; i++)
	{
		if(mplayer.s[i] != NULL)
			pauseSound(mplayer.s[i]);
	}
}

void stopSound(sound s)
{
	s->state = 0;
	s->currpos = s->buffer;
	s->currlength = s->length;
}

void stopAllSound()
{
	int i;
	for(i = 0;i < MAX_PLAYING_SOUND; i++)
	{
		if(mplayer.s[i] != NULL)
			stopSound(mplayer.s[i]);
	}
}

void closeWav(sound s)
{
	SDL_FreeWAV(s->buffer);
	free(s);
}

void quitAudio()
{
	SDL_PauseAudio(1);
	SDL_CloseAudio();
	int i;
	for(i=0;i<MAX_PLAYING_SOUND;i++)
	{
		mplayer.s[i] = NULL;
	}
}

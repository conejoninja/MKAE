
#include "includes.h"

#ifndef SOUND_H_
#define SOUND_H_


class Sound {
           
	private:
		static char filename[MAXPATHLEN];
		static FILE* pFile;
		static long lSize;
		static char * buffer;
		static size_t result;
		static char *file;
		static MODPlay mod;
		static u32 fadeCounter;
		static bool fadeFinished;
		static float fadeStep;
		static float fadeTime;
		static float realVolume;
		static u8 oggVolume;
		

                                   
	public:


		static lwp_t thread;


		Sound();
		static void initSound();
		static void play();
		static void loadFile2(const char *file);
		static void loadFile(void *arg);
		static void stopAllSounds();
		static void setVolume(u8 volume); 
		static void volumeUp(); 
		static void volumeDown(); 
		static void fadeIn(u32 milisec); 
		static void fadeOut(u32 milisec); 
		static bool isFading();
		static void frame(); 
		static u8 getVolume();
		static void pause();
		static void resume();
		static void setTimeOgg(s32 time_pos);
		static void fwd(u32 milisecs);	
		static void rwd(u32 milisecs);		



		~Sound();
		 
};


#endif /*SOUND_H_*/

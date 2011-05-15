#include "includes.h"
#include "Sound.h"

//#include "no_secret_part_mod.h"


#define MAX_VOLUME		255


char Sound::filename[MAXPATHLEN];
FILE* Sound::pFile;
long Sound::lSize;
char * Sound::buffer;
size_t Sound::result;
char *Sound::file = "";
u8 Sound::oggVolume = 127;
MODPlay Sound::mod;
bool Sound::fadeFinished = true;
u32 Sound::fadeCounter = 0; 
float Sound::fadeStep = 1;
float Sound::fadeTime = 0;
float Sound::realVolume = 0;






lwp_t Sound::thread = (lwp_t)NULL;

Sound::Sound() {

};	



void Sound::initSound() {
	//fatInitDefault();
	//MP3Player_Init();
	//MODPlay_Init (&Sound::mod);
	
	fatInit(8, false);
	SND_Init(INIT_RATE_48000);
    SND_Pause(0);
	
	
};


void Sound::loadFile2(const char *file) {
	
	char path[100] = "fat0:/MKAE/";
	strcat(path,file);
	Game::characters[Game::giliID].say("Loading...");
	int fd = open(path,O_RDONLY, 0);
	if(fd>=0) {
		Game::characters[Game::giliID].say("All is OK!");
		PlayOgg(fd,0,OGG_ONE_TIME);
	};
		
	/*char path[100] = "fat0:/mp3/";
		strcat(path,file);
		
		Sound::pFile = fopen (path, "r");
		 
		fseek (Sound::pFile , 0 , SEEK_END);
		Sound::lSize = ftell (Sound::pFile);
		rewind (Sound::pFile);


		Game::characters[Game::giliID].say("Loading...");
		

		Sound::buffer = (char*) malloc (sizeof(char)*Sound::lSize);
		if (Sound::buffer == NULL) {fputs ("   Memory error",stderr); exit (2);}
		Sound::result = fread (Sound::buffer,1,Sound::lSize,Sound::pFile);
		if (Sound::result != Sound::lSize) {fputs ("   Reading error",stderr); exit (3);}

		fclose (Sound::pFile); 

		Game::characters[Game::giliID].say("LOADED!");*/
		
};

void Sound::loadFile(void *arg) {
	
		/*file = (char *)arg;//"bso.mp3";
		
		char path[100] = "fat0:/mp3/";
		strcat(path,file);
		
		Sound::pFile = fopen (path, "r");
		 
		fseek (Sound::pFile , 0 , SEEK_END);
		Sound::lSize = ftell (Sound::pFile);
		rewind (Sound::pFile);


		Game::characters[Game::giliID].say("Loading...");
		

		Sound::buffer = (char*) malloc (sizeof(char)*Sound::lSize);
		if (Sound::buffer == NULL) {fputs ("   Memory error",stderr); exit (2);}
		Sound::result = fread (Sound::buffer,1,Sound::lSize,Sound::pFile);
		if (Sound::result != Sound::lSize) {fputs ("   Reading error",stderr); exit (3);}

		fclose (Sound::pFile); 

		Game::characters[Game::giliID].say("LOADED!");*/
		
		
		
		
};


void Sound::play() {
	//MP3Player_PlayBuffer(Sound::buffer,Sound::lSize, NULL);

    Game::characters[Game::giliID].say("Playing...");
    
    // while (MP3Player_IsPlaying ());
    
	//MODPlay_SetMOD (&Sound::mod, bso_fondo_mod);//no_secret_part_mod);
	//MODPlay_Start (&Sound::mod);
    
    
	
};


void Sound::stopAllSounds() {
	StopOgg();
	//MP3Player_Stop();
	//free (Sound::buffer);
	//MODPlay_Stop(&Sound::mod);
};


void Sound::setVolume(u8 volume) {
	
	/*if(volume==255) {
		volume = 0;
	};
	
	if(volume>65) {
		volume = 65;
	};
	
	Sound::mod.mod.musicvolume = volume;*/
	Sound::oggVolume = volume;
	SetVolumeOgg(Sound::oggVolume);
	
};

void Sound::volumeUp() {
	
	//Sound::setVolume(++Sound::mod.mod.musicvolume);
	if(Sound::oggVolume<255) {
		Sound::oggVolume++;
	};
	Sound::setVolume(Sound::oggVolume);
	
};

void Sound::volumeDown() {
	
	//Sound::setVolume(--Sound::mod.mod.musicvolume);
	if(Sound::oggVolume>0) {
		Sound::oggVolume--;
	};
	Sound::setVolume(Sound::oggVolume);
	
};

u8 Sound::getVolume() {
	
	//return Sound::mod.mod.musicvolume;
	return Sound::oggVolume;
	
};


void Sound::fadeIn(u32 milisec) {
	
	Sound::fadeCounter = 0;
	Sound::fadeTime = 6*milisec/100;
	Sound::realVolume = Sound::getVolume();//Sound::mod.mod.musicvolume;
	Sound::fadeStep = (MAX_VOLUME-Sound::getVolume())/Sound::fadeTime;
	
};


void Sound::fadeOut(u32 milisec) {
	
	Sound::fadeCounter = 0;
	Sound::fadeTime = 6*milisec/100;
	Sound::realVolume = Sound::getVolume();
	Sound::fadeStep = -Sound::getVolume()/Sound::fadeTime;
	
};


void Sound::frame() {

	if(Sound::fadeCounter<Sound::fadeTime) {
		Sound::fadeCounter++;	
		Sound::realVolume += Sound::fadeStep;
		if(Sound::realVolume<0) {
			Sound::realVolume = 0;
		};
			
		if(Sound::realVolume>MAX_VOLUME) {
			Sound::realVolume = MAX_VOLUME;
		};
		Sound::setVolume((u8)(Sound::realVolume));
		
	};
	
	int st = StatusOgg();

	if(st==OGG_STATUS_ERR || st==OGG_STATUS_EOF) {
		int fd = open("fat0:/MKAE/bso.ogg",O_RDONLY, 0);
		if(fd>=0) {
			PlayOgg(fd,0,OGG_ONE_TIME);
		};
	};	 
	
	
};


bool Sound::isFading() {
	return !fadeFinished;
};





void Sound::pause() {
	PauseOgg(1);
};

void Sound::resume() {
	PauseOgg(1);
};

void Sound::setTimeOgg(s32 time_pos) {
	SetTimeOgg(time_pos);
};

void Sound::fwd(u32 milisecs) {
	SetTimeOgg(GetTimeOgg()+milisecs);
};

void Sound::rwd(u32 milisecs) {
	SetTimeOgg(GetTimeOgg()-milisecs);
};


Sound::~Sound() {
	//printf("Ya no hay Scroll");
};


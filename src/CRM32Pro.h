// --------------------------------------------------------------------------- 
//   						   CRM32Pro Library 
//  				      MegaStorm Systems (c) 2007
//							Roberto Prieto Prieto 
// ---------------------------------------------------------------------------
#ifndef CRM32Pro_H
#define CRM32Pro_H
 
// ------------------------------INCLUDES-------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SDL/SDL.h"  
#include "SDL/SDL_thread.h"

// ----------------------------MAGIC LIBRARY STUFF----------------------------
#define RecoverSurf         // By default, auto recover surfaces support is enabled.
#if defined(_WINDOWS) || defined(WIN32) || defined(WIN64) // Is a Windows platform?
    #ifdef WIN64
      #undef RecoverSurf    // In Windows64, auto recover support is not needed.
    #endif
    #ifndef _WINDOWS
      #define _WINDOWS
    #endif
    #ifdef _WINDLL 
	  #define DllHandle __declspec(dllexport)    
	  #define DllExport __declspec(dllexport)
    #endif
    #ifndef _WINDLL
	  #define DllExport
	  #define DllHandle                          // Support static library.
      #ifndef CRM32PRO_STATIC 
        #undef DllHandle
        #define DllHandle __declspec(dllimport)  // Support shared library.
      #endif
    #endif	
#elif defined(__unix__) || defined(__UNIX__)     
    #define _LINUX                               // Otherwise, is a linux platform?
    #define DllHandle   
    #define DllExport  
    #undef RecoverSurf                           // In Linux, auto recover support is not needed.
#else                                            // Platform unknown, provocate compiling error.
    #error PLATFORM UNKNOWN - OVERRIDE THIS LINE TO FORCE COMPILING
#endif
  
// ---------------------------------------------------------------------------
/** @defgroup MODULE1 MODULE 1: CRM32Pro main and generic functions (v2.2). 
 \image html logotipo.png 
 * <br>This module contains main and generic functions:<br>
 * Init() and Quit(): these are the main functions of the library. They replace to SDL_Init() and SDL_Quit. <br>
 * SetVideoMode() uses Config struct to setup a video mode, it replaces SDL_SetVideoMode(). <br>
 * Update() is the main way to update all systems: graphics,events,timing,etc.It also replace SDL_Flip().<br>
 * XML parser, CRC32 functions, true random number generation and get useful information. <br>
 * Note that you always have to call to CRM32Pro.Init() to initialize the library and CRM32Pro.Quit() to close it. <br>
 * - Created on 10 June 2001
 * - Last modified on 19 November 2007*/
// ---------------------------------------------------------------------------
//! @{  

// -Video backend-
#define RENDER_DEFAULT 1 //!< Used with Config.VideoRender to use default backend. Default setting.
#define RENDER_WINDIB  2 //!< Used with Config.VideoRenderer to use Windib backend. Only for Win32/Win64.
#define RENDER_DIRECTX 4 //!< Used with Config.VideoRenderer to use DirectX backend. Only for Win32.
#define RENDER_X11     8 //!< Used with Config.VideoRenderer to use X11 backend. Only for Linux.
#define RENDER_FBCON  16 //!< Used with Config.VideoRenderer to use Frame Buffer Console backend. Only for Linux.
#define RENDER_DGA    32 //!< Used with Config.VideoRenderer to use DGA backend. Only for Linux.
#define RENDER_OPENGL 64 //!< Used with Config.VideoRenderer to use glSDL backend(OpenGL on 2D mode). For Win32/Win64 and Linux.

// -Video acceleration mode-
#define ACCEL_SOFTWARE    1 //!< Used with Config.VideoAccel to set software mode with optimizations.
#define ACCEL_HARDSMOOTH  2 //!< Used with Config.VideoAccel to set hardware mode with smooth system (double-buffer and waiting vsync).
#define ACCEL_HARDSPEED   3 //!< Used with Config.VideoAccel to set hardware mode at full speed (single-buffer without waiting vsync).

// -Customs events-
#define EVENT_LOGICWAIT 30  //!< Event type returned by CRM32Pro.Update() while it is waiting to fulfill the Logic Rate.

// -Detect mouse buttons-
#define CRM32PRO_BUTTON_LEFT    1 //!< Used with CRM32Pro.mouse_buttons or CRM32Pro.mouse_prevbuttons. It informs of a left button click.
#define CRM32PRO_BUTTON_MIDDLE  2 //!< Used with CRM32Pro.mouse_buttons or CRM32Pro.mouse_prevbuttons. It informs of a middle button click.
#define CRM32PRO_BUTTON_RIGHT   4 //!< Used with CRM32Pro.mouse_buttons or CRM32Pro.mouse_prevbuttons. It informs of a right button click.

//! CRM32Pro
/*! Main library interface.*/ 
class DllExport CRM32Pro_Main 
{
    public:
		// -Constructor-
		CRM32Pro_Main();
		// -Destructor-
		~CRM32Pro_Main();
		// -Init system-	
		int Init(unsigned int flags);  
		// -Quit system-		
		void Quit(void);      
		// -Update sytem-
		int Update(SDL_Event *ev=NULL);
		// -Clean up update system-
		void CleanUp(void);
		// -Set a video mode-
		int SetVideoMode(void);
		// -Blit a surface-
		int Blit(SDL_Surface *src, SDL_Rect *srcrect,SDL_Surface *dst, SDL_Rect *dstrect);
		// -Free a surface (using safe mode)-
		void FreeSurface(SDL_Surface *&);
		// -Set a callback function to blit your graphics at Rendering Frame Rate-
		void SetRenderCallback(void (*myRenderFunc)(int bLogicUpdate));
		// -Get current logic time-
		float GetLogicTime();
		// -Get keystate-
		int GetKeystate(int keysym);		

		// -Print version,copyright and compiled date and get string-
		void PrintVersion();       
		char *GetVersion();        
		char *GetCopyright();      
        // -Print useful information- 
		void VideoInfo(); 
		void AudioInfo();
	    void SurfaceInfo(SDL_Surface *surface);

		// -CRC32-
		unsigned int CRC32(char *buffer, int Size); 
		unsigned int CRC32(char *filename);

		// -True random number generator-
		void RandSeed(unsigned int seed); // Random seed
		Uint32 Rand();              // Random number on [0,0xffffffff] interval 
		double RandReal();          // Random number on [0,1] interval

		// -Misc stuff-
		int MakeDirectory(char *fullpath); // Create a directory. Supports more than one subdirectory.

		// -XML parser system-		
		int XMLCreate(char *mainnode);
		int XMLOpen(char *filename);
		int XMLOpen(char *fileDPF,char *blockname);
		int XMLOpen(int idDPF,char *blockname);
		int XMLSave(int id, char *filename);
		int XMLSave(int id, char *fileDPF, char *blockname);
		int XMLSave(int id, int idDPF, char *blockname);
		void XMLClose(int id);

		int XMLNodePointTo(int id,int nparam,char *, ...);
		int XMLNodeFirst(int id);
		int XMLNodeNext(int id);
		int XMLNodeParent(int id);
		int XMLNodeChild(int id);
		int XMLNodeRemove(int id);
		int XMLNodeCreate(int id, char *name);
		int XMLNodeRename(int id, char *name);
		char *XMLNodeGetName(int id);
		
		int XMLAttributeSet(int id,char *name,char *value);
		int XMLAttributeSet(int id,char *name,int value);
		int XMLAttributeSet(int id,char *name,double value);
		int XMLAttributeGet(int id,char *name, char **value);
		int XMLAttributeGet(int id,char *name, int *value);
		int XMLAttributeGet(int id,char *name, double *value);
		int XMLAttributeRemove(int id, char *name);

		char *XMLTextGet(int id);
		int XMLTextSet(int id, char *value);
		int XMLTextRemove(int id);

		char *XMLCommentGet(int id);
		int XMLCommentSet(int id, char *value);
		int XMLCommentRemove(int id);
		
		//! Main config struct.<br>You can manually fill it or using CRM32Pro.LoadConfig() loading an external XML.
		struct sConfig
		{
			// 1.General section
			char *Title;         //!< Title or name of your application. It is usually used as window title. By default is "CRM32Pro SDK Application"
			SDL_Surface *Icon;   //!< Pointer to surface to assign it as icon. By default is NULL.
			char bMTFriendly;    //!< MultiTasking Friendly flag.When it is enabled, it will give execution flow to OS scheduler for at less the given ms each Render Frame. By default is disabled.

			// 2.Video section
			Uint8 VideoRenderer; //!< See definition of RENDER_xx. By default is RENDER_DEFAULT.			
			Uint8 VideoAccel;    //!< See definition of ACCEL_xx. By default is ACCEL_SOFTWARE.
			Uint8 VideoWindow;   //!< 0 to force fullscreen or 1 to select window mode. By default is 1.
			Uint8 VideoBPP;      //!< Bits Per Pixel, you can choose 8,16 or 32. By default is 0 to auto-choose the best setting.
			Uint16 VideoWidth;   //!< Video screen width. By default is 640.
			Uint16 VideoHeight;  //!< Video screen height. By default is 480.

			// 3.Audio section
			Uint8 AudioEnable;   //!< 0 to disable or 1 to enable sound system. By default is 0.
			int   AudioFormat;   //!< AUDIO_S8 to 8bits or AUDIO_S16 to 16bits sound resolution. By default is AUDIO_S8.
			int   AudioFreq;     //!< Frequency in Hz (11025,22050,44100). By default is 11025.
			int   AudioMode;     //!< 1 for mono, 2 for stereo, 4 for surround and 6 for surround with center and lfe.
			int   AudioBuffer;   //!< Mixing buffer size. By default and a common and good value is 4096.
			Uint8 AudioMusicVol; //!< Music volume. By default is 128.
			Uint8 AudioSoundVol; //!< Sound volume. By default is 128.
		} Config; 
		int LoadConfig(char *fileDPF, char *fileXML, sConfig *conf = NULL);
		int SaveConfig(char *fileDPF, char *fileXML, sConfig *conf = NULL);

		// -Common vars-
		SDL_Surface *screen;     //!< Main screen surface. You always have to use it to blit your graphics.
        int mouse_x;             //!< Mouse X position. Updated automatically.
        int mouse_y;             //!< Mouse Y position. Updated automatically.
		Uint8 mouse_buttons;     /**< @brief Current state of mouses buttons. Updated automatically in CRM32Pro.Update().
								      <br>Used as a mask when testing mouse buttons, usually as follow:
									  <br>-Left mouse button (CRM32PRO_BUTTON_LEFT)
									  <br>-Middle mouse button (CRM32PRO_BUTTON_MIDDLE)
									  <br>-Right mouse button (CRM32PRO_BUTTON_RIGHT)
									  <br>It also stores buttons combinations.*/
        Uint8 mouse_prevbuttons; //!< Previous state of mouses buttons. Updated automatically in CRM32Pro.Update().
		Uint32 iStartTime;       //!< Store the start ticks(SDL_GetTicks()) when CRM32Pro was initialized.
		Uint8 iAutoSurfRecovery; //!< Flag to set on/off auto surface recovery.It is automatically setup in DirectX hardware mode.
		int GetCPUName(char *);  // Get the CPU name. Undocumented.

		// -Resources internal control-
        int iNTiles,iNSprites,iNFonts;

	private:
		class cInternalMain *IInternal;	
};
 
 // High optimized memory copy
 extern "C" DllExport void *(*CRM32Pro_memcpy)(void *dest, const void *src, size_t n); //!< Optimized memcpy() function for each platform: AMD(K5,K6,K7,K8) and Intel(Pentium MMX,Pentium II, Pentium III,Pentium 4,Pentium M)
 //! @}
   

// ---------------------------------------------------------------------------
/** @defgroup MODULE2 MODULE 2: ILogSystem v2.6, log system interface.
 \image html logotipo.png
 * <br>Log System Interface to log any operation on your application. <br><br>
 * CRM32Pro uses it to print a lot of useful debug information: <br>
 * <b>- LOG_LOW:</b> only print out error messages.<br>
 * <b>- LOG_NORMAL:</b> previous level plus warning messages(some info are also included).<br>
 * <b>- LOG_HIGH:</b> previous level plus info messages.<br>
 * Note that all query information methods of objects/interfaces are using LOG_LOW.<br><br>
 * All print actions are internally done using Msg(). <br>
 * You should initialize this interface before the CRM32Pro.Init() to print out all information messages. <br>
 * - Created on 18 May 2000
 * - Last modified on 16 June 2007*/
// ---------------------------------------------------------------------------
//! @{
   //---Structs---
   #define LOG_NULL              0  //!< Use with Init() in 'mode' parameter: no output at all.
   #define LOG_CONSOLE           8  //!< Use with Init() in 'mode' parameter: output to console.
   #define LOG_FILE              2  //!< Use with Init() in 'mode' parameter: output to a file(if it exists, its contents are destroyed).
   #define LOG_FILEAPPEND        4  //!< Use with Init() in 'mode' parameter: output to a file(if it exists, we write at the end of its contents).
   #define LOG_LOW               0  //!< Use with Init() in 'level' parameter: low-level output log (only errors messages).
   #define LOG_NORMAL            2  //!< Use with Init() in 'level' parameter: normal-level output log (errors and warning messages).
   #define LOG_HIGH              5  //!< Use with Init() in 'level' parameter: high-level output log (errors,warning and info messages).
   
   //! ILogSystem
   /*! Interface to log your application  */
   class DllExport CRM32Pro_ILogSystem
   {
   public:
	   // -Constructor-
	   CRM32Pro_ILogSystem(void); 	   
	   // -Destructor-
	   ~CRM32Pro_ILogSystem(void);	   
	   // -Init-
	   void Init(char *filename, char mode,char level,char *prgname,char *author=NULL,char *email=NULL,char *web=NULL);       
	   // -Msg-
	   void Msg(char level,char *, ...);   
	   // -Show the time when occurred the event-
	   void ShowTime(char);
	   // -Halt the log output-
	   void Halt();
	   // -Resume a previous halted log system-
	   void Resume();
	   // -GetState-
	   unsigned char GetState(void); 
	   // -Code block profile begin-
	   void ProfileBegin(char* name);
	   // -Code block profile end-
	   void ProfileEnd(char* name);
	   // -Profiles table show-
	   void ProfileShow(void);

   private:
	   class cInternalLogSystem *IInternal;
    };
//! @}

// ---------------------------------------------------------------------------
/** @defgroup MODULE3 MODULE 3: IStuffDPF v4.3, Data Package Format interface.
 \image html logotipo.png
 * <br>Interface to manage all operations related to DPF (Data Package Format). <br>
 * It is a secure container to avoid external modification which can be protected with password. <br>
 * It uses a precached algorithm to a faster loading/saving resources for the last 32 DPFs opened. <br>
 * It will close and display info for any DPF file that was not closed at CRM32Pro.Quit() time. <br>
 * Internally, CRM32Pro use it to pack images, tiles, sprites, fonts, buttons and sounds. <br>
 * Very useful and easy to use. <br>
 * CRM32Pro.Init() builds this interface and CRM32Pro.Quit() removes it. <br>
 * - Created on 21 June 2001
 * - Last modified on 28 June 2007*/
// ---------------------------------------------------------------------------
//! @{ 
   #define DPFACCESS_NORMAL   0 //!< Used with SetAccessMode(). Fast access but in case of block corruption, it could omit some blocks. Default setting.
   #define DPFACCESS_LOWLEVEL 1 //!< Used with SetAccessMode(). Extremly slow access but in case of block corruption, it can read all blocks.

   //! Data block
   typedef struct DPF_BlockData
   {
     char name[32];      //!< Block name
	 char type[8];       //!< Block type
	 Uint8 storedmethod; //!< 0 to compress the block, 1 to do nothing with it and 2 to crypt it
     Uint32 size;        //!< Size in bytes of data block
	 Uint32 size_packed; //!< Compressed size in bytes of data block. Information purposes only.
	 char *data;	     //!< Pointer to raw data block
   } DPF_BlockData;

   //! IStuffDPF
   /*! Interface to manage DPF.*/ 
   class DllExport CRM32Pro_IStuffDPF
   {
    public:
		// -Constructor-
		CRM32Pro_IStuffDPF(void);   
		// -Destructor-
		~CRM32Pro_IStuffDPF(void);	
		// -Create DPF-
		int Create(char *filename);
		// -Open DPF-
		int Open(char *filename);   
		// -Close a DPF-		
		void Close(int idDPF);		
		// -Add a block of data to DPF-		
		int AddData(int idDPF, DPF_BlockData *info);
		// -Add a block of file to DPF-
		int AddFile(int idDPF, char *filename);
		// -Load a block of specific type-
		int LoadBlock(int idDPF,char *type,char *name,DPF_BlockData *info);
		// -Free a loaded block-
		int FreeBlock(DPF_BlockData *);
		// -Delete a specific block-
		int Delete(int idDPF,DPF_BlockData *info);
		// -Search for a specific block-
		int Search(int idDPF,DPF_BlockData *info);
		// -Find first block-
		int FindFirst(int idDPF,DPF_BlockData *info);
		// -Find next block-
		int FindNext(int idDPF,DPF_BlockData *info);
		// -Set the access mode-
		void SetAccessMode(char mode);
		// -Set the access password-
		void SetPassword(unsigned char *key,unsigned char keylen);
		// -Get the filename given a valid idDPF-
		char *GetFilename(int idDPF);
		// -Flush given idDPF-
		void Flush(int idDPF);
    
		// -Compact DPF-
		int Compact(char *filename);
		// -Protect your DPF with heavy encription-
	    int Protect(char *filename, unsigned char *key,unsigned char keylen);
        // -Unprotect your previously protected DPF with heavy encription-
	    int UnProtect(char *filename, unsigned char *key,unsigned char keylen);

		// -Return total blocks number of given DPF-
		int GetNumBlocks(int idDPF);
		// -Return deleted blocks number of given DPF-
		int GetNumDelBlocks(int idDPF);
		// -Return fragment percent of given DPF-
		char GetFragment(int idDPF);
		// -Return size of given DPF-
		int GetSize(int idDPF);
        // -Return info from last loaded DPF-
		char *GetName(void);
		char *GetCopyright(void);
		char *GetCreateDate(void);
		char *GetLastModified(void);
		int IsProtected(void);

	private:
		class cInternalStuffDPF *IInternal;		
   };
//! @}

// ---------------------------------------------------------------------------
/** @defgroup MODULE4 MODULE 4: IImage v3.00, Image Package Format interface.
 \image html logotipo.png
 * <br>IImage allows to manage the load/save images and stores it on DPF. It supports BMP and PNG.<br>
 * It supports alpha per surface, colorkey and alpha per pixel. <br>
 * We advice you to use EditorDPF to modify/add/delete image and its features.<br>
 * CRM32Pro.Init() builds this interface and CRM32Pro.Quit() removes it. <br>
 * - Created on 7 June 2001
 * - Last modified on 11 May 2007*/
// ---------------------------------------------------------------------------
//! @{
   //! IPF header
   typedef struct sHeaderIPF
   {
	 int TamX;			//!< image size x
	 int TamY;			//!< image size y
	 char bps;          //!< color depth (8,16,24,32)
     int AlphaValue;    //!< alpha channel (0=opaque,255=transparent)
	 int ColorKey;      //!< colorkey
	 char name[32];     //!< image name
	 char reserved[128];
   } sHeaderIPF;

   #define IIMAGE_PNGCOMPRESS_OFF      0  //!< Used with SavePNG(). Disable PNG compression.
   #define IIMAGE_PNGCOMPRESS_MAX      9  //!< Used with SavePNG(). Enable maximum PNG compression level.
   #define IIMAGE_PNGCOMPRESS_DEFAULT -1  //!< Used with SavePNG(). Enable default PNG compression level.

   //! IImage
   /*! Interface to manage images.*/ 
   class DllExport CRM32Pro_IImage
   {
    public:
	   // -Constructor-
	   CRM32Pro_IImage(void);	   
	   // -Destructor-
	   ~CRM32Pro_IImage(void);	
       // -Load a IPF from a DPF-
	   SDL_Surface *Load(char *fileDPF,char *imgname, sHeaderIPF *header = NULL); 
	   SDL_Surface *Load(int idDPF,char *imgname, sHeaderIPF *header = NULL); 
	   // -Save a IPF into a DPF-
	   int Save(char *fileDPF, char *imgname, SDL_Surface *image); 
	   int Save(int idDPF, char *imgname, SDL_Surface *image); 
	   
	   // -Load and save BMP-
	   SDL_Surface *LoadBMP(const char *filename);
	   int SaveBMP(char *filename,SDL_Surface *surface);	
	   int isBMP(const char *file);
	   // -Load and save PNG-
	   SDL_Surface *LoadPNG(const char *filename);
	   int SavePNG(char *filename,SDL_Surface *surface,int compression = IIMAGE_PNGCOMPRESS_DEFAULT);
	   int isPNG(const char *file);
	   // -Load an image(BMP or PNG)-
	   SDL_Surface *LoadIMG(const char *filename);

   private:
		class cInternalImage *IInternal;	
   }; 
//! @}


// ---------------------------------------------------------------------------
/** @defgroup MODULE5 MODULE 5: IPrimitives v3.50, primitives interface system.
 \image html logotipo.png
 <br>IPrimitives supports all stuff related to primitives rendering as: <br>
 <b>- points or getting/putting pixels</b><br>
 <b>- lines</b><br>
 <b>- rects</b><br>
 <b>- collision system</b><br>
 <b>- conversion of color formats(RGB,HSV,YUV and CYMK)</b><br><br>
 All functions work with any color depth.<br>
 CRM32Pro.Init() builds this interface and CRM32Pro.Quit() removes it. <br>
 - Created on 9 July 2001
 - Last modified on 29 September 2007*/
// ---------------------------------------------------------------------------
//! @{

//! IPrimitives
/*! Primitives interface system.*/
   class DllExport CRM32Pro_IPrimitives
   {    
    public:
		// -Constructor-
		CRM32Pro_IPrimitives(void);   
		// -Destructor-
		~CRM32Pro_IPrimitives(void);  

		// -Customizable collision method between two surfaces-
		unsigned char PixelCollision(SDL_Surface *s1, SDL_Rect *r1,SDL_Surface *s, SDL_Rect *r2,unsigned char debug=0,SDL_Rect *posr1=NULL,SDL_Rect *posr2=NULL); 
		// -Set collision method-
		void SetCollisionMethod(int mode);
		// -Get current collision method-
		int GetCollisionMethod();
		// -Draw a single pixel-
		void PutPixelColor(SDL_Surface *surf, short x, short y, unsigned int color, unsigned char alock = 1);  
		void PutPixelRGBA(SDL_Surface *surf, short x, short y, unsigned char r, unsigned char g, unsigned char b,unsigned char a = 255, unsigned char alock = 1);  
		// -Draw a pack of 16 pixels (only 32bit depth color version)
		void Put16Pixel(SDL_Surface *surf, short x, short y, unsigned int *arraypixels,unsigned char alock=1); 
		// -Get a single pixel-
		unsigned int GetPixel(SDL_Surface *surf, short x, short y,unsigned char alock=1); 
		// -Get a pack of 16 pixels (only 32bit depth color version)
		void Get16Pixel(SDL_Surface *surf, short x, short y,unsigned int *arraypixels,unsigned char alock=1);
		// -Draw horizontal line-
		void HLineColor(SDL_Surface *surf, short x1, short x2, short y, unsigned int color);
		void HLineRGBA(SDL_Surface *surf, short x1, short x2, short y, unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
		// -Draw vertical line-
		void VLineColor(SDL_Surface *surf, short x, short y1, short y2, unsigned int color);
		void VLineRGBA(SDL_Surface *surf, short x, short y1, short y2, unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
		// -Draw a line-
		void LineColor(SDL_Surface *surf, short x1, short y1, short x2, short y2, unsigned int color);
		void LineRGBA(SDL_Surface *surf, short x1, short y1, short x2, short y2, unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
		// -Draw an outlined rectangle-
		void RectangleColor(SDL_Surface *surf, short x1, short y1, short x2, short y2, unsigned int color);
		void RectangleRGBA(SDL_Surface *surf, short x1, short y1, short x2, short y2, unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
		// -Draw a filled rectangle-
		void BoxColor(SDL_Surface *surf, short x1, short y1, short x2, short y2, unsigned int color);
		void BoxRGBA(SDL_Surface *surf, short x1, short y1, short x2, short y2, unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
	    // -Color conversion RGB to HSV-
		void RGBtoHSV(unsigned char r8, unsigned char g8, unsigned char b8, float *h, float *s, float *v);
		// -Color conversion HSV to RGB-
		void HSVtoRGB(float h, float s, float v, unsigned char *r8, unsigned char *g8, unsigned char *b8);	
		// -Color conversion RGB to YUV-
		void RGBtoYUV(unsigned char r8, unsigned char g8, unsigned char b8, unsigned char* Y, unsigned char* U, unsigned char* V);
		// -Color conversion YUV to RGB-
		void YUVtoRGB(unsigned char Y, unsigned char U, unsigned char V, unsigned char* r8, unsigned char* g8, unsigned char* b8);
		// -Color conversion RGB to CMYK-
		void RGBtoCMYK(unsigned char r8, unsigned char g8, unsigned char b8, unsigned char* c, unsigned char* m, unsigned char* y, unsigned char *k);
		// -Color conversion CMYK to RGB-
		void CMYKtoRGB(unsigned char c, unsigned char m, unsigned char y, unsigned char k, unsigned char* r8, unsigned char* g8, unsigned char* b8);
		// -Lock a surface-
		void Lock(SDL_Surface *);
		// -Unlock a surface-
		void UnLock(SDL_Surface *);
    private:
		class cInternalPrimitives *IInternal;
   };
//! @}

// ---------------------------------------------------------------------------
/** @defgroup MODULE6 MODULE 6: ICursor v2.70, manage cursor actions.
 \image html logotipo.png
 <br>ICursor allows to use images as cursors and some extra functionality:<br>
 <b>- stores up to 20 cursors</b><br>
 <b>- clip region</b><br>
 <b>- 5 hot spots</b><br>
 <b>- change cursor on the fly</b><br> 
 <b>- alpha per surface and colorkey</b><br>
 <b>- alpha per pixel</b><br><br>
 You can get the mouse position using CRM32Pro.mouse_x and CRM32Pro.mouse_y. <br>
 We advice you to use EditorDPF to modify/add/delete image cursor and its features. <br>
 CRM32Pro.Init() builds this interface and CRM32Pro.Quit() removes it. <br>
 - Created on 31 August 2001
 - Last modified on 23 June 2007*/
// ---------------------------------------------------------------------------
//! @{

#define CTYPE_NORMAL    0  //!< Use with Create() in 'type' parameter: start blit coordinate is (0,0)
#define CTYPE_REVERSEX  1  //!< Use with Create() in 'type' parameter: start blit coordinate is (x cursor size,0)
#define CTYPE_REVERSEY  2  //!< Use with Create() in 'type' parameter: start blit coordinate is (0,y cursor size)
#define CTYPE_REVERSEXY 3  //!< Use with Create() in 'type' parameter: start blit coordinate is (x cursor size,y cursor size)
#define CTYPE_CENTER    4  //!< Use with Create() in 'type' parameter: start blit coordinate is (x cursor size/2, and cursor size/2)

//! ICursor
/*! Interface to manage cursor.*/ 
class DllExport CRM32Pro_ICursor 
{
	friend class CRM32Pro_Main;
	friend class CRM32Pro_CSprite;
	friend class CRM32Pro_CTile;
	friend class CRM32Pro_CFont;
	friend class CRM32Pro_IPrimitives;
    public:
		// -Constructor-
		CRM32Pro_ICursor();
		// -Destructor-
		~CRM32Pro_ICursor();

		// -Init system-	
		void Init(void);		
		// -Close system-		
		void Close(void);		
		// -Create a cursor from a file-		
		char Create(char *imgfile,char type=CTYPE_NORMAL); 
		// -Create a cursor from a surface-		
		char Create(SDL_Surface *surf,char type=CTYPE_NORMAL);
		// -Load a cursor from an IPF stored on a DPF-
		char Load(char *fDPF,char *nameIPF,char type=CTYPE_NORMAL); 	    
		char Load(int idDPF,char *nameIPF,char type=CTYPE_NORMAL); 	    
		// -Delete a cursor-
		void Delete(char id);		
		// -Select a cursor and define it as current cursor-
		void Select(char id);		
		// -Invalidate next background autorestore-
		void Invalidate(void);   
		// -Hide current cursor-
		void Hide(void);
		// -Show current cursor-
		void Show(void);
		// -Define a valid clip region-
		void ClipRegion(int xi,int yi,int xf,int yf);
		// -Enable/Disable autorestore background
		void AutoRestore(char value);
		// -Enable/Disable smooth movement-
		void SetSmooth(char value);
		// -Set the cursor position-
		void SetPosition(int x, int y);
		// -Change the type of cursor-
		void ChangeType(char id, char type);
		// -Print a lot of useful information about cursor interface-
		void Info();

	private:
		//! Private members to update and save cursor. Called internally by CRM32Pro.Update()
		void Update(void);
		void SaveCoordinates(int x,int y);
		//! Private members used internally by CFont,CSprite and CTile
        int RestoreBG(SDL_Rect *r=NULL);
		void CopyBG();		
		class cInternalCursor *IInternal;	
};
//! @}


// ---------------------------------------------------------------------------
/** @defgroup MODULE7 MODULE 7: CTile v2.00, tile engine class.
 \image html logotipo.png
 <br>CTile supports all stuff related to manage and draw tiles: <br>
 <b>- tileset with independent width and height</b><br>
 <b>- easy to set a position</b><br>
 <b>- alpha per surface and colorkey</b><br>
 <b>- alpha per pixel</b><br><br>
 We advice you to use EditorDPF to modify/add/delete tiles and its features.<br>
 - Created on 23 June 2001
 - Last modified on 24 December 2006*/
// ---------------------------------------------------------------------------
//! @{

//! CTile
/*! Tile engine class.*/
class DllExport CRM32Pro_CTile
   {
    public:
		// -Constructor-
		CRM32Pro_CTile(void);  
		// -Destructor-
		~CRM32Pro_CTile(void);	
		// -Create tile from a BMP-		
		unsigned char Create(char *filebmp,char *nametile);
		// -Create tile from a surface-
		unsigned char Create(SDL_Surface *surf,char *nametile);
		// -Load tile from DPF-
		unsigned char Load(char *fileDPF,char *name,char *typeblock="TILE2");        
		unsigned char Load(int idDPF,char *name,char *typeblock="TILE2"); 
		// -Save tile to DPF-
		int Save(char *fileDPF,char *typeblock="TILE2");
		int Save(int idDPF,char *typeblock="TILE2");
		// -Clean tile-
		void Clean();
		// -Draw tile-
		int Draw(SDL_Surface *dumpto=NULL,int selTS=0);
		// -Print a lot of useful tile information-
		void Info();
		// -Get x size-
		int GetSizeX(void);
		// -Get y size-
		int GetSizeY(void);
		// -Get x position-
		int GetPosX();
		// -Get y position-
		int GetPosY();
		// -Get OffX(width) and OffY(height) for each tile on the tileset-
        int GetOffset(int *,int*);
		// -Get the tile name-
		char *GetName();
		// -Get the tile surface-
        SDL_Surface *GetSurface();		
		// -Get alpha blending information-
		int GetAlpha();
		// -Get current colorkey of the tile-
		int GetColorKey();
		// -Set position on screen of tile-
		void SetPosition(int x, int y);
		// -Set a colorkey using RGB values-
		void SetColorKey(int r,int g,int b);		
		// -Set a colorkey using a packed integer-
		void SetColorKey(int CKey);
		// -Set alpha per surface-
		void SetAlpha(int shade);
		// -Conversion from a tile to tileset and reverse-
		unsigned char SetTileSet(int isTS,int offsetX,int offsetY);	
		// -Set a new name for the tile-
		void SetName(char *name);	
    private:
		class cInternalTile *IInternal;
   };
//! @}


// ---------------------------------------------------------------------------
/** @defgroup MODULE8 MODULE 8: CFont v2.61, font engine class.
 \image html logotipo.png
 <br>CFont supports all stuff related to manage and render fonts. <br>
 You can use any external font and convert it to the internal format.<br>
 Although it can render fonts in 8bits surfaces, the font must be created using 16,24 or 32bits surfaces.<br>
 It supports alpha per surface and alpha per pixel <br>
 We advice you to use EditorDPF to modify/add/delete fonts and its features.<br>
 * - Created on 30 July 2001
 * - Last modified on 23 June 2007*/
// ---------------------------------------------------------------------------
//! @{
// ! " # $ % & ' ( ) * + , - . / 0 1 2 3 4 5 6 7 8 9 : ; < = > ? @ A B C D E F G H I J K L M N O P Q R S T U V W X Y Z [ \ ] ^ _ ` a b c d e f g h i j k l m n o p q r s t u v w x y z { | } ~ 

//! CFont
/*! Font engine class.*/
class DllExport CRM32Pro_CFont
{
    public:
		// -Constructor-
		CRM32Pro_CFont(); 
		// -Destructor-
		~CRM32Pro_CFont();
		// -Create a font from a surface or BMP-
		unsigned char Create(SDL_Surface *surface);
		unsigned char Create(char *filebmp);
		// -Load a font from DPF-
		unsigned char Load(char *fileDPF, char *fontname);
		unsigned char Load(int idDPF, char *fontname);
		// -Save this font to a DPF-
		int Save(char *fileDPF,char *fontname);
		int Save(int idDPF,char *fontname);
		// -Clean font-
		void Clean();
		// -Test if a given surface or BMP can be converted to a font-
		unsigned char Test(char *filebmp);
		unsigned char Test(SDL_Surface *);
		// -Print a lot of useful info-
		void Info();
	    // -Draw a string using the font-
	    void PutString(SDL_Surface *Surface, int x, int y, char *str, SDL_Rect *clip=NULL);	    
		// -Draw a string using the font with cursor-
		void PutStringWithCursor(SDL_Surface *Surface, int x, int y, char *str, int cursPos, SDL_Rect *clip=NULL, unsigned char showCurs=1);
		// -Get the size of the given string (in pixels)-
		int StringWidth(char *str);
		// -Render a X centered string-
		void PutStringXCenter(SDL_Surface *Surface, int y,  char *str, SDL_Rect* clip=NULL);		
		// -Render a Y centered string-
		void PutStringYCenter(SDL_Surface *Surface, int x,  char *str, SDL_Rect* clip=NULL);		
		// -Set the cursor position-
		int SetCursorAt(char *str,int px);			
	    // -Get alpha blending information-
		int GetAlpha();		
		// -Get the kerning value-
		int GetKerning();
		// -Get the surface of font-
		SDL_Surface *GetSurface();
		// -Get the name of the font-
		char *GetName();
		// -Set the kerning value-
		void SetKerning(int value);
		// -Set alpha per surface-
		void SetAlpha(int shade);
		// -Set a new name for the font-
		void SetName(char *name);	

	private:
		class cInternalFont *IInternal;
};
//! @}

// ---------------------------------------------------------------------------
/** @defgroup MODULE9 MODULE 9: IScreenFX v4.50, screen FX interface.
 \image html logotipo.png
 <br>IScreenFX has members to do simples special effects on screen surface as: <br>
 <b>- greyscales</b><br>
 <b>- negative</b><br>
 <b>- black & white</b><br>
 <b>- wind</b><br>
 <b>- red filter</b><br>
 <b>- blue filter</b><br>
 <b>- green filter</b><br><br>
 And it also has complex effects as: <br> 
 <b>- fades (from and to, any color and any surface)</b><br>
 <b>- gamma correct</b><br>
 <b>- blur filter</b><br>
 <b>- noise filter</b><br>
 <b>- scale surfaces</b><br>
 <b>- rotate surfaces</b><br><br>
 CRM32Pro.Init() builds this interface and CRM32Pro.Quit() removes it. <br>
 - Created on 9 July 2001
 - Last modified on 23 August 2007*/
// ---------------------------------------------------------------------------
//! @{
   #define FXSCREEN_NULL       0 //!< Switch off any kind of effect
   #define FXSCREEN_COLOR      1 //!< Color threshold effect Color threshold effect
   #define FXSCREEN_WIGGLE     2 //!< Wiggle effect
   #define FXSCREEN_ZOOM       3 //!< Progressive zoom effect
   #define FXSCREEN_VIDEO      4 //!< Video effect
   #define FXSCREEN_WIND       5 //!< Wind effect
   #define FXSCREEN_NEGATIVE   6 //!< Negative color effect
   #define FXSCREEN_GREY       7 //!< Grey effect
   #define FXSCREEN_GREYREAL   8 //!< Accurate grey effect
   #define FXSCREEN_BLACKWHITE 9 //!< Black/White effect
   #define FXSCREEN_RED       10 //!< Red effect
   #define FXSCREEN_GREEN     11 //!< Green effect
   #define FXSCREEN_BLUE      12 //!< Blue effect

   //! IScreenFX
   /*! Screen FX interface system.*/
   class DllExport CRM32Pro_IScreenFX
   {
    
    public:	  
		// -Construct-
		CRM32Pro_IScreenFX(void);
		// -Destructor-
		~CRM32Pro_IScreenFX(void);
		// -Add noise to given surface(very slow)-
		int Noise(SDL_Surface *surface, int noise_pct);
		// -Add blur to given surface(very slow)-
		int Blur(SDL_Surface *surface, int blur_pct);
		// -Set gamma to given surface-
		int GammaCorrect(SDL_Surface *surface,int r,int g,int b);
		// -Fade current screen surface to given color-
		int FadeToColor(unsigned char r,unsigned char g,unsigned char b,unsigned int ms,SDL_Rect *rdst=NULL);           
		// -Fade to given surface from current screen surface-
		int FadeToImage(SDL_Surface *surface,unsigned int ms,SDL_Rect *rdst=NULL,SDL_Rect *rsrc=NULL);
		// -Surface rotate-
		SDL_Surface *Rotate(SDL_Surface *src, SDL_Rect *src_rect,int smooth,double angle,SDL_Surface *dst = NULL, SDL_Rect *dst_rect = NULL);
		// -Surface rotate/resize-
		SDL_Surface *RotateResize(SDL_Surface *src, SDL_Rect *src_rect,int smooth,double angle,double zoom, SDL_Surface *dst = NULL, SDL_Rect *dst_rect = NULL);
		// -Surface resize-
		SDL_Surface *Resize(SDL_Surface *src, SDL_Rect *src_rect,int smooth,double fx, double fy,SDL_Surface *dst = NULL, SDL_Rect *dst_rect = NULL);
		SDL_Surface *Resize(SDL_Surface *src, SDL_Rect *src_rect,int smooth,int sx, int sy, SDL_Surface *dst = NULL, SDL_Rect *dst_rect = NULL);		
		// -Surface flip-
		SDL_Surface *Flip(SDL_Surface *src, SDL_Rect *src_rect = NULL,SDL_Surface *dst = NULL, SDL_Rect *dst_rect = NULL);
		// -Surface mirror-
		SDL_Surface *Mirror(SDL_Surface *src, SDL_Rect *src_rect = NULL,SDL_Surface *dst = NULL, SDL_Rect *dst_rect = NULL);
		// -Render simple special fx-
		void RenderFX(SDL_Surface *src,SDL_Surface *dst,int effect);
 
	private:
		class cInternalScreenFX *IInternal;
		char deInitIPrimitives; // Internal var
   };
//! @}

// ---------------------------------------------------------------------------
/** @defgroup MODULE10 MODULE 10: IButton v4.10, GUI interface.
 \image html logotipo.png
 <br>IButton is a multilayer GUI sytem with these type of buttons: <br>
 <b>- normal</b><br>
 <b>- complex</b><br>
 <b>- check</b><br>
 <b>- slider</b><br>
 <b>- progress bar</b><br>
 <b>- input box</b><br>
 <br>It also supports:<br>
 <b>- See below table or IButtonNew struct to a full list of properties</b><br>
 <b>- alpha per surface and colorkey</b><br>
 <b>- alpha per pixel</b><br>
 <br>Internally, it uses CTile to store/load the images.<br>
 Currently it supports up to 5(MAX_LAYERBUTTON) layers with 32(MAX_BUTTON) maximum buttons per layer.<br>
 In addition, the maximum number of master button is 100(MAX_MASTERBUTTON).<br>
 We advice you to use EditorDPF to modify/add/delete tiles and its features.<br>
 CRM32Pro.Init() builds this interface and CRM32Pro.Quit() removes it. <br>
 - Created on 10 June 2001
 - Last modified on 19 November 2007
 <table align="center" border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse" bordercolor="#111111" width="700">
 <tr> <td width="100%">
 <br>
 \image html ibutton.jpg  
 </td></tr></table>*/
// ---------------------------------------------------------------------------
   
   //! @{
   #define B_NORMAL 1  //!< Button state: normal                                                
   #define B_SELECT 2  //!< Button state: selected                                                
   #define B_PRESS 4   //!< Button state: pressed
   #define B_ACTION 8  //!< Button state: click
   #define B_OFF 16    //!< Button state: desactivated

   #define B_TYPE_NORMAL 1    //!< Used in IButtonNew.type: to create a normal button.
   #define B_TYPE_ICON   2    //!< Used in IButtonNew.type: deprecated, only for back compatibility.The same behaviour as NORMAL.
   #define B_TYPE_COMPLEX 4   //!< Used in IButtonNew.type: to create a complex button.
   #define B_TYPE_SLIDER 8    //!< Used in IButtonNew.type: to create a slider.
   #define B_TYPE_PROGRESS 16 //!< Used in IButtonNew.type: to create a progress bar.
   #define B_TYPE_CHECK 32    //!< Used in IButtonNew.type: to create a check button.
   #define B_TYPE_INPUT 64    //!< Used in IButtonNew.type: to create an input box.

   //! External button struct used to create new buttons
   typedef struct IButtonNew                                       
	{                                                                  
	 void (*ButtonFunc)(void *,void*); //!< Pointer to function to call with action state. 
	 Uint16 key;                       //!< Key associated to button
	 Uint8 type;                       //!< Button type. See definition of B_TYPE_xx
  	 Uint32 color_select;              //!< Color of select rectangle
	 Uint16 posx, posy;                //!< (X,Y) position
	 short int range;                  //!< Range
	 char bVisible;                    //!< 0=invisible and 1=visible
	 char bClon;                       //!< Am I a clone? 0=no 1=yes
	 int cvalue;                       //!< Current value.
   } IButtonNew;    
    
   //! IButton
   /*! Button interface system.*/
   class DllExport CRM32Pro_IButton
   {    
	   friend class CRM32Pro_Main;
    public:
		// -Constructor-
		CRM32Pro_IButton(void);   
		// -Destructor-
		~CRM32Pro_IButton(void);                                                       
		// -Add new button to current layer-                                    
		int Create(struct IButtonNew *button,char *tilename,unsigned char master,char *fDPF);  
		int Create(struct IButtonNew *button,char *tilename,unsigned char master,int idDPF); 
        // -Load a button from DPF file-
		int Load(char *fDPF,char *butname,unsigned char master=0); 
		int Load(int idDPF,char *butname,unsigned char master=0); 
		// -Only load the header of button from a DPF file-
		unsigned char LoadHeader(char *fDPF,char *butname, IButtonNew *info);
		unsigned char LoadHeader(int idDPF,char *butname, IButtonNew *info);
		// -Delete a button from a DPF file-
		unsigned char Delete(char *fDPF, char *butname);
		unsigned char Delete(int idDPF, char *butname);
		// -Save a button to DPF file-
		int Save(char *fDPF,char *butname,IButtonNew *button);
		int Save(int idDPF,char *butname,IButtonNew *button);
		// -Draw buttons of current layer-
		int Draw(void);            
		// -Get ID of selected button-
		int WhoIsSelected(void);     
		// -Remove a working button given its ID-
		void Remove(int id);  
		// -Remove all working buttons of current layer-
		void RemoveAll(void); 
		// -Remove a master button given its ID-
		void RemoveMaster(int id); 
		// -Clone a given ID button-
		int  Clone(int id);
		// -Force to draw all buttons on visible layer on next call to Draw()-
		void ForceDraw(void); 
		// -Print a lot of information about button interface-
		int Info(int m); 
		// -Get current text, only works with InputText button-
        char *GetText(int id);
		// -Get total number of buttons-
		int GetNum(void);            
		// -Get the range of slider or progress-
		int GetRange(int id);        
		// -Get current value of slider or progress-
		int GetValue(int id); 
		// -Get current state of given ID button-
		int GetState(int id);        
		// -Get surface of given ID button and its state
		SDL_Surface *GetSurface(int id,int state);
		// -Get the name of the given ID button-
		char *GetName(int id);	
		// -Get alpha blending information-
		int GetAlpha(int id, int state);
		// -Get the current color key used by the given button/state-
		int GetColorKey(int id, int state);
		// -Get the assigned key to the given ID button-
		int GetKey(int id);
		// -Get the color select to the given ID button-
		int GetColorSelect(int id);
		// -Get current mouse button sensibility of given IButton-
		int GetMouseButtons(int id);
		// -Force a state of given ID button-
		void SetState(int id,char s);     
		// -Set the colorkey using RGB-
        void SetColorKey(int id,int state,int r,int g,int b); 
		// -Set the colorkey using a packed integer-
		void SetColorKey(int id,int state,int CKey );
		// -Set alpha per-surface-
		void SetAlpha(int id,int state,int shade);
		// -Set the working layer-
		void SetLayer(char n);
		// -Set visibility of given layer-
        void SetLayerVisibility(char n,char v);
		// -Set visibility of given ID button-
		void SetVisible(int id,unsigned char value);  		
		// -Set position of given ID button-
		void SetPosition(int id,int x,int y);
		// -Set a font, only works with InputText button-
		void SetTextFont(int id,CRM32Pro_CFont *font);
		// -Set text rect area, only works with InputText button-
		void SetTextRect(int id,SDL_Rect *);
		// -Set text, only works with InputText button-
		void SetText(int id,char *);		
		// -Set current value of slider or progress-
		void SetValue(int id, int value);		      
		// -Set a function for the given ID button-
		void SetFunction(int id, void (*ButtonFunc)(void *,void *), void *iParam1 = NULL, void *iParam2 = NULL);		
		// -Set a new name for the given ID button-
		void SetName(int id,char *name);
		// -Set the assigned key to the given ID button-
		void SetKey(int id, int keycode);
		// -Set the color select to the given ID button-
		void SetColorSelect(int id, int r, int g, int b);
		void SetColorSelect(int id, int rgb);
		// -Set mouse button sensibility for the given IButton-
		void SetMouseButtons(int id, int mousebut);

	private:
		//! Private member to update GUI system. Called internally by CRM32Pro.Update()
		void Update();
		class cInternalButton *IInternal;
   };
//! @}


// ---------------------------------------------------------------------------
/** @defgroup MODULE11 MODULE 11: ITimeSystem v1.70, timer system interface
 \image html logotipo.png
 * <br>ITimeSystem has the timer control, Rendering Frame Rate, Logic Frame Rate. <br>
 * If you want to use it, you need to call to Init() after CRM32Pro.Init(). <br>
 * CRM32Pro.Init() builds this interface and CRM32Pro.Quit() removes it.  <br>
 * - Created on 28 September 2002
 * - Last modified on 23 June 2007*/
// ---------------------------------------------------------------------------
//! @{
#define TIMER_INIT   0  //!< Used with Init(). It always initializes the timer system. 
#define TIMER_RESET  1  //!< Used with Init(). If it was already initialized, it will cause a timer reset holding desired rates.

//! ITimeSystem
/*! Time system interface class.*/
class DllExport CRM32Pro_ITimeSystem
   {
	   friend class CRM32Pro_Main;
    public:
		// -Constructor-
		CRM32Pro_ITimeSystem(); 
		// -Destructor-
		~CRM32Pro_ITimeSystem(); 
		// -Initialize timer system-
		void Init(int mode=TIMER_INIT);  
		// -Set desired Rendering and Logic Frame Rates-
		void SetRate(unsigned int r, unsigned int l);
		// -Print a lot of useful information about cursor interface-
		void Info();
		// -Get desired Logic Frame Rate-
		int GetDesiredLFR();
		// -Get desired Rendering Frame Rate-
		int GetDesiredRFR();
		// -Get current Rendering Frame Rate (in real time)-
		int GetCurrentRFR();
		// -Get current Logic Frame Rate (in real time)-
		int GetCurrentLFR();
		// -Get average of Rendering Frame Rate-
		float GetRFR();
		// -Get average of Rendering Frame Rate-
		float GetLFR();
		// -Get total Rendered frames until now-
		int GetRenderedFrames();
		// -Get total Logic frames until now-
		int GetLogicFrames();
		// -Get execution time (in seconds)-
		float GetSeconds();
		// -Get current time (in ticks)-
		int GetTime();
   private:
	   // -Private members used internally by CRM32Pro.Update()-
	   void Update(); 
	   void IncRF();
	   void IncLF();
	   class cInternalTimer *IInternal;
   };
//! @}


// ---------------------------------------------------------------------------
/** @defgroup MODULE12 MODULE 12: CSprite v4.00, sprite engine class.
 \image html logotipo.png
 <br>CSprite supports all stuff related to manage and draw sprites: <br>
 <b>- sprites with independent number of animations and frames</b><br>
 <b>- animation features</b><br>
 <b>- frame features</b><br>
 <b>- easy to set a position</b><br>
 <b>- auto animation</b><br>
 <b>- special effects: flip,mirror,rotate and scale</b><br>
 <b>- alpha per surface and colorkey</b><br>
 <b>- alpha per pixel</b><br><br>
 We advice you to use EditorDPF to modify/add/delete sprites and its features.<br>
 - Created on 15 September 2001
 - Last modified on 30 September 2007
 <table align="center" border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse" bordercolor="#111111" width="700">
  <tr> <td width="100%">
  <br>
  \image html csprite.jpg
  <br>
  \image html csprite_text.jpg
 </td></tr></table>*/
// ---------------------------------------------------------------------------
//! @{

   // Sprite animation state
   // It used 16bit, high byte set high-state and low byte set low-state
   #define SPRSTATE_NORMAL      0x8000 //!< Sprite animation high-state: normal     (10000000-00000000) 
   #define SPRSTATE_UP          0x4000 //!< Sprite animation high-state: up         (01000000-00000000)
   #define SPRSTATE_DOWN        0x2000 //!< Sprite animation high-state: down       (00100000-00000000)
   #define SPRSTATE_LEFT        0x1000 //!< Sprite animation high-state: left       (00010000-00000000)
   #define SPRSTATE_RIGHT       0x0800 //!< Sprite animation high-state: right      (00001000-00000000)
   #define SPRSTATE_UPLEFT      0x0400 //!< Sprite animation high-state: up-left    (00000100-00000000)
   #define SPRSTATE_UPRIGHT     0x0200 //!< Sprite animation high-state: up-right   (00000010-00000000)
   #define SPRSTATE_DOWNLEFT    0x0100 //!< Sprite animation high-state: down-left  (00000001-00000000)
   #define SPRSTATE_DOWNRIGHT   0xC000 //!< Sprite animation high-state: down-right (11000000-00000000)
   #define GetSpriteHighState(x) (x & ~0x00FF) //!< Macro to get the sprite animation high-state. See above SPRSTATE_xx. 
   #define GetSpriteLowState(x)  (x & ~0xFF00) //!< Macro to get the sprite animation low-state. Each high-state can have until 256 low-states defined by the user.

   #define SPRTYPE_LOOP      2  //!< Sprite animation type: loop
   #define SPRTYPE_PINGPONG  4  //!< Sprite animation type: ping-pong
   #define SPRTYPE_ONESHOT   8  //!< Sprite animation type: one shot
   #define SPRANIM_LOOP     SPRTYPE_LOOP     // Backward compatibility
   #define SPRANIM_PINGPONG SPRTYPE_PINGPONG // Backward compatibility
   #define SPRANIM_ONESHOT  SPRTYPE_ONESHOT  // Backward compatibility

   #define SPRANIM_KEEP_PROPERTIES 0xAAA //!< To maintain current value. See SetAnimProperties() to further information.

   // Sprite special effects
   #define SPREFFECT_NONE            0 //!< Sprite is rendered without any special effect.
   #define SPREFFECT_FLIP            1 //!< Sprite is rendered using flip effect.
   #define SPREFFECT_MIRROR          2 //!< Sprite is rendered using mirror effect.
   #define SPREFFECT_RESIZE          3 //!< Sprite is rendered using resize effect.
   #define SPREFFECT_ROTATE          4 //!< Sprite is rendered using rotation effect.
   #define SPREFFECT_ROTATERESIZE    5 //!< Sprite is rendered using rotation and resize effect.

   //! CSprite
   /*! Sprite engine class.*/
   class DllExport CRM32Pro_CSprite
   {
    public:
		// -Constructor-
		CRM32Pro_CSprite(void);   
		// -Destructor-
		~CRM32Pro_CSprite(void);
	
		// -Turn off/on auto background restore-
        void AutoRestore(char value);
		// -Create a new sprite set from a BMP file-
		int Create(char *spritebmp,char *namespr,int OffX,int OffY);
		// -Create a new sprite set from a given surface-
		int Create(SDL_Surface *surf,char *namespr,int OffX,int OffY);
		// -Clean sprite-
		void Clean();
		// -Clone a sprite-
        int Clone(CRM32Pro_CSprite *pSpr);
		// -Save a sprite to DPF-		
		int Save(char *fileDPF,char *typeblock="SPR2");
		int Save(int idDPF,char *typeblock="SPR2");
		// -Load a sprite-		
		int Load(char *fileDPF,char *namespr,char *typeblock="SPR2");
		int Load(int idDPF,char *namespr,char *typeblock="SPR2");
		// -Check collision with another sprite-
		int Collision(CRM32Pro_CSprite *spr,short spr_x=-1,short spr_y=-1,short this_x=-1,short this_y=-1,unsigned char debug=0);
		// -Check collision with a surface-
		int Collision(SDL_Surface *surf,SDL_Rect *rect, short this_x=-1,short this_y=-1,unsigned char debug=0);
		// -Print a lot of useful info-
		void Info();
		// -Pause animation-
		void Pause();
		// -Resume animation-
		void Resume();
		// -Is finished the animation?-
		unsigned char IsFinished();
		// -Draw sprite-
		int Draw(SDL_Surface *dump=NULL);		
		// -Select a frame of current animation state-
		unsigned char SelectFrame(int iFrame);
		// -Get current animation state-
		int GetAnim();
		// -Get current frame-
		int GetFrame();		
		// -Get alpha blending information-
		int GetAlpha();
		// -Get surface-
        SDL_Surface *GetSurface();
		// -Get X position-
		int GetPosX();
		// -Get Y position-
		int GetPosY();
		// -Get OffX and OffY-
        void GetOffset(int *,int*);
		// -Get animation properties-
		void GetAnimProperties(int which,unsigned short *type=NULL, unsigned short *status=NULL,unsigned short *frames=NULL, 
			        signed short *hotx=NULL,signed short *hoty=NULL,unsigned short *startframe=NULL,unsigned short *endframe=NULL);
		// -Get frame properties-
		void GetFrameProperties(int iAnim,int iFrame, unsigned int *ms=NULL);
		// -Get the name of the sprite-
		char *GetName();
		// -Get current colorkey of the tile-
		int GetColorKey();
		// -Get current collision method of this sprite-
		int GetCollisionMethod();
		// -Set animation factor speed-
		void SetAnimFactor(float fRs);
		// -Select an animation state-
		unsigned char SelectAnim(int status);
		// -Set a colorkey using RGB values-
		void SetColorKey(int r,int g,int b);		
		// -Set a colorkey using packed integer-
		void SetColorKey(int CKey);
		// -Set alpha per surface-
		void SetAlpha(int shade);
        // -Set position-
		void SetPosition(int x, int y, int smooth = 0);
		// -Set animation properties-
		unsigned char SetAnimProperties(int iAnim,unsigned short iType=SPRANIM_KEEP_PROPERTIES,unsigned short iStatus=SPRANIM_KEEP_PROPERTIES,
			signed short iHotX=SPRANIM_KEEP_PROPERTIES, signed short iHotY=SPRANIM_KEEP_PROPERTIES,
			unsigned short iStartFrame=SPRANIM_KEEP_PROPERTIES, unsigned short iEndFrame=SPRANIM_KEEP_PROPERTIES);
		// -Set frame properties-
		unsigned char SetFrameProperties(int iAnim,int iFrame,unsigned int iMs);		
		// -Set a new name for the sprite-
		void SetName(char *name);
		// -Set collision method for this sprite-
		void SetCollisionMethod(int mode);
		// -Set a special effect-
		void SetEffect(int effect, int smooth = 0, double dParam1 = 0.0, double dParam2 = 0.0);    
		// Internal class
		class cInternalSprite *IInternal;
   };
//! @}

// ---------------------------------------------------------------------------
/** @defgroup MODULE13 MODULE 13: INetwork v4.10, network interface
 \image html logotipo.png
 <br>INetwork manages TCP/IP client and server architecture. <br>
 It has support for:<br>
 <b>- up to 16 clients</b><br>
 <b>- login with password</b><br>
 <b>- powerful log error system</b><br>
 <b>- reception queue</b><br>
 <b>- network statistic</b><br>
 <b>- secure transmision layer</b><br><br> 
 It also has two working modes:<br><br>\ref _NonAuthNet " - Non-Authoritative Server mode" <br><br>\ref _AuthNet " - Authoritative Server mode" <br>
 <br>CRM32Pro.Init() builds this interface and CRM32Pro.Quit() removes it.  
  - Created on 23 March 2004
  - Last modified on 20 September 2007*/
// ---------------------------------------------------------------------------
//! @{
   
   #define INETWORK_NEWCLIENT     40  //!< System Datanet: new client signal. It sends its name.
   #define INETWORK_QUITCLIENT    42  //!< System Datanet: quit client signal. It sends its name.
   #define INETWORK_CLOSE         44  //!< System Datanet: close signal.
   #define INETWORK_CLIENTSINFO   46  //!< System Datanet: reply to QueryClientsInfo(). Now you can get updated information using GetClientsInfo().
   #define INETWORK_PING          48  //!< System Datanet: automatic ping to check if the client-server connection is up.
   #define INETWORK_DATA          64  //!< Remote User Datanet: data signal from remote user. It sends the data. 
   #define INETWORK_DATAVALIDATED 68  //!< Own User Datanet: data signal from own user, accepted by the Authoritative Server. It sends the data. 
   #define INETWORK_DATADENIED    70  //!< Own User Datanet: data signal from own user, denied by the Authoritative Server. It sends the data. 
   #define INETWORK_ERROR        128  //!< System Datanet: error signal: connection lost.

   //! Client information struct
   typedef struct
   {
     char szName[16];    //!< The name of the client. Updated automatically.
     Uint32 IP;          //!< The IP v4 address of the client. Updated automatically.
	 int iLatency;       //!< The latency of the last second. Updated only when a client is connected or disconnected or you call to QueryClientsInfo().
	 int iLatencyAvg;    //!< The latency average of last 10 seconds Updated only when a client is connected or disconnected or you call to QueryClientsInfo().
   } sClientInfo;

   //! INetwork 
   /*! Network interface.*/
   class DllExport CRM32Pro_INetwork
   {
   public:
       // -Constructor-
	   CRM32Pro_INetwork(void);	   
	   // -Destructor-
	   ~CRM32Pro_INetwork(void); 
	   // -Initialize system-
	   unsigned char Init(char m_log);  
	   // -Close system-
	   void Quit();
	   // -Create a server- 
	   unsigned char CreateServer(unsigned short port,unsigned int passwd,unsigned char dedicated);
   	   // -Connect to server-
	   unsigned char ConnectTo(char *host,unsigned short port,char *user,unsigned int passwd); 
	   // -Set a callback function to hook into Server to evaluate the data(Authoritative Server)-
	   void SetCoreServerCallback(int (*myCoreServer)(void *data,int size));
	   // -Send data to clients-
	   unsigned char SendData(char *buff,int size, char isquery = 1); 
	   // -Received data of others clients-
	   unsigned char ReceiveData(char **buf,unsigned int *size);
	   // -Free previous received data-
	   void FreeData(char *&buf);
	   // -Query to close server (and all clients)-
	   unsigned char QueryKillServer(); 
	   // -Query to kill this client-
	   unsigned char QueryKillClient();  
	   // -Query to get all current clients with updated information-
	   unsigned char QueryClientsInfo();    
	   // -Print a lot of useful information-
	   void Info();	   
	   // -Check if we are running as server-
	   unsigned char IsServer();
	   // -Check if we are running as client-
	   unsigned char IsClient();
	   // -Get information about all the connected clients-
	   unsigned char GetClientsInfo(sClientInfo **cinfo);
	   // -Get my IP if any-
	   unsigned int GetMyIP();
	   // -Get my user name if any-
	   char *GetMyUserName();
	   // -Set the connection timeout in milliseconds-
	   void SetTimeOut(int ms);
   };
//! @}

// ---------------------------------------------------------------------------
/** @defgroup MODULE14 MODULE 14: IVideo v2.20, player video interface
 \image html logotipo.png
 <br>IVideo allows to play MPEG-1 video and music stream. <br><br>
 It supports: <br>
 <b>- smoothing and deblocking video stream</b><br>
 <b>- scaled video playback</b><br>
 <b>- centered or defined position video playback</b><br>
 <b>- set any of the FXSCREEN_xx definitions (see IScreenFX for further information)</b><br>
 <b>- set a function callback to be called each frame.</b><br><br>
 CRM32Pro.Init() builds this interface and CRM32Pro.Quit() removes it.  <br>
 - Created on 30 August 2001
 - Last modified on 23 June 2007*/
// ---------------------------------------------------------------------------
//! @{

#define VIDEO_FILTER_NULL    0 //!< Switch off any kind of filter (only MPEG)
#define VIDEO_FILTER_SMOOTH  1 //!< Switch on smooth video stream (only MPEG)
#define VIDEO_FILTER_DEBLOCK 2 //!< Switch on deblocking video stream (only MPEG)
#define VIDEO_PLAY_CENTER   -1 //!< Dump video stream centered on screen (only MPEG). Read more on SetPosition().

//! IVideo
/*! Player MPEG interface.*/
class DllExport CRM32Pro_IVideo
{
    public:
		// -Constructor-
		CRM32Pro_IVideo();
		// -Destructor-
		~CRM32Pro_IVideo();
		// -Play a MPEG-1-
		char PlayMPEG(char *file,char bSound=1, char bFilter=VIDEO_FILTER_NULL);  
		// -Set a scaled size to play the video-
		void SetScale(int width,int height);
		// -Set position to play the video-
		void SetPosition(int x,int y);
		// -Set special fx for video-
		void SetFX(int);
		// -Set a function for each frame update-
		void SetFunction(void (*MyFunction)(int kPressed));
};
//! @}

// ---------------------------------------------------------------------------
/** @defgroup MODULE15 MODULE 15: ISoundFX v4.00, sound,music and FX effects interface
 \image html logotipo.png
 <br>ISoundFX allows to play sound and music tracks. <br>
 Basically, it is a wrapper built on top of SDL_mixer with some changes and improvements and bugs fixed.<br>
 It supports XM,S3M,MOD,IT,WAV,VOC,AIFF and Vorbis OGG. <br>
 We advice you to use EditorDPF to add/delete sound and music tracks. <br>
 If you want to use it, you need to call Init() after CRM32Pro.Init(). <br>
 CRM32Pro.Init() builds this interface and CRM32Pro.Quit() removes it.  <br>
 - Created on 3 August 2001
 - Last modified on 23 June 2007*/
// ---------------------------------------------------------------------------
//! @{
#define ISOUNDFX_CHANNELS 8
#define ISOUNDFX_DEFAULT_FREQUENCY	22050
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
 #define ISOUNDFX_DEFAULT_FORMAT	AUDIO_S16LSB
#else
 #define ISOUNDFX_DEFAULT_FORMAT	AUDIO_S16MSB
#endif
#define ISOUNDFX_DEFAULT_CHANNELS	2
#define ISOUNDFX_MAX_VOLUME		128	

//! Audio type struct
typedef struct sAudioType
{
	char type[5];     //!< Wav Aiff Ogg Voc S3M XM Mod IT
	Uint8 channels;   //!< 1->mono 2->stereo
	Uint16 format;    //!< 8bit or 16bits	
	Uint32 freq;      //!< Frequency (11025,22050 or 44100)
	Uint32 size;      //!< Size (bytes)
} sAudioType;

//! ISoundFX
/*! Sound,music and FX effects interface.*/
class DllExport CRM32Pro_ISoundFX
{   
    public:
		// -Constructor-
		CRM32Pro_ISoundFX();
		// -Destructor-
		~CRM32Pro_ISoundFX();

        // -Initialize sound system-
		unsigned char Init(int frequency, unsigned short format, int channels,int chunksize);
		// -Try to initialize sound system according to CRM32Pro.Config-
		unsigned char Init();
        
		//! Turn off sound output
		void NoInit();
		//! Close sound system
		void Quit(void); 
		//! Was sound system activated?
		/*! \return 0 Is not active
		\return 1 Is active*/
		int Initialized();

		// -Query sound system features-
	    void QuerySpec(int *freq,unsigned short *format,int *ch);
		
		//! Dinamic change of channels
		void AllocateChannels(int nch);

		// -IO operations with music-
		int MusicLoad(const char *f);		
		int MusicLoad(char *fileDPF,char *musname);		        
		int MusicLoad(int idDPF,char *musname);		        
		int MusicImport(char *fileDPF,char *namemus,char *filemus);
		int MusicImport(int idDPF,char *namemus,char *filemus);
        unsigned char MusicInfo(char *fileDPF,char *namemus,sAudioType *mustype);
		unsigned char MusicInfo(int idDPF,char *namemus,sAudioType *mustype);
		void MusicFree(int hndMusic);

		// -IO operations with sound-
		int SoundLoad(const char *f);
		int SoundLoad(char *fileDPF,char *namesnd);				
		int SoundLoad(int idDPF,char *namesnd);				
		int SoundImport(char *fileDPF,char *namesnd,char *filesnd);
		int SoundImport(int idDPF,char *namesnd,char *filesnd);
		unsigned char SoundInfo(char *fileDPF,char *namesnd,sAudioType *sndtype); 				
		unsigned char SoundInfo(int idDPF,char *namesnd,sAudioType *sndtype); 				
        void SoundFree(int hndSound);		

		// -Exporting audio-
		unsigned char Export(char *fileDPF,char *namesnd,char m,char *s=NULL); 
		unsigned char Export(int idDPF,char *namesnd,char m,char *s=NULL); 

        // -Playing functions-
		void SoundPlay(int ch,int hndSound,int loops);
        int MusicPlay(int hndMusic,int loops); 

		//! Channel stop 
		/*! \param ch channel to stop*/
		void ChannelStop(int ch);
		//! Music stop
		void MusicStop(void);
		//! Channel pause 
		/*! \param ch channel to pause*/
        void ChannelPause(int ch);
		//! Channel resume 
		/*! \param ch channel to resume*/
		void ChannelResume(int ch);
        //! Query if a channel is paused 
		/*! \param ch channel to query its state
		\return 1 means a paused channel,otherwise is playing*/
		int ChannelIsPaused(int ch);
		//! Pause music
		void MusicPause(void);
		//! Resume music
		void MusicResume(void);
		//! Rewind music
		void MusicRewind(void);
        //! Query if music is paused 
		/*! \return 1 means a paused music,otherwise is playing*/  
        int MusicIsPaused(void);

		// -Volume control-
		void ChannelVolume(int ch,int vol);
		void SoundVolume(int hndSound,int vol);
		void MusicVolume(int vol);

		// -Fades In and Out-
		int ChannelFadeOut(int ch,int ms);
		int MusicFadeOut(int ms);
		int ChannelFadeIn(int ch, int hndSound,int loops,int ms);
		int MusicFadeIn(int hndMusic,int loops,int ms);

        // -Check playback-
        int IsPlaying(void);
		int IsPlaying(int ch);	
private:
		int IsSound;
};
//! @}

// ----------------External public interfaces declarations--------------------
extern CRM32Pro_Main         DllHandle   CRM32Pro;
extern CRM32Pro_ILogSystem   DllHandle   ILogSystem;
extern CRM32Pro_IStuffDPF    DllHandle   *IStuffDPF;
extern CRM32Pro_IImage       DllHandle   *IImage;
extern CRM32Pro_ICursor      DllHandle   *ICursor;
extern CRM32Pro_IPrimitives  DllHandle   *IPrimitives; 
extern CRM32Pro_IButton      DllHandle   *IButton; 
extern CRM32Pro_IScreenFX    DllHandle   *IScreenFX;
extern CRM32Pro_ITimeSystem  DllHandle   *ITimeSystem;
extern CRM32Pro_INetwork     DllHandle   *INetwork;
extern CRM32Pro_IVideo       DllHandle   *IVideo;
extern CRM32Pro_ISoundFX     DllHandle   *ISoundFX;

// -------------------------END OF CRM32Pro HEADER ----------------------------
#endif

#include "ReadAVI.h"	// WTF, ostream/fstream
#include <EMULATOR.H>
#include <EMULATOR_TIMER.H>
#include "DRIVER2.H"

#include "C/PAD.H"
#include "C/SYSTEM.H"
#include "C/E3STUFF.H"
#include "C/PAUSE.H"

#include "STRINGS.H"

#include <SDL_timer.h>
#include <AL/al.h>
#include <jpeglib.h>

struct UVWH
{
	uchar u, v;
	uchar w, h;
};

struct FMV_FONT
{
	uchar u, v;
	uchar w, h;
	short unk1;
};

// TODO: NEED SAVE
UVWH fontUV[256] = 
{
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 222, 18, 3, 18 }, { 22, 36, 5, 18 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 94, 54, 6, 18 }, { 70, 54, 3, 18 },
	{ 10, 36, 4, 18 }, { 16, 36, 4, 18 }, { 0, 0, 0, 0 }, { 34, 36, 6, 18 },
	{ 246, 18, 2, 18 }, { 28, 36, 4, 18 }, { 0, 36, 2, 18 }, { 4, 36, 5, 18 },
	{ 144, 18, 6, 18 }, { 152, 18, 4, 18 }, { 158, 18, 6, 18 }, { 166, 18, 6, 18 },
	{ 174, 18, 7, 18 }, { 182, 18, 6, 18 }, { 190, 18, 6, 18 }, { 198, 18, 6, 18 },
	{ 206, 18, 6, 18 }, { 214, 18, 6, 18 }, { 42, 36, 2, 18 }, { 66, 54, 3, 18 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 226, 18, 6, 18 },
	{ 0, 0, 0, 0 }, { 0, 0, 7, 18 }, { 8, 0, 6, 18 }, { 16, 0, 6, 18 },
	{ 24, 0, 6, 18 }, { 32, 0, 6, 18 }, { 40, 0, 5, 18 }, { 46, 0, 6, 18 },
	{ 54, 0, 6, 18 }, { 62, 0, 3, 18 }, { 66, 0, 6, 18 }, { 74, 0, 6, 18 },
	{ 82, 0, 5, 18 }, { 88, 0, 9, 18 }, { 98, 0, 6, 18 }, { 106, 0, 6, 18 },
	{ 114, 0, 6, 18 }, { 122, 0, 6, 18 }, { 130, 0, 7, 18 }, { 138, 0, 7, 18 },
	{ 146, 0, 6, 18 }, { 154, 0, 6, 18 }, { 162, 0, 7, 18 }, { 170, 0, 10, 18 },
	{ 182, 0, 7, 18 }, { 190, 0, 7, 18 }, { 198, 0, 6, 18 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 206, 0, 6, 18 }, { 214, 0, 6, 18 }, { 222, 0, 5, 18 },
	{ 228, 0, 5, 18 }, { 234, 0, 6, 18 }, { 242, 0, 5, 18 }, { 248, 0, 6, 18 },
	{ 0, 18, 6, 18 }, { 8, 18, 3, 18 }, { 12, 18, 4, 18 }, { 18, 18, 6, 18 },
	{ 26, 18, 3, 18 }, { 30, 18, 9, 18 }, { 40, 18, 6, 18 }, { 48, 18, 6, 18 },
	{ 56, 18, 6, 18 }, { 64, 18, 6, 18 }, { 72, 18, 6, 18 }, { 80, 18, 6, 18 },
	{ 88, 18, 5, 18 }, { 94, 18, 6, 18 }, { 102, 18, 7, 18 }, { 110, 18, 9, 18 },
	{ 120, 18, 6, 18 }, { 128, 18, 7, 18 }, { 136, 18, 6, 18 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 238, 18, 6, 18 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 38, 54, 3, 18 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 30, 54, 6, 18 },
	{ 50, 36, 8, 18 }, { 60, 36, 7, 18 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 68, 36, 7, 18 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 152, 36, 6, 18 },
	{ 76, 36, 5, 18 }, { 82, 36, 5, 18 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 88, 36, 3, 18 }, { 92, 36, 3, 18 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 144, 36, 7, 18 }, { 96, 36, 6, 18 }, { 104, 36, 7, 18 },
	{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 112, 36, 6, 18 }, { 0, 0, 0, 0 },
	{ 120, 36, 7, 18 }, { 0, 0, 0, 0 }, { 128, 36, 6, 18 }, { 0, 0, 0, 0 },
	{ 136, 36, 6, 18 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 22, 54, 7, 18 },
	{ 160, 36, 5, 18 }, { 166, 36, 6, 18 }, { 0, 54, 5, 18 }, { 0, 0, 0, 0 },
	{ 174, 36, 5, 18 }, { 0, 0, 0, 0 }, { 84, 54, 8, 18 }, { 250, 36, 5, 18 },
	{ 180, 36, 6, 18 }, { 188, 36, 6, 18 }, { 6, 54, 6, 18 }, { 0, 0, 0, 0 },
	{ 196, 36, 3, 18 }, { 200, 36, 3, 18 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 50, 54, 6, 18 }, { 204, 36, 6, 18 }, { 212, 36, 6, 18 },
	{ 58, 54, 6, 18 }, { 0, 0, 0, 0 }, { 220, 36, 6, 18 }, { 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }, { 228, 36, 6, 18 }, { 236, 36, 6, 18 }, { 14, 54, 6, 18 },
	{ 244, 36, 5, 18 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }
};

FMV_FONT font[256];

// Partially decompiled function from FMV EXE
void InitFMVFont()
{
	int i;
	RECT16 fontRect;

	Loadfile("FMV\\FONT.TIM", _other_buffer);

	//fontRect.x = 512;
	//fontRect.y = 0;
	//fontRect.w = 384;
	//fontRect.h = 72;

	//DrawSync(0);
	//LoadImage2(&fontRect,(u_long *)(_other_buffer + 20));
	//DrawSync(0);

	DrawSync(0);
	LoadClut((u_long *)(_other_buffer + 20),960,72);
	DrawSync(0);

	fontRect.x = 960;
	fontRect.y = 0;
	fontRect.w = 64;
	fontRect.h = 72;

	LoadImage2(&fontRect,(u_long *)(_other_buffer + 64));
	DrawSync(0);

	/*
	i = 0;
	while (i < 256) 
	{
		font[i].u = fontUV[i].u + (fontUV[i].u >> 1);
		font[i].w = fontUV[i].w + (fontUV[i].w >> 1);
	
		if (fontUV[i].w & 1)
			font[i].w += 1;
	
		if (i == 46) 
			font[i].w += 1;

		if (font[i].u + font[i].w < 256)
		{
			font[i].unk1 = 0x108;
		}
		else if (font[i].u >= 256) 
		{
			font[i].unk1 = 0x10c;
		}
		else if (font[i].u + font[i].w > 255) 
		{
			font[i].unk1 = 0x109;
			font[i].u -= 64;
		}

		//font[i].u = local_14;
		font[i].v = fontUV[i].v;
		font[i].h = fontUV[i].h;
		i = i + 1;
	}

	font[180].u = font[39].u;
	font[180].v = font[39].v;
	font[180].unk1 = font[39].unk1;
	font[146].u = font[39].u;
	font[146].v = font[39].v;
	font[146].unk1 = font[39].unk1;
	*/

	i = 0;
	while (i < 256)
	{
		font[i].u = fontUV[i].u;
		font[i].v = fontUV[i].v;
		font[i].w = fontUV[i].w;
		font[i].h = fontUV[i].h;
		i++;
	}
}

POLY_FT4 fmvTextPolys[512];

// partially decompiled
void PrintFMVText(char *str, int x, short y, int brightness)
{
	char chr;
	char *ptr;
	int x_ofs;
	int i;
	int str_w;
	int drawnChars;
	OTTYPE ot;
	POLY_FT4* poly;

	ClearOTagR((ulong*)&ot, 1);
	poly = fmvTextPolys;

	str_w = 0;

	if (brightness > 128) 
		brightness = 128;

	i = 0;
	while (chr = str[i], chr != 0) 
	{
		if (chr == 32)
			str_w += 4;
		else
			str_w += font[chr].w;
		i++;
	}

	x_ofs = x - str_w / 2;

	drawnChars = 0;

	ptr = (char *)str;
	while( true )
	{
		chr = *ptr;
		ptr++;
	
		if (chr == 0 || drawnChars > 511) 
			break;
		
		if (chr == 32)	// space
		{
			x_ofs += 4;
		}
		else
		{
			setPolyFT4(poly);
			
			poly->x0 = x_ofs;
			poly->y0 = y;
			poly->x1 = x_ofs + font[chr].w;
			poly->y1 = y;
			poly->x2 = x_ofs;
			poly->y2 = y + font[chr].h;
			poly->x3 = x_ofs + font[chr].w;
			poly->y3 = y + font[chr].h;
			poly->u0 = font[chr].u;
			poly->v0 = font[chr].v;
			poly->u1 = font[chr].u + font[chr].w;
			poly->v1 = font[chr].v;
			poly->u2 = font[chr].u;
			poly->v2 = font[chr].v + font[chr].h;
			poly->u3 = font[chr].u + font[chr].w;
			poly->v3 = font[chr].v + font[chr].h;
			poly->tpage = getTPage(0,0, 960, 0);
			poly->clut = getClut(960, 72);

			poly->r0 = brightness;
			poly->g0 = brightness;
			poly->b0 = brightness;

			addPrim(&ot, poly);
			
			x_ofs += font[chr].w;
			drawnChars++;
			poly++;
		}
	}

	DrawOTag((ulong*)&ot);
}

int UnpackJPEG(unsigned char* src_buf, unsigned src_length, unsigned bpp, unsigned char* dst_buf)
{
	// it's rough but it works...
	jpeg_decompress_struct cinfo;
	jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	jpeg_mem_src(&cinfo, src_buf, src_length);
	jpeg_read_header(&cinfo, TRUE);
	jpeg_start_decompress(&cinfo);

	for (u_char* curr_scanline = dst_buf; cinfo.output_scanline < cinfo.output_height; curr_scanline += cinfo.output_width * cinfo.num_components)
	{
		jpeg_read_scanlines(&cinfo, &curr_scanline, 1);
	}

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	return 0;
}

// emulator window TODO: interface
extern int g_swapInterval;

void SetupMovieRectangle(ReadAVI::stream_format_t& strFmt)
{
	int windowWidth, windowHeight;
	Emulator_GetScreenSize(windowWidth, windowHeight);

	float psxScreenW = 320.0f;
	float psxScreenH = 240.0f;

	int ideal_image_height = strFmt.image_height; // strFmt.image_height;

	if (ideal_image_height < 220)
		ideal_image_height = 220;

	RECT16 rect;
	rect.x = 0;
	rect.y = (psxScreenH - ideal_image_height);// / 2;
	rect.w = strFmt.image_width;
	rect.h = ideal_image_height;

	const float video_aspect = float(strFmt.image_width) / float(ideal_image_height);
	float emuScreenAspect = float(windowHeight) / float(windowWidth);

	// first map to 0..1
	float clipRectX = (float)(rect.x) / psxScreenW;
	float clipRectY = (float)(rect.y) / psxScreenH;
	float clipRectW = (float)(rect.w) / psxScreenW;
	float clipRectH = (float)(rect.h) / psxScreenH;

	// then map to screen
	clipRectY -= 1.0f;
	clipRectX -= 1.0f;

	clipRectY /= video_aspect * emuScreenAspect;
	clipRectH /= emuScreenAspect * video_aspect;

	clipRectW *= 2.0f;
	clipRectH *= 2.0f;

	u_char l = 0;
	u_char t = 0;
	u_char r = 1;
	u_char b = 1;

	Vertex blit_vertices[] =
	{
		{ clipRectX+ clipRectW,  clipRectY + clipRectH,    0, 0,    r, t,    0, 0,    0, 0, 0, 0 },
		{ clipRectX, clipRectY,    0, 0,    l, b,    0, 0,    0, 0, 0, 0 },
		{ clipRectX, clipRectY + clipRectH,    0, 0,    l, t,    0, 0,    0, 0, 0, 0 },

		{ clipRectX + clipRectW, clipRectY,    0, 0,    r, b,    0, 0,    0, 0, 0, 0 },
		{ clipRectX, clipRectY,    0, 0,    l, b,    0, 0,    0, 0, 0, 0 },
		{ clipRectX + clipRectW,  clipRectY + clipRectH,    0, 0,    r, t,    0, 0,    0, 0, 0, 0 },
	};

	Emulator_UpdateVertexBuffer(blit_vertices, 6);
}

// send audio buffer
void QueueAudioBuffer(ALuint buffer, ALuint source, ReadAVI::frame_entry_t& frame_entry, ReadAVI::stream_format_auds_t& audio_format, int frame_offset, int frame_size)
{
	ALenum alFormat;

	if (audio_format.block_size_of_data == 8)
		alFormat = audio_format.channels == 2 ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;
	else if (audio_format.block_size_of_data == 16)
		alFormat = audio_format.channels == 2 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
	else
		alFormat = AL_FORMAT_MONO16;

	// upload to specific buffer
	alBufferData(buffer, alFormat, frame_entry.buf + frame_offset, frame_size, audio_format.samples_per_second);

	// queue after uploading
	alSourceQueueBuffers(source, 1, &buffer);
}

const char* fmv_shader =
	"varying vec4 v_texcoord;\n"
	"#ifdef VERTEX\n"
	"	attribute vec4 a_position;\n"
	"	attribute vec4 a_texcoord;\n"
	"	void main() {\n"
	"		v_texcoord = a_texcoord;\n"
	"		gl_Position = vec4(a_position.xy, 0.0, 1.0);\n"
	"	}\n"
	"#else\n"
	"	uniform sampler2D s_texture;\n"
	"	void main() {\n"
	"		fragColor = texture2D(s_texture, v_texcoord.xy);\n"
	"	}\n"
	"#endif\n";

TextureID g_FMVTexture = 0;
ShaderID g_FMVShader = 0;

extern void Shader_CheckShaderStatus(GLuint shader);
extern void Shader_CheckProgramStatus(GLuint program);
extern ShaderID Shader_Compile(const char* source);
extern void Emulator_SetShader(const ShaderID& shader);

void FMVPlayerInitGL()
{
#if defined(OGL) || defined(OGLES)
	glGenTextures(1, &g_FMVTexture);

	glBindTexture(GL_TEXTURE_2D, g_FMVTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 320, 240, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);

	if(!g_FMVShader)
		g_FMVShader = Shader_Compile(fmv_shader);
#endif
}

void FMVPlayerShutdownGL()
{
	RECT16 rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 512;
	rect.h = 256;

	ClearImage(&rect, 0, 0, 0);
	Emulator_SwapWindow();

	Emulator_DestroyTexture(g_FMVTexture);
}

struct SUBTITLE
{
	ushort startframe;
	ushort endframe;
	ushort x;
	ushort y;
	ushort unk3;
	ushort unk4;
	char text[32];
};

SUBTITLE g_Subtitles[128];
int g_NumSubtitles = 0;

void InitSubtitles(const char* filename)
{
	g_NumSubtitles = 0;
	FILE* subFile = fopen(filename, "rb");
	if (subFile)
	{
		fread(&g_NumSubtitles, sizeof(int), 1, subFile);

		fread(g_Subtitles, sizeof(g_Subtitles), g_NumSubtitles, subFile);

		fclose(subFile);
	}
}

char* g_CreditsBuffer = NULL;
char* g_CreditsLines[512];

void InitCredits(const char* filename)
{
	memset(g_CreditsLines, 0, sizeof(g_CreditsLines));
	
	FILE* credFile = fopen(filename, "rb");
	if (credFile)
	{
		fseek(credFile, 0, SEEK_END);
		int credits_buffer_size = ftell(credFile);
		fseek(credFile, 0, SEEK_SET);

		g_CreditsBuffer = (char*)malloc(credits_buffer_size + 1);

		fread(g_CreditsBuffer, 1, credits_buffer_size, credFile);
		g_CreditsBuffer[credits_buffer_size] = 0;

		fclose(credFile);
	}

	if(g_CreditsBuffer)
	{
		// make credits into lines
		char* str = g_CreditsBuffer;
		int numCreditsLines = 0;

		while(*str)
		{
			if(!g_CreditsLines[numCreditsLines])
				g_CreditsLines[numCreditsLines] = str;
			
			if(*str == '\r')
			{
				*str = '\0';
				
				if (*++str == '\n')
					numCreditsLines++;
			}
			else if(*str == '\n')
			{
				*str = '\0';
				numCreditsLines++;
			}
			
			str++;
		}
	}
}

void PrintSubtitleText(SUBTITLE* sub)
{
	char* str = sub->text;

	// skip some trailing spaces
	while (isspace(*str)) {
		str++;
	}

	PrintFMVText(str, 256, sub->y - 25, 128);
}

void DisplaySubtitles(int frame_number)
{
	// draw subtitie text
	for (int i = 0; i < g_NumSubtitles; i++)
	{
		if(frame_number >= g_Subtitles[i].startframe && frame_number <= g_Subtitles[i].endframe)
			PrintSubtitleText(&g_Subtitles[i]);
	}
}

#define CREDITS_START_FRAME				700
#define CREDITS_STOP_FRAME				5450
#define CREDITS_FADE_START_FRAME		5900

void DisplayCredits(int frame_number)
{
	int i;

	int frame = frame_number;

	if (frame > CREDITS_STOP_FRAME)
		frame = CREDITS_STOP_FRAME;
	
	int height = (frame - CREDITS_START_FRAME) * 30 >> 5;

	int fade = 0;
	if (frame_number > CREDITS_FADE_START_FRAME)
	{
		fade = (frame_number - CREDITS_FADE_START_FRAME) * 2;
		if (fade > 128)
			fade = 128;
	}

	for(i = 0; i < 512; i++)
	{
		int text_h = 250 - height + i * 16;
		
		if (text_h < -20 || text_h > 260)
			continue;
		
		char* str = g_CreditsLines[i];

		if(str)
			PrintFMVText(str, 256, text_h, 128 - fade);
	}
}

extern void Emulator_Ortho2D(float left, float right, float bottom, float top, float znear, float zfar);

void DrawFrame(ReadAVI::stream_format_t& stream_format, int frame_number, int credits)
{
	int windowWidth, windowHeight;
	Emulator_GetScreenSize(windowWidth, windowHeight);

	Emulator_BeginScene();

	Emulator_Clear(0, 0, windowWidth, windowHeight, 0, 0, 0);

	glBindTexture(GL_TEXTURE_2D, g_FMVTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, stream_format.image_width, stream_format.image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, _frontend_buffer);
	
	Emulator_SetViewPort(0, 0, windowWidth, windowHeight);
	Emulator_SetTexture(g_FMVTexture, (TexFormat)-1);
	Emulator_SetShader(g_FMVShader);

	SetupMovieRectangle(stream_format);

	Emulator_SetBlendMode(BM_NONE);
	Emulator_DrawTriangles(0, 2);

	DisplaySubtitles(frame_number);

	if(credits && frame_number >= CREDITS_START_FRAME)
	{
		DisplayCredits(frame_number);
	}

	Emulator_EndScene();
}

void DoPlayFMV(RENDER_ARG* arg, int subtitles)
{
	int fd = arg->render - (arg->render % 10);
	if (fd > 0)
		fd /= 10;

	char filename[250];
	sprintf(filename, "%sFMV\\%d\\RENDER%d.STR[0].AVI", gDataFolder, fd, arg->render);

	ReadAVI readAVI(filename);
	
	// also load subtitle file
	if (subtitles)
	{
		sprintf(filename, "%sFMV\\%d\\RENDER%d.SBN", gDataFolder, fd, arg->render);
		InitSubtitles(filename);
	}
	else
	{
		g_NumSubtitles = 0;
	}

	if(arg->credits)
	{
		sprintf(filename, "%sDATA\\CREDITS.ENG", gDataFolder);
		InitCredits(filename);
	}

	ReadAVI::avi_header_t avi_header = readAVI.GetAviHeader();

	ReadAVI::stream_format_t stream_format = readAVI.GetVideoFormat();
	ReadAVI::stream_format_auds_t audio_format = readAVI.GetAudioFormat();

	if (strcmp(stream_format.compression_type, "MJPG")) {
		printf("Only MJPG supported\n");
		return;
	}

	ReadAVI::frame_entry_t frame_entry;
	frame_entry.type = (ReadAVI::chunk_type_t)(ReadAVI::ctype_video_data | ReadAVI::ctype_audio_data);
	frame_entry.pointer = 0;

	ALuint audioStreamSource;
	ALuint audioStreamBuffers[4];

	alGenSources(1, &audioStreamSource);
	alGenBuffers(4, audioStreamBuffers);
	alSourcei(audioStreamSource, AL_LOOPING, AL_FALSE);

	timerCtx_t fmvTimer;

	Emulator_InitHPCTimer(&fmvTimer);

	double nextFrameDelay = 0.0;

	int frame_size;
	int queue_counter = 0;

	int fade_out = 0;
	int done_frames = 0;

	Emulator_GetHPCTime(&fmvTimer, 1);
	
	// main loop
	while (true)
	{
		double delta = Emulator_GetHPCTime(&fmvTimer, 1);

		if (delta > 1.0)
			delta = 0.0;

		nextFrameDelay -= delta;

		if (nextFrameDelay > 0) // wait for frame
		{
			Emulator_EndScene();
			continue;
		}

		frame_entry.type = (ReadAVI::chunk_type_t)(ReadAVI::ctype_video_data | ReadAVI::ctype_audio_data);
		frame_size = readAVI.GetFrameFromIndex(&frame_entry);

		// done, no frames
		if (frame_size < 0)
			break;

		// handle recap
		if(arg->recap && done_frames > arg->recap)
			break;

		// fade out sound and stop playback
		if (fade_out > 0)
		{
			fade_out -= 18;
			if (fade_out < 0)
				break;

			alSourcef(audioStreamSource, AL_GAIN, float(fade_out) / 255.0);
		}

		if (frame_size > 0)
		{
			if (frame_entry.type == ReadAVI::ctype_compressed_video_frame)
			{
				// Do video frame
				int ret = UnpackJPEG(frame_entry.buf, frame_size, stream_format.bits_per_pixel, (unsigned char*)_frontend_buffer);

				if (ret == 0)
				{
					DrawFrame(stream_format, done_frames, arg->credits);
				}

				// set next step time
				if (g_swapInterval == 1)
					nextFrameDelay += double(avi_header.TimeBetweenFrames) / 1000000.0;
				else
					nextFrameDelay = 0.0;
				
				done_frames++;
			}
			else if (frame_entry.type == ReadAVI::ctype_audio_data)
			{
				// Update audio buffer
				ALint state;
				alGetSourcei(audioStreamSource, AL_SOURCE_STATE, &state);

				int numProcessed = 0;
				alGetSourcei(audioStreamSource, AL_BUFFERS_PROCESSED, &numProcessed);

				if (state == AL_STOPPED || numProcessed > 0)
				{
					ALuint qbuffer;

					// stop queued
					if (state == AL_STOPPED)
					{
						alGetSourcei(audioStreamSource, AL_BUFFERS_QUEUED, &numProcessed);

						// dequeue all buffers for restarting
						while (numProcessed--)
							alSourceUnqueueBuffers(audioStreamSource, 1, &qbuffer);

						// restart
						queue_counter = 0;
					}
					else if(numProcessed && queue_counter > 3)
					{
						// dequeue one buffer
						alSourceUnqueueBuffers(audioStreamSource, 1, &qbuffer);
						QueueAudioBuffer(qbuffer, audioStreamSource, frame_entry, audio_format, 0, frame_size);
					}
				}

				// for starting only
				if (queue_counter < 4)
					QueueAudioBuffer(audioStreamBuffers[queue_counter++], audioStreamSource, frame_entry, audio_format, 0, frame_size);

				if((queue_counter > 1 || numProcessed == -1) && state != AL_PLAYING)
					alSourcePlay(audioStreamSource);
			}
		}

		ReadControllers();

		// exit
		if (fade_out == 0 && Pads[0].mapnew > 0)
			fade_out = 255;
	}

	alDeleteSources(1, &audioStreamSource);
	alDeleteBuffers(2, audioStreamBuffers);
}

// FMV main function
int FMV_main(RENDER_ARGS* args)
{
	DISPENV disp;
	DRAWENV draw;

	FMVPlayerInitGL();
	//LoadFont(NULL);

	InitFMVFont();

	SetupDefDrawEnv(&draw, 0, 0, 512, 256);
	SetupDefDispEnv(&disp, 0, 0, 512, 256);

	draw.dfe = 1;

	draw.clip.x = -512;
	draw.clip.w = 1200;
	draw.clip.y = -1;
	draw.clip.h = 512;
	
	disp.isinter = 0;

	PutDrawEnv(&draw);
	PutDispEnv(&disp);

	Emulator_SetupClipMode(draw.clip);

	for (int i = 0; i < args->nRenders; i++)
	{
		DoPlayFMV(&args->Args[i], args->subtitle);
	}

	FMVPlayerShutdownGL();

	if (g_CreditsBuffer)
		free(g_CreditsBuffer);
	g_CreditsBuffer = NULL;

	return 0;
}


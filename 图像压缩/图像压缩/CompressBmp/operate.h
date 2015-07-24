#ifndef _OPERATE_H
#define _OPERATE_H
#include <windows.h>
#include <stdio.h>


class compress
{
public:
	bool comp(CString filename,CProgressCtrl *pro1);
	bool uncomp(CString bfilename,CString efilename,CProgressCtrl *pro1);
	short getsize(BYTE a);
	void Vbits(int l[],BYTE b[],int n,int s[],int kay[]);
	UINT atou(CString  str);
	CString btoa(BYTE a,BYTE ps);
	BYTE  atob(CString str);
	CString utoa(UINT c,int m1);
	//bool comp();
	//bool uncomp();
private:
	BYTE*	m_data;			// Image byte data
	int		m_bpp;			// Image color depth in bits per pixel
	int		m_width;		// Image width
	int		m_height;		// Image height
	bool		m_MipMap;
	/*GLfloat		m_MinFilter;
	GLfloat		m_MaxFilter;
	GLint		m_SWrap;
	GLint		m_TWrap;
	GLuint		m_TexID;*/		// Texture id used to select a texture
};

#endif
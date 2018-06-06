#ifndef _SCENE_SEGMENTATION_EXTERNAL_H_INCLUDE_
#define _SCENE_SEGMENTATION_EXTERNAL_H_INCLUDE_

class CIplFrame;
typedef		LPVOID		HSSENGINE;
// 샷 추가시 호출 할 함수
typedef void (CALLBACK * PROCTYPE_AddShot )(double dblSampleTime, int nFrameNo, LPBITMAPINFOHEADER lpBih, LPBYTE lpData, int nDataSize, DWORD_PTR dwUserData);

// 장면 추가시 호출 할 함수
typedef void (CALLBACK * PROCTYPE_AddScene)(int nShotIndex, DWORD_PTR dwUserData);


typedef HSSENGINE (WINAPI* LPFN_SS_CREATE            )();
typedef BOOL	  (WINAPI* LPFN_SS_DESTORY           )(HSSENGINE hSSEngine);
typedef void	  (WINAPI* LPFN_SS_INITIALIZE        )(HSSENGINE hSSEngine);
typedef void	  (WINAPI* LPFN_SS_SETFRAMEINFO      )(HSSENGINE hSSEngine, LPBITMAPINFOHEADER lpBih);
typedef int		  (WINAPI* LPFN_SS_SETFRAMEDATA      )(HSSENGINE hSSEngine, double dblSampleTime, int nFrameNo, LPBYTE lpData, int nDataSize);
typedef int		  (WINAPI* LPFN_SS_SETIPLFRAMEDATA   )(HSSENGINE hSSEngine, double dblSampleTime, int nFrameNo, CIplFrame* pFrame);
typedef UINT	  (WINAPI* LPFN_SS_GETCURRENTFRAME   )(HSSENGINE hSSEngine);
typedef double	  (WINAPI* LPFN_SS_GETCURRENTTIME    )(HSSENGINE hSSEngine);
typedef void	  (WINAPI* LPFN_SS_ENDFRAMEDATA      )(HSSENGINE hSSEngine);
typedef BOOL	  (WINAPI* LPFN_SS_SAVESTATE         )(HSSENGINE hSSEngine, LPCTSTR lpszPath);
typedef BOOL	  (WINAPI* LPFN_SS_LOADSTATE         )(HSSENGINE hSSEngine, LPCTSTR lpszPath);
typedef void	  (WINAPI* LPFN_SS_SETUSERDATA       )(HSSENGINE hSSEngine, DWORD_PTR dwUserData);
typedef void	  (WINAPI* LPFN_SS_SETADDSHOTPROC    )(HSSENGINE hSSEngine, PROCTYPE_AddShot pfnAddShot);
typedef void	  (WINAPI* LPFN_SS_SETADDSCENEPROC   )(HSSENGINE hSSEngine, PROCTYPE_AddScene pfnAddScene);
typedef INT       (WINAPI* LPFN_SS_GETREALFRAMEGAP   )(HSSENGINE hSSEngine);
typedef INT       (WINAPI* LPFN_SS_GETFRAMEWINDOWSIZE)(HSSENGINE hSSEngine);
typedef void      (WINAPI* LPFN_SS_SETSENSITIVE      )(HSSENGINE hSSEngine, const UINT& nSensitive );

typedef struct tagSceneSegAIP
{
	LPFN_SS_CREATE             lpfnCREATE            ;
	LPFN_SS_DESTORY            lpfnDESTORY           ;
	LPFN_SS_INITIALIZE         lpfnINITIALIZE        ;
	LPFN_SS_SETFRAMEINFO       lpfnSETFRAMEINFO      ;
	LPFN_SS_SETFRAMEDATA       lpfnSETFRAMEDATA      ;
	LPFN_SS_SETIPLFRAMEDATA    lpfnSETIPLFRAMEDATA   ;
	LPFN_SS_GETCURRENTFRAME    lpfnGETCURRENTFRAME   ;
	LPFN_SS_GETCURRENTTIME     lpfnGETCURRENTTIME    ;
	LPFN_SS_ENDFRAMEDATA       lpfnENDFRAMEDATA      ;
	LPFN_SS_SAVESTATE          lpfnSAVESTATE         ;
	LPFN_SS_LOADSTATE          lpfnLOADSTATE         ;
	LPFN_SS_SETUSERDATA        lpfnSETUSERDATA       ;
	LPFN_SS_SETADDSHOTPROC     lpfnSETADDSHOTPROC    ;
	LPFN_SS_SETADDSCENEPROC    lpfnSETADDSCENEPROC   ;
	LPFN_SS_GETREALFRAMEGAP    lpfnGETREALFRAMEGAP   ;
	LPFN_SS_GETFRAMEWINDOWSIZE lpfnGETFRAMEWINDOWSIZE;
	LPFN_SS_SETSENSITIVE       lpfnSETSENSITIVE      ;
}SCENE_SEG_API, *LPSCENE_SEG_API;



#define SS_FN_NAME_CREATE             ("SS_Create"            )
#define SS_FN_NAME_DESTORY            ("SS_Destroy"           )
#define SS_FN_NAME_INITIALIZE         ("SS_Initialize"        )
#define SS_FN_NAME_SETFRAMEINFO       ("SS_SetFrameInfo"      )
#define SS_FN_NAME_SETFRAMEDATA       ("SS_SetFrameData"      )
#define SS_FN_NAME_SETIPLFRAMEDATA    ("SS_SetIplFrameData"   )
#define SS_FN_NAME_GETCURRENTFRAME    ("SS_GetCurrentFrame"   )
#define SS_FN_NAME_GETCURRENTTIME     ("SS_GetCurrentTime"    )
#define SS_FN_NAME_ENDFRAMEDATA       ("SS_EndFrameData"      )
#define SS_FN_NAME_SAVESTATE          ("SS_SaveState"         )
#define SS_FN_NAME_LOADSTATE          ("SS_LoadState"         )
#define SS_FN_NAME_SETUSERDATA        ("SS_SetUserData"       )
#define SS_FN_NAME_SETADDSHOTPROC     ("SS_SetAddShotProc"    )
#define SS_FN_NAME_SETADDSCENEPROC    ("SS_SetAddSceneProc"   )
#define SS_FN_NAME_GETREALFRAMEGAP    ("SS_GetRealFrameGap"   )
#define SS_FN_NAME_GETFRAMEWINDOWSIZE ("SS_GetFrameWindowSize")
#define SS_FN_NAME_SETSENSITIVE       ("SS_SetSensitive"      )

#ifdef _DEBUG
	#ifdef UNICODE
		#define _SCENE_SEGMENT_DLL_CDECL_NAME  _T("SceneSegmentationUD_CDECL.dll")
	#else
		#define _SCENE_SEGMENT_DLL_CDECL_NAME  _T("SceneSegmentationD_CDECL.dll")
	#endif
#else
	#ifdef UNICODE
		#ifdef _OPENMP
			#define _SCENE_SEGMENT_DLL_CDECL_NAME  _T("SceneSegmentationU_CDECLOMP.dll")
		#else
			#define _SCENE_SEGMENT_DLL_CDECL_NAME  _T("SceneSegmentationU_CDECL.dll")
		#endif
	#else
		#define _SCENE_SEGMENT_DLL_CDECL_NAME  _T("SceneSegmentation_CDECL.dll")
	#endif
#endif

#ifdef _DEBUG
	#ifdef UNICODE
		#ifdef _OPENMP
			#define _SCENE_SEGMENT_DLL_STDCALL_NAME  _T("SceneSegmentationUD_STDCALLOMP.dll")
		#else
			#define _SCENE_SEGMENT_DLL_STDCALL_NAME  _T("SceneSegmentationUD_STDCALL.dll")
		#endif
	#else
		#define _SCENE_SEGMENT_DLL_STDCALL_NAME  _T("SceneSegmentationD_STDCALL.dll")
	#endif
#else
	#ifdef UNICODE
		#ifdef _OPENMP
			#define _SCENE_SEGMENT_DLL_STDCALL_NAME  _T("SceneSegmentationU_STDCALLOMP.dll")
		#else
			#define _SCENE_SEGMENT_DLL_STDCALL_NAME  _T("SceneSegmentationU_STDCALL.dll")
		#endif
	#else
		#define _SCENE_SEGMENT_DLL_STDCALL_NAME  _T("SceneSegmentation_STDCALL.dll")
	#endif
#endif


HSSENGINE WINAPI SS_Create            (); // 장면분할모듈을 생성
BOOL	  WINAPI SS_Destroy           (HSSENGINE hSSEngine);// 장면분할모듈을 파괴.
void	  WINAPI SS_Initialize        (HSSENGINE hSSEngine);// 초기화 진행
void	  WINAPI SS_SetFrameInfo      (HSSENGINE hSSEngine, LPBITMAPINFOHEADER lpBih);// Frame 정보를 설정.
int		  WINAPI SS_SetFrameData      (HSSENGINE hSSEngine, double dblSampleTime, int nFrameNo, LPBYTE lpData, int nDataSize);//비디오 스트림 입력
int		  WINAPI SS_SetIplFrameData   (HSSENGINE hSSEngine, double dblSampleTime, int nFrameNo, CIplFrame* pFrame);//비디오 스트림 입력.
UINT	  WINAPI SS_GetCurrentFrame   (HSSENGINE hSSEngine);// 현재 프레임 번호를 얻는다.
double	  WINAPI SS_GetCurrentTime    (HSSENGINE hSSEngine);// 현재 시간을 얻는다.
void	  WINAPI SS_EndFrameData      (HSSENGINE hSSEngine);// 프레임 자료가 끝났다.
BOOL	  WINAPI SS_SaveState         (HSSENGINE hSSEngine, LPCTSTR lpszPath);// 현재 상태를 보관한다.
BOOL	  WINAPI SS_LoadState         (HSSENGINE hSSEngine, LPCTSTR lpszPath);// 파일에서 상태를 로딩.
void	  WINAPI SS_SetUserData       (HSSENGINE hSSEngine, DWORD_PTR dwUserData);// 사용자 자료를 설정한다.
void	  WINAPI SS_SetAddShotProc    (HSSENGINE hSSEngine, PROCTYPE_AddShot pfnAddShot);// 샷 추가시 호출 할 콜백함수 설정
void	  WINAPI SS_SetAddSceneProc   (HSSENGINE hSSEngine, PROCTYPE_AddScene pfnAddScene);// 장면 추가시 호출 할 콜백함수 설정
INT       WINAPI SS_GetRealFrameGap   (HSSENGINE hSSEngine);
INT       WINAPI SS_GetFrameWindowSize(HSSENGINE hSSEngine);//return process frame window size
void      WINAPI SS_SetSensitive      (HSSENGINE hSSEngine, const UINT& nSensitive );//장면 분할 민감도 설정, // 1<=nSensitive<=9


#endif//_SCENE_SEGMENTATION_EXTERNAL_H_INCLUDE_
ORIGIN = PWB
ORIGIN_VER = 2.0
PROJ = JRT
PROJFILE = JRT.MAK
DEBUG = 1

BSCMAKE  = bscmake
SBRPACK  = sbrpack
NMAKEBSC1  = set
NMAKEBSC2  = nmake
CC  = cl
CFLAGS_G  = /AL /W2 /BATCH
CFLAGS_D  = /f /Od /Zi
CFLAGS_R  = /f- /Ot /Ol /Og /Oe /Oi /Gs
CXX  = cl
CXXFLAGS_G  = /W2 /BATCH
CXXFLAGS_D  = /f /Zi /Od
CXXFLAGS_R  = /f- /Ot /Oi /Ol /Oe /Og /Gs
MAPFILE_D  = NUL
MAPFILE_R  = NUL
LFLAGS_G  = /NOI /BATCH /ONERROR:NOEXE
LFLAGS_D  = /CO /FAR /PACKC
LFLAGS_R  = /EXE /FAR /PACKC
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL
ILFLAGS  = /a /e
BROWSE	= 0
PACK_SBRS  = 1

FILES  = DEL.C DIALOG.C HISTORY.C MAIN.C NEW.C NOW.C SELECT.C SETUP.C
OBJS  = DEL.obj DIALOG.obj HISTORY.obj MAIN.obj NEW.obj NOW.obj SELECT.obj\
	SETUP.obj
SBRS  = DEL.sbr DIALOG.sbr HISTORY.sbr MAIN.sbr NEW.sbr NOW.sbr SELECT.sbr\
	SETUP.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .sbr .obj .c

DEL.obj : DEL.C c:\boy20\include\boywin.h c:\boy20\include\key.h jrtz.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoDEL.obj DEL.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoDEL.obj DEL.C
<<
!ENDIF

DEL.sbr : DEL.C c:\boy20\include\boywin.h c:\boy20\include\key.h jrtz.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRDEL.sbr DEL.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRDEL.sbr DEL.C
<<
!ENDIF

DIALOG.obj : DIALOG.C c:\boy20\include\boywin.h c:\boy20\include\key.h\
	c:\boy20\include\dialog.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoDIALOG.obj DIALOG.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoDIALOG.obj DIALOG.C
<<
!ENDIF

DIALOG.sbr : DIALOG.C c:\boy20\include\boywin.h c:\boy20\include\key.h\
	c:\boy20\include\dialog.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRDIALOG.sbr DIALOG.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRDIALOG.sbr DIALOG.C
<<
!ENDIF

HISTORY.obj : HISTORY.C c:\boy20\include\boywin.h c:\boy20\include\key.h\
	jrtz.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoHISTORY.obj HISTORY.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoHISTORY.obj HISTORY.C
<<
!ENDIF

HISTORY.sbr : HISTORY.C c:\boy20\include\boywin.h c:\boy20\include\key.h\
	jrtz.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRHISTORY.sbr HISTORY.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRHISTORY.sbr HISTORY.C
<<
!ENDIF

MAIN.obj : MAIN.C c:\boy20\include\boywin.h c:\boy20\include\key.h\
	c:\boy20\include\dialog.h jrtz.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoMAIN.obj MAIN.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoMAIN.obj MAIN.C
<<
!ENDIF

MAIN.sbr : MAIN.C c:\boy20\include\boywin.h c:\boy20\include\key.h\
	c:\boy20\include\dialog.h jrtz.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRMAIN.sbr MAIN.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRMAIN.sbr MAIN.C
<<
!ENDIF

NEW.obj : NEW.C jrtz.h c:\boy20\include\boywin.h c:\boy20\include\key.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoNEW.obj NEW.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoNEW.obj NEW.C
<<
!ENDIF

NEW.sbr : NEW.C jrtz.h c:\boy20\include\boywin.h c:\boy20\include\key.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRNEW.sbr NEW.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRNEW.sbr NEW.C
<<
!ENDIF

NOW.obj : NOW.C c:\boy20\include\boywin.h c:\boy20\include\key.h jrtz.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoNOW.obj NOW.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoNOW.obj NOW.C
<<
!ENDIF

NOW.sbr : NOW.C c:\boy20\include\boywin.h c:\boy20\include\key.h jrtz.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRNOW.sbr NOW.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRNOW.sbr NOW.C
<<
!ENDIF

SELECT.obj : SELECT.C c:\boy20\include\boywin.h c:\boy20\include\key.h jrtz.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoSELECT.obj SELECT.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoSELECT.obj SELECT.C
<<
!ENDIF

SELECT.sbr : SELECT.C c:\boy20\include\boywin.h c:\boy20\include\key.h jrtz.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRSELECT.sbr SELECT.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRSELECT.sbr SELECT.C
<<
!ENDIF

SETUP.obj : SETUP.C c:\boy20\include\boywin.h c:\boy20\include\key.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoSETUP.obj SETUP.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoSETUP.obj SETUP.C
<<
!ENDIF

SETUP.sbr : SETUP.C c:\boy20\include\boywin.h c:\boy20\include\key.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRSETUP.sbr SETUP.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRSETUP.sbr SETUP.C
<<
!ENDIF


$(PROJ).bsc : $(SBRS)
	$(BSCMAKE) @<<
$(BRFLAGS) $(SBRS)
<<

$(PROJ).exe : $(OBJS)
!IF $(DEBUG)
	$(LRF) @<<$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_D)
$(LIBS: = +^
) +
$(LLIBS_G: = +^
) +
$(LLIBS_D: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_D);
<<
!ELSE
	$(LRF) @<<$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_R)
$(LIBS: = +^
) +
$(LLIBS_G: = +^
) +
$(LLIBS_R: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_R);
<<
!ENDIF
	$(LINKER) @$(PROJ).lrf


.c.sbr :
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FR$@ $<
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FR$@ $<
<<
!ENDIF

.c.obj :
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo$@ $<
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo$@ $<
<<
!ENDIF


run: $(PROJ).exe
	$(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
	CV $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)

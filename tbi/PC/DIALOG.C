 # define MaxFileNum 1024
 # include "boywin.h"
 # include "key.h"

 # include "dialog.h"
// #include "d:\boywin\include\boywin.h"
// #include "d:\boywin\include\key.h"
// #include "d:\boywin\include\dialog.h"

 # include <alloc.h>
 # include <conio.h>
 # include <dos.h>
 # include <dir.h>
 # include <io.h>
 # include <stdio.h>
 # include <string.h>
 # include <graphics.h>

 int  DialogTotal;
 int  DialogTab;
 int  CS_Dialog = 0;
 char DialogPath[MaxPath];
 char DLGPATH[MaxPath];
 char BOY_FILE_NAME[MaxPath];

 char DLL_openname[MAXPATH];
 TEST DLL_test;

 TYPE  DialogType[15];
 KEY3D DialogKey3d[5] = {
                           {0,0,0,0,"",0,0,1,0,2,"",0,0,7,0,0},
                           {0,0,0,0,"",0,0,1,0,2,"",0,0,7,0,0},
                           {0,0,0,0,"",0,0,1,0,2,"",0,0,7,0,0},
                           {0,0,0,0,"",0,0,1,0,2,"",0,0,7,0,0},
                           {0,0,0,0,"",0,0,1,0,2,"",0,0,7,0,0},
                         };
 LABEL DialogLabel[5] = {
                         {0,0,0,0, 0,0,0,0,0,0,15,0,0,1,"",0,""},
                         {0,0,0,0, 0,0,0,0,0,0,15,0,0,1,"",0,""},
                         {0,0,0,0, 0,0,0,0,0,0,15,0,0,1,"",0,""},
                         {0,0,0,0, 0,0,0,0,0,0,15,0,0,1,"",0,""},
                         {0,0,0,0, 0,0,0,0,0,0,15,0,0,1,"",0,""},
                        };
 INPUTBOX DialogInputbox[3] = {
                                  {0,0,5,0,40,1,0,0,0,15,15,0,0,1,0,0,"","",0,-4},
                                  {0,0,5,0,40,1,0,0,0,15,15,0,0,1,0,0,"","",0,-4},
                                  {0,0,5,0,40,1,0,0,0,15,15,0,0,1,0,0,"","",0,0},
                               };
 ICON DialogIcon[1] = { {0,0,0,""}};
 PICTURE DialogPicture[1] = {{0,0,""}};
 WINDOWS DialogWindows = { 0,0,0,0,"",15,1,0,0,1,2,15,0,0,0,15,1,15,0,7,0,0};

 void CreateDialogWindows(void)
 {
   if(CS_Dialog == 1)
      CREATE_WINDOWS_ALL(&DialogWindows,&DialogType[0],DialogTotal,DialogTab);
  }

 int  GetDialogWindows(TEST *tst)
  {
   if(CS_Dialog == 1)
      return(BOY_ALL_TEST(&DialogWindows,tst,DialogTotal,&DialogTab,DialogType));
   else
      return -2;
   }

 void  CloseDialogWindows(void)
 {
   if(CS_Dialog == 1)
    {
      CLOSE_BOY_WINDOWS(&DialogWindows);
      CS_Dialog = 0;
    }
 }

 int  ReadDialogWindows(char *fn)
 {
   FILE *f;
   int rn=1;
   register int i,j, k;
   int id;
   int readi;
   int Object[20];
   char pass[32];

   if(CS_Dialog == 1) CloseDialogWindows();

   if ((f=fopen(fn,"rb"))==NULL)
    {
       return -1;
    }

    fread(pass,1,sizeof(pass),f);
    if(strncmp(pass,"BoyWindows 2.0 Dialog Tools 1.0a",32)!=0)
     {
       fclose(f);
       return -2;
     }
    fread(&id,1,sizeof(int),f);
	fread(&DialogTotal,1,sizeof(int),f);
	fread(&DialogTab,1,sizeof(int),f);
	fread(DialogType,sizeof(TYPE), DialogTotal, f);
	fread(Object,sizeof(int),20,f);
	fread(&DialogWindows,sizeof(WINDOWS),1,f);

	for (i=1; i<20; i++)
	  if (Object[i])
		switch (i) {
					case 1 : DialogWindows.key = DialogKey3d;
							 fread(DialogKey3d,sizeof(KEY3D),Object[i],f);
				 break;
			case 3 : DialogWindows.lab = DialogLabel;
						 fread(DialogLabel,sizeof(LABEL),Object[i],f);
					 break;
			case 5 : DialogWindows.inp= DialogInputbox;
					 fread(DialogInputbox,sizeof(INPUTBOX),Object[i],f);
				 break;
			case 8 : DialogWindows.icn= DialogIcon;
					 fread(DialogIcon,sizeof(ICON),Object[i],f);
				 break;
			case 9 : DialogWindows.pic= DialogPicture;
					 fread(DialogPicture,sizeof(PICTURE),Object[i],f);
				 break;
			}
			fclose(f);
			if(rn == 1)
			{
			  CS_Dialog = 1;
			}
			  return rn;
		 }

 char *GetDialogPath(void)
 {
   if(CS_Dialog != 1)
	  strset(DialogPath,'\0');
   return(DialogPath);
 }

 int  SetDialogPath(char *Path)
  {
	char *s;
	char drive[MAXDRIVE];
	char dir[MAXDIR];
	char file[MAXFILE];
	char ext[MAXEXT];
	int  flags = 0;
	int i = 0;

	if(CS_Dialog == 1)
	 {
	   strcpy(DialogPath,Path);
	   while(i<5)
	   {
		 if(DialogKey3d[i].ico == '\0')
	 {
	   flags=fnsplit(DialogKey3d[i].ico,drive,dir,file,ext);
	   strset(DialogKey3d[i].ico,'\0');
	   strcpy(DialogKey3d[i].ico,Path);
	   strcat(DialogKey3d[i].ico,"\\");
	   strcat(DialogKey3d[i].ico,file);
	   strcat(DialogKey3d[i].ico,ext);
	 }
	 i++;
	   }
	  flags=fnsplit(DialogIcon[0].name,drive,dir,file,ext);
	  strset(DialogIcon[0].name,'\0');
	  strcpy(DialogIcon[0].name,Path);
	  strcat(DialogIcon[0].name,"\\");
	  strcat(DialogIcon[0].name,file);
	  strcat(DialogIcon[0].name,ext);

	  flags=fnsplit(DialogPicture[0].name,drive,dir,file,ext);
	  strset(DialogPicture[0].name,'\0');
	  strcpy(DialogPicture[0].name,Path);
	  strcat(DialogPicture[0].name,"\\");
	  strcat(DialogPicture[0].name,file);
	  strcat(DialogPicture[0].name,ext);
	 }
   return flags;
  }

  int  CreateErrorWindows(char *text)
   {
	 int FLAG = 0;
	 int CASE;
	 char DLL_openname[MAXPATH];

	 strset(DLL_openname,'\0');
	 strcpy(DLL_openname,DLGPATH);
	 strcat(DLL_openname,"\\Warning1.Dlg");

	 ReadDialogWindows(DLL_openname);
	 strcpy(DialogLabel[0].text,text);
	 SetDialogPath(DLGPATH);
	 CreateDialogWindows();

	 while(!FLAG)
	 {
	  BOY_GET_TEST(&DLL_test);
	  CASE=GetDialogWindows(&DLL_test);
	  switch(CASE)
	  {
	case 100:FLAG=1;break;
	case 101:
	case WM_CLOSE:FLAG=1;break;
	   }
	 }
	 CloseDialogWindows();
	 return (CASE);
  }

  int CreateInputWindows(char *text1,char *text2)
   {
	 int FLAG = 0;
	 int CASE;
	 char DLL_openname[MAXPATH];

	 strset(DLL_openname,'\0');
	 strcpy(DLL_openname,DLGPATH);
	 strcat(DLL_openname,"\\INPUT2.Dlg");

	 ReadDialogWindows(DLL_openname);
	 strcpy(DialogInputbox[0].text,text2);
	 strcpy(DialogLabel[0].text,text1);
	 SetDialogPath(DLGPATH);
	 CreateDialogWindows();

	 while(!FLAG)
	 {
	  BOY_GET_TEST(&DLL_test);
	  CASE=GetDialogWindows(&DLL_test);
	  if(CASE == 0 || CASE==-1 || CASE==-7 || CASE==-8 || CASE==-9)
	   {
	}
	   else
	   {
	  strcpy(BOY_FILE_NAME,DialogInputbox[0].text);
	  FLAG = 1;
	}
	 }
	 CloseDialogWindows();
	 return (CASE);
  }

  int  CreateAboutWindows(char *text[5])
  {
	int FLAG = 0;
	int CASE;
	int i;

	strset(DLL_openname,'\0');
	strcpy(DLL_openname,DLGPATH);
	strcat(DLL_openname,"\\ABOUT.DLG");

	ReadDialogWindows(DLL_openname);
	for(i=0;i<5;i++)
	  strcpy(DialogLabel[i].text,text[i]);
	SetDialogPath(DLGPATH);
	CreateDialogWindows();

	while(!FLAG)
	{
	 BOY_GET_TEST(&DLL_test);
	 CASE=GetDialogWindows(&DLL_test);
	 switch(CASE)
	  {
	case 100:
	case WM_CLOSE:FLAG=1;break;
	  }
	 }
	CloseDialogWindows();
	return (CASE);
  }

  int CreateWarningWindows(char *name,char *text,int type)
  {
   int FLAG = 0;
   int CASE;
   char DLL_openname[MAXPATH];
   static TEST DLL_test;

   strset(DLL_openname,'\0');
   strcpy(DLL_openname,DLGPATH);

   if(type == 0)
	  strcat(DLL_openname,"\\Warning1.Dlg");
   if(type == 1)
	  strcat(DLL_openname,"\\Warning2.Dlg");
   if(type == 2)
	  strcat(DLL_openname,"\\Warning3.Dlg");

   ReadDialogWindows(DLL_openname);
   if(type == 0 || type ==1)
	{
	  strcpy(DialogWindows.text,name);
	  strcpy(DialogLabel[0].text,text);
	}
   if(type == 2)
	{
	  strcpy(DialogLabel[0].text,name);
	  strcpy(DialogLabel[1].text,text);
	 }
	SetDialogPath(DLGPATH);
	CreateDialogWindows();

	while(!FLAG)
	{
	 BOY_GET_TEST(&DLL_test);
	 CASE=GetDialogWindows(&DLL_test);
	 if(CASE == 0 || CASE==-1 || CASE==-7 || CASE==-8 || CASE==-9)
	  {
	   }
	   else
		 FLAG=1;
	 }
	CloseDialogWindows();
	return (CASE);
  }

  int CreateFileWindows(char *find,int Style)
  {
	char *get_cur_dir(char *path);
	int VerityDisk (int disk);
	static TEST BOY_TEST;
	static WINDOWS BOY_WINDOWS = {70,98,505,380,"文件提取窗口",7,1,0,0,1,3,15,0,0,0,15,1,15,0,7,0,0};
	static KEY3D BOY_KEYS[2]   = {
				   {410,140,490,163,"",0,0,1,0,2,"提取",CR,0,7,0,0x0100},
								   {410,170,490,193,"",0,0,1,0,2,"取消",ESC,0,7,0,0x0101},
								  };
	static LABEL BOY_LABEL[5]  = {
								   {88,129,198,149,0,0,1,0,0,0,7,0,0x0000, 1,"提取文件名 :"},
								   {88,323,198,343,0,0,1,0,0,0,7,0,0x0000, 1,"文件类型表 :"},
								   {232,129,346,149,0,0,1,0,0,0,7,0,0x0000, 1,"目录 :"},
								   {232,149,395,169,0,0,1,0,0,0,7,0,0x0000, 1,""},
								   {232,275,346,295,0,0,1,0,0,0,7,0,0x0000, 1,"驱动器列表 :"}
								  };
	static INPUTBOX BOY_INPUTBOX = {82,151,17,0,12,3,0,0,0,15,15,1,255,1,0,0,"",""};
	static FILELIST BOY_FILELIST = {88,174,0,0,14,8,0,0,0,1,0,0xFF,0x1200,MaxFileNum,13,"","*.*"};
	static COMBO BOY_COMBO = { 89,345, 0,0,36,3,0,0,0,1,1,0,0,0xFF,1,20,0x1300,0};
	static char combo_buf[2][15] = { "*.*", "*.*"};
	static DIRLIST BOY_DIRLIST = { 232,176, 0,0, 18,5, 0,0,0,1,0,0xFF,0x1000,""};
	static DRIVELIST BOY_DRIVELIST = { 233,300, 0,0, 18, 4, 0, 0, 0, 1, 0, 0xff, 0x1100, ""};

	static TYPE BOY_TYPE[16]={
							   {5,0},
							   {16,0},
				   {13,0},
							   {17,0},
							   {15,0},
							   {1,0},{1,1},
							   {3,0},{3,1},{3,2},{3,3},{3,4},
							 };
	 static int BOY_TOTAL=12;
	 int BOY_TAB=0;
	 int i,j;
	 char CurDir[MaxPath], OldDir[MaxPath];
	 int  CurFile, CurDrive, CurType, OldDisk;
	 int r=0;

	 struct ffblk ffblk;
	 int done,file_count=0;
	 unsigned long memleft;

	 if(Style == 0)
	 {
	   strcpy(BOY_WINDOWS.text,"文件保存窗口");
	   strcpy(BOY_KEYS[0].text,"保存");
	  }
	 if(Style == 1)
	 {
	   strcpy(BOY_WINDOWS.text,"文件提取窗口");
	   strcpy(BOY_KEYS[0].text,"提取");
	  }

	 done = findfirst("*.*",&ffblk,FA_NORMAL|FA_RDONLY|FA_HIDDEN|FA_SYSTEM|
																		FA_LABEL|FA_DIREC|FA_ARCH);
	 while (!done)
	 {
	   done = findnext(&ffblk);
	   file_count++;
	 }
	 if(file_count>MaxFileNum)
		 file_count=MaxFileNum;
	 memleft=coreleft();
	 if(file_count*13>memleft)
	  {
	if(memleft>4096)
	   file_count=(memleft-2048)/13;
	else
	  {
		CreateWarningWindows("系统信息","内存无足够空间运行处理程序!",0);
		return -1;
	   }
	  }

	  get_cur_dir(OldDir);
	  OldDisk=getdisk();
	  strcpy(combo_buf[0],find);
	  strcpy(BOY_FILELIST.filetype,find);
	  strcpy(BOY_COMBO.name,find);
	  BOY_FILELIST.filename=(char *)farmalloc(file_count*13*sizeof(char));
	  BOY_COMBO.text=(char *)combo_buf;
	  BOY_FILELIST.sl=file_count;  //MaxFileNum;

	  CurDrive=BOY_DRIVELIST.drive[0];
	  CurType=BOY_COMBO.to;

	  BOY_WINDOWS.key=BOY_KEYS;
	  BOY_WINDOWS.lab=BOY_LABEL;
	  BOY_WINDOWS.inp=&BOY_INPUTBOX;
	  BOY_WINDOWS.fil=&BOY_FILELIST;
	  BOY_WINDOWS.cmb=&BOY_COMBO;
	  BOY_WINDOWS.dir=&BOY_DIRLIST;
	  BOY_WINDOWS.drv=&BOY_DRIVELIST;


	  CREATE_WINDOWS_ALL(&BOY_WINDOWS, &BOY_TYPE[0], BOY_TOTAL, BOY_TAB);

	  strcpy(CurDir,BOY_DIRLIST.path);
	  strcpy(BOY_LABEL[3].text,BOY_DIRLIST.path);
	  CREATE_BOY_LABEL(&BOY_LABEL[3]);

	  CurFile=BOY_FILELIST.to;
	  strcpy(BOY_INPUTBOX.text,BOY_FILELIST.filename+CurFile*13);
	  strcpy(BOY_INPUTBOX.seltext,BOY_FILELIST.filename+CurFile*13);
	  BOY_INPUTBOX.sels = 0;
	  BOY_INPUTBOX.seln = strlen(BOY_INPUTBOX.text);
	  BOY_INPUTBOX_ENABLE(&BOY_INPUTBOX);


	  i=0;
	  while(!i)
	   {
	BOY_GET_TEST(&BOY_TEST);
	j=BOY_ALL_TEST(&BOY_WINDOWS, &BOY_TEST, BOY_TOTAL, &BOY_TAB, BOY_TYPE);
	switch (j)
	{
	  case 0x1000 :{
					if (strcmp(CurDir,BOY_DIRLIST.path)!=0)
			 {
				   strcpy(CurDir,BOY_DIRLIST.path);
				   strcpy(BOY_LABEL[3].text,BOY_DIRLIST.path);
			   CREATE_BOY_LABEL(&BOY_LABEL[3]);
			   strcpy(BOY_FILELIST.path,BOY_DIRLIST.path);
			   BOY_FILELIST.sl=file_count;  //MaxFileNum;
			   CREATE_BOY_FILELIST(&BOY_FILELIST);
			   CurFile=BOY_FILELIST.to;
			   strcpy(BOY_INPUTBOX.text,
				  BOY_FILELIST.filename+BOY_FILELIST.to*13);
			   CREATE_BOY_INPUTBOX(&BOY_INPUTBOX,1);
			   strcpy(BOY_FILE_NAME,BOY_LABEL[3].text);
			   strcat(BOY_FILE_NAME,"\\");
			   strcat(BOY_FILE_NAME,BOY_INPUTBOX.text);
			   BOY_MOUSE_HIDE();
			   setfillstyle(1,7);
			   bar(BOY_WINDOWS.x1+345,BOY_WINDOWS.y1+115,
			   BOY_WINDOWS.x1+385,BOY_WINDOWS.y1+155);
			   if (strstr(BOY_INPUTBOX.text,".ICN")!=NULL)
				BOY_DRAW_ICN(BOY_WINDOWS.x1+345,BOY_WINDOWS.y1+115,BOY_FILE_NAME);
			   if (strstr(BOY_INPUTBOX.text,".PIC")!=NULL)
				BOY_DRAW_PIC(BOY_WINDOWS.x1+345,BOY_WINDOWS.y1+115,BOY_FILE_NAME);
			   BOY_MOUSE_VIEW();
				}
			   }break;
	  case 0x1100 :{
			if (CurDrive!=BOY_DRIVELIST.drive[0])
						if (VerityDisk(BOY_DRIVELIST.drive[0]-'A'))
			  {
							setdisk(BOY_DRIVELIST.drive[0]-'A');
							CurDrive=BOY_DRIVELIST.drive[0];
							BOY_DIRLIST.path[0]=0;
							CREATE_BOY_DIRLIST(&BOY_DIRLIST);
							strcpy(CurDir,BOY_DIRLIST.path);
							strcpy(BOY_LABEL[3].text,BOY_DIRLIST.path);
							CREATE_BOY_LABEL(&BOY_LABEL[3]);
							strcpy(BOY_FILELIST.path,BOY_DIRLIST.path);
							BOY_FILELIST.sl=file_count;  //MaxFileNum;
							CREATE_BOY_FILELIST(&BOY_FILELIST);
							CurFile=BOY_FILELIST.to;
							strcpy(BOY_INPUTBOX.text,
							BOY_FILELIST.filename+BOY_FILELIST.to*13);
							CREATE_BOY_INPUTBOX(&BOY_INPUTBOX,1);
							strcpy(BOY_FILE_NAME,BOY_LABEL[3].text);
							strcat(BOY_FILE_NAME,"\\");
							strcat(BOY_FILE_NAME,BOY_INPUTBOX.text);
				BOY_MOUSE_HIDE();
							setfillstyle(1,7);
				bar(BOY_WINDOWS.x1+345,BOY_WINDOWS.y1+115,
											BOY_WINDOWS.x1+385,BOY_WINDOWS.y1+155);
							if (strstr(BOY_INPUTBOX.text,".ICN")!=NULL)
											BOY_DRAW_ICN(BOY_WINDOWS.x1+345,BOY_WINDOWS.y1+115,BOY_FILE_NAME);
							if (strstr(BOY_INPUTBOX.text,".PIC")!=NULL)
											BOY_DRAW_PIC(BOY_WINDOWS.x1+345,BOY_WINDOWS.y1+115,BOY_FILE_NAME);
							BOY_MOUSE_VIEW();
						   }
						  }break;
				case 0x1200 :{
							   if (CurFile!=BOY_FILELIST.to)
							   {
									 CurFile=BOY_FILELIST.to;
									 strcpy(BOY_INPUTBOX.text,
											BOY_FILELIST.filename+BOY_FILELIST.to*13);
									 CREATE_BOY_INPUTBOX(&BOY_INPUTBOX,1);
									 strcpy(BOY_FILE_NAME,BOY_LABEL[3].text);
									 strcat(BOY_FILE_NAME,"\\");
					 strcat(BOY_FILE_NAME,BOY_INPUTBOX.text);
									 BOY_MOUSE_HIDE();
					 setfillstyle(1,7);
									 bar(BOY_WINDOWS.x1+345,BOY_WINDOWS.y1+115,
									 BOY_WINDOWS.x1+385,BOY_WINDOWS.y1+155);
									 if (strstr(BOY_INPUTBOX.text,".ICN")!=NULL)
													 BOY_DRAW_ICN(BOY_WINDOWS.x1+345,BOY_WINDOWS.y1+115,BOY_FILE_NAME);
									 if (strstr(BOY_INPUTBOX.text,".PIC")!=NULL)
													 BOY_DRAW_PIC(BOY_WINDOWS.x1+345,BOY_WINDOWS.y1+115,BOY_FILE_NAME);
									 BOY_MOUSE_VIEW();
								 }
							   }break;
				case 0x1300 : {
								if (CurType!=BOY_COMBO.to)
								 {
									CurType=BOY_COMBO.to;
									strcpy(BOY_FILELIST.filetype,
										   combo_buf[BOY_COMBO.to]);
									BOY_FILELIST.sl=file_count;  //MaxFileNum;
									CREATE_BOY_FILELIST(&BOY_FILELIST);
					CurFile=BOY_FILELIST.to;
									strcpy(BOY_INPUTBOX.text,
					   BOY_FILELIST.filename+BOY_FILELIST.to*13);
									CREATE_BOY_INPUTBOX(&BOY_INPUTBOX,1);
									strcpy(BOY_FILE_NAME,BOY_LABEL[3].text);
									strcat(BOY_FILE_NAME,"\\");
									strcat(BOY_FILE_NAME,BOY_INPUTBOX.text);
									BOY_MOUSE_HIDE();
									setfillstyle(1,7);

									bar(BOY_WINDOWS.x1+345,BOY_WINDOWS.y1+115,
										BOY_WINDOWS.x1+385,BOY_WINDOWS.y1+155);
									if (strstr(BOY_INPUTBOX.text,".ICN")!=NULL)
										BOY_DRAW_ICN(BOY_WINDOWS.x1+345,BOY_WINDOWS.y1+115,BOY_FILE_NAME);
									if (strstr(BOY_INPUTBOX.text,".PIC")!=NULL)
										BOY_DRAW_PIC(BOY_WINDOWS.x1+345,BOY_WINDOWS.y1+115,BOY_FILE_NAME);
									BOY_MOUSE_VIEW();
								  }
								}break;
				case 0x0100 : {
				if (BOY_INPUTBOX.text[0])
								  {
					strcpy(BOY_FILE_NAME,BOY_LABEL[3].text);
										strcat(BOY_FILE_NAME,"\\");
										strcat(BOY_FILE_NAME,BOY_INPUTBOX.text);
										strcpy(BOY_FILE_NAME,BOY_LABEL[3].text);
										strcat(BOY_FILE_NAME,"\\");
										strcat(BOY_FILE_NAME,BOY_INPUTBOX.text);
										BOY_MOUSE_HIDE();
										setfillstyle(1,7);
										bar(BOY_WINDOWS.x1+345,BOY_WINDOWS.y1+115,
														BOY_WINDOWS.x1+385,BOY_WINDOWS.y1+155);
										if (strstr(BOY_INPUTBOX.text,".ICN")!=NULL)
														BOY_DRAW_ICN(BOY_WINDOWS.x1+345,BOY_WINDOWS.y1+115,BOY_FILE_NAME);
										if (strstr(BOY_INPUTBOX.text,".PIC")!=NULL)
														BOY_DRAW_PIC(BOY_WINDOWS.x1+345,BOY_WINDOWS.y1+115,BOY_FILE_NAME);
										BOY_MOUSE_VIEW();
								  }
								  else //r=0;  //BOY_INPUTBOX.text[0]
									 memset(BOY_FILE_NAME,0,sizeof(BOY_FILE_NAME));
				  if(Style == 0)
								   {
					  memset(BOY_FILE_NAME,'\0',sizeof(BOY_FILE_NAME));
									  strcpy(BOY_FILE_NAME,BOY_LABEL[3].text);
									  strcat(BOY_FILE_NAME,"\\");
									  strcat(BOY_FILE_NAME,BOY_INPUTBOX.text);
									  if (memchr(BOY_FILE_NAME,'.',MAXPATH)==NULL)
										  strcat(BOY_FILE_NAME,memchr(find,'.',MAXPATH));
									  if(access(BOY_FILE_NAME,0)!=0)
					{
										  i=1;
										  r=1;
										 }
					   else
					{
					  BOY_WINDOWS_DISABLE(&BOY_WINDOWS);
					  if(CreateWarningWindows("警告信息","此文件已存在, 是否覆盖?",1)==30)
					   {
						  i=1;
						  r=1;
					   }
					   else   i=0;
					   BOY_WINDOWS_ENABLE(&BOY_WINDOWS);
					}
					 }
				  else
				   {
					   i=1;
					   r=1;
					 }
				   }break;
		   case 0x0101 : {
					r=0;
					i=1;
				   }break;
	   }
	   }
	  setdisk(OldDisk);
	  chdir(OldDir);
	  CLOSE_BOY_WINDOWS(&BOY_WINDOWS);
	  return (r);
  }

 int VerityDisk (int disk)
 {
  char  buf[2048];
  union REGS inregs, outregs;
  struct SREGS sregs;
  int i;

  if (disk>1) return 1;
  for (i=0;i<3;i++)
   {
	 inregs.x.ax=0x0201;
	 inregs.x.bx=FP_OFF(buf);
	 sregs.es=FP_SEG(buf);
	 inregs.x.cx=1;
	 inregs.h.dh=0;
	 inregs.h.dl=disk;
	 int86x(0x13, &inregs, &outregs, &sregs);
   }
  if (outregs.x.cflag!=0)  return 0;
  return 1;
 }

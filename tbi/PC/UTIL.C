# include <string.h>
# include <stdlib.h>

char *hex(int inter,char base,char *unit)
{
	static char tmp[10];
	char i;
	for(i=0;i<sizeof(tmp);i++)tmp[i]='\0';
	itoa(inter,tmp,10);
	i=0;
	while(tmp[i]!='\0')i++;
	if(base){
		if(i>base){
			base=i-base;
			for(;i>=base;i--)
				tmp[i+1]=tmp[i];
			tmp[base]='.';
		}
		else{
			for(;i>=0;i--)tmp[i+2]=tmp[i];
			tmp[1]='.';
			tmp[0]='0';
		}
	}
	strcat(tmp,unit);
	return tmp;
}

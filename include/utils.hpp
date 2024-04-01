#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sys/io.h>
#include <string.h>
#include <dirent.h>
using namespace std;

int get_need_file(const string path, vector<string>& files, string ext){
	
	int iFileCnt = 0;
	DIR *dirptr = NULL;
	struct dirent *dirp;
 
	if((dirptr = opendir(path.c_str())) == NULL)//打开一个目录
	{
		return 0;
	}
	while ((dirp = readdir(dirptr)) != NULL)
	{
		if ((dirp->d_type == DT_REG) && 0 ==(strcmp(strchr(dirp->d_name, '.'), ext.c_str())))//判断是否为文件以及文件后缀名
		{
			files.push_back(path+'/'+dirp->d_name);
		}
		iFileCnt++;
	}
	closedir(dirptr);
	
	return iFileCnt;
}

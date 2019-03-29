#!/bin/bash

### 函数定义 ###
#删除注释，入参为文件的路径
function cleanCommons ()  {
	filename=$1
	#删除单行注释
	sed -i "/^[ \t]*\/\//d" $filename
	#删除行尾注释
	sed -i 's#\/\/.*##g' $filename  #如果中文乱码，则删除不了
	#删除/*commnets*/类型的注释，包括多行和单行两种
	perl -0777 -pi -e 's,/\*.*?\*/,,gs' $filename
	rm $filename.bak
	#删除连续空行，只保留一个空行
	sed -i -e '/^$/{N;/\n$/D};' $filename
}

# 遍历工程目录
function traversalProject () {
for file in $1/*; do
	echo $file

	if [ -d $file ];then
		#如果是子文件夹，则对子文件夹进行遍历。
		traversalProject $file
	else
		#判断文件为.h或者.cpp类型
		if [ "${file##*.}"x = "h"x ] || [ "${file##*.}"x = "cpp"x ];then
			#如果是文件，则删除文件内注释。
			cleanCommons $file
		fi
	fi
done
}

### 具体实现 ###
source="./source"
dest="./dest"

#拷贝源工程
rm -rf $dest
cp -rf $source $dest

#遍历，对文件中的注释进行删除
traversalProject $dest

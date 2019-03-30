# CExtFile

`CExtFile类`是对CFile类的扩展，功能是类似于行车记录仪，自维护磁盘文件，只保留一定数据量的数据。

一般地，磁盘的容量是有限的，如果不做限制的向磁盘中写入数据， 那么迟早硬盘的容量会被写满。并且，我们一般只是对最近一定量的内容感兴趣，比如：报警日志、振动监测数据等等。CExtFile就是在这样的背景下被我创建出阿里的。

## 使用

CExtFile的操作同CFile十分相似，在具体使用时，可做如下操作：

### SetFileSize()

用于设置文件的总大小。之后，CExtFile会控制文件写入，使得总文件大小在可控范围内记录。

### SetBufferSize()

设置缓存大小。缓存用于对写入文件进行缓存，以减少磁盘的写入操作。

> 需要注意的是，bufferSize≤BlockSize。如果bufferSize>BlockSize，则其实际值只能是BlockSize。

## Open( )

用于创建文件。

### Write()

用于写文件，由CExtFile内部维护流数据。

### WriteHeader()

用于写文件头。该部分可有可无，是由用户自己决定的。

### Close()


## 工程目录介绍

`deploy.sh`用于发布CExtFile的代码，是对原有代码进行了一些操作处理，以保护个人的知识贡献。







#外部排序字符串

##说明
+ `N(>5)`个大于1G的文件
+ 乱序的字符串构成，暂且定位小写英文字母
+ 在使用内存小于`50M`的情况下，以行为单位，将其排序

###filesort_testgen命令行接口

    filesort_testgen FILE_COUNT LINES_PER_FILE PREFIX
    
####其中
+ `filesort_testgen`为可执行文件名
+ `FILE_COUNT`为需要生成的待排序文件的个数
+ `LINES_PER_FILE`：每个待排序文件的行数
+ `PREFIX`为生成文件的前缀

###filesort命令行接口

    filesort INPUT_FILE_1 INPUT_FILE_2 ... OUTPUT_FILE

####其中
+ `NPUT_FILE_1`表示输入文件的文件名（或路径）
+ `OUTPUT_FILE`表示输出文件的文件名
+ 结果会生出排序后的文件`sorted`，并输出内存使用情况


##实现算法
+ 将大文件分割为10M大小的小文件
+ 采用分治的思想将小文件两两合并，可以采用线段树的写法
+ 合并的方法采用归并排序思想
+ 文件读写用FILE的接口，每次读若干行字符串然后一次性写入文件

##本地环境
+ windows 7
+ vs2012 visual c++ win32应用控制台程序


##实现缺陷
+ 要求字符串的单行大小不得超过1e7字节
+ 文件读写速度很慢，1G的文件排序需要很久

##注意
+ 默认生成`.txt`文件,数据生成文件在当前目录，排序生成文件在`temp`目录。
+ `filesort_testgen`默认产生1G大小的文件，如需改变数据文件大小，需要修改代码中的`MAX_TOT_CHAR`值
+ `mingw32`编译文件可能会提示`GetProcessMemoryInfo`错误
+ 编译是可能提示fopen错误，需要在设置里面的配置属性/c/c++/预处理器，预处理定义中添加`_CRT_SECURE_NO_WARNINGS`
    

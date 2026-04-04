ump介绍

1. ump:
	该文件用来介绍ump用法。

2. ump_drs: delete right space
	用法: ump_drs file ...
	该文件用来删除其他文件每行左边的空格。

3. ump_dls: delete left space
	用法: ump_dls file ...
	该文件用来删除其他文件每行右边的空格。

4. ump_drls: delete right and left space
	用法: ump_drls file ...
	该文件用来删除其他文件每行左边和右边的空格。

5. ump_dlrs: delete left and right space
	用法: ump_dlrs file ...
	该文件用来删除其他文件每行左边和右边的空格。

6. ump_ccsie: change chinese symble into english
	用法: ump_ccsie file ...
	该文件用来将中文标点替换为英文。

7. ump_mw: make website
	用法: ump_mw
	该文件用于随机生成一个网页名。

8. ump_sudoku: sudoku
	用法: ump_sudoku
	该文件用于解数独。
	使用时应按九宫格形式输入给出每个数, 不知道的用0代替。

9. ump_24:
	用法1: ump_24 a b c d(a, b, c, d表示4个整数)
	用法2: ump_24, 然后再输入a b c d(a, b, c, d表示4个整数)
	该文件用来算24点。


注: 若提示没有文件，则需:
gcc program/ump.c -o ump -O3 -std=c99
gcc program/ump_24.c -o ump_24 -O3 -std=c99
gcc program/ump_ccsie.c -o ump_ccsie -O3 -std=c99
gcc program/ump_dls.c -o ump_dls -O3 -std=c99
gcc program/ump_drls.c -o ump_drls -O3 -std=c99
gcc program/ump_drs.c -o ump_drs -O3 -std=c99
gcc program/ump_jm.c -o ump_jm -O3 -std=c99
gcc program/ump_mw.c -o ump_mw -O3 -std=c99
gcc program/ump_sudoku.c -o ump_sudoku -O3 -std=c99

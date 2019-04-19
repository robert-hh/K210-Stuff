# Various file for the Sipeed MaixPy K210

This folder contains a few python scripts than can be used for the Sipeed MaixPy K210.
It also contains some C files, but these were made for the previous generation of the Maixpy 
firmware. Most likely is does not fit any more.

## uart_core.c

Version with wotking support for mp_hal_stdin_rx_chr(). With this version, fucntions like
input(), sys.stdin.read() etc. work a expcted. required for upysh.py and pye.py. When using this file, mpconfigport.h has top be modified too.

## mpconfigport.h

Some additional definitions to make uart_core working. Also exnabled max() and min() and define the module time as alias to utime.

## upysh.py

A version of upysh.py with some of the commands. The version is feature-reduced, bevause
the actual version of the K210 python lacks quite a few modules & functions. Typical usage pattern:  

from upysh import *  
man

## pye.py

A version of the pye editor with some minor modifications for the K210 python. Since the
K210 python port has some debug messages enabled for gc.collect(), some spurios messages may show up. The screen can be restored with Ctrl-E. To supporess the messages, remove
or comment the statement: 

gc_dump_info();  

in the function gc_collect() of the file main.c. The documentation for pye.py is at https://github.com/robert-hh/Micropython-Editor

Both upysh.py and pye.py can  be placed into frozen bytecode. When doing so, loading
times are fast.

## main.c

A 'hacked' version of main.c, which does not finish when Ctrl-D is entered. As a result, 
ampy and find the board and at least execute the command ls and put. Ampy get does not work,
because it tries to upload code to the K210 which is not supported.

## file_io.c

 A version which enables all file methods including special methods like __exit__ and __del__ Doing that allows enable statements like  
 ```
 with open("name") as myfile:  
     ....
```
Also: fix a memory leak and memory overflow in file_open()

## moduos.c

Extend the function mp_vfs_import_stat() such that it reports properly
if a file exists or not. As a result, weak links to modules work. 

Major refactor of the module uos

- The code has beem simplified and RAM usage was reduced by 9k
- A simple "directory" concept is implemented, which treats directories
  as file name prefix. This prefix is inserted before any file name
  which does not start with '/'. chdir() and getcwd() set or get this
  prefix. For compliance rmdir() and mkdir() are deined, but do nothing.
- uos.stat() now delivers a compatible data structure, even if most values
  are 0. The only resonable values is file size. Other values are set
  to a sane value (access rights -> stat.IS_FILE, inode -> file_id).
- uos.statvfs() also delivers now the formally intended structure with
  the value 0 in unused fiels instead of <nil>, which at least had the
  wrong type. Can be improved.
- os.listdir() and os.ls() are swapped, such that os.listdir now ŕeturns
  the compatible value of just  alist with file names, whereas os.ls()
  returns a list with 'type size name' strings.   



## modutime.c, mphalport.c, mphalport.h

Added ticks_ms, ticks_us, ticks_cpu, ticks_diff, ticks_add

The ticks period is 2**62, which will probably never overflow, at least not in my lifetime. 

# Various file for the Sipeed MaixPy K210

This folder contains a few python scripts than can be used for the Sipeed MaixPy K210.

- uart_core.c

Version with wotking support for mp_hal_stdin_rx_chr(). With this version, fucntions like
input(), sys.stdin.read() etc. work a expcted. required for upysh.py and pye.py. When using this file, mpconfigport.h has top be modified too.

- mpconfigport.h

Some additional definitions to make uart_core working. Also exnabled max() and min() and define the module time as alias to utime.

- upysh.py

A version of upysh.py with some of the commands. The version is feature-reduced, bevause
the actual version of the K210 python lacks quite a few modules & functions. Typical usage pattern:  

from upysh import *  
man

- pye.py

A version of the pye editor with some minor modifications for the K210 python. Since the
K210 python port has some debug messages enabled for gc.collect(), some spurios messages may show up. The screen can be restored with Ctrl-E. To supporess the messages, remove
or comment the statement: 

gc_dump_info();  

in the function gc_collect() of the file main.c. The documentation for pye.py is at https://github.com/robert-hh/Micropython-Editor

Both upysh.py and pye.py can  be placed into frozen bytecode. When doing so, loading
times are fast.

- main.c

A 'hacked' version of main.c, which does not finish when Ctrl-D is entered. As a result, 
ampy and find the board and at least execute the command ls and put. Ampy get does not work,
because it tries to upload code to the K210 which is not supported.

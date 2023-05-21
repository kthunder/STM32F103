openocd.exe ^
-s "C:\\ENV\\EmbeddedToolChain\\xpack-openocd-0.11.0-5\\scripts" ^
-f "C:\\Users\\Administrator\\Desktop\\STM-PROJECTS\Print\\st_nucleo_f103rb.cfg" ^
-c "tcl_port disabled" ^
-c "gdb_port disabled" ^
-c "tcl_port disabled" ^
-c "program %1" ^
-c reset ^
-c shutdown
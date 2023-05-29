set old_dir=%cd%
cd /d %~dp0%

openocd.exe ^
-s "C:\\ENV\\EmbeddedToolChain\\xpack-openocd-0.11.0-5\\scripts" ^
-f "./st_nucleo_f103rb.cfg" ^
-c "tcl_port disabled" ^
-c "gdb_port disabled" ^
-c "tcl_port disabled" ^
-c "program '%1'" ^
-c reset ^
-c shutdown

cd /d %old_dir%
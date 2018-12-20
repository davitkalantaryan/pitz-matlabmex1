
Up to now, there is a problem to read TINE servers frm DOOCS client
In order to fix this, tine compiled as static then added to DOOCS client

In order to compile DOOCSapi without linkage error on some APIs (nanosleep, poll, etc.)
/FORCE:MULTIPLE  command line option is added to linker flag
See notes https://msdn.microsoft.com/en-us/library/72zdcz6f.aspx 

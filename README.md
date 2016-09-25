***2016-09-25***

Add an Anti-debug logic in native code, actually in JNI_OnLoad().
It works by checking `TracerPid` in `/proc/[pid]/status`.
If TracerPid is not 0, it will be recognised being attached and then kill the process.

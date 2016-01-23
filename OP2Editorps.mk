
OP2Editorps.dll: dlldata.obj OP2Editor_p.obj OP2Editor_i.obj
	link /dll /out:OP2Editorps.dll /def:OP2Editorps.def /entry:DllMain dlldata.obj OP2Editor_p.obj OP2Editor_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del OP2Editorps.dll
	@del OP2Editorps.lib
	@del OP2Editorps.exp
	@del dlldata.obj
	@del OP2Editor_p.obj
	@del OP2Editor_i.obj

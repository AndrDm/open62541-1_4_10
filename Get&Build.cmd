REM goto :version
python.exe -m pip install --upgrade pip
pip install six

:ask_user
echo Please enter 'M' or 'A'.
set /p "choice=Clone Master(M) or actual 1.4.10(A)? "

if /i "%choice%"=="M" git clone https://github.com/open62541/open62541
if /i "%choice%"=="A" git clone --branch v1.4.10 --depth 1 https://github.com/open62541/open62541

REM git clone https://github.com/open62541/open62541
REM git clone --branch v1.4.10 --depth 1 https://github.com/open62541/open62541

mkdir open62541-build32
mkdir open62541-build64
:make
set "FLAGS=-DBUILD_SHARED_LIBS=ON -DUA_BUILD_EXAMPLES=ON -DUA_ENABLE_ENCRYPTION=OPENSSL"
set "BUILD=-DCMAKE_BUILD_TYPE=Release -G "Visual Studio 17 2022""
set "CMAKE="C:\Program Files\CMake\bin\cmake.exe""
%CMAKE% %BUILD% %FLAGS% -A Win32 -S open62541 -B "open62541-build32" 
%CMAKE% %BUILD% %FLAGS% -A x64 -S open62541 -B "open62541-build64" 
:build
set "MSBUILD="C:\Program Files\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe""
%MSBUILD% open62541-build32\open62541.sln /t:Clean;Rebuild /property:Configuration=Release
%MSBUILD% open62541-build64\open62541.sln /t:Clean;Rebuild /property:Configuration=Release
:copy
copy open62541-build32\bin\Release\open62541.dll open62541x86.dll
copy open62541-build64\bin\Release\open62541.dll open62541x64.dll
copy "C:\Program Files\OpenSSL-Win64\bin\libcrypto-3-x64.dll" libcrypto-3-x64.dll
copy "C:\Program Files (x86)\OpenSSL-Win32\bin\libcrypto-3.dll" libcrypto-3.dll 

:version
REM RC.exe /fo Resources.res Resources.rc
RH.exe -open Resources.rc -save Version.res -action compile
RH.exe -open open62541x86.dll -save open62541x86.dll -action addoverwrite -resource Version.res
RH.exe -open open62541x64.dll -save open62541x64.dll -action addoverwrite -resource Version.res

:end
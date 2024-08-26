@ECHO OFF

for /f %%a in ('powershell -Command "[int](python -c 'import multiprocessing as mp; print(int(mp.cpu_count() * 1.5))')"') do set CPU_COUNT_MULTIPLIER=%%a
set DEBUG=1

set FILE=-f "make/main.mk"
set FLAGS=-j %CPU_COUNT_MULTIPLIER% DEBUG=%DEBUG%
set UTILITY=%FILE% utility %FLAGS%
set PREPARE=%FILE% prepare %FLAGS%
set BUILD=%FILE% build %FLAGS%

start pwsh -NoExit -Command "make %UTILITY% && make %PREPARE% && make %BUILD%"

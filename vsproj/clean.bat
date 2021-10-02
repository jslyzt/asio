@echo off

rd /s /q .vs

rd /s /q bin
rd /s /q lib

for /D %%i in (*) do (
	if exist %%~ni\x64 (
		rd /s /q %%~ni\x64
	)
)
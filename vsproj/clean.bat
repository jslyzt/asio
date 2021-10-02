@echo off

rd /s /q .vs
rd /s /q x64
rd /s /q ..\bin

for /D %%i in (*) do (
	if exist %%~ni\x64 (
		rd /s /q %%~ni\x64
	)
)
echo off

mkdir bk
for %%f in (*.png) do (
	copy %%f bk\%%f
)

setlocal EnableDelayedExpansion
set /a count = 0
for %%f in (*.png) do (
	rename %%f !count!.png
	set /a count = count + 1
)
echo %count%.png
echo on
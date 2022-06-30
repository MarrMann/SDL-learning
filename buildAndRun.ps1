$buildDir = "./build/Debug"

Write-Host "Building..." -ForegroundColor Green
Invoke-Expression "cmake --build ./build"

Write-Host "Copying resources..." -ForegroundColor Green
Copy-Item -Path "./resources" -Destination "./build/Debug/resources" -Recurse -Force
Write-Host "Copying binaries..." -ForegroundColor Green
Copy-Item -Path "./bin/*" -Destination "./build/Debug" -Recurse

Write-Host "Running..." -ForegroundColor Green
Push-Location $buildDir
& "./SDLTest.exe"
Pop-Location
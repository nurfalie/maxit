# Define installer name.
Name "Maxit Installer"
outFile "Maxit-Installer-1.00.exe"

# Install directory.
installDir C:\Maxit.d

DirText "Please choose an installation directory for Maxit."

# Default section start.
section

# Define output path.
setOutPath $INSTDIR

# Specify files to go in output path.
file /r release\images.d
file release\*.dll
file release\Maxit.exe
file THEMES

# Define uninstaller name.
writeUninstaller $INSTDIR\Maxit-Uninstaller-1.00.exe

# Default section end.
sectionEnd

# Create a section to define what the uninstaller does.
# The section will always be named "Uninstall".
section "Uninstall"

# Always delete uninstaller first.
RMDir /r $INSTDIR

sectionEnd

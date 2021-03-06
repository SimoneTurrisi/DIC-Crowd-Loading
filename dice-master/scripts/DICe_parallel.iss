; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{656EC412-D2C6-4104-91F5-5CE58A8EDFEC}
AppName=Digital Image Correlation Engine (parallel)
AppVersion=1.0 (pre-release) parallel 
;AppVerName=Digital Image Correlation Engine 1.0 (pre-release)
AppPublisher=Sandia National Laboratories
AppPublisherURL=http://dice.sandia.gov/
AppSupportURL=http://dice.sandia.gov/
AppUpdatesURL=http://dice.sandia.gov/
DefaultDirName={pf}\Digital Image Correlation Engine (parallel)
DefaultGroupName=Digital Image Correlation Engine (parallel)
AllowNoIcons=yes
LicenseFile=C:\Users\dzturne\Software\dice_packages\License\License.txt
OutputDir=C:\Users\dzturne\Software\dice_packages\Output
OutputBaseFilename=DICe_setup_pre-release_parallel_0.10
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Files]
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\bin\dice.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\bin\diceutils.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\bin\diceutils.dll.manifest"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\lib\diceutils.exp"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\lib\diceutils.lib"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\bin\dicefft.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\bin\dicefft.dll.manifest"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\lib\dicefft.exp"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\lib\dicefft.lib"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\bin\dicecine.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\bin\dicecine.dll.manifest"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\lib\dicecine.exp"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\lib\dicecine.lib"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\bin\DICe_CineToTiff.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\bin\DICe_Diff.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\bin\DICe_DiffAvg.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\bin\dicebase.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\bin\dicebase.dll.manifest"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\lib\dicebase.exp"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\lib\dicebase.lib"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\bin\dice.exe.manifest"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\lib\dice.exp"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\lib\dice.lib"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\bin\dicecore.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\bin\dicecore.dll.manifest"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\lib\dicecore.exp"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice\build_msvc_mpi\lib\dicecore.lib"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice_packages\TPLs\msvcp120.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice_packages\TPLs\msvcr120.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice_packages\TPLs\msvcr120d.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice_packages\TPLs\msvcp120d.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice_packages\TPLs\libmmd.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice_packages\TPLs\tiff.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\dzturne\Software\dice_packages\TPLs\libiomp5md.dll"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\Digital Image Correlation Engine (parallel)"; Filename: "{app}\dice.exe"
Name: "{group}\{cm:UninstallProgram,Digital Image Correlation Engine (parallel)}"; Filename: "{uninstallexe}"


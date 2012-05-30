; Inno Setup Script

#define MyAppName "OSDKeys"
#define MyAppVerName "OSDKeys 2.0"
#define MyAppVersion "2.0"
#define MyAppPublisher "Matúš Sulír"
#define MyAppURL "http://suloweb.html.sk/osdkeys/"
#define MyAppExeName "osdkeys.exe"

[Setup]
AppName={#MyAppName}
AppVerName={#MyAppVerName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
VersionInfoVersion={#MyAppVersion}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
LicenseFile=..\license.txt
OutputDir=.
OutputBaseFilename=osdkeys-{#MyAppVersion}-setup
SetupIconFile=..\res\osdkeys.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"; InfoAfterFile: "after-en.txt"
Name: "slovak"; MessagesFile: "compiler:Languages\Slovak.isl"; InfoAfterFile: "after-sk.txt"

[Files]
Source: "..\osdkeys.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\license.txt"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:ProgramOnTheWeb,{#MyAppName}}"; Filename: "{#MyAppURL}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"

[Registry]
Root: HKCU; Subkey: "Software\Microsoft\Windows\CurrentVersion\Run"; ValueType: string; ValueName: "OSDKeys"; ValueData: """{app}\{#MyAppExeName}"""; Flags: uninsdeletevalue

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#MyAppName}}"; Flags: nowait postinstall skipifsilent

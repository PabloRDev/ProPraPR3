##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=UOCPlay
ConfigurationName      :=Debug
WorkspaceConfiguration :=Debug
WorkspacePath          :=C:/Users/djjar/Documents/UOC/Topo/20242-PP/PR3/UOC20242_PR3_code/UOC20242
ProjectPath            :=C:/Users/djjar/Documents/UOC/Topo/20242-PP/PR3/UOC20242_PR3_code/UOC20242/UOCPlay
IntermediateDirectory  :=../build-$(WorkspaceConfiguration)/UOCPlay
OutDir                 :=$(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=djjar
Date                   :=5/4/2025
CodeLitePath           :="C:/Program Files/CodeLite"
MakeDirCommand         :=C:/msys64/usr/bin/mkdir.exe -p
LinkerName             :=C:/msys64/mingw64/bin/g++.exe
SharedObjectLinkerName :=C:/msys64/mingw64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputDirectory        :=../lib
OutputFile             :=..\lib\lib$(ProjectName).a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
RcCmpOptions           := 
RcCompilerName         :=C:/msys64/mingw64/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)./include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
##
AR       := C:/msys64/mingw64/bin/ar.exe -r
CXX      := C:/msys64/mingw64/bin/g++.exe
CC       := C:/msys64/mingw64/bin/gcc.exe
CXXFLAGS :=  -gdwarf-2 $(Preprocessors)
CFLAGS   :=  -gdwarf-2 $(Preprocessors)
ASFLAGS  := 
AS       := C:/msys64/mingw64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/src_csv.c$(ObjectSuffix) $(IntermediateDirectory)/src_date.c$(ObjectSuffix) $(IntermediateDirectory)/src_person.c$(ObjectSuffix) $(IntermediateDirectory)/src_api.c$(ObjectSuffix) $(IntermediateDirectory)/src_watchstack.c$(ObjectSuffix) $(IntermediateDirectory)/src_subscription.c$(ObjectSuffix) $(IntermediateDirectory)/src_film.c$(ObjectSuffix) $(IntermediateDirectory)/src_show.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(IntermediateDirectory)/$(OutputFile)

$(IntermediateDirectory)/$(OutputFile): $(Objects)
	@if not exist "$(IntermediateDirectory)" $(MakeDirCommand) "$(IntermediateDirectory)"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList)
	@echo rebuilt > $(IntermediateDirectory)/UOCPlay.relink

MakeIntermediateDirs:
	@if not exist "$(IntermediateDirectory)" $(MakeDirCommand) "$(IntermediateDirectory)"
	@if not exist "$(OutputDirectory)" $(MakeDirCommand) "$(OutputDirectory)"

$(IntermediateDirectory):
	@if not exist "$(IntermediateDirectory)" $(MakeDirCommand) "$(IntermediateDirectory)"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_csv.c$(ObjectSuffix): src/csv.c 
	$(CC) $(SourceSwitch) "C:/Users/djjar/Documents/UOC/Topo/20242-PP/PR3/UOC20242_PR3_code/UOC20242/UOCPlay/src/csv.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_csv.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_csv.c$(PreprocessSuffix): src/csv.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_csv.c$(PreprocessSuffix) src/csv.c

$(IntermediateDirectory)/src_date.c$(ObjectSuffix): src/date.c 
	$(CC) $(SourceSwitch) "C:/Users/djjar/Documents/UOC/Topo/20242-PP/PR3/UOC20242_PR3_code/UOC20242/UOCPlay/src/date.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_date.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_date.c$(PreprocessSuffix): src/date.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_date.c$(PreprocessSuffix) src/date.c

$(IntermediateDirectory)/src_person.c$(ObjectSuffix): src/person.c 
	$(CC) $(SourceSwitch) "C:/Users/djjar/Documents/UOC/Topo/20242-PP/PR3/UOC20242_PR3_code/UOC20242/UOCPlay/src/person.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_person.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_person.c$(PreprocessSuffix): src/person.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_person.c$(PreprocessSuffix) src/person.c

$(IntermediateDirectory)/src_api.c$(ObjectSuffix): src/api.c 
	$(CC) $(SourceSwitch) "C:/Users/djjar/Documents/UOC/Topo/20242-PP/PR3/UOC20242_PR3_code/UOC20242/UOCPlay/src/api.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_api.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_api.c$(PreprocessSuffix): src/api.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_api.c$(PreprocessSuffix) src/api.c

$(IntermediateDirectory)/src_watchstack.c$(ObjectSuffix): src/watchstack.c 
	$(CC) $(SourceSwitch) "C:/Users/djjar/Documents/UOC/Topo/20242-PP/PR3/UOC20242_PR3_code/UOC20242/UOCPlay/src/watchstack.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_watchstack.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_watchstack.c$(PreprocessSuffix): src/watchstack.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_watchstack.c$(PreprocessSuffix) src/watchstack.c

$(IntermediateDirectory)/src_subscription.c$(ObjectSuffix): src/subscription.c 
	$(CC) $(SourceSwitch) "C:/Users/djjar/Documents/UOC/Topo/20242-PP/PR3/UOC20242_PR3_code/UOC20242/UOCPlay/src/subscription.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_subscription.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_subscription.c$(PreprocessSuffix): src/subscription.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_subscription.c$(PreprocessSuffix) src/subscription.c

$(IntermediateDirectory)/src_film.c$(ObjectSuffix): src/film.c 
	$(CC) $(SourceSwitch) "C:/Users/djjar/Documents/UOC/Topo/20242-PP/PR3/UOC20242_PR3_code/UOC20242/UOCPlay/src/film.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_film.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_film.c$(PreprocessSuffix): src/film.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_film.c$(PreprocessSuffix) src/film.c

$(IntermediateDirectory)/src_show.c$(ObjectSuffix): src/show.c 
	$(CC) $(SourceSwitch) "C:/Users/djjar/Documents/UOC/Topo/20242-PP/PR3/UOC20242_PR3_code/UOC20242/UOCPlay/src/show.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_show.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_show.c$(PreprocessSuffix): src/show.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_show.c$(PreprocessSuffix) src/show.c

##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)



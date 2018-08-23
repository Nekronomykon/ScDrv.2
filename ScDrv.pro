#-------------------------------------------------
#
# Project created by QtCreator 2018-05-25T16:14:30
#
#-------------------------------------------------

QT       += core gui widgets printsupport

TARGET = ScDrv
TEMPLATE = app
unix:DESTDIR = Build/gnu
win32:DESTDIR = Build/win

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

unix:  INCLUDEPATH += "/home/serge/VTK/include/vtk-9.0"
win32: INCLUDEPATH += "C:/Serge/VTK/include/vtk-9.0"
unix:  LIBS += -L"/home/serge/VTK/lib" \
-lvtkCommonCore-9.0 \
-lvtkCommonColor-9.0 \
-lvtkCommonMath-9.0 \
-lvtkCommonMisc-9.0 \
-lvtkCommonSystem-9.0 \
-lvtkCommonDataModel-9.0 \
-lvtkCommonExecutionModel-9.0 \
-lvtkCommonComputationalGeometry-9.0 \
-lvtkCommonTransforms-9.0 \
-lvtkDomainsChemistry-9.0 \
-lvtkDomainsChemistryOpenGL2-9.0 \
-lvtkFiltersCore-9.0 \
-lvtkFiltersGeneral-9.0 \
-lvtkFiltersGeneric-9.0 \
-lvtkFiltersSources-9.0 \
-lvtkFiltersGeometry-9.0 \
-lvtkFiltersExtraction-9.0 \
-lvtkFiltersStatistics-9.0 \
-lvtkGUISupportQt-9.0 \
-lvtkGUISupportQtSQL-9.0 \
-lvtkImagingCore-9.0 \
-lvtkImagingFourier-9.0 \
-lvtkInteractionStyle-9.0 \
-lvtkInteractionImage-9.0 \
-lvtkInteractionWidgets-9.0 \
-lvtkIOCore-9.0 \
-lvtkIOParallel-9.0 \
-lvtkIOXML-9.0 \
-lvtkIOParallelXML-9.0 \
-lvtkIOXMLParser-9.0 \
-lvtkRenderingCore-9.0 \
-lvtkRenderingQt-9.0 \
-lvtkRenderingImage-9.0 \
-lvtkRenderingLabel-9.0 \
-lvtkRenderingLOD-9.0 \
-lvtkRenderingOpenGL2-9.0 \
-lvtkRenderingGL2PSOpenGL2-9.0 \
-lvtkViewsCore-9.0 \
-lvtkViewsQt-9.0 \
-lvtkalglib-9.0 \
-lvtkdoubleconversion-9.0 \
-lvtkexpat-9.0 \
-lvtklzma-9.0 \
-lvtkglew-9.0 \
-lvtkzlib-9.0 \
-lvtklz4-9.0 \
-lvtksys-9.0
win32: LIBS += C:/Serge/VTK/lib/vtkCommonCore-9.0.lib \
C:/Serge/VTK/lib/vtkCommonColor-9.0.lib \
C:/Serge/VTK/lib/vtkCommonMath-9.0.lib \
C:/Serge/VTK/lib/vtkCommonMisc-9.0.lib \
C:/Serge/VTK/lib/vtkCommonSystem-9.0.lib \
C:/Serge/VTK/lib/vtkCommonDataModel-9.0.lib \
C:/Serge/VTK/lib/vtkCommonExecutionModel-9.0.lib \
C:/Serge/VTK/lib/vtkCommonComputationalGeometry-9.0.lib \
C:/Serge/VTK/lib/vtkCommonTransforms-9.0.lib \
C:/Serge/VTK/lib/vtkDomainsChemistry-9.0.lib \
C:/Serge/VTK/lib/vtkDomainsChemistryOpenGL2-9.0.lib \
C:/Serge/VTK/lib/vtkFiltersCore-9.0.lib \
C:/Serge/VTK/lib/vtkFiltersGeneral-9.0.lib \
C:/Serge/VTK/lib/vtkFiltersGeneric-9.0.lib \
C:/Serge/VTK/lib/vtkFiltersSources-9.0.lib \
C:/Serge/VTK/lib/vtkFiltersGeometry-9.0.lib \
C:/Serge/VTK/lib/vtkFiltersExtraction-9.0.lib \
C:/Serge/VTK/lib/vtkFiltersStatistics-9.0.lib \
C:/Serge/VTK/lib/vtkGUISupportQt-9.0.lib \
C:/Serge/VTK/lib/vtkGUISupportQtSQL-9.0.lib \
C:/Serge/VTK/lib/vtkImagingCore-9.0.lib \
C:/Serge/VTK/lib/vtkImagingFourier-9.0.lib \
C:/Serge/VTK/lib/vtkInteractionStyle-9.0.lib \
C:/Serge/VTK/lib/vtkInteractionImage-9.0.lib \
C:/Serge/VTK/lib/vtkInteractionWidgets-9.0.lib \
C:/Serge/VTK/lib/vtkIOCore-9.0.lib \
C:/Serge/VTK/lib/vtkIOParallel-9.0.lib \
C:/Serge/VTK/lib/vtkIOXML-9.0.lib \
C:/Serge/VTK/lib/vtkIOParallelXML-9.0.lib \
C:/Serge/VTK/lib/vtkIOXMLParser-9.0.lib \
C:/Serge/VTK/lib/vtkRenderingCore-9.0.lib \
C:/Serge/VTK/lib/vtkRenderingQt-9.0.lib \
C:/Serge/VTK/lib/vtkRenderingLOD-9.0.lib \
C:/Serge/VTK/lib/vtkRenderingImage-9.0.lib \
C:/Serge/VTK/lib/vtkRenderingLabel-9.0.lib \
C:/Serge/VTK/lib/vtkRenderingOpenGL2-9.0.lib \
C:/Serge/VTK/lib/vtkRenderingGL2PSOpenGL2-9.0.lib \
C:/Serge/VTK/lib/vtkViewsCore-9.0.lib \
C:/Serge/VTK/lib/vtkViewsQt-9.0.lib \
C:/Serge/VTK/lib/vtkdoubleconversion-9.0.lib \
C:/Serge/VTK/lib/vtkexpat-9.0.lib \
C:/Serge/VTK/lib/vtkglew-9.0.lib \
C:/Serge/VTK/lib/vtksys-9.0.lib
win32:QMAKE_EXTRA_TARGETS += before_build makefilehook
win32:makefilehook.target = $(MAKEFILE)
win32:makefilehook.depends = .beforebuild
win32:PRE_TARGETDEPS += .beforebuild
win32:before_build.target = .beforebuild
win32:before_build.depends = FORCE
win32:before_build.commands = chcp 1251

SOURCES += \
        main.cpp \
    FrameFile.cpp \
    MoleculeAcquireBase.cpp \
    MoleculeAcquireFile.cpp \
    MoleculeAcquireFileWFN.cpp \
    MoleculeAcquireFileXYZ.cpp \
    MoleculeAcquireFileQTAIM.cpp \
    MoleculeAcquireFileCUBE.cpp \
    ResetCursor.cpp \
    TraitsAcquireAtoms.cpp \
    CodeEditor.cpp \
    FrameFile.cpp \
    main.cpp \
    MoleculeAcquireBase.cpp \
    MoleculeAcquireFile.cpp \
    MoleculeAcquireFileCUBE.cpp \
    MoleculeAcquireFileQTAIM.cpp \
    MoleculeAcquireFileWFN.cpp \
    MoleculeAcquireFileXYZ.cpp \
    QVTKMoleculeWidget.cpp \
    ResetCursor.cpp \
    SideBarDecorator.cpp \
    TraitsAcquireAtoms.cpp \
    FrameWorkspace.cpp \
    ModelTextFiles.cpp \
    EditTextSource.cpp \
    CodeEditor.cpp \
    EditTextSource.cpp \
    FrameFile.cpp \
    FrameWorkspace.cpp \
    main.cpp \
    ModelTextFiles.cpp \
    MoleculeAcquireBase.cpp \
    MoleculeAcquireFile.cpp \
    MoleculeAcquireFileCUBE.cpp \
    MoleculeAcquireFileQTAIM.cpp \
    MoleculeAcquireFileWFN.cpp \
    MoleculeAcquireFileXYZ.cpp \
    QVTKMoleculeWidget.cpp \
    ResetCursor.cpp \
    SideBarDecorator.cpp \
    TraitsAcquireAtoms.cpp \
    BrowseFiles.cpp \
    ViewWorkspace.cpp \
    MolecularStructure.cpp \
    ViewMoleculeAtomic.cpp \
    ModelMoleculeAtomic.cpp \
    ModelElements.cpp \
    DelegateElements.cpp \
    TableElements.cpp \
    ViewFilesystem.cpp \
    DelegateElements.cpp \
    ViewFilesystem.cpp \
    ModelWorkspace.cpp \
    BondsetBuild.cpp \
    BrowseFiles.cpp \
    CheckComboBox.cpp \
    CodeEditor.cpp \
    DelegateElements.cpp \
    EditTextSource.cpp \
    FileFormat.cpp \
    FrameFile.cpp \
    FrameWorkspace.cpp \
    main.cpp \
    ModelElements.cpp \
    ModelMoleculeAtomic.cpp \
    ModelTextFiles.cpp \
    ModelWorkspace.cpp \
    MolecularStructure.cpp \
    MoleculeAcquireBase.cpp \
    MoleculeAcquireFile.cpp \
    MoleculeAcquireFileCUBE.cpp \
    MoleculeAcquireFileQTAIM.cpp \
    MoleculeAcquireFileWFN.cpp \
    MoleculeAcquireFileXYZ.cpp \
    QVTKMoleculeWidget.cpp \
    ResetCursor.cpp \
    SideBarDecorator.cpp \
    TableElements.cpp \
    TraitsAcquireAtoms.cpp \
    ViewFilesystem.cpp \
    ViewMoleculeAtomic.cpp \
    ViewWorkspace.cpp \
    ElementData.cpp \
    Elements.cpp \
    QVTKMoleculeMapStyle.cpp \
    ElementDataParser.cpp \
    ModelMolecularBondset.cpp

HEADERS += \
    FrameFile.h \
    ResetCursor.h \
    MoleculeAcquireBase.h \
    MoleculeAcquireFile.h \
    MoleculeAcquireFileWFN.h \
    MoleculeAcquireFileXYZ.h \
    ImplFileName.h \
    MoleculeAcquireBase.h \
    MoleculeAcquireFile.h \
    MoleculeAcquireFileWFN.h \
    MoleculeAcquireFileXYZ.h \
    MoleculeAcquireFileQTAIM.h \
    MoleculeAcquireFileCUBE.h \
    TraitsAcquireAtoms.h \
    CodeEditor.h \
    FrameFile.h \
    ImplFileName.h \
    MoleculeAcquireBase.h \
    MoleculeAcquireFile.h \
    MoleculeAcquireFileCUBE.h \
    MoleculeAcquireFileQTAIM.h \
    MoleculeAcquireFileWFN.h \
    MoleculeAcquireFileXYZ.h \
    QVTKMoleculeWidget.h \
    ResetCursor.h \
    SideBarDecorator.h \
    TraitsAcquireAtoms.h \
    FileFormatContext.h \
    FrameWorkspace.h \
    ModelTextFiles.h \
    EditTextSource.h \
    CodeEditor.h \
    EditTextSource.h \
    FileFormat.h \
    FrameFile.h \
    FrameWorkspace.h \
    ImplFileName.h \
    ModelTextFiles.h \
    MoleculeAcquireBase.h \
    MoleculeAcquireFile.h \
    MoleculeAcquireFileCUBE.h \
    MoleculeAcquireFileQTAIM.h \
    MoleculeAcquireFileWFN.h \
    MoleculeAcquireFileXYZ.h \
    QVTKMoleculeWidget.h \
    ResetCursor.h \
    SideBarDecorator.h \
    TraitsAcquireAtoms.h \
    BrowseFiles.h \
    ViewWorkspace.h \
    MolecularStructure.h \
    ViewMoleculeAtomic.h \
    ModelMoleculeAtomic.h \
    ModelElements.h \
    DelegateElements.h \
    TableElements.h \
    ViewFilesystem.h \
    DelegateElements.h \
    ViewFilesystem.h \
    ModelWorkspace.h \
    BondsetBuild.h \
    BrowseFiles.h \
    CheckComboBox.h \
    CodeEditor.h \
    DelegateElements.h \
    EditTextSource.h \
    FileFormat.h \
    FrameFile.h \
    FrameWorkspace.h \
    ImplFileName.h \
    ImplModelView.h \
    ModelElements.h \
    ModelMoleculeAtomic.h \
    ModelTextFiles.h \
    ModelWorkspace.h \
    MolecularStructure.h \
    MoleculeAcquireBase.h \
    MoleculeAcquireFile.h \
    MoleculeAcquireFileCUBE.h \
    MoleculeAcquireFileQTAIM.h \
    MoleculeAcquireFileWFN.h \
    MoleculeAcquireFileXYZ.h \
    QVTKMoleculeWidget.h \
    ResetCursor.h \
    SideBarDecorator.h \
    TableElements.h \
    TraitsAcquireAtoms.h \
    ViewFilesystem.h \
    ViewMoleculeAtomic.h \
    ViewWorkspace.h \
    ElementData.h \
    Elements.h \
    QVTKMoleculeMapStyle.h \
    ElementDataParser.h \
    ElementDataInternal.h \
    ModelMolecularBondset.h

FORMS += \
    FrameWorkspace.ui \
    FrameWorkspace.ui \
    FrameWorkspace.ui

RESOURCES += \
    ScDrv.qrc \
    ScDrv.qrc \
    ScDrv.qrc \
    ScDrv.qrc

DISTFILES += \
    CMakeLists.txt \
    CMakeLists.txt \
    CONTRIBUTORS.md \
    README.md \
    CMakeLists.txt \
    README.md \
    CMakeLists.txt

SUBDIRS += \
    ScDrv.pro \
    ScDrv.pro \
    ScDrv.pro


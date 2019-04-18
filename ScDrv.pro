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

unix:  INCLUDEPATH += "/home/serge/VTK/include/vtk-8.90"
win32: INCLUDEPATH += "C:/Serge/VTK/include/vtk-8.90"
unix:  LIBS += -L"/home/serge/VTK/lib" \
-lvtkCommonCore-8.90 \
-lvtkCommonColor-8.90 \
-lvtkCommonMath-8.90 \
-lvtkCommonMisc-8.90 \
-lvtkCommonSystem-8.90 \
-lvtkCommonDataModel-8.90 \
-lvtkCommonExecutionModel-8.90 \
-lvtkCommonComputationalGeometry-8.90 \
-lvtkCommonTransforms-8.90 \
-lvtkDomainsChemistry-8.90 \
-lvtkDomainsChemistryOpenGL2-8.90 \
-lvtkFiltersCore-8.90 \
-lvtkFiltersGeneral-8.90 \
-lvtkFiltersGeneric-8.90 \
-lvtkFiltersSources-8.90 \
-lvtkFiltersGeometry-8.90 \
-lvtkFiltersExtraction-8.90 \
-lvtkFiltersStatistics-8.90 \
-lvtkGUISupportQt-8.90 \
-lvtkGUISupportQtSQL-8.90 \
-lvtkImagingCore-8.90 \
-lvtkImagingFourier-8.90 \
-lvtkInteractionStyle-8.90 \
-lvtkInteractionImage-8.90 \
-lvtkInteractionWidgets-8.90 \
-lvtkIOCore-8.90 \
-lvtkIOParallel-8.90 \
-lvtkIOXML-8.90 \
-lvtkIOParallelXML-8.90 \
-lvtkIOXMLParser-8.90 \
-lvtkRenderingCore-8.90 \
-lvtkRenderingQt-8.90 \
-lvtkRenderingImage-8.90 \
-lvtkRenderingLabel-8.90 \
-lvtkRenderingLOD-8.90 \
-lvtkRenderingOpenGL2-8.90 \
-lvtkRenderingGL2PSOpenGL2-8.90 \
-lvtkViewsCore-8.90 \
-lvtkViewsQt-8.90 \
-lvtkalglib-8.90 \
-lvtkdoubleconversion-8.90 \
-lvtkexpat-8.90 \
-lvtklzma-8.90 \
-lvtkglew-8.90 \
-lvtkzlib-8.90 \
-lvtklz4-8.90 \
-lvtksys-8.90
win32: LIBS += C:/Serge/VTK/lib/vtkCommonCore-8.90.lib \
C:/Serge/VTK/lib/vtkCommonColor-8.90.lib \
C:/Serge/VTK/lib/vtkCommonMath-8.90.lib \
C:/Serge/VTK/lib/vtkCommonMisc-8.90.lib \
C:/Serge/VTK/lib/vtkCommonSystem-8.90.lib \
C:/Serge/VTK/lib/vtkCommonDataModel-8.90.lib \
C:/Serge/VTK/lib/vtkCommonExecutionModel-8.90.lib \
C:/Serge/VTK/lib/vtkCommonComputationalGeometry-8.90.lib \
C:/Serge/VTK/lib/vtkCommonTransforms-8.90.lib \
C:/Serge/VTK/lib/vtkDomainsChemistry-8.90.lib \
C:/Serge/VTK/lib/vtkDomainsChemistryOpenGL2-8.90.lib \
C:/Serge/VTK/lib/vtkFiltersCore-8.90.lib \
C:/Serge/VTK/lib/vtkFiltersGeneral-8.90.lib \
C:/Serge/VTK/lib/vtkFiltersGeneric-8.90.lib \
C:/Serge/VTK/lib/vtkFiltersSources-8.90.lib \
C:/Serge/VTK/lib/vtkFiltersGeometry-8.90.lib \
C:/Serge/VTK/lib/vtkFiltersExtraction-8.90.lib \
C:/Serge/VTK/lib/vtkFiltersStatistics-8.90.lib \
C:/Serge/VTK/lib/vtkGUISupportQt-8.90.lib \
C:/Serge/VTK/lib/vtkGUISupportQtSQL-8.90.lib \
C:/Serge/VTK/lib/vtkImagingCore-8.90.lib \
C:/Serge/VTK/lib/vtkImagingFourier-8.90.lib \
C:/Serge/VTK/lib/vtkInteractionStyle-8.90.lib \
C:/Serge/VTK/lib/vtkInteractionImage-8.90.lib \
C:/Serge/VTK/lib/vtkInteractionWidgets-8.90.lib \
C:/Serge/VTK/lib/vtkIOCore-8.90.lib \
C:/Serge/VTK/lib/vtkIOParallel-8.90.lib \
C:/Serge/VTK/lib/vtkIOXML-8.90.lib \
C:/Serge/VTK/lib/vtkIOParallelXML-8.90.lib \
C:/Serge/VTK/lib/vtkIOXMLParser-8.90.lib \
C:/Serge/VTK/lib/vtkRenderingCore-8.90.lib \
C:/Serge/VTK/lib/vtkRenderingQt-8.90.lib \
C:/Serge/VTK/lib/vtkRenderingLOD-8.90.lib \
C:/Serge/VTK/lib/vtkRenderingImage-8.90.lib \
C:/Serge/VTK/lib/vtkRenderingLabel-8.90.lib \
C:/Serge/VTK/lib/vtkRenderingOpenGL2-8.90.lib \
C:/Serge/VTK/lib/vtkRenderingGL2PSOpenGL2-8.90.lib \
C:/Serge/VTK/lib/vtkViewsCore-8.90.lib \
C:/Serge/VTK/lib/vtkViewsQt-8.90.lib \
C:/Serge/VTK/lib/vtkdoubleconversion-8.90.lib \
C:/Serge/VTK/lib/vtkexpat-8.90.lib \
C:/Serge/VTK/lib/vtkglew-8.90.lib \
C:/Serge/VTK/lib/vtksys-8.90.lib
win32:QMAKE_EXTRA_TARGETS += before_build makefilehook
win32:makefilehook.target = $(MAKEFILE)
win32:makefilehook.depends = .beforebuild
win32:PRE_TARGETDEPS += .beforebuild
win32:before_build.target = .beforebuild
win32:before_build.depends = FORCE
win32:before_build.commands = chcp 1251

SOURCES += \
        main.cpp \
    BondsetBuild.cpp \
    BrowseFiles.cpp \
    CheckComboBox.cpp \
    CodeEditor.cpp \
    EditTextSource.cpp \
    ElementData.cpp \
    ElementDataParser.cpp \
    Elements.cpp \
    FileFormat.cpp \
    FrameFile.cpp \
    FrameWorkspace.cpp \
    ModelElements.cpp \
    ModelMoleculeAtomic.cpp \
    ModelMolecularBondset.cpp \
    ModelTextFiles.cpp \
    ModelWorkspace.cpp \
    MolecularStructure.cpp \
    MoleculeAcquireBase.cpp \
    MoleculeAcquireFile.cpp \
    MoleculeAcquireFileWFN.cpp \
    MoleculeAcquireFileXYZ.cpp \
    MoleculeAcquireFileQTAIM.cpp \
    MoleculeAcquireFileCUBE.cpp \
    QVTKMoleculeMapStyle.cpp \
    QVTKMoleculeWidget.cpp \
    ResetCursor.cpp \
    SideBarDecorator.cpp \
    TableElements.cpp \
    TraitsAcquireAtoms.cpp \
    ViewFilesystem.cpp \
    ViewMoleculeAtomic.cpp \
    ViewMoleculeBonds.cpp \
    ViewWorkspace.cpp \
    DelegateElementSpin.cpp \
    DelegateElementTable.cpp \
    TableAtomTypes.cpp \
    FrameFile.cpp

HEADERS += \
    BondsetBuild.h \
    BrowseFiles.h \
    CheckComboBox.h \
    CodeEditor.h \
    Elements.h \
    ElementData.h \
    ElementDataParser.h \
    ElementDataInternal.h \
    EditTextSource.h \
    FileFormat.h \
    FrameFile.h \
    FrameWorkspace.h \
    ImplFileName.h \
    ImplModelView.h \
    ModelElements.h \
    ModelMoleculeAtomic.h \
    ModelMolecularBondset.h \
    ModelTextFiles.h \
    ModelWorkspace.h \
    MolecularStructure.h \
    MoleculeAcquireBase.h \
    MoleculeAcquireFile.h \
    MoleculeAcquireFileWFN.h \
    MoleculeAcquireFileXYZ.h \
    MoleculeAcquireFileQTAIM.h \
    MoleculeAcquireFileCUBE.h \
    QVTKMoleculeMapStyle.h \
    QVTKMoleculeWidget.h \
    ResetCursor.h \
    SideBarDecorator.h \
    TableElements.h \
    TraitsAcquireAtoms.h \
    ViewFilesystem.h \
    ViewMoleculeAtomic.h \
    ViewMoleculeBonds.h \
    ViewWorkspace.h \
    DelegateElementSpin.h \
    DelegateElementTable.h \
    TableAtomTypes.h

FORMS += \
    FrameWorkspace.ui \
    ViewSource.ui \
    Generator.ui

RESOURCES += \
    ScDrv.qrc

DISTFILES += \
    CMakeLists.txt \
    CONTRIBUTORS.md \
    README.md

SUBDIRS += \
    ScDrv.pro


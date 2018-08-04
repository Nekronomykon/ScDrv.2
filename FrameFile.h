#ifndef __Frame_File_h__
#define __Frame_File_h__

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QPointer>
#include <QString>
#include <QStringList>
#include <QWidget>
#include <QMap>

#include <QTabWidget>
#include "ImplFileName.h"

#include <QToolButton>
#include <vtkNew.h>
#include <vtkSmartPointer.h>

#include <vtkMolecule.h>

#include "CodeEditor.h"
#include "QVTKMoleculeWidget.h"
// temporary view header to implement table views of atoms / bonds in Molecule
#include <vtkQtTableView.h>

#include "MoleculeAcquireFile.h"

#include "FileFormatContext.h"


class FrameFile
        : public QTabWidget
        , public ImplFileName<FrameFile, QString>
{
    Q_OBJECT
public:
    FrameFile(QWidget * /*parent*/ = Q_NULLPTR);
    ~FrameFile() override;

    typedef FileFormatContext<FrameFile> FileContext;

    void InterpretFileName();

    static FrameFile *New(QWidget * /*parent*/ = Q_NULLPTR);
    static QStringList getRecentFiles() { return recent_files; }

    static QString GetFileInputContextString();
    static void BuildFileContext();
    static void SetupFileInputContext(const QString &);
    static void ClearFileInputContext();

    bool readSource(const QString &);
    template<class T>
    bool applyReaderType()
    {
        // convert to const char*
        QString str = this->getEditSource()->getDumpPath();
        if(!str.isEmpty())
        {
            vtkSmartPointer<MoleculeAcquireFile> reader(vtkSmartPointer<T>::New());
            QByteArray bytes = str.toLatin1();
            reader->ResetFileName(bytes.data());
            reader->SetOutput(a_molecule_);
            a_molecule_->Initialize();
            reader->Update();
        }
        return bool(a_molecule_->GetNumberOfAtoms() > 0);
    }

    bool readContentXYZ();
    bool readContentWFN();
    bool readContentCUBE();
    bool readContentNone();

    CodeEditor* getEditSource() const {return edit_source_;}
private:
    static QStringList recent_files;
    static QMap<FileContext,QString> all_formats;
    static FileContext fmt_active;
    static const size_t num_formats;

    FileContext format_current_;

    vtkNew<vtkMolecule> a_molecule_;

    //QPointer <QToolButton> extend_;
    //QPointer <QToolButton> compress_;

    QPointer<CodeEditor> edit_source_;
    QPointer<QVTKMoleculeWidget> view_molecule_;
};

#endif // !__Frame_File_h__

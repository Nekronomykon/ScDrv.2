#ifndef Frame_File__H_
#define Frame_File__H_

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

// #include <filesystem>

#include <QPointer>

#include <vtkMolecule.h>

#include <vtkNew.h>
#include <vtkSmartPointer.h>

#include <QTabWidget>
#include <QSplitter>

#include <vtkVectorFieldTopology.h>

#include <vtkMoleculeAlgorithm.h>
#include <vtkMoleculeReaderBase.h>

#include "ReadMoleculeFileMGP.h"

#include "StyleMapMolecule.h"

#include "EditCode.h"
#include "ViewMolecule.h"
#include "ViewQuantities.h"

#include "FormatFor.h"

typedef vtkNew<vtkMolecule> NewMolecule;
typedef vtkSmartPointer<vtkMolecule> AMolecule;

typedef vtkNew<vtkMoleculeAlgorithm> NewMolAlgorithm;
typedef vtkSmartPointer<vtkMoleculeAlgorithm> AMolAlgorithm;

typedef vtkNew<vtkVectorFieldTopology> NewFieldTopology;
typedef vtkSmartPointer<vtkVectorFieldTopology> AFieldTopology;

using namespace std;
using namespace vtk;

class FrameFile;

typedef FileFormatFor<FrameFile> FileFormat;

class FrameFile : public QTabWidget
{
  Q_OBJECT

private:
  static const FileFormat formatInput[];

public:
  static QString filterInput();
  static QString filterOutput();

  static QString QuerySavePath(QWidget *parent, QString src, QString & /* context */);

public:
  explicit FrameFile(QWidget * /*parent*/ = nullptr);

  bool isUntitled() const;
  bool hasSourcePath() const;
  const QString &pathSource() const;

  EditCode *editSource();
  EditCode *getEditSource() const;
  QTextDocument *getSourceDocument() const;

  ViewMolecule *viewMolecule();
  ViewMolecule *getViewMolecule() const;

  QString describeInputFormats() const;

  bool changePathToBind(bool bSync = false);

  bool querySave();
  void doSave();
  bool isModified() const;
  bool hasPendingTasks() const;
  bool canBeClosed() const;
  bool openTextFile(const QString & /* path */, bool /* bExistent */ = true);

  void ParseXYZ();
  void ParsePDB();
  void ParseCUBE();
  void ParseEXTOUT();
  void ParseMGP();
  void ParseSUM();

  // signals:

protected:
  bool SourceToStructure();
  void ShowTheStructure();

  template <class Reader>
  void ReadMoleculeAs();

private:
  // std::filesystem::path path_bound_;
  QString path_src_bound_ = QString();
  //
  // AMoleculeField molecule_;
  //
  // QPointer<FormStructureText> source_;
  // QPointer<FormStructureView> view_;

  // StyleMapMolecule styleMapMol_;

  // QByteArray state_;
  // QPointer<QSplitter> split_;
  // QPointer<ViewStructure> view_str_;
  // int id_view_str_;
  //
  QPointer<EditCode> edit_src_;
  int id_edit_src_ = -1;
  QPointer<ViewMolecule> view_mol_;
  int id_view_mol_ = -1;
  QPointer<ViewQuantities> view_val_;
  int id_view_val_ = -1;

  AMolecule molecule_;
  AFieldTopology field_;

  AMolAlgorithm make_bonds_;

  QWidget *ptrActiveWidget_ = nullptr;

private slots:
  void castChangedViews(int id);
};

#endif // Frame_File__H_

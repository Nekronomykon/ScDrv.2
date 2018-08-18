#ifndef Impl_ModelView_h
#define Impl_ModelView_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <QWidget>

template <class T, class TBase, class TModel>
class ImplModelView
    : public TBase
{
  // Q_OBJECT
public:
  typedef TBase Base;
  typedef TModel Model;
  ImplModelView(QWidget *parent = nullptr)
      : TBase(parent), ptrModel_(new Model)
  {
    assert(ptrModel_);
    this->setModel(ptrModel_);
  }
  Model* getViewModel() const {return ptrModel_;}

private:
  Model *ptrModel_;
};

#endif // !Impl_ModelView_h

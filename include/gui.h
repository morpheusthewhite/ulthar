#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QFormLayout>
#include <QLineEdit>
class Gui : public QWidget
{
    Q_OBJECT
public:
    explicit Gui(QWidget *parent = nullptr);

signals:

public slots:

private:
    QFrame* mLeftFrame;
    QPushButton* mExportButton;
    QLabel* mPreviewLabel;
    QHBoxLayout* mLayout;
    QFormLayout* mLeftFrameLayout;
    QLabel* mDefinitionLabel;
    QLineEdit* mDefinionLineEdit;
};

#endif // GUI_H

#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>

class Gui : public QWidget
{
    Q_OBJECT
public:
    explicit Gui(QWidget *parent = nullptr);

signals:

public slots:

private:
    QPushButton* mExportButton;
    QHBoxLayout* mLayout;
    QLabel* mPreviewLabel;
};

#endif // GUI_H

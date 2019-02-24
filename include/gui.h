#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>

#define COORDINATES_PRECISION 3
#define COORDINATES_MIN       -10
#define COORDINATES_MAX       10
#define COORDINATES_STEP      0.1

class Gui : public QWidget
{
    Q_OBJECT
public:
    explicit Gui(QWidget *parent = nullptr);

signals:

public slots:

private:
    QFrame* mLeftFrame;
    QFormLayout* mLeftFrameLayout;

    QLabel* mDefinitionLabel;
    QSpinBox* mDefinionSpinBox;

    QLabel* mStartLabel;
    QDoubleSpinBox* mStartX;
    QDoubleSpinBox* mStartY;
    QHBoxLayout* mStartCoordinatesLayout;
    QLabel* mEndLabel;
    QDoubleSpinBox* mEndX;
    QDoubleSpinBox* mEndY;
    QHBoxLayout* mEndCoordinatesLayout;

    QLabel* mOutPathLabel;
    QLineEdit* mOutPathLineEdit;
    QPushButton* mOutPathSelect;
    QHBoxLayout* mOutPathLayout;

    QPushButton* mExportButton;
    QPushButton* mColorsButton;
    QHBoxLayout* mButtonsLayout;
    QFrame* mButtonsFrame;

    QLabel* mPreviewLabel;

    QHBoxLayout* mLayout;
};

#endif // GUI_H

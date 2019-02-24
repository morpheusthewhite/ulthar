#include "gui.h"
#include <QImageReader>


QDoubleSpinBox* getCoordinatesSpinBox(QWidget* parent=nullptr){
    QDoubleSpinBox* spinbox = new QDoubleSpinBox(parent);
    spinbox->setDecimals(COORDINATES_PRECISION);
    spinbox->setSingleStep(COORDINATES_STEP);
    spinbox->setRange(COORDINATES_MIN, COORDINATES_MAX);

    return spinbox;
}


Gui::Gui(QWidget *parent) : QWidget(parent)
{
    /* initializing left box */
    // left frame containing all widgets
    mLeftFrame = new QFrame(this);
    // its layout
    mLeftFrameLayout = new QFormLayout();

    // setting the row of the starting coordinates
    mStartLabel = new QLabel("Start coordinates", mLeftFrame);
    // setting up spinbox (the others will be bare copies of it)
    mStartX = getCoordinatesSpinBox();
    mStartY = getCoordinatesSpinBox();
    mStartCoordinatesLayout = new QHBoxLayout();
    mStartCoordinatesLayout->addWidget(mStartX);
    mStartCoordinatesLayout->addWidget(mStartY);
    mLeftFrameLayout->addRow(mStartLabel, mStartCoordinatesLayout);

    // setting the row of the ending coordinates
    mEndLabel = new QLabel("End coordinates", mLeftFrame);
    mEndX = getCoordinatesSpinBox();
    mEndY = getCoordinatesSpinBox();
    mEndCoordinatesLayout = new QHBoxLayout();
    mEndCoordinatesLayout->addWidget(mEndX);
    mEndCoordinatesLayout->addWidget(mEndY);
    mLeftFrameLayout->addRow(mEndLabel, mEndCoordinatesLayout);

    // row for asking for the definition of the final image
    mDefinitionLabel = new QLabel("Definition", mLeftFrame);
    mDefinionSpinBox = new QSpinBox(mLeftFrame);
    mDefinionSpinBox->setMaximum(100);
    mLeftFrameLayout->addRow(mDefinitionLabel, mDefinionSpinBox);

    mOutPathLabel = new QLabel("Saving to");
    mOutPathLineEdit = new QLineEdit();
    mOutPathSelect = new QPushButton("Select Folder");
    mOutPathLayout = new QHBoxLayout();
    mOutPathLayout->addWidget(mOutPathLineEdit);
    mOutPathLayout->addWidget(mOutPathSelect);
    mLeftFrameLayout->addRow(mOutPathLabel, mOutPathLayout);

    // the export button
    mColorsButton = new QPushButton("Colors");
    mExportButton = new QPushButton("Export");
    mButtonsLayout = new QHBoxLayout();
    mButtonsLayout->addWidget(mColorsButton);
    mButtonsLayout->addWidget(mExportButton);
    mButtonsFrame = new QFrame();
    mButtonsFrame->setLayout(mButtonsLayout);
    mLeftFrameLayout->addWidget(mButtonsFrame);

    // setting the layout for the left box
    mLeftFrame->setLayout(mLeftFrameLayout);

    /* setting right box */
    mPreviewLabel = new QLabel();
    mPreviewLabel->setPixmap(QPixmap("/home/francesco/GitHub Projects/ulthar/out.jpeg"));

    /* setting layout of the right box */
    mLayout = new QHBoxLayout();
    mLayout->addWidget(mLeftFrame);
    mLayout->addWidget(mPreviewLabel);

    this->setLayout(mLayout);

}


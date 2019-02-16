#include "gui.h"

Gui::Gui(QWidget *parent) : QWidget(parent)
{
    /* initializing left box */
    mLeftFrame = new QFrame(this);
    mExportButton = new QPushButton("Export", mLeftFrame);
    mDefinitionLabel = new QLabel("Definition", mLeftFrame);
    mDefinionLineEdit = new QLineEdit(mLeftFrame);

    /* setting layout of the left box */
    mLeftFrameLayout = new QFormLayout();
    mLeftFrameLayout->addWidget(mExportButton);
    mLeftFrameLayout->addRow(mDefinitionLabel, mDefinionLineEdit);

    mLeftFrame->setLayout(mLeftFrameLayout);


    /* setting right box */
    mPreviewLabel = new QLabel(this);
    QPixmap pixmap("out.jpeg");
    mPreviewLabel->setPixmap(pixmap);

    /* setting layout of the right box */
    mLayout = new QHBoxLayout();
    mLayout->addWidget(mExportButton);
    mLayout->addWidget(mPreviewLabel);

    this->setLayout(mLayout);
}


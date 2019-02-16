#include "gui.h"

Gui::Gui(QWidget *parent) : QWidget(parent)
{
    mLayout = new QHBoxLayout();

    mExportButton = new QPushButton("Export", this);

    mPreviewLabel = new QLabel(this);
    QPixmap pixmap("out.jpeg");
    mPreviewLabel->setPixmap(pixmap);

    mLayout->addWidget(mExportButton);
    mLayout->addWidget(mPreviewLabel);

    this->setLayout(mLayout);
}

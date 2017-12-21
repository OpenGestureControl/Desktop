#include "testwindowinformation.h"

void TestWindowInformation::getCorrectWindowTitle()
{
    // Arrange
    WindowInformation *info = new WindowInformation();
    QString title;

    // Act
    title = info->GetWindowTitle();

    // Assert
    Q_ASSERT(title.toStdString() == "QtCreator");
}

/*
   Copyright (c) 2017 ICT Group

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

#include "testmoduleoptionsmodel.h"

void TestModuleOptionsModel::storingAndRetrievingOptions()
{
    // Arrange
    QString name = "Example option";
    QString icon = "test.png";

    ModuleOptionsModel *moduleOptionsModel = new ModuleOptionsModel();
    ModuleOption *moduleOption = new ModuleOption(name, icon, 1);

    // Act
    moduleOptionsModel->addOption(moduleOption);
    ModuleOption *retrievedModuleOption = moduleOptionsModel->get(0);

    // Assert
    QVERIFY(retrievedModuleOption->name() == name);
    QVERIFY(retrievedModuleOption->icon() == icon);
}

void TestModuleOptionsModel::storingAndRetrievingDuplicateOptions()
{
    // Arrange
    bool result;
    QString name = "Example option";
    QString icon = "test.png";

    ModuleOptionsModel *moduleOptionsModel = new ModuleOptionsModel();
    ModuleOption *moduleOption = new ModuleOption(name, icon, 1);

    moduleOptionsModel->addOption(moduleOption);

    // Act
    result = moduleOptionsModel->addOption(moduleOption);

    // Assert
    QVERIFY(result == false);
    QVERIFY(moduleOptionsModel->rowCount() == 1);
}

void TestModuleOptionsModel::getCorrectOptionsCount()
{
    // Arrange
    QString name1 = "Example option 1";
    QString name2 = "Example option 2";
    QString name3 = "Example option 3";
    QString icon1 = "test1.png";
    QString icon2 = "test2.png";
    QString icon3 = "test3.png";

    ModuleOptionsModel *moduleOptionsModel = new ModuleOptionsModel();
    ModuleOption *moduleOption1 = new ModuleOption(name1, icon1, 1);
    ModuleOption *moduleOption2 = new ModuleOption(name2, icon2, 2);
    ModuleOption *moduleOption3 = new ModuleOption(name3, icon3, 3);

    moduleOptionsModel->addOption(moduleOption1);
    moduleOptionsModel->addOption(moduleOption2);
    moduleOptionsModel->addOption(moduleOption3);

    // Act
    int deviceCount = moduleOptionsModel->rowCount();

    // Assert
    QVERIFY(deviceCount == 3);
}

void TestModuleOptionsModel::correctlyClearOptionsCount()
{
    // Arrange
    QString name1 = "Example option 1";
    QString name2 = "Example option 2";
    QString name3 = "Example option 3";
    QString icon1 = "test1.png";
    QString icon2 = "test2.png";
    QString icon3 = "test3.png";

    ModuleOptionsModel *moduleOptionsModel = new ModuleOptionsModel();
    ModuleOption *moduleOption1 = new ModuleOption(name1, icon1, 1);
    ModuleOption *moduleOption2 = new ModuleOption(name2, icon2, 2);
    ModuleOption *moduleOption3 = new ModuleOption(name3, icon3, 3);

    moduleOptionsModel->addOption(moduleOption1);
    moduleOptionsModel->addOption(moduleOption2);
    moduleOptionsModel->addOption(moduleOption3);

    // Act
    moduleOptionsModel->clear();

    // Assert
    QVERIFY(moduleOptionsModel->rowCount() == 0);
}

void TestModuleOptionsModel::retrieveIncorrectRoleData()
{
    // Arrange
    QVariant qvar;
    const QModelIndex qindex;
    QString name = "Example option";
    QString icon = "test.png";

    ModuleOptionsModel *moduleOptionsModel = new ModuleOptionsModel();
    ModuleOption *moduleOption = new ModuleOption(name, icon, 1);

    moduleOptionsModel->addOption(moduleOption);

    // Act
    qvar = moduleOptionsModel->data(qindex, 0);

    // Assert
    QVERIFY(qvar.isValid() == false);
}

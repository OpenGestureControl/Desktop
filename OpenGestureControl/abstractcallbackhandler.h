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

#ifndef ABSTRACTCALLBACKHANDLER_H
#define ABSTRACTCALLBACKHANDLER_H

#include <QtGlobal>

#include <QDebug>
#include <QList>
#include <QObject>
#include <QString>
#include <QUrl>
#include <QDesktopServices>
#include <QMessageBox>

#include <lua.hpp>

#include <functional>
#include <sstream>

#include "modulemanager.h"
#include "moduleoptionslistmodel.h"
#include "moduleoption.h"

/*! \brief A class which handles callbacks from the piemenu.
 *
 *  This class is created to be attached to an options in the piemenu.
 *  When that option is selected this class is activated to execute the selected option.
 *  The action to perform for each option is retrieved from the Lua module.
 */

class AbstractCallbackHandler : public QObject
{
    Q_OBJECT
public:
    /*! \brief The constructor.
     *
     *  This constructor instantiates this class.
     *  When this constructor is called it requests the name of the current foreground application.
     *  It uses this name to define which Lua module to call (currently only browser and music module).
     */
    explicit AbstractCallbackHandler(QObject *parent = 0 /*!< [in] optional parameter, a QObject pointer to the parent of this class.*/);

    /*! \brief This function initializes the callbackhandler for usage of Lua. */
    bool init(const QDir modulePath);

    /*! \brief This function handles a selected piemenu option.
     *
     *  This function is called when an option in the piemenu is selected.
     *  It retrieves the action to execute from the Lua module with the given option name.
     *  It retrieves the last application on the foreground, brings it to back to the foreground and executes the action on it.
     *  It return true when successful.
     */
    virtual bool handle(const QString optionName /*!< [in] parameter, a QString reference to the option to be executed.*/) const = 0;

    /*! \brief This function returns all options defined within the active Lua module.*/
    ModuleOptionsListModel* getOptions() const;

    bool initialized = false;   /*!< A boolean stating if the callbackhandler initialized correctly. */
    QString exeTitle;           /*!< A QString reference to the name of the last application executable on the foreground. */
    QDir modulePath;            /*!< A QDir reference to the path of module. */
    lua_State *L;               /*!< A lua_State pointer to the menu options pointers from the piemenu. */

protected:
    /*! \brief This function retrieves all info from the current active window.*/
    virtual void retrieveFocusWindowInfo() = 0;
    /*! \brief This function returns the previously active window to the foreground.*/
    virtual void restoreFocusWindow() const = 0;
    /*! \brief This function closes the Lua interpreter.*/
    virtual void close() const;
};

#endif // ABSTRACTCALLBACKHANDLER_H

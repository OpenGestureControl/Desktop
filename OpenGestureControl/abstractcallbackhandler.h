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
    bool init(QDir modulePath);

    /*! \brief This function returns all options defined within the active Lua module.*/
    ModuleOptionsListModel* getOptions();

    bool initialized = false;   /*!< A boolean stating if the callbackhandler initialized correctly. */
    QString exeTitle;           /*!< A QString reference to the name of the last application executable on the foreground. */
    QDir modulePath;            /*!< A QDir reference to the path of module. */
    lua_State *L;               /*!< A lua_State pointer to the menu options pointers from the piemenu. */

protected:
    /*! \brief This function retrieves all info from the current active window.*/
    virtual void retrieveFocusWindowInfo() = 0;
    /*! \brief This function returns the previously active window to the foreground.*/
    virtual void restoreFocusWindow() = 0;
    /*! \brief This function closes the Lua interpreter.*/
    virtual void close();
};

#endif // ABSTRACTCALLBACKHANDLER_H

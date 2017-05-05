///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CRUX_PROVIDER_SQL_ENGINE_HPP
#define CRUX_PROVIDER_SQL_ENGINE_HPP

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <QtCore/QDebug>
#include <QtCore/QByteArray>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtCore/QMetaType>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QVariantList>
#include <QtCore/QVariantMap>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlField>
#include <QtSql/QSqlIndex>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlRelation>
#include <QtSql/QSqlResult>
#include <string>
#include <stdarg.h>
#include "Driver.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Crux Namespace ///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Crux
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Crux::Provider Namespace /////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	namespace Provider
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Crux::Provider::Sql Namespace ////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////

		namespace Sql
		{
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Crux::Provider::Sql::Engine Class Definition /////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			class Engine : public QObject
			{

				///////////////////////////////////////////////////////////////////////////////////////////////////////
				/// Qt Object Recognition ////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////

				Q_OBJECT

				///////////////////////////////////////////////////////////////////////////////////////////////////////
				/// Protected Methods & Properties ///////////////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////

				protected:

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Static Properties ////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph This property contains the database connections
					 * @access protected
					 * @name Crux::Provider::Sql::Engine::mDatabaseConnections
					 * @namespace Crux::Provider::Sql
					 * @static
					 * @var QtCore/QMap<QtCore/QString, Crux::Provider::Sql::Engine*>
					 */
					static QMap<QString, Engine*> mDatabaseConnections;

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Properties ///////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph This property contains the database connection
					 * @access protected
					 * @name Crux::Provider::Sql::Engine::mConnection
					 * @namespace Crux::Provider::Sql
					 * @var QtSql/QSqlDatabase
					 */
					QSqlDatabase mConnection;

					/**
					 * @paragraph This property contains the name of the database to authenticate against
					 * @access protected
					 * @name Crux::Provider::Sql::Engine::mDatabase
					 * @namespace Crux::Provider::Sql
					 * @var QtCore/QString
					 */
					QString mDatabase;

					/**
					 * @paragraph This property contains the SQL driver to use
					 * @access protected
					 * @name Crux::Provider::Sql::Engine::mDriver
					 * @namespace Crux::Provider::Sql
					 * @var QtCore/QString
					 */
					QString mDriver;

					/**
					 * @paragraph This property contains the address of the host to connect to
					 * @access protected
					 * @name Crux::Provider::Sql::Engine::mHost
					 * @namespace Crux::Provider::Sql
					 * @var QtCore/QString
					 */
					QString mHost;

					/**
					 * @paragraph This property contains the name of the connection
					 * @access protected
					 * @name Crux::Provider::Sql::Engine::mName
					 * @namespace Crux::Provider::Sql
					 * @var QtCore/QString
					 */
					QString mName;

					/**
					 * @paragraph This property contains the password for the database authentication
					 * @access protected
					 * @name Crux::Provider::Sql::Engine::mPassword
					 * @namespace Crux::Provider::Sql
					 * @var QtCore/QString
					 */
					QString mPassword;

					/**
					 * @paragraph This property contains the port number in which the database server is listening on
					 * @access protected
					 * @name Crux::Provider::Sql::Engine::mPort
					 * @namespace Crux::Provider::Sql
					 * @var int
					 */
					int mPort;

					/**
					 * @paragraph This property contains the username for the database authentication
					 * @access protected
					 * @name Crux::Provider::Sql::Engine::mUsername
					 * @namespace Crux::Provider::Sql
					 * @var QtCore/QString
					 */
					QString mUsername;

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Methods //////////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph This method establishes a connection to the database
					 * @access protected
					 * @name Crux::Provider::Sql::Engine::connect()
					 * @namespace Crux::Provider::Sql
					 * @param strConnectionName
					 * @return void
					 */
					void connect();

				///////////////////////////////////////////////////////////////////////////////////////////////////////
				/// Public Methods & Properties //////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////

				public:

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Constructor //////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph This method instantiates a new SQL Engine Provider
					 * @access public
					 * @name Crux::Provider::Sql::Lite::Lite()
					 * @namespace Crux::Provider::Sql
					 * @param QObject* qoParent [0]
					 * @return
					 */
					Engine(QObject* qoParent = 0);

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Abstract Methods /////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph This method is responsible for describing a table in the database
					 * @access public
					 * @name Crux::Provider::Sql::Engine::describe()
					 * @namespace Crux::Provider::Sql
					 * @param QtCore/QString strTable
					 * @param QtCore/QString strSchema [QtCore/QString::null]
					 * @return QtCore/QMap<QtCore/QString, QtCore/QVector<QtCore/QString>>
					 */
					virtual QMap<QString, QVector<QString>> describe(QString strTable, QString strSchema = QString::null) = 0;

					/**
					 * @paragraph This method escapes a column's name for a SQL statement
					 * @access public
					 * @name Crux::Provider::Sql::Engine::escapeColumn()
					 * @param QtCore/QString strColumn
					 * @return QtCore/QString
					 */
					virtual QString escapeColumn(QString strColumn) = 0;

					/**
					 * @paragraph This method escapes the table name for a SQL statement
					 * @access public
					 * @name Crux::Provider::Sql::Engine::escapeTable()
					 * @namespace Crux::Provider::Sql
					 * @param QString strTable
					 * @return QtCore/QString
					 */
					virtual QString escapeTable(QString strTable) = 0;

					/**
					 * @paragraph This method quotes a value to be used in a SQL statement
					 * @access public
					 * @name Crux::Provider::Sql::Engine::escapeValue()
					 * @namespace Crux::Provider::Sql
					 * @param QtCore/QVariant varValue
					 * @return QtCore/QString
					 */
					virtual QString escapeValue(QVariant varValue) = 0;

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Static Methods ///////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph This method adds a new connection to the database connection pool
					 * @access public
					 * @name Crux::Provider::Sql::Engine::addConnection()
					 * @namespace Crux::Provider::Sql
					 * @param Crux::Provider::Sql::Engine* dbConnection
					 * @return void
					 * @static
					 */
					static void addConnection(Engine* dbConnection);

					/**
					 * @paragraph This method removes a connection from the database connection pool
					 * @access public
					 * @name Crux::Provider::Sql::Engine::deleteConnection()
					 * @namespace Crux::Provider::Sql
					 * @param QtCore/QString strName
					 * @return void
					 * @static
					 */
					static void deleteConnection(QString strName);

					/**
					 * @paragraph This method returns a connection from the database connection pool
					 * @access public
					 * @name Crux::Provider::Sql::Engine::getConnection()
					 * @namespace Crux::Provider::Sql
					 * @param QtCore/QString strName
					 * @return Crux::Provider::Sql::Engine*
					 * @static
					 */
					static Engine* getConnection(QString strName);

					/**
					 * @paragraph This method returns the global connection pool
					 * @access public
					 * @name Crux::Provider::Sql::Engine::getConnectionPool()
					 * @namespace Crux::Provider::Sql
					 * @return QtCore/QMap<QtCore/QString, Crux::Provider::Sql::Engine*>
					 * @static
					 */
					static QMap<QString, Engine*> getConnectionPool();

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Methods //////////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph This method formats a SQL statement
					 * @access public
					 * @name Crux::Provider::Sql::Engine::formatQueryString()
					 * @param const char* chrStatement
					 * @param va_list lstArguments
					 * @return QtSql/QSqlQuery
					 */
					QString formatQueryString(const char* chrStatement, va_list lstArguments);

					/**
					 * @paragraph This method returns a new query for the connection
					 * @access public
					 * @name Crux::Provider::Sql::Engine::newQuery()
					 * @namespace Crux::Provider::Sql
					 * @return QtSql/QSqlQuery*
					 */
					QSqlQuery* newQuery();

					/**
					 * @paragraph This method executes a SQL query against the database
					 * @access public
					 * @name Crux::Provider::Sql::Engine::query()
					 * @namespace Crux::Provider::Sql
					 * @param QtCore/QString strStatement
					 * @param QtCore/QVariantMap qvmReplacements [QVariantMap()]
					 * @return QtSql/QSqlQuery*
					 */
					QSqlQuery* query(QString strStatement, QVariantMap qvmReplacements = QVariantMap());

					/**
					 * @paragraph This method formats and executes a SQL query against the database
					 * @access public
					 * @name Crux::Provider::Sql::Engine::query()
					 * @param const char* chrStatement
					 * @param QtCore/QVariant ...
					 * @return QtSql/QSqlQuery
					 */
					QSqlQuery* query(const char* chrStatement, ...);

					/**
					 * @paragraph This method formats a SQL query
					 * @access public
					 * @name Crux::Provider::Sql::Engine::queryf()
					 * @param const char* chrStatement
					 * @param QtCore/QVariant ...
					 * @return QtCore/QString
					 */
					QString queryf(const char* chrStatement, ...);

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Getters //////////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph This method returns the database connection from the instance
					 * @access public
					 * @name Crux::Provider::Sql::Engine::getConnectionObject()
					 * @namespace Crux::Provider::Sql
					 * @return QtSql/QSqlDatabase
					 */
					QSqlDatabase getConnectionObject();

					/**
					 * @paragraph This method returns the database's name from the instance
					 * @access public
					 * @name Crux::Provider::Sql::Engine::getDatabase()
					 * @namespace Crux::Provider::Sql
					 * @return QtCore/QString
					 */
					QString getDatabase();

					/**
					 * @paragraph This method returns the database's driver name from the instance
					 * @access public
					 * @name Crux::Provider::Sql::Engine::getDriver()
					 * @namespace Crux::Provider::Sql
					 * @return QtCore/QString
					 */
					QString getDriver();

					/**
					 * @paragraph This method returns the database's host name from the instance
					 * @access public
					 * @name Crux::Provider::Sql::Engine::getHost()
					 * @namespace Crux::Provider::Sql
					 * @return QtCore/QString
					 */
					QString getHost();

					/**
					 * @paragraph This method returns the connection name from the instance
					 * @access public
					 * @name Crux::Provider::Sql::Engine::getName()
					 * @namespace Crux::Provider::Sql
					 * @return QtCore/QString
					 */
					QString getName();

					/**
					 * @paragraph This method returns the database's authentication password from the instance
					 * @access public
					 * @name Crux::Provider::Sql::Engine::getPassword()
					 * @namespace Crux::Provider::Sql
					 * @return QtCore/QString
					 */
					QString getPassword();

					/**
					 * @paragraph This method returns the database's port number from the instance
					 * @access public
					 * @name Crux::Provider::Sql::Engine::getPort()
					 * @namespace Crux::Provider::Sql
					 * @return int
					 */
					int getPort();

					/**
					 * @paragraph This method returns the database's authentication username from the instance
					 * @access public
					 * @name Crux::Provider::Sql::Engine::getUsername()
					 * @namespace Crux::Provider::Sql
					 * @return QtCore/QString
					 */
					QString getUsername();

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Setters //////////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph this method sets an external/existing connection into the instance
					 * @access public
					 * @name Crux::Provider::Sql::Engine::setConnectionObject()
					 * @namespace Crux::Provider::Sql
					 * @param QtSql/QSqlDatabase qsdExistingConnection
					 * @return Crux::Provider::Sql::Engine* this
					 */
					Engine* setConnectionObject(QSqlDatabase qsdExistingConnection);

					/**
					 * @paragraph this method sets the database name into the instance
					 * @access public
					 * @name Crux::Provider::Sql::Engine::setDatabase()
					 * @namespace Crux::Provider::Sql
					 * @param QtCore/QString strDatabaseName
					 * @return Crux::Provider::Sql::Engine* this
					 */
					Engine* setDatabase(QString strDatabaseName);

					/**
					 * @paragraph this method sets the database driver name into the instance
					 * @access public
					 * @name Crux::Provider::Sql::Engine::setDriver()
					 * @namespace Crux::Provider::Sql
					 * @param QtCore/QString strDriverName
					 * @return Crux::Provider::Sql::Engine* this
					 */
					Engine* setDriver(QString strDriverName);

					/**
					 * @paragraph this method sets the database's host name into the instance
					 * @access public
					 * @name Crux::Provider::Sql::Engine::setHost()
					 * @namespace Crux::Provider::Sql
					 * @param QtCore/QString strHostName
					 * @return Crux::Provider::Sql::Engine* this
					 */
					Engine* setHost(QString strHostName);

					/**
					 * @paragraph this method sets the name of the connection into the instance
					 * @access public
					 * @name Crux::Provider::Sql::Engine::setName()
					 * @namespace Crux::Provider::Sql
					 * @param QtCore/QString strName
					 * @return Crux::Provider::Sql::Engine* this
					 */
					Engine* setName(QString strName);

					/**
					 * @paragraph this method sets the database's authentication password into the instance
					 * @access public
					 * @name Crux::Provider::Sql::Engine::setPassword()
					 * @namespace Crux::Provider::Sql
					 * @param QtCore/QString strPassword
					 * @return Crux::Provider::Sql::Engine* this
					 */
					Engine* setPassword(QString strPassword);

					/**
					 * @paragraph this method sets the database's port number into the instance
					 * @access public
					 * @name Crux::Provider::Sql::Engine::setPort()
					 * @namespace Crux::Provider::Sql
					 * @param int intPort
					 * @return Crux::Provider::Sql::Engine* this
					 */
					Engine* setPort(int intPort);

					/**
					 * @paragraph this method sets the database's authentication user name into the instance
					 * @access public
					 * @name Crux::Provider::Sql::Engine::setUsername()
					 * @namespace Crux::Provider::Sql
					 * @param QtCore/QString strUsername
					 * @return Crux::Provider::Sql::Engine* this
					 */
					Engine* setUsername(QString strUsername);

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			}; /// End Crux::Provider::Sql::Engine Class Definition //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		} /// End Crux::Provider::Sql Namespace //////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	} /// End Crux::Provider Namespace ///////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} /// End Crux Namespace /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif /// End Definitions ///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

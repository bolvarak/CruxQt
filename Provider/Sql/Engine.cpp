///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Engine.hpp"

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
			/// Properties ///////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			QMap<QString, Engine*> Engine::mDatabaseConnections = QMap<QString, Engine*>();

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Constructor //////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			Engine::Engine(QObject *qoParent) : QObject(qoParent)
			{
				// TODO - Maybe more initialization here?!?!
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Protected Methods ////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			void Engine::connect()
			{
				// Instantiate the new connection
				this->mConnection = QSqlDatabase::addDatabase(this->mDriver, this->mName.toLatin1());
				// Set the database name into the connection
				this->mConnection.setDatabaseName(this->mDatabase);
				// Check for a username
				if (!this->mUsername.isEmpty() && !this->mUsername.isNull()) {
					// Set the username into the connection
					this->mConnection.setUserName(this->mUsername);
				}
				// Check for a password
				if (!this->mPassword.isEmpty() && !this->mPassword.isNull()) {
					// Set the password into the connection
					this->mConnection.setPassword(this->mPassword);
				}
				// Check the driver type
				if ((this->mDriver != Driver::SQLite) && (this->mDriver != Driver::SQLite2)) {
					// Set the host into the connection
					this->mConnection.setHostName(this->mHost);
					// Set the port into the connection
					this->mConnection.setPort(this->mPort);
				}
				// Try to open the connection
				if (!this->mConnection.isOpen() && !this->mConnection.open()) {
					// TODO - Add Error Signal Emission
					qDebug() << this->mConnection.lastError();
				}
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Public Static Methods ////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			void Engine::addConnection(Engine *dbConnection)
			{
				// Set the connection into the pool
				Engine::mDatabaseConnections.insert(dbConnection->getName(), dbConnection);
			}

			void Engine::deleteConnection(QString strName)
			{
				// Remove the connection from the pool
				Engine::mDatabaseConnections.remove(strName);
			}

			Engine* Engine::getConnection(QString strName)
			{
				// Return a connection from the pool
				return Engine::mDatabaseConnections.value(strName);
			}

			QMap<QString, Engine*> Engine::getConnectionPool()
			{
				// Return the entire connection pool
				return Engine::mDatabaseConnections;
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Public Methods ///////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			QString Engine::formatQueryString(const char *chrStatement, va_list lstArguments)
			{
				// Create our query placeholder
				QString strQuery;
				// Define our character iterator
				int intCharacter = 0;
				// Define our statement
				QString strStatement = QString(chrStatement);
				// Iterate to the end of the format string
				while (intCharacter < strStatement.size()) {
					// Check for a placeholder
					if (strStatement.at(intCharacter).toLatin1() == '%') {
						// Check the placeholder
						if (strStatement.at(intCharacter + 1).toLatin1() == '%') {
							// Append the percentage sign
							strQuery.append("%");
						} else if (strStatement.at(intCharacter + 1).toLower().toLatin1() == 'c') {
							// Escape and append the column name
							strQuery.append(this->escapeColumn(va_arg(lstArguments, QString)));
							// Increment the argument
							++chrStatement;
						} else if (strStatement.at(intCharacter + 1).toLower().toLatin1() == 't') {
							// Escape and append the table name
							strQuery.append(this->escapeTable(va_arg(lstArguments, QString)));
							// Increment the argument
							++chrStatement;
						} else if (strStatement.at(intCharacter + 1).toLower().toLatin1() == 'd') {
							// Append the placeholder to the query
							strQuery.append(this->escapeValue(QVariant::fromValue(va_arg(lstArguments, double))));
							// Increment the argument
							++chrStatement;
						} else if (strStatement.at(intCharacter + 1).toLower().toLatin1() == 'f') {
							// Append the placeholder to the query
							strQuery.append(this->escapeValue(QVariant::fromValue(va_arg(lstArguments, double))));
							// Increment the argument
							++chrStatement;
						} else if (strStatement.at(intCharacter + 1).toLower().toLatin1() == 'i') {
							// Append the placeholder to the query
							strQuery.append(this->escapeValue(QVariant::fromValue(va_arg(lstArguments, int))));
							// Increment the argument
							++chrStatement;
						} else if (strStatement.at(intCharacter + 1).toLower().toLatin1() == 'v') {
							// Append the placeholder to the query
							strQuery.append(this->escapeValue(va_arg(lstArguments, QVariant)));
							// Increment the argument
							++chrStatement;
						} else {
							// Append the placeholder to the query
							strQuery.append(this->escapeValue(QVariant::fromValue(va_arg(lstArguments, QString))));
							// Increment the argument
							++chrStatement;
						}
						// Increment the character
						++intCharacter;
					} else {
						// Append the character to the query
						strQuery.append(strStatement.at(intCharacter));
					}
					// Increment the statement
					++chrStatement;
					// Increment the character
					++intCharacter;
				}
				// We're done
				return strQuery.trimmed();
			}

			QSqlQuery* Engine::newQuery()
			{
				// Return a new query
				return new QSqlQuery(this->mConnection);
			}

			QSqlQuery* Engine::query(QString strStatement, QVariantMap qvmReplacements)
			{
				// Instantiate the query
				QSqlQuery* qsqStatement = new QSqlQuery(this->mConnection);
				// Prepare the statement
				qsqStatement->prepare(strStatement);
				// Check for replacements
				if (!qvmReplacements.isEmpty()) {
					// Iterate over the replacements
					foreach (QString strKey, qvmReplacements.keys()) {
						// Check the first character
						if (strKey.at(0).toLatin1() == ':') {
							// Bind the value
							qsqStatement->bindValue(strKey, qvmReplacements.value(strKey));
						} else {
							// Bind the value
							qsqStatement->bindValue(QString(":%1").arg(strKey), qvmReplacements.value(strKey));
						}
					}
				}
				// Try to execute the query
				if (!qsqStatement->exec()) {
					// TODO - Emit Error Signal
				}
				// Return the result set
				return qsqStatement;
			}

			QSqlQuery* Engine::query(const char* chrStatement, ...)
			{
				// Grab the variadic arguments
				va_list valArguments;
				// Start the iteration over the arguments
				va_start(valArguments, chrStatement);
				// Grab the query string
				QString strQuery = this->formatQueryString(chrStatement, valArguments);
				// We're done with the variadic arguments
				va_end(valArguments);
				// Create the new query
				QSqlQuery* qsqFormatted = new QSqlQuery(this->mConnection);
				// Prepare the statement
				qsqFormatted->prepare(strQuery);
				// Try to execute the query
				if (!qsqFormatted->exec()) {
					// TODO - Emit Error Signal
				}
				// Return the result set
				return qsqFormatted;
			}

			QString Engine::queryf(const char* chrStatement, ...)
			{
				// Grab the variadic arguments
				va_list valArguments;
				// Unpack the arguments
				va_start(valArguments, chrStatement);
				// Format the query string
				QString strQuery = this->formatQueryString(chrStatement, valArguments);
				// We're done with the variadic arguments
				va_end(valArguments);
				// We're done, return the query
				return strQuery;
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Getters //////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			QSqlDatabase Engine::getConnectionObject()
			{
				// Return the connection from the instance
				return this->mConnection;
			}

			QString Engine::getDatabase()
			{
				// Return the database name from the instance
				return this->mDatabase;
			}

			QString Engine::getDriver()
			{
				// Return the database driver from the instance
				return this->mDriver;
			}

			QString Engine::getHost()
			{
				// Return the database's host name from the instance
				return this->mHost;
			}

			QString Engine::getName()
			{
				// Return the connection name from the instance
				return this->mName;
			}

			QString Engine::getPassword()
			{
				// Return the database's authentication password from the instance
				return this->mPassword;
			}

			int Engine::getPort()
			{
				// Return the database's port number from the instance
				return this->mPort;
			}

			QString Engine::getUsername()
			{
				// Return the database's authentication username from the instance
				return this->mUsername;
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Setters //////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			Engine* Engine::setConnectionObject(QSqlDatabase qsdExistingConnection)
			{
				// Set the connection into the instance
				this->mConnection = qsdExistingConnection;
				// We're done, return the instance
				return this;
			}

			Engine* Engine::setDatabase(QString strDatabaseName)
			{
				// Set the database name into the instance
				this->mDatabase = strDatabaseName;
				// We're done, return the instance
				return this;
			}

			Engine* Engine::setDriver(QString strDriverName)
			{
				// Set the driver into the instance
				this->mDriver = strDriverName.toUpper();
				// We're done, return the instance
				return this;
			}

			Engine* Engine::setHost(QString strHostName)
			{
				// Set the database's host name into the instance
				this->mHost = strHostName;
				// We're done, return the instance
				return this;
			}

			Engine* Engine::setName(QString strName)
			{
				// Set the connection name into the instance
				this->mName = strName;
				// We're done, return the instance
				return this;
			}

			Engine* Engine::setPassword(QString strPassword)
			{
				// Set the database's authentication password into the instance
				this->mPassword = strPassword;
				// We're done, return the instance
				return this;
			}

			Engine* Engine::setPort(int intPort)
			{
				// Set the database's port number into the instance
				this->mPort = intPort;
				// We're done, return the instance
				return this;
			}

			Engine* Engine::setUsername(QString strUsername)
			{
				// Set the database's authentication username into the instance
				this->mUsername = strUsername;
				// We're done, return the instance
				return this;
			}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		} /// End Crux::Provider::Sql Namespace //////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	} /// End Crux::Provider Namespace ///////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} /// End Crux Namespace /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

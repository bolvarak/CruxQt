///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Model.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Imports //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using Crux::Provider::Sql::Engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Crux Namespace ///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Crux
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Crux::Fluent Namespace ///////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	namespace Fluent
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Crux::Fluent::Sql Namespace //////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////

		namespace Sql
		{
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Constructor //////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			Model::Model(QString strConnectionName, QString strTable, QString strPrimaryKey, QString strSchema, QObject *qoParent) : QObject(qoParent) {
				// Set the connection name into the instance
				this->mConnectionName = strConnectionName;
				// Set the table name into the instance
				this->mTable = strTable;
				// Set the schema into the instance
				this->mSchema = strSchema;
				// Set the primary key into the instance
				this->mPrimaryKey = strPrimaryKey;
				// Initialize the column map
				this->mColumns = QVariantMap();
				// Initialize the error
				this->mError = QString::null;
				// Initialize the empty flag
				this->mIsEmpty = true;
				// Initialize the one-to-many relationship container
				this->mOneToMany = QMap<QString, QVector<Model *>>();
				// Initialize the one-to-one relationship container
				this->mOneToOne = QMap<QString, Model *>();
				// Initialize the table description container
				this->mTableDescription = QMap<QString, QVector<QString>>();
				// Initialize the WHERE clauses
				this->mWhere = QString::null;
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Protected Methods ////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			QString Model::deleteStatement() {
				// Check for a schema
				if (this->mSchema == QString::null) {
					// Return the query
					return Engine::getConnection(this->mConnectionName)->queryf("DELETE FROM %T WHERE %T.%C = %v", this->mTable, this->mTable, this->mPrimaryKey, this->mColumns.value(this->mPrimaryKey));
				} else {
					// Return the query
					return Engine::getConnection(this->mConnectionName)->queryf("DELETE FROM %T.%T WHERE %T.%C = %v", this->mSchema, this->mTable, this->mTable, this->mPrimaryKey, this->mColumns.value(this->mPrimaryKey));
				}
			}

			bool Model::connectionIsOpen() {
				// Reset the error on the instance
				this->mError = QString::null;
				// Check the connection
				if (Engine::getConnection(this->mConnectionName)->getConnectionObject().isOpen()) {
					// We're done, the connection is already open
					return true;
				} else if (!Engine::getConnection(this->mConnectionName)->getConnectionObject().open()) {
					// TODO - Emit Error Signal
					// Set the error message into the instance
					this->mError = Engine::getConnection(this->mConnectionName)->getConnectionObject().lastError().text();
					// We're done, the connection cannot be opened
					return false;
				} else {
					// We're done, the connection was successfully opened
					return true;
				}
			}

			QString Model::findColumn(QString strColumn) {
				// Check for the column as-is
				if (this->mColumns.contains(strColumn)) {
					// We're done, we've the column exists as-is
					return strColumn;
				}
				// Create our regular expression pattern
				QRegExp rxpSanitize("/(_|-|\\s)/", Qt::CaseInsensitive);
				// Iterate over the columns
				for (QString strThisColumn: this->mColumns.keys()) {
					// Compare the columns
					if (strThisColumn.replace(rxpSanitize, "").toLower() == strColumn.replace(rxpSanitize, "").toLower()) {
						// We're done, we've found the column
						return strThisColumn;
					}
				}
				// We're done, the column could not be found
				return QString::null;
			}

			QString Model::insertStatement(bool blnIncludePrimaryKey) {
				// Define our statement
				QString strStatement;
				// Check for a schema
				if (this->mSchema == QString::null) {
					// Start the statement
					strStatement = Engine::getConnection(this->mConnectionName)->queryf("INSERT INTO %T", this->mTable);
				} else {
					// Start the statement
					strStatement = Engine::getConnection(this->mConnectionName)->queryf("INSERT INTO %T.%T", this->mSchema, this->mTable);
				}
				// Define our columns container
				QStringList qslColumnToInsert;
				// Define our values container
				QStringList qslValueToInsert;
				// Localize the keys
				QStringList qslColumns = this->mColumns.keys();
				// Iterate over the columns
				for (QString strColumn: this->mColumns.keys()) {
					// Check the column
					if ((strColumn.toLower() != this->mPrimaryKey.toLower()) || blnIncludePrimaryKey) {
						// Add the column to the list
						qslColumnToInsert.append(Engine::getConnection(this->mConnectionName)->queryf("%T.%C", this->mTable, strColumn));
						// Add the value to the list
						qslValueToInsert.append(Engine::getConnection(this->mConnectionName)->queryf("%v", this->mColumns.value(strColumn)));
					}
				}
				// Reset the WHERE clauses
				this->mWhere = QString::null;
				// Return the finalized query
				return QString("%1 (%2) VALUES (%3);").arg(strStatement, qslColumns.join(", "), qslValueToInsert.join(", "));
			}

			bool Model::primaryKeyExists() {
				// Has the primary key column been set
				if (this->mPrimaryKey.isNull() || this->mPrimaryKey.isEmpty() || (this->mPrimaryKey == QString::null)) {
					// We're done, the primary key has not been set
					return false;
				}
				// We're done, return the comparison
				return !(this->findColumn(this->mPrimaryKey) == QString::null);
			}

			QString Model::selectStatement(QString strColumn, QVariant varValue) {
				// Define our statement container
				QString strStatement;
				// Check for a schema
				if (this->mSchema == QString::null) {
					// Start the statement
					strStatement = Engine::getConnection(this->mConnectionName)->queryf("SELECT %T.* FROM %T", this->mTable, this->mTable);
				} else {
					// Start the statement
					strStatement = Engine::getConnection(this->mConnectionName)->queryf("SELECT %T.* FROM %T.%T", this->mTable, this->mSchema, this->mTable);
				}
				// Check for a custom WHERE clause
				if (this->mWhere == QString::null) {
					// Append the WHERE clause to the statement
					strStatement.append(Engine::getConnection(this->mConnectionName)->queryf("WHERE %T.%C = %v", this->mTable, strColumn, varValue).prepend(" "));
				} else {
					// Append the custom WHERE clause to the statement
					strStatement.append(this->mWhere.prepend(" "));
				}
				// Reset the WHERE clauses
				this->mWhere = QString::null;
				// We're done, return the statement
				return strStatement;
			}

			bool Model::tableDescription(bool blnCloseConnectionWhenDone) {
				// Reset our error
				this->mError = QString::null;
				// Load the description
				this->mTableDescription = this->getConnection()->describe(this->mTable, this->mSchema);
				// Check the description
				if (this->mTableDescription.isEmpty()) {
					// TODO - Emit Error Signal
					// Reset the error into the instance
					this->mError = QString("Unable to load table description for table:  %1").arg(this->mTable);
					// We're done
					return false;
				}
				// Iterate over the columns
				for (QString strColumn: this->mTableDescription.keys()) {
					// Check the column data length
					if ((this->mTableDescription.value(strColumn).size() >= 3) &&
						(this->mTableDescription.value(strColumn).at(2).toLower() == "pri")) {
						// Set the primary key into the instance
						this->mPrimaryKey = strColumn;
					}
				}
				// Check the close flag
				if (blnCloseConnectionWhenDone) {
					// Close the connection
					this->getConnection()->getConnectionObject().close();
				}
				// We're done, the table's description has been loaded
				return true;
			}

			QString Model::updateStatement() {
				// Define our query placeholder
				QString strStatement;
				// Check for a schema
				if (this->mSchema == QString::null) {
					// Start the statement
					strStatement = Engine::getConnection(this->mConnectionName)->queryf("UPDATE %T SET", this->mTable);
				} else {
					// Start the statement
					strStatement = Engine::getConnection(this->mConnectionName)->queryf("UPDATE %T.%T SET", this->mSchema, this->mTable);
				}
				// Define our pairs container
				QStringList qslPairs;
				// Iterate over the column values
				for (QString strColumn: this->mColumns.keys()) {
					// Check for a primary key
					if (strColumn.toLower() != this->mPrimaryKey.toLower()) {
						// Add the pair to the container
						qslPairs.append(Engine::getConnection(this->mConnectionName)->queryf("SET %T.%C = %v", this->mTable, strColumn, this->mColumns.value(strColumn)));
					}
				}
				// Append the pairs to the query
				strStatement.append(qslPairs.join(", "));
				// Check for a custom WHERE clause
				if (this->mWhere != QString::null) {
					// Append the custom WHERE clause to the statement
					strStatement.append(this->mWhere);
				} else {
					// Append the WHERE clause to the statement
					strStatement.append(Engine::getConnection(this->mConnectionName)->queryf("WHERE %T.%C = %v", this->mTable, this->mPrimaryKey, this->mColumns.value(this->mPrimaryKey)));
				}
				// Reset the WHERE clauses
				this->mWhere = QString::null;
				// We're done, return the statement
				return strStatement.append(";");
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Public Methods ///////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			bool Model::hasError() {
				// Return the error state
				return !(this->mError.isEmpty() || this->mError.isNull());
			}

			Model *Model::hasMany(Model *modContainer, QString strColumn, QString strTargetColumn) {
				// Define our sql statement
				QString strStatement;
				// Define our primary key container
				QString strPrimaryKey = QString::null;
				// Describe the table
				QMap<QString, QVector<QString>> mapDescription = this->getConnection()->describe(this->mTable, this->mSchema);
				// Check the primary key
				if (mapDescription.isEmpty()) {
					// TODO - Emit Error Signal
					// Reset the error
					this->mError = QString("Unable to table description for table:  %1").arg(modContainer->getTable());
					// We're done, return the instance
					return this;
				}
				// Iterate over the description
				for (QString strThisColumn: mapDescription.keys()) {
					// Check the column data
					if ((mapDescription.value(strThisColumn).size() >= 3) &&
						(mapDescription.value(strThisColumn).at(2).toLower() == "pri")) {
						// Reset the primary key
						strPrimaryKey = strThisColumn;
					}
				}
				// Check the primary key
				if (strPrimaryKey == QString::null) {
					// TODO - Emit Error Signal
					// Reset the error
					this->mError = QString("Unable to find primary key for table:  %1").arg(modContainer->getTable());
					// We're done, return the instance
					return this;
				}
				// Check for a schema
				if (modContainer->getSchema().isEmpty() || modContainer->getSchema().isNull() ||
					(modContainer->getSchema() == QString::null)) {
					// Start the statement
					strStatement = this->getConnection()->queryf("SELECT %T.%C FROM %T", modContainer->getTable(), strPrimaryKey, modContainer->getTable());
				} else {
					// Start the statement
					strStatement = this->getConnection()->queryf("SELECT %T.%C FROM %T.%T", modContainer->getTable(), strPrimaryKey, modContainer->getSchema(), modContainer->getTable());
				}
				// Check for a column
				if ((strColumn == QString::null) && (strTargetColumn != QString::null)) {
					// Add the WHERE clause
					strStatement.append(this->getConnection()->queryf("WHERE %T.%C = %v", modContainer->getTable(), strTargetColumn, this->get(this->mPrimaryKey)).prepend(" "));
				} else if ((strColumn != QString::null) && (strTargetColumn == QString::null)) {
					// Add the WHERE clause
					strStatement.append(this->getConnection()->queryf("WHERE %T.%C = %v", modContainer->getTable(), this->mPrimaryKey, this->get(strColumn)).prepend(" "));
				} else if ((strColumn != QString::null) && (strTargetColumn != QString::null)) {
					// Add the WHERE clause
					strStatement.append(this->getConnection()->queryf("WHERE %T.%C = %v", modContainer->getTable(), strTargetColumn, this->get(strColumn)).prepend(" "));
				} else {
					// Add the WHERE clause
					strStatement.prepend(this->getConnection()->queryf("WHERE %T.%C = %v", modContainer->getTable(), this->mPrimaryKey, this->get(this->mPrimaryKey)).prepend(" "));
				}
				// Grab a new query
				QSqlQuery *qsqOneToMany = this->getConnection()->newQuery();
				// Try to execute the query
				if (!qsqOneToMany->exec(strStatement)) {
					// TODO - Emit Error Signal
					// Reset the error
					this->mError = qsqOneToMany->lastError().text();
					// We're done, return the instance
					return this;
				}
				// Define our list container
				QVector<Model *> vecRelationships;
				// Iterate over the results
				while (qsqOneToMany->next()) {
					// Define our relationship model
					Model *modRelationship = new Model(modContainer->getConnectionName(), modContainer->getTable(), strPrimaryKey, modContainer->getSchema());
					// Add the model instance to the list
					vecRelationships.push_back(modRelationship->load(qsqOneToMany->value(strPrimaryKey), strPrimaryKey));
				}
				// Add the relationships to the instance
				this->mOneToMany.insert(modContainer->getTable(), vecRelationships);
				// We're done, return the instance
				return this;
			}

			Model *Model::hasOne(Model *modContainer, QString strSourceColumn, QString strTargetColumn) {
				// Check for a column
				if ((strSourceColumn == QString::null) && (strTargetColumn != QString::null)) {
					// Set the child into the instance
					this->mOneToOne.insert(modContainer->getTable(), modContainer->load(this->get(this->mPrimaryKey), strTargetColumn));
				} else if ((strSourceColumn != QString::null) && (strTargetColumn == QString::null)) {
					// Set the child into the instance
					this->mOneToOne.insert(modContainer->getTable(), modContainer->load(this->get(strSourceColumn), this->mPrimaryKey));
				} else if ((strSourceColumn != QString::null) && (strTargetColumn != QString::null)) {
					// Set the child into the instance
					this->mOneToOne.insert(modContainer->getTable(), modContainer->load(this->get(strSourceColumn), strTargetColumn));
				} else {
					// Set the child into the instance
					this->mOneToOne.insert(modContainer->getTable(), modContainer->load(this->get(this->mPrimaryKey), this->mPrimaryKey));
				}
				// We're done, return the instance
				return this;
			}

			bool Model::isEmpty() {
				// Return the empty state
				return (this->mIsEmpty || this->mColumns.isEmpty());
			}

			Model *Model::load(QVariant varUniqueIdentifier, QString strColumn) {
				// Make sure the connection is open
				if (!this->connectionIsOpen()) {
					// We're done, there is no connection
					return this;
				}
				// Reset the error message in the instance
				this->mError = QString::null;
				// Make sure we have table meta data
				if (this->mTableDescription.isEmpty() && !this->tableDescription(false)) {
					// We're done, we don't have the table's description
					return this;
				}
				// Grab a new query
				QSqlQuery *qsqLoad = Engine::getConnection(this->mConnectionName)->newQuery();
				// We only want to traverse forward in the iterator
				qsqLoad->setForwardOnly(true);
				// Try to execute the query
				if (!qsqLoad->exec(this->selectStatement((strColumn == QString::null) ? this->mPrimaryKey : strColumn, varUniqueIdentifier))) {
					// TODO - Emit Error Signal
					// Reset the error into the instance
					this->mError = qsqLoad->lastError().text();
					// We're done, could not execute the query
					return this;
				}
				// Check the results
				if (qsqLoad->size() == 0) {
					// Reset the empty state of the instance
					this->mIsEmpty = true;
					// We're done, no results
					return this;
				}
				// Clear the column data map
				this->mColumns.clear();
				// Seek the first record
				qsqLoad->seek(0);
				// Iterate over the columns
				for (QString strThisColumn: this->mTableDescription.keys()) {
					// Set the value into the column data map
					this->mColumns.insert(strThisColumn, qsqLoad->value(strThisColumn));
				}
				// We're done with the query
				qsqLoad->finish();
				// We're done, return the instance
				return this;
			}

			Model *Model::purge() {
				// Make sure we have a primary key
				if (!this->primaryKeyExists()) {
					// We're done, nothing to do
					return this;
				}
				// Make sure the connection is open
				if (!this->connectionIsOpen()) {
					// We're done, cannot establish a connection
					return this;
				}
				// Reset the error on the instance
				this->mError = QString::null;
				// Grab a new query
				QSqlQuery *qsqPurge = Engine::getConnection(this->mConnectionName)->newQuery();
				// Try to execute the query
				if (!qsqPurge->exec(this->deleteStatement())) {
					// TODO - Emit Error Signal
					// Reset the error into the instance
					this->mError = qsqPurge->lastError().text();
					// We're done, the query failed
					return this;
				}
				// We're done with the statement
				qsqPurge->finish();
				// We're done, return the instance
				return this;
			}

			Model *Model::recover() {
				// Check for a primary key
				if (!this->primaryKeyExists()) {
					// We're done, there's nothing to do
					return this;
				}
				// Save the model
				return this->save(true);
			}

			Model *Model::save(bool blnForceInsert) {
				// Check the connection open state
				if (!this->connectionIsOpen()) {
					// We're done
					return this;
				}
				// Reset the error on the instance
				this->mError = QString::null;
				// Grab a new query
				QSqlQuery *qsqSave = Engine::getConnection(this->mConnectionName)->newQuery();
				// Define our statement container
				QString strStatement;
				// Check the primary key and force insert boolean
				if (this->primaryKeyExists() && blnForceInsert) {
					// Prepare the statement
					strStatement = this->insertStatement(true);
				} else if (this->primaryKeyExists() && !blnForceInsert) {
					// Prepare the statement
					strStatement = this->updateStatement();
				} else {
					// Prepare the statement
					strStatement = this->insertStatement(false);
				}
				// Try to execute the query
				if (!qsqSave->exec(strStatement)) {
					// TODO - Emit Error Signal
					// Reset the error into the instance
					this->mError = qsqSave->lastError().text();
					// We're done, unable to execute query
					return this;
				}
				// Reload the model
				this->load(qsqSave->lastInsertId(), this->mPrimaryKey);
				// Close the query
				qsqSave->finish();
				// We're done, return the instance
				return this;
			}

			Model *Model::where(const char *chrClauses, ...) {
				// Define our argument container
				va_list valArguments;
				// Unpack the arguments
				va_start(valArguments, chrClauses);
				// Set the WHERE clauses into the instance
				this->mWhere = Engine::getConnection(this->mConnectionName)->formatQueryString(chrClauses, valArguments);
				// We're done with the argument list
				va_end(valArguments);
				// We're done, return the instance
				return this;
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Converters ///////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			QJsonDocument Model::toJson() {
				// Return the JSON document object
				return QJsonDocument(QJsonObject::fromVariantMap(this->toMap()));
			}

			QVariantMap Model::toMap() {
				// Localize the column data map
				QVariantMap qvmMap = this->mColumns;
				// Check for one-to-one relationships
				if (!this->mOneToOne.isEmpty()) {
					// Iterate over the one-to-one relationships
					for (QString strTable: this->mOneToOne.keys()) {
						// Add the relationship to map
						qvmMap.insert(strTable, this->mOneToOne.value(strTable)->toMap());
					}
				}
				// Check for one-to-many relationships
				if (!this->mOneToMany.isEmpty()) {
					// Iterate over the one-to-many relationships
					for (QString strTable: this->mOneToMany.keys()) {
						// Define our list
						QVariantList lstRelationships;
						// Iterate over the models
						for (Model *modRelationship: this->mOneToMany.value(strTable)) {
							// Add the model to the list
							lstRelationships.append(modRelationship->toMap());
						}
						// Add the relationship to the map
						qvmMap.insert(strTable, lstRelationships);
						// Clear the relationships
						lstRelationships.clear();
					}
				}
				// We're done, return the map
				return qvmMap;
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Getters //////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			QVariant Model::get(QString strColumn, QVariant varDefault) {
				// Return the getColumn method
				return this->getColumn(strColumn, varDefault);
			}

			QVariant Model::getColumn(QString strColumn, QVariant varDefault) {
				// Search for the column
				strColumn = this->findColumn(strColumn);
				// Do we have a column
				if (strColumn.isNull()) {
					// We're done, return the default value
					return varDefault;
				}
				// Return the column data
				return this->mColumns.value(strColumn);
			}

			QVariantMap Model::getColumns() {
				// Return the columns from the instance
				return this->mColumns;
			}

			Engine *Model::getConnection() {
				// Return the connection from the instance
				return Engine::getConnection(this->mConnectionName);
			}

			QString Model::getConnectionName() {
				// Return the connection name from the instance
				return this->mConnectionName;
			}

			QString Model::getError() {
				// Return the error message from the instance
				return this->mError;
			}

			QString Model::getPrimaryKey() {
				// Return the primary key from the instance
				return this->mPrimaryKey;
			}

			QString Model::getSchema() {
				// Return the schema from the instance
				return this->mSchema;
			}

			QString Model::getTable() {
				// Return the table from the instance
				return this->mTable;
			}

			QMap<QString, QVector<QString>> Model::getTableDescription() {
				// Return the table description from the instance
				return this->mTableDescription;
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Setters //////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			Model *Model::set(QString strColumn, QVariant varValue) {
				// Return the setColumn method
				return this->setColumn(strColumn, varValue);
			}

			Model *Model::setColumn(QString strColumn, QVariant varValue) {
				// Search for the column in the data map
				strColumn = this->findColumn(strColumn);
				// Do we have a match
				if (!strColumn.isNull()) {
					// Set the column value
					this->mColumns.insert(strColumn, varValue);
				}
				// We're done, return the instance
				return this;
			}

			Model *Model::setColumns(QVariantMap mapColumns) {
				// Set the columns into the instance
				this->mColumns = mapColumns;
				// We're done, return the instance
				return this;
			}

			Model *Model::setConnection(Engine *dbConnection) {
				// Check for an instance name
				if (this->mConnectionName.isEmpty() || this->mConnectionName.isNull()) {
					// Set the name into the instance
					this->setConnectionName(dbConnection->getName());
				}
				// Add the connection
				// Set the connection into the instance
				Engine::addConnection(dbConnection);
				// We're done, return the instance
				return this;
			}

			Model *Model::setConnectionName(QString strName) {
				// Set the connection name into the instance
				this->mConnectionName = strName;
				// We're done, return the instance
				return this;
			}

			Model *Model::setError(QString strMessage) {
				// Set the error into the instance
				this->mError = strMessage;
				// We're done, return the instance
				return this;
			}

			Model *Model::setPrimaryKey(QString strColumn) {
				// Set the primary key into the instance
				this->mPrimaryKey = strColumn;
				// We're done, return the instance
				return this;
			}

			Model *Model::setSchema(QString strName) {
				// Set the schema into the instance
				this->mSchema = strName;
				// We're done, return the instance
				return this;
			}

			Model *Model::setTable(QString strName) {
				// Set the table into the instance
				this->mTable = strName;
				// We're done, return the instance
				return this;
			}

			Model *Model::setTableDescription(QMap<QString, QVector<QString>> mapDescription) {
				// Set the table description into the instance
				this->mTableDescription = mapDescription;
				// We're done, return the instance
				return this;
			}

			Model *Model::setWhereClause(QString strClause) {
				// Set the WHERE clause(s) into the instance
				this->mWhere = strClause;
				// We're done, return the instance
				return this;
			}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		} /// End Crux::Fluent::Sql Namespace ////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	} /// End Crux::Fluent Namespace /////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} /// End Crux Namespace /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
